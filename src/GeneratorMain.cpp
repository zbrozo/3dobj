#include "IGenerator.hpp"
#include "Face.hpp"
#include "Object3D.hpp"
#include "Cube.hpp"
#include "CubeExt.hpp"
#include "Thorus.hpp"
#include "ObjectFactories.hpp"
#include "AmigaFile.hpp"
#include "Params.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <array>
#include <map>
#include <memory>
#include <utility>

#include <boost/program_options.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace po = boost::program_options;

std::map<std::string, ObjectId> ObjectIdMap {
  {"cube", ObjectId::Cube},
  {"cube-ext", ObjectId::CubeExt},
  {"thorus", ObjectId::Thorus},
  {"cuboid", ObjectId::Cuboid},
};

std::map<ObjectId, std::string> ParamsHelp {
  {ObjectId::Cube, "additional-params: size"},
  {ObjectId::CubeExt, "component-list and component-params must be defined"},
  {ObjectId::Thorus, "additional-params: circleAmount ringAmount circleSize circleOffset"},
  {ObjectId::Cuboid, ""}
};

using ObjectFactoryPair = std::pair<ObjectId, std::unique_ptr<ObjectFactoryBase>>;
std::map<ObjectId, std::unique_ptr<ObjectFactoryBase>> ObjectFactoryMap;

void InitObjectFactoryMap()
{
  ObjectFactoryMap.insert(ObjectFactoryPair(ObjectId::Cube, std::make_unique<CubeFactory>()));
  ObjectFactoryMap.insert(ObjectFactoryPair(ObjectId::CubeExt, std::make_unique<CubeExtFactory>()));
  ObjectFactoryMap.insert(ObjectFactoryPair(ObjectId::Thorus, std::make_unique<ThorusFactory>()));
  ObjectFactoryMap.insert(ObjectFactoryPair(ObjectId::Cuboid, std::make_unique<CuboidFactory>()));
}

const auto& GetFactory(const std::string& name)
{
  InitObjectFactoryMap();

  const auto it = ObjectIdMap.find(name);
  if (it == ObjectIdMap.end())
  {
      throw std::out_of_range("3d object id not found");
  }
  
  const auto creatorIt = ObjectFactoryMap.find(it->second);
  if (creatorIt == ObjectFactoryMap.end())
  {
    throw std::out_of_range("3d object factory not found");
  }

  return creatorIt->second;
}

void PrintParamsHelp()
{
  std::cout << "Possible 3d objects to use:" << std::endl;
  std::for_each(ObjectIdMap.begin(), ObjectIdMap.end(),
    [](std::pair<std::string, ObjectId> item)
      {
        std::cout << "  name: " << item.first << ", params: " << ParamsHelp[item.second];
        std::cout << std::endl;
      });
}

auto ReadGeneratorParams(int argc, char *argv[], po::options_description& desc)
{
  po::variables_map vm;

  po::positional_options_description p;
  p.add("additional-params", -1);

  po::store(po::command_line_parser(argc, argv).
          options(desc).positional(p).run(), vm);
  
  po::notify(vm);

  return vm;
}

void SetLogging(bool verbose)
{
  boost::log::trivial::severity_level logLevel = (verbose ?
    boost::log::trivial::debug : boost::log::trivial::error);
  
  auto logFilter = boost::log::filter(boost::log::trivial::severity >= logLevel);
  boost::log::core::get()->set_filter(logFilter);
}

