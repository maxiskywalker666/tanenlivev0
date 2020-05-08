/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

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
    lastSampleRate = 44100;
    freqMin = 20.0f;
    freqMax = 20000.0f;
    resMin = 1.0f;
    resMax = 5.0f;
    addParameter(mFilterTypeParameter = new AudioParameterInt("filterType",
                                                            "FilterType",
                                                            0,
                                                            1,
                                                            0));
    addParameter(mFilterCutoffParameter = new AudioParameterFloat("cutoff",
                                                            "Cutoff",
                                                            freqMin, // min
                                                            freqMax, // max
                                                            20000.0f)); // default position
    addParameter(mFilterResParameter = new AudioParameterFloat("resonance",
                                                            "Resonance",
                                                            resMin,
                                                            resMax,
                                                            1.0f));
    addParameter(mReverbDryParameter = new AudioParameterFloat("dryReverb",
                                                            "DryReverb",
                                                            0.0f,
                                                            1.0f,
                                                            1.0f));
    addParameter(mReverbWetParameter = new AudioParameterFloat("wetReverb",
                                                            "WetReverb",
                                                            0.0f,
                                                            1.0f,
                                                            0.0f));
    addParameter(mReverbSizeParameter = new AudioParameterFloat("roomSizeReverb",
                                                            "RoomSizeReverb",
                                                            0.0f,
                                                            1.0f,
                                                            0.0f));
    addParameter(mCutoffSendParameter = new AudioParameterBool("cutoffSend",
                                                            "CutoffSend",
                                                            false));
    addParameter(mResSendParameter = new AudioParameterBool("resSend",
                                                            "ResSend",
                                                            false));
    addParameter(mReverbWetSendParameter = new AudioParameterBool("reverbWetSend",
                                                            "ReverbWetSend",
                                                            false));
    addParameter(mReverbSizeSendParameter = new AudioParameterBool("reverbSizeSend",
                                                            "RevebrSizeSend",
                                                            false));
    addParameter(mPerfParameter = new AudioParameterFloat("performance",
                                                            "Performance",
                                                            0.0f,
                                                            1.0f,
                                                            0.0f));

    //TanenLiveV0AudioProcessor::runTest();
}

TanenLiveV0AudioProcessor::~TanenLiveV0AudioProcessor()
{
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
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    iIRFilter.prepare(spec);
    iIRFilter.reset();
    
    fxReverbChain.prepare(spec);
        
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

void TanenLiveV0AudioProcessor::sendFx() {
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
    sendFx();
    linkPerformance();
    
    /*for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        // ..do something to the data...

    }*/
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
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TanenLiveV0AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
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
