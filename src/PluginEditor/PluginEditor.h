//
// Created by Adam Szokalski on 10/05/2023.
//

#ifndef PROI_EQUALIZER_PROJECT_PLUGINEDITOR_H
#define PROI_EQUALIZER_PROJECT_PLUGINEDITOR_H

#include "../PluginProcessor/PluginProcessor.h"
#include "../SpectrumAnalyser/SpectrumAnalyser.h"


//==============================================================================
class EqualizerEditor  : public juce::AudioProcessorEditor
{
private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using SliderAttachmentPtr = std::unique_ptr<SliderAttachment>;
public:
    explicit EqualizerEditor (EqualizerProcessor&);
    ~EqualizerEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider lowSlider;
    juce::Slider midSlider;
    juce::Slider highSlider;

    juce::Label lowLabel;
    juce::Label midLabel;
    juce::Label highLabel;

    SliderAttachmentPtr lowAttachment;
    SliderAttachmentPtr midAttachment;
    SliderAttachmentPtr highAttachment;

    EqualizerProcessor& processorRef;
    SpectrumAnalyser spectrumAnalyser;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerEditor)
};

#endif //PROI_EQUALIZER_PROJECT_PLUGINEDITOR_H
