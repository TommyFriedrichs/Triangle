#pragma once

#include "ofMain.h"
#include <vector>
#include "ofVectorMath.h"
#include "ofVec2f.h"
#include "ofVec3f.h"
#include "ofVec4f.h"
#include "ofMatrix3x3.h"
#include "ofMatrix4x4.h"
#include "ofQuaternion.h"
#include "TriangleReceiver.h"

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    float getMaximumTriangleArea();
    float getMaximumRadiusInTriangle(ofPoint A, ofPoint B, ofPoint C);
    float getTriangleArea(ofPoint A, ofPoint B, ofPoint C);
    ofPoint getTriangleCenter(ofPoint A, ofPoint B, ofPoint C);    

    float maximumAreaThreshold;    
    vector<ofPoint> points;
    TriangleReceiver triangleReceiver;
    
    
};

