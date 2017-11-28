#include "ofxAudioInput.h"


void ofxAudioInput::printDeviceList()
{
  soundStream.printDeviceList();
}

// setup
//----------------------------------------
void ofxAudioInput::setup( ofBaseApp* _app, int _inChannels, int _bufferSize )
{
  soundStream.setup( _app, 0, _inChannels, 44100, _bufferSize, 4 );
  
  volume = 0.0;
  
  channels.assign( _inChannels, vector< float >() );
  
  for( int i = 0; i < _inChannels; ++i )
  {
    channels.at( i ).assign( _bufferSize, 0.0 );
  }
  
  bSetup = true;
}


// audioReceived
//----------------------------------------
void ofxAudioInput::audioIn( float* _input, int _bufferSize, int _nChannels )
{
  if( !bSetup )
  {
    ofLog() << "[ofxAudioInput] audioReceived : call setup() at first!" ;
    return;
  }
  
  float curVol = 0.0;
  int   i      = 0;
  int   j      = 0;
  for( auto& c : channels )
  {
    for( auto& v : c )
    {
      int idx = ( j * _nChannels ) + i;
      v       = _input[ idx ] * ( 1.0 / _nChannels );
      curVol += v * v;
      
      ++j;
    }
    ++i;
  }
  
  // calculate avarage of RMS
  curVol /= _bufferSize * _nChannels;
  
  // calculate root of RMS
  curVol = sqrt( curVol );
  
  smoothedVol *= 0.93;
  smoothedVol += 0.07 * curVol;
  
  // map volume 0 ~ 1
  volume = ofMap( smoothedVol, 0.0, 0.17, 0.0, 1.0, false );
}


// start
//----------------------------------------
void ofxAudioInput::start()
{
  soundStream.start();
}

// stop
//----------------------------------------
void ofxAudioInput::stop()
{
  soundStream.stop();
}
