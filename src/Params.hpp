#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <variant>

enum class ObjectId {
  None = 0,
  Cube = 1,
  CubeExt = 2,
  Thorus = 3,
  Cuboid = 4,
  Square = 5,
  SquareHolePart1 = 6,
  SquareHolePart2 = 7,
  Pyramid = 8,
};

enum class ParamsId {
  ComponentsList,
  ComponentsParams,
  AdditionalParams,
  ComponentsListFace0,
  ComponentsListFace1,
  ComponentsListFace2,
  ComponentsListFace3,
  ComponentsListFace4,
  ComponentsListFace5,
  ComponentsParamsFace0,
  ComponentsParamsFace1,
  ComponentsParamsFace2,
  ComponentsParamsFace3,
  ComponentsParamsFace4,
  ComponentsParamsFace5,
  ParamsFace0,
  ParamsFace1,
  ParamsFace2,
  ParamsFace3,
  ParamsFace4,
  ParamsFace5,
};

using ParamsVector = std::vector<int>;
using ComponentNamesVector = std::vector<std::string>;
using ParamsPair = std::pair<ParamsId, std::variant<ParamsVector, ComponentNamesVector>>;
using ParamsMap = std::map<ParamsId, std::variant<ParamsVector, ComponentNamesVector>>;

class Object3D;
using ComponentsVector = std::vector<std::unique_ptr<Object3D>>;
using ComponentsAndMainParamsPair = std::pair<ParamsVector, std::unique_ptr<ComponentsVector>>;
using ComponentsPerFaceVector = std::vector<ComponentsAndMainParamsPair>;
