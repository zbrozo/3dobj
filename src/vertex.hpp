#pragma once

#include <string>

class Vertex
{

public:

  short mX;
  short mY;
  short mZ;

  Vertex() :
    mX(0), mY(0), mZ(0)
  {
  }
    
  Vertex(short x, short y, short z) :
    mX(x), mY(y), mZ(z)
  {
  }

  virtual ~Vertex() = default;

  Vertex(Vertex const &) = default;
  Vertex(Vertex &&) = default;
  Vertex& operator=(const Vertex& v) = default;
  Vertex& operator=(Vertex &&) = default;
  
  Vertex operator+(const Vertex& v) const;
  bool operator==(const Vertex& v) const;
  Vertex operator*(short value) const;
  Vertex operator/(short value) const;
  
  std::string ToString() const;
  Vertex Rotate(int degX, int degY, int degZ) const;
};
