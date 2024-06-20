#pragma once

#include <string>

template<class T>
class Vertex3D
{
public:

  T mX = 0;
  T mY = 0;
  T mZ = 0;

  Vertex3D() {}
    
  Vertex3D(T x, T y, T z) :
    mX(x), mY(y), mZ(z)
  {
  }

  virtual ~Vertex3D() = default;

  Vertex3D(Vertex3D const &) = default;
  Vertex3D(Vertex3D &&) = default;
  Vertex3D& operator=(const Vertex3D& v) = default;
  Vertex3D& operator=(Vertex3D &&) = default;
  
  Vertex3D operator+(const Vertex3D& v) const;
  bool operator==(const Vertex3D& v) const;
  Vertex3D operator*(T value) const;
  Vertex3D operator/(T value) const;
  
  std::string ToString() const;
  //  Vertex3D Rotate(int degX, int degY, int degZ) const;
};

