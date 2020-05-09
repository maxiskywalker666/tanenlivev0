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
    cutoffSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red.withAlpha(perfOpacity));
    addAndMakeVisible(cutoffSendButton);
    //resSendButton.setLookAndFeel(&sendLook);
    resSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red.withAlpha(perfOpacity));
    addAndMakeVisible(resSendButton);
    //reverbDryWetSendButton.setLookAndFeel(&sendLook);
    reverbWetSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red.withAlpha(perfOpacity));
    addAndMakeVisible(reverbWetSendButton);
    //reverbSizeSendButton.setLookAndFeel(&sendLook);
    reverbSizeSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red.withAlpha(perfOpacity));
    addAndMakeVisible(reverbSizeSendButton);
    //delayDryWetSendButton.setLookAndFeel(&sendLook);
    delayDryWetSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red.withAlpha(perfOpacity));
    addAndMakeVisible(delayDryWetSendButton);
    //delayDepthSendButton.setLookAndFeel(&sendLook);
    delayDepthSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red.withAlpha(perfOpacity));
    addAndMakeVisible(delayDepthSendButton);
    //delayRateSendButton.setLookAndFeel(&sendLook);
    delayRateSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red.withAlpha(perfOpacity));
    addAndMakeVisible(delayRateSendButton);
    //delayFeedbackSendButton.setLookAndFeel(&sendLook);
    delayFeedbackSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red.withAlpha(perfOpacity));
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
    mReverbDrySlider.setColour(juce::Slider::trackColourId, Colours::lightsteelblue);
    mReverbDrySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 100, mReverbDrySlider.getTextBoxHeight());
    mReverbDrySlider.onValueChange = [this, reverbDryParameter] { *reverbDryParameter = mReverbDrySlider.getValue(); };
    mReverbDrySlider.onDragStart = [reverbDryParameter] { reverbDryParameter->beginChangeGesture(); };
    mReverbDrySlider.onDragEnd = [reverbDryParameter] { reverbDryParameter->endChangeGesture(); };
    addAndMakeVisible(mReverbDrySlider);
    
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
    
    // PHASEOFFSET
    AudioParameterFloat* phaseParameter = (AudioParameterFloat*)params.getUnchecked(14);
    mDelayPhaseOffsetSlider.setRange(phaseParameter->range.start, phaseParameter->range.end);
    mDelayPhaseOffsetSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mDelayPhaseOffsetSlider.setValue(*phaseParameter);
    mDelayPhaseOffsetSlider.setColour(juce::Slider::trackColourId, Colours::mediumpurple);
    mDelayPhaseOffsetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDelayPhaseOffsetSlider.onValueChange = [this, phaseParameter] { *phaseParameter = mDelayPhaseOffsetSlider.getValue(); };
    mDelayPhaseOffsetSlider.onDragStart = [phaseParameter] { phaseParameter->beginChangeGesture(); };
    mDelayPhaseOffsetSlider.onDragEnd = [phaseParameter] { phaseParameter->endChangeGesture(); };
    //addAndMakeVisible(mDelayPhaseOffsetSlider);
    
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
    mPerfSlider.setAlpha(0.5);
    mPerfSlider.setValue(*perfParameter);
    //mPerfSlider.setLookAndFeel(&sliderBarLook);
    mPerfSlider.setColour(juce::Slider::trackColourId, Colours::red);
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
    AudioParameterBool* cutoffSendParameter = (AudioParameterBool*)params.getUnchecked(6);
    AudioParameterBool* resSendParameter = (AudioParameterBool*)params.getUnchecked(7);
    AudioParameterBool* reverbWetSendParameter = (AudioParameterBool*)params.getUnchecked(8);
    AudioParameterBool* reverbSizeSendParameter = (AudioParameterBool*)params.getUnchecked(9);
    AudioParameterBool* delayDryWetSendParameter = (AudioParameterBool*)params.getUnchecked(16);
    AudioParameterBool* delayDepthSendParameter = (AudioParameterBool*)params.getUnchecked(17);
    AudioParameterBool* delayRateSendParameter = (AudioParameterBool*)params.getUnchecked(18);
    AudioParameterBool* delayFeedbackSendParameter = (AudioParameterBool*)params.getUnchecked(19);
    if (button == &cutoffSendButton) {
        *cutoffSendParameter = true;
        filterCutoffSendColour = sendingLinesColour;
        filRevUpperSendColour  = sendingLinesColour;
        filRevLowerSendColour  = sendingLinesColour;
    } else if (button == &resSendButton) {
        *resSendParameter = true;
        filterResSendColour    = sendingLinesColour;
        filRevLowerSendColour  = sendingLinesColour;
    } else if (button == &reverbWetSendButton) {
        *reverbWetSendParameter = true;
        reverbWetSendColour    = sendingLinesColour;
        filRevUpperSendColour  = sendingLinesColour;
        filRevLowerSendColour  = sendingLinesColour;
    } else if (button == &reverbSizeSendButton) {
        reverbSizeSendColour    = sendingLinesColour;
        filRevLowerSendColour  = sendingLinesColour;
        *reverbSizeSendParameter = true;
    } else if (button == &delayDryWetSendButton) {
        *delayDryWetSendParameter = true;
    } else if (button == &delayDepthSendButton) {
        *delayDepthSendParameter = true;
    } else if (button == &delayRateSendButton) {
        *delayRateSendParameter = true;
    } else if (button == &delayFeedbackSendButton) {
        *delayFeedbackSendParameter = true;
    }
    button->setToggleState(true, NotificationType::dontSendNotification);
    button->setButtonText("SENDING");
    joinFinalSendColour    = sendingLinesColour;
    repaint();
}

