#pragma once

#include "Object3d.hpp"
#include "IGenerator.hpp"

class Cube : public Object3D, public IGenerator
{

public:

  Cube(const char* name) :
    Object3D(name)
  {
  }

  virtual ~Cube() = default;
  
  Cube(Cube const &) = delete;
  Cube(Cube &&) = delete;
  Cube& operator=(const Cube& v) = delete;
  Cube& operator=(Cube &&) = delete;
  
  virtual void Generate() override;

protected:
  
  std::pair<Faces, Vertices> CreateCube(const Faces& faces, const Vertices& vertices);

  void RotateSide(int degx, int degy, int degz,
                  const Faces& faces,
                  const Vertices& vertices,
                  Faces& objectFaces,
                  Vertices& objectVertices);
  
};
