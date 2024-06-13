#pragma once

#include "IGenerator.hpp"
#include "Object3d.hpp"

class Component1 : public Object3D, public IGenerator
{
public:

  Component1() :
    Object3D("SimpleObject1")
  {
  }

  void Generate() override;
  
  virtual ~Component1() = default;
  
  Component1(Component1 const &) = delete;
  Component1(Component1 &&) = delete;
  Component1& operator=(const Component1& v) = delete;
  Component1& operator=(Component1 &&) = delete;

};

class Component2 : public Object3D, public IGenerator
{
public:

  Component2() :
    Object3D("Component2")
  {
  }

  void Generate() override;
  
  virtual ~Component2() = default;
  
  Component2(Component2 const &) = delete;
  Component2(Component2 &&) = delete;
  Component2& operator=(const Component2& v) = delete;
  Component2& operator=(Component2 &&) = delete;

};