void TanenLiveV0AudioProcessorEditor::bypassFx(Button* button) {
    auto& params = processor.getParameters();
    AudioParameterBool* cutoffSendParameter = (AudioParameterBool*)params.getUnchecked(6);
    AudioParameterBool* resSendParameter = (AudioParameterBool*)params.getUnchecked(7);
    AudioParameterBool* reverbWetSendParameter = (AudioParameterBool*)params.getUnchecked(8);
    AudioParameterBool* reverbSizeSendParameter = (AudioParameterBool*)params.getUnchecked(9);
    AudioParameterBool* delayDryWetSendParameter = (AudioParameterBool*)params.getUnchecked(16);
    AudioParameterBool* delayDepthSendParameter = (AudioParameterBool*)params.getUnchecked(17);
    AudioParameterBool* delayRateSendParameter = (AudioParameterBool*)params.getUnchecked(18);
    AudioParameterBool* delayFeedbackSendParameter = (AudioParameterBool*)params.getUnchecked(19);

    if (button == &cutoffSendButton) {
        filterCutoffSendColour = bypassedLinesColour;
        if (!*reverbWetSendParameter) {
            filRevUpperSendColour = bypassedLinesColour;
            if (!*resSendParameter && !*reverbSizeSendParameter) {
                filRevLowerSendColour = bypassedLinesColour;
                joinFinalSendColour = bypassedLinesColour;
            }
        }
        *cutoffSendParameter = false;
    } else if (button == &resSendButton) {
        filterResSendColour = bypassedLinesColour;
        if (!*reverbSizeSendParameter && !*cutoffSendParameter && !*reverbWetSendParameter) {
            filRevLowerSendColour = bypassedLinesColour;
            joinFinalSendColour = bypassedLinesColour;
        }
        *resSendParameter = false;
    } else if (button == &reverbWetSendButton) {
        reverbWetSendColour = bypassedLinesColour;
        if (!*cutoffSendParameter) {
            filRevUpperSendColour = bypassedLinesColour;
            if (!*resSendParameter && !*reverbSizeSendParameter) {
                filRevLowerSendColour = bypassedLinesColour;
                joinFinalSendColour = bypassedLinesColour;
            }
        }
        *reverbWetSendParameter = false;
    } else if (button == &reverbSizeSendButton) {
        reverbSizeSendColour = bypassedLinesColour;
        if (!*resSendParameter && !*cutoffSendParameter && !*reverbWetSendParameter) {
            filRevLowerSendColour = bypassedLinesColour;
            joinFinalSendColour = bypassedLinesColour;
        }
        *reverbSizeSendParameter = false;
    } else if (button == &delayDryWetSendButton) {
        *delayDryWetSendParameter = false;
    } else if (button == &delayDepthSendButton) {
        *delayDepthSendParameter = false;
    } else if (button == &delayRateSendButton) {
        *delayRateSendParameter = false;
    } else if (button == &delayFeedbackSendButton) {
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
    
    // TODO Redefine colour before drawing each line - with a variable for each path
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
    Line<float> filRevFirstLineV (Point<float> (fxWidth, headerHeight+itemSize+sendSize+sendMargin-lineThickness*0.5),
                                 Point<float> (fxWidth, headerHeight+sendMargin+(itemSize+sendSize)*2-lineThickness*0.5));
    g.drawLine (filRevFirstLineV, lineThickness);
    // filRevLowerSend line
    g.setColour(filRevLowerSendColour);
    Line<float> filRevSndLineV (Point<float> (fxWidth, headerHeight+sendMargin+(itemSize+sendSize)*2-lineThickness*0.5),
                               Point<float> (fxWidth, pluginHeight-footerHeight*0.5-lineThickness*0.5));
    g.drawLine (filRevSndLineV, lineThickness);
    Line<float> filRevLineH (Point<float> (fxWidth-lineThickness*0.5, pluginHeight-footerHeight*0.5),
                                 Point<float> (fxWidth*2.5-lineThickness*0.5, pluginHeight-footerHeight*0.5+lineThickness*1.5));
    g.drawLine (filRevLineH, lineThickness);
    
    // JOIN FINAL LINE
    g.setColour(joinFinalSendColour);
    Line<float> joinFinalLineV (Point<float> (fxWidth*2.5, pluginHeight-footerHeight*0.5+lineThickness*2),
                                 Point<float> (fxWidth*2.5, pluginHeight-footerHeight));
    g.drawLine (joinFinalLineV, lineThickness);
    
}

//==============================================================================
void TanenLiveV0AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
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
    mReverbDrySlider.setBounds(header.removeFromLeft(fxWidth).reduced(headerMargin));
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
    auto performanceHeaderZone = header.removeFromLeft(fxWidth);
    mDelayPhaseOffsetSlider.setBounds(header.removeFromLeft(fxWidth).reduced(headerMargin));
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
    mPerfSlider.setBounds(performanceZone);
    mImageComponent.setBounds(performanceZone.reduced(0, imageMargin));


}

