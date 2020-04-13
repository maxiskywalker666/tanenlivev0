/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TanenLiveV0AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TanenLiveV0AudioProcessorEditor (TanenLiveV0AudioProcessor&);
    ~TanenLiveV0AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TanenLiveV0AudioProcessor& processor;

    // TANEN LIVE General Parameters
    
    // FILTER Parameters
    Slider mFilterCutoffSlider; // OK - log scale to do
    Slider mFilterResSlider; // OK
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mFilterCutoffValue;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mFilterResValue;
    
    Slider mFilterAttackSlider;
    Slider mFilterDecaySlider;
    Slider mFilterSustainSlider;
    Slider mFilterReleaseSlider;
    ComboBox mFilterType; // OK
    // DELAY Parameters
    Slider mDelayDryWetSlider;
    Slider mDelayPitchSlider;
    Slider mDelayTimeSlider;
    Slider mDelayFeedbackSlider;
    ComboBox mReverseTimeType;
    // REVERB Parameters
    Slider mReverbDryWetSlider; // OK
    Slider mReverbPitchSlider;
    Slider mReverbRoomSizeSlider; // OK
    Slider mReverbWidthSlider; // OK - bug to fix
    // TANEN LIVE SEND Parameters
    Slider mSendLiveSlider;
    ComboBox mReverbSendType;
    ComboBox mDelaySendType;
    // If mDelayTimeSendType is ON the DelayTimeSlider value is applied to the value 0 of mSendLiveSlider.
    ComboBox mDelayTimeSendType;
    //TODO LFO Parameters
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TanenLiveV0AudioProcessorEditor)
};
