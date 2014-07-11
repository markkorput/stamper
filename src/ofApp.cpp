#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int winW, winH;
    winW = 800;
    winH = 600;

    imgLoader.loadFromDisk(this->stampImage, "face01.png");

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

    fbo.begin();
        ofRect(10, 10, 20, 20);
    fbo.end();

    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    fbo.begin();
        stampImage.draw(x-stampImage.getWidth()/2, y-stampImage.getHeight()/2);
    fbo.end();
}
