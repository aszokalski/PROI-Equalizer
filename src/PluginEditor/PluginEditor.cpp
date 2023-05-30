//
// Created by Adam Szokalski on 10/05/2023.
//

#include "PluginEditor.h"
#include "../PluginProcessor/PluginProcessor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
        : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    lowSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    lowSlider.setRange(0.0f, 1.0f, 0.01f);
    lowSlider.setValue(0.5f);
    lowSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(lowSlider);

    midSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    midSlider.setRange(0.0f, 1.0f, 0.01f);
    midSlider.setValue(0.5f);
    midSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(midSlider);

    highSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    highSlider.setRange(0.0f, 1.0f, 0.01f);
    highSlider.setValue(0.5f);
    highSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(highSlider);

    setSize (600, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void AudioPluginAudioProcessorEditor::resized()
{
    lowSlider.setBounds(100, 80, 50, getHeight() - 100);
    midSlider.setBounds(300, 80, 50, getHeight() - 100);
    highSlider.setBounds(500, 80, 50, getHeight() - 100);
}