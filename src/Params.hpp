#pragma once

#include <vector>
#include <string>
#include <map>

enum class ParamsId {
  ComponentNames,
  AdditionalParams
};

using ParamsVector = std::vector<std::string>;
using ParamsMap = std::map<ParamsId, std::vector<std::string>>;

