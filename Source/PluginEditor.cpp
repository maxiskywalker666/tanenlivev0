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
    mReverbWetSlider.setRange(reverbDryWetParameter->range.start, reverbDryWetParameter->range.end);
    mReverbWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReverbWetSlider.setValue(*reverbDryWetParameter);
    mReverbWetSlider.setLookAndFeel(&reverbLook);
    addAndMakeVisible(mReverbWetSlider);
    
    mReverbWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mReverbWetSlider.onValueChange = [this, reverbDryWetParameter] { *reverbDryWetParameter = mReverbWetSlider.getValue(); };
    mReverbWetSlider.onDragStart = [reverbDryWetParameter] { reverbDryWetParameter->beginChangeGesture(); };
    mReverbWetSlider.onDragEnd = [reverbDryWetParameter] { reverbDryWetParameter->endChangeGesture(); };
    mReverbWetLabel.setText("WET", dontSendNotification);
    
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

    // SEND BUTTON EVENTS
    AudioParameterBool* cutoffSendParameter = (AudioParameterBool*)params.getUnchecked(5);
    cutoffSendButton.setToggleState(*cutoffSendParameter, NotificationType::dontSendNotification);
    cutoffSendButton.addListener(this);
    cutoffSendButton.onClick = [this, cutoffSendParameter]() {
        if (*cutoffSendParameter == true) {
            *cutoffSendParameter = false;
        } else {
            *cutoffSendParameter = true;
        }
    };
    resSendButton.setToggleState(false, NotificationType::dontSendNotification);
    resSendButton.addListener(this);
    reverbWetSendButton.addListener(this);
    reverbSizeSendButton.addListener(this);
    delaySendButton.addListener(this);
}

TanenLiveV0AudioProcessorEditor::~TanenLiveV0AudioProcessorEditor()
{
}

void TanenLiveV0AudioProcessorEditor::sendFx(Button* button) {
    auto& params = processor.getParameters();
    if (button == &cutoffSendButton) {
        AudioParameterBool* cutoffSendParameter = (AudioParameterBool*)params.getUnchecked(5);
        *cutoffSendParameter = true;
    }
    button->setToggleState(true, NotificationType::dontSendNotification);
    button->setButtonText("SENDING");
}
void TanenLiveV0AudioProcessorEditor::bypassFx(Button* button) {
    auto& params = processor.getParameters();
    if (button == &cutoffSendButton) {
        AudioParameterBool* cutoffSendParameter = (AudioParameterBool*)params.getUnchecked(5);
        *cutoffSendParameter = false;
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
    //mReverbDryWetSlider.setBounds(reverbZone.removeFromTop(itemSize).reduced(itemMargin));
    //mReverbRoomSizeSlider.setBounds(reverbZone.removeFromTop(itemSize+itemMargin).reduced(itemMargin));
    // drywet slider
    auto dryWetZone = reverbZone.removeFromTop(itemSize);
    mReverbWetSlider.setBounds(dryWetZone.reduced(itemMargin));
    // drywet label
    addAndMakeVisible(mReverbWetLabel);
    mReverbWetLabel.setJustificationType(Justification::centred);
    mReverbWetLabel.setBounds(dryWetZone.removeFromBottom(labelMargin));
    // drywet send button
    reverbWetSendButton.setBounds(reverbZone.removeFromTop(sendSize).reduced(sendMargin));
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

