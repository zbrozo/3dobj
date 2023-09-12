#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
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
  
auto PrepareFacesAssignedToVertices(const Vertices& vertexes,
                                    const Faces& faces)
{
  std::cout << __FUNCTION__ << "\n";

  std::vector<std::vector<unsigned short>> result;
  
  for(unsigned int i = 0; i < vertexes.size(); i++)
    {
      std::vector<unsigned short> foundFaces;

      unsigned short faceNr = 0;
      
      for (auto face : faces)
        {
          if (std::find(face.begin(), face.end(), i) != face.end())
          {
            foundFaces.push_back(faceNr);
          }
          
          ++faceNr;
        }

      result.push_back(foundFaces);

      for(auto v : foundFaces)
        {
          std::cout << v << ", ";
        }
      std::cout << "\n";
      
    }

  return result;
}


Vertex CalculateNormalVectorToFace(const Vertices& vertexes,
                                  const Face& face)
{
  std::cout << __FUNCTION__ << "\n";

  // wyznaczenie wektora wypadkowego do ściany
  
  auto v1 = face[0];
  auto v2 = face[1];
  auto v3 = face[2];

  auto x1 = vertexes[v2].x - vertexes[v1].x;
  auto y1 = vertexes[v2].y - vertexes[v1].y;
  auto z1 = vertexes[v2].z - vertexes[v1].z;
  
  auto x2 = vertexes[v3].x - vertexes[v1].x;
  auto y2 = vertexes[v3].y - vertexes[v1].y;
  auto z2 = vertexes[v3].z - vertexes[v1].z;
  
  auto x = (y1 * z2 - z1 * y2);
  auto y = (z1 * x2 - x1 * z2);
  auto z = (x1 * y2 - y1 * x2);

  const double len = sqrt(x * x + y * y + z * z);

  if (len != 0)
    {
      const short normalizedVectorLength = 60;
      x = x * normalizedVectorLength / len;
      y = y * normalizedVectorLength / len;
      z = z * normalizedVectorLength / len;
    }
  
  Vertex vertex(x, y, z);

  std::cout << x << ", " << y << ", " << z << "\n";
  
  return vertex;
}

auto CalculateNormalVectorToFaces(const Vertices& vertexes,
                                  const Faces& faces
                                  )
{
  Vertices normalFaceVectors;
  for(auto face : faces)
    {
      Vertex coord = CalculateNormalVectorToFace(vertexes, face);
      normalFaceVectors.push_back(coord);
    }

  return normalFaceVectors;
}

auto CalculateVectorsInVertices(const Faces& vertexInFaceDependency,
                                const Vertices& normalFaceVectors)
{
  std::cout << __FUNCTION__ << "\n";

  Vertices vectorsInVertices;
  
  for(auto faces : vertexInFaceDependency)
    {
      short x = 0;
      short y = 0;
      short z = 0;
      
      for(auto face : faces)
        {
          std::cout << "face: " <<  face << ", " << x << "\n";
          
          x += normalFaceVectors[face].x;
          y += normalFaceVectors[face].y;
          z += normalFaceVectors[face].z;
        }

      short count = faces.size();
      
      if (faces.size() != 0)
        {
          x = x / count;
          y = y / count;
          z = z / count;
        }

      Vertex coord;
      coord.x = x;
      coord.y = y;
      coord.z = z;

      std::cout << x << ", " << y << ", " << z << "\n";
      
      vectorsInVertices.push_back(coord);      
    }

  return vectorsInVertices;
}

auto NormalizeVectorsInVertices(Vertices& vectorsInVertices)
{
  std::cout << __FUNCTION__ << "\n";

  Vertices normalizedVectorsInVertices;

  const short normalizedVectorLength = 60;
  
  for (auto vec : vectorsInVertices)
    {
      short x = 0;
      short y = 0;
      short z = 0;
      
      const double len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

      if (len != 0)
        {
          x = vec.x * normalizedVectorLength / len;
          y = vec.y * normalizedVectorLength / len;
          z = vec.z * normalizedVectorLength / len;
        }

      Vertex coord;
      coord.x = x;
      coord.y = y;
      coord.z = z;

      normalizedVectorsInVertices.push_back(coord);
    }

  return normalizedVectorsInVertices;
}

}

void Object3D::CreateNormalVectors()
{
  Faces facesAssignedToVertex = PrepareFacesAssignedToVertices(vertices, faces);
  
  normalVectorsInFaces = CalculateNormalVectorToFaces(vertices, faces);

  Vertices vectorsInVertices = CalculateVectorsInVertices(facesAssignedToVertex, normalVectorsInFaces);

  normalVectorsInVertices = NormalizeVectorsInVertices(vectorsInVertices);
}

bool Object3D::SaveToFile()
{
  std::ofstream file(name, std::ios::out | std::ios::binary);
  
  if (!file)
    {
      std::cout << "ERROR: File is not opened" << "\n";
      return false;
    }
  
  WriteWord(file, vertices.size());
  WriteWord(file, faces.size());

  std::cout << "vertices" << "\n";

  // odwrotna kolejnosc poniewaz funkcja obrotu odwroci ta kolejnosc pozniej
  std::reverse(vertices.begin(), vertices.end());
  
  for(auto value : vertices)
    {
      std::cout << std::hex << value.x << ", " <<  value.y << ", " <<  value.z << "\n";
      WriteWord(file, value.x);
      WriteWord(file, value.y);
      WriteWord(file, value.z);
    }

  std::cout << "normalized vectors in vertices" << "\n";

  std::reverse(normalVectorsInVertices.begin(), normalVectorsInVertices.end());

  for(auto value : normalVectorsInVertices)
    {
      std::cout << std::hex << value.x << ", " <<  value.y << ", " <<  value.z << "\n";
      WriteWord(file, value.x);
      WriteWord(file, value.y);
      WriteWord(file, value.z);
    }
  
  std::cout << "faces" << "\n";
  for(auto face : faces)
    {
      WriteWord(file, 0);
      WriteWord(file, face.size());
      for (auto number : face)
        {
          WriteWord(file, number * 8);
        }
    }

  std::cout << "normalized face vectors" << "\n";

  std::reverse(normalVectorsInFaces.begin(), normalVectorsInFaces.end());

  for(auto face : normalVectorsInFaces)
    {
      std::cout << std::hex << face.x << ", " <<  face.y << ", " <<  face.z << "\n";
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
  for (auto v : vertices)
    {
      std::cout << v.x << ", " << v.y << ", " << v.z << "\n";
    }
}


void Object3D::LogFaces()
{
  std::cout << __FUNCTION__ << "\n";
  for (auto face : faces)
    {
      for (auto v : face)
        {
          std::cout << v << ", ";
        }
      std::cout << "\n";
    }
}


