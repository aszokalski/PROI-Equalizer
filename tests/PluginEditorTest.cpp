//
// Created by kkrol on 05.06.2023.
//

#include "PluginEditorTest.h"
#include "../src/PluginEditor/PluginEditor.h"
#include "../src/PluginProcessor/PluginProcessor.h"

//EqualizerEditorTest::EqualizerEditorTest() {
//    EqualizerProcessor processor;
//    EqualizerEditor editor(processor);
//}

float EqualizerEditorTest::testLowSliderStartValue(){
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    return editor.lowSlider.getValue();
}

float EqualizerEditorTest::testMidSliderStartValue(){
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    return editor.midSlider.getValue();
}

float EqualizerEditorTest::testHighSliderStartValue(){
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    return editor.highSlider.getValue();
}

float EqualizerEditorTest::testLowSliderMaxValue(){
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    return editor.lowSlider.getMaximum();
}

float EqualizerEditorTest::testMidSliderMaxValue(){
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    return editor.midSlider.getMaximum();
}

float EqualizerEditorTest::testHighSliderMaxValue(){
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    return editor.highSlider.getMaximum();
}

float EqualizerEditorTest::testLowSliderMinValue(){
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    return editor.lowSlider.getMinimum();
}

float EqualizerEditorTest::testMidSliderMinValue(){
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    return editor.midSlider.getMinimum();
}

float EqualizerEditorTest::testHighSliderMinValue(){
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    return editor.highSlider.getMinimum();
}

//float EqualizerEditorTest::testLowSliderDoubleClick(){
//    EqualizerProcessor processor;
//    EqualizerEditor editor(processor);
//    editor.lowSlider.setValue(0.0f);
//    // Simulate the double-click event
//    const int doubleClickTime = juce::DoubleClickDetector::getDoubleClickTime();
//    const juce::Point<int> mousePosition(10, 10);
//
//    // First click
//    editor.lowSlider.mouseDown(juce::MouseEvent(juce::MouseEvent::leftButton, mousePosition, juce::ModifierKeys::noModifiers));
//    slider.mouseUp(juce::MouseEvent(juce::MouseEvent::leftButton, mousePosition, juce::ModifierKeys::noModifiers));
//
//    juce::Time::waitForMillisecondCounter(juce::Time::getMillisecondCounter() + doubleClickTime + 1);
//
//    // Second click
//    slider.mouseDown(juce::MouseEvent(juce::MouseEvent::leftButton, mousePosition, juce::ModifierKeys::noModifiers));
//    slider.mouseUp(juce::MouseEvent(juce::MouseEvent::leftButton, mousePosition, juce::ModifierKeys::noModifiers));
//
//
//
//    return editor.lowSlider.getValue();
//}

//float EqualizerEditorTest::testMidSliderDoubleClick(){
//    EqualizerProcessor processor;
//    EqualizerEditor editor(processor);
//    editor.midSlider.setValue(0.0f);
//    editor.midSlider.mouseDoubleClick();
//    return editor.midSlider.getValue();
//}
//
//float EqualizerEditorTest::testHighSliderDoubleClick(){
//    EqualizerProcessor processor;
//    EqualizerEditor editor(processor);
//    editor.highSlider.setValue(0.0f);
//    editor.highSlider.mouseDoubleClick();
//    return editor.highSlider.getValue();
//}

