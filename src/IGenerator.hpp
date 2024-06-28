#pragma once

class IGenerator
{
public:
  virtual ~IGenerator() = default;
  virtual void Generate() = 0;
};

