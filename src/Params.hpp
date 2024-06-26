#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <variant>

enum class ObjectId {
  None = 0,
  Cube,
  CubeExt,
  Thorus,
  Cuboid,
  Square,
  SquareHolePart1,
  SquareHolePart2,
  Pyramid,
  Rectangle,
  Taper,
};

enum class ParamsId {
  AdditionalParams,
  ComponentsList,
  ComponentsParams,
  Params,
  ComponentsList0,
  ComponentsList1,
  ComponentsList2,
  ComponentsList3,
  ComponentsList4,
  ComponentsList5,
  ComponentsParams0,
  ComponentsParams1,
  ComponentsParams2,
  ComponentsParams3,
  ComponentsParams4,
  ComponentsParams5,
  Params0,
  Params1,
  Params2,
  Params3,
  Params4,
  Params5,
};

using ParamsVector = std::vector<int>;
using ComponentNamesVector = std::vector<std::string>;
using ParamsPair = std::pair<ParamsId, std::variant<ParamsVector, ComponentNamesVector>>;
using ParamsMap = std::map<ParamsId, std::variant<ParamsVector, ComponentNamesVector>>;

class Object3D;
using ComponentsVector = std::vector<std::unique_ptr<Object3D>>;
using ComponentsWithParamsPair = std::pair<ParamsVector, std::unique_ptr<ComponentsVector>>;
using ComponentsWithParamsVector = std::vector<ComponentsWithParamsPair>;
