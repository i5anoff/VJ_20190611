#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "melt.hpp"
#include "brushRenderer.hpp"
#include "ofxProcessFFT.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    Melt melt;
    ofImage nikonikoman;
    
    float eTime = 0;
    int WIDTH;
    int HEIGHT;
    
    ofxPanel gui;
    ofxIntSlider g_nikoNum;
    ofxFloatSlider g_lowValAmp, g_midValAmp, g_highValAmp;
    ofxFloatSlider g_screenAlph;
    
    BrushRenderer pRenderer;
    
    //-------------fft
    ProcessFFT fft;
    float lowVal, midVal, highVal;
    
    //-------------displayAppに送る用のfbo
    ofFbo displayFbo;
    
};
