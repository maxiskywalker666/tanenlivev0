/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================


TanenLiveV0AudioProcessorEditor::TanenLiveV0AudioProcessorEditor (TanenLiveV0AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    /*addAndMakeVisible(headerFrame);
    addAndMakeVisible(footerFrame);
    addAndMakeVisible(filterFrame);
    addAndMakeVisible(reverbFrame);
    addAndMakeVisible(delayFrame);
    addAndMakeVisible(performanceFrame);*/
    // IMAGE
    auto t1000Image = ImageCache::getFromMemory(BinaryData::T1000_png, BinaryData::T1000_pngSize);
    if (!t1000Image.isNull())
        mImageComponent.setImage(t1000Image, RectanglePlacement::stretchToFit);
    else
        jassert(!t1000Image.isNull());
    addAndMakeVisible(mImageComponent);
    
    // WINDOW SIZE
    setSize (pluginWidth, pluginHeight);
    
    // SEND BUTTON
    //cutoffSendButton.setLookAndFeel(&sendLook);
    cutoffSendButton.setColour(TextButton::ColourIds::buttonOnColourId, sendingLinesColour);
    addAndMakeVisible(cutoffSendButton);
    //resSendButton.setLookAndFeel(&sendLook);
    resSendButton.setColour(TextButton::ColourIds::buttonOnColourId, sendingLinesColour);
    addAndMakeVisible(resSendButton);
    //reverbDryWetSendButton.setLookAndFeel(&sendLook);
    reverbWetSendButton.setColour(TextButton::ColourIds::buttonOnColourId, sendingLinesColour);
    addAndMakeVisible(reverbWetSendButton);
    //reverbSizeSendButton.setLookAndFeel(&sendLook);
    reverbSizeSendButton.setColour(TextButton::ColourIds::buttonOnColourId, sendingLinesColour);
    addAndMakeVisible(reverbSizeSendButton);
    //delayDryWetSendButton.setLookAndFeel(&sendLook);
    delayDryWetSendButton.setColour(TextButton::ColourIds::buttonOnColourId, sendingLinesColour);
    addAndMakeVisible(delayDryWetSendButton);
    //delayDepthSendButton.setLookAndFeel(&sendLook);
    delayDepthSendButton.setColour(TextButton::ColourIds::buttonOnColourId, sendingLinesColour);
    addAndMakeVisible(delayDepthSendButton);
    //delayRateSendButton.setLookAndFeel(&sendLook);
    delayRateSendButton.setColour(TextButton::ColourIds::buttonOnColourId, sendingLinesColour);
    addAndMakeVisible(delayRateSendButton);
    //delayFeedbackSendButton.setLookAndFeel(&sendLook);
    delayFeedbackSendButton.setColour(TextButton::ColourIds::buttonOnColourId, sendingLinesColour);
    addAndMakeVisible(delayFeedbackSendButton);
    
    auto& params = processor.getParameters();
    // COMBOBOX FILTER TYPE
    AudioParameterInt* filterTypeParameter = (AudioParameterInt*)params.getUnchecked(0);
    //mFilterType.setBounds(0, 280, 100, 30);
    mFilterType.addItem("LOWPASS", 1);
    mFilterType.addItem("HIPASS", 2);
    addAndMakeVisible(mFilterType);
    mFilterType.onChange = [this, filterTypeParameter] {
        filterTypeParameter->beginChangeGesture();
        *filterTypeParameter = mFilterType.getSelectedItemIndex();
        filterTypeParameter->endChangeGesture();
    };
    mFilterType.setSelectedItemIndex(*filterTypeParameter);
    
    // FILTER CUTOFF FREQUENCY
    AudioParameterFloat* filterCutoffParameter = (AudioParameterFloat*)params.getUnchecked(1);
    mFilterCutoffSlider.setRange(filterCutoffParameter->range.start, filterCutoffParameter->range.end);
    mFilterCutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFilterCutoffSlider.setValue(*filterCutoffParameter);
    mFilterCutoffSlider.setSkewFactorFromMidPoint (1000);
    mFilterCutoffSlider.setLookAndFeel(&filterLook);
    mFilterCutoffSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 100, mFilterCutoffSlider.getTextBoxHeight());
    mFilterCutoffSlider.onValueChange = [this, filterCutoffParameter] { *filterCutoffParameter = mFilterCutoffSlider.getValue(); };
    mFilterCutoffSlider.onDragStart = [filterCutoffParameter] { filterCutoffParameter->beginChangeGesture(); };
    mFilterCutoffSlider.onDragEnd = [filterCutoffParameter] { filterCutoffParameter->endChangeGesture(); };
    addAndMakeVisible(mFilterCutoffSlider);
    // frequency label
    mFilterCutoffLabel.setJustificationType(Justification::centred);
    mFilterCutoffLabel.setText("CUTOFF", dontSendNotification);
    addAndMakeVisible(mFilterCutoffLabel);
    
    // FILTER RESONANCE
    AudioParameterFloat* filterResParameter = (AudioParameterFloat*)params.getUnchecked(2);
    mFilterResSlider.setRange(filterResParameter->range.start, filterResParameter->range.end);
    //mFilterResSlider.setBounds(0, 160, 100, 100);
    mFilterResSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFilterResSlider.setValue(*filterResParameter);
    mFilterResSlider.setLookAndFeel(&filterLook);
    mFilterResSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 100, mFilterResSlider.getTextBoxHeight());
    mFilterResSlider.onValueChange = [this, filterResParameter] { *filterResParameter = mFilterResSlider.getValue(); };
    mFilterResSlider.onDragStart = [filterResParameter] { filterResParameter->beginChangeGesture(); };
    mFilterResSlider.onDragEnd = [filterResParameter] { filterResParameter->endChangeGesture(); };
    addAndMakeVisible(mFilterResSlider);
    // resonance label
    mFilterResLabel.setJustificationType(Justification::centred);
    mFilterResLabel.setText("RESONANCE", dontSendNotification);
    addAndMakeVisible(mFilterResLabel);
    
    // REVERB DRY
    AudioParameterFloat* reverbDryParameter = (AudioParameterFloat*)params.getUnchecked(3);
    mReverbDrySlider.setRange(reverbDryParameter->range.start, reverbDryParameter->range.end);
    mReverbDrySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mReverbDrySlider.setValue(*reverbDryParameter);
    mReverbDrySlider.setColour(juce::Slider::trackColourId, lightGrey);
    mReverbDrySlider.setColour(juce::Slider::thumbColourId, lightBlue);
    mReverbDrySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 100, mReverbDrySlider.getTextBoxHeight());
    mReverbDrySlider.onValueChange = [this, reverbDryParameter] { *reverbDryParameter = mReverbDrySlider.getValue(); };
    mReverbDrySlider.onDragStart = [reverbDryParameter] { reverbDryParameter->beginChangeGesture(); };
    mReverbDrySlider.onDragEnd = [reverbDryParameter] { reverbDryParameter->endChangeGesture(); };
    addAndMakeVisible(mReverbDrySlider);
    // reverb dry label
    mReverbDryLabel.setJustificationType(Justification::centred);
    mReverbDryLabel.setText("DRY", dontSendNotification);
    //mReverbDryLabel.setSize(5, 3);
    addAndMakeVisible(mReverbDryLabel);
    
    // REVERB WET
    AudioParameterFloat* reverbWetParameter = (AudioParameterFloat*)params.getUnchecked(4);
    mReverbWetSlider.setRange(reverbWetParameter->range.start, reverbWetParameter->range.end);
    mReverbWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbWetSlider.setValue(*reverbWetParameter);
    mReverbWetSlider.setLookAndFeel(&reverbLook);
    mReverbWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbWetSlider.onValueChange = [this, reverbWetParameter] { *reverbWetParameter = mReverbWetSlider.getValue(); };
    mReverbWetSlider.onDragStart = [reverbWetParameter] { reverbWetParameter->beginChangeGesture(); };
    mReverbWetSlider.onDragEnd = [reverbWetParameter] { reverbWetParameter->endChangeGesture(); };
    addAndMakeVisible(mReverbWetSlider);
    // reverb wet label
    mReverbWetLabel.setJustificationType(Justification::centred);
    mReverbWetLabel.setText("WET", dontSendNotification);
    addAndMakeVisible(mReverbWetLabel);
    
    // REVERB ROOMSIZE
    AudioParameterFloat* reverbSizeParameter = (AudioParameterFloat*)params.getUnchecked(5);
    mReverbSizeSlider.setRange(reverbSizeParameter->range.start, reverbSizeParameter->range.end);
    mReverbSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbSizeSlider.setValue(*reverbSizeParameter);
    mReverbSizeSlider.setLookAndFeel(&reverbLook);
    mReverbSizeSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbSizeSlider.onValueChange = [this, reverbSizeParameter] { *reverbSizeParameter = mReverbSizeSlider.getValue(); };
    mReverbSizeSlider.onDragStart = [reverbSizeParameter] { reverbSizeParameter->beginChangeGesture(); };
    mReverbSizeSlider.onDragEnd = [reverbSizeParameter] { reverbSizeParameter->endChangeGesture(); };
    addAndMakeVisible(mReverbSizeSlider);
    // reverb roomsize label
    mReverbSizeLabel.setJustificationType(Justification::centred);
    mReverbSizeLabel.setText("ROOMSIZE", dontSendNotification);
    addAndMakeVisible(mReverbSizeLabel);
    
    /* DELAY STARTS HERE ***************************************************************************************************************************/
    
    // DRY WET
    AudioParameterFloat* dryWetParameter = (AudioParameterFloat*)params.getUnchecked(11);
    mDelayDryWetSlider.setRange(dryWetParameter->range.start, dryWetParameter->range.end);
    mDelayDryWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDelayDryWetSlider.setValue(*dryWetParameter);
    mDelayDryWetSlider.setLookAndFeel(&delayLook);
    mDelayDryWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDelayDryWetSlider.onValueChange = [this, dryWetParameter] { *dryWetParameter = mDelayDryWetSlider.getValue(); };
    mDelayDryWetSlider.onDragStart = [dryWetParameter] { dryWetParameter->beginChangeGesture(); };
    mDelayDryWetSlider.onDragEnd = [dryWetParameter] { dryWetParameter->endChangeGesture(); };
    addAndMakeVisible(mDelayDryWetSlider);
    // delay drywet label
    mDelayDryWetLabel.setJustificationType(Justification::centred);
    mDelayDryWetLabel.setText("DRY/WET", dontSendNotification);
    addAndMakeVisible(mDelayDryWetLabel);

    // DEPTH
    AudioParameterFloat* depthParameter = (AudioParameterFloat*)params.getUnchecked(12);
    mDelayDepthSlider.setRange(depthParameter->range.start, depthParameter->range.end);
    mDelayDepthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDelayDepthSlider.setValue(*depthParameter);
    mDelayDepthSlider.setLookAndFeel(&delayLook);
    mDelayDepthSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDelayDepthSlider.onValueChange = [this, depthParameter] { *depthParameter = mDelayDepthSlider.getValue(); };
    mDelayDepthSlider.onDragStart = [depthParameter] { depthParameter->beginChangeGesture(); };
    mDelayDepthSlider.onDragEnd = [depthParameter] { depthParameter->endChangeGesture(); };
    addAndMakeVisible(mDelayDepthSlider);
    // delay depth label
    mDelayDepthLabel.setJustificationType(Justification::centred);
    mDelayDepthLabel.setText("DEPTH", dontSendNotification);
    addAndMakeVisible(mDelayDepthLabel);
    
    // RATE
    AudioParameterFloat* rateParameter = (AudioParameterFloat*)params.getUnchecked(13);
    mDelayRateSlider.setRange(rateParameter->range.start, rateParameter->range.end);
    mDelayRateSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDelayRateSlider.setValue(*rateParameter);
    mDelayRateSlider.setLookAndFeel(&delayLook);
    mDelayRateSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDelayRateSlider.onValueChange = [this, rateParameter] { *rateParameter = mDelayRateSlider.getValue(); };
    mDelayRateSlider.onDragStart = [rateParameter] { rateParameter->beginChangeGesture(); };
    mDelayRateSlider.onDragEnd = [rateParameter] { rateParameter->endChangeGesture(); };
    addAndMakeVisible(mDelayRateSlider);
    // delay rate label
    mDelayRateLabel.setJustificationType(Justification::centred);
    mDelayRateLabel.setText("RATE", dontSendNotification);
    addAndMakeVisible(mDelayRateLabel);
    
    // XTREM FEEDBACK
    AudioParameterFloat* xTremFeedbackParameter = (AudioParameterFloat*)params.getUnchecked(14);
    mXTremFeedbackSlider.setRange(xTremFeedbackParameter->range.start, xTremFeedbackParameter->range.end);
    mXTremFeedbackSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mXTremFeedbackSlider.setValue(*xTremFeedbackParameter);
    mXTremFeedbackSlider.setColour(juce::Slider::trackColourId, lightGrey);
    mXTremFeedbackSlider.setColour(juce::Slider::thumbColourId, lightBlue);
    mXTremFeedbackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mXTremFeedbackSlider.onValueChange = [this, xTremFeedbackParameter] { *xTremFeedbackParameter = mXTremFeedbackSlider.getValue(); };
    mXTremFeedbackSlider.onDragStart = [xTremFeedbackParameter] { xTremFeedbackParameter->beginChangeGesture(); };
    mXTremFeedbackSlider.onDragEnd = [xTremFeedbackParameter] { xTremFeedbackParameter->endChangeGesture(); };
    addAndMakeVisible(mXTremFeedbackSlider);
    // x trem feedback label
    mXTremFeedbackLabel.setJustificationType(Justification::centred);
    mXTremFeedbackLabel.setText("X-TREM FEEDBACK", dontSendNotification);
    addAndMakeVisible(mXTremFeedbackLabel);
    
    // FEEDBACK
    AudioParameterFloat* feedbackParameter = (AudioParameterFloat*)params.getUnchecked(15);
    mDelayFeedbackSlider.setRange(feedbackParameter->range.start, feedbackParameter->range.end);
    mDelayFeedbackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFeedbackSlider.setValue(*feedbackParameter);
    mDelayFeedbackSlider.setLookAndFeel(&delayLook);
    mDelayFeedbackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDelayFeedbackSlider.onValueChange = [this, feedbackParameter] { *feedbackParameter = mDelayFeedbackSlider.getValue(); };
    mDelayFeedbackSlider.onDragStart = [feedbackParameter] { feedbackParameter->beginChangeGesture(); };
    mDelayFeedbackSlider.onDragEnd = [feedbackParameter] { feedbackParameter->endChangeGesture(); };
    addAndMakeVisible(mDelayFeedbackSlider);
    // delay feedback label
    mDelayFeedbackLabel.setJustificationType(Justification::centred);
    mDelayFeedbackLabel.setText("FEEDBACK", dontSendNotification);
    addAndMakeVisible(mDelayFeedbackLabel);

    /* DELAY ENDS HERE ***************************************************************************************************************************/

    // SEND BUTTON EVENTS
    AudioParameterBool* cutoffSendParameter = (AudioParameterBool*)params.getUnchecked(6);
    cutoffSendButton.setToggleState(*cutoffSendParameter, NotificationType::dontSendNotification);
    cutoffSendButton.addListener(this);
    AudioParameterBool* resSendParameter = (AudioParameterBool*)params.getUnchecked(7);
    resSendButton.setToggleState(*resSendParameter, NotificationType::dontSendNotification);
    resSendButton.addListener(this);
    AudioParameterBool* reverbWetSendParameter = (AudioParameterBool*)params.getUnchecked(8);
    reverbWetSendButton.setToggleState(*reverbWetSendParameter, NotificationType::dontSendNotification);
    reverbWetSendButton.addListener(this);
    AudioParameterBool* reverbSizeSendParameter = (AudioParameterBool*)params.getUnchecked(9);
    reverbSizeSendButton.setToggleState(*reverbSizeSendParameter, NotificationType::dontSendNotification);
    reverbSizeSendButton.addListener(this);
    // delay
    AudioParameterBool* delayDryWetSendParameter = (AudioParameterBool*)params.getUnchecked(16);
    delayDryWetSendButton.setToggleState(*delayDryWetSendParameter, NotificationType::dontSendNotification);
    delayDryWetSendButton.addListener(this);
    AudioParameterBool* delayDepthSendParameter = (AudioParameterBool*)params.getUnchecked(17);
    delayDepthSendButton.setToggleState(*delayDepthSendParameter, NotificationType::dontSendNotification);
    delayDepthSendButton.addListener(this);
    AudioParameterBool* delayRateSendParameter = (AudioParameterBool*)params.getUnchecked(18);
    delayRateSendButton.setToggleState(*delayRateSendParameter, NotificationType::dontSendNotification);
    delayRateSendButton.addListener(this);
    AudioParameterBool* delayFeedbackSendParameter = (AudioParameterBool*)params.getUnchecked(19);
    delayFeedbackSendButton.setToggleState(*delayFeedbackSendParameter, NotificationType::dontSendNotification);
    delayFeedbackSendButton.addListener(this);
    
    // PERFORMANCE
    AudioParameterFloat* perfParameter = (AudioParameterFloat*)params.getUnchecked(10);
    mPerfSlider.setRange(perfParameter->range.start, perfParameter->range.end);
    mPerfSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    //mPerfSlider.setAlpha(perfOpacity);
    mPerfSlider.setValue(*perfParameter);
    //mPerfSlider.setLookAndFeel(&sliderBarLook);
    mPerfSlider.setColour(juce::Slider::trackColourId, sendingLinesColour);
    addAndMakeVisible(mPerfSlider);
    
    mPerfSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mPerfSlider.onValueChange = [this,
                                 perfParameter,
                                 filterCutoffParameter,
                                 filterResParameter,
                                 reverbWetParameter,
                                 reverbSizeParameter,
                                 dryWetParameter,
                                 depthParameter,
                                 rateParameter,
                                 feedbackParameter] {
        *perfParameter = mPerfSlider.getValue();
        mFilterCutoffSlider.setValue(*filterCutoffParameter);
        mFilterResSlider.setValue(*filterResParameter);
        mReverbWetSlider.setValue(*reverbWetParameter);
        mReverbSizeSlider.setValue(*reverbSizeParameter);
        mDelayDryWetSlider.setValue(*dryWetParameter);
        mDelayDepthSlider.setValue(*depthParameter);
        mDelayRateSlider.setValue(*rateParameter);
        mDelayFeedbackSlider.setValue(*feedbackParameter);
    };
    mPerfSlider.onDragStart = [perfParameter] { perfParameter->beginChangeGesture(); };
    mPerfSlider.onDragEnd = [perfParameter] { perfParameter->endChangeGesture(); };

}

