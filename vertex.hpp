#pragma once

#include <string>

class Vertex
{

public:

  short x;
  short y;
  short z;

  Vertex()
  {
  }
    
  Vertex(short _x, short _y, short _z) :
    x(_x), y(_y), z(_z)
  {
  }

  Vertex operator=(const Vertex& v)
  {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }
  
  Vertex operator+(const Vertex& v) const
  {
    const Vertex result(x + v.x,
                        y + v.y,
                        z + v.z);
    return result;
  }

  bool operator==(const Vertex& v) const
  {
    return (x == v.x && y == v.y && z == v.z);
  }

  Vertex operator/(int value) const
  {
    const Vertex result(x / value, y / value, z / value);
    return result;
  }
  
  std::string ToString() const
  {
    const std::string s(std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z));
    return s;
  }
  
};
