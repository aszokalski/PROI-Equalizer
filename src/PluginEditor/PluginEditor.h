//
// Created by Adam Szokalski on 10/05/2023.
//

#ifndef PROI_EQUALIZER_PROJECT_PLUGINEDITOR_H
#define PROI_EQUALIZER_PROJECT_PLUGINEDITOR_H

#include "../PluginProcessor/PluginProcessor.h"
#include <JuceHeader.h>

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerEditor)
};

class AnalyserComponent : public juce::Component
{
public:
    enum
    {
        fftOrder = 11,
        fftSize = 1 << fftOrder,
        scopeSize = 512
    };
    AnalyserComponent() : forwardFFT(fftOrder), window(fftSize, juce::dsp::WindowingFunction<float>::hann) {};
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill);
    void pushNextSampleIntoFifo (float sample) noexcept;
    void drawNextFrameOfSpectrum();
    void timerCallback();
    void drawFrame (juce::Graphics& g);
private:
    juce::dsp::FFT forwardFFT;
    juce::dsp::WindowingFunction<float> window;

    float fifo[fftSize]{};
    float fftData[2 * fftSize]{};
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    float scopeData[scopeSize]{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalyserComponent)
};

#endif //PROI_EQUALIZER_PROJECT_PLUGINEDITOR_H
