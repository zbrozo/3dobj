#include "face.hpp"
#include "vertex.hpp"
#include "vector3d.hpp"
#include <cmath>
#include <stdexcept>

Vector3d Face::CalculateNormalVector(const std::vector<Vertex>& vertices) const
{
  if (this->size() < 3)
    {
      throw std::out_of_range("Face vertices size error");
    }
  
  auto n1 = this->at(0);
  auto n2 = this->at(1);
  auto n3 = this->at(2);

  auto v1 = Vector3d(vertices[n2].x - vertices[n1].x,
                     vertices[n2].y - vertices[n1].y,
                     vertices[n2].z - vertices[n1].z);
  
  auto v2 = Vector3d(vertices[n3].x - vertices[n1].x,
                     vertices[n3].y - vertices[n1].y,
                     vertices[n3].z - vertices[n1].z);
  
  return v1.CrossProduct(v2).Normalize();
}
