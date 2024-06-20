#include "Types.hpp"

template<class T>
class Rotation3D
{
 public:
  
  T rotateX(T coord, int d);
  T rotateY(T coord, int d);
  T rotateZ(T coors, int d);
};

using Rotation = Rotation3D<Vertex>;
using VectorRotation = Rotation3D<Vector>;
