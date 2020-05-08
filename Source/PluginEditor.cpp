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
    addAndMakeVisible(headerFrame);
    addAndMakeVisible(footerFrame);
    addAndMakeVisible(filterFrame);
    addAndMakeVisible(reverbFrame);
    addAndMakeVisible(delayFrame);
    addAndMakeVisible(performanceFrame);
    // IMAGE
    auto t1000Image = ImageCache::getFromMemory(BinaryData::T1000_png, BinaryData::T1000_pngSize);
    if (!t1000Image.isNull())
        mImageComponent.setImage(t1000Image, RectanglePlacement::stretchToFit);
    else
        jassert(!t1000Image.isNull());
    addAndMakeVisible(mImageComponent);
    
    // WINDOW SIZE
    setSize (600, 450);
    
    // SEND BUTTON
    //cutoffSendButton.setLookAndFeel(&sendLook);
    cutoffSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red);
    addAndMakeVisible(cutoffSendButton);
    //resSendButton.setLookAndFeel(&sendLook);
    resSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red);
    addAndMakeVisible(resSendButton);
    //reverbDryWetSendButton.setLookAndFeel(&sendLook);
    reverbWetSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red);
    addAndMakeVisible(reverbWetSendButton);
    //reverbSizeSendButton.setLookAndFeel(&sendLook);
    reverbSizeSendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red);
    addAndMakeVisible(reverbSizeSendButton);
    //delaySendButton.setLookAndFeel(&sendLook);
    delaySendButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red);
    addAndMakeVisible(delaySendButton);
    
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
    //mFilterCutoffSlider.setBounds(0, 30, 100, 100);
    mFilterCutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFilterCutoffSlider.setValue(*filterCutoffParameter);
    mFilterCutoffSlider.setSkewFactorFromMidPoint (1000);
    mFilterCutoffSlider.setLookAndFeel(&filterLook);
    addAndMakeVisible(mFilterCutoffSlider);
    
    mFilterCutoffSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 100, mFilterCutoffSlider.getTextBoxHeight());
    mFilterCutoffSlider.onValueChange = [this, filterCutoffParameter] { *filterCutoffParameter = mFilterCutoffSlider.getValue(); };
    mFilterCutoffSlider.onDragStart = [filterCutoffParameter] { filterCutoffParameter->beginChangeGesture(); };
    mFilterCutoffSlider.onDragEnd = [filterCutoffParameter] { filterCutoffParameter->endChangeGesture(); };
    mFilterCutoffSlider.setTextValueSuffix (" Hz");     // [2]
    //mFilterCutoffSlider.addListener (this);
    // frequency label
    mFilterCutoffLabel.setText("CUTOFF", dontSendNotification);
    
    // FILTER RESONANCE
    AudioParameterFloat* filterResParameter = (AudioParameterFloat*)params.getUnchecked(2);
    mFilterResSlider.setRange(filterResParameter->range.start, filterResParameter->range.end);
    //mFilterResSlider.setBounds(0, 160, 100, 100);
    mFilterResSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFilterResSlider.setValue(*filterResParameter);
    mFilterResSlider.setLookAndFeel(&filterLook);
    addAndMakeVisible(mFilterResSlider);
    
    mFilterResSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 100, mFilterResSlider.getTextBoxHeight());
    mFilterResSlider.onValueChange = [this, filterResParameter] { *filterResParameter = mFilterResSlider.getValue(); };
    mFilterResSlider.onDragStart = [filterResParameter] { filterResParameter->beginChangeGesture(); };
    mFilterResSlider.onDragEnd = [filterResParameter] { filterResParameter->endChangeGesture(); };
    // resonance label
    mFilterResLabel.setText("RESONANCE", dontSendNotification);
    
    // REVERB DRY
    AudioParameterFloat* reverbDryParameter = (AudioParameterFloat*)params.getUnchecked(3);
    mReverbDrySlider.setRange(reverbDryParameter->range.start, reverbDryParameter->range.end);
    mReverbDrySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mReverbDrySlider.setValue(*reverbDryParameter);
    //mReverbDrySlider.setLookAndFeel(&reverbLook);
    mReverbDrySlider.setColour(juce::Slider::trackColourId, Colours::lightsteelblue);
    addAndMakeVisible(mReverbDrySlider);
    
    mReverbDrySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 100, mReverbDrySlider.getTextBoxHeight());
    mReverbDrySlider.onValueChange = [this, reverbDryParameter] { *reverbDryParameter = mReverbDrySlider.getValue(); };
    mReverbDrySlider.onDragStart = [reverbDryParameter] { reverbDryParameter->beginChangeGesture(); };
    mReverbDrySlider.onDragEnd = [reverbDryParameter] { reverbDryParameter->endChangeGesture(); };
    
    // REVERB WET
    AudioParameterFloat* reverbWetParameter = (AudioParameterFloat*)params.getUnchecked(4);
    mReverbWetSlider.setRange(reverbWetParameter->range.start, reverbWetParameter->range.end);
    mReverbWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbWetSlider.setValue(*reverbWetParameter);
    mReverbWetSlider.setLookAndFeel(&reverbLook);
    addAndMakeVisible(mReverbWetSlider);
    
    mReverbWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbWetSlider.onValueChange = [this, reverbWetParameter] { *reverbWetParameter = mReverbWetSlider.getValue(); };
    mReverbWetSlider.onDragStart = [reverbWetParameter] { reverbWetParameter->beginChangeGesture(); };
    mReverbWetSlider.onDragEnd = [reverbWetParameter] { reverbWetParameter->endChangeGesture(); };
    mReverbWetLabel.setText("WET", dontSendNotification);
    
    // REVERB ROOMSIZE
    AudioParameterFloat* reverbSizeParameter = (AudioParameterFloat*)params.getUnchecked(5);
    mReverbSizeSlider.setRange(reverbSizeParameter->range.start, reverbSizeParameter->range.end);
    mReverbSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbSizeSlider.setValue(*reverbSizeParameter);
    mReverbSizeSlider.setLookAndFeel(&reverbLook);
    addAndMakeVisible(mReverbSizeSlider);
    
    mReverbSizeSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbSizeSlider.onValueChange = [this, reverbSizeParameter] { *reverbSizeParameter = mReverbSizeSlider.getValue(); };
    mReverbSizeSlider.onDragStart = [reverbSizeParameter] { reverbSizeParameter->beginChangeGesture(); };
    mReverbSizeSlider.onDragEnd = [reverbSizeParameter] { reverbSizeParameter->endChangeGesture(); };
    mReverbSizeLabel.setText("SIZE", dontSendNotification);

    // SEND BUTTON EVENTS
    AudioParameterBool* cutoffSendParameter = (AudioParameterBool*)params.getUnchecked(6);
    cutoffSendButton.setToggleState(*cutoffSendParameter, NotificationType::dontSendNotification);
    cutoffSendButton.addListener(this);
    AudioParameterBool* resSendParameter = (AudioParameterBool*)params.getUnchecked(7);
    resSendButton.setToggleState(*resSendParameter, NotificationType::dontSendNotification);
    resSendButton.addListener(this);
    AudioParameterBool* reverbWetSendParameter = (AudioParameterBool*)params.getUnchecked(8);
    resSendButton.setToggleState(*reverbWetSendParameter, NotificationType::dontSendNotification);
    reverbWetSendButton.addListener(this);
    AudioParameterBool* reverbSizeSendParameter = (AudioParameterBool*)params.getUnchecked(9);
    resSendButton.setToggleState(*reverbSizeSendParameter, NotificationType::dontSendNotification);
    reverbSizeSendButton.addListener(this);
    // TODO when DELAY will be ok
    delaySendButton.addListener(this);
    
    // PERFORMANCE
    AudioParameterFloat* perfParameter = (AudioParameterFloat*)params.getUnchecked(10);
    mPerfSlider.setRange(perfParameter->range.start, perfParameter->range.end);
    mPerfSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
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
                                 reverbSizeParameter] { *perfParameter = mPerfSlider.getValue();
        // TODO Skew modification for the cutof...
        mFilterCutoffSlider.setValue(*filterCutoffParameter);
        mFilterResSlider.setValue(*filterResParameter);
        mReverbWetSlider.setValue(*reverbWetParameter);
        mReverbSizeSlider.setValue(*reverbSizeParameter);
    };
    mPerfSlider.onDragStart = [perfParameter] { perfParameter->beginChangeGesture(); };
    mPerfSlider.onDragEnd = [perfParameter] { perfParameter->endChangeGesture(); };

}

