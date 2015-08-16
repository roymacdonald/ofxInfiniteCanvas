//
//  ofx2DCam.cpp
//  ofx2DCam
//
//  Created by Roy Macdonald on 27-06-15.
//
//

#include "ofx2DCam.h"


ofMatrix4x4 ofx2DCam::FM = ofMatrix4x4( 1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1 );
ofMatrix4x4 ofx2DCam::BM = ofMatrix4x4(-1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1 );
ofMatrix4x4 ofx2DCam::LM = ofMatrix4x4( 0, 0, 1, 0,
                                        0, 1, 0, 0,
                                        1, 0, 0, 0,
                                        0, 0, 0, 1 );
ofMatrix4x4 ofx2DCam::RM = ofMatrix4x4( 0, 0,-1, 0,
                                        0, 1, 0, 0,
                                        1, 0, 0, 0,
                                        0, 0, 0, 1 );
ofMatrix4x4 ofx2DCam::TM = ofMatrix4x4( 1, 0, 0, 0,
                                        0, 0, 1, 0,
                                        0, 1, 0, 0,
                                        0, 0, 0, 1 );
ofMatrix4x4 ofx2DCam::BoM = ofMatrix4x4( 1, 0, 0, 0,
                                         0, 0,-1, 0,
                                         0, 1, 0, 0,
                                         0, 0, 0, 1 );

static const float minDifference = 0.1e-5f;

static const unsigned long doubleclickTime = 300;

//----------------------------------------
ofx2DCam::ofx2DCam(){
    setLookAt(OFX2DCAM_FRONT);
    lastTap	= 0;
    drag = 0.9f;
    sensitivityXY = .5f;
    sensitivityZ= .001f;
    
    bApplyInertia =false;
    bDoTranslate = false;

    bDistanceSet = false;
    bDoScale = false;
    
    farClip = 2000;
    nearClip = -1000;
    
    reset();

    enableMouseInput();

}
//----------------------------------------
ofx2DCam::~ofx2DCam(){
    disableMouseInput();
}
//----------------------------------------
void ofx2DCam::reset(){
    if (!viewport.isEmpty()) {
        translation = ofVec3f(viewport.width/2, viewport.height/2);
    }else{
        translation = ofVec3f(ofGetWidth()/2, ofGetHeight()/2);
    }
    scale =1;
    move = ofVec3f::zero();
    bDoScale = false;
    bApplyInertia = false;
    bDoTranslate = false;
    
}
//----------------------------------------
void ofx2DCam::begin(ofRectangle _viewport){
    viewport = _viewport;
    ofPushView();
    ofViewport(viewport);
    ofSetupScreenOrtho(viewport.width, viewport.height, nearClip, farClip);
    ofPushMatrix();
    ofRotateX(orientation.x);
    ofRotateY(orientation.y);
    
    ofTranslate(translation*orientationMatrix);
    ofScale(scale,scale,scale);
    
}
//----------------------------------------
ofx2DCam::LookAt ofx2DCam::getLookAt(){
    return lookAt;
}
//----------------------------------------
void ofx2DCam::end(){
    ofPopMatrix();
    ofPopView();
}
//----------------------------------------
void ofx2DCam::setFarClip(float far){
    farClip = far;
}
//----------------------------------------
void ofx2DCam::setNearClip(float near){
    nearClip = near;
}

