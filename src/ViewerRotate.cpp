#include "Types.hpp"
#include "Vertices.hpp"
#include "Rotation.hpp"

void RotateObject(int degx, int degy, int degz,
  const Vertices& vertices,
  const Vectors& normalVectorsInFaces,
  const Vectors& normalVectorsInVertices,
  Vertices& resultVertices,
  Vectors& resultNormalVectorsInFaces,
  Vectors& resultNormalVectorsInVertices)
{
  auto rotate = [degx, degy, degz](const Vertex& v){
    VertexRotation rotation;
    return rotation.rotateZ(rotation.rotateY(rotation.rotateX(v, degx) ,degy), degz);
  };

  auto rotateVector = [degx, degy, degz](const Vector& v){
    VectorRotation rotation;
    return rotation.rotateZ(rotation.rotateY(rotation.rotateX(v, degx) ,degy), degz);
  };

  for (auto v : vertices)
  {
    resultVertices.push_back(rotate(v));
  }

  for (auto v : normalVectorsInFaces)
  {
    resultNormalVectorsInFaces.push_back(rotateVector(v));
  }

  for (auto v : normalVectorsInVertices)
  {
    resultNormalVectorsInVertices.push_back(rotateVector(v));
  }

}
