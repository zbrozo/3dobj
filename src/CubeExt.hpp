#pragma once

#include "Cube.hpp"
#include "IGenerator.hpp"
#include "Object3d.hpp"
#include <memory>
#include <vector>

using ComponentsVector = std::vector<std::unique_ptr<Object3D>>;

class CubeExt : public Cube
{

  std::unique_ptr<ComponentsVector> mObjects = nullptr;
  
public:

  CubeExt(const char* name, std::unique_ptr<ComponentsVector> objects) :
    Cube(name),
    mObjects(std::move(objects))
  {
  }
  
  virtual ~CubeExt() = default;
  
  CubeExt(CubeExt const &) = delete;
  CubeExt(CubeExt &&) = delete;
  CubeExt& operator=(const CubeExt& v) = delete;
  CubeExt& operator=(CubeExt &&) = delete;
  
  virtual void Generate() override;
};
