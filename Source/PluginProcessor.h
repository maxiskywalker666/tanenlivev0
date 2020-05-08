/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h" // include juce_core that include juce_UniTest
// #include "/Applications/JUCE/modules/juce_core/unit_tests/juce_UnitTest.h"

//==============================================================================
/**
*/
class TanenLiveV0AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TanenLiveV0AudioProcessor();
    ~TanenLiveV0AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void updateFilter();
    void updateReverb();
    
    //void buttonClicked(Button* button) override;
    void sendFx();
    //AudioProcessorValueTreeState tree;
    static void runTest();

private:
    // FILTER PARAMETERS
    AudioParameterInt* mFilterTypeParameter;
    AudioParameterFloat* mFilterCutoffParameter;
    AudioParameterFloat* mFilterResonanceParameter;
    // REVERB PARAMETERS
    AudioParameterFloat* mReverbDryParameter;
    AudioParameterFloat* mReverbWetParameter;
    AudioParameterFloat* mReverbRoomSizeParameter;
    // SEND PARAMETERS
    AudioParameterBool* mCutoffSendParameter;
    AudioParameterBool* mResSendParameter;
    AudioParameterBool* mReverbWetSendParameter;
    AudioParameterBool* mReverbSizeSendParameter;

    float lastSampleRate;
    dsp::ProcessorDuplicator<dsp::IIR::Filter <float> , dsp::IIR::Coefficients <float>> iIRFilter;
    enum
    {
        reverbIndex             // [2]
    };
 
    juce::dsp::ProcessorChain<juce::dsp::Reverb> fxReverbChain; // [1]
    //dsp::Reverb::Reverb();
    //dsp::Reverb::Parameters();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TanenLiveV0AudioProcessor)
};
