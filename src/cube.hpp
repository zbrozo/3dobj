#pragma once

#include "object3d.hpp"

class Cube : public Object3D
{

public:

  Cube(const char* name) :
    Object3D(name)
  {
  }

  void Generate();

protected:
  
  std::pair<Faces, Vertices> CreateCube(const Faces& faces, const Vertices& vertices);

  void RotateSide(int degx, int degy, int degz,
                  const Faces& faces,
                  const Vertices& vertices,
                  Faces& objectFaces,
                  Vertices& objectVertices);
  
};