TanenLiveV0AudioProcessorEditor::~TanenLiveV0AudioProcessorEditor()
{
}

void TanenLiveV0AudioProcessorEditor::sendFx(Button* button) {
    auto& params = processor.getParameters();
    AudioParameterBool* filterCutoffSendParameter = (AudioParameterBool*)params.getUnchecked(6);
    AudioParameterBool* filterResSendParameter = (AudioParameterBool*)params.getUnchecked(7);
    AudioParameterBool* reverbWetSendParameter = (AudioParameterBool*)params.getUnchecked(8);
    AudioParameterBool* reverbSizeSendParameter = (AudioParameterBool*)params.getUnchecked(9);
    AudioParameterBool* delayDryWetSendParameter = (AudioParameterBool*)params.getUnchecked(16);
    AudioParameterBool* delayDepthSendParameter = (AudioParameterBool*)params.getUnchecked(17);
    AudioParameterBool* delayRateSendParameter = (AudioParameterBool*)params.getUnchecked(18);
    AudioParameterBool* delayFeedbackSendParameter = (AudioParameterBool*)params.getUnchecked(19);
    
    if (button == &cutoffSendButton) {
        *filterCutoffSendParameter = true;
        filterCutoffSendColour = sendingLinesColour;
        filRevUpperSendColour  = sendingLinesColour;
        filRevLowerSendColour  = sendingLinesColour;
    } else if (button == &resSendButton) {
        *filterResSendParameter = true;
        filterResSendColour    = sendingLinesColour;
        filRevLowerSendColour  = sendingLinesColour;
    } else if (button == &reverbWetSendButton) {
        *reverbWetSendParameter = true;
        reverbWetSendColour    = sendingLinesColour;
        filRevUpperSendColour  = sendingLinesColour;
        filRevLowerSendColour  = sendingLinesColour;
    } else if (button == &reverbSizeSendButton) {
        reverbSizeSendColour   = sendingLinesColour;
        filRevLowerSendColour  = sendingLinesColour;
        *reverbSizeSendParameter = true;
    } else if (button == &delayDryWetSendButton) {
        delayDryWetSendColour = sendingLinesColour;
        delayUpperSendColour  = sendingLinesColour;
        delayLowerSendColour  = sendingLinesColour;
        *delayDryWetSendParameter = true;
    } else if (button == &delayDepthSendButton) {
        delayDepthSendColour  = sendingLinesColour;
        delayLowerSendColour  = sendingLinesColour;
        *delayDepthSendParameter = true;
    } else if (button == &delayRateSendButton) {
        delayRateSendColour   = sendingLinesColour;
        delayUpperSendColour  = sendingLinesColour;
        delayLowerSendColour  = sendingLinesColour;
        *delayRateSendParameter = true;
    } else if (button == &delayFeedbackSendButton) {
        delayFeedbackSendColour = sendingLinesColour;
        delayLowerSendColour    = sendingLinesColour;
        *delayFeedbackSendParameter = true;
    }
    button->setToggleState(true, NotificationType::dontSendNotification);
    button->setButtonText("SENDING");
    joinFinalSendColour    = sendingLinesColour;
    repaint();
}

