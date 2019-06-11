
#include "bug_leader.hpp"

void Bug_leader::update(){
    /*
     float theta = ofSignedNoise(seed*1000, ofGetFrameNum()*0.01) * 5;
     dir = ofVec2f(dir).getRotated(theta);
     dir = glm::normalize(dir);
     */
    glm::vec3 v = dir;
    pos += v;
    
    if (pos.x < 0 || pos.x > ofGetWidth()) {
        dir.x = -dir.x;
    }
    if (pos.y < 0 || pos.y > ofGetHeight()) {
        dir.y = -dir.y;
    }
    
    //特定の条件下で産む
    if (ofRandom(1) < 0.02 && generation < 3 ) {
        this->bear(*this);
    }
    
    
    age ++;
}

void Bug_leader::display(){
    //ofPushStyle();
    //ofSetColor(255,0,0);
    //ofSetColor(ofColor::fromHsb(seed*255, 255, 255));
    ofDrawCircle(pos, 1);
    //ofPopStyle();
}


void Bug_leader::bear(Bug _child){
    childNum ++;
    
    _child.age = 0;
    _child.generation ++;
    _child.seed = ofRandom(10000);
    _child.childNum = 0;
    _child.maxChildNum = 2;
    _child.lifeSpan = this->lifeSpan * 0.8;
    //_child.dir = ofVec2f(dir).getRotated(30);
    
    ofNotifyEvent(birth, _child, this);
}


