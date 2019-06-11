//
//  rollScreen_melt.hpp
//  rollScreenMelt
//
//  Created by 藤田　恭輔 on 2019/05/30.
//

#ifndef rollScreen_melt_hpp
#define rollScreen_melt_hpp

#include "ofMain.h"
#include "ofxGui.h"

class RollScreen_melt {
public:
    RollScreen_melt();
    void init(const int &_width, const int &_height);
    
    void begin();
    void end();
    float getScreenPositionX(const float &_posX);
    void clear();
    void drawIn(const function<void()> &_draw); //draw関数を受け取ってfboにかき入れるやつ
    
    void update();
    void draw(const float &_width, const float &_height);
    void drawRectFrame(const float &_width, const float &_height); //fbo(四角)の枠を表示(デバッグ用)
    void swapBuffers();
    
    int screenWidth;
    float scrollingX = 0;
    ofFloatColor backgroundColor;
    
    ofFbo fbFbo[2];
    ofShader shader;
    
    //----------------------guiうまく動かない問題....
    //ofxPanel gui;
    //ofxFloatSlider g_meltVal, g_fade, g_speed;
    float g_meltVal, g_fade, g_speed;
    //void drawGui();
    
};

#endif /* rollScreen_melt_hpp */
