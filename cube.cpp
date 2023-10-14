#include "cube.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

auto CreateOneFace(Vertices& vertices)
{
  std::vector<Vertices> allVertices;

  const size_t facesCount = 4;

  for (size_t i = 0; i < facesCount; ++i)
    {

      const auto rotatedVertices = vertices.Rotate(0, 0, i * 90);
      allVertices.push_back(rotatedVertices);
    }

  return allVertices;
}

auto MatchNewFaceAndVerticesWithExistingVertices(const Vertices& objectVertices,
                                                 const Face& face,
                                                 const Vertices& vertices)
{
  Face resultFace;
  Vertices resultVertices = objectVertices;
  
  for (size_t i = 0; i < face.size(); ++i)
    {
      auto vertexNr = face[i];
      Vertex vertex = vertices[vertexNr];

      int foundNr = 0;

      auto found = std::find_if(resultVertices.begin(), resultVertices.end(), [&](const Vertex& v){
        const short vertexRange = 0;

        if ((vertex.mX >= v.mX - vertexRange && vertex.mX <= v.mX + vertexRange)
            && (vertex.mY >= v.mY - vertexRange && vertex.mY <= v.mY + vertexRange)
            && (vertex.mZ >= v.mZ - vertexRange && vertex.mZ <= v.mZ + vertexRange))
          {
            return true;
          }
        
        ++foundNr;
        return false;
      });

      if (found != resultVertices.end())
        {
          resultFace.push_back(foundNr);
        }
      else
        {
          const short nr = resultVertices.size();
          
          resultFace.push_back(nr);
          resultVertices.push_back(vertex);
        }
    }
  
  return std::make_pair(resultFace, resultVertices);
}

auto CreateFaces(const std::vector<Vertices>& allVertices)
{
  Faces faces;
  Vertices vertices;

  for(const auto& tmpVertices : allVertices)
    {
      Face face{0,1,2,3};
      const auto [resultFace, resultVertices] = MatchNewFaceAndVerticesWithExistingVertices(vertices, face, tmpVertices);
      vertices = resultVertices;
      faces.push_back(resultFace);
    }
  
  return std::make_pair(faces, vertices);
}


void RotateCubeFace(int degx, int degy, int degz,
                    const Faces& faces,
                    const Vertices& vertices,
                    Faces& objectFaces,
                    Vertices& objectVertices)
{
  const auto rotatedVertices = vertices.Rotate(degx, degy, degz);
  
  for (const auto& face : faces)
    {
      const auto [resultFace, resultVertices] = MatchNewFaceAndVerticesWithExistingVertices(objectVertices, face, rotatedVertices);
      objectVertices = resultVertices;
      objectFaces.push_back(resultFace);
    }
}

auto CreateCube(const Faces& faces, const Vertices& vertices)
{
  Faces objectFaces;
  Vertices objectVertices;

  const size_t facesCount = 4;

  for (size_t i = 0; i < facesCount; ++i)
    {
      RotateCubeFace(i * 90, 0, 0, faces, vertices, objectFaces, objectVertices);
    }

  RotateCubeFace(0, 90, 0, faces, vertices, objectFaces, objectVertices);
  RotateCubeFace(0, -90, 0, faces, vertices, objectFaces, objectVertices);

  return std::make_pair(objectFaces, objectVertices);
}

auto CreateCubePart1()
{
  const short value = 50;

  Vertices basicVertices = {
    {value, value, value},
    {-value, value, value},
    {-(value-20), value-20, value},
    {value-20, value-20, value},
  };

  const auto allVertices = CreateOneFace(basicVertices);
  const auto facesWithVertices = CreateFaces(allVertices);
  const auto result = CreateCube(facesWithVertices.first, facesWithVertices.second);

  return result;
}

auto CreateCubePart2()
{
  const short value = 50;

  Vertices basicVertices = {
    {value-20, value-20, value},
    {-(value-20), value-20, value},
    {-(value-20), value-20, value-20},
    {value-20, value-20, value-20},
  };

  const auto allVertices = CreateOneFace(basicVertices);
  const auto facesWithVertices = CreateFaces(allVertices);
  const auto result = CreateCube(facesWithVertices.first, facesWithVertices.second);

  return result;
}

auto CreateSimpleCube()
{
  const short value = 50;

  Vertices vertices= {
    {value, value, value},
    {-value, value, value},
    {-value, -value, value},
    {value, -value, value},
  };

  Face face{0,1,2,3};
  
  Faces faces;
  faces.push_back(face);
  
  const auto result = CreateCube(faces, vertices);

  return result;
}


void Cube::Generate()
{

  //auto r = CreateSimpleCube();
  //mFaces = r.first;
  //mVertices = r.second;



  
  auto part1 = CreateCubePart2();
  auto part2 = CreateCubePart1();

  mFaces = part1.first;
  mVertices = part1.second;

  for (const auto& face : part2.first)
    {
      auto r = MatchNewFaceAndVerticesWithExistingVertices(mVertices,
                                                           face,
                                                           part2.second);

      mFaces.push_back(r.first);
      mVertices = r.second;
    }
}


