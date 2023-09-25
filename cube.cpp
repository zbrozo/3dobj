#include "cube.hpp"
#include "rotation.hpp"
#include <algorithm>
#include <iostream>

void Cube::CreateFaceWithVertices(int step, int degX, int degY, Face& face, Vertices& vertices)
{
  const short value = 50;

  Vertices baseVertices= {
    {value, value, value},
    {-value, value, value},
    {-value, -value, value},
    {value, -value, value},
  };

  Vertices tmpVertices;
  for (auto vertex : baseVertices)
    {
      Rotation rotation;
      
      if (degX)
        {
          auto v = rotation.rotateX(vertex, step * degX);
          tmpVertices.push_back(v);
        }
      else if (degY)
        {
          auto v = rotation.rotateY(vertex, step * degY);
          tmpVertices.push_back(v);
        }
    }
  /*
  std::for_each(resultVertices.begin(), resultVertices.end(),
                [](auto& v) {
                  v = v / 10;
                });
  */

  face = Face{0,1,2,3};
  vertices = tmpVertices;

}

void Cube::ProcessFaceWithVertices(Face& face, Vertices& vertices)
{
  Face resultFace;
  Vertices resultVertices;
  
  for (size_t i = 0; i < face.size(); ++i)
    {
      auto& vertexNr = face[i];
      Vertex vertex = vertices[vertexNr];

      int foundNr = 0;
      auto found = std::find_if(mVertices.begin(), mVertices.end(), [&](const Vertex& v){
        if ((vertex.x >= v.x - 2 && vertex.x <= v.x + 2)
            && (vertex.y >= v.y - 2 && vertex.y <= v.y + 2)
            && (vertex.z >= v.z - 2 && vertex.z <= v.z + 2))
          {
            return true;
          }

        ++foundNr;
        return false;
      });

      if (found != mVertices.end())
        {
          resultFace.push_back(foundNr);
        }
      else
        {
          resultVertices.push_back(vertex);
          resultFace.push_back((resultVertices.size() - 1) + mVertices.size());
        }
    }

  face = resultFace;
  vertices = resultVertices;
}


void Cube::Generate()
{
  const size_t facesCount = 4;
  for (size_t i = 0; i < facesCount; ++i)
    {
      Face face;
      Vertices vertices;
      CreateFaceWithVertices(i, 90, 0, face, vertices);
      ProcessFaceWithVertices(face, vertices);
      mVertices.insert(mVertices.end(), vertices.begin(), vertices.end());
      mFaces.push_back(face);
    }

  {
      Face face;
      Vertices vertices;
      CreateFaceWithVertices(1, 0, 90, face, vertices);
      ProcessFaceWithVertices(face, vertices);
      mVertices.insert(mVertices.end(), vertices.begin(), vertices.end());
      mFaces.push_back(face);
  }

  {
      Face face;
      Vertices vertices;
      CreateFaceWithVertices(1, 0, -90, face, vertices);
      ProcessFaceWithVertices(face, vertices);
      mVertices.insert(mVertices.end(), vertices.begin(), vertices.end());
      mFaces.push_back(face);
  }
  
}


