//
//  brushRenderer.cpp
//  naruchan_test
//
//  Created by 藤田　恭輔 on 2019/06/04.
//

#include "brushRenderer.hpp"


BrushRenderer::BrushRenderer(){
    // we need to disable ARB textures in order to use normalized texcoords
    ofDisableArbTex(); //テクスチャ読み込み時に呼ぶ
    brushTex.load("brushShader/nikonikoman2-1.png");
    ofEnableArbTex();
    shader.load("brushShader/shader");
}

void BrushRenderer::draw(){
    if(doShader) {
        shader.begin();
        ofEnablePointSprites();
        ofEnableAlphaBlending();
        brushTex.getTexture().bind();
    }
    vboMesh.getVbo().setAttributeData(shader.getAttributeLocation("pointsize"), &pointsSize[0], 1, pointsSize.size(), GL_DYNAMIC_DRAW, sizeof(float));
    vboMesh.draw();
    
    if(doShader) {
        brushTex.getTexture().unbind();
        shader.end();
        ofDisablePointSprites();
    }
    
    vboMesh.clear();
    pointsSize.clear();
    
}
