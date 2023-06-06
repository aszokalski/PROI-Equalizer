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

void SpectrumAnalyser::drawFrame(juce::Graphics& g) {
    int numPoints = scopeSize; // Number of data points

    auto width = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();

    // Generate the smooth curve using a cubic B-spline
    juce::Path path;
    float tStep = 1.0f / static_cast<float>(numPoints/3 - 1);

    path.startNewSubPath(0.0f, juce::jmap(scopeData[0], 0.0f, 1.0f, static_cast<float>(height), 0.0f));

    for (int i = 0; i < numPoints - 3; i += 3){
        float t0 = static_cast<float>(i) * tStep;
        float t1 = static_cast<float>(i + 1) * tStep;
        float t2 = static_cast<float>(i + 2) * tStep;
        float t3 = static_cast<float>(i + 3) * tStep;

        float x0 = juce::jmap(t0, 0.0f, 1.0f, 0.0f, static_cast<float>(width));
        float x1 = juce::jmap(t1, 0.0f, 1.0f, 0.0f, static_cast<float>(width));
        float x2 = juce::jmap(t2, 0.0f, 1.0f, 0.0f, static_cast<float>(width));
        float x3 = juce::jmap(t3, 0.0f, 1.0f, 0.0f, static_cast<float>(width));

        float y0 = juce::jmap(scopeData[i], 0.0f, 1.0f, static_cast<float>(height), 0.0f);
        float y1 = juce::jmap(scopeData[i + 1], 0.0f, 1.0f, static_cast<float>(height), 0.0f);
        float y2 = juce::jmap(scopeData[i + 2], 0.0f, 1.0f, static_cast<float>(height), 0.0f);
        float y3 = juce::jmap(scopeData[i + 3], 0.0f, 1.0f, static_cast<float>(height), 0.0f);

        path.cubicTo(x1, y1, x2, y2, x3, y3);
    }

    g.setColour(juce::Colours::white);
    g.strokePath(path, juce::PathStrokeType(1.0f));
}



void SpectrumAnalyser::setLastSampleRate(double sampleRate) noexcept {
    lastSampleRate = sampleRate;
}
