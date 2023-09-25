#include "vertex.hpp"
#include "rotation.hpp"
#include "thorus.hpp"

namespace {

  Face CreateFace(int face1, int face2, int face3, int face4)
  {
    Face face;
    face.push_back(face1);
    face.push_back(face2);
    face.push_back(face3);
    face.push_back(face4);
    return face;
  }
  
  Faces CreateFacesInCircle(int ringIndex,
                            int circleSize,
                            int begin,
                            int count,
                            bool last = false)
  {
    if (begin + count > circleSize)
      {
        return Faces();
      }
    
    Faces faces;

    for (int rowIndex = 0; rowIndex < count; rowIndex++)
      {
        int faceNr1 = 0;
        int faceNr2 = 0;
        int faceNr3 = 0;
        int faceNr4 = 0;

        const int pos = ringIndex * circleSize + begin;
        const int next = last ? begin : (pos + circleSize);
        
        if ((begin + count) == circleSize &&
            (begin + rowIndex) == (circleSize - 1))
          {
            faceNr1 = pos - begin;
            faceNr2 = pos + rowIndex;
            faceNr3 = next + rowIndex;
            faceNr4 = next - begin;
          }
        else
          {
            faceNr1 = pos + rowIndex + 1;
            faceNr2 = pos + rowIndex;
            faceNr3 = next + rowIndex;
            faceNr4 = next + rowIndex + 1;
          }

        faces.push_back(CreateFace(faceNr1, faceNr2, faceNr3, faceNr4));
      }

    return faces;
  }
  
  Vertices CreateCircleVertices(int size)
  {
    Vertex vertex(0, 0, 30);
    Rotation rotate;

    const int degStep = (360 << 8) / size;
    int degree = 0;

    Vertices circle;

    // obrót w X punktu aby utworzyć "okrąg"
    for (int i = 0; i < size; i++)
      {
        const int d = (degree >> 8);
        circle.push_back(rotate.rotateX(vertex, d));
        degree += degStep;
      }

    return circle;
  }

  Vertices MoveVertices(Vertices vertices, Vertex moveVector)
  {
    for (auto& v : vertices)
      {
        v.x += moveVector.x;
        v.y += moveVector.y;
        v.z += moveVector.z;
      }
    return vertices;
  }


  Vertices CreateRingVertices(Vertices circle, int size)
  {
    Vertices vertices;
    Rotation rotate;
    
    const int degStep = (360 << 8) / size;
    int degree = 0;
  
    // obrót w Z okręgu tworzy torus
    for (int i = 0; i < size; i++)
    {
      for (const auto& v : circle)
        {
          const int d = (degree >> 8);
          vertices.push_back(rotate.rotateZ(v, d));
        }
      degree += degStep;
    }

    return vertices;
  }

  Faces CreateInternalFacesInRing(int circleSize, int ringSize)
  {
    Faces facesInRing;
    
    for (int ringIndex = 0; ringIndex < ringSize; ++ringIndex)
      {
        Faces faces;
        
        const auto isLast = (ringIndex == (ringSize - 1));
        
        if (isLast)
          {
            faces = CreateFacesInCircle(ringIndex, circleSize, 0, circleSize/2, true);
          }
        else
          {
            faces = CreateFacesInCircle(ringIndex, circleSize, 0, circleSize/2);
          }
        
        for (auto face : faces)
          {
            facesInRing.push_back(face);
          }
      }
    
    return facesInRing;
  }


  Faces CreateExternalFacesInRing(int circleSize, int ringSize)
  {
    Faces facesInRing;
    
    for (int ringIndex = 0; ringIndex < ringSize; ++ringIndex)
      {
        Faces faces;
        
        const auto isLast = (ringIndex == (ringSize - 1));
        
        if (isLast)
          {
            faces = CreateFacesInCircle(ringIndex, circleSize, circleSize/2, circleSize/2, true);
          }
        else
          {
            faces = CreateFacesInCircle(ringIndex, circleSize, circleSize/2, circleSize/2);
          }
        
        for (auto face : faces)
          {
            facesInRing.push_back(face);
          }
      }
    
    return facesInRing;
  }
  
}


void Thorus::Generate()
{
  Vertices circle = CreateCircleVertices(mCircleSize);
  circle = MoveVertices(circle, Vertex(0,50,0));
  mVertices = CreateRingVertices(circle, mRingSize);

  /// --- Faces ---

  auto internalFaces = CreateInternalFacesInRing(mCircleSize, mRingSize);
    
  for (auto face : internalFaces)
    {
      mFaces.push_back(face);
    }

  auto externalFaces = CreateExternalFacesInRing(mCircleSize, mRingSize);
    
  for (auto face : externalFaces)
    {
      mFaces.push_back(face);
    }

}
