#include <iostream>
#include <array>
#include <map>
#include <memory>
#include <algorithm>
#include <any>
#include <stdexcept>
#include <functional>

#include "Types.hpp"
#include "Vertices.hpp"
#include "Object3D.hpp"
#include "Face.hpp"
#include "Rotation.hpp"
#include "AmigaFile.hpp"

#include "ViewerSortingFaces.hpp"
#include "ViewerPerspective.hpp"
#include "ViewerLight.hpp"
#include "ViewerRotate.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std::placeholders;

SDL_Color colors[maxColorNumber];

constexpr int WindowW = 800;
constexpr int WindowH = 800;
constexpr int CenterX = WindowW / 2;
constexpr int CenterY = WindowH / 2;

enum DrawLineMode
{
  DrawLineMode_None                    = 0,
  DrawLineMode_LineVectors             = 0b0000'0001,
  DrawLineMode_NormalVectorsInFaces    = 0b0000'0010,
  DrawLineMode_NormalVectorsInVertices = 0b0000'0100,
};

enum DrawFilledMode {
  DrawFilledMode_None                    = 0,
  DrawFilledMode_FlatShading             = 0b0000'0001,
  DrawFilledMode_GouraudShading          = 0b0000'0010,
  DrawFilledMode_TextureMapping          = 0b0000'0100,
};

const char *help = "press h for help";
const char *helpDetailed =
  "ESC - quit viewer\n"
  "F1-F12 - objects\n"
  "1 - line vectors\n"
  "2 - normals in faces\n"
  "3 - normals in vertices\n"
  "4 - flat shaded\n"
  "5 - gouraud shaded\n"
  "6 - textured\n"
  "space - rotate\n"
  "cursors - modify rotation\n"
  ", - zoom in\n"
  ". - zoom out\n"
  ;


void RenderFace(
  SDL_Renderer* rend,
  int quantityOfVertices,
  const std::vector<SDL_Vertex>& geometryVertices,
  SDL_Texture* texture = nullptr)
{
  switch(quantityOfVertices)
  {
  case 3:
  {
    SDL_RenderGeometry(rend, texture, geometryVertices.data(), geometryVertices.size(), nullptr, 0);
    break;
  }
  case 4:
  {
    const int triangleIndices[] = {0,1,2,3,2,0};
    SDL_RenderGeometry(rend, texture, geometryVertices.data(), geometryVertices.size(), triangleIndices, 6);
    break;
  }
  default:
    throw std::invalid_argument("Face is not handled");
  }
}

void DrawFlatShading(SDL_Renderer* rend,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInFaces
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

    RenderFace(rend, size, geometryVertices);
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
                
      const auto x = vertices2d[face[i]].getX();
      const auto y = vertices2d[face[i]].getY();
      vertex.position.x = x + CenterX;
      vertex.position.y = y + CenterY;
      geometryVertices.push_back(vertex);
    }

    RenderFace(rend, face.size(), geometryVertices);
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
      const auto x = vertices2d[face[i]].getX();
      const auto y = vertices2d[face[i]].getY();
      vertex.position.x = x + CenterX;
      vertex.position.y = y + CenterY;
      vertex.tex_coord.x = textureCoords[i][0];
      vertex.tex_coord.y = textureCoords[i][1];
      vertex.color = SDL_Color{255,255,255,255};
      geometryVertices.push_back(vertex);
    }

    RenderFace(rend, face.size(), geometryVertices, texture);
  }
}


void DrawNormalVectorsInFaces(SDL_Renderer* rend,
  const Vertices& vertices,
  const Vertices& vertices2d,
  const Faces& faces,
  const Vectors& normalVectorsInFaces,
  const std::function<Vertex(const Vertex&)> calcPerspectiveFunction
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
    const auto vBegin = calcPerspectiveFunction(v);
    const auto vEnd = calcPerspectiveFunction(v + normalVectorsInFaces[faceNr].getEnd());
      
    SDL_RenderDrawLine(rend,
      vBegin.getX() + CenterX, vBegin.getY() + CenterY,
      vEnd.getX() + CenterX, vEnd.getY() + CenterY
      );

    ++faceNr;
  }
}

