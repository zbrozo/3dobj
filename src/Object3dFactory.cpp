
#include "Object3dFactory.hpp"
#include "Cube.hpp"
#include "Cube2.hpp"
#include "Thorus.hpp"

#include <stdexcept>

const std::string TooLessParamsMessage = "Too less parameters for ";

std::unique_ptr<Object3D> ObjectFactory::Create(const std::string& name, const Object3dParams& params) const
{
  auto object = FactoryMethod(name, params);
  Generate(*object);
  return object;
}

void ObjectFactory::Generate(Object3D& object) const
{
  auto& generator = dynamic_cast<IGenerator&>(object);
  generator.Generate();
  
  object.CreateNormalVectors();
}

std::unique_ptr<Object3D> CubeFactory::FactoryMethod(
  const std::string& name,
  const Object3dParams& /*params*/) const
{
  auto object = std::make_unique<Cube>(name.c_str());
  return object;
}

std::unique_ptr<Object3D> Cube2Factory::FactoryMethod(
  const std::string& name,
  const Object3dParams& /*params*/) const 
{
  auto object = std::make_unique<Cube2>(name.c_str());
  return object;
}

std::unique_ptr<Object3D> ThorusFactory::FactoryMethod(
  const std::string& name,
  const Object3dParams& params) const
{
  if (params.size() < 2)
  {
    throw std::out_of_range(TooLessParamsMessage + name);
  }
  
  const auto circleSize = params[0];
  const auto ringSize = params[1];
  const auto nameExt = std::string(name) + "_" + circleSize + "_" + ringSize;
  
  auto object = std::make_unique<Thorus>(
    std::stoi(circleSize),
    std::stoi(ringSize),
    nameExt.c_str());

  return object;
}
