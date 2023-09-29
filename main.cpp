#include "face.hpp"
#include "vector3d.hpp"
#include "cube.hpp"
#include "thorus.hpp"
#include "rotation.hpp"
#include "amigafile.hpp"
#include <iostream>
#include <array>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

const int maxColorNumber = 64;
const int maxLightValue = 64;
SDL_Color colors[maxColorNumber];

const int WindowW = 800;
const int WindowH = 800;
const int CenterX = WindowW / 2;
const int CenterY = WindowH / 2;

enum DrawMode
  {
    DrawMode_None = 0,
    DrawMode_LineVectors = 1,
    DrawMode_NormalVectorsInFaces = 1 << 1,
    DrawMode_NormalVectorsInVertices = 1 << 2,
    DrawMode_FlatShading = 1 << 3,
    DrawMode_GouraudShading = 1 << 4,
    DrawMode_TextureMapping = 1 << 5,
  };

void PrepareColors()
{
  for (int i = 0; i < maxColorNumber; ++i)
    {
      const int maxValue = 255;
      unsigned char col = ((-i + maxColorNumber) * maxValue) /  maxColorNumber;
      colors[i] = SDL_Color{col, col, col, maxValue};
    }
}

Vertex CalculatePerspective(const Vertex& v)
{
  auto z = v.z + 400;
  auto x = (v.x << 10) / z;
  auto y = (v.y << 10) / z;
  return Vertex(x, y, 0);
}

void RotateObject(Object3D* object,
                  int degx, int degy, int degz,
                  Vertices& vertices,
                  Vectors& normalVectorsInFaces,
                  Vectors& normalVectorsInVertices)
{
    Rotation rotation;
    for (auto v : object->mVertices)
      {
        const auto v2 = rotation.rotateX(v, degx);
        const auto v3 = rotation.rotateY(v2, degy);
        const auto v4 = rotation.rotateZ(v3, degz);
        vertices.push_back(v4);
      }

    for (auto v : object->mNormalVectorsInFaces)
      {
        const auto v2 = rotation.rotateX(v, degx);
        const auto v3 = rotation.rotateY(v2, degy);
        const auto v4 = rotation.rotateZ(v3, degz);
        normalVectorsInFaces.push_back(Vector3d(v4));
      }

    for (auto v : object->mNormalVectorsInVertices)
      {
        const auto v2 = rotation.rotateX(v, degx);
        const auto v3 = rotation.rotateY(v2, degy);
        const auto v4 = rotation.rotateZ(v3, degz);
        normalVectorsInVertices.push_back(Vector3d(v4));
      }
}

void CalculateLight(int light,
                    const Vectors& normalVectorsInFaces,
                    const Vectors& normalVectorsInVertices,
                    std::vector<int>& colorNumbersInFaces,
                    std::vector<int>& colorNumbersInVertices)
{
  for (auto v : normalVectorsInFaces)
    {
      Vertex lightVector(0,0,light); // wektor światła
      const auto z = (v.z * lightVector.z) + (maxLightValue * maxLightValue);
      const int id = (z * maxColorNumber) / (maxLightValue * 2 * maxLightValue);
      colorNumbersInFaces.push_back(id);
    }
  
  for (auto v : normalVectorsInVertices)
    {
      Vertex lightVector(0,0,light); // wektor światła
      const auto z = (v.z * lightVector.z) + (maxLightValue * maxLightValue);
      const int id = (z * maxColorNumber) / (maxLightValue * 2 * maxLightValue);
      colorNumbersInVertices.push_back(id);
    }
}

