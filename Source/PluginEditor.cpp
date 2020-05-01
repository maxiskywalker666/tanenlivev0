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
    auto t1000Image = ImageCache::getFromMemory(BinaryData::T1000_png, BinaryData::T1000_pngSize);
    if (!t1000Image.isNull())
        mImageComponent.setImage(t1000Image, RectanglePlacement::stretchToFit);
    else
        jassert(!t1000Image.isNull());
    addAndMakeVisible(mImageComponent);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 450);
    byPassButton.setLookAndFeel(&reverbLook);
    addAndMakeVisible(byPassButton);
    
    auto& params = processor.getParameters();
    // COMBOBOX FILTER TYPE
    AudioParameterInt* filterTypeParameter = (AudioParameterInt*)params.getUnchecked(5);
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
    AudioParameterFloat* filterCutoffParameter = (AudioParameterFloat*)params.getUnchecked(0);
    mFilterCutoffSlider.setRange(filterCutoffParameter->range.start, filterCutoffParameter->range.end);
    mFilterCutoffSlider.setBounds(0, 30, 100, 100);
    mFilterCutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFilterCutoffSlider.setValue(*filterCutoffParameter);
    mFilterCutoffSlider.setLookAndFeel(&filterLook);
    addAndMakeVisible(mFilterCutoffSlider);
    
    mFilterCutoffSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mFilterCutoffSlider.onValueChange = [this, filterCutoffParameter] { *filterCutoffParameter = mFilterCutoffSlider.getValue(); };
    mFilterCutoffSlider.onDragStart = [filterCutoffParameter] { filterCutoffParameter->beginChangeGesture(); };
    mFilterCutoffSlider.onDragEnd = [filterCutoffParameter] { filterCutoffParameter->endChangeGesture(); };
    mFilterCutoffSlider.setTextValueSuffix (" Hz");     // [2]
    //mFilterCutoffSlider.addListener (this);
    // frequency label
    addAndMakeVisible (frequencyLabel);
    //frequencyLabel.setBounds(0, 100, 100, 100);
    frequencyLabel.setText ("CUTOFF", dontSendNotification);
    frequencyLabel.attachToComponent (&mFilterCutoffSlider, false);
    
    // FILTER RESONANCE
    AudioParameterFloat* filterResonanceParameter = (AudioParameterFloat*)params.getUnchecked(1);
    mFilterResSlider.setRange(filterResonanceParameter->range.start, filterResonanceParameter->range.end);
    mFilterResSlider.setBounds(0, 160, 100, 100);
    mFilterResSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFilterResSlider.setValue(*filterResonanceParameter);
    mFilterResSlider.setLookAndFeel(&filterLook);
    addAndMakeVisible(mFilterResSlider);
    
    mFilterResSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mFilterResSlider.onValueChange = [this, filterResonanceParameter] { *filterResonanceParameter = mFilterResSlider.getValue(); };
    mFilterResSlider.onDragStart = [filterResonanceParameter] { filterResonanceParameter->beginChangeGesture(); };
    mFilterResSlider.onDragEnd = [filterResonanceParameter] { filterResonanceParameter->endChangeGesture(); };
    // resonance label
    addAndMakeVisible (resonanceLabel);
    //frequencyLabel.setBounds(0, 100, 100, 100);
    resonanceLabel.setText ("RESONANCE", dontSendNotification);
    resonanceLabel.attachToComponent (&mFilterResSlider, false);
    
    // REVERB DRYWET
    AudioParameterFloat* reverbDryWetParameter = (AudioParameterFloat*)params.getUnchecked(2);
    mReverbDryWetSlider.setRange(reverbDryWetParameter->range.start, reverbDryWetParameter->range.end);
    mReverbDryWetSlider.setBounds(110, 0, 100, 100);
    mReverbDryWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbDryWetSlider.setValue(*reverbDryWetParameter);
    mReverbDryWetSlider.setLookAndFeel(&reverbLook);
    addAndMakeVisible(mReverbDryWetSlider);
    
    mReverbDryWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbDryWetSlider.onValueChange = [this, reverbDryWetParameter] { *reverbDryWetParameter = mReverbDryWetSlider.getValue(); };
    mReverbDryWetSlider.onDragStart = [reverbDryWetParameter] { reverbDryWetParameter->beginChangeGesture(); };
    mReverbDryWetSlider.onDragEnd = [reverbDryWetParameter] { reverbDryWetParameter->endChangeGesture(); };
    
    // REVERB ROOMSIZE
    AudioParameterFloat* reverbRoomSizeParameter = (AudioParameterFloat*)params.getUnchecked(3);
    mReverbRoomSizeSlider.setRange(reverbRoomSizeParameter->range.start, reverbRoomSizeParameter->range.end);
    mReverbRoomSizeSlider.setBounds(110, 120, 100, 100);
    mReverbRoomSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbRoomSizeSlider.setValue(*reverbRoomSizeParameter);
    mReverbRoomSizeSlider.setLookAndFeel(&reverbLook);
    addAndMakeVisible(mReverbRoomSizeSlider);
    
    mReverbRoomSizeSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbRoomSizeSlider.onValueChange = [this, reverbRoomSizeParameter] { *reverbRoomSizeParameter = mReverbRoomSizeSlider.getValue(); };
    mReverbRoomSizeSlider.onDragStart = [reverbRoomSizeParameter] { reverbRoomSizeParameter->beginChangeGesture(); };
    mReverbRoomSizeSlider.onDragEnd = [reverbRoomSizeParameter] { reverbRoomSizeParameter->endChangeGesture(); };
    
    // REVERB WIDTH
    AudioParameterFloat* reverbWidthParameter = (AudioParameterFloat*)params.getUnchecked(4);
    mReverbWidthSlider.setRange(reverbWidthParameter->range.start, reverbWidthParameter->range.end);
    mReverbWidthSlider.setBounds(110, 240, 100, 100);
    mReverbWidthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbWidthSlider.setValue(*reverbWidthParameter);
    mReverbWidthSlider.setLookAndFeel(&reverbLook);
    addAndMakeVisible(mReverbWidthSlider);
    
    mReverbWidthSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbWidthSlider.onValueChange = [this, reverbWidthParameter] { *reverbWidthParameter = mReverbRoomSizeSlider.getValue(); };
    mReverbWidthSlider.onDragStart = [reverbWidthParameter] { reverbWidthParameter->beginChangeGesture(); };
    mReverbWidthSlider.onDragEnd = [reverbWidthParameter] { reverbWidthParameter->endChangeGesture(); };
}

TanenLiveV0AudioProcessorEditor::~TanenLiveV0AudioProcessorEditor()
{
}

//==============================================================================
void TanenLiveV0AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("TANEN LIVE MACHINE", getLocalBounds(), Justification::centredBottom, 1);
}

void TanenLiveV0AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto r = getLocalBounds();
    mImageComponent.setBounds(280, 10, 220, 240);
    
    byPassButton.setBounds(110, 380, 100, 30);
}