void DrawNormalVectorsInVertices(SDL_Renderer* rend,
  const Vertices& vertices,
  const Vertices& vertices2d,
  const Faces& faces,
  const Vectors& normalVectorsInVertices,
  const std::function<Vector(const Vector&)> calcPerspectiveFunction
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
      const auto vBegin = vertices2d[face[i]];
      const auto vEnd = calcPerspectiveFunction(vertices[face[i]] + normalVectorsInVertices[face[i]].getEnd());
                
      SDL_RenderDrawLine(rend,
        vBegin.getX() + CenterX, vBegin.getY() + CenterY,
        vEnd.getX() + CenterX, vEnd.getY() + CenterY
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
      auto x1 = vertices2d[face[i]].getX();
      auto y1 = vertices2d[face[i]].getY();
            
      int x2 = 0;
      int y2 = 0;
            
      if (i == size-1)
      {  
        x2 = vertices2d[face[0]].getX();
        y2 = vertices2d[face[0]].getY();
      }
      else
      {
        x2 = vertices2d[face[i + 1]].getX();
        y2 = vertices2d[face[i + 1]].getY();
      }
                
      SDL_RenderDrawLine(rend,
        x1 + CenterX, y1 + CenterY,
        x2 + CenterX, y2 + CenterY
        );
    }
  }
}

void LoadObjects(int argc, char* argv[], std::vector<std::shared_ptr<Object3D>>& objects)
{
  AmigaFile file;
  std::string path;

  if (argc > 1)
  {
    path = argv[1];
  }
  
  for (int i = 2; i < argc; i++)
  {
    std::unique_ptr<Object3D> object = std::make_unique<Object3D>("aaaa");
    const char* name = argv[i];
    file.Load(path + "/" +name, *object.get());
    objects.push_back(std::move(object));
  }
}

SDL_Texture*  getMessage(
  SDL_Renderer *renderer,
  int x, int y,
  const char *text,
  TTF_Font* font,
  SDL_Rect* rect)
{
  SDL_Color textColor = {255, 255, 255, 0};
  SDL_Surface* surface = TTF_RenderText_Solid_Wrapped(font, text, textColor, 1000);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  auto text_width = surface->w;
  auto text_height = surface->h;
  SDL_FreeSurface(surface);
  rect->x = x;
  rect->y = y;
  rect->w = text_width;
  rect->h = text_height;
  return texture;
}


