//
// Created by kkrol on 31.05.2023.
//
#include <catch2/catch_test_macros.hpp>
#include "PluginEditorTest.h"
#include "../src/PluginEditor/PluginEditor.h"

TEST_CASE("Is testing even working", "[test]") {
    REQUIRE(1 == 1);
}

TEST_CASE("TestLowSlider", "[test]") {
    EqualizerEditorTest editorTest;
    REQUIRE(editorTest.testLowSliderStartValue() == 0.5f);
}

TEST_CASE("TestMidSlider", "[test]") {
    EqualizerEditorTest editorTest;
    REQUIRE(editorTest.testMidSliderStartValue() == 0.5f);
}

TEST_CASE("TestHighSlider", "[test]") {
    EqualizerEditorTest editorTest;
    REQUIRE(editorTest.testHighSliderStartValue() == 0.5f);
}

TEST_CASE("TestLowSliderMaxValue", "[test]") {
    EqualizerEditorTest editorTest;
    REQUIRE(editorTest.testLowSliderMaxValue() == 1.0f);
}

TEST_CASE("TestMidSliderMaxValue", "[test]") {
    EqualizerEditorTest editorTest;
    REQUIRE(editorTest.testMidSliderMaxValue() == 1.0f);
}

TEST_CASE("TestHighSliderMaxValue", "[test]") {
    EqualizerEditorTest editorTest;
    REQUIRE(editorTest.testHighSliderMaxValue() == 1.0f);
}

TEST_CASE("TestLowSliderMinValue", "[test]") {
    EqualizerEditorTest editorTest;
    REQUIRE(editorTest.testLowSliderMinValue() == 0.0f);
}

TEST_CASE("TestMidSliderMinValue", "[test]") {
    EqualizerEditorTest editorTest;
    REQUIRE(editorTest.testMidSliderMinValue() == 0.0f);
}

TEST_CASE("TestHighSliderMinValue", "[test]") {
    EqualizerEditorTest editorTest;
    REQUIRE(editorTest.testHighSliderMinValue() == 0.0f);
}
//
//TEST_CASE("TestLowSliderDoubleClick", "[test]") {
//    EqualizerEditorTest editorTest;
//    REQUIRE(editorTest.testLowSliderDoubleClick() == 0.5f);
//}
//
//TEST_CASE("TestMidSliderDoubleClick", "[test]") {
//    EqualizerEditorTest editorTest;
//    REQUIRE(editorTest.testMidSliderDoubleClick() == 0.5f);
//}
//
//TEST_CASE("TestHighSliderDoubleClick", "[test]") {
//    EqualizerEditorTest editorTest;
//    REQUIRE(editorTest.testHighSliderDoubleClick() == 0.5f);
//}

