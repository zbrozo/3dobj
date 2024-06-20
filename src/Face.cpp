#include "Face.hpp"
#include "Types.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

#define MIN_FACES 3

Vector Face::CalculateNormalVector(const std::vector<Vertex>& vertices) const
{
  if (this->size() < MIN_FACES)
  {
    throw std::out_of_range("Vertex numbers in a face error");
  }

  const auto n1 = this->at(0);
  const auto n2 = this->at(1);
  const auto n3 = this->at(2);

  auto v1 = Vector(
    vertices[n2].mX - vertices[n1].mX,
    vertices[n2].mY - vertices[n1].mY,
    vertices[n2].mZ - vertices[n1].mZ);
  
  auto v2 = Vector(
    vertices[n3].mX - vertices[n2].mX,
    vertices[n3].mY - vertices[n2].mY,
    vertices[n3].mZ - vertices[n2].mZ);
  
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
    x += vertices[nr].mX;
    y += vertices[nr].mY;
    z += vertices[nr].mZ;
  }

  x /= static_cast<int>(size);
  y /= static_cast<int>(size);
  z /= static_cast<int>(size);
  
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

  const auto v1 = Vector(
    vertices[n1].mX - vertices[n0].mX,
    vertices[n1].mY - vertices[n0].mY,
    0);
  
  const auto v2 = Vector(
    vertices[n2].mX - vertices[n1].mX,
    vertices[n2].mY - vertices[n1].mY,
    0);

  // cross product w Z (jest większy niż short bo liczony po perspektywie)
  int result = v1.mX * v2.mY - v1.mY * v2.mX;

  return (result <= 0);
}

std::string Face::ToString() const
{
  std::string s;
  for (size_t i = 0; i < size(); ++i)
  {
    s += std::to_string(at(i)) + ((i != size() - 1) ? ", " : "");
  }
  return s;
}
