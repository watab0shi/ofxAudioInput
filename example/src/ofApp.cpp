#include "ofApp.h"


// setup
//----------------------------------------
void ofApp::setup()
{
  w  = ofGetWidth();
  h  = ofGetHeight();
  hw = w * .5;
  hh = h * .5;
  
  audioInput.printDeviceList();
  
  bufferSize = 1024;
  audioInput.setup( this, 1, bufferSize );
  
  ofBackground( 0 );
  ofSetCircleResolution( 64 );
}

// update
//----------------------------------------
void ofApp::update()
{
  
}

// draw
//----------------------------------------
void ofApp::draw()
{
  ofSetColor( 255, 128 );
  
  // volume
  ofFill();
  ofDrawCircle( hw, hh, audioInput.getVolume() * hh );
  
  // wave
  float xStep = w / audioInput.getChannel( 0 ).size();
  int   i     = 0;
  ofNoFill();
  ofBeginShape();
  for( auto& v : audioInput.getChannel( 0 ) )
  {
    float wav = v * hh;
    ofVertex( i * xStep, hh + wav );
    
    ++i;
  }
  ofEndShape();
}

// audioIn
//----------------------------------------
void ofApp::audioIn( float* _input, int _bufferSize, int _nChannels )
{
  audioInput.audioIn( _input, _bufferSize, _nChannels );
}
