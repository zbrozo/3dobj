#pragma once

#include <vector>

#include "Vertex.hpp"

class Vertices : public std::vector<Vertex>
{
public:

  Vertices()
  {
  }
  
  Vertices(std::initializer_list<Vertex> init)
  {
    insert(end(), init.begin(), init.end());
  }
    
  Vertices Rotate(int degX, int degY, int degZ) const;

};


