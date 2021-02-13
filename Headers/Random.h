#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

class Random{
private:
    AnalogIn *noiseSource;

public:

    Random(AnalogIn *_source){
        noiseSource = _source;
    }

    float RandomSmallFloat(){
        float t1 = *noiseSource;

        wait_ns(1);

        float t2 = *noiseSource;

        return abs(t1 - t2);
    }

    float RandomFloat(){
        return RandomSmallFloat() * 10000;
    }

    char RandomRange(char max){
        return ((char)RandomFloat())%max;
    }

    char RandomRangeFromBool(char max){ //Biases towards max/2
        char i=0;
        
        for (char j=max;j>0;j--) i+=RandomBool();
        return i;
    }

    bool RandomBool(){
        float t1 = *noiseSource;

        wait_ns(1);

        float t2 = *noiseSource;

        return signbit(t1-t2);
    }
};