int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    std::cout << "No object files provided\n"
              << "Command line:\n"
              << "  viewer path file..." << std::endl;
    return 0;
  }
  
  std::vector<std::shared_ptr<Object3D>> objects;
  LoadObjects(argc, argv, objects);

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }
  
  TTF_Init();
  TTF_Font *font = TTF_OpenFont("Kode-Regular.ttf", 20);
  if (font == NULL) {
    fprintf(stderr, "error: font not found\n");
    exit(EXIT_FAILURE);
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

  SDL_Rect helpRect;
  SDL_Rect helpDetailsRect;
  SDL_Texture *helpTexture = getMessage(rend, 0, 0, help, font, &helpRect);
  SDL_Texture *helpDetailsTexture = getMessage(rend, 0, 0, helpDetailed, font, &helpDetailsRect);
  
  SDL_Surface* surface = IMG_Load("wood.png");
  if (surface == 0)
  {
    std::cerr << "No image file" << std::endl;
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
  int zoom = 400;
  
  bool help = false;
  
  unsigned short lineMode = 0;
  unsigned short filledMode = 0;
  
  auto SwitchDrawLineMode = [&](DrawLineMode mode){
    lineMode = (lineMode & mode) ? (lineMode ^ mode) : (lineMode | mode);
  };

  auto SwitchDrawFilledMode = [&](DrawFilledMode mode){
    filledMode = 0;
    filledMode = (filledMode & mode) ? (filledMode ^ mode) : (filledMode | mode);
  };
  
  SwitchDrawLineMode(DrawLineMode_LineVectors);

  PrepareColors(colors);

  std::weak_ptr<Object3D> selectedObject;
  
  auto SelectObject = [&](unsigned int nr) {
    if (nr < objects.size())
    {
      selectedObject = std::weak_ptr<Object3D>(objects[nr]);
    }
  };

  SelectObject(0);
  
  std::map<int, std::function<void()>> keyActions{
    {SDL_SCANCODE_COMMA, [&](){ zoom -= 10; }},
    {SDL_SCANCODE_PERIOD, [&](){ zoom += 10; }},
    {SDL_SCANCODE_ESCAPE, [&](){ close = 1; }},
    {SDL_SCANCODE_H, [&](){ help = !help; }},
    {SDL_SCANCODE_1, [&](){ SwitchDrawLineMode(DrawLineMode_LineVectors); }},
    {SDL_SCANCODE_2, [&](){ SwitchDrawLineMode(DrawLineMode_NormalVectorsInFaces); }},
    {SDL_SCANCODE_3, [&](){ SwitchDrawLineMode(DrawLineMode_NormalVectorsInVertices); }},
    {SDL_SCANCODE_4, [&](){ SwitchDrawFilledMode(DrawFilledMode_FlatShading); }},
    {SDL_SCANCODE_5, [&](){ SwitchDrawFilledMode(DrawFilledMode_GouraudShading); }},
    {SDL_SCANCODE_6, [&](){ SwitchDrawFilledMode(DrawFilledMode_TextureMapping); }},
    {SDL_SCANCODE_UP, [&](){ degx += 1; }},
    {SDL_SCANCODE_DOWN, [&](){ degx -= 1; }},
    {SDL_SCANCODE_LEFT, [&](){ degy += 1; }},
    {SDL_SCANCODE_RIGHT, [&](){ degy -= 1; }},
    {SDL_SCANCODE_M, [&](){
      if (light < maxLightValue)
      {
        light += 1;
      }
    }},
    {SDL_SCANCODE_N, [&]() {
      if (light > -maxLightValue)
      {
        light -= 1;
      }      
    }},
    {SDL_SCANCODE_SPACE, [&]() {
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
    }},
    {SDL_SCANCODE_F1, [&](){ SelectObject(0); }},
    {SDL_SCANCODE_F2, [&](){ SelectObject(1); }},
    {SDL_SCANCODE_F3, [&](){ SelectObject(2); }},
    {SDL_SCANCODE_F4, [&](){ SelectObject(3); }},
    {SDL_SCANCODE_F5, [&](){ SelectObject(4); }},
    {SDL_SCANCODE_F6, [&](){ SelectObject(5); }},
    {SDL_SCANCODE_F7, [&](){ SelectObject(6); }},
    {SDL_SCANCODE_F8, [&](){ SelectObject(7); }},
    {SDL_SCANCODE_F9, [&](){ SelectObject(8); }},
    {SDL_SCANCODE_F10, [&](){ SelectObject(9); }},
    {SDL_SCANCODE_F11, [&](){ SelectObject(10); }},
    {SDL_SCANCODE_F12, [&](){ SelectObject(11); }},
  };

  // animation loop
  while (!close) {
    SDL_Event event;

   
    // Events management
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        
      case SDL_QUIT:
      {
        // handling of close button
        close = 1;
        break;
      }
        
      case SDL_KEYDOWN:
      {
        auto action = keyActions.find(event.key.keysym.scancode);
        if (action != keyActions.end())
        {
          action->second();
        }
        break;
      }
        
      default:
        break;
        
      }
    }
    
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend, 0xFF, 0, 0, 0xFF);

    auto object = selectedObject.lock();
    
    if (!object)
    {
      continue;
    }

    Vertices vertices;
    Vectors normalVectorsInFaces;
    Vectors normalVectorsInVertices;
    
    RotateObject(
      degx, degy, degz,
      object->mVertices,
      object->mNormalVectorsInFaces,
      object->mNormalVectorsInVertices,
      vertices,
      normalVectorsInFaces,
      normalVectorsInVertices);

    std::vector<int> colorNumbersInFaces;
    std::vector<int> colorNumbersInVertices;
    
    CalculateLight(
      light,
      normalVectorsInFaces,
      normalVectorsInVertices,
      colorNumbersInFaces,
      colorNumbersInVertices);

    Vertices vertices2d = CalculatePerspective(vertices, zoom);

    if (filledMode & DrawFilledMode_FlatShading)
    {
      DrawFlatShading(rend,
        vertices2d,
        object->mFaces,
        colorNumbersInFaces
        );
    }

    if (filledMode & DrawFilledMode_GouraudShading)
    {
      DrawGouraudShading(rend,
        vertices2d,
        object->mFaces,
        colorNumbersInVertices
        );
    }

    if (filledMode & DrawFilledMode_TextureMapping)
    {
      DrawTextureMapping(rend,
        vertices2d,
        object->mFaces,
        texture);
    }
        
    if (lineMode & DrawLineMode_NormalVectorsInFaces)
    {
      DrawNormalVectorsInFaces(rend,
        vertices,
        vertices2d,
        object->mFaces,
        normalVectorsInFaces,
        std::bind(CalculatePerspective<Vertex>, _1, zoom));
    }

    if (lineMode & DrawLineMode_NormalVectorsInVertices)
    {
      DrawNormalVectorsInVertices(rend,
        vertices,
        vertices2d,
        object->mFaces,
        normalVectorsInVertices,
        std::bind(CalculatePerspective<Vector>, _1, zoom));
    }
        
    if (lineMode & DrawLineMode_LineVectors)
    {
      DrawLines(rend, vertices2d, object->mFaces);
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

    auto msgTexture = help ? helpDetailsTexture : helpTexture;
    auto msgRect = help ? &helpDetailsRect : &helpRect;
    SDL_RenderCopy(rend, msgTexture, NULL, msgRect);

    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(rend);

    // calculates to 60 fps
    SDL_Delay(1000 / 60);
  }

  SDL_DestroyTexture(helpTexture);
  SDL_DestroyTexture(helpDetailsTexture);
  TTF_Quit();
    
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
 
