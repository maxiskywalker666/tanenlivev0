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
    cutoffSendButton.setLookAndFeel(&sendLook);
    addAndMakeVisible(cutoffSendButton);
    resSendButton.setLookAndFeel(&sendLook);
    addAndMakeVisible(resSendButton);
    reverbDryWetSendButton.setLookAndFeel(&sendLook);
    addAndMakeVisible(reverbDryWetSendButton);
    reverbSizeSendButton.setLookAndFeel(&sendLook);
    addAndMakeVisible(reverbSizeSendButton);
    delaySendButton.setLookAndFeel(&sendLook);
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
    mFilterCutoffSlider.setSkewFactorFromMidPoint (500);
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
    AudioParameterFloat* filterResonanceParameter = (AudioParameterFloat*)params.getUnchecked(2);
    mFilterResSlider.setRange(filterResonanceParameter->range.start, filterResonanceParameter->range.end);
    //mFilterResSlider.setBounds(0, 160, 100, 100);
    mFilterResSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFilterResSlider.setValue(*filterResonanceParameter);
    mFilterResSlider.setLookAndFeel(&filterLook);
    addAndMakeVisible(mFilterResSlider);
    
    mFilterResSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 100, mFilterResSlider.getTextBoxHeight());
    mFilterResSlider.onValueChange = [this, filterResonanceParameter] { *filterResonanceParameter = mFilterResSlider.getValue(); };
    mFilterResSlider.onDragStart = [filterResonanceParameter] { filterResonanceParameter->beginChangeGesture(); };
    mFilterResSlider.onDragEnd = [filterResonanceParameter] { filterResonanceParameter->endChangeGesture(); };
    // resonance label
    mFilterResLabel.setText("RESONANCE", dontSendNotification);
    
    // REVERB DRYWET
    AudioParameterFloat* reverbDryWetParameter = (AudioParameterFloat*)params.getUnchecked(3);
    mReverbDryWetSlider.setRange(reverbDryWetParameter->range.start, reverbDryWetParameter->range.end);
    mReverbDryWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbDryWetSlider.setValue(*reverbDryWetParameter);
    mReverbDryWetSlider.setLookAndFeel(&reverbLook);
    addAndMakeVisible(mReverbDryWetSlider);
    
    mReverbDryWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbDryWetSlider.onValueChange = [this, reverbDryWetParameter] { *reverbDryWetParameter = mReverbDryWetSlider.getValue(); };
    mReverbDryWetSlider.onDragStart = [reverbDryWetParameter] { reverbDryWetParameter->beginChangeGesture(); };
    mReverbDryWetSlider.onDragEnd = [reverbDryWetParameter] { reverbDryWetParameter->endChangeGesture(); };
    mReverbDryWetLabel.setText("DRY/WET", dontSendNotification);
    
    // REVERB ROOMSIZE
    AudioParameterFloat* reverbRoomSizeParameter = (AudioParameterFloat*)params.getUnchecked(4);
    mReverbRoomSizeSlider.setRange(reverbRoomSizeParameter->range.start, reverbRoomSizeParameter->range.end);
    mReverbRoomSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbRoomSizeSlider.setValue(*reverbRoomSizeParameter);
    mReverbRoomSizeSlider.setLookAndFeel(&reverbLook);
    addAndMakeVisible(mReverbRoomSizeSlider);
    
    mReverbRoomSizeSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbRoomSizeSlider.onValueChange = [this, reverbRoomSizeParameter] { *reverbRoomSizeParameter = mReverbRoomSizeSlider.getValue(); };
    mReverbRoomSizeSlider.onDragStart = [reverbRoomSizeParameter] { reverbRoomSizeParameter->beginChangeGesture(); };
    mReverbRoomSizeSlider.onDragEnd = [reverbRoomSizeParameter] { reverbRoomSizeParameter->endChangeGesture(); };
    mReverbRoomSizeLabel.setText("SIZE", dontSendNotification);

    
}

TanenLiveV0AudioProcessorEditor::~TanenLiveV0AudioProcessorEditor()
{
}

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
    //mReverbDryWetSlider.setBounds(reverbZone.removeFromTop(itemSize).reduced(itemMargin));
    //mReverbRoomSizeSlider.setBounds(reverbZone.removeFromTop(itemSize+itemMargin).reduced(itemMargin));
    // drywet slider
    auto dryWetZone = reverbZone.removeFromTop(itemSize);
    mReverbDryWetSlider.setBounds(dryWetZone.reduced(itemMargin));
    // drywet label
    addAndMakeVisible(mReverbDryWetLabel);
    mReverbDryWetLabel.setJustificationType(Justification::centred);
    mReverbDryWetLabel.setBounds(dryWetZone.removeFromBottom(labelMargin));
    // drywet send button
    reverbDryWetSendButton.setBounds(reverbZone.removeFromTop(sendSize).reduced(sendMargin));
    // size slider
    auto sizeZone = reverbZone.removeFromTop(itemSize);
    mReverbRoomSizeSlider.setBounds(sizeZone.reduced(itemMargin));
    // size label
    addAndMakeVisible(mReverbRoomSizeLabel);
    mReverbRoomSizeLabel.setJustificationType(Justification::centred);
    mReverbRoomSizeLabel.setBounds(sizeZone.removeFromBottom(labelMargin));
    // size send button
    reverbSizeSendButton.setBounds(reverbZone.removeFromTop(sendSize).reduced(sendMargin));
    
    // DELAY
    delaySendButton.setBounds(delayZone.removeFromBottom(sendSize).reduced(sendMargin));

    // PERFORMANCE
    mImageComponent.setBounds(performanceZone.reduced(imageMargin));


    
}

