//
//  Particles.cpp
//  OpticalFlow
//
//  Created by 村上 晋太郎 on 2014/07/30.
//
//

#include "Particles.h"
#define STEP_SIZE 4

Particles::Particles(ofxCv::FlowFarneback * farneback) {
  _farneback = farneback;
  _array = NULL;
  _arraySize = 0;
}

Particles::~Particles() {
  if (_array) {
    releaseArray();
  }
}

void Particles::releaseArray() {
  for (int i = 0; i < _arraySize; i++) {
    delete _array[i];
    _array[i] = NULL;
  }
  free(_array);
  _array = NULL;
  _arraySize = 0;
}

void Particles::generate() {
  if (_array) {
    releaseArray();
  }
  
  _arraySize = (_farneback->getFlow().rows / STEP_SIZE) * (_farneback->getFlow().cols / STEP_SIZE);
  _array = (Particle **)malloc(sizeof(Particle *) * _arraySize);
  int num = 0;
  
  ofRectangle rect(0, 0, ofGetWidth(), ofGetHeight());
  ofVec2f offset(rect.x,rect.y);
  ofVec2f scale(rect.width/_farneback->getFlow().cols, rect.height/_farneback->getFlow().rows);
  for(int y = 0; y < _farneback->getFlow().rows; y += STEP_SIZE) {
    for(int x = 0; x < _farneback->getFlow().cols; x += STEP_SIZE) {
      ofVec2f cur = ofVec2f(x, y) * scale + offset;
      ofVec2f off = _farneback->getFlowOffset(x, y) * scale + offset;
      _array[num] = new Particle(cur, off, _farneback);
      num++;
    }
  }
}

void Particles::update() {
  for (int i = 0; i < _arraySize; i++){
    _array[i]->update();
  }
}

void Particles::draw() {
  for (int i = 0; i < _arraySize; i++){
    _array[i]->draw();
  }
}