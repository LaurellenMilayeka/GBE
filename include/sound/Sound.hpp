#pragma once

namespace Engine {

  /* Sweep frequency change formula : X(t) = X(t-1) +/- X(t-1)/2^n */
  /* Sound length : (64-t1)*(1/256) */
  
  class Audio {

    static Audio *_singleton;

    Audio();

    uint8_t sweepFrequency;
    
    double GetSweepTime();
    
  public:
    
    ~Audio();

    static Audio *Instance();

    
  };
};
