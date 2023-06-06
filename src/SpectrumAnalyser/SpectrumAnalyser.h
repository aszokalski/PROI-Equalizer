//
// Created by Adam Szokalski on 03/06/2023.
//

#ifndef PROI_EQUALIZER_PROJECT_SPECTRUMANALYSER_H
#define PROI_EQUALIZER_PROJECT_SPECTRUMANALYSER_H
#include <JuceHeader.h>

//==============================================================================
class SpectrumAnalyser   : public juce::Component,
                           private juce::Timer
{
public:
    SpectrumAnalyser();
    ~SpectrumAnalyser() override = default;


    //==============================================================================
    void paint (juce::Graphics& g) override; // from Component

    void timerCallback() override; // from Timer

    void pushBuffer (juce::AudioBuffer<float>& buffer) noexcept;

    void setLastSampleRate (double sampleRate) noexcept;

    void setMaxFrequency (double maxFreq) noexcept;

private:
    void updateScope();

    void drawFrame (juce::Graphics& g);

    enum
    {
        fftOrder  = 11,
        fftSize   = 1 << fftOrder,
        scopeSize = 48
    };

    juce::dsp::FFT forwardFFT;
    juce::dsp::WindowingFunction<float> window;

    float fifo [fftSize]{};
    float fftData [2 * fftSize]{};
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    float scopeData [scopeSize]{};

    double lastSampleRate = 44100.0f;
    double maxFrequency = 20000.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumAnalyser)
};


#endif //PROI_EQUALIZER_PROJECT_SPECTRUMANALYSER_H
