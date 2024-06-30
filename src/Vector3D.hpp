#pragma once
#include "Vertex3D.hpp"
#include <cmath>
#include <ostream>
#include <type_traits>

template<typename T>
class Vector3D final
{
  static_assert(std::is_integral_v<T>);

  Vertex3D<T> mBegin = {0,0,0};
  Vertex3D<T> mEnd = {0,0,0};
  
public:

  Vector3D() {}

  Vector3D(Vertex3D<T> end) :
    mBegin({0,0,0}), mEnd(end)
  {
  }
  
  Vector3D(Vertex3D<T> begin, Vertex3D<T> end) :
    mBegin(begin), mEnd(end)
  {
  }

  ~Vector3D() = default;

  Vector3D(const Vector3D&) = default;
  Vector3D(Vector3D &&) = default;
  Vector3D& operator=(const Vector3D&) = default;
  Vector3D& operator=(Vector3D &&) = default;

  bool operator==(const Vector3D& v) const noexcept;

  constexpr Vertex3D<T> getBegin() const noexcept
  {
    return mBegin;
  }

  constexpr Vertex3D<T> getEnd() const noexcept
  {
    return mEnd;
  }
  
  constexpr T getX() const noexcept
  {
    return mEnd.getX() - mBegin.getX();
  }

  constexpr T getY() const noexcept
  {
    return mEnd.getY() - mBegin.getY();
  }

  constexpr T getZ() const noexcept
  {
    return mEnd.getZ() - mBegin.getZ();
  }

  constexpr int length() const noexcept
  {
    const auto x = getX();
    const auto y = getY();
    const auto z = getZ();
    return sqrt(x * x + y * y + z * z);
  }
  
  Vector3D calculateCrossProduct(const Vector3D& v) const noexcept;
  Vector3D normalize(int normalizedVectorLength = 64) const noexcept;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector3D<T>& vector)
{
  os << "[" << vector.getX()  << ", " << vector.getY() << ", " << vector.getZ() << "]";
  return os;
}
