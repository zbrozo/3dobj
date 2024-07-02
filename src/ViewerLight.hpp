#pragma once

#include "Types.hpp"

constexpr int maxColorNumber = 64;
constexpr int maxLightValue = 64;

struct SDL_Color;

void PrepareColors(SDL_Color* colors);

void CalculateLight(
  int light,
  const Vectors& normalVectorsInFaces,
  const Vectors& normalVectorsInVertices,
  std::vector<int>& colorNumbersInFaces,
  std::vector<int>& colorNumbersInVertices);
