//
// Created by Adam Szokalski on 10/05/2023.
//

#include "PluginEditor.h"

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

    processorRef.setSpectrumAnalyser(&spectrumAnalyser);
    addAndMakeVisible(spectrumAnalyser);

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

    spectrumAnalyser.setBounds(10, 10, 580, 320);
}