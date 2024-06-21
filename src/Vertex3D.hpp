#pragma once

#include <string>
#include <ostream>

template<class T>
class Vertex3D
{
  
  T mX = 0;
  T mY = 0;
  T mZ = 0;

public:

  Vertex3D() {}
    
  Vertex3D(T x, T y, T z) :
    mX(x), mY(y), mZ(z)
  {
  }

  virtual ~Vertex3D() = default;

  Vertex3D(Vertex3D const &) = default;
  Vertex3D(Vertex3D &&) = default;
  Vertex3D& operator=(const Vertex3D&) = default;
  Vertex3D& operator=(Vertex3D &&) = default;
  
  Vertex3D operator+(const Vertex3D& v) const;
  Vertex3D& operator+=(const Vertex3D& v);
  bool operator==(const Vertex3D& v) const;
  Vertex3D operator*(T value) const;
  Vertex3D operator/(T value) const;

  T getX() const { return mX; } 
  T getY() const { return mY; } 
  T getZ() const { return mZ; } 
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vertex3D<T>& vertex)
{
  os << "[" << vertex.getX()  << ", " << vertex.getY() << ", " << vertex.getZ() << "]";
  return os;
}
