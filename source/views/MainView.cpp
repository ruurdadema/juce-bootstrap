//
// Created by Ruurd Adema on 18/12/2020.
// Copyright (c) 2020 Owllab. All rights reserved.
//

#include "MainView.h"

MainView::MainView()
{
    setSize (800, 400);
}

void MainView::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawFittedText ("Hello world!", getLocalBounds(), juce::Justification::centred, 1);
}

void MainView::resized() {}
