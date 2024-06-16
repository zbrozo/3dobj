#include "ObjectComponents.hpp"

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
  const short value = 50;

  Vertices vertices= {
    {value, value, value},
    {-value, value, value},
    {-value, -value, value},
    {value, -value, value},
  };

  Face face{0,1,2,3};
  mFaces.push_back(face);
  mVertices = vertices;
}

void Component1::Generate()
{
  const short value = 50;
  
  Vertices basicVertices = {
    {value-20, value-20, value},
    {-(value-20), value-20, value},
    {-(value-20), value-20, value-20},
    {value-20, value-20, value-20},
  };
  
  const auto allVertices = CreateSideVertices(basicVertices);
  const auto facesWithVertices = CreateSideFaces(allVertices);
  
  mFaces = facesWithVertices.first;
  mVertices = facesWithVertices.second;
}

void Component2::Generate()
{
  const short value = 50;

  Vertices basicVertices = {
    {value, value, value},
    {-value, value, value},
    {-(value-20), value-20, value},
    {value-20, value-20, value},
  };

  const auto allVertices = CreateSideVertices(basicVertices);
  const auto facesWithVertices = CreateSideFaces(allVertices);
  
  mFaces = facesWithVertices.first;
  mVertices = facesWithVertices.second;
}
