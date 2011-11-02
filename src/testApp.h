//test

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

#include "ofVideoPlayer_alpha.h"
#include "ofxImageSequence.h"


class testApp : public ofBaseApp{

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

    float getMaximumRadiusInTriangle(ofPoint A, ofPoint B, ofPoint C);
    ofPoint getTriangleCenter(ofPoint A, ofPoint B, ofPoint C);
    
    float radius;
	float rot;
	float counter;
	float midLine;
    
    
    float A;
    float B;
    float C;
    
    ofPoint AB;
    ofPoint BC;
    ofPoint CA;
    
    ofPoint triangleCenter;
    
    float inCircle;
    float semiPerimeter;
    float area;
    
    int mouseX;
    int mouseY;
		
    vector<ofPoint> points;
    int nrOfPoints;
    
	ofVideoPlayer_alpha		bloemMovie;
    
    
    ofxImageSequence sequence;
	ofImage background;
	bool playing;
};
