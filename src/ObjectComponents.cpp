#include "ObjectComponents.hpp"

#include <algorithm>

auto CreateSideVertices(Vertices& vertices)
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

auto CreateSideFaces(const std::vector<Vertices>& allVertices)
{
  Faces faces;
  Vertices vertices;

  for(const auto& tmpVertices : allVertices)
    {
      Face face{0,1,2,3};
      const auto [resultFace, resultVertices] = Object3D::Merge(vertices, face, tmpVertices);
      vertices = resultVertices;
      faces.push_back(resultFace);
    }
  
  return std::make_pair(faces, vertices);
}

void Component0::Generate()
{
  Vertices vertices= {
    {1, 1, 1},
    {-1, 1, 1},
    {-1, -1, 1},
    {1, -1, 1},
  };

  std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(), [&](const Vertex& vertex){
    return vertex * mSize;
  });
   
  Face face{0,1,2,3};
  mFaces.push_back(face);
  mVertices = vertices;
}

void Component1::Generate()
{
  Vertices vertices = {
    {1, 1, 1},
    {-1, 1, 1},
    {-1, 1, 1},
    {1, 1, 1},
  };
  
  Vertices verticesModify = {
    {-1, -1, 0},
    {1, -1, 0},
    {1, -1, -1},
    {-1, -1, -1},
  };

  std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(), [&](const Vertex& vertex){
    return vertex * mSize;
  });

  std::transform(verticesModify.cbegin(), verticesModify.cend(), verticesModify.begin(), [&](const Vertex& vertex){
    return Vertex(vertex.mX * mSizeXY, vertex.mY * mSizeXY, vertex.mZ * mSizeZ);
  });

  for (unsigned int i = 0; i < vertices.size(); i++)
  {
    auto& v1 = vertices.at(i);
    const auto& v2 = verticesModify.at(i);
    v1 = v1 + v2;
  }
  
  const auto allVertices = CreateSideVertices(vertices);
  const auto facesWithVertices = CreateSideFaces(allVertices);
  
  mFaces = facesWithVertices.first;
  mVertices = facesWithVertices.second;
}

void Component2::Generate()
{
  Vertices vertices = {
    {1, 1, 1},
    {-1, 1, 1},
    {-1, 1, 1},
    {1, 1, 1},
  };

  Vertices verticesModify = {
    {0, 0, 0},
    {0, 0, 0},
    {1, -1, 0},
    {-1, -1, 0},
  };

  std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(), [&](const Vertex& vertex){
    return vertex * mSize;
  });

  std::transform(verticesModify.cbegin(), verticesModify.cend(), verticesModify.begin(), [&](const Vertex& vertex){
    return Vertex(vertex.mX * mSizeXY, vertex.mY * mSizeXY, vertex.mZ);
  });

  for (unsigned int i = 0; i < vertices.size(); i++)
  {
    auto& v1 = vertices.at(i);
    const auto& v2 = verticesModify.at(i);
    v1 = v1 + v2;
  }
  
  const auto allVertices = CreateSideVertices(vertices);
  const auto facesWithVertices = CreateSideFaces(allVertices);
  
  mFaces = facesWithVertices.first;
  mVertices = facesWithVertices.second;
}
