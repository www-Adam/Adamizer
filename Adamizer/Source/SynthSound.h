/*
  ==============================================================================

    SynthSound.h
    Created: 13 Apr 2018 8:31:37am
    Author:  Adam Gyuris

    all written by me unless specified otherwise
  ==============================================================================
*/

//includes basic setup for synthesiser

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
    
    bool appliesToChannel (int midiNoteNumber) override
    {
        return true;
    }
    
};
