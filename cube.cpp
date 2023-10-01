#include "cube.hpp"
#include "rotation.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

void Cube::CreateFaceWithVertices(int step, int degX, int degY, Face& face, Vertices& vertices)
{
  const short value = 50;
  
  const short scaleValue = 10;
  
  Vertices baseVertices= {
    {value, value, value},
    {-value, value, value},
    {-value, -value, value},
    {value, -value, value},
  };

  Vertices tmpVertices;
  for (auto vertex : baseVertices)
    {
      vertex = vertex * scaleValue;
      
      Rotation rotation;

      Vertex v;
      
      if (degX)
        {
          v = rotation.rotateX(vertex, step * degX);
        }
      else if (degY)
        {
          v = rotation.rotateY(vertex, step * degY);
        }

      v = v / scaleValue;

      tmpVertices.push_back(v);
    }
  
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
        const short vertexRange = 2;

        if ((vertex.mX >= v.mX - vertexRange && vertex.mX <= v.mX + vertexRange)
            && (vertex.mY >= v.mY - vertexRange && vertex.mY <= v.mY + vertexRange)
            && (vertex.mZ >= v.mZ - vertexRange && vertex.mZ <= v.mZ + vertexRange))
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


