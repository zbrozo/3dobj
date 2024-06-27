#include "Vertices.hpp"
#include "Rotation.hpp"

Vertices Vertices::Rotate(int degX, int degY, int degZ) const
{
  const short scaleValue = 10;
  
  Vertices rotatedVertices;
  VertexRotation rotate;
  
  for (const auto& vertex : *this)
  {
    Vertex v = vertex * scaleValue;
    v = rotate.rotateZ(rotate.rotateY(rotate.rotateX(v, degX), degY), degZ);
    v = v / scaleValue;
    
    rotatedVertices.push_back(v);
  }

  return rotatedVertices;
}

Vertices& Vertices::operator+=(const Vertex &vertex)
{
  for (auto& v : *this)
  {
    v += vertex;
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Vertices& vertices)
{
  for (const auto& v : vertices)
  {
    os << v;
  }

  os << std::endl;

  return os;
}

