//
//  2DCam.h
//  emptyExample
//
//  Created by Roy Macdonald on 27-06-15.
//
//

#pragma once

#include "ofMain.h"


class ofx2DCam {//: public ofCamera {
public:
    
    enum LookAt{
        OFX2DCAM_FRONT =0,
        OFX2DCAM_BACK,
        OFX2DCAM_LEFT,
        OFX2DCAM_RIGHT,
        OFX2DCAM_TOP,
        OFX2DCAM_BOTTOM
    };
    ofx2DCam();
    ~ofx2DCam();
    
    virtual void begin(ofRectangle viewport = ofGetCurrentViewport());
    virtual void end();
    void reset();

    void setDrag(float drag);
    float getDrag() const;

    void enableMouseInput();
    void disableMouseInput();
    bool getMouseInputEnabled();
    
    ofVec3f getTranslation(){return translation;}
    float getScale(){return scale;}

    ofVec3f screenToWorld(ofVec3f screen);
    
    void setLookAt(LookAt l);
    
    LookAt getLookAt();
    
    void setFarClip(float far);
    void setNearClip(float near);
    
    float getNearClip(){return nearClip;}
    float getFarClip(){return farClip;}
protected:

    ofVec3f orientation;
    
    ofRectangle viewport;
    bool bApplyInertia;
    bool bDoTranslate;
    bool bDoScale;
    bool bDoScrollZoom;
    bool bMouseInputEnabled;
    bool bDistanceSet;
    bool bEventsSet;
    
    float drag;
    ofVec3f move;
    float scale;
    
    ofVec3f translation;
    
    float sensitivityXY;
    float sensitivityZ;
    
    ofVec2f prevMouse;
 
    ofVec2f mouseVel;
    
    float farClip, nearClip;

    void update(ofEventArgs & args);
    void mousePressed(ofMouseEventArgs & mouse);
    void mouseReleased(ofMouseEventArgs & mouse);
    void mouseDragged(ofMouseEventArgs & mouse);
    void mouseScrolled(ofMouseEventArgs & mouse);
    void updateMouse();
    
    ofMatrix4x4 orientationMatrix;
    
    unsigned long lastTap;
    
    LookAt lookAt;
    
    static ofMatrix4x4 FM, BM, LM, RM, TM, BoM;
};
