#pragma once

#include "Types.hpp"

class Vertices;

template<typename T>
Vertex CalculatePerspective(const T& v, int zoom = 400)
{
  auto z = v.getZ() + zoom;
  auto x = (v.getX() << 10) / z;
  auto y = (v.getY() << 10) / z;
  return Vertex(x, y, v.getZ());
}

Vertices CalculatePerspective(const Vertices& vertices, int zoom);
