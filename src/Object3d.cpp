#include <iostream>
#include <algorithm>
#include <cmath>

#include <boost/log/trivial.hpp>

#include "Object3d.hpp"
#include "Vector3d.hpp"

namespace
{
  
auto PrepareFacesAssignedToVertices(
  const Vertices& vertices,
  const Faces& faces)
{
  BOOST_LOG_TRIVIAL(debug) << __FUNCTION__;

  FaceNumbersInVertices result;
  
  for(unsigned int i = 0; i < vertices.size(); i++)
  {
    FaceNumbers foundFaceNumbers;

    unsigned short faceNr = 0;
      
    for (auto face : faces)
    {
      if (std::find(face.begin(), face.end(), i) != face.end())
      {
        foundFaceNumbers.push_back(faceNr);
      }
          
      ++faceNr;
    }

    result.push_back(foundFaceNumbers);
  }

  return result;
}

auto CalculateNormalVectorToFaces(const Vertices& vertices,
  const Faces& faces
  )
{
  BOOST_LOG_TRIVIAL(debug) << __FUNCTION__;

  Vectors normalVectors;
  
  for(auto face : faces)
  {
    const auto vector = face.CalculateNormalVector(vertices);
    normalVectors.push_back(vector);
  }
  
  return normalVectors;
}

auto CalculateVectorsInVertices(const FaceNumbersInVertices& vertexInFaceDependency,
  const Vectors& normalFaceVectors)
{
  BOOST_LOG_TRIVIAL(debug) << __FUNCTION__;  

  Vectors vectorsInVertices;
  
  for(auto faces : vertexInFaceDependency)
  {
    short x = 0;
    short y = 0;
    short z = 0;
      
    for(auto faceNr : faces)
    {
      x += normalFaceVectors[faceNr].mX;
      y += normalFaceVectors[faceNr].mY;
      z += normalFaceVectors[faceNr].mZ;
    }

    const short count = faces.size();
      
    if (faces.size() != 0)
    {
      x = x / count;
      y = y / count;
      z = z / count;
    }

    vectorsInVertices.push_back(Vector3d(x,y,z));      
  }

  return vectorsInVertices;
}

auto NormalizeVectorsInVertices(const Vectors& vectorsInVertices)
{
  BOOST_LOG_TRIVIAL(debug) << __FUNCTION__;  

  Vectors normalizedVectorsInVertices;

  for (auto vector : vectorsInVertices)
  {
    normalizedVectorsInVertices.push_back(vector.Normalize());
  }

  return normalizedVectorsInVertices;
}

}

void Object3D::CreateNormalVectors()
{
  FaceNumbersInVertices facesAssignedToVertex = PrepareFacesAssignedToVertices(mVertices, mFaces);
  
  mNormalVectorsInFaces = CalculateNormalVectorToFaces(mVertices, mFaces);

  Vectors vectorsInVertices = CalculateVectorsInVertices(facesAssignedToVertex, mNormalVectorsInFaces);

  mNormalVectorsInVertices = NormalizeVectorsInVertices(vectorsInVertices);
}
    
void Object3D::LogVertices() const
{
  BOOST_LOG_TRIVIAL(debug) << __FUNCTION__;  
  for (auto v : mVertices)
  {
    BOOST_LOG_TRIVIAL(debug) << v.ToString();
  }
}

void Object3D::LogFaces() const
{
  BOOST_LOG_TRIVIAL(debug) << __FUNCTION__;  
  for (auto face : mFaces)
  {
    BOOST_LOG_TRIVIAL(debug) << face.ToString();
  }
}

std::pair<Face, Vertices> Object3D::Merge(const Vertices& objectVertices,
                                          const Face& face,
                                          const Vertices& vertices)
{
  BOOST_LOG_TRIVIAL(debug) << __FUNCTION__;

  Face resultFace;
  Vertices resultVertices = objectVertices;
  
  for (size_t i = 0; i < face.size(); ++i)
    {
      auto vertexNr = face[i];
      Vertex vertex = vertices[vertexNr];

      int foundNr = 0;

      auto found = std::find_if(resultVertices.begin(), resultVertices.end(), [&](const Vertex& v){
        const short vertexRange = 0;

        if ((vertex.mX >= v.mX - vertexRange && vertex.mX <= v.mX + vertexRange)
            && (vertex.mY >= v.mY - vertexRange && vertex.mY <= v.mY + vertexRange)
            && (vertex.mZ >= v.mZ - vertexRange && vertex.mZ <= v.mZ + vertexRange))
          {
            return true;
          }
        
        ++foundNr;
        return false;
      });

      if (found != resultVertices.end())
        {
          resultFace.push_back(foundNr);
        }
      else
        {
          const short nr = resultVertices.size();
          
          resultFace.push_back(nr);
          resultVertices.push_back(vertex);
        }
    }
  
  return std::make_pair(resultFace, resultVertices);
}
