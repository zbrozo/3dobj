#include "ObjectFactoryBase.hpp"
#include "IGenerator.hpp"
#include "Components.hpp"
#include "ComponentFactories.hpp"
#include "Params.hpp"

#include <algorithm>
#include <optional>
#include <type_traits>
#include <variant>
#include <type_traits>

using namespace std::placeholders;

namespace
{

auto findParamsVector = [](const ParamsPair& params, ParamsId id) {
  return params.first == id;
};

void InitAllComponentFactoriesVector(ComponentFactories& allComponentFactories)
{
  allComponentFactories[ObjectId::Square] = std::make_unique<Components::SquareFactory>();
  allComponentFactories[ObjectId::Rectangle] = std::make_unique<Components::RectangleFactory>();
  allComponentFactories[ObjectId::SquareHolePart1] = std::make_unique<Components::SquareWithHolePart1Factory>();
  allComponentFactories[ObjectId::SquareHolePart2] = std::make_unique<Components::SquareWithHolePart2Factory>();
  allComponentFactories[ObjectId::Pyramid] = std::make_unique<Components::PyramidFactory>();
  allComponentFactories[ObjectId::Taper] = std::make_unique<Components::TaperFactory>();
  allComponentFactories[ObjectId::Cylinder] = std::make_unique<Components::CylinderFactory>();
}

template<typename T>
void appendParams (std::string& result, const T& params) {
  for (auto value : params)
  {
    if constexpr (std::is_same_v<T, ParamsVector>) {
      result += "_" + std::to_string(value);
    }
    if constexpr (std::is_same_v<T, SinusParamsVector>) {
      result += "_" + std::to_string(value);
    }
    else {
      result += "_" + value;
    }
  }
};

} // namespace

ObjectFactoryBase::ObjectFactoryBase()
{
  InitAllComponentFactoriesVector(mAllComponentFactories);
}

std::unique_ptr<Object3D> ObjectFactoryBase::Create(
  const std::string& name,
  const ParamsMap& params) const
{
  auto object = FactoryMethod(name, params);
  Generate(*object);
  return object;
}

std::string ObjectFactoryBase::CreateFullName(const std::string& name, const ParamsMap &params) const
{
  std::string result = name;
  
  for (const auto& paramsVector : params)
  {
    std::visit(
      [&](auto&& arg){
        appendParams(result, arg);
      },
      paramsVector.second);
  }
  
  return result;
}

void ObjectFactoryBase::Generate(Object3D& object) const
{
  auto& generator = dynamic_cast<IGenerator&>(object);
  generator.Generate();
  
  object.CreateNormalVectors();
}
