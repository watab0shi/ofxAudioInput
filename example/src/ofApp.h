#pragma once

#include "ofMain.h"
#include "ofxAudioInput.h"


// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
  
  void audioIn( float* _input, int _bufferSize, int _nChannels );
  
  float         w, h, hw, hh;
  ofxAudioInput audioInput;
  int           bufferSize;
};
