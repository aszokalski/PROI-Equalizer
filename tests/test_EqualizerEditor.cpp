//
// Created by kkrol on 31.05.2023.
//
#include <catch2/catch_test_macros.hpp>
#include "../src/PluginProcessor/PluginProcessor.h"
#include "./src/PluginEditor/PluginEditor.h"

TEST_CASE("Test lowSlider value", "[lowSlider]")
{
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    editor.lowSlider.setValue(0.5f);
    REQUIRE(editor.lowSlider.getValue() == 0.5f);
}

TEST_CASE("Test lowSlider range"), "[lowSlider]")
{
    EqualizerProcessor processor;
    EqualizerEditor editor(processor);
    editor.lowSlider.setRange(0.0f, 1.0f, 0.01f);
    REQUIRE(editor.lowSlider.getMinimum() == 0.0f);
    REQUIRE(editor.lowSlider.getMaximum() == 1.0f);
    REQUIRE(editor.lowSlider.getInterval() == 0.01f);
}