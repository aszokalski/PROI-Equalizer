//
// Created by Adam Szokalski on 10/05/2023.
//

#ifndef PROI_EQUALIZER_PROJECT_PLUGINPROCESSOR_H
#define PROI_EQUALIZER_PROJECT_PLUGINPROCESSOR_H


#include <juce_dsp/juce_dsp.h>
#include <juce_audio_processors/juce_audio_processors.h>

static constexpr float inverseRootTwo = static_cast<float > (0.70710678118654752440L);

struct FrequencyBorders {
    constexpr static float Min=20.0f;
    constexpr static float LowMid=250.0f;
    constexpr static float MidHigh=8000.0f;
    constexpr static float Max=20000.0f;

    constexpr static float HighRange=Max-MidHigh;
    constexpr static float MidRange=MidHigh-LowMid;
    constexpr static float LowRange=LowMid-Min;

    inline static float getLowFreq(float lowGain){
        return LowMid-lowGain*LowRange;
    }

    inline static float getMidFreq(float midGain){
        return LowMid+midGain*MidRange;
    }

    inline static float getHighFreq(float highGain){
        return MidHigh+highGain*HighRange;
    }
};

//==============================================================================
class EqualizerProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    EqualizerProcessor();
    ~EqualizerProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    juce::AudioProcessorValueTreeState state {*this, nullptr, "Parameters", createParameters()};

    void updateFilters() const;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerProcessor)
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> lowPassFilter;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> lowPeakFilter;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highPassFilter;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> highPeakFilter;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> midPeakFilter;
    double lastSampleRate;
};

#endif //PROI_EQUALIZER_PROJECT_PLUGINPROCESSOR_H
