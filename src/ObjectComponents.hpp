#pragma once

#include "IGenerator.hpp"
#include "Object3d.hpp"

#include <optional>
#include <iostream>

class Component0 : public Object3D, public IGenerator
{
  int mSize = 50;
  
public:

  Component0(std::optional<int> size) :
    Object3D("")
  {
    if (size.has_value())
    {
      mSize = size.value();
    }
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
  int mSize = 50;
  int mSizeXY = 20;
  int mSizeZ = 20;
  
public:

  Component1(std::optional<int> size, std::optional<int> sizeXY, std::optional<int> sizeZ) :
    Object3D("")
  {
    if (size.has_value())
    {
      mSize = size.value();
    }
    
    if (sizeXY.has_value())
    {
      mSizeXY = sizeXY.value();
    }

    if (sizeZ.has_value())
    {
      mSizeZ = sizeZ.value();
    }
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
  int mSize;
  int mSizeXY;
  
public:

  Component2(std::optional<int> size, std::optional<int> sizeXY) :
    Object3D("")
  {
    if (size.has_value())
    {
      mSize = size.value();
    }
    
    if (sizeXY.has_value())
    {
      mSizeXY = sizeXY.value();
    }
  }

  void Generate() override;
  
  virtual ~Component2() = default;
  
  Component2(Component2 const &) = delete;
  Component2(Component2 &&) = delete;
  Component2& operator=(const Component2&) = delete;
  Component2& operator=(Component2 &&) = delete;

};
