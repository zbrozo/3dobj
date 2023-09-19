#pragma once

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

  Vertex operator+(const Vertex& v) const
  {
    const Vertex result(x + v.x,
                        y + v.y,
                        z + v.z);
    return result;
  }
  
};