TanenLiveV0AudioProcessorEditor::~TanenLiveV0AudioProcessorEditor()
{
}

void TanenLiveV0AudioProcessorEditor::sendFx(Button* button) {
    auto& params = processor.getParameters();
    if (button == &cutoffSendButton) {
        AudioParameterBool* cutoffSendParameter = (AudioParameterBool*)params.getUnchecked(6);
        *cutoffSendParameter = true;
        // TODO le régler quand on active le SENDING pour que le potard se mette au bon endroit direct... là faut cliquer deux fois pour que ça le fasse.
        //AudioParameterFloat* filterCutoffParameter = (AudioParameterFloat*)params.getUnchecked(1);
        //mFilterCutoffSlider.setValue(*filterCutoffParameter);
    } else if (button == &resSendButton) {
        AudioParameterBool* resSendParameter = (AudioParameterBool*)params.getUnchecked(7);
        *resSendParameter = true;
    } else if (button == &reverbWetSendButton) {
        AudioParameterBool* reverbWetSendParameter = (AudioParameterBool*)params.getUnchecked(8);
        *reverbWetSendParameter = true;
    } else if (button == &reverbSizeSendButton) {
        AudioParameterBool* reverbSizeSendParameter = (AudioParameterBool*)params.getUnchecked(9);
        *reverbSizeSendParameter = true;
    }
    button->setToggleState(true, NotificationType::dontSendNotification);
    button->setButtonText("SENDING");
}
void TanenLiveV0AudioProcessorEditor::bypassFx(Button* button) {
    auto& params = processor.getParameters();
    if (button == &cutoffSendButton) {
        AudioParameterBool* cutoffSendParameter = (AudioParameterBool*)params.getUnchecked(6);
        *cutoffSendParameter = false;
    } else if (button == &resSendButton) {
        AudioParameterBool* resSendParameter = (AudioParameterBool*)params.getUnchecked(7);
        *resSendParameter = false;
    } else if (button == &reverbWetSendButton) {
        AudioParameterBool* reverbWetParameter = (AudioParameterBool*)params.getUnchecked(8);
        *reverbWetParameter = false;
    } else if (button == &reverbSizeSendButton) {
        AudioParameterBool* reverbSizeParameter = (AudioParameterBool*)params.getUnchecked(9);
        *reverbSizeParameter = false;
    }
    button->setToggleState(false, NotificationType::dontSendNotification);
    button->setButtonText("BYPASSED");
}

