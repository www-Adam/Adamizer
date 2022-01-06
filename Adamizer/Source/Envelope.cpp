/*
  ==============================================================================

    Envelope.cpp
    Created: 21 Apr 2018 4:39:01pm
    Author:  Adam Gyuris

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(Synth1AudioProcessor& p) : processor(p)
{
    //attack slider
    addAndMakeVisible(&attackSlider);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setValue(0.1f);
    attackSlider.setRange(0.1f, 5000.f); //in milliseconds
    //attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    
    //decay slider
    addAndMakeVisible(&decaySlider);
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setValue(1.0f);
    decaySlider.setRange(1.0f, 2000.0f);
    
    //sustain slider
    addAndMakeVisible(&sustainSlider);
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setValue(0.0f);
    sustainSlider.setRange(0.0f, 1.0f);
    
    //release slider
    addAndMakeVisible(&releaseSlider);
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setValue(0.1f);
    releaseSlider.setRange(0.1f, 5000.0f);
    
    //set up automation
    attackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);
    decayTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);
    sustainTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);
    
    setSize(200, 200);
    
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    Rectangle<int> header (0, 10, getWidth(), 20);
    
    g.fillAll(Colours::black);
    
    g.setColour(Colours::white);
    g.drawText("Envelope", header, Justification::centredTop);
    
    g.drawText("A", 53, 150, 20, 20, Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20, Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20, Justification::centredTop);
    
    Rectangle<float> area (25, 25, 150, 150);
    g.setColour(Colours::red);
//  g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderWidth = 25;
    int sliderHeight = 175;
    
    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(-20));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(-20));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(-20));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(-20));
}

