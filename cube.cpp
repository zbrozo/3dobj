#include "cube.hpp"

void Cube::Generate()
{
  const short value = 50;
  const int count = 4;

  short coords[][3] = {
    {value, value, value},
    {value, -value, value},
    {-value, -value, value},
    {-value, value, value}};

  for (int i = 0; i < count; ++i)
    {
      vertices.push_back(Vertex(coords[i][0], coords[i][1], coords[i][2])); 
    }

  for (int i = 0; i < count; ++i)
    {
      vertices.push_back(Vertex(coords[i][0], coords[i][1], -coords[i][2])); 
    }

  Face face1;
  for (int i = 0; i < count; ++i)
    {
      face1.push_back(i);
    }
  faces.push_back(face1);

  Face face2;
  for (int i = 0; i < count; ++i)
    {
      face2.push_back(7 - i);
    }
  faces.push_back(face2);

  Face face3;
  face3.push_back(4);
  face3.push_back(5);
  face3.push_back(1);
  face3.push_back(0);
  faces.push_back(face3);
  
  Face face4;
  face4.push_back(3);
  face4.push_back(2);
  face4.push_back(6);
  face4.push_back(7);
  faces.push_back(face4);

  Face face5;
  face5.push_back(5);
  face5.push_back(6);
  face5.push_back(2);
  face5.push_back(1);
  faces.push_back(face5);
  
  Face face6;
  face6.push_back(4);
  face6.push_back(0);
  face6.push_back(3);
  face6.push_back(7);
  faces.push_back(face6);
}

