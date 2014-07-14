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

    // Allocate another framebuffer, this one will be emptied and used to apply hue to the current stamp
    hueFbo.allocate(winW, winH);
    tintColor = getTintColor();

    
    // eventHandlers
    ofAddListener(stampEvent, this, &ofApp::onStamp);
}

//--------------------------------------------------------------
void ofApp::update(){
    float timer = ofGetElapsedTimeMillis() * 0.005;
    ofVec2f pos(400+cos(timer*0.5+PI*0.25) * 200, 300+cos(timer) * 100);

    // let's change the image
    int imageIndex = (ofGetElapsedTimeMillis()/500 % stampImages.size());
    ofImage* tmpImg = &stampImages.at(imageIndex);

    if(currentImage != tmpImg){
        // set current image
        currentImage = tmpImg;
        // set tint color
        if(tinting) tintColor = getTintColor();
    }

    // make completely transparant
    ofNotifyEvent(stampEvent, pos, this);
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255,255,255);
    
    if(fading){
        fbo.begin();
            ofPushStyle();
                ofSetColor(fadingColor);
                ofFill();
                ofRect(0,0,winW,winH);
            ofPopStyle();
        fbo.end();
    }

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
    
    if(key == 99) tinting = !tinting; // 'c' toggles tinting
    if(key == 102) fading = !fading; // 'f' toggles fading
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
    hueFbo.begin();
        ofBackground(0,0,0, 0);
        currentImage->draw(x-currentImage->getWidth()/2, y-currentImage->getHeight()/2);
    hueFbo.end();
    
    applyTint(&hueFbo);

    fbo.begin();
        hueFbo.draw(0,0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::onStamp(ofVec2f &pos){
    stamp(pos.x, pos.y);
}

//--------------------------------------------------------------
ofColor ofApp::getTintColor(){
    return ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 50);
}

//--------------------------------------------------------------
void ofApp::applyTint(ofFbo* _fbo){
    hueFbo.begin();
        ofPushStyle();
            ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
                ofSetColor(tintColor);
                ofFill();
                ofRect(0,0,winW,winH);
            ofDisableBlendMode();
        ofPopStyle();
    hueFbo.end();
}
