#include "Cube2.hpp"

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

auto Cube2::CreateCubePart1()
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
  const auto result = CreateCube(facesWithVertices.first, facesWithVertices.second);

  return result;
}

auto Cube2::CreateCubePart2()
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
  const auto result = CreateCube(facesWithVertices.first, facesWithVertices.second);

  return result;
}

void Cube2::Generate()
{
  auto part1 = CreateCubePart2();
  auto part2 = CreateCubePart1();

  mFaces = part1.first;
  mVertices = part1.second;

  for (const auto& face : part2.first)
    {
      auto r = Object3D::Merge(mVertices,
                               face,
                               part2.second);

      mFaces.push_back(r.first);
      mVertices = r.second;
    }
}