int main(int argc, char* argv[])
{
  po::options_description optionsDesc("generator <type> [params]\n");
  optionsDesc.add_options()
    ("help,h", "produce help message")
    ("verbose,v", "debug")
    ("output,o", po::value<std::string>(), "output name")
    ("type,t", po::value<std::string>(), "object3d type")
    ("params,f", po::value<ParamsVector>()->multitoken(), "")
    ("component-list,c", po::value<ComponentNamesVector>()->multitoken(),
      "Square, SquareHolePart1, SquareHolePart2, Pyramid")
    ("component-params,p", po::value<ParamsVector>()->multitoken(), "depends on particular component")
    ("additional-params", po::value<ParamsVector>(), "depends on selected object in type")
    ("c0", po::value<ComponentNamesVector>()->multitoken(), "")
    ("c1", po::value<ComponentNamesVector>()->multitoken(), "")
    ("c2", po::value<ComponentNamesVector>()->multitoken(), "") 
    ("c3", po::value<ComponentNamesVector>()->multitoken(), "")
    ("c4", po::value<ComponentNamesVector>()->multitoken(), "")
    ("c5", po::value<ComponentNamesVector>()->multitoken(), "")
    ("p0", po::value<ParamsVector>()->multitoken(), "")
    ("p1", po::value<ParamsVector>()->multitoken(), "")
    ("p2", po::value<ParamsVector>()->multitoken(), "") 
    ("p3", po::value<ParamsVector>()->multitoken(), "")
    ("p4", po::value<ParamsVector>()->multitoken(), "")
    ("p5", po::value<ParamsVector>()->multitoken(), "")
    ("f0", po::value<ParamsVector>()->multitoken(), "")
    ("f1", po::value<ParamsVector>()->multitoken(), "")
    ("f2", po::value<ParamsVector>()->multitoken(), "") 
    ("f3", po::value<ParamsVector>()->multitoken(), "")
    ("f4", po::value<ParamsVector>()->multitoken(), "")
    ("f5", po::value<ParamsVector>()->multitoken(), "")
    ;

  const po::variables_map& options = ReadGeneratorParams(argc, argv, optionsDesc);

  if (options.count("help"))
  {
    std::cout << optionsDesc << std::endl;
    PrintParamsHelp();
    return 1;
  }

  const auto verbose = options.count("verbose");
  
  std::string name;
  if (options.count("type"))
  {
    name = options["type"].as<std::string>();
  }
  else
  {
    std::cout << optionsDesc << std::endl;
    PrintParamsHelp();
    return 1;
  }

  std::string outputName;
  if (options.count("output"))
  {
    outputName = options["output"].as<std::string>();
  }
  
  ParamsMap paramsMap;

  auto getParams = [&options, &paramsMap](std::string name, ParamsId param)
  {
    if (!options[name].empty())
    {
      const auto& list = options[name].as<ParamsVector>();
      paramsMap[param] = list;
    }
  };

  auto getComponent = [&options, &paramsMap](std::string name, ParamsId param)
  {
    if (!options[name].empty())
    {
      const auto& list = options[name].as<ComponentNamesVector>();
      paramsMap[param] = list;
    }
  };

  getComponent("component-list", ParamsId::ComponentsList);
  getParams("params", ParamsId::Params);
  getParams("component-params", ParamsId::ComponentsParams);
  getParams("additional-params", ParamsId::AdditionalParams);

  getComponent("c0", ParamsId::ComponentsList0);
  getComponent("c1", ParamsId::ComponentsList1);
  getComponent("c2", ParamsId::ComponentsList2);
  getComponent("c3", ParamsId::ComponentsList3);
  getComponent("c4", ParamsId::ComponentsList4);
  getComponent("c5", ParamsId::ComponentsList5);

  getParams("p0", ParamsId::ComponentsParams0);
  getParams("p1", ParamsId::ComponentsParams1);
  getParams("p2", ParamsId::ComponentsParams2);
  getParams("p3", ParamsId::ComponentsParams3);
  getParams("p4", ParamsId::ComponentsParams4);
  getParams("p5", ParamsId::ComponentsParams5);

  getParams("f0", ParamsId::Params0);
  getParams("f1", ParamsId::Params1);
  getParams("f2", ParamsId::Params2);
  getParams("f3", ParamsId::Params3);
  getParams("f4", ParamsId::Params4);
  getParams("f5", ParamsId::Params5);
  
  SetLogging(verbose);
  
  try {
    BOOST_LOG_TRIVIAL(debug) << "Creating: " << name;
    const auto& factory = GetFactory(name);
    const auto object3d = factory->Create(name, paramsMap);

    if (!outputName.empty())
    {
      object3d->mName = outputName;
    }
      
    AmigaFile file;
    file.Save(*object3d);

    BOOST_LOG_TRIVIAL(debug) << *object3d;
    
  } catch (const std::out_of_range& ex) {
    BOOST_LOG_TRIVIAL(error) << ex.what();
    PrintParamsHelp();
    return 1;
  } catch (const std::bad_cast& ex) {
    BOOST_LOG_TRIVIAL(error) << ex.what();
    PrintParamsHelp();
    return 1;
  }
  
  return 0;
  
}
