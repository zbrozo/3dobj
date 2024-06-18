#include "CubeExt.hpp"
#include "IGenerator.hpp"

void CubeExt::Generate()
{
  for (auto& object : *mObjects)
  {
    const auto result = CreateCube(
      object->mFaces,
      object->mVertices);
    
    for (auto face : result.first)
    {
      auto r = Object3D::Merge(mVertices,
        face,
        result.second);

      mFaces.push_back(r.first);
      mVertices = r.second;
    }
  }
}
