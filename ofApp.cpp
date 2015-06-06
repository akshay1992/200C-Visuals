#include "ofApp.h"
#include <iostream>

int xRes = 600;
int yRes = 600;

int mouseX;
int mouseY;

bool display_pixel_values = false;

//--------------------------------------------------------------
void ofApp::setup(){
    fractal.init(xRes, yRes);
    fractal.setMouseVars(mouseX, mouseY);

}

//--------------------------------------------------------------
void ofApp::update(){
    fractal.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fractal.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key)
	{
		case 'q': 
			std::exit(0);
			break;
        case 'v':
            fractal.display_values = !fractal.display_values;
            break;
        default: break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}