//
//  Synth.hpp
//  AudioKit Core
//
//  Created by Shane Dunne, revision history on Github.
//  Copyright © 2018 AudioKit. All rights reserved.
//

#include "SynthVoice.hpp"
#include "WaveStack.hpp"
#include "SustainPedalLogic.hpp"

#include <list>

#define MAX_POLYPHONY 32        // number of voices
#define MIDI_NOTENUMBERS 128    // MIDI offers 128 distinct note numbers
#define CHUNKSIZE 16            // process samples in "chunks" this size

namespace AudioKitCore
{
    
    class Synth
    {
    public:
        Synth();
        ~Synth();
        
        int init(double sampleRate);    // returns system error code, nonzero only if a problem occurs
        void deinit();                  // call this to un-load all samples and clear the keymap
        
        void playNote(unsigned noteNumber, unsigned velocity, float noteHz);
        void stopNote(unsigned noteNumber, bool immediate);
        void sustainPedal(bool down);
        
        void Render(unsigned channelCount, unsigned sampleCount, float *outBuffers[]);
        
    protected:
        // array of voice resources
        SynthVoice voice[MAX_POLYPHONY];

        // "event" counter for voice-stealing (reallocation)
        unsigned eventCounter;

        WaveStack waveForm1, waveForm2, waveForm3;      // WaveStacks are shared by all voice oscillators
        FunctionTableOscillator vibratoLFO;             // one vibrato LFO shared by all voices
        SustainPedalLogic pedalLogic;
        
        // simple parameters
        SynthVoiceParameters voiceParameters;
        ADSREnvelopeParameters ampEGParameters;
        ADSREnvelopeParameters filterEGParameters;

        EnvelopeSegmentParameters segParameters[8];
        EnvelopeParameters envParameters;
        
        // performance parameters
        float masterVolume, pitchOffset, vibratoDepth;

        // filter parameters
        float cutoffMultiple;   // multiple of note frequency - 1.0 means cutoff at fundamental
        float cutoffEgStrength; // how much filter EG adds on top of cutoffMultiple
        float resLinear;        // resonance [-20 dB, +20 dB] becomes linear [10.0, 0.1]
        
        void play(unsigned noteNumber, unsigned velocity, float noteHz);
        void stop(unsigned noteNumber, bool immediate);

        SynthVoice* voicePlayingNote(unsigned noteNumber);
    };
}
