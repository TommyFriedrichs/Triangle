//
//  TriangleReceiver.h
//  emptyExample
//
//  Created by Daan on 11/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include <list>
#include "ofxImageSequence.h"

enum TriangleState {
	TriangleStateDrawFirstLayer,
	TriangleStateDrawSecondLayer,
	TriangleStateDrawThirdLayer,
	TriangleStateDrawFourthLayer,
	TriangleStateDrawFifthLayer
};

struct Triangle {
    int id;
    ofPoint A;
    ofPoint B;
    ofPoint C;
    float tension;
    float radius;
    float radius1;
    float radius2;
    float radius3;
    float radius4;
    float radius5;
    float lengthOfAB;
    float lengthOfBC;
    float lengthOfCA;
    ofPoint center;
	TriangleState state;
    
};

/* class TriangleReceiver
 * this class provides a simple interface for receiving data formatted in the Triangle protocol
 * it receives the data via OSC and keeps a list of triangles
 */

class TriangleReceiver {
    
public:
    void setup(int port);
    void update();
    void draw();
    
    //png sequence
    ofxImageSequence sequence;
	ofImage background;
	bool playing;
    
    //img loader
    ofxImageSequence shape1;
	bool playingImg;
    
    list<Triangle*> triangles;
    
private:
    ofxOscReceiver receiver;
};
