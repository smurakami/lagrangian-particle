//
//  Particle.h
//  OpticalFlow
//
//  Created by 村上 晋太郎 on 2014/07/08.
//
//

#ifndef __OpticalFlow__Particle__
#define __OpticalFlow__Particle__

#include <iostream>
#include "ofMain.h"
#include "ofxCv.h"

class Particle {
  float _x;
  float _y;
  float _vx;
  float _vy;
  int _age;
  ofxCv::FlowFarneback * _farneback;
  
public:
  Particle(ofVec2f pos, ofVec2f speed, ofxCv::FlowFarneback * _farneback);
  ~Particle();
  void update();
  void draw();
};
#endif /* defined(__OpticalFlow__Particle__) */
