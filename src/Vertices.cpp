#include "Vertices.hpp"
#include "Vertex.hpp"

Vertices Vertices::Rotate(int degX, int degY, int degZ) const
{
  const short scaleValue = 10;
  
  Vertices rotatedVertices;
  
  for (const auto& vertex : *this)
    {
      Vertex v = vertex * scaleValue;
      
      v = v.Rotate(degX, degY, degZ);

      v = v / scaleValue;

      rotatedVertices.push_back(v);
    }

  return rotatedVertices;
}
