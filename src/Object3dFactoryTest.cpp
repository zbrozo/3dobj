#define BOOST_TEST_MODULE tests
#include <boost/test/unit_test.hpp>

#include "IGenerator.hpp"
#include "Object3dFactory.hpp"
#include "Object3d.hpp"
#include "Cube.hpp"
#include "Thorus.hpp"
#include "Params.hpp"

BOOST_AUTO_TEST_SUITE(ObjectFactory_Suite)

BOOST_AUTO_TEST_CASE(cube_factory_test)
{
  CubeFactory factory;
  ParamsMap paramsMap;

  const auto object = factory.Create("cube", paramsMap);
  
  BOOST_CHECK_EQUAL("cube", object->mName);
  BOOST_CHECK_EQUAL(8, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(6, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(cube_ext_factory_test)
{
  CubeExtFactory factory;
  ParamsMap paramsMap;

  ParamsVector params;
  params.push_back(1);
  params.push_back(2);
  paramsMap[ParamsId::ComponentsList] =  params;

  const auto object = factory.Create("cube-ext", paramsMap);
  
  BOOST_CHECK_EQUAL("cube-ext_1_2", object->mName);
  BOOST_CHECK_EQUAL(40, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(cube_ext2_factory_test)
{
  CubeExtFactory factory;
  ParamsMap paramsMap;

  ParamsVector params;
  params.push_back(1);
  params.push_back(2);
  paramsMap[ParamsId::ComponentsList] =  params;

  params.clear();
  
  params.push_back(50);
  params.push_back(20);
  params.push_back(20);
  paramsMap[ParamsId::ComponentsParams] =  params;
  
  const auto object = factory.Create("cube-ext", paramsMap);
  
  BOOST_CHECK_EQUAL("cube-ext_1_2_50_20_20", object->mName);
  BOOST_CHECK_EQUAL(40, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(thorus_factory_test)
{
  ThorusFactory factory;
  ParamsMap paramsMap;

  ParamsVector params;
  params.push_back(6);
  params.push_back(8);
  paramsMap[ParamsId::AdditionalParams] = params;

  auto object = factory.Create("thorus", paramsMap);

  BOOST_CHECK_EQUAL("thorus_6_8", object->mName);
  BOOST_CHECK_EQUAL(48, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_SUITE_END()
