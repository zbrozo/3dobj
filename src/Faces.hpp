#pragma once
#include <vector>
#include "Face.hpp"

class Faces : public std::vector<Face>
{
public:

  Faces()
  {
  }
  
  Faces(std::initializer_list<Face> init)
  {
    insert(end(), init.begin(), init.end());
  }

  virtual ~Faces() = default;
  
  Faces(Faces const &) = default;
  Faces(Faces&&) = default;
  Faces& operator=(const Faces&) = default;
  Faces& operator=(Faces &&) = default;
  
  friend std::ostream& operator<<(std::ostream& os, const Faces& faces);
  
};
