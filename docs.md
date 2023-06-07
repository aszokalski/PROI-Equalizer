# Simple Equalizer VST Plugin written in JUCE

## Documentation

### Build & Setup

For info on building and setting up project go to [README](/README.md)

### File Structure
- [/lib](/lib) - the directory for the JUCE library files
- [/src](/src) - all the source code
  - [/PluginProcessor](/src/PluginProcessor) - the directory for the plugin logic and audio processing
    - [PluginProcessor.cpp](/src/PluginProcessor/PluginProcessor.cpp) - the source code file for the plugin logic and audio processing
    - [PluginProcessor.h](/src/PluginProcessor/PluginProcessor.h) - the header file for the plugin logic and audio processing
  - [/PluginEditor](/src/PluginEditor) - the directory for the plugin GUI and general layout
    - [PluginEditor.cpp](/src/PluginEditor/PluginEditor.cpp) - the source code file for the plugin GUI and general layout
    - [PluginEditor.h](/src/PluginEditor/PluginEditor.h) - the header file for the plugin GUI and general layout
  - [/SpectrumAnalyser](/src/SpectrumAnalyser) - the directory for the spectrum analyser
      - [SpectrumAnalyser.cpp](/src/SpectrumAnalyser/SpectrumAnalyser.cpp) - the source code with spectrum analyser logic and user output
      - [SpectrumAnalyser.h](/src/SpectrumAnalyser/SpectrumAnalyser.h) - the header file for the spectrum analyser
  - [util.cpp](/src/util.cpp) - source code for utility objects. It lets you configure some parameters of the EQ.
  - [util.h](/src/util.h) - header file for utility objects.
- [/tests](/tests) - the directory for the test files
- [CMakeLists.txt](CMakeLists.txt) - the CMake file for the project
- [docs.md](docs.md) - this file (project documentation)
- [README.md](README.md) - the general project README file

### Basic plugin structure graph

![Plugin structure](/plugin_structure.png)
