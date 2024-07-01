#include "ViewerSortingFaces.hpp"

#include "Vertices.hpp"
#include "Faces.hpp"

#include <algorithm>

FaceNumbers PrepareFaceNumbers(const Vertices& vertices2d, const Faces &faces)
{
  FaceNumbers faceNumbers;

  unsigned int faceNr = 0;

  for (const auto& face : faces)
  {
    if (!face.IsVisible(vertices2d))
    {
      ++faceNr;
      continue;
    }
    
    auto centerVertex = face.GetCenter(vertices2d);
    faceNumbers.push_back(faceNr);

    ++faceNr;
  }
  
  return faceNumbers;
}

FaceNumbers SortFaceNumbers(const Vertices& vertices2d, const Faces &faces)
{
  FaceNumbers faceNumbers = PrepareFaceNumbers(vertices2d, faces);

  std::sort(faceNumbers.begin(), faceNumbers.end(),
    [&vertices2d, &faces](int first, int second)
    {
      const Vertex v1 = faces[first].GetCenter(vertices2d);
      const Vertex v2 = faces[second].GetCenter(vertices2d);
      return v1.getZ() > v2.getZ();
    });

  return faceNumbers;
}
