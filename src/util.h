//
// Created by Adam Szokalski on 04/06/2023.
//

#ifndef PROI_EQUALIZER_PROJECT_UTIL_H
#define PROI_EQUALIZER_PROJECT_UTIL_H

static constexpr float inverseRootTwo = static_cast<float > (0.70710678118654752440L);

struct FrequencyBorders {
    constexpr static float Min=80.0f;
    constexpr static float LowMid=250.0f;
    constexpr static float MidHigh=5000.0f;
    constexpr static float Max=20000.0f;

    constexpr static float HighRange=Max-MidHigh;
    constexpr static float LowRange=LowMid-Min;

    inline static float getLowFreq(float lowGain){
        return LowMid-lowGain*LowRange;
    }

    inline static float getHighFreq(float highGain){
        return MidHigh+highGain*HighRange;
    }
};

#endif //PROI_EQUALIZER_PROJECT_UTIL_H
