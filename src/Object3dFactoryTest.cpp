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

BOOST_AUTO_TEST_SUITE_END()
