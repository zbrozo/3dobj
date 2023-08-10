// 1. utworzenie list numerów scian zawierających poszczególne wierzchołków
// 2. wyznaczenie werktora normalnego (prostopadłego) do każdej ze ścian
// 3. wyznaczenie wektorów w wierzchołakach
// 4. normalizacja wektorów w wierzchołkach

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

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

struct Coord
{
  short x;
  short y;
  short z;
};

using Face = std::vector<unsigned short>;

auto PrepareFacesAssignedToVertices(const std::vector<Coord>& vertexes,
                                    const std::vector<Face>& faces)
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


Coord CalculateNormalVectorToFace(const std::vector<Coord>& vertexes,
                                  const Face& face)
{
  std::cout << __FUNCTION__ << "\n";

  auto v1 = face[0];
  auto v2 = face[1];
  auto v3 = face[2];

  auto x1 = vertexes[v2].x - vertexes[v1].x;
  auto y1 = vertexes[v2].y - vertexes[v1].y;
  auto z1 = vertexes[v2].z - vertexes[v1].z;
  
  auto x2 = vertexes[v3].x - vertexes[v1].x;
  auto y2 = vertexes[v3].y - vertexes[v1].y;
  auto z2 = vertexes[v3].z - vertexes[v1].z;
  
  auto x = (y1 * z2 - z1 * y2) >> 8;
  auto y = (z1 * x2 - x1 * z2) >> 8;
  auto z = (x1 * y2 - y1 * x2) >> 8;

  Coord coord;
  coord.x = x;
  coord.y = y;
  coord.z = z;

  std::cout << x << ", " << y << ", " << z << "\n";
  
  return coord;
}

auto CalculateNormalVectorToFaces(const std::vector<Coord>& vertexes,
                                  const std::vector<Face>& faces
                                  )
{
  std::vector<Coord> normalFaceVectors;
  for(auto face : faces)
    {
      Coord coord = CalculateNormalVectorToFace(vertexes, face);
      normalFaceVectors.push_back(coord);
    }

  return normalFaceVectors;
}

auto CalculateVectorsInVertices(const std::vector<std::vector<unsigned short>>& vertexInFaceDependency,
                                const std::vector<Coord>& normalFaceVectors)
{
  std::cout << __FUNCTION__ << "\n";

  std::vector<Coord> vectorsInVertices;
  
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

      Coord coord;
      coord.x = x;
      coord.y = y;
      coord.z = z;

      std::cout << x << ", " << y << ", " << z << "\n";
      
      vectorsInVertices.push_back(coord);      
    }

  return vectorsInVertices;
}

auto NormalizeVectorsInVertices(std::vector<Coord>& vectorsInVertices)
{
  std::cout << __FUNCTION__ << "\n";

  std::vector<Coord> normalizedVectorsInVertices;

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

      Coord coord;
      coord.x = x;
      coord.y = y;
      coord.z = z;

      normalizedVectorsInVertices.push_back(coord);
    }

  return normalizedVectorsInVertices;
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

int main()
{
  std::vector<Coord> vertices
    {
      {60, -60, 60},
      {-60, -60, 60},
      {-60, 60, 60},
      {60, 60, 60},
      {60, -60, -60},
      {-60, -60, -60},
      {-60, 60, -60},
      {60, 60, -60},
    };
  
  std::vector<Face> faces
    {
      {1,2,3,0},
      {4,7,6,5},
      {3,7,4,0},
      {6,2,1,5},
      {6,7,3,2},
      {1,0,4,5}
    };

  std::vector<Coord> normalFaceVectors;

  std::vector<Coord> vectorsInVertices;
  std::vector<Coord> normalizedVectorsInVertices;

  std::vector<std::vector<unsigned short>> facesAssignedToVertex;
  
  facesAssignedToVertex = PrepareFacesAssignedToVertices(vertices, faces);
  
  normalFaceVectors = CalculateNormalVectorToFaces(vertices, faces);

  vectorsInVertices = CalculateVectorsInVertices(facesAssignedToVertex, normalFaceVectors);

  normalizedVectorsInVertices = NormalizeVectorsInVertices(vectorsInVertices);
  
  std::ofstream file("test.bin", std::ios::out | std::ios::app | std::ios::binary);
  
  if (!file)
    {
      std::cout << "ERROR: File is not opened" << "\n";
      return 1;
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

  std::reverse(normalizedVectorsInVertices.begin(), normalizedVectorsInVertices.end());

  for(auto value : normalizedVectorsInVertices)
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

  std::reverse(normalFaceVectors.begin(), normalFaceVectors.end());

  for(auto face : normalFaceVectors)
    {
      std::cout << std::hex << face.x << ", " <<  face.y << ", " <<  face.z << "\n";
      WriteWord(file, face.x);
      WriteWord(file, face.y);
      WriteWord(file, face.z);
    }

  file.close();
  
  return 0;
}





