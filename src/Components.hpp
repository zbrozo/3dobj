#pragma once

#include "IGenerator.hpp"
#include "Object3D.hpp"

#include <optional>
#include <iostream>

namespace Components
{

class Square : public Object3D, public IGenerator
{
  int mSize = 50;
  
public:

  Square(std::optional<int> size) :
    Object3D("")
  {
    if (size.has_value())
    {
      mSize = size.value();
    }
  }

  void Generate() override;
  
  virtual ~Square() = default;
  
  Square(Square const &) = delete;
  Square(Square &&) = delete;
  Square& operator=(const Square&) = delete;
  Square& operator=(Square &&) = delete;

};

class SquareWithHolePart1 : public Object3D, public IGenerator
{
  int mSize1 = 50;
  int mSize2 = 20;
  int mSize3 = 20;
  
public:

  SquareWithHolePart1(
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
  
  virtual ~SquareWithHolePart1() = default;
  
  SquareWithHolePart1(SquareWithHolePart1 const &) = delete;
  SquareWithHolePart1(SquareWithHolePart1 &&) = delete;
  SquareWithHolePart1& operator=(const SquareWithHolePart1&) = delete;
  SquareWithHolePart1& operator=(SquareWithHolePart1 &&) = delete;

};

class SquareWithHolePart2 : public Object3D, public IGenerator
{
  int mSize1 = 50;
  int mSize2 = 20;
  
public:

  SquareWithHolePart2(
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
  
  virtual ~SquareWithHolePart2() = default;
  
  SquareWithHolePart2(SquareWithHolePart2 const &) = delete;
  SquareWithHolePart2(SquareWithHolePart2 &&) = delete;
  SquareWithHolePart2& operator=(const SquareWithHolePart2&) = delete;
  SquareWithHolePart2& operator=(SquareWithHolePart2 &&) = delete;

};

class Pyramid : public Object3D, public IGenerator
{
  int mSize1 = 50;
  int mSize2 = 20;
  
public:

  Pyramid(
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
  
  virtual ~Pyramid() = default;
  
  Pyramid(Pyramid const &) = delete;
  Pyramid(Pyramid &&) = delete;
  Pyramid& operator=(const Pyramid&) = delete;
  Pyramid& operator=(Pyramid &&) = delete;

};

}