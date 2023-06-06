//
// Created by Adam Szokalski on 10/05/2023.
//

#include "PluginEditor.h"
#include "../util.h"

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

    flavourComboBox.addItemList(util::eqParametersList.getNames(), 1);

    flavourComboBox.setJustificationType(juce::Justification::centred);
    flavourComboBox.setSelectedItemIndex(0);

    flavourComboBox.onChange = [this] {
        auto index = flavourComboBox.getSelectedItemIndex();
        auto &pair = util::eqParametersList.eqParametersList[static_cast<unsigned long>(index)];
        spectrumAnalyser.setMaxFrequency(pair.second->getMax());
    };
    addAndMakeVisible(flavourComboBox);

    flavourLabel.setText("Flavour", juce::dontSendNotification);
    flavourLabel.setFont(juce::Font(15.0f, juce::Font::bold));
    flavourLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(flavourLabel);

    flavourAttachment = std::make_unique<ComboBoxAttachment>(processorRef.state, "TYPE", flavourComboBox);

    processorRef.setSpectrumAnalyser(&spectrumAnalyser);
    addAndMakeVisible(spectrumAnalyser);

    setSize (600, 600);
}

EqualizerEditor::~EqualizerEditor() = default;

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
    flavourComboBox.setBounds(290, 10, 80, 20);
    flavourComboBox.toFront(false);

    lowLabel.setBounds(lowSlider.getX(), lowSlider.getY() + 205, lowSlider.getWidth(), 20);
    midLabel.setBounds(midSlider.getX(), midSlider.getY() + 205, midSlider.getWidth(), 20);
    highLabel.setBounds(highSlider.getX(), highSlider.getY() + 205, highSlider.getWidth(), 20);
    flavourLabel.setBounds(flavourComboBox.getX() - 80, flavourComboBox.getY(), flavourComboBox.getWidth(), 20);
    flavourLabel.toFront(false);

    spectrumAnalyser.setBounds(10, 10, 580, 320);
}