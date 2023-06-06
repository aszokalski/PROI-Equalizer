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
    REQUIRE(editorTest.testLowSlider() == 0.5f);
}