#define BOOST_TEST_MODULE tests
#include <boost/test/unit_test.hpp>

#include "IGenerator.hpp"
#include "ObjectFactories.hpp"
#include "Object3D.hpp"
#include "Cube.hpp"
#include "Thorus.hpp"
#include "Params.hpp"

BOOST_AUTO_TEST_SUITE(ObjectFactory_Suite)

BOOST_AUTO_TEST_CASE(vector_crossproduct_test)
{
  Vector3D<int> vector1 {{0,0,0}, {10, 5, 10}};
  Vector3D<int> vector2 {{0,0,0}, {5, 10, 5}};
  const auto result = vector1.calculateCrossProduct(vector2);
  BOOST_CHECK_EQUAL(result, Vector3D<int>(Vertex3D<int>(-75, 0, 75)));
}

BOOST_AUTO_TEST_CASE(vector_normalize_test)
{
  Vector3D<int> vector {{0,0,0}, {10, 10, 10}};
  const auto result = vector.normalize();
  BOOST_CHECK_EQUAL(result.length(), 64);
  BOOST_CHECK_EQUAL(result, Vector3D<int>(Vertex3D<int>(37, 37, 37)));
}

BOOST_AUTO_TEST_CASE(cube_factory_test)
{
  CubeFactory factory;
  ParamsMap paramsMap;

  const auto object = factory.Create("cube", paramsMap);
  
  BOOST_CHECK_EQUAL("cube", object->mName);
  BOOST_CHECK_EQUAL(8, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(6, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(cube_ext_factory_test1)
{
  CubeExtFactory factory;
  ParamsMap paramsMap;

  paramsMap[ParamsId::ComponentsList] = {1, 2};

  const auto object = factory.Create("cube-ext", paramsMap);
  
  BOOST_CHECK_EQUAL("cube-ext_1_2", object->mName);
  BOOST_CHECK_EQUAL(40, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(cube_ext_factory_test2)
{
  CubeExtFactory factory;
  ParamsMap paramsMap;

  paramsMap[ParamsId::ComponentsList] = {1, 2};
  paramsMap[ParamsId::ComponentsParams] = {50, 20, 20};
  
  const auto object = factory.Create("cube-ext", paramsMap);
  
  BOOST_CHECK_EQUAL("cube-ext_1_2_50_20_20", object->mName);
  BOOST_CHECK_EQUAL(40, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(thorus_factory_test)
{
  ThorusFactory factory;
  ParamsMap paramsMap;

  paramsMap[ParamsId::AdditionalParams] = {6, 8};

  auto object = factory.Create("thorus", paramsMap);

  BOOST_CHECK_EQUAL("thorus_6_8", object->mName);
  BOOST_CHECK_EQUAL(48, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_SUITE_END()
