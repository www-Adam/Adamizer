/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.
 
    Things written by me are indicated

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth1AudioProcessor::Synth1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
tree (*this, nullptr)
#endif

//written by me
{
    //relay the value of the attack slider to the host for automation
    NormalisableRange<float> attackParamater(0.1f, 5000.0f);
    NormalisableRange<float> decayParamater(0.1f, 2000.0f);
    NormalisableRange<float> sustainParamater(0.0f, 1.0f);
    NormalisableRange<float> releaseParamater(0.1f, 5000.0f);
    
    tree.createAndAddParameter("attack", "Attack", "attack", attackParamater, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("decay", "Decay", "decay", decayParamater, 1.0f, nullptr, nullptr);
    tree.createAndAddParameter("sustain", "Sustain", "sustain", sustainParamater, 0.75f, nullptr, nullptr);
    tree.createAndAddParameter("release", "Release", "release", releaseParamater, 0.1f, nullptr, nullptr);
    
    NormalisableRange<float> wavetableParamater(0, 2);
    tree.createAndAddParameter("wavetable", "Wavetable", "wavetable", wavetableParamater, 0, nullptr, nullptr);
    
    NormalisableRange<float> cutoffFreqParamater(20.0f, 10000.0f);
    tree.createAndAddParameter("filterCutoffFreq", "FilterCutoffFreq", "filterCutoffFreq", cutoffFreqParamater, 500.0, nullptr, nullptr);
    
    NormalisableRange<float> resonanceParamater(1, 5);
    tree.createAndAddParameter("filterResonance", "FilterResonance", "filterResonance", resonanceParamater, 1, nullptr, nullptr);
    
    NormalisableRange<float> filterShapeValue(0, 2);
    tree.createAndAddParameter("filterShape", "FilterShape", "filterShape", filterShapeValue, 0, nullptr, nullptr);
    
    adamizerSynth.clearVoices();
    
    //here I specify that I want by synthesiser to be a polyphonic with 16 voices as opposed to mono (1 voice).
    for (int i = 0; i < 16; i++)
    {
        adamizerSynth.addVoice(new SynthVoice());
    }
    
    adamizerSynth.clearSounds();
    adamizerSynth.addSound(new SynthSound());
}
//end

Synth1AudioProcessor::~Synth1AudioProcessor()
{
}

//==============================================================================
const String Synth1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Synth1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Synth1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Synth1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Synth1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Synth1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Synth1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Synth1AudioProcessor::setCurrentProgram (int index)
{
}

const String Synth1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Synth1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================

//written by me
void Synth1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //to prevent crashing if sample rate in DAW were to change
    lastSampleRate = sampleRate;
    adamizerSynth.setCurrentPlaybackSampleRate(lastSampleRate); //sample rate will not constantly change
    reset();
    
    ignoreUnused(samplesPerBlock); //clears unused samples from last key press
}
//end

void Synth1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Synth1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Synth1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    //play around here
    
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    buffer.clear(); //written by me
    
    adamizerSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples()); //written by me
    
   // std::cout << attackTime << std::endl;
    
    for (int i = 0; i < adamizerSynth.getNumVoices(); i++)
    {
        if ((adamizerVoice = dynamic_cast<SynthVoice*>(adamizerSynth.getVoice(i))))
        {
            adamizerVoice->getParamater(tree.getRawParameterValue("attack"),
                                        tree.getRawParameterValue("decay"),
                                        tree.getRawParameterValue("sustain"),
                                        tree.getRawParameterValue("release"));
            
            adamizerVoice->getOscillatorTable(tree.getRawParameterValue("wavetable"));
            
            adamizerVoice->getFilterParamater(tree.getRawParameterValue("filterShape"),
                                              tree.getRawParameterValue("filterCutoffFreq"),
                                              tree.getRawParameterValue("filterResonance"));
        }
    }
    
}

//==============================================================================
bool Synth1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Synth1AudioProcessor::createEditor()
{
    return new Synth1AudioProcessorEditor (*this);
}

//==============================================================================
void Synth1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or Value classes
    // as intermediaries to make it easy to save and load complex data.
}

void Synth1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Synth1AudioProcessor();
}
