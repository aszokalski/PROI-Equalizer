//
// Created by Adam Szokalski on 10/05/2023.
//

#include "PluginProcessor.h"
#include "../PluginEditor/PluginEditor.h"

//==============================================================================
EqualizerProcessor::EqualizerProcessor()
        : AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
), lowPassFilter(juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 300, 5.0f)),
lowPeakFilter(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000, 5.0f, 1.0f)),
highPassFilter(juce::dsp::IIR::Coefficients<float>::makeHighPass(44100, 20000, 5.0f)),
highPeakFilter(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000, 5.0f, 1.0f)),
midPeakFilter(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 20000, 5.0f, 1.0f))
{

}

EqualizerProcessor::~EqualizerProcessor()
= default;

//==============================================================================
const juce::String EqualizerProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EqualizerProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool EqualizerProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool EqualizerProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double EqualizerProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EqualizerProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int EqualizerProcessor::getCurrentProgram()
{
    return 0;
}

void EqualizerProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String EqualizerProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void EqualizerProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void EqualizerProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;

    if (spectrumAnalyserPtr != nullptr)
        spectrumAnalyserPtr->setLastSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec{};
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<unsigned int>(samplesPerBlock);
    spec.numChannels = static_cast<unsigned int>(getTotalNumOutputChannels());

    lowPassFilter.prepare(spec);
    lowPassFilter.reset();

    highPassFilter.prepare(spec);
    highPassFilter.reset();

    lowPeakFilter.prepare(spec);
    lowPeakFilter.reset();

    highPeakFilter.prepare(spec);
    highPeakFilter.reset();

    midPeakFilter.prepare(spec);
    midPeakFilter.reset();
}

void EqualizerProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool EqualizerProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}

void EqualizerProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                       juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block(buffer);
    updateFilters();
    lowPassFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    highPassFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    lowPeakFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    highPeakFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    midPeakFilter.process(juce::dsp::ProcessContextReplacing<float>(block));

    if(spectrumAnalyserPtr != nullptr)
        spectrumAnalyserPtr->pushBuffer(buffer);
}

//==============================================================================
bool EqualizerProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EqualizerProcessor::createEditor()
{
    return new EqualizerEditor (*this);
}

//==============================================================================
void EqualizerProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void EqualizerProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

juce::AudioProcessorValueTreeState::ParameterLayout EqualizerProcessor::createParameters() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("LOW",
                                                                 "LOW",
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
                                                                 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("HIGH",
                                                                    "HIGH",
                                                                    juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
                                                                    0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MID",
                                                                    "MID",
                                                                    juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
                                                                    0.5f));

    return { params.begin(), params.end() };
}

void EqualizerProcessor::updateFilters() const {
    float l_f = *state.getRawParameterValue("LOW");
    float h_f = *state.getRawParameterValue("HIGH");
    float m_f = *state.getRawParameterValue("MID");

    // low cut = high pass
    *highPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, FrequencyBorders::getLowFreq(l_f));
    // high cut = low pass
    *lowPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate, FrequencyBorders::getHighFreq(h_f));
    // low peak
    *lowPeakFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, FrequencyBorders::Min, inverseRootTwo, juce::Decibels::decibelsToGain(fmax((l_f - 0.5f) * 50.0f, 0.1f)));
    // high peak
    *highPeakFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, FrequencyBorders::Max, inverseRootTwo, juce::Decibels::decibelsToGain(fmax((h_f - 0.5f) * 50.0f, 0.1f)));
    // mid peak
    *midPeakFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, FrequencyBorders::MidHigh, inverseRootTwo, juce::Decibels::decibelsToGain(m_f*25.0f));

}

void EqualizerProcessor::setSpectrumAnalyser(SpectrumAnalyser *spectrumAnalyser) {
    this->spectrumAnalyserPtr = spectrumAnalyser;
    spectrumAnalyserPtr->setLastSampleRate(lastSampleRate);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EqualizerProcessor();
}