#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    bUseEasyCam = false;
    //cam.setFlipY(true);//flip the Y axis so it matches OF's default inverted Y axis of ofCamera (and ofEasyCam).
    easyCam.enableOrtho();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(20);
    if (bUseEasyCam) {
        easyCam.begin();
    }else{
        cam.begin();
    }
    ofSetConeResolution(20, 2);
    ofSetCylinderResolution(20, 2);
    ofEnableDepthTest();
    ofSetColor(ofColor::red);//RIGHT
    ofDrawCone(100, 0, 0, 50, 100);
    
    ofSetColor(ofColor::white);//LEFT
    ofDrawSphere(-100, 0, 0, 50);
    
    ofSetColor(ofColor::blue);//BOTTOM
    ofDrawBox(0, 100, 0, 100);
    
    ofSetColor(ofColor::cyan);//TOP
    ofDrawCylinder(0, -100, 0, 50, 100);
    
    ofSetColor(ofColor::yellow);//FRONT
    ofDrawBox(0, 0, 100, 100);
    
    ofSetColor(ofColor::magenta);//BACK
    ofDrawBox(0, 0, -100, 100);
    
    
    
    ofDrawGrid(20,10,true,true,true,true);
    ofDisableDepthTest();
    if (bUseEasyCam) {
        easyCam.end();
    }else{
        cam.end();
    }
    cam.drawDebug();
    /*
    string str = "Currently using: ";
    if (bUseEasyCam) {
        str += "ofEasyCam";
    }else{
        str += "ofxInfiniteCanvas\n\n";
        str += "ofxInfiniteCanvas use:\n";
        str += "    Drag mouse with:\n";
        str += "        Left Button: move\n";
        str += "        Right button: zoom\n";
        str += "    Mouse scroll:  zoom\n\n";
        str += "Set LookAt:   key:\n";
        str += "    RIGHT      d\n";
        str += "    LEFT       a\n";
        str += "    TOP        w\n";
        str += "    BOTTOM     x\n";
        str += "    FRONT      s\n";
        str += "    BACK       z\n\n";
        
        str += "Current LookAt: ";
        
        switch (cam.getLookAt()) {
            case ofxInfiniteCanvas::OFX2DCAM_FRONT:
                str+="FRONT";
                break;
            case ofxInfiniteCanvas::OFX2DCAM_BACK:
                str+="BACK";
                break;
            case ofxInfiniteCanvas::OFX2DCAM_LEFT:
                str+="LEFT";
                break;
            case ofxInfiniteCanvas::OFX2DCAM_RIGHT:
                str+="RIGHT";
                break;
            case ofxInfiniteCanvas::OFX2DCAM_TOP:
                str+="TOP";
                break;
            case ofxInfiniteCanvas::OFX2DCAM_BOTTOM:
                str+="BOTTOM";
                break;
            default:
                break;
        }
        
    }
    ofDrawBitmapStringHighlight(str, 4,28);
    
    str="Press the spacebar to switch between\n";
    str += "projective ofEasyCam and orthogonal ofxInfiniteCanvas.\n";
    ofDrawBitmapStringHighlight(str, 4,12, ofColor::magenta, ofColor::black);
//*/

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == ' ') {
        cam.toggleOfCam();
    }
    if (key == 'c') {
        if (bUseEasyCam) {
            easyCam.disableMouseInput();
            cam.enableMouseInput();
        }else{
            easyCam.enableMouseInput();
            cam.disableMouseInput();
        }
        
        bUseEasyCam ^= true;
    }
    if (key == 'a') {
        cam.setLookAt(ofxInfiniteCanvas::OFX2DCAM_LEFT);
    }else if (key == 's') {
        cam.setLookAt(ofxInfiniteCanvas::OFX2DCAM_FRONT);
    }else if (key == 'd') {
        cam.setLookAt(ofxInfiniteCanvas::OFX2DCAM_RIGHT);
    }else if (key == 'w') {
        cam.setLookAt(ofxInfiniteCanvas::OFX2DCAM_TOP);
    }else if (key == 'x') {
        cam.setLookAt(ofxInfiniteCanvas::OFX2DCAM_BOTTOM);
    }else if (key == 'z') {
        cam.setLookAt(ofxInfiniteCanvas::OFX2DCAM_BACK);
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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