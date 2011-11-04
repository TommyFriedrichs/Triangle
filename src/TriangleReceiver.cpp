//
//  TriangleReceiver.cpp
//  emptyExample
//
//  Created by Daan on 11/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "TriangleReceiver.h"

void TriangleReceiver::setup(int port){
    receiver.setup(port);
    cout << "TriangleReceiver::setup(int port) -- will start listening on port " << port << endl;
    

}


void TriangleReceiver::update(){
    // check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
        
		// check for didAppear
		if ( m.getAddress() == "/triangle/didAppear" )
		{
            Triangle *tri = new Triangle;
            tri->id = m.getArgAsInt32(0);
            tri->A = ofPoint(m.getArgAsFloat(1), m.getArgAsFloat(2));
            tri->B = ofPoint(m.getArgAsFloat(3), m.getArgAsFloat(4));
            tri->C = ofPoint(m.getArgAsFloat(5), m.getArgAsFloat(6));
            tri->tension = m.getArgAsFloat(7);
            triangles.push_back(tri);
		}
		// check for didMove
		else if ( m.getAddress() == "/triangle/didMove" )
		{
            int id = m.getArgAsInt32(0);
            list<Triangle*>::iterator triangleIt;
            for(triangleIt = triangles.begin(); triangleIt != triangles.end(); triangleIt++){
                if((*triangleIt)->id == id){
                    (*triangleIt)->A = ofPoint(m.getArgAsFloat(1), m.getArgAsFloat(2));
                    (*triangleIt)->B = ofPoint(m.getArgAsFloat(3), m.getArgAsFloat(4));
                    (*triangleIt)->C = ofPoint(m.getArgAsFloat(5), m.getArgAsFloat(6));
                    (*triangleIt)->tension = m.getArgAsFloat(7);
                    return;
                }
            }
		}
        // check for didDisappear
		else if ( m.getAddress() == "/triangle/didDisappear" )
		{
            int id = m.getArgAsInt32(0);
            list<Triangle*>::iterator triangleIt;
            for(triangleIt = triangles.begin(); triangleIt != triangles.end(); triangleIt++){
                if((*triangleIt)->id == id){
                    triangles.remove((*triangleIt));
                    return;
                }
            }
		}
        
        // unrecognized address
		else
		{
			cout << "TriangleReceiver::update() -- unrecognized address: " << m.getAddress() << endl;
		}
	}
}

void TriangleReceiver::draw(){
    list<Triangle*>::iterator triangleIt;
    for(triangleIt = triangles.begin(); triangleIt != triangles.end(); triangleIt++){
        ofSetColor(255, 0, 0, (*triangleIt)->tension * 255.0f);
        ofTriangle((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
    }
}





