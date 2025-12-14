#pragma once
#include <vector>
#include "blok.h"

// Zarządza zestawem cegieł i ich tworzeniem/resetem.
class Bloki {
private:
    std::vector<Brick> bricks;

public:
    void generateDefault(float areaWidth, float startY = 50.f);
    std::vector<Brick>& getBricks() { return bricks; }
    const std::vector<Brick>& getBricks() const { return bricks; }
    void reset();
};
