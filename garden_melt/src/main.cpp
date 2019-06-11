#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3,2);
    
    settings.setSize(1280, 512 + 50); //50は下の余白
    settings.setPosition(ofVec2f(400,400));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    mainWindow->setVerticalSync(false);
    
    settings.shareContextWith = mainWindow; //fboを共有するためポインタを共有
    settings.setSize(1280, 1024);
    settings.setPosition(ofVec2f(0,50));
    shared_ptr<ofAppBaseWindow> displayWindow_A = ofCreateWindow(settings);
    displayWindow_A->setVerticalSync(false);
    displayWindow_A->setWindowTitle("A");
    
    settings.shareContextWith = mainWindow;  //fboを共有するためポインタを共有
    settings.setSize(1280, 1024);
    settings.setPosition(ofVec2f(640,50));
    shared_ptr<ofAppBaseWindow> displayWindow_B = ofCreateWindow(settings);
    displayWindow_B->setVerticalSync(false);
    displayWindow_B->setWindowTitle("B");
    
    
    shared_ptr<ofApp> mainApp(new ofApp);
    ofAddListener(displayWindow_A->events().draw,mainApp.get(),&ofApp::drawDisplay_A);
    ofAddListener(displayWindow_B->events().draw,mainApp.get(),&ofApp::drawDisplay_B);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
