/*
  ==============================================================================

    Oscillator.h
    Created: 20 Apr 2018 8:37:11pm
    Author:  Adam Gyuris

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/


class Oscillator    : public Component, private ComboBox::Listener
{
public:
    Oscillator(Synth1AudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged (ComboBox*) override; //change in the combo box

private:
    Synth1AudioProcessor& processor;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> selectedWavetable;
    
    ComboBox oscillatorMenu;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
