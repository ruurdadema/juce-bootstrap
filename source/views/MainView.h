//
// Created by Ruurd Adema on 18/12/2020.
// Copyright (c) 2020 Owllab. All rights reserved.
//

#pragma once

#include <JuceHeader.h>

class MainView : public juce::Component
{
public:
    MainView();
    void paint (juce::Graphics& g) override;
    void resized() override;
};
