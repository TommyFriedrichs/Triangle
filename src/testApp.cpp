#include "testApp.h"

//point[0] = A
//point[1] = B
//point[2] = C

//lengtes zijden opslaan

float A;
float B;
float C;

// middenpunten opslaan om zwaartelijnen te tekenen

ofPoint AB;
ofPoint BC;
ofPoint CA;

// zwaartepunt opslaan

ofPoint triangleCenter;

// lengte zwaartepunt naar middenpunt lijn

float RadiusArray[3];

//incircle opslaan
//s= semi-perimeter van driehoek (a+b+c) /2
//area = wortel p*(p-a)(p-b)(p-c)

float inCircle;
float s;
float area;


//--------------------------------------------------------------
void testApp::setup(){
    nrOfPoints = 3;
//    for (int i = 0; i < nrOfPoints; i++) {
//        int x = i * 200;
//        int y = i * 50;
//        int z = 200;
//        ofPoint pt = ofPoint(x, y, z);
//        points.push_back(pt);
//    }
    
    points.push_back(ofPoint(300,300));
    points.push_back(ofPoint(600,300));    
    points.push_back(ofPoint(200,150));
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    points[2]= ofPoint(mouseX,mouseY);

    //Uitrekenen lengtes zijden

        
    A = (ofDist(points[0].x, points[0].y, points[1].x, points[1].y));
    B = (ofDist(points[1].x, points[1].y, points[2].x, points[2].y));
    C = (ofDist(points[2].x, points[2].y, points[0].x, points[0].y));

    

    //Uitrekenen middenpunten van zijden
    
    AB = ofPoint(((points[0].x + points[1].x) /2),((points[0].y + points[1].y) /2)); 
    BC = ofPoint(((points[1].x + points[2].x) /2),((points[1].y + points[2].y) /2));
    CA = ofPoint(((points[2].x + points[0].x) /2),((points[2].y + points[0].y) /2));
    

    float p = (A+B+C);
    
//    uitrekenen inCenter
    
    triangleCenter = ofPoint(((B*points[0]) + (C*points[1]) + (A*points[2]))/(A+B+C));
    
    
//    uitrekenen inCircle
    s = p/2;
    
    
   
    float area = sqrtl(s*((s-A)*(s-B)*(s-C))) ;
    
    
    inCircle = sqrtf(((s-A)*(s-B)*(s-C))/s);
    

    
}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(0, 0, 0);
    
    ofSetColor(255);      
    ofSetLineWidth(2);       
    ofLine(points[0], points[1]);
    ofLine(points[1], points[2]);
    ofLine(points[2], points[0]);
    
    
//    InCircle tekenen;
    ofSetColor(255,0, 0);
    ofSetLineWidth(1);
    ofNoFill();
    ofCircle(triangleCenter, inCircle);
    

    
        
    
}
//--------------------------------------------------------------
void testApp::drawCustomShape(ofPoint A, ofPoint B, ofPoint C){ 
    ofTriangle(A, B, C);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    mouseX = x;
    mouseY = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}