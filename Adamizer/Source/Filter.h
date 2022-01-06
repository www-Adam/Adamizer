/*
  ==============================================================================

    Filter.h
    Created: 21 Apr 2018 5:09:37pm
    Author:  Gerda GYURIS

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(Synth1AudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
    Synth1AudioProcessor& processor;
    
    Slider filterCutoffFreq;
    Slider filterResonance;
    
    ComboBox filterMenu;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterShapeValue;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> cutoffFreqValue;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resonanceValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
