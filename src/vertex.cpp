#include "vertex.hpp"
#include "rotation.hpp"

Vertex Vertex::operator+(const Vertex& v) const
{
  const Vertex result(mX + v.mX,
                      mY + v.mY,
                      mZ + v.mZ);
  return result;
}

bool Vertex::operator==(const Vertex& v) const
{
  return (mX == v.mX && mY == v.mY && mZ == v.mZ);
}

Vertex Vertex::operator*(short value) const
{
  const Vertex result(mX * value, mY * value, mZ * value);
  return result;
}

Vertex Vertex::operator/(short value) const
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

std::string Vertex::ToString() const
{
  const std::string s(std::to_string(mX) + ", " + std::to_string(mY) + ", " + std::to_string(mZ));
  return s;
}

Vertex Vertex::Rotate(int degX, int degY, int degZ) const
{
  Rotation rotation;

  Vertex v = *this;
  
  if (degX)
    {
      v = rotation.rotateX(v, degX);
    }
  
  if (degY)
    {
      v = rotation.rotateY(v, degY);
    }
  
  if (degZ)
    {
      v = rotation.rotateZ(v, degZ);
    }

  return v;
}
