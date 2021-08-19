//
// Created by Ruurd Adema on 18/12/2020.
// Copyright (c) 2020 Owllab. All rights reserved.
//

#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginProcessor::PluginProcessor() {}

PluginProcessor::~PluginProcessor() {}

void PluginProcessor::prepareToPlay (double, int) {}

void PluginProcessor::releaseResources() {}

bool PluginProcessor::isBusesLayoutSupported (const juce::AudioProcessor::BusesLayout& layouts) const
{
    return AudioProcessor::isBusesLayoutSupported (layouts);
}

void PluginProcessor::processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) {}

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

bool PluginProcessor::hasEditor() const
{
    return true;
}

const juce::String PluginProcessor::getName() const
{
    return mProgramName;
}

bool PluginProcessor::acceptsMidi() const
{
    return false;
}

bool PluginProcessor::producesMidi() const
{
    return false;
}

bool PluginProcessor::isMidiEffect() const
{
    return false;
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0;
}

int PluginProcessor::getNumPrograms()
{
    return 1;
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram (int) {}

const juce::String PluginProcessor::getProgramName (int)
{
    return mProgramName;
}

void PluginProcessor::changeProgramName (int, const juce::String&) {}

void PluginProcessor::getStateInformation (juce::MemoryBlock&) {}

void PluginProcessor::setStateInformation (const void*, int) {}

// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
