#pragma once
#include <vector>

class Vertices;
class Faces;

using FaceNumbers = std::vector<int>;

FaceNumbers PrepareFaceNumbers(const Vertices &vertices2d, const Faces &faces);
FaceNumbers SortFaceNumbers(const Vertices& vertices2d, const Faces &faces);

