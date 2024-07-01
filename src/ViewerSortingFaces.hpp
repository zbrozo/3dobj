#pragma once
#include <vector>

class Vertices;
class Faces;

using FaceNumbers = std::vector<int>;

FaceNumbers SortFaceNumbers(const Vertices& vertices2d, const Faces &faces);

