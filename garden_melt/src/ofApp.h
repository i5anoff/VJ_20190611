#pragma once

#include "ofMain.h"

#include "rollScreen_melt.hpp"
#include "pointsRenderer.hpp"
#include "flower.hpp"
#include "bug.hpp"
#include "bug_leader.hpp"

#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void drawDisplay_A(ofEventArgs & args);
    void drawDisplay_B(ofEventArgs & args);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseScrolled(int x, int y, float scrollX, float scrollY);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int WIDTH, HEIGHT, wideWIDTH; //WIDTH,HEIGHTはウインドウサイズwideWIDTHはループスクリーン本体の大きさ
    int currentHEIGHT; //mainウインドウのスクリーンの今の縦幅
    
    RollScreen_melt rollScreen; //ロールスクリーン
    PointsRenderer pRenderer; //ポイントドロー用
    
    //---------------植物用のイベントとか
    void bear(Bug & _bug);
    deque<Bug> bugs;
    deque<Flower> flowers;
    void bloom(Bug & _bug);
    
    //---------------植物関係のGUI
    ofxPanel plantsGui;
    ofxIntSlider g_lifeSpan;
    ofxFloatSlider g_initialRadius;
    ofxFloatColorSlider g_plantColor;
    ofxIntSlider g_limit; //bugの数の上限
    
    //--------ほんとはやりたくないけどrollScreenの中のofxGuiがうまく動かないから無理やりこっちで呼び出す
    ofxPanel screenGui;
    ofxFloatSlider g_meltVal, g_fade, g_speed;
    ofxFloatSlider g_offSetX_A, g_offSetX_B; //ついでにプロジェクション対応用のスクリーンのオフセット値
    ofxFloatSlider g_screenAlph_A, g_screenAlph_B; //それぞれのスクリーンのアルファ値
    
    //--------------別スクリーンに渡す用のfbo
    ofFbo displayFbo[2];

};
