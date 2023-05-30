//
// Created by Adam Szokalski on 10/05/2023.
//

#ifndef PROI_EQUALIZER_PROJECT_PLUGINEDITOR_H
#define PROI_EQUALIZER_PROJECT_PLUGINEDITOR_H

#include "../PluginProcessor/PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider lowSlider;
    juce::Label lowLabel;
    juce::Slider midSlider;
    juce::Label midLabel;
    juce::Slider highSlider;
    juce::Label highLabel;

    AudioPluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};


#endif //PROI_EQUALIZER_PROJECT_PLUGINEDITOR_H
