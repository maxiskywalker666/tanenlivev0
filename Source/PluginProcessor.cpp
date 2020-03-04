/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TanenLiveV0AudioProcessor::TanenLiveV0AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                       .withOutput ("Output", AudioChannelSet::stereo(), true))
                        , lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))

#endif
{
    lastSampleRate = 44100;
    NormalisableRange<float> cutoffRange (20.0f, 20000.0f);
    NormalisableRange<float> resRange (1.0f, 5.0f);
    //tree.createAndAddParameter("cutoff", "Cutoff", "cutoff", cutoffRange, 600.0f, nullptr, nullptr);
    //tree.createAndAddParameter("resonance", "Resonance", "resonance", resRange, 1.0f, nullptr, nullptr);
    addParameter(mFilterCutoffParameter = new AudioParameterFloat("cutoff",
                                                            "Cutoff",
                                                            20.0f,
                                                            20000.0f,
                                                            600.0f));
    addParameter(mFilterResonanceParameter = new AudioParameterFloat("resonance",
                                                            "Resonance",
                                                            1.0f,
                                                            5.0f,
                                                            1.0f));
}

TanenLiveV0AudioProcessor::~TanenLiveV0AudioProcessor()
{
}

//==============================================================================
const String TanenLiveV0AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TanenLiveV0AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TanenLiveV0AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TanenLiveV0AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TanenLiveV0AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TanenLiveV0AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TanenLiveV0AudioProcessor::getCurrentProgram()
{
    return 0;
}

void TanenLiveV0AudioProcessor::setCurrentProgram (int index)
{
}

const String TanenLiveV0AudioProcessor::getProgramName (int index)
{
    return {};
}

void TanenLiveV0AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TanenLiveV0AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    lowPassFilter.prepare(spec);
    lowPassFilter.reset();
    
    fxReverbChain.prepare (spec);
    
    // Reverb
    
    
}

void TanenLiveV0AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TanenLiveV0AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainInputChannelSet() == AudioChannelSet::stereo() &&
        layouts.getMainOutputChannelSet() == AudioChannelSet::stereo()) {
        return true;
    } else {
        return false;
    }
  #endif
}
#endif

void TanenLiveV0AudioProcessor::updateFilter() {
    //float freq = *tree.getRawParameterValue("cutoff");
    float freq = *mFilterCutoffParameter;
    //float res = *tree.getRawParameterValue("resonance");
    float res = *mFilterResonanceParameter;
    *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate, freq, res);
}

void TanenLiveV0AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    dsp::AudioBlock<float> block (buffer); // [4]
    lastSampleRate = getSampleRate();
    updateFilter();
    lowPassFilter.process(dsp::ProcessContextReplacing<float> (block));

    auto blockToUse = block.getSubBlock ((size_t) buffer.getSample(0, 0), (size_t) buffer.getNumSamples()); // [5]
    auto contextToUse = juce::dsp::ProcessContextReplacing<float> (blockToUse);      // [6]
    fxReverbChain.process(contextToUse);                                                  // [7]
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        // ..do something to the data...

    }
}

//==============================================================================
bool TanenLiveV0AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TanenLiveV0AudioProcessor::createEditor()
{
    return new TanenLiveV0AudioProcessorEditor (*this);
}

//==============================================================================
void TanenLiveV0AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TanenLiveV0AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TanenLiveV0AudioProcessor();
}
