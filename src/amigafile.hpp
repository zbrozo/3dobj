#pragma once

#include <string>

class Object3D;

class AmigaFile
{

public:
  
  bool Load(const std::string& name, Object3D& object);
  bool Save(const Object3D& object);

};
