//
// Created by Adam Szokalski on 03/06/2023.
//

#include "SpectrumAnalyser.h"

SpectrumAnalyser::SpectrumAnalyser() :  forwardFFT (fftOrder),
                                        window (fftSize, juce::dsp::WindowingFunction<float>::rectangular)
{
    setOpaque (true);
    startTimerHz (30);
    setSize (700, 500);
}

void SpectrumAnalyser::paint(juce::Graphics &g) {
    g.fillAll (juce::Colours::black);

    g.setOpacity (1.0f);
    g.setColour (juce::Colours::white);
    drawFrame (g);
}

void SpectrumAnalyser::timerCallback()
{
    if (nextFFTBlockReady)
    {
        updateScope();
        nextFFTBlockReady = false;
        juce::Component::repaint();
    }
}

void SpectrumAnalyser::pushBuffer(juce::AudioBuffer<float> &buffer) noexcept     {
    auto* channelData = buffer.getReadPointer (0);

    for (auto i = 0; i < buffer.getNumSamples(); ++i){
        if (fifoIndex == fftSize)
        {
            if (! nextFFTBlockReady)
            {
                juce::zeromem (fftData, sizeof (fftData));
                memcpy (fftData, fifo, sizeof (fifo));
                nextFFTBlockReady = true;
            }

            fifoIndex = 0;
        }

        fifo[fifoIndex++] = channelData[i];
    }
}

void SpectrumAnalyser::updateScope() {
    // Windowing function
    window.multiplyWithWindowingTable(fftData, fftSize);

    // Fast Fourier Transform
    forwardFFT.performFrequencyOnlyForwardTransform(fftData);

    auto mindB = -100.0f;
    auto maxdB = 0.0f;

    int numBands = fftSize / 2;

    // Calculate the maximum index in the FFT data corresponding to 20kHz
    int maxIndex = (int)((float)numBands * 20000.0f / lastSampleRate);

    for (int i = 0; i < scopeSize; ++i)
    {
        int fftDataIndex = (int)((float)i / (float)scopeSize * (float)maxIndex);
        auto dB = juce::jlimit(
                mindB,
                maxdB,
                juce::Decibels::gainToDecibels(fftData[fftDataIndex])
                - juce::Decibels::gainToDecibels((float)fftSize)
        );

        auto level = juce::jmap(dB,mindB, maxdB, 0.0f, 1.0f);

        scopeData[i] = level;
    }
}

void SpectrumAnalyser::drawFrame(juce::Graphics &g) {
    for (int i = 1; i < scopeSize; ++i)
    {
        auto width  = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight();

        g.drawLine ({ (float) juce::jmap (i - 1, 0, scopeSize - 1, 0, width),
                      juce::jmap (scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
                      (float) juce::jmap (i,     0, scopeSize - 1, 0, width),
                      juce::jmap (scopeData[i],     0.0f, 1.0f, (float) height, 0.0f) });
    }
}

void SpectrumAnalyser::setLastSampleRate(double sampleRate) noexcept {
    lastSampleRate = sampleRate;
}
