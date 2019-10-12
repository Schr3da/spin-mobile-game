#include "ofMain.h"
#include "ofAppiOSWindow.h"
#include "ofApp.h"


//extern "C"{
//    size_t fwrite$UNIX2003( const void *a, size_t b, size_t c, FILE *d )
//    {
//        return fwrite(a, b, c, d);
//    }
//    char* strerror$UNIX2003( int errnum )
//    {
//        return strerror(errnum);
//    }
//    time_t mktime$UNIX2003(struct tm * a)
//    {
//        return mktime(a);
//    }
//    double strtod$UNIX2003(const char * a, char ** b) {
//        return strtod(a, b);
//    }
//}

int main() {
    
    //  here are the most commonly used iOS window settings.
    //------------------------------------------------------
    CGRect frame = [UIScreen mainScreen].bounds;
    
    ofiOSWindowSettings settings;
    settings.enableRetina = true; // enables retina resolution if the device supports it.
    settings.enableDepth = true; // enables depth buffer for 3d drawing.
    settings.enableAntiAliasing = true; // enables anti-aliasing which smooths out graphics on the screen.
    settings.numOfAntiAliasingSamples = 2; // number of samples used for anti-aliasing.
    settings.enableHardwareOrientation = false; // enables native view orientation.
    settings.enableHardwareOrientationAnimation = false; // enables native orientation changes to be animated.
    settings.glesVersion = OFXIOS_RENDERER_ES1; // type of renderer to use, ES1, ES2, etc.
    settings.width = frame.size.width;
    settings.height = frame.size.height;
    ofCreateWindow(settings);
    
    return ofRunApp(new ofApp);
}
