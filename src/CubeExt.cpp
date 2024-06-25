#include "CubeExt.hpp"
#include "IGenerator.hpp"
#include <algorithm>

#include <boost/log/trivial.hpp>

namespace
{

auto getParam(std::vector<int> values, unsigned int index)
{
  if (values.size() > index)
  {
    return values[index];
  }

  return 0;
}

} // namespace

void CubeExt::Generate()
{
  for (auto& pair : *mObjects)
  {
    const auto& params = pair.first;
    
    auto translationX = getParam(params, 0);
    auto translationY = getParam(params, 1);
    auto translationZ = getParam(params, 2);

    BOOST_LOG_TRIVIAL(debug) << "Component vertices translation: " << translationX << " "  << translationY << " " << translationZ << std::endl;
        
    for (auto& object : *pair.second)
    {
      std::transform(
        object->mVertices.cbegin(),
        object->mVertices.cend(),
        object->mVertices.begin(),
        [&](const Vertex& vertex){
          return Vertex(
            vertex.getX() + translationX,
            vertex.getY() + translationY,
            vertex.getZ() + translationZ
            );
        });
      
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
}
