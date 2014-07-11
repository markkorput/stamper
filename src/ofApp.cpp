#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    winW = 800;
    winH = 600;
    
    imgLoader.loadFromDisk(stampImage, "face01.png");
    
    for(int i=0; i<8; i++){
        ofImage *tmpImage = new ofImage();
        imgLoader.loadFromDisk(*tmpImage, "face0"+ofToString(i+1)+".png");
        stampImages.push_back(tmpImage);
    }
    


    ofSetWindowShape(winW, winH);

    // Allocate framebuffer and initialize with a transparant background
    fbo.allocate(winW, winH);
    fbo.begin();
        ofBackground(0,0,0, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255,255,255);
    
    float timer = ofGetElapsedTimeMillis() * 0.005;
    stamp(400+sin(timer) * 100, 300+cos(timer) * 100);
	
    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 13){ // RETURN
        ofImage screen;
        screen.grabScreen(0,0, winW, winH);
        screen.saveImage("screen-"+ofToString(ofGetElapsedTimeMillis())+".png");
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
    stamp(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    stamp(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

//--------------------------------------------------------------
void ofApp::stamp(int x, int y){
    int imageIndex = (ofGetElapsedTimeMillis()/500 % stampImages.size());
    ofImage* img = stampImages.at(imageIndex);

    fbo.begin();
        img->draw(x-stampImage.getWidth()/2, y-stampImage.getHeight()/2);
    fbo.end();
}
