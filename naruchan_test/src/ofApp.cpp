#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAntiAliasing();
    ofSetCircleResolution(64);
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    
    WIDTH = 1280;
    HEIGHT = 1024;
    
    nikonikoman.load("nikonikoman2-1.png");
    nikonikoman.setAnchorPercent(0.5, 0.5);
    
    melt.setup(1280, 1024);
    
    gui.setup();
    gui.setName("main");
    gui.add(g_nikoNum.setup("nikoNum", 1, 0, 10));
    gui.add(g_lowValAmp.setup("lowVal", .0, 0, 3));
    gui.add(g_midValAmp.setup("middleVal", 0.0, 0, 3)); //0.3くらいが適量
    gui.add(g_highValAmp.setup("highVal", 0., 0, 3));
    gui.add(g_screenAlph.setup("screenAlph", 255, 0, 255));
    gui.setPosition(10, 120);
    
    //----------------------------fft
    fft.setup();
    fft.setNumFFTBins(256);
    fft.setExponent(1.0);
    fft.setFFTpercentage(0.05);
    
    //----------------------------
    displayFbo.allocate(1280, 1024, GL_RGB32F, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    float lastFrameTime = ofGetLastFrameTime()*2;
    glm::vec2 mouse = glm::vec2(ofGetMouseX(), ofGetHeight()-ofGetMouseY());
    mouse.x *= WIDTH/ofGetWidth();
    mouse.y *= HEIGHT/ofGetHeight();
    
    //------------------------------fft
    fft.update();
    lowVal = fft.getLowVal() * g_lowValAmp;
    midVal = fft.getMidVal() * g_midValAmp;
    highVal = fft.getHighVal() * g_highValAmp;
    
    //-----------------------------------meltレイヤーに書き込み
    melt.begin();
    
        ofSetColor(200+cos(eTime)*55, 200+sin(eTime)*55, 255);
        ofDrawCircle(WIDTH/2, HEIGHT/2, 3*lowVal);
        ofSetColor(0);
        ofDrawCircle(WIDTH/2, HEIGHT/2, 3*lowVal-5);
    
        if (ofGetMousePressed() && ofGetKeyPressed(' ')) {
            ofFloatColor col = ofFloatColor::fromHsb((sin(eTime)+1)*0.5 ,0.3 ,1);
            pRenderer.addPoint(glm::vec3(mouse.x, mouse.y, 0), col, 60);
        }
    
        if (midVal > 5){
            for (int i=0; i<10; i++) {
                glm::vec3 p;
                float scale = ofRandom(240);
                p.x = WIDTH/2 + sin(ofRandom(6)*PI) * scale;
                p.y = HEIGHT/2 + cos(ofRandom(6)*PI) * scale;
                ofFloatColor col = ofFloatColor::fromHsb(ofRandom(1),0.3,1);
                pRenderer.addPoint(p, col, ofRandom(50));
            }
        }
    
        for (int n=0; n<g_nikoNum; n++) {
            float inum = 30; //補完の密度
            for (int i=0; i<inum; i++) {
                glm::vec3 p;
                p.x = sin(-(eTime + lastFrameTime/inum*i + 2*PI/g_nikoNum*n)) * 200 + WIDTH/2;
                p.y = cos(-(eTime + lastFrameTime/inum*i + 2*PI/g_nikoNum*n)) * 200 + HEIGHT/2;
                glm::vec3 noise;
                noise.x = ofSignedNoise((eTime+lastFrameTime/inum*i)*0.4, 100);
                noise.y = ofSignedNoise((eTime+lastFrameTime/inum*i)*0.4, 700);
                p += noise * 10 * highVal;
                ofFloatColor col = ofFloatColor( (100+highVal*4)/255., 255/255., (200+sin(eTime + lastFrameTime/inum)*55)/255);
                pRenderer.addPoint(p, col, 60);
            }
        }
        pRenderer.draw();
    
    melt.end();
    

    //----------------------時間の更新
    eTime += lastFrameTime;
}

//--------------------------------------------------------------
void ofApp::draw(){
    displayFbo.begin();
        ofSetColor(255);
        melt.draw();
    
        ofPushStyle();
        ofPushMatrix();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofTranslate(WIDTH/2, HEIGHT/2);
        ofRotateDeg(eTime*20);
        ofSetColor(255, 255, 100+1*lowVal, 170+1*lowVal);
        float r = 5*lowVal*2.;
        nikonikoman.draw(0,0, r,r);
        ofPopMatrix();
        ofPopStyle();
    displayFbo.end();
    
    displayFbo.draw(0,0, ofGetWidth(), ofGetHeight());
    
    
    gui.draw();
    melt.drawGui();
    ofDrawBitmapString("fps : " + ofToString(ofGetFrameRate()), 10, 20);
    ofDrawBitmapString("lowVal : " + ofToString(lowVal), 10, 40);
    ofDrawBitmapString("midVal : " + ofToString(midVal), 10, 60);
    ofDrawBitmapString("highVal : " + ofToString(highVal), 10, 80);
    ofDrawBitmapString("key:'space' and mousePressed to nikonikoman", 10, 100);
    
    if (ofGetKeyPressed('w')) {
        ofSetColor(255);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    //toggle between normalized and not to get a sense of the effects
    //You will need to set a volume range if you're not normalizing everything - but this will depend on your sound source and input type to determine the maximum volume range of your codez
    if(key=='q'){
        fft.setVolumeRange(100);
        fft.setNormalize(false);
    }
    if(key=='r'){
        fft.setNormalize(true);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
