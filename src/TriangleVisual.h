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

class TriangleVisual : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    float getMaximumTriangleArea();
    float getMaximumRadiusInTriangle(ofPoint A, ofPoint B, ofPoint C);
    float getTriangleArea(ofPoint A, ofPoint B, ofPoint C);
    ofPoint getTriangleCenter(ofPoint A, ofPoint B, ofPoint C);    
    int getRandom();
           
    
    ofPoint AB;
    ofPoint BC;
    ofPoint CA;    
    ofPoint triangleCenter;
    
    float lengthOfAB;
    float lengthOfBC;
    float lengthOfCA;
    
    float inCircle;
    float semiPerimeter;
    float area;
    float sideA;
    float sideB;
    float sideC;    
    float radius; 
    float maximumAreaThreshold;
    
    bool layer1;
    bool layer2;
    bool layer3;
    bool layer4;
    bool layer5;
    int mouseX;
    int mouseY;
	
	int random;
    vector<ofPoint> points;
    int nrOfPoints;
    
    TriangleReceiver triangleReceiver;
    
    ofEasyCam cam;
};
