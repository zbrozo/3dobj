#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "object3d.hpp"
#include "vector3d.hpp"

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
  
auto PrepareFacesAssignedToVertices(const Vertices& vertices,
                                    const Faces& faces)
{
  std::cout << __FUNCTION__ << "\n";

  FaceNumbersInVertices result;
  
  for(unsigned int i = 0; i < vertices.size(); i++)
    {
      FaceNumbers foundFaceNumbers;

      unsigned short faceNr = 0;
      
      for (auto face : faces)
        {
          if (std::find(face.begin(), face.end(), i) != face.end())
          {
            foundFaceNumbers.push_back(faceNr);
          }
          
          ++faceNr;
        }

      result.push_back(foundFaceNumbers);

      for(auto v : foundFaceNumbers)
        {
          std::cout << v << ", ";
        }
      std::cout << "\n";
      
    }

  return result;
}

auto CalculateNormalVectorToFaces(const Vertices& vertices,
                                  const Faces& faces
                                  )
{
  Vectors normalVectors;
  for(auto face : faces)
    {
      const auto vector = face.CalculateNormalVector(vertices);
      normalVectors.push_back(vector);
    }

  return normalVectors;
}

auto CalculateVectorsInVertices(const FaceNumbersInVertices& vertexInFaceDependency,
                                const Vectors& normalFaceVectors)
{
  std::cout << __FUNCTION__ << "\n";

  Vectors vectorsInVertices;
  
  for(auto faces : vertexInFaceDependency)
    {
      short x = 0;
      short y = 0;
      short z = 0;
      
      for(auto faceNr : faces)
        {
          std::cout << "face: " <<  faceNr << ", " << x << "\n";
          
          x += normalFaceVectors[faceNr].x;
          y += normalFaceVectors[faceNr].y;
          z += normalFaceVectors[faceNr].z;
        }

      const short count = faces.size();
      
      if (faces.size() != 0)
        {
          x = x / count;
          y = y / count;
          z = z / count;
        }

      Vertex vertex(x, y, z);
      std::cout << x << ", " << y << ", " << z << "\n";
      
      vectorsInVertices.push_back(Vector3d(vertex));      
    }

  return vectorsInVertices;
}

auto NormalizeVectorsInVertices(const Vectors& vectorsInVertices)
{
  std::cout << __FUNCTION__ << "\n";

  Vectors normalizedVectorsInVertices;

  for (auto vector : vectorsInVertices)
    {
      normalizedVectorsInVertices.push_back(vector.Normalize());
    }

  return normalizedVectorsInVertices;
}

}

void Object3D::CreateNormalVectors()
{
  FaceNumbersInVertices facesAssignedToVertex = PrepareFacesAssignedToVertices(mVertices, mFaces);
  
  mNormalVectorsInFaces = CalculateNormalVectorToFaces(mVertices, mFaces);

  Vectors vectorsInVertices = CalculateVectorsInVertices(facesAssignedToVertex, mNormalVectorsInFaces);

  mNormalVectorsInVertices = NormalizeVectorsInVertices(vectorsInVertices);
}

bool Object3D::SaveToFile()
{
  // UWAGA - współrzędne są zapisywane w odwrotnej kolejności
  // ponieważ funkcja obrotu (na amidze) zapisuje dane w odwrotnej kolejności (jak na stosie)

  std::ofstream file(mName, std::ios::out | std::ios::binary);
  
  if (!file)
    {
      std::cout << "ERROR: File is not opened" << "\n";
      return false;
    }
  
  WriteWord(file, mVertices.size());
  WriteWord(file, mFaces.size());

  std::cout << "vertices" << "\n";
  for (auto it = mVertices.rbegin(); it != mVertices.rend(); ++it)
    {
      auto value = *it;
      std::cout << value.ToString() << "\n";
      WriteWord(file, value.x);
      WriteWord(file, value.y);
      WriteWord(file, value.z);
    }

  std::cout << "normalized vectors in vertices" << "\n";
  for (auto it = mNormalVectorsInVertices.rbegin(); it != mNormalVectorsInVertices.rend(); ++it)
    {
      auto value = *it;
      std::cout << value.ToString() << "\n";
      WriteWord(file, value.x);
      WriteWord(file, value.y);
      WriteWord(file, value.z);
    }
  
  std::cout << "faces" << "\n";
  for(auto face : mFaces)
    {
      WriteWord(file, 0);
      WriteWord(file, face.size());
      for (auto number : face)
        {
          WriteWord(file, number * 8);
        }
    }

  std::cout << "normalized face vectors" << "\n";

  for (auto it = mNormalVectorsInFaces.rbegin(); it != mNormalVectorsInFaces.rend(); ++it)
    {
      auto face = *it;
      std::cout << face.ToString() << "\n";
      WriteWord(file, face.x);
      WriteWord(file, face.y);
      WriteWord(file, face.z);
    }

  file.close();

  return true;
}
    
void Object3D::LogVertices()
{
  std::cout << __FUNCTION__ << "\n";
  for (auto v : mVertices)
    {
      std::cout << v.ToString() << "\n";
    }
}

void Object3D::LogFaces()
{
  std::cout << __FUNCTION__ << "\n";
  for (auto face : mFaces)
    {
      std::cout << face.ToString() << "\n";
    }
}

