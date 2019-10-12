#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"
#include "ofAppNoWindow.h"

    /*
    WITHOUT DEPTH SAMPLING:
        window.setGlutDisplayString("rgba double samples>=4");
    WITH DEPTH SAMPLING:
        window.setGlutDisplayString("rgba double depth samples>=4");
        window.setGlutDisplayString("rgba double depth alpha samples>=4);
     */

int main( ){
	ofAppGlutWindow window;
    window.setGlutDisplayString("rgba double depth alpha samples>=4");
    ofSetupOpenGL(&window, 320, 568, OF_WINDOW);
    ofApp *app = new ofApp;
    ofRunApp( app );
    delete app;
}

