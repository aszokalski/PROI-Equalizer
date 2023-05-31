//
// Created by Adam Szokalski on 10/05/2023.
//

#include "PluginEditor.h"
#include "../PluginProcessor/PluginProcessor.h"

//==============================================================================
EqualizerEditor::EqualizerEditor (EqualizerProcessor& p)
        : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    lowSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    lowSlider.setRange(0.0f, 1.0f, 0.01f);
    lowSlider.setValue(0.5f);
    lowSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    lowSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::lightblue);
    lowSlider.setDoubleClickReturnValue(true, 0.5f);
    addAndMakeVisible(lowSlider);

    lowLabel.setText("Low", juce::dontSendNotification);
    lowLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    lowLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lowLabel);

    lowAttachment = std::make_unique<SliderAttachment>(processorRef.state, "LOW", lowSlider);

    midSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    midSlider.setRange(0.0f, 1.0f, 0.01f);
    midSlider.setValue(0.5f);
    midSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    midSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::lightblue);
    midSlider.setDoubleClickReturnValue(true, 0.5f);
    addAndMakeVisible(midSlider);

    midLabel.setText("Mid", juce::dontSendNotification);
    midLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    midLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(midLabel);

    midAttachment = std::make_unique<SliderAttachment>(processorRef.state, "MID", midSlider);

    highSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    highSlider.setRange(0.0f, 1.0f, 0.01f);
    highSlider.setValue(0.5f);
    highSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    highSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::lightblue);
    highSlider.setDoubleClickReturnValue(true, 0.5f);
    addAndMakeVisible(highSlider);

    highLabel.setText("High", juce::dontSendNotification);
    highLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    highLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(highLabel);

    highAttachment = std::make_unique<SliderAttachment>(processorRef.state, "HIGH", highSlider);

    setSize (600, 600);
}

EqualizerEditor::~EqualizerEditor()
{
}

//==============================================================================
void EqualizerEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    juce::Rectangle<int> waveformBox(10, 10, 580, 320);
    g.setColour(juce::Colours::lightblue);
    g.fillRect(waveformBox);
    g.setColour(juce::Colours::darkblue);
}


void EqualizerEditor::resized()
{
    lowSlider.setBounds(105, 360, 60, 200);
    midSlider.setBounds(270, 360, 60, 200);
    highSlider.setBounds(435, 360, 60, 200);

    lowLabel.setBounds(lowSlider.getX(), lowSlider.getY() + 205, lowSlider.getWidth(), 20);
    midLabel.setBounds(midSlider.getX(), midSlider.getY() + 205, midSlider.getWidth(), 20);
    highLabel.setBounds(highSlider.getX(), highSlider.getY() + 205, highSlider.getWidth(), 20);
}

void AnalyserComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    if (bufferToFill.buffer->getNumChannels() > 0)
    {
        auto* channelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);

        for (auto i = 0; i < bufferToFill.numSamples; ++i)
            pushNextSampleIntoFifo (channelData[i]);
    }
}

void AnalyserComponent::pushNextSampleIntoFifo(float sample) noexcept
{
    // if the fifo contains enough data, set a flag to say
    // that the next frame should now be rendered..
    if (fifoIndex == fftSize)               // [11]
    {
        if (! nextFFTBlockReady)            // [12]
        {
            juce::zeromem (fftData, sizeof (fftData));
            memcpy (fftData, fifo, sizeof (fifo));
            nextFFTBlockReady = true;
        }
        fifoIndex = 0;
    }
    fifo[fifoIndex++] = sample;
}

void AnalyserComponent::drawNextFrameOfSpectrum()
{
    // first apply a windowing function to our data
    window.multiplyWithWindowingTable (fftData, fftSize);       // [1]
    // then render our FFT data..
    forwardFFT.performFrequencyOnlyForwardTransform (fftData);  // [2]
    auto mindB = -100.0f;
    auto maxdB =    0.0f;

    for (int i = 0; i < scopeSize; ++i)                         // [3]
    {
        auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - (float) i / (float) scopeSize) * 0.2f);
        auto fftDataIndex = juce::jlimit (0, fftSize / 2, (int) (skewedProportionX * (float) fftSize * 0.5f));
        auto level = juce::jmap (juce::jlimit (mindB, maxdB, juce::Decibels::gainToDecibels (fftData[fftDataIndex])
                                                             - juce::Decibels::gainToDecibels ((float) fftSize)),
                                 mindB, maxdB, 0.0f, 1.0f);
        scopeData[i] = level;                                   // [4]
    }
}

void AnalyserComponent::timerCallback()
{
    if (nextFFTBlockReady) {
        drawNextFrameOfSpectrum();
        nextFFTBlockReady = false;
        AnalyserComponent::repaint();
    }
}

void AnalyserComponent::drawFrame(juce::Graphics &g)
{
    for (int i = 1; i < scopeSize; ++i)
    {
        auto width  = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight();

        g.drawLine ({ (float) juce::jmap (i - 1, 0, scopeSize - 1, 0, width),
                      juce::jmap (scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
                      (float) juce::jmap (i, 0, scopeSize - 1, 0, width),
                      juce::jmap (scopeData[i], 0.0f, 1.0f, (float) height, 0.0f) });
    }
}