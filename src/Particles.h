//
//  Particles.h
//  OpticalFlow
//
//  Created by 村上 晋太郎 on 2014/07/30.
//
//

#ifndef __OpticalFlow__Particles__
#define __OpticalFlow__Particles__

#include <iostream>
#include "ofxCv.h"
#include "Particle.h"

class Particles {
  ofxCv::FlowFarneback * _farneback;
  Particle ** _array;
  int _arraySize;

public:
  Particles(ofxCv::FlowFarneback * farneback);
  ~Particles();
  void releaseArray();
  void generate();
  void update();
  void draw();
};

#endif /* defined(__OpticalFlow__Particles__) */
