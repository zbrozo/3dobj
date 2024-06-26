#include "Cuboid.hpp"
#include "IGenerator.hpp"
#include <optional>

#include <boost/log/trivial.hpp>

namespace
{

auto getParam(const std::vector<int>& values, unsigned int index)
{
  if (values.size() > index)
  {
    return std::optional<int>{values[index]};
  }
    
  return std::optional<int>();
}

void RotateSide(int degx, int degy, int degz,
  const Faces& faces,
  const Vertices& vertices,
  Faces& objectFaces,
  Vertices& objectVertices)
{
  const auto rotatedVertices = vertices.Rotate(degx, degy, degz);
  
  for (const auto& face : faces)
    {
      const auto [resultFace, resultVertices] = Object3D::Merge(objectVertices, face, rotatedVertices);
      objectVertices = resultVertices;
      objectFaces.push_back(resultFace);
    }
}

} // namespace

void Cuboid::Generate()
{
  BOOST_LOG_TRIVIAL(debug) << __FUNCTION__;

  for (const auto& object : *mObjects)
  {
    auto params = object.first;
    auto& components = *object.second;

    auto param0 = getParam(params, 0);
    auto param1 = getParam(params, 1);
    auto param2 = getParam(params, 2);
    auto param3 = getParam(params, 3);
    auto param4 = getParam(params, 4);
    auto param5 = getParam(params, 5);
    
    int offX = param0.has_value() ? param0.value() : 0;
    int offY = param1.has_value() ? param1.value() : 0;
    int offZ = param2.has_value() ? param2.value() : 0;
    int degX = param3.has_value() ? param3.value() : 0;
    int degY = param4.has_value() ? param4.value() : 0;
    int degZ = param5.has_value() ? param5.value() : 0;

    Faces objectFaces;
    Vertices objectVertices;
    
    for (const auto& component : components)
    {
      Vertices vertices{component->mVertices};
      vertices += Vertex(offX, offY, offZ);
      RotateSide(degX, degY, degZ, component->mFaces, vertices, objectFaces, objectVertices);
    }

    for (auto face : objectFaces)
    {
      auto r = Object3D::Merge(mVertices,
        face,
        objectVertices);

      mFaces.push_back(r.first);
      mVertices = r.second;
    }
  }
}