//----------------------------------------
void ofx2DCam::setLookAt(LookAt l){
    bool bUpdateMatrix = false;
    lookAt = l;
    switch (l) {
        case OFX2DCAM_FRONT:
            orientationMatrix = FM;
            orientation.set(0);
            break;
        case OFX2DCAM_BACK:
            orientationMatrix = BM;
            orientation.set(0,180,0);
            break;
        case OFX2DCAM_LEFT:
            orientationMatrix = LM;
            orientation.set(0, 90,0);
            break;
        case OFX2DCAM_RIGHT:
            orientationMatrix = RM;
            orientation.set(0, -90, 0);
            break;
        case OFX2DCAM_TOP:
            orientationMatrix = TM;
            orientation.set(-90, 0,0);
            break;
        case OFX2DCAM_BOTTOM:
            orientationMatrix = BoM;
            orientation.set(90, 0, 0);
            break;
        default:
            break;
    }
}
//----------------------------------------
void ofx2DCam::setDrag(float drag){this->drag = drag;}
//----------------------------------------
float ofx2DCam::getDrag() const{return drag;}
//----------------------------------------
void ofx2DCam::enableMouseInput(){
    if(!bMouseInputEnabled){
        ofAddListener(ofEvents().update, this, &ofx2DCam::update);
        ofAddListener(ofEvents().mouseDragged , this, &ofx2DCam::mouseDragged);
        ofAddListener(ofEvents().mousePressed, this, &ofx2DCam::mousePressed);
        ofAddListener(ofEvents().mouseReleased, this, &ofx2DCam::mouseReleased);
        ofAddListener(ofEvents().mouseScrolled, this, &ofx2DCam::mouseScrolled);
    }
    bMouseInputEnabled = true;
}
//----------------------------------------
void ofx2DCam::disableMouseInput(){
    if(bMouseInputEnabled){
        ofRemoveListener(ofEvents().update, this, &ofx2DCam::update);
        ofRemoveListener(ofEvents().mouseDragged, this, &ofx2DCam::mouseDragged);
        ofRemoveListener(ofEvents().mousePressed, this, &ofx2DCam::mousePressed);
        ofRemoveListener(ofEvents().mouseReleased, this, &ofx2DCam::mouseReleased);
        ofRemoveListener(ofEvents().mouseScrolled, this, &ofx2DCam::mouseScrolled);
    }
    bMouseInputEnabled = false;
}
//----------------------------------------
bool ofx2DCam::getMouseInputEnabled(){
    return bMouseInputEnabled;
}
//----------------------------------------
void ofx2DCam::mousePressed(ofMouseEventArgs & mouse){
    if(viewport.inside(mouse.x, mouse.y)){
        prevMouse = mouse;
        bDoTranslate =(mouse.button == OF_MOUSE_BUTTON_LEFT);
        bDoScale =(mouse.button == OF_MOUSE_BUTTON_RIGHT);
        bApplyInertia = false;
    }
}
//----------------------------------------
void ofx2DCam::mouseReleased(ofMouseEventArgs & mouse){
    unsigned long curTap = ofGetElapsedTimeMillis();
    if(lastTap != 0 && curTap - lastTap < doubleclickTime){
        reset();
        return;
    }
    lastTap = curTap;
    bApplyInertia = true;
    mouseVel = mouse  - prevMouse;
    updateMouse();
    prevMouse = mouse;
}
//----------------------------------------
void ofx2DCam::mouseDragged(ofMouseEventArgs & mouse){
    mouseVel = mouse  - prevMouse;
    bApplyInertia = false;
    updateMouse();
    prevMouse = mouse;
}
//----------------------------------------
void ofx2DCam::mouseScrolled(ofMouseEventArgs & mouse){
    move.z = mouse.y * 30 * sensitivityZ;
    bDoTranslate = false;
    bDoScale = true;
}
//----------------------------------------
void ofx2DCam::updateMouse(){
        move = ofVec3f::zero();
        if(bDoScale){
            move.z = mouseVel.y * sensitivityZ;
        }else if(bDoTranslate){
            move.x = mouseVel.x ;
            move.y = mouseVel.y;
        }
}
//----------------------------------------
void ofx2DCam::update(ofEventArgs & args){
    if(bMouseInputEnabled){
        if(bApplyInertia){
            move *= drag;
            if(ABS(move.x) <= minDifference && ABS(move.y) <= minDifference && ABS(move.z) <= minDifference){
                bApplyInertia = false;
                bDoTranslate = false;
                bDoScale = false;
            }
        }
        if(bDoTranslate){
            translation += ofVec3f(move.x , move.y, 0);
        }else if(bDoScale){
            scale+= move.z;
        }
        if(!bApplyInertia){
            move = ofVec3f::zero();
        }
    }
}
//----------------------------------------
ofVec3f ofx2DCam::screenToWorld(ofVec3f screen){
    ofVec3f s = screen - translation - ofVec3f(viewport.x, viewport.y);
    s = s*orientationMatrix;
    s /= scale;
    return s;
}
