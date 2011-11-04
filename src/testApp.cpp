#include "testApp.h"

//Test nog een keer

//--------------------------------------------------------------
void testApp::setup(){
    maximumAreaThreshold = getMaximumTriangleArea()/5;  // we'll use this value for determining which layers to enable
    triangleReceiver.setup(3334);       // setup trianglereceiver to listen on port 3334
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    // png sequence
    triangleReceiver.sequence.loadSequence("frame/frame00", "png", 1, 99, 2);
	triangleReceiver.sequence.preloadAllFrames();	
	triangleReceiver.sequence.setFrameRate(20); //fps
	
	triangleReceiver.playing = true; 
    
    // img player
    triangleReceiver.shape1.loadSequence("image/shape1_layer", "png", 1, 4, 2);
	triangleReceiver.shape1.preloadAllFrames();	
    
    triangleReceiver.playingImg = false; 
}

//--------------------------------------------------------------
void testApp::update(){
    triangleReceiver.update();  // receive triangle data
        
    list<Triangle*>::iterator triangleIt;
    for(triangleIt = triangleReceiver.triangles.begin(); triangleIt != triangleReceiver.triangles.end(); triangleIt++){             // set radius, center for every triangle
        (*triangleIt)->radius       = getMaximumRadiusInTriangle((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
        (*triangleIt)->center       = getTriangleCenter((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
        (*triangleIt)->lengthOfAB   = (ofDist((*triangleIt)->A.x, (*triangleIt)->A.y, (*triangleIt)->B.x, (*triangleIt)->B.y));     // set linelengths
        (*triangleIt)->lengthOfBC   = (ofDist((*triangleIt)->B.x, (*triangleIt)->B.y, (*triangleIt)->C.x, (*triangleIt)->C.y));
        (*triangleIt)->lengthOfCA   = (ofDist((*triangleIt)->C.x, (*triangleIt)->C.y, (*triangleIt)->A.x, (*triangleIt)->A.y));
        (*triangleIt)->radius1      = (*triangleIt)->radius*1.6/5;
        (*triangleIt)->radius2      = (*triangleIt)->radius*1.6/5*2;
        (*triangleIt)->radius3      = (*triangleIt)->radius*1.6/5*3;
        (*triangleIt)->radius4      = (*triangleIt)->radius*1.6/5*4;
        (*triangleIt)->radius5      = (*triangleIt)->radius*1.6;
        
        
        // enable or disable each of the 5 layers according to the area of the triangle
        float triangleArea = getTriangleArea((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
        if(triangleArea < maximumAreaThreshold){
			(*triangleIt)->state = TriangleStateDrawFirstLayer;
        }
        
        else if(triangleArea > maximumAreaThreshold && triangleArea < maximumAreaThreshold*2 ){
			(*triangleIt)->state = TriangleStateDrawSecondLayer;
        }
        
        else if(triangleArea > maximumAreaThreshold*2 && triangleArea < maximumAreaThreshold*3){
			(*triangleIt)->state = TriangleStateDrawThirdLayer;
        }
        
        else if(triangleArea > maximumAreaThreshold*3 && triangleArea < maximumAreaThreshold*4){
            (*triangleIt)->state = TriangleStateDrawFourthLayer;
        }        
        else{
            (*triangleIt)->state = TriangleStateDrawFifthLayer;
        }
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 0); 
    
    list<Triangle*>::iterator triangleIt;
    for(triangleIt = triangleReceiver.triangles.begin(); triangleIt != triangleReceiver.triangles.end(); triangleIt++){
        // draw (red) filled triangle, opacity determined by tension
        ofFill();
        ofSetColor(255, 0, 0, (*triangleIt)->tension * 255.0f);
        ofTriangle((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
        
        // draw (white) lines, full opacity
        ofSetColor(255);      
        ofSetLineWidth(2);
        ofLine((*triangleIt)->A.x,(*triangleIt)->A.y, (*triangleIt)->B.x,(*triangleIt)->B.y);
        ofLine((*triangleIt)->B.x,(*triangleIt)->B.y,(*triangleIt)->C.x,(*triangleIt)->C.y);
        ofLine((*triangleIt)->C.x,(*triangleIt)->C.y, (*triangleIt)->A.x,(*triangleIt)->A.y);
        
        // draw (green) animation placeholders
        ofSetColor(0, 255, 0);
        ofSetLineWidth(1);
        ofNoFill();    

        
		if((*triangleIt)->state == TriangleStateDrawFirstLayer){
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(180);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius1/2,0 - (*triangleIt)->radius1/2, (*triangleIt)->radius1, (*triangleIt)->radius1);
            ofPopMatrix();
		}
		else if((*triangleIt)->state == TriangleStateDrawSecondLayer){
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(170);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius1/2,0 - (*triangleIt)->radius1/2, (*triangleIt)->radius1, (*triangleIt)->radius1);
            ofPopMatrix();
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(100);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius2/2,0 - (*triangleIt)->radius2/2, (*triangleIt)->radius2, (*triangleIt)->radius2);
            ofPopMatrix(); 
		}
		else if((*triangleIt)->state == TriangleStateDrawThirdLayer){
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(180);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius1/2,0 - (*triangleIt)->radius1/2, (*triangleIt)->radius1, (*triangleIt)->radius1);
            ofPopMatrix();
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(100);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius2/2,0 - (*triangleIt)->radius2/2, (*triangleIt)->radius2, (*triangleIt)->radius2);
            ofPopMatrix();  
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(10);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius3/2,0 - (*triangleIt)->radius3/2, (*triangleIt)->radius3, (*triangleIt)->radius3);
            ofPopMatrix();
		}
		else if((*triangleIt)->state == TriangleStateDrawFourthLayer){
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(180);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius1/2,0 - (*triangleIt)->radius1/2, (*triangleIt)->radius1, (*triangleIt)->radius1);
            ofPopMatrix();
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(100);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius2/2,0 - (*triangleIt)->radius2/2, (*triangleIt)->radius2, (*triangleIt)->radius2);
            ofPopMatrix(); 
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(60);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius3/2,0 - (*triangleIt)->radius3/2, (*triangleIt)->radius3, (*triangleIt)->radius3);
            ofPopMatrix();
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(90);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius4/2,0 - (*triangleIt)->radius4/2, (*triangleIt)->radius4, (*triangleIt)->radius4);
            ofPopMatrix(); 
		}
		else if((*triangleIt)->state == TriangleStateDrawFifthLayer){
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(30);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius1/2,0 - (*triangleIt)->radius1/2, (*triangleIt)->radius1, (*triangleIt)->radius1);
            ofPopMatrix();
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(70);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius2/2,0 - (*triangleIt)->radius2/2, (*triangleIt)->radius2, (*triangleIt)->radius2);
            ofPopMatrix();   
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(130);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius3/2,0 - (*triangleIt)->radius3/2, (*triangleIt)->radius3, (*triangleIt)->radius3);
            ofPopMatrix();
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(110);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius4/2,0 - (*triangleIt)->radius4/2, (*triangleIt)->radius4, (*triangleIt)->radius4);
            ofPopMatrix();
            ofPushMatrix();
            ofTranslate((*triangleIt)->center.x, (*triangleIt)->center.y, 0);
            ofRotateZ(40);
            triangleReceiver.shape1.getFrame(1)->draw(0 -(*triangleIt)->radius5/2,0 - (*triangleIt)->radius5/2, (*triangleIt)->radius5, (*triangleIt)->radius5);
            ofPopMatrix();
		}
    }
}

