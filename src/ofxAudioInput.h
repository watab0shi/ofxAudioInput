#pragma once

#include "ofMain.h"


// ofxAudioInput
//--------------------------------------------------------------------------------
class ofxAudioInput
{
private:
  ofSoundStream             soundStream;
  float                     volume;
  float                     smoothedVol;
  vector< vector< float > > channels;
  bool                      bSetup;
  
  
public:
  ofxAudioInput() : volume( 0. ), smoothedVol( 0. ), bSetup( false )
  {}
  
  void printDeviceList();
  void setup( ofBaseApp* _app, int _inChannels, int _bufferSize );
  void audioIn( float* _input, int _bufferSize, int _nChannels );
  
  void start();
  void stop();
  
  float        getVolume(){    return volume; }
  const float* getVolumeRef(){ return &volume; }

  const vector< float >& getChannel( int _index )
  {
    return channels.at( _index );
  }
};
