#pragma once

#include "IGenerator.hpp"
#include "Object3D.hpp"

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
  int mSize1 = 50;
  int mSize2 = 20;
  int mSize3 = 20;
  
public:

  Component1(
    const std::optional<int>& size1,
    const std::optional<int>& size2,
    const std::optional<int>& size3
    ) :
    Object3D("")
  {
    if (size1.has_value())
    {
      mSize1 = size1.value();
    }
    
    if (size2.has_value())
    {
      mSize2 = size2.value();
    }

    if (size3.has_value())
    {
      mSize3 = size3.value();
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
  int mSize1 = 50;
  int mSize2 = 20;
  
public:

  Component2(
    const std::optional<int>& size1,
    const std::optional<int>& size2
    ) :
    Object3D("")
  {
    if (size1.has_value())
    {
      mSize1 = size1.value();
    }
    
    if (size2.has_value())
    {
      mSize2 = size2.value();
    }
  }

  void Generate() override;
  
  virtual ~Component2() = default;
  
  Component2(Component2 const &) = delete;
  Component2(Component2 &&) = delete;
  Component2& operator=(const Component2&) = delete;
  Component2& operator=(Component2 &&) = delete;

};

class Component3 : public Object3D, public IGenerator
{
  int mSize1 = 50;
  int mSize2 = 20;
  
public:

  Component3(
    const std::optional<int>& size1,
    const std::optional<int>& size2
    ) :
    Object3D("")
  {
    if (size1.has_value())
    {
      mSize1 = size1.value();
    }
    
    if (size2.has_value())
    {
      mSize2 = size2.value();
    }
  }

  void Generate() override;
  
  virtual ~Component3() = default;
  
  Component3(Component3 const &) = delete;
  Component3(Component3 &&) = delete;
  Component3& operator=(const Component3&) = delete;
  Component3& operator=(Component3 &&) = delete;

};