//--------------------------------------------------------------
ofPoint testApp::getTriangleCenter(ofPoint A, ofPoint B, ofPoint C){
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    ofPoint triangleCenter = ofPoint(((lengthOfBC * A) + (lengthOfCA * B) + (lengthOfAB * C)) / perimeter);   
    
    return(triangleCenter);
}

//--------------------------------------------------------------
float testApp::getMaximumRadiusInTriangle(ofPoint A, ofPoint B, ofPoint C){ 
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    float semiPerimeter = perimeter/2;  
    float maxRadius = sqrtf( ( (semiPerimeter - lengthOfAB) * (semiPerimeter - lengthOfBC) * (semiPerimeter - lengthOfCA) ) / semiPerimeter);
    
    return(maxRadius);
}
//--------------------------------------------------------------
float testApp::getTriangleArea(ofPoint A, ofPoint B, ofPoint C){
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    float semiPerimeter = perimeter/2;
    float area = sqrtf( semiPerimeter * ( (semiPerimeter - lengthOfAB) * (semiPerimeter - lengthOfBC) * (semiPerimeter - lengthOfCA) ));
    
    return(area);
}

//--------------------------------------------------------------
float testApp::getMaximumTriangleArea(){ 
    float maxSideLength = 500;
    float maxSemiPerimeter = (maxSideLength*3)/2;
    float maxArea = sqrtf( maxSemiPerimeter * ( (maxSemiPerimeter - maxSideLength) * (maxSemiPerimeter - maxSideLength) * (maxSemiPerimeter - maxSideLength) ) );
    float areaThreshold = maxArea/5;
    
    return(areaThreshold);
}