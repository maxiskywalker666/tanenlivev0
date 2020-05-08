/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h" // include juce_core that include juce_UniTest
// #include "/Applications/JUCE/modules/juce_core/unit_tests/juce_UnitTest.h"
#define MAX_DELAY_TIME 2

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
    void testSendFx();
    void linkPerformance();
    float lin_interp(float sample_x, float sample_x1, float inPhase);
    
    // TODO TEST
    static void runTest();

private:
    // FILTER PARAMETERS
    AudioParameterInt* mFilterTypeParameter; // 0
    AudioParameterFloat* mFilterCutoffParameter;
    AudioParameterFloat* mFilterResParameter;
    // REVERB PARAMETERS
    AudioParameterFloat* mReverbDryParameter;
    AudioParameterFloat* mReverbWetParameter;
    AudioParameterFloat* mReverbSizeParameter; // 5
    // SEND PARAMETERS
    AudioParameterBool* mCutoffSendParameter; // 6
    AudioParameterBool* mResSendParameter;
    AudioParameterBool* mReverbWetSendParameter;
    AudioParameterBool* mReverbSizeSendParameter; // 9
    // PERFORMANCE PARAMETERS
    AudioParameterFloat* mPerfParameter; // 10
    // DELAY PARAMETERS
    AudioParameterFloat* mDelayDryWetParameter; // 11
    AudioParameterFloat* mDelayDepthParameter;
    AudioParameterFloat* mDelayRateParameter;
    AudioParameterFloat* mDelayPhaseOffsetParameter;
    AudioParameterFloat* mDelayFeedbackParameter; // 15
    // DELAY SEND PARAMETERS
    AudioParameterBool* mDelayDryWetSendParameter; // 16
    AudioParameterBool* mDelayDepthSendParameter; // 17
    AudioParameterBool* mDelayRateSendParameter; // 18
    AudioParameterBool* mDelayFeedbackSendParameter; //19


    // VARIABLES
    float lastSampleRate;
    // Filter objects
    dsp::ProcessorDuplicator<dsp::IIR::Filter <float> , dsp::IIR::Coefficients <float>> iIRFilter;
    float freqMin;
    float freqMax;
    float resMin;
    float resMax;
    // Reverb init
    juce::dsp::ProcessorChain<juce::dsp::Reverb> fxReverbChain;
    // Delay objects
    float mLFOPhase;
    float mDelayTimeSmoothed;
    float mFeedbackLeft;
    float mFeedbackRight;
    float mDelayTimeInSamples;
    float mDelayReadHead;
    int mCircularBufferWriteHead;
    int mCircularBufferLength;
    float* mCircularBufferLeft;
    float* mCircularBufferRight;
    float rateMin;
    float rateMax;
    float feedbackMax;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TanenLiveV0AudioProcessor)
};
