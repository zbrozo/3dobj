#include "face.hpp"
#include "vertex.hpp"
#include "vector3d.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

#define MIN_FACES 3

Vector3d Face::CalculateNormalVector(const std::vector<Vertex>& vertices) const
{
  if (this->size() < MIN_FACES)
    {
      throw std::out_of_range("Vertex numbers in a face error");
    }
  
  auto n1 = this->at(0);
  auto n2 = this->at(1);
  auto n3 = this->at(2);

  auto v1 = Vector3d(vertices[n2].x - vertices[n1].x,
                     vertices[n2].y - vertices[n1].y,
                     vertices[n2].z - vertices[n1].z);
  
  auto v2 = Vector3d(vertices[n3].x - vertices[n2].x,
                     vertices[n3].y - vertices[n2].y,
                     vertices[n3].z - vertices[n2].z);
  
  return v1.CrossProduct(v2).Normalize();
}

Vertex Face::GetCenter(const std::vector<Vertex>& vertices) const
{
  if (this->size() < MIN_FACES)
    {
      throw std::out_of_range("Vertex numbers in a face error");
    }
  
  const unsigned int size = this->size();
  
  short x = 0;
  short y = 0;
  short z = 0;
  
  for (unsigned int i = 0; i < size; ++i)
    {
      const auto nr = this->at(i);
      x += vertices[nr].x;
      y += vertices[nr].y;
      z += vertices[nr].z;
    }

  x /= size;
  y /= size;
  z /= size;
  
  return Vertex(x, y, z);
}

bool Face::IsVisible(const std::vector<Vertex>& vertices) const
{
  if (this->size() < MIN_FACES)
    {
      throw std::out_of_range("Vertex numbers in a face error");
    }

  const auto n0 = this->at(0);
  const auto n1 = this->at(1);
  const auto n2 = this->at(2);

  const auto v1 = Vector3d(vertices[n1].x - vertices[n0].x,
                           vertices[n1].y - vertices[n0].y,
                           0);
  
  const auto v2 = Vector3d(vertices[n2].x - vertices[n1].x,
                           vertices[n2].y - vertices[n1].y,
                           0);

  // cross product w Z (jest większy niż short bo liczony po perspektywie)
  int result = v1.x * v2.y - v1.y * v2.x; 

  return (result >= 0);
}
