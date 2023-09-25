#pragma once
#include <vector>
#include <string>

class Vertex;
class Vector3d;

class Face : public std::vector<unsigned short>
{

public:

  Face()
  {
  }
  
  Face(std::initializer_list<unsigned short> init)
  {
    insert(end(), init.begin(), init.end());
  }

  
  Vector3d CalculateNormalVector(const std::vector<Vertex>& vertices) const;
  Vertex GetCenter(const std::vector<Vertex>& vertices) const;
  bool IsVisible(const std::vector<Vertex>& vertices) const;

  std::string ToString() const;
};
