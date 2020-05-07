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
    mImageComponent.setBounds(280, 10, 220, 240);
    
    // WINDOW SIZE
    setSize (500, 500);
    
    // BYPASS BUTTON
    reverbSendButton.setLookAndFeel(&reverbLook);
    addAndMakeVisible(reverbSendButton);
    reverbSendButton.setBounds(110, 380, 100, 30);
    
    auto& params = processor.getParameters();
    // COMBOBOX FILTER TYPE
    AudioParameterInt* filterTypeParameter = (AudioParameterInt*)params.getUnchecked(0);
    mFilterType.setBounds(0, 280, 100, 30);
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
    mFilterCutoffSlider.setBounds(0, 30, 100, 100);
    mFilterCutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFilterCutoffSlider.setValue(*filterCutoffParameter);
    mFilterCutoffSlider.setSkewFactorFromMidPoint (500);
    mFilterCutoffSlider.setLookAndFeel(&filterLook);
    addAndMakeVisible(mFilterCutoffSlider);
    
    mFilterCutoffSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, true, 100, mFilterCutoffSlider.getTextBoxHeight());
    mFilterCutoffSlider.onValueChange = [this, filterCutoffParameter] { *filterCutoffParameter = mFilterCutoffSlider.getValue(); };
    mFilterCutoffSlider.onDragStart = [filterCutoffParameter] { filterCutoffParameter->beginChangeGesture(); };
    mFilterCutoffSlider.onDragEnd = [filterCutoffParameter] { filterCutoffParameter->endChangeGesture(); };
    mFilterCutoffSlider.setTextValueSuffix (" Hz");     // [2]
    //mFilterCutoffSlider.addListener (this);
    // frequency label
    mFilterCutoffLabel.setText ("CUTOFF", dontSendNotification);
    mFilterCutoffLabel.attachToComponent (&mFilterCutoffSlider, false);
    
    // FILTER RESONANCE
    AudioParameterFloat* filterResonanceParameter = (AudioParameterFloat*)params.getUnchecked(2);
    mFilterResSlider.setRange(filterResonanceParameter->range.start, filterResonanceParameter->range.end);
    mFilterResSlider.setBounds(0, 160, 100, 100);
    mFilterResSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFilterResSlider.setValue(*filterResonanceParameter);
    mFilterResSlider.setLookAndFeel(&filterLook);
    addAndMakeVisible(mFilterResSlider);
    
    mFilterResSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, true, 100, mFilterResSlider.getTextBoxHeight());
    mFilterResSlider.onValueChange = [this, filterResonanceParameter] { *filterResonanceParameter = mFilterResSlider.getValue(); };
    mFilterResSlider.onDragStart = [filterResonanceParameter] { filterResonanceParameter->beginChangeGesture(); };
    mFilterResSlider.onDragEnd = [filterResonanceParameter] { filterResonanceParameter->endChangeGesture(); };
    // resonance label
    mFilterResLabel.setText ("RESONANCE", dontSendNotification);
    mFilterResLabel.attachToComponent (&mFilterResSlider, false);
    
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
    mReverbDryWetLabel.setText ("DRY/WET", dontSendNotification);
    //mReverbDryWetLabel.attachToComponent (&mReverbDryWetSlider, false);
    
    // REVERB ROOMSIZE
    AudioParameterFloat* reverbRoomSizeParameter = (AudioParameterFloat*)params.getUnchecked(4);
    mReverbRoomSizeSlider.setRange(reverbRoomSizeParameter->range.start, reverbRoomSizeParameter->range.end);
    mReverbRoomSizeSlider.setBounds(110, 170, 100, 100);
    mReverbRoomSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbRoomSizeSlider.setValue(*reverbRoomSizeParameter);
    mReverbRoomSizeSlider.setLookAndFeel(&reverbLook);
    //addAndMakeVisible(mReverbRoomSizeSlider);
    
    mReverbRoomSizeSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbRoomSizeSlider.onValueChange = [this, reverbRoomSizeParameter] { *reverbRoomSizeParameter = mReverbRoomSizeSlider.getValue(); };
    mReverbRoomSizeSlider.onDragStart = [reverbRoomSizeParameter] { reverbRoomSizeParameter->beginChangeGesture(); };
    mReverbRoomSizeSlider.onDragEnd = [reverbRoomSizeParameter] { reverbRoomSizeParameter->endChangeGesture(); };
    
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
    //setSize (500, 500);
    auto area = getLocalBounds();
 
    auto headerHeight = 40;
    auto footerHeight = 60;
    auto header = area.removeFromTop(headerHeight);
    auto footer = area.removeFromBottom(footerHeight);
 
    auto fxWidth = 120; // height = 500 - (20+30) = 450
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
    auto ItemMargin = 15;
    // sideItemA.setBounds (sideBarArea.removeFromTop (sideItemHeight).reduced (sideItemMargin));
    
    mImageComponent.setBounds(280, 10, 220, 240);
    reverbSendButton.setBounds(110, 380, 100, 30);
    
    // REVERB
    //mReverbDryWetSlider.setBounds(110, 30, 100, 100);
    mReverbDryWetSlider.setBounds(reverbZone.reduced(ItemMargin));
    mReverbDryWetLabel.attachToComponent (&mReverbDryWetSlider, false);

    
}

