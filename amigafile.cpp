#include <iostream>
#include <fstream>
#include "amigafile.hpp"
#include "object3d.hpp"

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

unsigned int swapByteOrder(const unsigned int value)
{
  const char* bytes = reinterpret_cast<const char*>(&value);
  const unsigned char byte0 = bytes[0];
  const unsigned char byte1 = bytes[1];
  const unsigned char byte2 = bytes[2];
  const unsigned char byte3 = bytes[3];
  const unsigned int result = static_cast<unsigned int> ( (byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3 );
  return result;
}

void WriteByte(std::ofstream& file, unsigned char value)
{
  file.write(reinterpret_cast<const char*>(&value), sizeof(char));
}

void WriteWord(std::ofstream& file, unsigned short value)
{
  unsigned short swappedShort = swapByteOrder(value);
  file.write(reinterpret_cast<const char*>(&swappedShort), sizeof(short));
}

void WriteLong(std::ofstream& file, unsigned int value)
{
  unsigned int swappedValue = swapByteOrder(value);
  file.write(reinterpret_cast<const char*>(&swappedValue), sizeof(unsigned int));
}
  
}

bool AmigaFile::Save(const Object3D& object3d)
{
  // UWAGA - współrzędne są zapisywane w odwrotnej kolejności
  // ponieważ funkcja obrotu (na amidze) zapisuje dane w odwrotnej kolejności (jak na stosie)

  std::ofstream file(object3d.mName, std::ios::out | std::ios::binary);
  
  if (!file)
    {
      std::cout << "ERROR: File is not opened" << "\n";
      return false;
    }
  
  WriteWord(file, object3d.mVertices.size());
  WriteWord(file, object3d.mFaces.size());

  std::cout << "vertices" << "\n";
  for (auto it = object3d.mVertices.rbegin(); it != object3d.mVertices.rend(); ++it)
    {
      auto value = *it;
      std::cout << value.ToString() << "\n";
      WriteWord(file, value.mX);
      WriteWord(file, value.mY);
      WriteWord(file, value.mZ);
    }

  std::cout << "normalized vectors in vertices" << "\n";
  for (auto it = object3d.mNormalVectorsInVertices.rbegin(); it != object3d.mNormalVectorsInVertices.rend(); ++it)
    {
      auto value = *it;
      std::cout << value.ToString() << "\n";
      WriteWord(file, value.mX);
      WriteWord(file, value.mY);
      WriteWord(file, value.mZ);
    }
  
  std::cout << "faces" << "\n";
  for(auto face : object3d.mFaces)
    {
      WriteWord(file, 0);
      WriteWord(file, face.size());
      for (auto number : face)
        {
          WriteWord(file, number * 8);
        }
    }

  std::cout << "normalized face vectors" << "\n";

  for (auto it = object3d.mNormalVectorsInFaces.rbegin(); it != object3d.mNormalVectorsInFaces.rend(); ++it)
    {
      auto face = *it;
      std::cout << face.ToString() << "\n";
      WriteWord(file, face.mX);
      WriteWord(file, face.mY);
      WriteWord(file, face.mZ);
    }

  file.close();

  return true;
}
