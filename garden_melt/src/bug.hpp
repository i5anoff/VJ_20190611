#pragma once

#include "ofMain.h"


class Bug {
public:
    
    
    Bug();
    
    static ofEvent<Bug> birth;
    static ofEvent<Bug> bloom; //花咲かせる用
    
    void setup(const glm::vec3 &_pos,const glm::vec3 &_dir, const int &_generation);
    virtual void update();
    virtual void display();
    virtual void bear(Bug _child);
    void inherited(const Bug &_bug); //引き継ぐ（遺伝する）
    
    
    float seed; //ノイズシードなどに使うようの個体値
    int generation; //枝分かれの階層レベル
    int age; //年齢
    int lifeSpan; //寿命
    int childNum, maxChildNum; //子供の数
    float radius, initialRadius; //円の半径と初期値
    int flowerNum, maxFlowerNum; //花の数
    ofFloatColor color;
    
    
    glm::vec3 pos;
    glm::vec3 dir;
    
    
};

