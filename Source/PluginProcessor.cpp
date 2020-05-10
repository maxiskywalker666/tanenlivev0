/*
  ==============================================================================

    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
    
    Plugin developed by Maxime Boiron starting from March 2020
    Name : Tanen Live Machine
    Version : V0
    GitHub project: https://github.com/maxiskywalker666/tanenlivev0.git
 
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
TanenLiveV0AudioProcessor::TanenLiveV0AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                       .withOutput ("Output", AudioChannelSet::stereo(), true))
                        , iIRFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))

#endif
{
    // VAR INIT
    lastSampleRate = 44100;
    freqMin = 20.f;
    freqMax = 20000.f;
    resMin = 1.f;
    resMax = 5.f;
    // DELAY VAR INIT
    mCircularBufferLeft = nullptr;
    mCircularBufferRight = nullptr;
    mCircularBufferWriteHead = 0;
    mCircularBufferLength = 0;
    mDelayTimeInSamples = 0;
    mDelayReadHead = 0;
    mFeedbackLeft = 0;
    mFeedbackRight = 0;
    mDelayTimeSmoothed = 0;
    mLFOPhase = 0;
    rateMin = 0.001f;
    rateMax = 50.f;
    xTremFeedbackMax = 0.1f;
    feedbackMax = 0.98f;
    // PARAMETERS INIT
    addParameter(mFilterTypeParameter       = new AudioParameterInt  ("filterType", "FilterType", 0, 1, 0));                           // 0
    addParameter(mFilterCutoffParameter     = new AudioParameterFloat("cutoff", "Cutoff", freqMin, freqMax, 20000.f));                 // 1
    addParameter(mFilterResParameter        = new AudioParameterFloat("resonance", "Resonance", resMin, resMax, 1.f));                 // 2
    addParameter(mReverbDryParameter        = new AudioParameterFloat("dryReverb", "DryReverb", 0.f, 1.f, 1.f));                       // 3
    addParameter(mReverbWetParameter        = new AudioParameterFloat("wetReverb", "WetReverb", 0.f, 1.f, 0.f));                       // 4
    addParameter(mReverbSizeParameter       = new AudioParameterFloat("roomSizeReverb", "RoomSizeReverb", 0.f, 1.f, 0.f));             // 5
    addParameter(mCutoffSendParameter       = new AudioParameterBool ("cutoffSend", "CutoffSend", false));                             // 6
    addParameter(mResSendParameter          = new AudioParameterBool ("resSend", "ResSend", false));                                   // 7
    addParameter(mReverbWetSendParameter    = new AudioParameterBool ("reverbWetSend", "ReverbWetSend", false));                       // 8
    addParameter(mReverbSizeSendParameter   = new AudioParameterBool ("reverbSizeSend", "ReverbSizeSend", false));                     // 9
    addParameter(mPerfParameter             = new AudioParameterFloat("performance", "Performance", 0.f, 1.f, 0.f));                   // 10
    addParameter(mDelayDryWetParameter      = new AudioParameterFloat("drywet", "Dry Wet", 0.f, 1.f, 0.f));                            // 11
    addParameter(mDelayDepthParameter       = new AudioParameterFloat("depth", "Depth", 0.f, 1.f, 0.f));                               // 12
    addParameter(mDelayRateParameter        = new AudioParameterFloat("rate", "Rate", rateMin, rateMax, rateMax));                     // 13
    addParameter(mXTremFeedbackParameter    = new AudioParameterFloat("xTremFeedback", "XTremFeedback", 0.f, xTremFeedbackMax, 0.f));  // 14
    addParameter(mDelayFeedbackParameter    = new AudioParameterFloat("feedback", "Feedback", 0.f, feedbackMax, 0.f));                 // 15
    addParameter(mDelayDryWetSendParameter  = new AudioParameterBool ("delayDryWetSend", "DelayDryWetSend", false));                   // 16
    addParameter(mDelayDepthSendParameter   = new AudioParameterBool ("delayDepthSend", "DelayDepthSend", false));                     // 17
    addParameter(mDelayRateSendParameter    = new AudioParameterBool ("delayRateSend", "DelayRateSend", false));                       // 18
    addParameter(mDelayFeedbackSendParameter= new AudioParameterBool ("delayFeedbackSend", "DelayFeedbackSend", false));               // 19
    //TanenLiveV0AudioProcessor::runTest();
}

TanenLiveV0AudioProcessor::~TanenLiveV0AudioProcessor()
{
    if (mCircularBufferLeft != nullptr) {
           delete [] mCircularBufferLeft;
           mCircularBufferLeft = nullptr;
    }
    if (mCircularBufferLeft == nullptr ) {
       mCircularBufferLeft = new float[mCircularBufferLength];
    }
    if (mCircularBufferRight != nullptr) {
       delete [] mCircularBufferRight;
       mCircularBufferRight = nullptr;
    }
    if (mCircularBufferRight == nullptr ) {
       mCircularBufferRight = new float[mCircularBufferLength];
    }
}

//==============================================================================
const String TanenLiveV0AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TanenLiveV0AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TanenLiveV0AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TanenLiveV0AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TanenLiveV0AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TanenLiveV0AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TanenLiveV0AudioProcessor::getCurrentProgram()
{
    return 0;
}

void TanenLiveV0AudioProcessor::setCurrentProgram (int index)
{
}

const String TanenLiveV0AudioProcessor::getProgramName (int index)
{
    return {};
}

void TanenLiveV0AudioProcessor::changeProgramName (int index, const String& newName)
{
}



//==============================================================================
void TanenLiveV0AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // GENERAL
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    // FILTER
    iIRFilter.prepare(spec);
    iIRFilter.reset();
    // REVERB
    fxReverbChain.prepare(spec);
    // DELAY
    mLFOPhase = 0;
    mDelayTimeSmoothed = 1;
    mCircularBufferLength = sampleRate * maxDelayTime;
    if (mCircularBufferLeft != nullptr ) {
       delete [] mCircularBufferLeft;
       mCircularBufferLeft = nullptr;
    }
    if (mCircularBufferLeft == nullptr) {
        mCircularBufferLeft = new float[mCircularBufferLength];
    }
    zeromem(mCircularBufferLeft, mCircularBufferLength * sizeof(float));
    if (mCircularBufferRight != nullptr ) {
       delete [] mCircularBufferRight;
       mCircularBufferRight = nullptr;
    }
    if (mCircularBufferRight == nullptr) {
        mCircularBufferRight = new float[mCircularBufferLength];
    }
    zeromem(mCircularBufferRight, mCircularBufferLength * sizeof(float));
    mCircularBufferWriteHead = 0;
        
}

void TanenLiveV0AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TanenLiveV0AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainInputChannelSet() == AudioChannelSet::stereo() &&
        layouts.getMainOutputChannelSet() == AudioChannelSet::stereo()) {
        return true;
    } else {
        return false;
    }
  #endif
}
#endif

/*void TanenLiveV0AudioProcessor::buttonClicked(Button* button) {
    
}*/

