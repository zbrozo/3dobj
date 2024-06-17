#pragma once

#include "ObjectFactoryBase.hpp"

class CubeFactory : public ObjectFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const override;
};

class CubeExtFactory : public ObjectFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const override;
};

class ThorusFactory : public ObjectFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const override;
};
