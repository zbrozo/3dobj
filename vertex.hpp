#pragma once

//#include <vector>

class Vertex
{

public:

  short x;
  short y;
  short z;

  Vertex()
  {
  }
    
  Vertex(short _x, short _y, short _z)
  {
    x = _x;
    y = _y;
    z = _z;
  }

  Vertex operator+(const Vertex& v)
  {
    x += v.x;
    y += v.y;
    z += v.z;
    return (*this);
  }
  
};

//using Vertices = std::vector<Vertex>;
