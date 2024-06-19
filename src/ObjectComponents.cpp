#include "ObjectComponents.hpp"

#include <algorithm>

namespace
{
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
} // namespace

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
    return vertex * mSize1;
  });

  std::transform(verticesModify.cbegin(), verticesModify.cend(), verticesModify.begin(), [&](const Vertex& vertex){
    return Vertex(vertex.mX * mSize2, vertex.mY * mSize2, vertex.mZ * mSize3);
  });

  for (size_t i = 0; i < vertices.size(); i++)
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
    return vertex * mSize1;
  });

  std::transform(verticesModify.cbegin(), verticesModify.cend(), verticesModify.begin(), [&](const Vertex& vertex){
    return Vertex(vertex.mX * mSize2, vertex.mY * mSize2, vertex.mZ);
  });

  for (size_t i = 0; i < vertices.size(); i++)
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

void Component3::Generate()
{
  Vertices vertices= {
    {1, 1, 1},
    {-1, 1, 1},
    {-1, -1, 1},
    {1, -1, 1},
    {0, 0, 1}
  };

  std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(), [&](const Vertex& vertex){
    return vertex * mSize1;
  });

  vertices[4].mZ += mSize2;
  
  mVertices = vertices;

  mFaces.push_back({0,1,4});
  mFaces.push_back({1,2,4});
  mFaces.push_back({2,3,4});
  mFaces.push_back({3,0,4});
}