void TanenLiveV0AudioProcessor::updateFilter() {
    float freq = *mFilterCutoffParameter;
    float res = *mFilterResParameter;
    /** LOWPASS */
    if (*mFilterTypeParameter == 0) {
        *iIRFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate, freq, res);
    /** HIPASS */
    } else {
        *iIRFilter.state = *dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate, freq, res);
    }
}

void TanenLiveV0AudioProcessor::updateReverb() {
    const juce::Reverb::Parameters& reverbParameters = fxReverbChain.getProcessor().getParameters();
    juce::Reverb::Parameters reverbParametersVar;
    reverbParametersVar = reverbParameters;
    reverbParametersVar.dryLevel = *mReverbDryParameter;
    reverbParametersVar.wetLevel = *mReverbWetParameter;
    reverbParametersVar.roomSize = *mReverbSizeParameter;
    // Make it a large stereo reverb
    reverbParametersVar.width = 1.0f;
    fxReverbChain.getProcessor().setParameters(reverbParametersVar);
    // DEBUG
    std::cout << "\n roomSize : ";
    std::cout << reverbParameters.roomSize;
    std::cout << "\n dryLevel : ";
    std::cout << reverbParameters.dryLevel;
    //std::cout << *mReverbDryParameter;
    std::cout << "\n wetLevel : ";
    std::cout << reverbParameters.wetLevel;
    std::cout << "\n \n";
}

