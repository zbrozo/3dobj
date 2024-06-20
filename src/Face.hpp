#pragma once

#include <vector>
#include <string>
#include "Types.hpp"

class Face : public std::vector<unsigned short>
{

public:

  Face() = default;
  
  Face(std::initializer_list<unsigned short> init)
  {
    insert(end(), init.begin(), init.end());
  }

  Face(Face const &) = default;
  Face(Face &&) = default;
  Face& operator=(const Face& v) = default;
  Face& operator=(Face &&) = delete;
  
  Vector CalculateNormalVector(const std::vector<Vertex>& vertices) const;
  Vertex GetCenter(const std::vector<Vertex>& vertices) const;
  bool IsVisible(const std::vector<Vertex>& vertices) const;

  std::string ToString() const;
};
