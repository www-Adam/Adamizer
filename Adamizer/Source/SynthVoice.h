/*
  ==============================================================================

    SynthVoice.h
    Created: 13 Apr 2018 8:31:58am
    Author:  Adam Gyuris

    all written by me unless specified otherwise
  ==============================================================================
*/
//mix up order of functions
//includes basic setup for synthesiser
//signal goes oscillator -> envelope -> filter
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h" //using Maximilian sound library

using namespace std;

class SynthVoice : public SynthesiserVoice
{
public:
    
    //canPlaySound function written by JUCE
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    //======
    
    //osc
    
    double setOscillatorType ()
    {
        if (waveform == 0)
        {
            return osc1.sinewave(freq);
        }
        
        if (waveform == 1)
        {
            return osc1.saw(freq);
        }
        
        if (waveform == 2)
        {
            return osc1.square(freq);
        }
        
        else
        {
            return osc1.sinewave(freq);
        }
    }
    
    void getOscillatorTable (float* selection)
    {
        waveform = *selection;
    }
    
    //======
    
    //envelope
    
    void getParamater(float* attackValue, float* decayValue, float* sustainValue, float* releaseValue)
    {
        env1.setAttack(*attackValue); //convert float to double
        env1.setDecay(*decayValue);
        env1.setSustain(*sustainValue);
        env1.setRelease(*releaseValue);
    }
    
    double setEnvelope()
    {
        return env1.adsr(setOscillatorType(), env1.trigger); //takes signal from oscillator then applies volume envelope
    }
    
    //======
    
    //filter
    
    void getFilterParamater(float* filterShape, float* filterCutoffFreq, float* filterResonance)
    {
        filterSelected = *filterShape;
        cutoffFreq = *filterCutoffFreq;
        resonance = *filterResonance;
    }
    
    double setFilterShape()
    {
        if (filterSelected == 0) //low pass
            return filter1.lores(setEnvelope(), cutoffFreq, resonance); //low pass
        
        if (filterSelected == 1) //high pass
            return filter1.hires(setEnvelope(), cutoffFreq, resonance); //high pass
        
        if (filterSelected == 2) //band pass
            return filter1.bandpass(setEnvelope(), cutoffFreq, resonance);
        
        else
            return filter1.lores (setEnvelope(), cutoffFreq, resonance); //takes signal from envelope component then applies filter
    }
    
    //=======
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        env1.trigger = 1;
        //convert recieved midi note to corresponding freqeuncy
        freq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        //cout << midiNoteNumber << endl;
        
        level = velocity;
    }
    
    //=======
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        env1.trigger = 0;
        
        allowTailOff = true;
        
        if (velocity == 0)
        {
            clearCurrentNote();
        }
        
        
    }
    
    //=======
    
    void pitchWheelMoved (int newPitchWheelValue) override
    {
        
    }
    
    //=======
    
    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }
    
    //=======
    
    
    
    //=======
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override
    {
    
        //algo for generating sound
        for (int sample = 0; sample < numSamples; sample++)
        {
            //oscillator1 in action
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                outputBuffer.addSample(channel, startSample, setFilterShape() * 0.3f); //outputs sound calculated above
            }
            ++startSample;
        }
        
        
    }
    
    //=======
    
private:
    int waveform;
    double freq;
    double level;
    
    maxiOsc osc1; //creating oscillator 1
    maxiEnv env1; //volume envelope for osc1
    maxiFilter filter1; //creating a filter for osc1
    
    int filterSelected;
    float cutoffFreq;
    float resonance;
    
};
