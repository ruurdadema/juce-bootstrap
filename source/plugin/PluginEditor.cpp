//
// Created by Ruurd Adema on 18/12/2020.
// Copyright (c) 2020 Owllab. All rights reserved.
//

#include "PluginEditor.h"

PluginEditor::PluginEditor(PluginProcessor& owningProcessor) : AudioProcessorEditor(owningProcessor)
{
    setSize(mMainView.getWidth(), mMainView.getHeight());
    addAndMakeVisible(mMainView);
}

PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics&) {}

void PluginEditor::resized()
{
    mMainView.setBounds(getLocalBounds());
}
