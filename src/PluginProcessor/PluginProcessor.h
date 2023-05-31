//
// Created by Adam Szokalski on 10/05/2023.
//

#ifndef PROI_EQUALIZER_PROJECT_PLUGINPROCESSOR_H
#define PROI_EQUALIZER_PROJECT_PLUGINPROCESSOR_H



#include <juce_audio_processors/juce_audio_processors.h>

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

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerProcessor)
};


#endif //PROI_EQUALIZER_PROJECT_PLUGINPROCESSOR_H