float TanenLiveV0AudioProcessor::lin_interp(float sample_x, float sample_x1, float inPhase)
{
    float interp = (1-inPhase) * sample_x + inPhase * sample_x1;
    return interp;
}

void TanenLiveV0AudioProcessor::testSendFx() {
    // tester cette valeur du booléen
    // DEBUG
    std::cout << "\n cutoffSend : ";
    std::cout << *mCutoffSendParameter;
    std::cout << "\n resSend : ";
    std::cout << *mResSendParameter;
    std::cout << "\n reverbWetSend : ";
    std::cout << *mReverbWetSendParameter;
    std::cout << "\n reverbSizeSend : ";
    std::cout << *mReverbSizeSendParameter;
    std::cout << "\n delayDryWetSend : ";
    std::cout << *mDelayDryWetSendParameter;
    std::cout << "\n delayDepthSend : ";
    std::cout << *mDelayDepthSendParameter;
    std::cout << "\n delayRateSend : ";
    std::cout << *mDelayRateSendParameter;
    std::cout << "\n delayFeedbackSend : ";
    std::cout << *mDelayFeedbackSendParameter;
}

void TanenLiveV0AudioProcessor::linkPerformance() {
    std::cout << "\n Performance : ";
    std::cout << *mPerfParameter;
    if (*mCutoffSendParameter) {
        // Use logaritmic range to adapt the values in a reasonable and playful way
        NormalisableRange<float> range = NormalisableRange<float> (0.0f, 1.0f, 1.0f, 1.0f, false);
        range.setSkewForCentre(0.86f);
        float perfSkew = range.convertTo0to1(*mPerfParameter);
        *mFilterCutoffParameter = perfSkew * freqMax;
    }
    if (*mResSendParameter) {
        *mFilterResParameter = *mPerfParameter * resMax;
    }
    if (*mReverbWetSendParameter) {
        *mReverbWetParameter = (float) *mPerfParameter;
    }
    if (*mReverbSizeSendParameter) {
        *mReverbSizeParameter = (float) *mPerfParameter;
    }
    if (*mDelayDryWetSendParameter) {
        *mDelayDryWetParameter = (float) *mPerfParameter;
    }
    if (*mDelayDepthSendParameter) {
        *mDelayDepthParameter = (float) *mPerfParameter;
    }
    if (*mDelayRateSendParameter) {
        *mDelayRateParameter = (float) (1 - *mPerfParameter) * rateMax;
    }
    if (*mDelayFeedbackSendParameter) {
        *mDelayFeedbackParameter = (float) *mPerfParameter * feedbackMax;
    }
    std::cout << "\n CutoffParameter : ";
    std::cout << *mFilterCutoffParameter;
    std::cout << "\n ResParameter : ";
    std::cout << *mFilterResParameter;
}

