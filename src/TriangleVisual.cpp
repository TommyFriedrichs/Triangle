#include "TriangleVisual.h"


//--------------------------------------------------------------
void TriangleVisual::setup(){
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
    
    int randomLayer = getRandom();
    
    maximumAreaThreshold = getMaximumTriangleArea()/5;
    
    cout << "MaximumThreshold: " << maximumAreaThreshold << endl;
    
    layer1 = true;
    layer2 = false;
    layer3 = false;
    layer4 = false;
    layer5 = false;

}

//--------------------------------------------------------------
void TriangleVisual::update(){
    
    points[2]= ofPoint(mouseX,mouseY);

    list<Triangle*>::iterator triangleIt;
    for(triangleIt = triangleReceiver.triangles.begin(); triangleIt != triangleReceiver.triangles.end(); triangleIt++){
        ofSetColor(255, 0, 0, (*triangleIt)->tension * 255.0f);
        ofTriangle((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
    
    radius = getMaximumRadiusInTriangle((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
    ofPoint triangleCenter = getTriangleCenter((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
    float triangleArea = getTriangleArea((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
    
    lengthOfAB = (ofDist((*triangleIt)->A.x, (*triangleIt)->A.y, (*triangleIt)->B.x, (*triangleIt)->B.y));
    lengthOfBC = (ofDist((*triangleIt)->B.x, (*triangleIt)->B.y, (*triangleIt)->C.x, (*triangleIt)->C.y));
    lengthOfCA = (ofDist((*triangleIt)->C.x, (*triangleIt)->C.y, (*triangleIt)->A.x, (*triangleIt)->A.y));
    
    
    
//    cout << "LengthofAB" << lengthOfBC << endl;
    
    if(triangleArea < maximumAreaThreshold){
        cout<< "Layer 1" << endl;
        layer1 = true;
        layer2 = false;
        layer3 = false;
        layer4 = false;
        layer5 = false;
    }
    
    if(triangleArea > maximumAreaThreshold && triangleArea < maximumAreaThreshold*2 ){
        cout<< "Layer 1 + Layer2" << endl;
        //layer1 = true;
        layer2 = true;
        layer3 = false;
        layer4 = false;
        layer5 = false;
    }
    
    if(triangleArea > maximumAreaThreshold*2 && triangleArea < maximumAreaThreshold*3){
        cout<< "Layer 1 + Layer2 + Layer3" << endl;
        //layer1 = true;
        //layer2 = true;
        layer3 = true;
        layer4 = false;
        layer5 = false;
    }
    
    if(triangleArea > maximumAreaThreshold*3 && triangleArea < maximumAreaThreshold*4){
        cout<< "Layer 1 + Layer2 + Layer3 + Layer4" << endl;
        //layer1 = true;
//        layer2 = true;
//        layer3 = true;
        layer4 = true;
        layer5 = false;
    }
    
    if(triangleArea  > maximumAreaThreshold*5){
//        cout<< "Layer 1 + Layer2 + Layer3 + layer 4+ layer 5" << endl;
//        layer1 = true;
//        layer2 = true;
//        layer3 = true;
//        layer4 = true;
        layer5 = true;
    }
    }
       
}

//--------------------------------------------------------------
void TriangleVisual::draw(){
    
    list<Triangle*>::iterator triangleIt;
    for(triangleIt = triangleReceiver.triangles.begin(); triangleIt != triangleReceiver.triangles.end(); triangleIt++){
        ofSetColor(255, 0, 0, (*triangleIt)->tension * 255.0f);
        ofTriangle((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);

    float maxSideLength = 500;
    
    
    ofBackground(0, 0, 0);    
    ofSetColor(255);      
    ofSetLineWidth(2);
    
    if(lengthOfAB < maxSideLength && lengthOfBC < maxSideLength && lengthOfCA < maxSideLength){
        ofLine((*triangleIt)->A.x,(*triangleIt)->A.y, (*triangleIt)->B.x,(*triangleIt)->B.y);
        ofLine((*triangleIt)->B.x,(*triangleIt)->B.y,(*triangleIt)->C.x,(*triangleIt)->C.y);
        ofLine((*triangleIt)->C.x,(*triangleIt)->C.y, (*triangleIt)->A.x,(*triangleIt)->A.y);
    }

    
    
//    InCircle tekenen;
    ofSetColor(255,0, 0);
    ofSetLineWidth(1);
    ofNoFill();
    //ofCircle(triangleCenter, radius);
    
    if(layer1 == true){
      ofCircle(triangleCenter, radius/5);  
    }
    
    if(layer2 == true){
        ofCircle(triangleCenter, (radius/5*2));  
    }
    
    if(layer3 == true){
        ofCircle(triangleCenter, (radius/5*3));  
    }
    
    if(layer4 == true){
        ofCircle(triangleCenter, (radius/5*4));  
    }
    
    if(layer5 == true){
        ofCircle(triangleCenter, radius);  
    }
    }
    
}

//--------------------------------------------------------------
ofPoint TriangleVisual::getTriangleCenter(ofPoint A, ofPoint B, ofPoint C){
    
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    
    triangleCenter = ofPoint(((lengthOfBC*points[0]) + (lengthOfCA*points[1]) + (lengthOfAB*points[2]))/perimeter);   
    
    return(triangleCenter);
}

//--------------------------------------------------------------
float TriangleVisual::getMaximumRadiusInTriangle(ofPoint A, ofPoint B, ofPoint C){ 
    //Uitrekenen lengtes zijden
    
    
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    
    float semiPerimeter = perimeter/2;  
        
    float inCircle = sqrtf(((semiPerimeter-lengthOfAB)*(semiPerimeter-lengthOfBC)*(semiPerimeter-lengthOfCA))/semiPerimeter);
    
    return(inCircle);
    
    
    //Uitrekenen middenpunten van zijden
    
    ofPoint centerOfLineAB = ofPoint(((points[0].x + points[1].x) /2),((points[0].y + points[1].y) /2)); 
    ofPoint centerOfLineBC = ofPoint(((points[1].x + points[2].x) /2),((points[1].y + points[2].y) /2));
    ofPoint centerOfLineCA = ofPoint(((points[2].x + points[0].x) /2),((points[2].y + points[0].y) /2));

}
//--------------------------------------------------------------
float TriangleVisual::getTriangleArea(ofPoint A, ofPoint B, ofPoint C){
    
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    
    float semiPerimeter = perimeter/2;
    
    float area = sqrtl(semiPerimeter*((semiPerimeter-lengthOfAB)*(semiPerimeter-lengthOfBC)*(semiPerimeter-lengthOfCA)));

    return(area);
}

//--------------------------------------------------------------
float TriangleVisual::getMaximumTriangleArea(){ 
    
    float maxSideLength = 500;
    
    float maxSemiPerimeter = (maxSideLength*3)/2;
    
    float maxArea = sqrtl(maxSemiPerimeter*((maxSemiPerimeter-maxSideLength)*(maxSemiPerimeter-maxSideLength)*(maxSemiPerimeter-maxSideLength)));
    
    float areaThreshold = maxArea/5;
    
    return(areaThreshold);

}

//--------------------------------------------------------------
int TriangleVisual::getRandom(){

         
    random = ofRandom(0,4);
    
    return random;  
    //cout << "randomBase: " << randomBase[0] << endl;
}

//--------------------------------------------------------------
void TriangleVisual::keyPressed(int key){

}

//--------------------------------------------------------------
void TriangleVisual::keyReleased(int key){

}

//--------------------------------------------------------------
void TriangleVisual::mouseMoved(int x, int y ){
    mouseX = x;
    mouseY = y;
}

//--------------------------------------------------------------
void TriangleVisual::mouseDragged(int x, int y, int button){
    mouseMoved(x, y);
}

//--------------------------------------------------------------
void TriangleVisual::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void TriangleVisual::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void TriangleVisual::windowResized(int w, int h){

}

//--------------------------------------------------------------
void TriangleVisual::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void TriangleVisual::dragEvent(ofDragInfo dragInfo){ 

}