
#pragma once

#include "ofMain.h"
#include "pointsRenderer.hpp"

class BrushRenderer : public PointsRenderer {
public:
    
    BrushRenderer();
    void draw();
    ofImage brushTex;
    
    
};