void TanenLiveV0AudioProcessorEditor::bypassFx(Button* button) {
    auto& params = processor.getParameters();
    AudioParameterBool* filterCutoffSendParameter = (AudioParameterBool*)params.getUnchecked(6);
    AudioParameterBool* filterResSendParameter = (AudioParameterBool*)params.getUnchecked(7);
    AudioParameterBool* reverbWetSendParameter = (AudioParameterBool*)params.getUnchecked(8);
    AudioParameterBool* reverbSizeSendParameter = (AudioParameterBool*)params.getUnchecked(9);
    AudioParameterBool* delayDryWetSendParameter = (AudioParameterBool*)params.getUnchecked(16);
    AudioParameterBool* delayDepthSendParameter = (AudioParameterBool*)params.getUnchecked(17);
    AudioParameterBool* delayRateSendParameter = (AudioParameterBool*)params.getUnchecked(18);
    AudioParameterBool* delayFeedbackSendParameter = (AudioParameterBool*)params.getUnchecked(19);

    bool leftSideOn  = *filterCutoffSendParameter||*filterResSendParameter ||*reverbWetSendParameter||*reverbSizeSendParameter;
    bool rightSideOn = *delayDryWetSendParameter ||*delayDepthSendParameter||*delayRateSendParameter||*delayFeedbackSendParameter;
    
    // LEFT SIDE
    if (button == &cutoffSendButton) {
        filterCutoffSendColour = bypassedLinesColour;
        if (!*reverbWetSendParameter) {
            filRevUpperSendColour = bypassedLinesColour;
            if (!*filterResSendParameter && !*reverbSizeSendParameter) {
                filRevLowerSendColour = bypassedLinesColour;
                if (!rightSideOn) {
                    joinFinalSendColour = bypassedLinesColour;
                }
            }
        }
        *filterCutoffSendParameter = false;
    } else if (button == &resSendButton) {
        filterResSendColour = bypassedLinesColour;
        if (!*reverbSizeSendParameter && !*filterCutoffSendParameter && !*reverbWetSendParameter) {
            filRevLowerSendColour = bypassedLinesColour;
            if (!rightSideOn) {
                joinFinalSendColour = bypassedLinesColour;
            }
        }
        *filterResSendParameter = false;
    } else if (button == &reverbWetSendButton) {
        reverbWetSendColour = bypassedLinesColour;
        if (!*filterCutoffSendParameter) {
            filRevUpperSendColour = bypassedLinesColour;
            if (!*filterResSendParameter && !*reverbSizeSendParameter) {
                filRevLowerSendColour = bypassedLinesColour;
                if (!rightSideOn) {
                    joinFinalSendColour = bypassedLinesColour;
                }
            }
        }
        *reverbWetSendParameter = false;
    } else if (button == &reverbSizeSendButton) {
        reverbSizeSendColour = bypassedLinesColour;
        if (!*filterResSendParameter && !*filterCutoffSendParameter && !*reverbWetSendParameter) {
            filRevLowerSendColour = bypassedLinesColour;
            if (!rightSideOn) {
                joinFinalSendColour = bypassedLinesColour;
            }
        }
        *reverbSizeSendParameter = false;
    // RIGHT SIDE
    } else if (button == &delayDryWetSendButton) {
        delayDryWetSendColour = bypassedLinesColour;
        if (!*delayRateSendParameter) {
            delayUpperSendColour = bypassedLinesColour;
            if (!*delayDepthSendParameter && !*delayFeedbackSendParameter) {
                delayLowerSendColour = bypassedLinesColour;
                if (!leftSideOn) {
                    joinFinalSendColour = bypassedLinesColour;
                }
            }
        }
        *delayDryWetSendParameter = false;
    } else if (button == &delayDepthSendButton) {
        delayDepthSendColour = bypassedLinesColour;
        if (!*delayFeedbackSendParameter && !*delayDryWetSendParameter && !*delayRateSendParameter) {
            delayLowerSendColour = bypassedLinesColour;
            if (!leftSideOn) {
                joinFinalSendColour = bypassedLinesColour;
            }
        }
        *delayDepthSendParameter = false;
    } else if (button == &delayRateSendButton) {
        delayRateSendColour = bypassedLinesColour;
        if (!*delayDryWetSendParameter) {
            delayUpperSendColour = bypassedLinesColour;
            if (!*delayDepthSendParameter && !*delayFeedbackSendParameter) {
                delayLowerSendColour = bypassedLinesColour;
                if (!leftSideOn) {
                    joinFinalSendColour = bypassedLinesColour;
                }
            }
        }
        *delayRateSendParameter = false;
    } else if (button == &delayFeedbackSendButton) {
        delayFeedbackSendColour = bypassedLinesColour;
        if (!*delayDepthSendParameter && !*delayDryWetSendParameter && !*delayRateSendParameter) {
            delayLowerSendColour = bypassedLinesColour;
            if (!leftSideOn) {
                joinFinalSendColour = bypassedLinesColour;
            }
        }
        *delayFeedbackSendParameter = false;
    }
    button->setToggleState(false, NotificationType::dontSendNotification);
    button->setButtonText("BYPASSED");
    repaint();
}

