/*
  ==============================================================================

    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
 
    Plugin developed by Maxime Boiron starting from March 2020
    Name : Tanen Live Machine
    Version : V0
    GitHub project: https://github.com/maxiskywalker666/tanenlivev0.git
 
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================

/** SliderLookAndFeel class:
                        - declares a new drawRotarySlider method to make a custon slider
                        - declares two members (sliderFillColour, sliderPointerColour) with setters to be able tu custom the slider colours
*/
class SliderLookAndFeel : public LookAndFeel_V4
{
public:
    SliderLookAndFeel(){}
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
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

/** TanenLiveV0AudioProcessorEditor class:
                            - contains the declaration of the general parameters and methods that will be used in the Editor for the UI
                            - declares all the variables and methods for the editor
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
    void buttonClicked(Button* button) override;
    void sendFx(Button* button);
    void bypassFx(Button* button);
    void drawSendLines(Graphics&);

private:
    TanenLiveV0AudioProcessor& processor;
    
    // IMAGES
    ImageComponent t1000ImageComponent;
    
    // TEXT
    String filterTitleText              = "FILTER";
    String reverbTitleText              = "REVERB";
    String delayTitleText               = "DESCTRUCT DELAY";
    String offSendButtonText            = "FREE";
    String onSendButtonText             = "CONTROLLED";
    String filterLowPassText            = "LOWPASS";
    String filterHiPassText             = "HIPASS";
    String filterCutoffText             = "CUTOFF";
    String filterResText                = "RESONANCE";
    String reverbDryText                = "DRY";
    String reverbWetText                = "WET";
    String reverbSizeText               = "ROOMSIZE";
    String delayDryWetText              = "DRY/WET";
    String delayDepthText               = "DEPTH";
    String delayRateText                = "RATE";
    String delayFeedbackText            = "FEEEDBACK";
    String delayXTremFeedbackText       = "X-TREM FEEDBACK";
    
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
    TextButton cutoffSendButton{offSendButtonText};
    TextButton resSendButton{offSendButtonText};
    
    // REVERB Parameters
    Label mReverbTitle;
    Slider mReverbWetSlider;
    Label mReverbWetLabel;
    Slider mReverbSizeSlider;
    Label mReverbSizeLabel;
    Slider mReverbDrySlider;
    Label mReverbDryLabel;
    TextButton reverbWetSendButton{offSendButtonText};
    TextButton reverbSizeSendButton{offSendButtonText};
    
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
    TextButton delayDryWetSendButton{offSendButtonText};
    TextButton delayDepthSendButton{offSendButtonText};
    TextButton delayRateSendButton{offSendButtonText};
    TextButton delayFeedbackSendButton{offSendButtonText};
    Slider mXTremFeedbackSlider;
    Label mXTremFeedbackLabel;
    
    // PERFORMANCE Parameters
    Slider mPerfSlider;
    
    // GUI VARIABLES
    float pluginWidth            = 600.f;
    float pluginHeight           = 490.f;
    float fontSize               = 15.f;
    float logoFontSize           = 20.f;
    float headerHeight           = 80.f;
    float headerTitlesHeight     = 40.f;
    float footerHeight           = 60.f;
    float fxWidth                = 120.f;
    float itemSize               = 125.f;
    float itemMargin             = 15.f;
    float imageMargin            = 100.f;
    float headerMargin           = 3.f;
    float filterTypeMargin       = 5.f;
    float sendSize               = 50.f;
    float sendMargin             = 10.f;
    float labelMargin            = 15.f;
    float lineThickness          = 4.f;
    
    // COLOURS
    float perfOpacity= 0.7f;
    Colour almostBlack             = Colour(18, 18, 18);
    Colour fontColour              = Colour(255, 255, 255);
    Colour lightGrey               = Colour(84, 83, 83);
    Colour darkDarkGrey            = Colour(29, 29, 29);
    Colour grey                    = Colour(61, 61, 61);
    Colour darkGrey                = Colour(43, 43, 43);
    Colour lightBlue               = Colour(182, 193, 215);
    
    Colour backgroundColor         = almostBlack;
    Colour bypassedLinesColour     = lightGrey;
    Colour sendingLinesColour      = lightBlue.withAlpha(perfOpacity);
    
    
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
