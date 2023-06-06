cmake_minimum_required(VERSION 3.15)

project(PROI_EQUALIZER_PROJECT VERSION 0.0.1)

add_subdirectory(lib/juce)

juce_add_plugin(ProiEqualizer
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...

        PLUGIN_MANUFACTURER_CODE Juce               # A four-character manufacturer id with at least one upper-case character
        PLUGIN_CODE Eqa0                            # A unique four-character plugin id with exactly one upper-case character
        FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
        PRODUCT_NAME "PROI Equalizer")              # The name of the final executable, which can differ from the target name

juce_generate_juce_header(ProiEqualizer)

target_sources(ProiEqualizer
        PRIVATE
        src/PluginProcessor/PluginProcessor.cpp
        src/PluginEditor/PluginEditor.cpp
        src/SpectrumAnalyser/SpectrumAnalyser.cpp
        src/util.cpp
        )

target_compile_definitions(ProiEqualizer
        PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)


target_link_libraries(ProiEqualizer
        PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

add_subdirectory(tests)