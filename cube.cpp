#include "cube.hpp"
#include "rotation.hpp"
#include <algorithm>
#include <iostream>

Vertices Cube::CreateVertices(int step, int degX, int degY)
{
  const short value = 50;

  Vertices baseVertices= {
    {value, value, value},
    {-value, value, value},
    {-value, -value, value},
    {value, -value, value},
  };

  Vertices resultVertices;
  
  for (auto vertex : baseVertices)
    {
      Rotation rotation;
      
      if (degX)
        {
          auto v = rotation.rotateX(vertex, step * degX);
          std::cout << v.ToString() << "\n";
          resultVertices.push_back(v);
        }
      else if (degY)
        {
          auto v = rotation.rotateY(vertex, step * degY);
          resultVertices.push_back(v);
        }
    }
  /*
  std::for_each(resultVertices.begin(), resultVertices.end(),
                [](auto& v) {
                  v = v / 10;
                });
  */
  return resultVertices;
}

void Cube::CreateFaceWithVertices(const Vertices& tmpVertices,
                                  Face& oFace,
                                  Vertices& oVertices)
{
  Face tmpFace{0,1,2,3};
  for (size_t j = 0; j < tmpFace.size(); ++j)
    {
      auto& vertexNr = tmpFace[j];
      Vertex vertex = tmpVertices[vertexNr];

      int foundNr = 0;
      auto found = std::find_if(vertices.begin(), vertices.end(), [&](const Vertex& v){
        if ((vertex.x >= v.x - 2 && vertex.x <= v.x + 2)
            && (vertex.y >= v.y - 2 && vertex.y <= v.y + 2)
            && (vertex.z >= v.z - 2 && vertex.z <= v.z + 2))
          {
            return true;
          }

        ++foundNr;
        return false;
      });

      if (found != vertices.end())
        {
          oFace.push_back(foundNr);
        }
      else
        {
          oVertices.push_back(vertex);
          oFace.push_back((oVertices.size() - 1) + vertices.size());
        }
    }
}


void Cube::Generate()
{
  const size_t facesCount = 4;
  for (size_t i = 0; i < facesCount; ++i)
    {
      Face resultFace;
      Vertices resultVertices;
      const Vertices tmpVertices = CreateVertices(i, 90, 0);
      CreateFaceWithVertices(tmpVertices, resultFace, resultVertices);
      vertices.insert(vertices.end(), resultVertices.begin(), resultVertices.end());
      faces.push_back(resultFace);
    }

  {
      Face resultFace;
      Vertices resultVertices;
      const Vertices tmpVertices = CreateVertices(1, 0, 90);
      CreateFaceWithVertices(tmpVertices, resultFace, resultVertices);
      vertices.insert(vertices.end(), resultVertices.begin(), resultVertices.end());
      faces.push_back(resultFace);
  }

  {
      Face resultFace;
      Vertices resultVertices;
      const Vertices tmpVertices = CreateVertices(1, 0, -90);
      CreateFaceWithVertices(tmpVertices, resultFace, resultVertices);
      vertices.insert(vertices.end(), resultVertices.begin(), resultVertices.end());
      faces.push_back(resultFace);
  }
  
}


