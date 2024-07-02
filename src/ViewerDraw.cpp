#include "Types.hpp"
#include "Vertices.hpp"
#include "Faces.hpp"

#include "ViewerSortingFaces.hpp"
#include "ViewerDraw.hpp"

#include <SDL2/SDL.h>
#include <functional>

void DrawFlatShadedFaces(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInFaces,
  RenderFunction render
  )
{
  const auto sortedFaces = SortFaceNumbers(vertices2d, faces);
  
  for (const auto& faceNr : sortedFaces)
  {
    std::vector<SDL_Vertex> geometryVertices;

    SDL_Vertex vertex;
    vertex.tex_coord.x = 0;
    vertex.tex_coord.y = 0;
    vertex.color = colors[colorNumbersInFaces[faceNr]];

    const auto& face = faces[faceNr];
    const size_t size = face.size();
    
    for (size_t i = 0; i < size; ++i)
    {
      const auto x = vertices2d[face[i]].getX();
      const auto y = vertices2d[face[i]].getY();
      vertex.position.x = x + CenterX;
      vertex.position.y = y + CenterY;
      geometryVertices.push_back(vertex);
    }

    render(size, geometryVertices, nullptr);
  }
}

void DrawGouraudShadedFaces(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInVertices,
  RenderFunction render
  )
{
  for (auto face : faces)
  {
    if (!face.IsVisible(vertices2d))
    {
      continue;
    }

    std::vector<SDL_Vertex> geometryVertices;

    SDL_Vertex vertex;
    vertex.tex_coord.x = 0;
    vertex.tex_coord.y = 0;

    const size_t size = face.size();

    for (size_t i = 0; i < size; ++i)
    {
      vertex.color = colors[colorNumbersInVertices[face[i]]];
                
      const auto x = vertices2d[face[i]].getX();
      const auto y = vertices2d[face[i]].getY();
      vertex.position.x = x + CenterX;
      vertex.position.y = y + CenterY;
      geometryVertices.push_back(vertex);
    }

    render(size, geometryVertices, nullptr);
  }
}

void DrawTextureMapping(
  int CenterX, int CenterY,
  const Vertices& vertices2d,
  const Faces& faces,
  SDL_Texture* texture,
  RenderFunction render
  )
{
  for (auto face : faces)
  {
    if (!face.IsVisible(vertices2d))
    {
      continue;
    }

    std::vector<SDL_Vertex> geometryVertices;

    float textureCoords[][2] = {
      {0.0f, 0.0f},
      {0.0f,1.0f},
      {1.0f, 1.0f},
      {1.0f, 0.0f}};

    const size_t size = face.size();
    
    for (size_t i = 0; i < size; ++i)
    {
      SDL_Vertex vertex;
      const auto x = vertices2d[face[i]].getX();
      const auto y = vertices2d[face[i]].getY();
      vertex.position.x = x + CenterX;
      vertex.position.y = y + CenterY;
      vertex.tex_coord.x = textureCoords[i][0];
      vertex.tex_coord.y = textureCoords[i][1];
      vertex.color = SDL_Color{255,255,255,255};
      geometryVertices.push_back(vertex);
    }

    render(size, geometryVertices, texture);
  }
}
