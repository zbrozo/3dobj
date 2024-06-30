#include "Cube.hpp"
#include "Object3D.hpp"
#include <algorithm>

void Cube::RotateSide(int degx, int degy, int degz,
                      const Faces& faces,
                      const Vertices& vertices,
                      Faces& objectFaces,
                      Vertices& objectVertices)
{
  const auto rotatedVertices = vertices.Rotate(degx, degy, degz);
  
  for (const auto& face : faces)
  {
    const auto [resultFace, resultVertices] = Object3D::Merge(objectVertices, face, rotatedVertices);
    objectVertices = resultVertices;
    objectFaces.push_back(resultFace);
  }
}

std::pair<Faces, Vertices> Cube::CreateCube(const Faces& faces, const Vertices& vertices)
{
  Faces objectFaces;
  Vertices objectVertices;

  const size_t facesCount = 4;

  for (size_t i = 0; i < facesCount; ++i)
  {
    RotateSide(i * 90, 0, 0, faces, vertices, objectFaces, objectVertices);
  }

  RotateSide(0, 90, 0, faces, vertices, objectFaces, objectVertices);
  RotateSide(0, -90, 0, faces, vertices, objectFaces, objectVertices);

  return std::make_pair(objectFaces, objectVertices);
}

void Cube::Generate()
{
  Vertices vertices {
    {1, 1, 1},
    {-1, 1, 1},
    {-1, -1, 1},
    {1, -1, 1},
  };

  std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(),
    [&](const Vertex& vertex)
    {
      return vertex * mSize;
    });
  
  Face face{0,1,2,3};
  
  Faces faces;
  faces.push_back(face);
  
  const auto result = CreateCube(faces, vertices);

  mFaces = result.first;
  mVertices = result.second;
}


