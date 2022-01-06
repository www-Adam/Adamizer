/*
  ==============================================================================

    Filter.cpp
    Created: 21 Apr 2018 5:09:37pm
    Author:  Gerda GYURIS

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"
//this will be similar to how i implemented oscillator
//==============================================================================
Filter::Filter(Synth1AudioProcessor& p) : processor(p)
{
    addAndMakeVisible(&filterMenu);
    filterMenu.setJustificationType(Justification::centred);
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);
    
    //filterCutoffFreq
    addAndMakeVisible(&filterCutoffFreq);
    filterCutoffFreq.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoffFreq.setRange(20.0, 10000.0);
    filterCutoffFreq.setValue(500.0);
    filterCutoffFreq.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutoffFreq.setSkewFactorFromMidPoint(1000.0);
    
    cutoffFreqValue = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterCutoffFreq", filterCutoffFreq);
    
    //filterResonance
    addAndMakeVisible(&filterResonance);
    filterResonance.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterResonance.setRange(1, 5);
    filterResonance.setValue(1);
    filterResonance.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    resonanceValue = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterResonance", filterResonance);
    
    
    filterShapeValue = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "filterShape", filterMenu);

    setSize(200, 200);
    
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    Rectangle<int> header (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    
    g.setColour(Colours::white);
    g.drawText("Filter", header, Justification::centredTop);
    
    Rectangle<float> area (25, 25, 150, 150);
    
    g.setColour(Colours::red);
//  g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    
    filterMenu.setBounds(area.removeFromTop(20));
    filterCutoffFreq.setBounds(30, 100, 70, 70);
    filterResonance.setBounds(100, 100, 70, 70);
}
