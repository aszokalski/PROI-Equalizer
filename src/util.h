//
// Created by Adam Szokalski on 04/06/2023.
//

#ifndef PROI_EQUALIZER_PROJECT_UTIL_H
#define PROI_EQUALIZER_PROJECT_UTIL_H

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <juce_core/juce_core.h>

namespace util {
    static constexpr float inverseRootTwo = static_cast<float > (0.70710678118654752440L);

    class FrequencyBordersBase {
    public:
        virtual float getMin() = 0;
        virtual float getMax() = 0;
        virtual float getMidHigh() = 0;
        virtual float getLowMid() = 0;

        virtual float getLowFreq(float lowGain) = 0;
        virtual float getHighFreq(float highGain) = 0;
        virtual ~FrequencyBordersBase() = default;
    };

    template<int freq1, int freq2, int freq3, int freq4>
    struct FrequencyBorders : public FrequencyBordersBase {
        constexpr static float Min = static_cast<float>(freq1);
        constexpr static float LowMid = static_cast<float>(freq2);
        constexpr static float MidHigh= static_cast<float>(freq3);
        constexpr static float Max= static_cast<float>(freq4);

        constexpr static float HighRange=Max-MidHigh;
        constexpr static float LowRange=LowMid-Min;

        inline float getMin() override{ return Min; }
        inline float getMax() override{ return Max; }
        inline float getMidHigh() override{ return MidHigh; }
        inline float getLowMid() override{ return LowMid; }

        inline float getLowFreq(float lowGain) override{ return LowMid-lowGain*LowRange; }
        inline float getHighFreq(float highGain) override{ return MidHigh+highGain*HighRange; }
    };

    struct EQParametersList {
        std::vector<std::pair<std::string, std::unique_ptr<FrequencyBordersBase>>> eqParametersList;

        EQParametersList();

        juce::StringArray getNames();

    };

    extern EQParametersList eqParametersList;
}

#endif //PROI_EQUALIZER_PROJECT_UTIL_H
