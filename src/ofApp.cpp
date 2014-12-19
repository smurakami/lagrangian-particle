#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

#define CAMERA_WIDTH 320
#define CAMERA_HEIGHT 240

//--------------------------------------------------------------
void ofApp::setup(){
  // Initialize cv
  camera.setDeviceID(1);
  camera.initGrabber(CAMERA_WIDTH, CAMERA_HEIGHT);
  
  // GUI
  gui.setup();
  gui.add(pyrScale.setup("pyrScale", .5, 0, 1));
  gui.add(levels.setup("levels", 4, 1, 8));
  gui.add(winsize.setup("levels", 8, 4, 64));
  gui.add(iterations.setup("iterations", 2, 1, 8));
  gui.add(polyN.setup("polyN", 7, 5, 10));
  gui.add(polySigma.setup("polySigma", 1.5, 1.1, 2));
  gui.add(OPTFLOW_FARNEBACK_GAUSSIAN.setup("OPTFLOW_FARNEBACK_GAUSSIAN", false));
  
  gui.add(useFarneback.setup("useFarneback", true));
  gui.add(winSize.setup("winSize", 32, 4, 64));
  gui.add(maxLevel.setup("maxLevel", 3, 0, 8));
  
  gui.add(levels.setup("maxFeatures", 200, 1, 1000));
  gui.add(qualityLevel.setup("maxFeatures", 0.01, 0.001, 0.02));
  gui.add(minDistance.setup("minDistance", 4, 1, 16));
  
  curFlow = &farneback;
  
  particles = new Particles(&farneback);
  
}

//--------------------------------------------------------------
void ofApp::update(){
  camera.update();
  if(camera.isFrameNew()){
    if(useFarneback){  // dense optical flow by farneback
      curFlow = &farneback;
      farneback.setPyramidScale(pyrScale);
      farneback.setNumLevels(levels);
      farneback.setWindowSize(winsize);
      farneback.setPolyN(polyN);
      farneback.setPolySigma(polySigma);
      farneback.setUseGaussian(OPTFLOW_FARNEBACK_GAUSSIAN);
    } else { // sparse optical flow by image pyramid
      curFlow = &pyrLk;
      pyrLk.setMaxFeatures(maxFeatures);
      pyrLk.setQualityLevel(qualityLevel);
      pyrLk.setMinDistance(minDistance);
      pyrLk.setWindowSize(winSize);
      pyrLk.setMaxLevel(maxLevel);
    }
    curFlow->calcOpticalFlow(camera);
    
    if(useFarneback){  // calc particle;
//      ofRectangle rect(0, 0, ofGetWidth(), ofGetHeight());
//      ofVec2f offset(rect.x,rect.y);
//      ofVec2f scale(rect.width/farneback.getFlow().cols, rect.height/farneback.getFlow().rows);
//      int stepSize = 4; //TODO: make class-level parameteric
//      for(int y = 0; y < farneback.getFlow().rows; y += stepSize) {
//        for(int x = 0; x < farneback.getFlow().cols; x += stepSize) {
//          ofVec2f cur = ofVec2f(x, y) * scale + offset;
//          ofVec2f off = farneback.getFlowOffset(x, y) * scale + offset;
//          ofLine(cur, cur + off);
//        }
//      }
    }
    
    particles->update();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  
  ofSetColor(255);
  camera.draw(0, 0, ofGetWidth(), ofGetHeight());
  ofSetColor(100, 255, 200);
  curFlow->draw(0, 0, ofGetWidth(), ofGetHeight());
  ofSetColor(100, 200, 255);
  particles->draw();
  
//  gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 'g') {
    particles->generate();
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