void DrawFlatShading(SDL_Renderer* rend,
                     const Vertices& vertices2d,
                     const Faces& faces,
                     const std::vector<int>& colorNumbersInFaces
                     )
{
  unsigned int faceNr = 0;
    
  for (auto face : faces)
    {
      if (!face.IsVisible(vertices2d))
        {
          ++faceNr;
          continue;
        }

      std::vector<SDL_Vertex> geometryVertices;

      SDL_Vertex vertex;
      vertex.tex_coord.x = 0;
      vertex.tex_coord.y = 0;
      vertex.color = colors[colorNumbersInFaces[faceNr]];
        
      for (size_t i = 0; i < face.size(); ++i)
        {
          const auto x = vertices2d[face[i]].x;
          const auto y = vertices2d[face[i]].y;
          vertex.position.x = x + CenterX;
          vertex.position.y = y + CenterY;
          geometryVertices.push_back(vertex);
        }
      
      const int triangleIndices[] = {0,1,2,3,2,0};
      SDL_RenderGeometry(rend, NULL, geometryVertices.data(), geometryVertices.size(), triangleIndices, 6);

      ++faceNr;
    }
}

void DrawGouraudShading(SDL_Renderer* rend,
                        const Vertices& vertices2d,
                        const Faces& faces,
                        const std::vector<int>& colorNumbersInVertices
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
        
      for (size_t i = 0; i < face.size(); ++i)
        {
          vertex.color = colors[colorNumbersInVertices[face[i]]];
                
          const auto x = vertices2d[face[i]].x;
          const auto y = vertices2d[face[i]].y;
          vertex.position.x = x + CenterX;
          vertex.position.y = y + CenterY;
          geometryVertices.push_back(vertex);
        }

      const int triangleIndices[] = {0,1,2,3,2,0};
      SDL_RenderGeometry(rend, NULL, geometryVertices.data(), geometryVertices.size(), triangleIndices, 6);
    }
}

void DrawTextureMapping(SDL_Renderer* rend,
                        const Vertices& vertices2d,
                        const Faces& faces,
                        SDL_Texture* texture)
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
      
      for (size_t i = 0; i < face.size(); ++i)
        {
          SDL_Vertex vertex;
          const auto x = vertices2d[face[i]].x;
          const auto y = vertices2d[face[i]].y;
          vertex.position.x = x + CenterX;
          vertex.position.y = y + CenterY;
          vertex.tex_coord.x = textureCoords[i][0];
          vertex.tex_coord.y = textureCoords[i][1];
          vertex.color = SDL_Color{255,255,255,255};
          geometryVertices.push_back(vertex);
        }

      const int triangleIndices[] = {0,1,2,3,2,0};
      SDL_RenderGeometry(rend, texture, geometryVertices.data(), geometryVertices.size(), triangleIndices, 6);
    }
}


void DrawNormalVectorsInFaces(SDL_Renderer* rend,
                              const Vertices& vertices,
                              const Vertices& vertices2d,
                              const Faces& faces,
                              const Vectors& normalVectorsInFaces
                              )
{
  unsigned int faceNr = 0;
    
  for (auto face : faces)
    {
      if (!face.IsVisible(vertices2d))
        {
          ++faceNr;
          continue;
        }

      const auto v = face.GetCenter(vertices);
      const auto v1 = CalculatePerspective(v);
      const auto v2 = CalculatePerspective(v + normalVectorsInFaces[faceNr]);
      
      SDL_RenderDrawLine(rend,
                         v1.x + CenterX, v1.y + CenterY,
                         v2.x + CenterX, v2.y + CenterY
                         );

      ++faceNr;
    }
}

void DrawNormalVectorsInVertices(SDL_Renderer* rend,
                                 const Vertices& vertices,
                                 const Vertices& vertices2d,
                                 const Faces& faces,
                                 const Vectors& normalVectorsInVertices
                                 )
{
  unsigned int faceNr = 0;
    
  for (auto face : faces)
    {
      if (!face.IsVisible(vertices2d))
        {
          ++faceNr;
          continue;
        }

      const unsigned int size = face.size();
            
      for (unsigned int i = 0; i < size; ++i)
        {
          const auto v1 = vertices2d[face[i]];
          const auto v2 = CalculatePerspective(vertices[face[i]] + normalVectorsInVertices[face[i]]);
                
          SDL_RenderDrawLine(rend,
                             v1.x + CenterX, v1.y + CenterY,
                             v2.x + CenterX, v2.y + CenterY
                             );
        }

      ++faceNr;
    }
}

