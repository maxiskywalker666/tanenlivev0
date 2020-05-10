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
class SliderLookAndFeel : public LookAndFeel_V4
{
public:
    SliderLookAndFeel(){}
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
            g.setColour (sliderFillColour);
            g.fillEllipse (rx, ry, rw, rw);
            // outline
            g.setColour (sliderPointerColour);
            g.drawEllipse (rx, ry, rw, rw, 3.0f);
            // pointer
            Path p;
            auto pointerLength = radius * 0.53f;
            auto pointerThickness = 4.0f;
            p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
            p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
            // pointer
            g.setColour (sliderPointerColour);
            g.fillPath (p);
        }
    void setSliderFillColour(Colour c) {
        sliderFillColour = c;
    }
    void setSliderPointerColour(Colour c) {
        sliderPointerColour = c;
    }
private:
    Colour sliderFillColour = Colour(84, 83, 83); // lightGrey
    Colour sliderPointerColour = Colour(182, 193, 215); // lightBlue
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
    TanenLiveV0AudioProcessor& processor;
    // TANEN LIVE General Parameters
    // IMAGES
    ImageComponent t1000ImageComponent;
    // LOOKANDFEEL
    SliderLookAndFeel filterLook;
    SliderLookAndFeel reverbLook;
    SliderLookAndFeel delayLook;
    Rectangle<int> headerTitlesRectangle;
    Rectangle<int> performanceTitleRectangle;
    // FILTER Parameters
    Label mFilterTitle;
    ComboBox mFilterType;
    Slider mFilterCutoffSlider;
    Label mFilterCutoffLabel;
    Slider mFilterResSlider;
    Label mFilterResLabel;
    TextButton cutoffSendButton{"BYPASSED"};
    TextButton resSendButton{"BYPASSED"};
    //TextButton filterSendButton{"SEND"};
    // REVERB Parameters
    Label mReverbTitle;
    Slider mReverbWetSlider;
    Label mReverbWetLabel;
    Slider mReverbSizeSlider;
    Label mReverbSizeLabel;
    Slider mReverbDrySlider; // horizontal slider in the header
    Label mReverbDryLabel;
    TextButton reverbWetSendButton{"BYPASSED"};
    TextButton reverbSizeSendButton{"BYPASSED"};
    // DELAY Parameters
    Label mDelayTitle;
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
    Slider mXTremFeedbackSlider;
    Label mXTremFeedbackLabel;
    // PERFORMANCE Parameters
    Slider mPerfSlider;
    
    // GUI VARIABLES
    float pluginWidth = 600.f;
    float pluginHeight = 490.f;
    float fontSize = 15.f;
    float logoFontSize = 20.f;
    float headerHeight = 80.f;
    float headerTitlesHeight = 40.f;
    float footerHeight = 60.f;
    
    float itemMargin = 15.f;
    float imageMargin = 100.f;
    float headerMargin = 3.f;
    float filterTypeMargin = 5.f;
    float itemSize = 125.f;
    float sendSize = 50.f;
    //float sendMargin = 10.f;
    float sendMargin = 10.f;
    float labelMargin = 15.f;
    
    float perfOpacity= 0.7f;
    float fxWidth = 120.f;
    float lineThickness = 4.f;
    
    // COLOURS
    //Colour goodRed                 = Colour(220, 19, 19);
    Colour almostBlack             = Colour(18, 18, 18);
    Colour fontColour              = Colours::white;
    Colour lightGrey               = Colour(84, 83, 83);
    Colour darkDarkGrey            = Colour(29, 29, 29);
    Colour grey                    = Colour(61, 61, 61);
    Colour darkGrey                = Colour(43, 43, 43);
    Colour lightBlue               = Colour(182, 193, 215);
    
    Colour backgroundColor         = almostBlack;
    Colour bypassedLinesColour     = lightGrey;
    Colour sendingLinesColour      = lightBlue.withAlpha(perfOpacity); // NOW BLUE
    
    
    // ALL SENDING LINES
    // upper left
    Colour filterCutoffSendColour  = bypassedLinesColour;
    Colour reverbWetSendColour     = bypassedLinesColour;
    Colour filRevUpperSendColour   = bypassedLinesColour;
    // lower left
    Colour filterResSendColour     = bypassedLinesColour;
    Colour reverbSizeSendColour    = bypassedLinesColour;
    Colour filRevLowerSendColour   = bypassedLinesColour;
    // upper right
    Colour delayDryWetSendColour   = bypassedLinesColour;
    Colour delayRateSendColour     = bypassedLinesColour;
    Colour delayUpperSendColour    = bypassedLinesColour;
    // lower right
    Colour delayDepthSendColour    = bypassedLinesColour;
    Colour delayFeedbackSendColour = bypassedLinesColour;
    Colour delayLowerSendColour    = bypassedLinesColour;
    // center (performance)
    Colour joinFinalSendColour     = bypassedLinesColour;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TanenLiveV0AudioProcessorEditor)
};
