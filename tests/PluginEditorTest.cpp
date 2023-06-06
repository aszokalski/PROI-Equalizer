//
// Created by kkrol on 05.06.2023.
//

#include "PluginEditorTest.h"
#include "../src/PluginEditor/PluginEditor.h"
#include "../src/PluginProcessor/PluginProcessor.h"

float EqualizerEditorTest::testLowSlider(){
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    editor.lowSlider.setValue(0.5f);
    return editor.lowSlider.getValue();
}