void TanenLiveV0AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // FILTER UPDATE
    dsp::AudioBlock<float> block (buffer); // [4]
    lastSampleRate = getSampleRate();
    updateFilter();
    iIRFilter.process(dsp::ProcessContextReplacing<float> (block));

    // REVERB UPDATE
    auto blockToUse = block.getSubBlock ((size_t) buffer.getSample(0, 0), (size_t) buffer.getNumSamples());
    auto contextToUse = juce::dsp::ProcessContextReplacing<float> (blockToUse);
    fxReverbChain.process(contextToUse);
    updateReverb();

    // DELAY UPDATE
    DBG("DRY WET: " << *mDelayDryWetParameter);
    DBG("DEPTH: " << *mDelayDepthParameter);
    DBG("RATE: " << *mDelayRateParameter);
    DBG("XTREM FEEDBACK: " << *mXTremFeedbackParameter);
    DBG("FEEDBACK: " << *mDelayFeedbackParameter);
    
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        float lfoOut = (2*M_PI * mLFOPhase);
        mLFOPhase += *mDelayRateParameter / getSampleRate();
        if (mLFOPhase > 1) {
            mLFOPhase -= 1;
        }
        lfoOut *= *mDelayDepthParameter;
        
        float lfoOutMapped = jmap(lfoOut, -1.f, 1.f, 0.005f, 0.03f);
        
        mDelayTimeSmoothed = mDelayTimeSmoothed - 0.001 * (mDelayTimeSmoothed - lfoOutMapped);
        mDelayTimeInSamples = getSampleRate() * mDelayTimeSmoothed;
        
        mCircularBufferLeft[mCircularBufferWriteHead] = leftChannel[i] + mFeedbackLeft;
        mCircularBufferRight[mCircularBufferWriteHead] = rightChannel[i] + mFeedbackRight;
        
        mDelayReadHead = mCircularBufferWriteHead - mDelayTimeInSamples;
        
        if (mDelayReadHead < 0) {
            mDelayReadHead += mCircularBufferLength;
        }
        
        int readHead_x = (int)mDelayReadHead;
        int readHead_x1 = readHead_x + 1;
        float readHeadFloat = mDelayReadHead - readHead_x;
        
        if (readHead_x1 >= mCircularBufferLength) {
            readHead_x1 -= mCircularBufferLength;
        }
        
        // LIN INTERP
        float delay_sample_left = lin_interp((float) mCircularBufferLeft[readHead_x], (float) mCircularBufferLeft[readHead_x1], readHeadFloat);
        float delay_sample_right = lin_interp((float) mCircularBufferRight[readHead_x], (float) mCircularBufferRight[readHead_x1], readHeadFloat);
        
        mFeedbackLeft = delay_sample_left* (*mDelayFeedbackParameter + *mXTremFeedbackParameter);
        mFeedbackRight = delay_sample_right* (*mDelayFeedbackParameter + *mXTremFeedbackParameter);
        
        mCircularBufferWriteHead++;

        // DRYWET
        buffer.setSample(0, i, (buffer.getSample(0, i) * (1-*mDelayDryWetParameter))+(delay_sample_left*(*mDelayDryWetParameter)));
        buffer.setSample(1, i, (buffer.getSample(1, i) * (1-*mDelayDryWetParameter))+(delay_sample_right*(*mDelayDryWetParameter)));
        
        if (mCircularBufferWriteHead >= mCircularBufferLength) {
            mCircularBufferWriteHead = 0;
        }
    }
    
    // PERFORMANCE
    testSendFx();
    linkPerformance();
}

//==============================================================================
bool TanenLiveV0AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TanenLiveV0AudioProcessor::createEditor()
{
    return new TanenLiveV0AudioProcessorEditor (*this);
}

//==============================================================================
void TanenLiveV0AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    std::unique_ptr<XmlElement> xml(new XmlElement("TanenLiveV0SavedParameters"));
    xml->setAttribute("FilterType", *mFilterTypeParameter);
    xml->setAttribute("Cutoff", *mFilterCutoffParameter);
    xml->setAttribute("Resonance", *mFilterResParameter);
    xml->setAttribute("DryReverb", *mReverbDryParameter);
    xml->setAttribute("WetReverb", *mReverbWetParameter);
    xml->setAttribute("RoomSizeReverb", *mReverbSizeParameter);
    xml->setAttribute("CutoffSend", *mCutoffSendParameter);
    xml->setAttribute("ResSend", *mResSendParameter);
    xml->setAttribute("ReverbWetSend", *mReverbWetSendParameter);
    xml->setAttribute("ReverbSizeSend", *mReverbSizeSendParameter);
    xml->setAttribute("Performance", *mPerfParameter);
    xml->setAttribute("DelayDryWet", *mDelayDryWetParameter);
    xml->setAttribute("DelayDepth", *mDelayDepthParameter);
    xml->setAttribute("DelayRate", *mDelayRateParameter);
    xml->setAttribute("XTremFeedback", *mXTremFeedbackParameter);
    xml->setAttribute("DelayFeedback", *mDelayFeedbackParameter);
    xml->setAttribute("DelayDryWetSend", *mDelayDryWetSendParameter);
    xml->setAttribute("DelayDepthSend", *mDelayDepthSendParameter);
    xml->setAttribute("DelayRateSend", *mDelayRateSendParameter);
    xml->setAttribute("DelayFeedbackSend", *mDelayFeedbackSendParameter);

    
    copyXmlToBinary(*xml, destData);
}

