/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

    Things written by me are indicated
 
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth1AudioProcessorEditor::Synth1AudioProcessorEditor (Synth1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor(p), oscillatorUi(p), envelopeUi(p), filterUi(p)
{
    addAndMakeVisible(&oscillatorUi);
    addAndMakeVisible(&envelopeUi);
    addAndMakeVisible(&filterUi);
    
    setSize (600, 200);
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor()
{
}

//==============================================================================
void Synth1AudioProcessorEditor::paint (Graphics& g)
{
   g.fillAll(Colours::black);
}

void Synth1AudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    oscillatorUi.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envelopeUi.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterUi.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
}
