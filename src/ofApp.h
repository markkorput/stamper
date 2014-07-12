#pragma once

#include <math.h>
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    private:
        int winW, winH;
        void stamp(int x, int y);

        // screenbuffer
        ofFbo fbo;

        ofxThreadedImageLoader imgLoader;
        vector<ofImage> stampImages;
    
        ofEvent<ofVec2f> stampEvent;
        void onStamp(ofVec2f &pos);
};
