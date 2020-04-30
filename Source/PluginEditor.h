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
class FilterLookAndFeel : public LookAndFeel_V4
{
public:
    FilterLookAndFeel(){}
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
        {
            auto radius = jmin (width / 2, height / 2) - 4.0f;
            auto centreX = x + width  * 0.5f;
            auto centreY = y + height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
            
            // fill
            g.setColour (Colours::grey);
            g.fillEllipse (rx, ry, rw, rw);
            // outline
            g.setColour (Colours::black);
            g.drawEllipse (rx, ry, rw, rw, 3.0f);
            // pointer
            Path p;
            auto pointerLength = radius * 0.53f;
            auto pointerThickness = 4.0f;
            p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
            p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
            // pointer
            g.setColour (Colours::black);
            g.fillPath (p);
        }
};

class ReverbLookAndFeel : public LookAndFeel_V4
{
public:
    ReverbLookAndFeel(){}
    ~ReverbLookAndFeel(){
        
    }
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
        {
            auto radius = jmin (width / 2, height / 2) - 4.0f;
            auto centreX = x + width  * 0.5f;
            auto centreY = y + height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
            
            // fill
            g.setColour (Colours::lightsteelblue);
            g.fillEllipse (rx, ry, rw, rw);
            // outline
            g.setColour (Colours::black);
            g.drawEllipse (rx, ry, rw, rw, 3.0f);
            // pointer
            Path p;
            auto pointerLength = radius * 0.53f;
            auto pointerThickness = 4.0f;
            p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
            p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
            // pointer
            g.setColour (Colours::black);
            g.fillPath (p);
        }
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override
        {
            auto buttonArea = button.getLocalBounds();
            auto edge = 4;
            buttonArea.removeFromLeft (edge);
            buttonArea.removeFromTop (edge);
            const Colour& colour = isMouseOverButton ? backgroundColour.withAlpha(0.8f) : backgroundColour;
            // shadow
            g.setColour (Colours::darkgrey.withAlpha (0.5f));
            g.fillRect (buttonArea);
            auto offset = isButtonDown ? -edge / 2 : -edge;
            buttonArea.translate (offset, offset);
            g.setColour (colour);
            g.fillRect (buttonArea);

        }
    void drawButtonText (Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override
        {
            auto font = getTextButtonFont (button, button.getHeight());
            g.setFont (font);
            g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                                                    : TextButton::textColourOffId)
                               .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
         
            auto yIndent = jmin (4, button.proportionOfHeight (0.3f));
            auto cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;
         
            auto fontHeight = roundToInt (font.getHeight() * 0.6f);
            auto leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft()  ? 4 : 2));
            auto rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
            auto textWidth = button.getWidth() - leftIndent - rightIndent;
 
            auto edge = 4;
            auto offset = isButtonDown ? edge / 2 : 0;
            if (textWidth > 0)
                g.drawFittedText (button.getButtonText(),
                                  leftIndent + offset, yIndent + offset, textWidth, button.getHeight() - yIndent * 2 - edge,
                                  Justification::centred, 2);
        }
};

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

    ImageComponent mImageComponent;
    FilterLookAndFeel filterLook;
    ReverbLookAndFeel reverbLook;
    // TANEN LIVE General Parameters
    TextButton byPassButton{"BYPASS"}, b2{"2"}, b3{"3"};
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
