#include "cube.hpp"
#include "thorus.hpp"
#include "rotation.hpp"
#include <iostream>

#include <SDL2/SDL.h>
//#include <SDL3/SDL_image.h>
#include <SDL2/SDL_timer.h>

int main(int argc, char* argv[])
{
  //Cube cube;
  //cube.Generate();
  //cube.LogVertices();
  //cube.LogFaces();
  //  cube.CreateNormalVectors();
  //  cube.SaveToFile();
  
	Thorus thorus(18,18);
	thorus.Generate();
  thorus.LogVertices();
  thorus.LogFaces();
	thorus.CreateNormalVectors();
  //thorus.SaveToFile();
  
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }
  
  SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     800, 800, 0);
  
  // triggers the program that controls
  // your graphics hardware and sets flags
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  
  // creates a renderer to render our images
  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
  // creates a surface to load an image into the main memory
  //  SDL_Surface* surface;
 
  // please provide a path for your image
  //surface = IMG_Load("path");
 
  // loads image to our graphics hardware memory.
  //SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
 
  // clears main-memory
  //SDL_FreeSurface(surface);
 
  // let us control our image position
  // so that we can move it with our keyboard.
  SDL_Rect dest;
  
  // connects our texture with dest to control position
  //SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
  
  // adjust height and width of our image box.
  dest.w /= 6;
  dest.h /= 6;
  
  // sets initial x-position of object
  dest.x = (1000 - dest.w) / 2;
  
  // sets initial y-position of object
  dest.y = (1000 - dest.h) / 2;
  
  // controls animation loop
  int close = 0;
  
  int degx = 0;
  int degy = 0;
  int degz = 0;

  int speedx = 0;
  int speedy = 0;
  int speedz = 0;
  
  int centerx = 400;
  int centery = 400;

  bool drawLightShadedFaces = false;
  bool drawLines = false;
  
  const int maxColorNumber = 64;
  SDL_Color colors[maxColorNumber];

  for (int i = 0; i < maxColorNumber; ++i)
    {
      const int maxValue = 255;
      unsigned char col = ((-i + maxColorNumber) * maxValue) /  maxColorNumber;
      colors[i] = SDL_Color{col, col, col, maxValue};
    }
  
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
          drawLines = !drawLines;
          break;

        case SDL_SCANCODE_2:
          drawLightShadedFaces = !drawLightShadedFaces;
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


        default:
          break;
                }
      }
    }
    
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    SDL_RenderClear(rend);

    const Object3D& object = thorus;
    
    Rotation rotation;
    Vertices vertices;
    for (auto v : object.vertices)
      {
        const auto v2 = rotation.rotateX(v, degx);
        const auto v3 = rotation.rotateY(v2, degy);
        const auto v4 = rotation.rotateZ(v3, degz);
        vertices.push_back(v4);
      }

    Vertices normalVectorsInFaces;
    for (auto v : object.normalVectorsInFaces)
      {
        const auto v2 = rotation.rotateX(v, degx);
        const auto v3 = rotation.rotateY(v2, degy);
        const auto v4 = rotation.rotateZ(v3, degz);
        normalVectorsInFaces.push_back(v4);
      }

    // światło
    std::vector<int> colorNumbersInFaces;
    for (auto v : normalVectorsInFaces)
      {
        const int maxValue = 60;
        Vertex lightVector(0,0,maxValue);
        const auto z = (v.z * lightVector.z) + (maxValue*maxValue);
        const int id = (z * maxColorNumber) / (maxValue*2*maxValue);
        colorNumbersInFaces.push_back(id);
      }
    
    // perspektywa
    Vertices vertices2d;
    for (auto v : vertices)
      {
        auto z = v.z + 300;
        auto x = (v.x << 10) / z;
        auto y = (v.y << 10) / z;
        vertices2d.push_back(Vertex(x,y,0));
      }
    
    SDL_SetRenderDrawColor(rend, 0xFF, 0, 0, 0xFF);

    int faceNr = 0;
    for (auto face : object.faces)
      {
        // VISIBILITY

        auto xlen = vertices2d[face[1]].x - vertices2d[face[0]].x;
        auto ylen = vertices2d[face[2]].y - vertices2d[face[1]].y;

        auto x2len = vertices2d[face[2]].x - vertices2d[face[1]].x;
        auto y2len = vertices2d[face[1]].y - vertices2d[face[0]].y;

        auto visible = xlen * ylen - x2len * y2len; // wektor Z

        if (visible >= 0)
          {
            ++faceNr;
            continue;
          }

        // DRAW
       
        if (drawLightShadedFaces)
          {
            std::vector<SDL_Vertex> geometryVertices;

            SDL_Vertex vertex;
            vertex.tex_coord.x = 0;
            vertex.tex_coord.y = 0;
            vertex.color = colors[colorNumbersInFaces[faceNr]];
        
            for (unsigned int i = 0; i < face.size(); ++i)
              {
                const auto x = vertices2d[face[i]].x;
                const auto y = vertices2d[face[i]].y;
                vertex.position.x = x + centerx;
                vertex.position.y = y + centery;
                geometryVertices.push_back(vertex);
              }

            const int triangleIndices[] = {0,1,2,3,2,0};
            SDL_RenderGeometry(rend, NULL, geometryVertices.data(), geometryVertices.size(), triangleIndices, 6);
          }

        if (drawLines)
          {
            for (int i = 0; i < 4; ++i)
              {
                auto x1 = vertices2d[face[i]].x;
                auto y1 = vertices2d[face[i]].y;
            
                int x2 = 0;
                int y2 = 0;
            
                if (i == 3)
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
                                   x1 + centerx, y1 + centery,
                                   x2 + centerx, y2 + centery
                                   );
              }
          }


        
        ++faceNr;
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
 
    // destroy texture
  //    SDL_DestroyTexture(tex);
 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
  

  return 0;
}
 
