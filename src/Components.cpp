#include "Components.hpp"
#include <algorithm>

#include <boost/log/trivial.hpp>

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

namespace Components
{

void Square::Generate()
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

void SquareWithHolePart1::Generate()
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
    return Vertex(vertex.getX() * mSize2, vertex.getY() * mSize2, vertex.getZ() * mSize3);
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

void SquareWithHolePart2::Generate()
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
    return Vertex(vertex.getX() * mSize2, vertex.getY() * mSize2, vertex.getZ());
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

void Pyramid::Generate()
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
  
  vertices[4] = Vertex(vertices[4].getX(), vertices[4].getY(), vertices[4].getZ() + mSize2);
  
  mVertices = vertices;

  mFaces.push_back({0,1,4});
  mFaces.push_back({1,2,4});
  mFaces.push_back({2,3,4});
  mFaces.push_back({3,0,4});
}

} // namespace
