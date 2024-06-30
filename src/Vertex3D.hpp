#pragma once

#include <string>
#include <ostream>
#include <type_traits>

template<class T>
class Vertex3D final
{
  static_assert(std::is_integral_v<T>);
  
  T mX = 0;
  T mY = 0;
  T mZ = 0;

public:

  Vertex3D() {}
    
  Vertex3D(T x, T y, T z) :
    mX(x), mY(y), mZ(z)
  {
  }

  ~Vertex3D() = default;

  Vertex3D(Vertex3D const &) = default;
  Vertex3D(Vertex3D &&) = default;
  Vertex3D& operator=(const Vertex3D&) = default;
  Vertex3D& operator=(Vertex3D &&) = default;
  
  Vertex3D operator+(const Vertex3D& v) const noexcept;
  Vertex3D& operator+=(const Vertex3D& v) noexcept;
  Vertex3D operator-(const Vertex3D& v) const noexcept;
  Vertex3D& operator-=(const Vertex3D& v) noexcept;
  Vertex3D operator*(T value) const noexcept;
  Vertex3D operator/(T value) const noexcept;

  bool operator==(const Vertex3D& v) const noexcept;

  constexpr T getX() const noexcept { return mX; } 
  constexpr T getY() const noexcept { return mY; } 
  constexpr T getZ() const noexcept { return mZ; } 
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vertex3D<T>& vertex)
{
  os << "[" << vertex.getX()  << ", " << vertex.getY() << ", " << vertex.getZ() << "]";
  return os;
}
