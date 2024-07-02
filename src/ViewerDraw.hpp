#pragma once

struct SDL_Color;
struct SDL_Vertex;
struct SDL_Texture;

#include <functional>

#include "Types.hpp"
#include "Vertices.hpp"
#include "Faces.hpp"

using RenderFunction = std::function<void(
                                       int,
                                       const std::vector<SDL_Vertex> &,
                                       SDL_Texture *texture)
                                     >;

void DrawFlatShadedFaces(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInFaces,
  RenderFunction render
  );

void DrawGouraudShadedFaces(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInVertices,
  RenderFunction render
  );

void DrawTextureMapping(
  int CenterX, int CenterY,
  const Vertices& vertices2d,
  const Faces& faces,
  SDL_Texture* texture,
  RenderFunction render
  );
