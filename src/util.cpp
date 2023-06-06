//
// Created by Adam Szokalski on 06/06/2023.
//

#include "util.h"

namespace util {
    EQParametersList eqParametersList;

    EQParametersList::EQParametersList() {
        eqParametersList.emplace_back("Default", std::make_unique<FrequencyBorders<60, 250, 5000, 20000>>());
        eqParametersList.emplace_back("Custom", std::make_unique<FrequencyBorders<20, 100, 10000, 20000>>());
        eqParametersList.emplace_back("Custom 2", std::make_unique<FrequencyBorders<200, 800, 7000, 10000>>());
    }

    juce::StringArray EQParametersList::getNames() {
        juce::StringArray names;

        for (auto &pair : eqParametersList) {
            names.add(pair.first);
        }

        return names;
    }
}