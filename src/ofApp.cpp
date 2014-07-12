#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    winW = 800;
    winH = 600;
    
    stampImages.resize(8);
    for(int i=0; i<stampImages.size(); i++){
        imgLoader.loadFromDisk(stampImages[i], "face0"+ofToString(i+1)+".png");
    }
    
    ofSetWindowShape(winW, winH);

    // Allocate framebuffer and initialize with a transparant background
    fbo.allocate(winW, winH);
    fbo.begin();
        ofBackground(0,0,0, 0);
    fbo.end();
    
    // eventHandlers
    ofAddListener(stampEvent, this, &ofApp::onStamp);
}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255,255,255);

    float timer = ofGetElapsedTimeMillis() * 0.005;
    ofVec2f pos(400+sin(timer) * 100, 300+cos(timer) * 100);
    ofNotifyEvent(stampEvent, pos, this);
 	
    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::exit(){
	imgLoader.stopThread();
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
    ofVec2f vec(x,y);
    ofNotifyEvent(stampEvent, vec, this);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofVec2f pos(x,y);
    ofNotifyEvent(stampEvent, pos, this);
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
    ofImage img = stampImages.at(imageIndex);

    fbo.begin();
        img.draw(x-img.getWidth()/2, y-img.getHeight()/2);
    fbo.end();
}

void ofApp::onStamp(ofVec2f &pos){
    stamp(pos.x, pos.y);
}
