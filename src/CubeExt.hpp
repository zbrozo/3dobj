#pragma once

#include "Cube.hpp"
#include "IGenerator.hpp"
#include "Object3D.hpp"
#include "Params.hpp"

#include <memory>
#include <vector>

class CubeExt : public Cube
{

  std::unique_ptr<ComponentsWithParamsVector> mObjects = nullptr;
  
public:

  CubeExt(const char* name, std::unique_ptr<ComponentsWithParamsVector> objects) :
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