void DrawLines(SDL_Renderer* rend,
               const Vertices& vertices2d,
               const Faces& faces
               )
{
  for (auto face : faces)
    {
      if (!face.IsVisible(vertices2d))
        {
          continue;
        }

      const unsigned int size = face.size();
            
      for (unsigned int i = 0; i < size; ++i)
        {
          auto x1 = vertices2d[face[i]].x;
          auto y1 = vertices2d[face[i]].y;
            
          int x2 = 0;
          int y2 = 0;
            
          if (i == size-1)
            {  
              x2 = vertices2d[face[0]].x;
              y2 = vertices2d[face[0]].y;
            }
          else
            {
              x2 = vertices2d[face[i + 1]].x;
              y2 = vertices2d[face[i + 1]].y;
            }
                
          SDL_RenderDrawLine(rend,
                             x1 + CenterX, y1 + CenterY,
                             x2 + CenterX, y2 + CenterY
                             );
        }
    }
}


int main(int argc, char* argv[])
{
  std::vector<Object3D*> objects;
  
  objects.push_back(new Cube("cube"));
  
  std::vector<int> thorusVerticesNr{4,6,8};
  for (size_t i = 0; i < thorusVerticesNr.size(); ++i)
    {
      auto n = thorusVerticesNr[i];
      objects.push_back(new Thorus(n,n, ("thorus" + std::to_string(i)).c_str()));
    }

  for(auto obj : objects)
    {
      obj->Generate();
      obj->LogVertices();
      obj->LogFaces();
      obj->CreateNormalVectors();

      AmigaFile file;
      file.Save(*obj);
    }

  
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }
  
  SDL_Window* win = SDL_CreateWindow("3D Objects Generator And Demo",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     WindowW, WindowH, 0);
  
  // triggers the program that controls
  // your graphics hardware and sets flags
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  
  // creates a renderer to render our images
  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
  SDL_Surface* surface = IMG_Load("wood.png");
  if (surface == 0)
    {
      std::cout << "No image file" << "\n";
      return 1;
    }
 
  SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
  SDL_FreeSurface(surface);
 
  // controls animation loop
  int close = 0;
  
  int degx = 0;
  int degy = 0;
  int degz = 0;

  int speedx = 0;
  int speedy = 0;
  int speedz = 0;
  
  int light = maxLightValue;
  
  unsigned short drawMode = 0;
  auto SwitchDrawMode = [&](DrawMode mode){
    drawMode = (drawMode & mode) ? (drawMode ^ mode) : (drawMode | mode);
  };

  SwitchDrawMode(DrawMode_LineVectors);
  PrepareColors();
  Object3D* object = objects[0];
  
  // animation loop
  while (!close) {
    SDL_Event event;

   
    // Events management
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        
      case SDL_QUIT:
        // handling of close button
        close = 1;
        break;
        
      case SDL_KEYDOWN:
        // keyboard API for key pressed
        switch (event.key.keysym.scancode) {

        case SDL_SCANCODE_ESCAPE:
          close = 1;
          break;

        case SDL_SCANCODE_1:
          SwitchDrawMode(DrawMode_LineVectors);
          break;

        case SDL_SCANCODE_2:
          SwitchDrawMode(DrawMode_NormalVectorsInFaces);
          break;

        case SDL_SCANCODE_3:
          SwitchDrawMode(DrawMode_NormalVectorsInVertices);
          break;

        case SDL_SCANCODE_4:
          SwitchDrawMode(DrawMode_FlatShading);
          break;

        case SDL_SCANCODE_5:
          SwitchDrawMode(DrawMode_GouraudShading);
          break;

        case SDL_SCANCODE_6:
          SwitchDrawMode(DrawMode_TextureMapping);
          break;
          
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
          degx += 1;
          break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
          degy += 1;
          break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
          degx -= 1;
          break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
          degy -= 1;
          break;

        case SDL_SCANCODE_M:
          if (light < maxLightValue)
            {
              light += 1;
            }
          break;

        case SDL_SCANCODE_N:
          if (light > -maxLightValue)
            {
              light -= 1;
            }
          break;
          
        case SDL_SCANCODE_SPACE:
          if (speedx == 0)
            {
              speedx = 1;
              speedy = 1;
              speedz = 1;
            }
          else
            {
              speedx = 0;
              speedy = 0;
              speedz = 0;
            }
          break;

        case SDL_SCANCODE_F1:
        case SDL_SCANCODE_F2:
        case SDL_SCANCODE_F3:
        case SDL_SCANCODE_F4:
        case SDL_SCANCODE_F5:
        case SDL_SCANCODE_F6:
        case SDL_SCANCODE_F7:
        case SDL_SCANCODE_F8:
        case SDL_SCANCODE_F9:
        case SDL_SCANCODE_F10:
        case SDL_SCANCODE_F11:
        case SDL_SCANCODE_F12:
          {
            unsigned int nr = event.key.keysym.scancode - SDL_SCANCODE_F1;
            if (nr < objects.size())
            {
              object = objects[nr];
            }
            break;
          }
          break;
        default:
          break;
        }
      }
    }
    
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    SDL_RenderClear(rend);

    //    SDL_RenderCopy(rend, tex, &dest, NULL);
    
    SDL_SetRenderDrawColor(rend, 0xFF, 0, 0, 0xFF);
    
    if (object)
      {
        Vertices vertices;
        Vectors normalVectorsInFaces;
        Vectors normalVectorsInVertices;
        RotateObject(object, degx, degy, degz,
                     vertices,
                     normalVectorsInFaces,
                     normalVectorsInVertices);

        std::vector<int> colorNumbersInFaces;
        std::vector<int> colorNumbersInVertices;
        CalculateLight(light,
                       normalVectorsInFaces,
                       normalVectorsInVertices,
                       colorNumbersInFaces,
                       colorNumbersInVertices);

        Vertices vertices2d;
        for (auto v : vertices)
          {
            const auto v2d = CalculatePerspective(v);
            vertices2d.push_back(v2d);
          }

        if (drawMode & DrawMode_FlatShading)
          {
            DrawFlatShading(rend,
                            vertices2d,
                            object->mFaces,
                            colorNumbersInFaces
                            );
          }

        if (drawMode & DrawMode_GouraudShading)
          {
            DrawGouraudShading(rend,
                               vertices2d,
                               object->mFaces,
                               colorNumbersInVertices
                               );
          }

        if (drawMode & DrawMode_TextureMapping)
          {
            DrawTextureMapping(rend,
                               vertices2d,
                               object->mFaces,
                               texture);
          }
        
        if (drawMode & DrawMode_NormalVectorsInFaces)
          {
            DrawNormalVectorsInFaces(rend,
                                     vertices,
                                     vertices2d,
                                     object->mFaces,
                                     normalVectorsInFaces);
          }

        if (drawMode & DrawMode_NormalVectorsInVertices)
          {
            DrawNormalVectorsInVertices(rend,
                                        vertices,
                                        vertices2d,
                                        object->mFaces,
                                        normalVectorsInVertices);
          }
        
        if (drawMode & DrawMode_LineVectors)
          {
            DrawLines(rend, vertices2d, object->mFaces);
          }
      }

    degx += speedx;
    degy += speedy;
    degz += speedz;

    if (degx > 360)
      {
        degx = 0;
      }
    if (degy > 360)
      {
        degy = 0;
      }
    if (degz > 360)
      {
        degz = 0;
      }
        
    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(rend);
    
    // calculates to 60 fps
    SDL_Delay(1000 / 60);
  }
 
  SDL_DestroyRenderer(rend);
  
  SDL_DestroyWindow(win);
  
  SDL_Quit();

  return 0;
}
 