void TanenLiveV0AudioProcessorEditor::buttonClicked(Button* button) {
    // WHAT TO DO AVEC BUTTON CLICKED
    if (button->getToggleStateValue().getValue()) {
        button->onClick =[this, button]() { bypassFx(button); };
    } else {
        button->onClick =[this, button]() { sendFx(button); };
    }
  
}

/*void TanenLiveV0AudioProcessorEditor::clicked() {
    std::cout << "coucou clicked()";
    
}*/

//==============================================================================
void TanenLiveV0AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("TANEN LIVE MACHINE", getLocalBounds(), Justification::centredBottom, 1);
}

void TanenLiveV0AudioProcessorEditor::resized()
{
    //setSize (600 width, 450 height);
    auto area = getLocalBounds();
 
    auto headerHeight = 40;
    auto footerHeight = 60;
    auto header = area.removeFromTop(headerHeight);
    auto footer = area.removeFromBottom(footerHeight);
 
    auto fxWidth = 120; // height = 450 - (40+60) = 350
    auto filterZone = area.removeFromLeft (fxWidth);
    auto reverbZone = area.removeFromLeft (fxWidth);
    auto delayZone = area.removeFromLeft (fxWidth);
    auto performanceZone = area; // width = 500 - 3*(120) = 140
    
    // DRAW FRAMES
    headerFrame.setBounds(header);
    footerFrame.setBounds(footer);
    filterFrame.setBounds(filterZone);
    reverbFrame.setBounds(reverbZone);
    delayFrame.setBounds(delayZone);
    performanceFrame.setBounds(performanceZone);
    // zone in zone :
    auto itemMargin = 15;
    auto imageMargin = 5;
    auto headerMargin = 3;
    auto itemSize = 125;
    auto sendSize = 50;
    auto sendMargin = 10;
    auto labelMargin = 15;
    
    // FILTER
    mFilterType.setBounds(header.removeFromLeft(fxWidth).reduced(headerMargin));
    // cutoff slider
    auto cutoffZone = filterZone.removeFromTop(itemSize);
    mFilterCutoffSlider.setBounds(cutoffZone.reduced(itemMargin));
    // cutoff label
    addAndMakeVisible(mFilterCutoffLabel);
    mFilterCutoffLabel.setJustificationType(Justification::centred);
    mFilterCutoffLabel.setBounds(cutoffZone.removeFromBottom(labelMargin));
    // cutoff send button
    cutoffSendButton.setBounds(filterZone.removeFromTop(sendSize).reduced(sendMargin));
    // res slider
    auto resZone = filterZone.removeFromTop(itemSize);
    mFilterResSlider.setBounds(resZone.reduced(itemMargin));
    // res label
    addAndMakeVisible(mFilterResLabel);
    mFilterResLabel.setJustificationType(Justification::centred);
    mFilterResLabel.setBounds(resZone.removeFromBottom(labelMargin));
    // res send button
    resSendButton.setBounds(filterZone.removeFromTop(sendSize).reduced(sendMargin));

    
    // REVERB
    // dry slider
    mReverbDrySlider.setBounds(header.removeFromLeft(fxWidth).reduced(headerMargin));
    auto wetZone = reverbZone.removeFromTop(itemSize);
    mReverbWetSlider.setBounds(wetZone.reduced(itemMargin));
    // wet label
    addAndMakeVisible(mReverbWetLabel);
    mReverbWetLabel.setJustificationType(Justification::centred);
    mReverbWetLabel.setBounds(wetZone.removeFromBottom(labelMargin));
    // wet send button
    reverbWetSendButton.setBounds(reverbZone.removeFromTop(sendSize).reduced(sendMargin));
    // size slider
    auto sizeZone = reverbZone.removeFromTop(itemSize);
    mReverbSizeSlider.setBounds(sizeZone.reduced(itemMargin));
    // size label
    addAndMakeVisible(mReverbSizeLabel);
    mReverbSizeLabel.setJustificationType(Justification::centred);
    mReverbSizeLabel.setBounds(sizeZone.removeFromBottom(labelMargin));
    // size send button
    reverbSizeSendButton.setBounds(reverbZone.removeFromTop(sendSize).reduced(sendMargin));
    
    // DELAY
    delaySendButton.setBounds(delayZone.removeFromBottom(sendSize).reduced(sendMargin));

    // PERFORMANCE
    mPerfSlider.setBounds(performanceZone);
    mImageComponent.setBounds(performanceZone.reduced(imageMargin));


}

