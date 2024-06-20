#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <boost/log/trivial.hpp>

#include "AmigaFile.hpp"
#include "Object3D.hpp"

namespace
{
  
unsigned short swapByteOrder(const unsigned short value)
{
  const char* bytes = reinterpret_cast<const char*>(&value);
  const unsigned char lower = bytes[0];
  const unsigned char higher = bytes[1];
  const unsigned short result = static_cast<unsigned short> ( (lower << 8) | higher );
  return result;
}

// unsigned int swapByteOrder(const unsigned int value)
// {
//   const char* bytes = reinterpret_cast<const char*>(&value);
//   const unsigned char byte0 = bytes[0];
//   const unsigned char byte1 = bytes[1];
//   const unsigned char byte2 = bytes[2];
//   const unsigned char byte3 = bytes[3];
//   const unsigned int result = static_cast<unsigned int> ( (byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3 );
//   return result;
// }
  
// void WriteByte(std::ofstream& file, unsigned char value)
// {
//   file.write(reinterpret_cast<const char*>(&value), sizeof(char));
// }

void WriteWord(std::ofstream& file, unsigned short value)
{
  unsigned short swappedShort = swapByteOrder(value);
  file.write(reinterpret_cast<const char*>(&swappedShort), sizeof(short));
}

unsigned short ReadWord(std::ifstream& file)
{
  unsigned short swappedShort;
  file.read(reinterpret_cast<char*>(&swappedShort), sizeof(short));
  return swapByteOrder(swappedShort);
}
  
// void WriteLong(std::ofstream& file, unsigned int value)
// {
//   unsigned int swappedValue = swapByteOrder(value);
//   file.write(reinterpret_cast<const char*>(&swappedValue), sizeof(unsigned int));
// }
  
}

bool AmigaFile::Save(const Object3D& object3d)
{
  // UWAGA - współrzędne są zapisywane w odwrotnej kolejności
  // ponieważ funkcja obrotu (na amidze) zapisuje dane w odwrotnej kolejności (jak na stosie)

  std::ofstream file(object3d.mName, std::ios::out | std::ios::binary);
  
  if (!file)
    {
      BOOST_LOG_TRIVIAL(error) << "File is not opened (" << object3d.mName << ")" ;
      return false;
    }

  BOOST_LOG_TRIVIAL(debug) << "Save file: " << object3d.mName;

  WriteWord(file, object3d.mVertices.size());
  WriteWord(file, object3d.mFaces.size());

  for (auto it = object3d.mVertices.rbegin(); it != object3d.mVertices.rend(); ++it)
    {
      auto value = *it;
      WriteWord(file, value.mX);
      WriteWord(file, value.mY);
      WriteWord(file, value.mZ);
    }

  for (auto it = object3d.mNormalVectorsInVertices.rbegin(); it != object3d.mNormalVectorsInVertices.rend(); ++it)
    {
      auto value = *it;
      WriteWord(file, value.mX);
      WriteWord(file, value.mY);
      WriteWord(file, value.mZ);
    }
  
  for(auto face : object3d.mFaces)
    {
      WriteWord(file, 0);
      WriteWord(file, face.size());
      for (auto number : face)
        {
          WriteWord(file, number * 8);
        }
    }

  for (auto it = object3d.mNormalVectorsInFaces.rbegin(); it != object3d.mNormalVectorsInFaces.rend(); ++it)
    {
      auto face = *it;
      WriteWord(file, face.mX);
      WriteWord(file, face.mY);
      WriteWord(file, face.mZ);
    }

  file.close();

  return true;
}

bool AmigaFile::Load(const std::string& name, Object3D& object3d)
{
  // UWAGA - współrzędne są zapisywane w odwrotnej kolejności
  // ponieważ funkcja obrotu (na amidze) zapisuje dane w odwrotnej kolejności (jak na stosie)

  std::ifstream file(name, std::ios::in | std::ios::binary);
  
  if (!file)
    {
      BOOST_LOG_TRIVIAL(error) << "File is not opened";
      return false;
    }

  BOOST_LOG_TRIVIAL(debug) << "Load file: " << name;
  
  unsigned short verticesCount = ReadWord(file);
  unsigned short facesCount = ReadWord(file);

  BOOST_LOG_TRIVIAL(debug) << "vertices = " + std::to_string(verticesCount);

  for (int i = 0; i < verticesCount; i++)
    {
      const auto x = ReadWord(file);
      const auto y = ReadWord(file);
      const auto z = ReadWord(file);
      const Vertex vertex(x,y,z);
      object3d.mVertices.push_back(vertex);
    }
  std::reverse(object3d.mVertices.begin(), object3d.mVertices.end());
  
  for (int i = 0; i < verticesCount; i++)
    {
      const auto x = ReadWord(file);
      const auto y = ReadWord(file);
      const auto z = ReadWord(file);
      const Vector vector(x,y,z);
      object3d.mNormalVectorsInVertices.push_back(vector);
    }
  std::reverse(object3d.mNormalVectorsInVertices.begin(), object3d.mNormalVectorsInVertices.end());

  BOOST_LOG_TRIVIAL(debug) << "faces = " + std::to_string(facesCount);

  for (int i = 0; i < facesCount; i++)
    {
      ReadWord(file); // not used
      const auto faceSize = ReadWord(file);
      
      Face face;
      for (int faceNr = 0; faceNr < faceSize; faceNr++)
        {
          const auto vertexNr = ReadWord(file) / 8;
          face.push_back(vertexNr);
        }
      object3d.mFaces.push_back(face);
    }

  for (int i = 0; i < facesCount; i++)
    {
      const auto x = ReadWord(file);
      const auto y = ReadWord(file);
      const auto z = ReadWord(file);
      const Vector vector(x,y,z);
      object3d.mNormalVectorsInFaces.push_back(vector);
    }
  std::reverse(object3d.mNormalVectorsInFaces.begin(), object3d.mNormalVectorsInFaces.end());
  
  file.close();

  return true;
}
