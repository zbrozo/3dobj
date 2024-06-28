#include "Types.hpp"
#include "Rotation.hpp"
#include "Thorus.hpp"
#include <algorithm>
#include <exception>
#include <stdexcept>

#define PI 3.14159265
#define radian (PI / 180.0)

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

Vertices Thorus::CreateCircleVertices()
{
  Vertex vertex(0, 0, mCircleRadius);
  VertexRotation rotation;
  
  const int degStep = (360 << 8) / mCircleAmount;
  int degree = 0;

  Vertices circle;

  // obrót w X punktu aby utworzyć "okrąg"
  for (int i = 0; i < mCircleAmount; i++)
  {
    const int d = (degree >> 8);
    circle.push_back(rotation.rotateX(vertex, d));
    degree += degStep;
  }
  
  return circle;
}

Vertices Thorus::CreateRingVertices(Vertices circle)
{
  Vertices vertices;
  VertexRotation rotation;
    
  const int degStep = (360 << 8) / mRingAmount;
  int degree = 0;
  
  // obrót w Z okręgu tworzy torus
  for (int i = 0; i < mRingAmount; i++)
  {
    const auto modifiedCircle = ApplySinusToCircle(circle, i);
      
    for (const auto& v : modifiedCircle)
    {
      const int d = (degree >> 8);
      vertices.push_back(rotation.rotateZ(v, d));
    }
    degree += degStep;
  }

  return vertices;
}

Vertices Thorus::ApplySinusToCircle(const Vertices& vertices, int index)
{
  Vertices resultVertices;

  auto calcTranslation = [&](auto step, int amp){
    const auto translation =  index * step * 360 / mCircleAmount;
    return sin(translation * radian) * amp;
  };
  
  const auto translationX = calcTranslation(mCircleSinusStepX, mCircleSinusAmpX);
  const auto translationY = calcTranslation(mCircleSinusStepY, mCircleSinusAmpY);
  const auto translationZ = calcTranslation(mCircleSinusStepZ, mCircleSinusAmpZ);

  for (auto& v : vertices)
  {
    resultVertices.push_back(Vertex(
        v.getX() + translationX,
        v.getY() + translationY,
        v.getZ() + translationZ)
      );
  }

  return resultVertices;
}

Vertices Thorus::ApplySinusToRing(const Vertices& vertices)
{
  Vertices resultVertices;
  
  double addX = 0;
  double addY = 0;
  double addZ = 0;

  int i = 0;
  for (auto& v : vertices)
  {
    auto calcTranslation = [&](int add, int amp){
      const auto deg = add * 360 / mCircleAmount;
      return sin(deg * radian) * amp;
    };
    
    const auto translationX = calcTranslation(addX, mRingSinusAmpX);
    const auto translationY = calcTranslation(addY, mRingSinusAmpY);
    const auto translationZ = calcTranslation(addZ, mRingSinusAmpZ);

    resultVertices.push_back(Vertex(
        v.getX() + translationX,
        v.getY() + translationY,
        v.getZ() + translationZ)
      );

    ++i;
    
    if (i == mCircleAmount)
    {
      addX += mRingSinusStepX;
      addY += mRingSinusStepY;
      addZ += mRingSinusStepZ;
      i = 0;
    }
  }

  return resultVertices;
}

Thorus::Thorus(
  const char* name,
  std::optional<int> circleAmount,
  std::optional<int> ringAmount,
  std::optional<int> circleRadius,
  std::optional<int> circleOffset,
  std::optional<int> circleSinusStepX,
  std::optional<int> circleSinusAmpX,
  std::optional<int> circleSinusStepY,
  std::optional<int> circleSinusAmpY,
  std::optional<int> circleSinusStepZ,
  std::optional<int> circleSinusAmpZ,
  std::optional<int> ringSinusStepX,
  std::optional<int> ringSinusAmpX,
  std::optional<int> ringSinusStepY,
  std::optional<int> ringSinusAmpY,
  std::optional<int> ringSinusStepZ,
  std::optional<int> ringSinusAmpZ  
  ) :
  Object3D(name)
{
  if (circleAmount.has_value())
  {
    if (circleAmount.value() < 3)
    {
      throw std::out_of_range("Too less points declared");
    }
    mCircleAmount = circleAmount.value();
  }
  if (ringAmount.has_value())
  {
    if (ringAmount.value() < 3)
    {
      throw std::out_of_range("Too less points declared");
    }
    mRingAmount = ringAmount.value();
  }
  if (circleRadius.has_value())
  {
    mCircleRadius = circleRadius.value();
  }
  if (circleOffset.has_value())
  {
    mCircleOffset = circleOffset.value();
  }

  if (circleSinusStepX.has_value())
  {
    mCircleSinusStepX = circleSinusStepX.value();
  }
  if (circleSinusStepY.has_value())
  {
    mCircleSinusStepY = circleSinusStepY.value();
  }
  if (circleSinusStepZ.has_value())
  {
    mCircleSinusStepZ = circleSinusStepZ.value();
  }

  if (circleSinusAmpX.has_value())
  {
    mCircleSinusAmpX = circleSinusAmpX.value();
  }
  if (circleSinusAmpY.has_value())
  {
    mCircleSinusAmpY = circleSinusAmpY.value();
  }
  if (circleSinusAmpZ.has_value())
  {
    mCircleSinusAmpZ = circleSinusAmpZ.value();
  }

  if (ringSinusStepX.has_value())
  {
    mRingSinusStepX = ringSinusStepX.value();
  }
  if (ringSinusStepY.has_value())
  {
    mRingSinusStepY = ringSinusStepY.value();
  }
  if (ringSinusStepZ.has_value())
  {
    mRingSinusStepZ = ringSinusStepZ.value();
  }

  if (ringSinusAmpX.has_value())
  {
    mRingSinusAmpX = ringSinusAmpX.value();
  }
  if (ringSinusAmpY.has_value())
  {
    mRingSinusAmpY = ringSinusAmpY.value();
  }
  if (ringSinusAmpZ.has_value())
  {
    mRingSinusAmpZ = ringSinusAmpZ.value();
  }
}

void Thorus::Generate()
{
  Vertices circle { CreateCircleVertices() };

  std::transform(circle.cbegin(), circle.cend(), circle.begin(),
    [&](const Vertex& vertex ){ return vertex + Vertex(0, mCircleOffset, 0); });
  
  mVertices = ApplySinusToRing(CreateRingVertices(circle));

  /// --- Faces ---

  auto internalFaces = CreateInternalFacesInRing(mCircleAmount, mRingAmount);
    
  for (auto face : internalFaces)
  {
    mFaces.push_back(face);
  }

  auto externalFaces = CreateExternalFacesInRing(mCircleAmount, mRingAmount);
    
  for (auto face : externalFaces)
  {
    mFaces.push_back(face);
  }
}