void TanenLiveV0AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr && xml->hasTagName("TanenLiveV0SavedParameters")) {
        *mFilterTypeParameter           = xml->getDoubleAttribute("FilterType");
        *mFilterCutoffParameter         = xml->getDoubleAttribute("Cutoff");
        *mFilterResParameter            = xml->getDoubleAttribute("Resonance");
        *mReverbDryParameter            = xml->getDoubleAttribute("DryReverb");
        *mReverbWetParameter            = xml->getDoubleAttribute("WetReverb");
        *mReverbSizeParameter           = xml->getDoubleAttribute("RoomSizeReverb");
        *mCutoffSendParameter           = xml->getDoubleAttribute("CutoffSend");
        *mResSendParameter              = xml->getDoubleAttribute("ResSend");
        *mReverbWetSendParameter        = xml->getDoubleAttribute("ReverbWetSend");
        *mReverbSizeSendParameter       = xml->getDoubleAttribute("ReverbSizeSend");
        *mPerfParameter                 = xml->getDoubleAttribute("Performance");
        *mDelayDryWetParameter          = xml->getDoubleAttribute("DelayDryWet");
        *mDelayDepthParameter           = xml->getDoubleAttribute("DelayDepth");
        *mDelayRateParameter            = xml->getDoubleAttribute("DelayRate");
        *mXTremFeedbackParameter        = xml->getDoubleAttribute("XTremFeedback");
        *mDelayFeedbackParameter        = xml->getDoubleAttribute("DelayFeedback");
        *mDelayDryWetSendParameter      = xml->getDoubleAttribute("DelayDryWetSend");
        *mDelayDepthSendParameter       = xml->getDoubleAttribute("DelayDepthSend");
        *mDelayRateSendParameter        = xml->getDoubleAttribute("DelayRateSend");
        *mDelayFeedbackSendParameter    = xml->getDoubleAttribute("DelayFeedbackSend");
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TanenLiveV0AudioProcessor();
}

#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#define BEGIN_NAMESPACE(n) namespace n {
#define END_NAMESPACE }

BEGIN_NAMESPACE(UnitTestValidator)

struct PlayedFret
{
    int string = -1;
    int fret = -1;
    bool operator == (const PlayedFret& other) const;
};

bool PlayedFret::operator==(const PlayedFret &other) const
{
    std::cout << "this: {" << string << ", " << fret << "} ";
    std::cout << "other: {" << other.string << ", " << other.fret << "} ";
    std::cout << std::endl;
    return string == other.string && fret == other.fret;
}

struct Fretboard
{
    using Solution = std::vector< PlayedFret >;
    using SolutionSet = std::vector< Solution >;
    
    static SolutionSet Make(std::vector<int> tuning,
                             std::vector<int> input);
};

Fretboard::SolutionSet Fretboard::Make(std::vector<int> tuning,
                                       std::vector<int> input)
{
    return
    {
        std::vector< PlayedFret >
        {
            PlayedFret{0, 0},
            PlayedFret{1, 2},
            PlayedFret{2, 2},
            PlayedFret{3, 1},
            PlayedFret{4, 0},
            PlayedFret{5, 0},
        }
    };
}

struct FretboardValidator
{
    FretboardValidator(std::vector<int> t,
                             std::vector<int> i) :
    tuning(t), inputToCheck(i)
    {
        solutions = Fretboard::Make(tuning, inputToCheck);
    }
    FretboardValidator& with(const PlayedFret& pr)
    {
        if ( isValid /* && some check */)
            return *this;
        std::cout << "not found in solution " << std::endl;
        jassertfalse;
        isValid = false;
        return *this;
    }
    operator bool() const { return isValid; }
private:
    bool isValid = true;
    std::vector<int> tuning;
    std::vector<int> inputToCheck;
    Fretboard::SolutionSet solutions;
    bool verify(const PlayedFret& pf);
};

bool FretboardValidator::verify(const PlayedFret &pf)
{
    for (const auto& fretboard : solutions)
    {
        for(const auto& playedFret : fretboard)
        {
            if(pf == playedFret)
                return  true;
        }
    }
    return false;
}

bool expect(bool expression)
{
    if (expression)
    {
        std::cout << "good to go!" << std::endl;
        return true;
    }
    std::cout << "failed test!!" << std::endl;
    return false;
}

END_NAMESPACE

void TanenLiveV0AudioProcessor::runTest()
{
    UnitTestValidator::FretboardValidator candidate(
    {40, 45, 50, 55, 59, 64},
    {50, 55});
    
    UnitTestValidator::expect(candidate
                              .with({3, 1})
                              .with({2, 2}));
    
    //jassertfalse;
    
}
