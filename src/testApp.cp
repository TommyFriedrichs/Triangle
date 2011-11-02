#include "testApp.h"

ofPoint centerOfLineAB;

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
	
	// alpha aan
	ofEnableAlphaBlending();
	
	// load movie
	bloemMovie.loadMovie("movies/bloem_flv.flv");  
    // plays movie  
    bloemMovie.play();  
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    points[2]= ofPoint(mouseX,mouseY);

    radius = getMaximumRadiusInTriangle(points[0], points[1], points[2]);
    ofPoint triangleCenter = getTriangleCenter(points[0], points[1], points[2]);
    
    cout<< "radius: " << radius << endl; 
    cout<< "TriangleCenter: " << triangleCenter << endl;
	
	//uitrekenen middelijn [2]AB
	
	centerOfLineAB = ofPoint(((points[0].x + points[1].x) /2),((points[0].y + points[1].y) /2)); 
	
	midLine = ofDist(points[2].x, points[2].y, centerOfLineAB.x, centerOfLineAB.y);
	
	rot = counter;
    
	//counter koekenbakken
	counter = counter+midLine/600; 
	if (counter == 360) { 
		counter = 0; 
	}
	
	cout << "rot: " << rot << endl;
	cout << "midLine: " << midLine << endl;
	
	//change movie frame
	bloemMovie.idleMovie();
	
	

    
}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(0, 0, 0);
    
    ofSetColor(255);      
    ofSetLineWidth(2);       
    ofLine(points[0], points[1]);
    ofLine(points[1], points[2]);
    ofLine(points[2], points[0]);
	ofLine(points[2],centerOfLineAB);
    
    
//    InCircle tekenen;
 //   ofSetColor(255,0, 0);
    ofSetLineWidth(1);
    ofNoFill();
    ofCircle(triangleCenter, radius);
	
	{   
		ofPushMatrix();
		ofTranslate(triangleCenter.x, triangleCenter.y, 0);
		ofRotateZ(rot);
		bloemMovie.draw(-radius,-radius, radius*2, radius*2);
		ofRect(-radius,-radius, radius*2, radius*2);			//	<< Deze uit.
		ofPopMatrix();
	}  
    
}

//--------------------------------------------------------------
ofPoint testApp::getTriangleCenter(ofPoint A, ofPoint B, ofPoint C){
    
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    
    triangleCenter = ofPoint(((lengthOfBC*points[0]) + (lengthOfCA*points[1]) + (lengthOfAB*points[2]))/perimeter);   
    
    return(triangleCenter);
}

//--------------------------------------------------------------
float testApp::getMaximumRadiusInTriangle(ofPoint A, ofPoint B, ofPoint C){ 
    //Uitrekenen lengtes zijden
    
    
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    
    float semiPerimeter = perimeter/2;
    
    float area = sqrtl(semiPerimeter*((semiPerimeter-lengthOfAB)*(semiPerimeter-lengthOfBC)*(semiPerimeter-lengthOfCA)));
    
    float inCircle = sqrtf(((semiPerimeter-lengthOfAB)*(semiPerimeter-lengthOfBC)*(semiPerimeter-lengthOfCA))/semiPerimeter);
    
    return(inCircle);
    
    //Uitrekenen middenpunten van zijden
    
    //ofPoint centerOfLineAB = ofPoint(((points[0].x + points[1].x) /2),((points[0].y + points[1].y) /2)); 
    ofPoint centerOfLineBC = ofPoint(((points[1].x + points[2].x) /2),((points[1].y + points[2].y) /2));
    ofPoint centerOfLineCA = ofPoint(((points[2].x + points[0].x) /2),((points[2].y + points[0].y) /2));

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