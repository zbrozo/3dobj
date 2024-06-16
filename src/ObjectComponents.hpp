#pragma once

#include "IGenerator.hpp"
#include "Object3d.hpp"

class Component0 : public Object3D, public IGenerator
{
public:

  Component0() :
    Object3D("")
  {
  }

  void Generate() override;
  
  virtual ~Component0() = default;
  
  Component0(Component0 const &) = delete;
  Component0(Component0 &&) = delete;
  Component0& operator=(const Component0&) = delete;
  Component0& operator=(Component0 &&) = delete;

};

class Component1 : public Object3D, public IGenerator
{
public:

  Component1() :
    Object3D("")
  {
  }

  void Generate() override;
  
  virtual ~Component1() = default;
  
  Component1(Component1 const &) = delete;
  Component1(Component1 &&) = delete;
  Component1& operator=(const Component1&) = delete;
  Component1& operator=(Component1 &&) = delete;

};

class Component2 : public Object3D, public IGenerator
{
public:

  Component2() :
    Object3D("")
  {
  }

  void Generate() override;
  
  virtual ~Component2() = default;
  
  Component2(Component2 const &) = delete;
  Component2(Component2 &&) = delete;
  Component2& operator=(const Component2&) = delete;
  Component2& operator=(Component2 &&) = delete;

};