void TanenLiveV0AudioProcessorEditor::buttonClicked(Button* button) {
    // WHAT TO DO WITH BUTTON CLICKED
    if (button->getToggleStateValue().getValue()) {
        button->onClick =[this, button]() { bypassFx(button); };
    } else {
        button->onClick =[this, button]() { sendFx(button); };
    }
  
}

void TanenLiveV0AudioProcessorEditor::drawSendLines(Graphics& g) {
    
    // LEFT SIDE
    // FilterCuttoffSend
    g.setColour(filterCutoffSendColour);
    Line<float> filterCutoffLineV (Point<float> (fxWidth*0.5, headerHeight+itemSize+sendSize-sendMargin),
                                 Point<float> (fxWidth*0.5, headerHeight+itemSize+sendSize+sendMargin));
    g.drawLine (filterCutoffLineV, lineThickness);
    Line<float> filterCutoffLineH (Point<float> (fxWidth*0.5-lineThickness*0.5, headerHeight+itemSize+sendSize+sendMargin+lineThickness*0.5),
                                 Point<float> (fxWidth-lineThickness*0.5, headerHeight+itemSize+sendSize+sendMargin));
    g.drawLine (filterCutoffLineH, lineThickness);
    // FilterResSend
    g.setColour(filterResSendColour);
    Line<float> filterResLineV (Point<float> (fxWidth*0.5, headerHeight+sendMargin+(itemSize+sendSize-sendMargin)*2),
                               Point<float> (fxWidth*0.5, headerHeight+sendMargin+(itemSize+sendSize)*2));
    g.drawLine (filterResLineV, lineThickness);
    Line<float> filterResLineH (Point<float> (fxWidth*0.5-lineThickness*0.5, headerHeight+sendMargin+(itemSize+sendSize)*2+lineThickness*0.5),
                               Point<float> (fxWidth-lineThickness*0.5, headerHeight+sendMargin+(itemSize+sendSize)*2));
    g.drawLine (filterResLineH, lineThickness);
    
    // ReverbWetSend
    g.setColour(reverbWetSendColour);
    Line<float> reverbWetLineV (Point<float> (fxWidth*1.5, headerHeight+itemSize+sendSize-sendMargin),
                                 Point<float> (fxWidth*1.5, headerHeight+itemSize+sendSize+sendMargin));
    g.drawLine (reverbWetLineV, lineThickness);
    Line<float> reverbWetLineH (Point<float> (fxWidth*1.5+lineThickness*0.5, headerHeight+itemSize+sendSize+sendMargin+lineThickness*0.5),
                                 Point<float> (fxWidth+lineThickness*0.5, headerHeight+itemSize+sendSize+sendMargin));
    g.drawLine (reverbWetLineH, lineThickness);
    // ReverbSizeSend
    g.setColour(reverbSizeSendColour);
    Line<float> reverbSizeLineV (Point<float> (fxWidth*1.5, headerHeight+sendMargin+(itemSize+sendSize-sendMargin)*2),
                               Point<float> (fxWidth*1.5, headerHeight+sendMargin+(itemSize+sendSize)*2));
    g.drawLine (reverbSizeLineV, lineThickness);
    Line<float> reverbSizeLineH (Point<float> (fxWidth*1.5+lineThickness*0.5, headerHeight+sendMargin+(itemSize+sendSize)*2+lineThickness*0.5),
                               Point<float> (fxWidth+lineThickness*0.5, headerHeight+sendMargin+(itemSize+sendSize)*2));
    g.drawLine (reverbSizeLineH , lineThickness);
    
    
    // FILTER + REVERB
    // filRevUpperSend line
    g.setColour(filRevUpperSendColour);
    Line<float> filRevUpperLineV (Point<float> (fxWidth, headerHeight+itemSize+sendSize+sendMargin-lineThickness*0.5),
                                 Point<float> (fxWidth, headerHeight+sendMargin+(itemSize+sendSize)*2-lineThickness*0.5));
    g.drawLine (filRevUpperLineV, lineThickness);
    // filRevLowerSend line
    g.setColour(filRevLowerSendColour);
    Line<float> filRevLowerLineV (Point<float> (fxWidth, headerHeight+sendMargin+(itemSize+sendSize)*2-lineThickness*0.5),
                               Point<float> (fxWidth, pluginHeight-footerHeight*0.5-lineThickness*0.5));
    g.drawLine (filRevLowerLineV, lineThickness);
    Line<float> filRevLowerLineH (Point<float> (fxWidth-lineThickness*0.5, pluginHeight-footerHeight*0.5),
                                 Point<float> (fxWidth*2.5-lineThickness*0.5, pluginHeight-footerHeight*0.5+lineThickness*1.5));
    g.drawLine (filRevLowerLineH, lineThickness);
    
    // RIGHT SIDE
    // DelayDryWetSend
    g.setColour(delayDryWetSendColour);
    Line<float> delayDryWetLineV (Point<float> (pluginWidth-fxWidth*1.5, headerHeight+itemSize+sendSize-sendMargin),
                                 Point<float> (pluginWidth-fxWidth*1.5, headerHeight+itemSize+sendSize+sendMargin));
    g.drawLine (delayDryWetLineV, lineThickness);
    Line<float> delayDryWetCutoffLineH (Point<float> (pluginWidth-fxWidth*1.5-lineThickness*0.5, headerHeight+itemSize+sendSize+sendMargin+lineThickness*0.5),
                                 Point<float> (pluginWidth-fxWidth-lineThickness*0.5, headerHeight+itemSize+sendSize+sendMargin));
    g.drawLine (delayDryWetCutoffLineH, lineThickness);
    // DelayDepthSend
    g.setColour(delayDepthSendColour);
    Line<float> delayDepthLineV (Point<float> (pluginWidth-fxWidth*1.5, headerHeight+sendMargin+(itemSize+sendSize-sendMargin)*2),
                               Point<float> (pluginWidth-fxWidth*1.5, headerHeight+sendMargin+(itemSize+sendSize)*2));
    g.drawLine (delayDepthLineV, lineThickness);
    Line<float> delayDepthLineH (Point<float> (pluginWidth-fxWidth*1.5-lineThickness*0.5, headerHeight+sendMargin+(itemSize+sendSize)*2+lineThickness*0.5),
                               Point<float> (pluginWidth-fxWidth-lineThickness*0.5, headerHeight+sendMargin+(itemSize+sendSize)*2));
    g.drawLine (delayDepthLineH, lineThickness);
    
    // DelayRateSend
    g.setColour(delayRateSendColour);
    Line<float> delayRateLineV (Point<float> (pluginWidth-fxWidth*0.5, headerHeight+itemSize+sendSize-sendMargin),
                                 Point<float> (pluginWidth-fxWidth*0.5, headerHeight+itemSize+sendSize+sendMargin));
    g.drawLine (delayRateLineV, lineThickness);
    Line<float> delayRateLineH (Point<float> (pluginWidth-fxWidth*0.5+lineThickness*0.5, headerHeight+itemSize+sendSize+sendMargin+lineThickness*0.5),
                                 Point<float> (pluginWidth-fxWidth+lineThickness*0.5, headerHeight+itemSize+sendSize+sendMargin));
    g.drawLine (delayRateLineH, lineThickness);
    // DelayFeedbackSend
    g.setColour(delayFeedbackSendColour);
    Line<float> delayFeedbackLineV (Point<float> (pluginWidth-fxWidth*0.5, headerHeight+sendMargin+(itemSize+sendSize-sendMargin)*2),
                               Point<float> (pluginWidth-fxWidth*0.5, headerHeight+sendMargin+(itemSize+sendSize)*2));
    g.drawLine (delayFeedbackLineV, lineThickness);
    Line<float> delayFeedbackLineH (Point<float> (pluginWidth-fxWidth*0.5+lineThickness*0.5, headerHeight+sendMargin+(itemSize+sendSize)*2+lineThickness*0.5),
                               Point<float> (pluginWidth-fxWidth+lineThickness*0.5, headerHeight+sendMargin+(itemSize+sendSize)*2));
    g.drawLine (delayFeedbackLineH , lineThickness);
    
    // DELAY CENTER
    // filRevUpperSend line
    g.setColour(delayUpperSendColour);
    Line<float> delayUpperLineV (Point<float> (pluginWidth-fxWidth, headerHeight+itemSize+sendSize+sendMargin-lineThickness*0.5),
                                 Point<float> (pluginWidth-fxWidth, headerHeight+sendMargin+(itemSize+sendSize)*2-lineThickness*0.5));
    g.drawLine (delayUpperLineV, lineThickness);
    // filRevLowerSend line
    g.setColour(delayLowerSendColour);
    Line<float> delayLowerLineV (Point<float> (pluginWidth-fxWidth, headerHeight+sendMargin+(itemSize+sendSize)*2-lineThickness*0.5),
                               Point<float> (pluginWidth-fxWidth, pluginHeight-footerHeight*0.5-lineThickness*0.5));
    g.drawLine (delayLowerLineV, lineThickness);
    Line<float> delayLowerLineH (Point<float> (pluginWidth-fxWidth+lineThickness*0.5, pluginHeight-footerHeight*0.5),
                                 Point<float> (pluginWidth-fxWidth*2.5+lineThickness*0.5, pluginHeight-footerHeight*0.5+lineThickness*1.5));
    g.drawLine (delayLowerLineH, lineThickness);
    
    // JOIN FINAL LINE
    g.setColour(joinFinalSendColour);
    Line<float> joinFinalLineV (Point<float> (fxWidth*2.5, pluginHeight-footerHeight*0.5+lineThickness*2),
                                 Point<float> (fxWidth*2.5, pluginHeight-footerHeight));
    g.drawLine (joinFinalLineV, lineThickness);
    
}

