#include "ofMain.h"
#include "ofApp.h"
#include "displayApp.hpp"

//#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3,2);
    
    settings.setSize(1280, 1024);
    settings.setPosition(ofVec2f(100,100));
    shared_ptr<ofAppBaseWindow> displayWindow = ofCreateWindow(settings);
    
    settings.setSize(640, 512);
    settings.setPosition(ofVec2f(600,300));
    settings.shareContextWith = displayWindow;
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    
    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<DisplayApp> displayApp(new DisplayApp);
    displayApp->mainObj = mainApp;
    
    
    ofRunApp(displayWindow, displayApp);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
}
