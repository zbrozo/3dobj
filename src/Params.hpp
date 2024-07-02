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
  Composite,
  Square,
  SquareHolePart1,
  SquareHolePart2,
  Pyramid,
  Rectangle,
  Taper,
  Cylinder,
};

enum class ParamsId {
  AdditionalParams,
  ComponentsList,
  ComponentsParams,
  SinusParams,
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
using SinusParamsVector = std::vector<double>;
using ComponentNamesVector = std::vector<std::string>;
using ParamsPair = std::pair<ParamsId, std::variant<ParamsVector, ComponentNamesVector, SinusParamsVector>>;
using ParamsMap = std::map<ParamsId, std::variant<ParamsVector, ComponentNamesVector, SinusParamsVector>>;

class Object3D;
using ComponentsVector = std::vector<std::unique_ptr<Object3D>>;
using ComponentsWithParamsPair = std::pair<ParamsVector, std::unique_ptr<ComponentsVector>>;
using ComponentsWithParamsVector = std::vector<ComponentsWithParamsPair>;
