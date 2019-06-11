
#include "melt.hpp"

void Melt::setup(const int &_width, const int &_height){
    ofFbo::Settings setting;
    setting.width = _width;
    setting.height = _height;
    setting.internalformat = GL_RGB32F;
    setting.numSamples = 0;
    setting.wrapModeVertical = GL_REPEAT;
    setting.wrapModeHorizontal = GL_REPEAT;
    setting.textureTarget = GL_TEXTURE_2D;
    
    for (int i=0; i<2; i++) {
        fbFbo[i].allocate(setting);
        fbFbo[i].begin();
        //ofClear(0,0,0,255);
        ofSetColor(0,255);
        ofDrawRectangle(0, 0, _width, _height);
        fbFbo[i].end();
    }
    shader.load("meltShaders/melt7");
    
    gui.setup();
    gui.setName("melt");
    gui.add(g_val.setup("u_val", 0, 0, 0.2));
    gui.setPosition(10, 240);
}

void Melt::begin(){
    fbFbo[0].begin();
    /*
    ofPushStyle();
    ofSetColor(0,20);
    ofDrawRectangle(0, 0, fbFbo[0].getWidth(), 1); //上端
    ofDrawRectangle(0, fbFbo[0].getHeight()-1, fbFbo[0].getWidth(), 1); //下端
    ofDrawRectangle(0, 0, 1, fbFbo[0].getHeight()); //左端
    ofDrawRectangle(fbFbo[0].getWidth()-1, 0, 1, fbFbo[0].getHeight()); //右端
    ofPopStyle();
     */
}

void Melt::end(){
    fbFbo[0].end();
}

void Melt::draw(){
    
    fbFbo[1].begin();
    shader.begin();
    // here is where the fbo is passed to the shader
    shader.setUniformTexture("tex1", fbFbo[1].getTexture(), 1 );
    shader.setUniform2f("u_resolution", fbFbo[0].getWidth(), fbFbo[0].getHeight());
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform1f("u_val", g_val);
    shader.setUniform3f("u_bColor", glm::vec3(0.));
    shader.setUniform1f("u_framerate", ofGetFrameRate());
    //ofDrawRectangle(0,0, ofGetWidth(),ofGetHeight());
    fbFbo[0].draw(0,0);
    shader.end();
    fbFbo[1].end();
    
    ofSetColor(255,255);
    fbFbo[1].draw(0,0);
    swap(fbFbo[0], fbFbo[1]); //二つのfboの中身を入れ替える
}

void Melt::drawGui(){
    ofPushStyle();
    gui.draw();
    ofPopStyle();
}

