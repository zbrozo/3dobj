#pragma once

#include <vector>
#include <string>
#include <map>

enum class ParamsId {
  ComponentsList,
  ComponentsParams,
  AdditionalParams
};

using ParamsVector = std::vector<int>;
using ParamsMap = std::map<ParamsId, ParamsVector>;

