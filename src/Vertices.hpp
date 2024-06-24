#pragma once

#include <vector>

#include "Types.hpp"

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

  virtual ~Vertices() = default;
  
  Vertices(Vertices const &) = default;
  Vertices(Vertices&&) = delete;
  Vertices& operator=(const Vertices&) = default;
  Vertices& operator=(Vertices &&) = default;
  
  Vertices& operator+=(const Vertex& vertex);
  
  Vertices Rotate(int degX, int degY, int degZ) const;
};


