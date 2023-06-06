Include(FetchContent)
# Fetching Catch2
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1 # or later versions if you wish
)

FetchContent_makeAvailable(Catch2)

juce_generate_juce_header(ProiEqualizer)

set(TEST_FILES
        test_main.cpp
        test_EqualizerEditor.cpp
        test_EqualizerProcessor.cpp)
add_executable(${PROJECT_NAME}-tests ${TEST_FILES})

target_link_libraries(${PROJECT_NAME}-tests
        PRIVATE
        Catch2::Catch2WithMain
        juce::juce_audio_utils
        juce::juce_dsp
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

target_sources(${PROJECT_NAME}-tests
        PRIVATE
        PluginEditorTest.cpp
        PluginProcessorTest.cpp
        ../src/PluginEditor/PluginEditor.cpp
        ../src/PluginProcessor/PluginProcessor.cpp)

# Discovering tests
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
include(CTest)
catch_discover_tests(${PROJECT_NAME}-tests)
