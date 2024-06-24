#include "Faces.hpp"

std::ostream& operator<<(std::ostream& os, const Faces& faces)
{
  for (const auto& face : faces)
  {
    os << face;
  }

  os << std::endl;

  return os;
}

