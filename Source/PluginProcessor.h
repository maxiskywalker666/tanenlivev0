/*
  ==============================================================================

    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
 
    Plugin developed by Maxime Boiron starting from March 2020
    Name : Tanen Live Machine
    Version : V0
    GitHub project: https://github.com/maxiskywalker666/tanenlivev0.git

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/** TanenLiveV0AudioProcessor class:
                            - contains a bunch of inherited juce methods to treat audio & midi
                            - declares all the variables and methods for the processor
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

    void extracted(AudioBuffer<float> &buffer, int i, float *leftChannel, float *rightChannel);
    
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

    //==============================================================================
    void updateFilter();
    void updateReverb();
    void updateDelay(AudioBuffer<float> &buffer, int i, float *leftChannel, float *rightChannel);
    void testSendFx();
    void linkPerformance();
    float linInterp(float sample_x, float sample_x1, float inPhase);

private:
    // FILTER PARAMETERS
    AudioParameterInt* mFilterTypeParameter;
    AudioParameterFloat* mFilterCutoffParameter;
    AudioParameterFloat* mFilterResParameter;
    // REVERB PARAMETERS
    AudioParameterFloat* mReverbDryParameter;
    AudioParameterFloat* mReverbWetParameter;
    AudioParameterFloat* mReverbSizeParameter;
    // SEND PARAMETERS
    AudioParameterBool* mCutoffSendParameter;
    AudioParameterBool* mResSendParameter;
    AudioParameterBool* mReverbWetSendParameter;
    AudioParameterBool* mReverbSizeSendParameter;
    // PERFORMANCE PARAMETERS
    AudioParameterFloat* mPerfParameter;
    // DELAY PARAMETERS
    AudioParameterFloat* mDelayDryWetParameter;
    AudioParameterFloat* mDelayDepthParameter;
    AudioParameterFloat* mDelayRateParameter;
    AudioParameterFloat* mXTremFeedbackParameter;
    AudioParameterFloat* mDelayFeedbackParameter;
    // DELAY SEND PARAMETERS
    AudioParameterBool* mDelayDryWetSendParameter;
    AudioParameterBool* mDelayDepthSendParameter;
    AudioParameterBool* mDelayRateSendParameter;
    AudioParameterBool* mDelayFeedbackSendParameter;

    // VARIABLES
    float lastSampleRate;
    int maxDelayTime = 2;
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
    float xTremFeedbackMax;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TanenLiveV0AudioProcessor)
};
