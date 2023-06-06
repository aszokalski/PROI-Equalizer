////
//// Created by kkrol on 04.06.2023.
////
//
#ifndef PROI_EQUALIZER_PROJECT_PLUGINEDITORTEST_H
#define PROI_EQUALIZER_PROJECT_PLUGINEDITORTEST_H

#include "../src/PluginEditor/PluginEditor.h"
#include "../src/PluginProcessor/PluginProcessor.h"

class EqualizerEditorTest {
public:
//    EqualizerEditorTest();
    float testLowSliderStartValue();
    float testMidSliderStartValue();
    float testHighSliderStartValue();
    float testLowSliderMaxValue();
    float testMidSliderMaxValue();
    float testHighSliderMaxValue();
    float testLowSliderMinValue();
    float testMidSliderMinValue();
    float testHighSliderMinValue();
//    float testLowSliderDoubleClick();
//    float testMidSliderDoubleClick();
//    float testHighSliderDoubleClick();
//private:
//    EqualizerEditor editor;
//    EqualizerProcessor processor;

};

#endif //PROI_EQUALIZER_PROJECT_PLUGINEDITORTEST_H
