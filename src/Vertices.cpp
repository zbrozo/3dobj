#include "Vertices.hpp"
#include "Rotation.hpp"

Vertices Vertices::Rotate(int degX, int degY, int degZ) const
{
  const short scaleValue = 10;
  
  Vertices rotatedVertices;
  Rotation rotation;
  
  for (const auto& vertex : *this)
  {
    Vertex v = vertex * scaleValue;
    v = rotation.rotateZ(rotation.rotateY(rotation.rotateX(v, degX), degY), degZ);
    v = v / scaleValue;
    
    rotatedVertices.push_back(v);
  }

  return rotatedVertices;
}
