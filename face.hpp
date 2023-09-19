#pragma once
#include <vector>

class Vertex;
class Vector3d;

class Face : public std::vector<unsigned short>
{

public:

  Vector3d CalculateNormalVector(const std::vector<Vertex>& vertices) const;
  Vertex GetCenter(const std::vector<Vertex>& vertices) const;
  bool IsVisible(const std::vector<Vertex>& vertices) const;
};
