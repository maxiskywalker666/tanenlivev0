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
};

class DelayLookAndFeel : public LookAndFeel_V4
{
public:
    DelayLookAndFeel(){}
    ~DelayLookAndFeel(){
        
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
            g.setColour (Colours::mediumpurple);
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

class SendLookAndFeel : public LookAndFeel_V4
{
public:
    SendLookAndFeel(){}
    ~SendLookAndFeel(){
        
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
class TanenLiveV0AudioProcessorEditor  : public AudioProcessorEditor,
                                         public Button::Listener

{
public:
    TanenLiveV0AudioProcessorEditor (TanenLiveV0AudioProcessor&);
    ~TanenLiveV0AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sendFx(Button* button);
    void bypassFx(Button* button);
    void buttonClicked(Button* button) override;
    void drawSendLines(Graphics&);

private:
    // ZONES
    TextButton headerFrame;
    TextButton footerFrame;
    TextButton filterFrame;
    TextButton reverbFrame;
    TextButton delayFrame;
    TextButton performanceFrame;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TanenLiveV0AudioProcessor& processor;
    ImageComponent mImageComponent;
    FilterLookAndFeel filterLook;
    ReverbLookAndFeel reverbLook;
    DelayLookAndFeel delayLook;
    SendLookAndFeel sendLook;
    // TANEN LIVE General Parameters
    // FILTER Parameters
    Slider mFilterCutoffSlider;
    Label mFilterCutoffLabel;
    Slider mFilterResSlider;
    Label mFilterResLabel;
    ComboBox mFilterType;
    TextButton cutoffSendButton{"BYPASSED"};
    TextButton resSendButton{"BYPASSED"};
    //TextButton filterSendButton{"SEND"};
    // REVERB Parameters
    Slider mReverbDrySlider;
    Slider mReverbWetSlider;
    Label mReverbWetLabel;
    Slider mReverbSizeSlider;
    Label mReverbSizeLabel;
    Slider mDrySlider; // horizontale slider in the header
    TextButton reverbWetSendButton{"BYPASSED"};
    TextButton reverbSizeSendButton{"BYPASSED"};
    // DELAY Parameters
    Slider mDelayDryWetSlider;
    Label mDelayDryWetLabel;
    Slider mDelayDepthSlider;
    Label mDelayDepthLabel;
    Slider mDelayRateSlider;
    Label mDelayRateLabel;
    Slider mDelayFeedbackSlider;
    Label mDelayFeedbackLabel;
    TextButton delayDryWetSendButton{"BYPASSED"};
    TextButton delayDepthSendButton{"BYPASSED"};
    TextButton delayRateSendButton{"BYPASSED"};
    TextButton delayFeedbackSendButton{"BYPASSED"};
    // TODO Replace useless PhaseOffsetSlider with Checkbox ReverseTime
    Slider mDelayPhaseOffsetSlider;
    Label mDelayPhaseOffsetLabel;
    // PERFORMANCE Parameters
    Slider mPerfSlider;
    
    // GUI VARIABLES
    float fontSize = 15.f;
    float pluginWidth = 600.f;
    float pluginHeight = 450.f;
    float headerHeight = 40.f;
    float footerHeight = 60.f;
    
    float itemMargin = 15.f;
    float imageMargin = 100.f;
    float headerMargin = 3.f;
    float itemSize = 125.f;
    float sendSize = 50.f;
    float sendMargin = 10.f;
    float labelMargin = 15.f;
    
    float perfOpacity= 0.5f;
    float fxWidth = 120.f;
    float lineThickness = 4.f;
    
    Colour bypassedLinesColour = Colours::white.withAlpha(0.5f);
    Colour sendingLinesColour = Colours::red.withAlpha(0.5f);
    // 8 SEND BUTTONS
    Colour filterCutoffSendColour  = Colours::white.withAlpha(0.5f);
    Colour reverbWetSendColour     = Colours::white.withAlpha(0.5f);
    Colour filRevUpperSendColour   = Colours::white.withAlpha(0.5f);

    Colour filterResSendColour     = Colours::white.withAlpha(0.5f);
    Colour reverbSizeSendColour    = Colours::white.withAlpha(0.5f);
    Colour filRevLowerSendColour   = Colours::white.withAlpha(0.5f);

    Colour joinFinalSendColour     = Colours::white.withAlpha(0.5f);
    
    Colour delayDryWetSendColour   = Colours::white.withAlpha(0.5f);
    Colour delayDepthSendColour    = Colours::white.withAlpha(0.5f);
    Colour delayRateSendColour     = Colours::white.withAlpha(0.5f);
    Colour delayFeedbackSendColour = Colours::white.withAlpha(0.5f);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TanenLiveV0AudioProcessorEditor)
};
