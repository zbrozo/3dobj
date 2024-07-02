
#include <vector>
#include "Types.hpp"

#include "ViewerLight.hpp"

#include <SDL2/SDL.h>

void PrepareColors(SDL_Color* colors)
{
  for (int i = 0; i < maxColorNumber; ++i)
  {
    const int maxValue = 255;
    unsigned char col = ((-i + maxColorNumber) * maxValue) /  maxColorNumber;
    colors[i] = SDL_Color{col, col, col, maxValue};
  }
}

void CalculateLight(
  int light,
  const Vectors& normalVectorsInFaces,
  const Vectors& normalVectorsInVertices,
  std::vector<int>& colorNumbersInFaces,
  std::vector<int>& colorNumbersInVertices)
{
  auto calcColorNumber = [light](const Vector& v){
    Vertex lightVector(0,0,light);
    const int z = (v.getZ() * lightVector.getZ()) + (maxLightValue * maxLightValue);
    const int id = (z * maxColorNumber) / (maxLightValue * 2 * maxLightValue);
    return id;
  };
  
  for (auto v : normalVectorsInFaces)
  {
    colorNumbersInFaces.push_back(calcColorNumber(v));
  }
  
  for (auto v : normalVectorsInVertices)
  {
    colorNumbersInVertices.push_back(calcColorNumber(v));
  }
}
