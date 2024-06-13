#define BOOST_TEST_MODULE tests
#include <boost/test/unit_test.hpp>
#include "IGenerator.hpp"
#include "Object3dFactory.hpp"
#include "Object3d.hpp"

#include "Cube.hpp"
#include "Cube2.hpp"
#include "Thorus.hpp"

BOOST_AUTO_TEST_SUITE(ObjectFactory_Suite)

BOOST_AUTO_TEST_CASE(cube_factory_test)
{
  CubeFactory factory;
  Object3dParams params;
  auto object = factory.Create("cube", params);
  
  BOOST_CHECK_EQUAL("cube", object->mName);
}

BOOST_AUTO_TEST_CASE(thorus_factory_test)
{
  ThorusFactory factory;
  Object3dParams params;
  params.push_back("4");
  params.push_back("10");
  auto object = factory.Create("thorus", params);
  
  BOOST_CHECK_EQUAL("thorus_4_10", object->mName);
}

BOOST_AUTO_TEST_SUITE_END()
