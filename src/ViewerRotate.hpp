#pragma once

#include "Types.hpp"

class Vertices;

void RotateObject(int degx, int degy, int degz,
  const Vertices &vertices,
  const Vectors &normalVectorsInFaces,
  const Vectors &normalVectorsInVertices,
  Vertices &resultVertices,
  Vectors &resultNormalVectorsInFaces,
  Vectors &resultNormalVectorsInVertices);