//==============================================================================
void TanenLiveV0AudioProcessorEditor::paint (Graphics& g)
{
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    getLookAndFeel().setColour(juce::ColourSelector::backgroundColourId , almostBlack);
    g.fillAll(darkDarkGrey);
    g.setColour (fontColour);
    g.setFont (fontSize);
    g.drawFittedText ("TANEN LIVE MACHINE", getLocalBounds(), Justification::centredBottom, 1);
    
    drawSendLines(g);
}

void TanenLiveV0AudioProcessorEditor::resized()
{
    //setSize (600 width, 450 height);
    auto area = getLocalBounds();
    //auto headerHeight = 40;
    //auto footerHeight = 60;
    // zone in zone :
    /*auto itemMargin = 15;
    auto imageMargin = 100;
    auto headerMargin = 3;
    auto itemSize = 125;
    auto sendSize = 50;
    auto sendMargin = 10;
    auto labelMargin = 15;*/
    
    auto header = area.removeFromTop(headerHeight);
    auto footer = area.removeFromBottom(footerHeight);
 
    //auto fxWidth = 120; // height = 450 - (40+60) = 350
    auto filterZone = area.removeFromLeft (fxWidth);
    auto reverbZone = area.removeFromLeft (fxWidth);
    auto performanceZone = area.removeFromLeft (fxWidth);
    auto delayZone = area;
    auto delayZoneLeft = area.removeFromLeft (fxWidth);
    auto delayZoneRight = area.removeFromRight (fxWidth);
    
    // DRAW FRAMES
    headerFrame.setBounds(header);
    footerFrame.setBounds(footer);
    filterFrame.setBounds(filterZone);
    reverbFrame.setBounds(reverbZone);
    delayFrame.setBounds(delayZone);
    performanceFrame.setBounds(performanceZone);

    
    // FILTER
    mFilterType.setBounds(header.removeFromLeft(fxWidth).reduced(headerMargin));
    // cutoff slider
    auto cutoffZone = filterZone.removeFromTop(itemSize);
    mFilterCutoffSlider.setBounds(cutoffZone.reduced(itemMargin));
    // cutoff label
    mFilterCutoffLabel.setBounds(cutoffZone.removeFromBottom(labelMargin));
    // cutoff send button
    cutoffSendButton.setBounds(filterZone.removeFromTop(sendSize).reduced(sendMargin));
    // res slider
    auto resZone = filterZone.removeFromTop(itemSize);
    mFilterResSlider.setBounds(resZone.reduced(itemMargin));
    // res label
    mFilterResLabel.setBounds(resZone.removeFromBottom(labelMargin));
    // res send button
    resSendButton.setBounds(filterZone.removeFromTop(sendSize).reduced(sendMargin));

    
    // REVERB
    // dry slider
    auto reverbDryZone = header.removeFromLeft(fxWidth);
    mReverbDrySlider.setBounds(reverbDryZone.removeFromTop(headerHeight*0.66).reduced(headerMargin));
    // dry label
    mReverbDryLabel.setBounds(reverbDryZone);
    // wet slider
    auto reverbWetZone = reverbZone.removeFromTop(itemSize);
    mReverbWetSlider.setBounds(reverbWetZone.reduced(itemMargin));
    // wet label
    mReverbWetLabel.setBounds(reverbWetZone.removeFromBottom(labelMargin));
    // wet send button
    reverbWetSendButton.setBounds(reverbZone.removeFromTop(sendSize).reduced(sendMargin));
    // size slider
    auto reverbSizeZone = reverbZone.removeFromTop(itemSize);
    mReverbSizeSlider.setBounds(reverbSizeZone.reduced(itemMargin));
    // size label
    mReverbSizeLabel.setBounds(reverbSizeZone.removeFromBottom(labelMargin));
    // size send button
    reverbSizeSendButton.setBounds(reverbZone.removeFromTop(sendSize).reduced(sendMargin));
    
    // DELAY
    // phase offset slider
    header.removeFromLeft(fxWidth);
    auto xTremZone = header.removeFromLeft(fxWidth);
    mXTremFeedbackSlider.setBounds(xTremZone.removeFromTop(headerHeight*0.66).reduced(headerMargin));
    // dry label
    mXTremFeedbackLabel.setBounds(xTremZone);
    // drywet slider
    auto delayDryWetZone = delayZoneLeft.removeFromTop(itemSize);
    mDelayDryWetSlider.setBounds(delayDryWetZone.reduced(itemMargin));
    // drywet label
    mDelayDryWetLabel.setBounds(delayDryWetZone.removeFromBottom(labelMargin));
    // drywet send button
    delayDryWetSendButton.setBounds(delayZoneLeft.removeFromTop(sendSize).reduced(sendMargin));
    // depth slider
    auto delayDepthZone = delayZoneLeft.removeFromTop(itemSize);
    mDelayDepthSlider.setBounds(delayDepthZone.reduced(itemMargin));
    // depth label
    mDelayDepthLabel.setBounds(delayDepthZone.removeFromBottom(labelMargin));
    // depth send button
    delayDepthSendButton.setBounds(delayZoneLeft.removeFromTop(sendSize).reduced(sendMargin));
    
    // rate slider
    auto delayRateZone = delayZoneRight.removeFromTop(itemSize);
    mDelayRateSlider.setBounds(delayRateZone.reduced(itemMargin));
    // rate label
    mDelayRateLabel.setBounds(delayRateZone.removeFromBottom(labelMargin));
    // rate send button
    delayRateSendButton.setBounds(delayZoneRight.removeFromTop(sendSize).reduced(sendMargin));
    // feedback slider
    auto delayFeedbackZone = delayZoneRight.removeFromTop(itemSize);
    mDelayFeedbackSlider.setBounds(delayFeedbackZone.reduced(itemMargin));
    // feedback label
    mDelayFeedbackLabel.setBounds(delayFeedbackZone.removeFromBottom(labelMargin));
    // feedback send button
    delayFeedbackSendButton.setBounds(delayZoneRight.removeFromTop(sendSize).reduced(sendMargin));
    
    // PERFORMANCE
    performanceZone.removeFromTop(sendMargin);
    mPerfSlider.setBounds(performanceZone);
    mImageComponent.setBounds(performanceZone.reduced(0, imageMargin));


}

