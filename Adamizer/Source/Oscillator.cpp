/*
  ==============================================================================

    Oscillator.cpp
    Created: 20 Apr 2018 8:37:11pm
    Author:  Adam Gyuris

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(Synth1AudioProcessor& p) : processor(p)
{
    oscillatorMenu.setJustificationType(Justification::centred);
    
    addAndMakeVisible(oscillatorMenu);
    oscillatorMenu.addListener(this);
    oscillatorMenu.addItem("Sine", 1);
    oscillatorMenu.addItem("Saw", 2);
    oscillatorMenu.addItem("Square", 3);
    
    selectedWavetable = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetable", oscillatorMenu);
    
    setSize(200, 200);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    Rectangle<int> header (0, 10, getWidth(), 20);
    
    g.fillAll(Colours::black);
    
    g.setColour(Colours::white);
    g.drawText("Oscillator", header, Justification::centredTop);
    
    Rectangle<float> area (25, 25, 150, 150);
    g.setColour(Colours::red);
//  g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    oscillatorMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(ComboBox* box)
{
    
}
