#include "cube.hpp"
#include "object3d.hpp"

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

  mFaces = result.first;
  mVertices = result.second;
}


