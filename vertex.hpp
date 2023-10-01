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

  Vertex operator=(const Vertex& v)
  {
    mX = v.mX;
    mY = v.mY;
    mZ = v.mZ;
    return *this;
  }
  
  Vertex operator+(const Vertex& v) const
  {
    const Vertex result(mX + v.mX,
                        mY + v.mY,
                        mZ + v.mZ);
    return result;
  }

  bool operator==(const Vertex& v) const
  {
    return (mX == v.mX && mY == v.mY && mZ == v.mZ);
  }

  Vertex operator*(short value) const
  {
    const Vertex result(mX * value, mY * value, mZ * value);
    return result;
  }
  
  Vertex operator/(short value) const
  {
    Vertex vertex(mX / value, mY / value, mZ / value);

    if (abs(mX % value) >= (value / 2))
      {
        vertex.mX += vertex.mX < 0 ? -1 : 1;
      }

    if (abs(mY % value) >= (value / 2))
      {
        vertex.mY += vertex.mY < 0 ? -1 : 1;
      }

    if (abs(mZ % value) >= (value / 2))
      {
        vertex.mZ += vertex.mZ < 0 ? -1 : 1;
      }
    
    return vertex;
  }
  
  std::string ToString() const
  {
    const std::string s(std::to_string(mX) + ", " + std::to_string(mY) + ", " + std::to_string(mZ));
    return s;
  }
  
};
