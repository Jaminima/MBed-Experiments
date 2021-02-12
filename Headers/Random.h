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

    bool RandomBool(){
        float t1 = *noiseSource;

        wait_ns(1);

        float t2 = *noiseSource;

        return signbit(t1-t2);
    }
};