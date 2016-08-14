##Infinite Machine: Algorithmic Drum Sequencer with Dynamic Controls
Ableton Live 9 compatible Sequencer built by openFrameworks (0.9.2)
Supports sync mode with Ableton Live through Max 4 Live device with OSC

##Features
Standalone mode : lets control the external Instruments that supports MIDI 

Compound Euclidean / Poly-rhythm generator : Creates sequences by using Bjorklund Algorithm and its application (clough-douthett algorithm, Complimentary Euclidean (or maximally-even) set)

Hybrid Sequencing Model : mutate sequences on-the-go with Deterministic/stochastic methods (Weighted-probability model, Clarence Barlow's metric indispensability formula)

MIDI-compatible software : allows to connect external instrument such as Elektron Machinedrum (natively supported in current build*)

##Dependencies
Ableton Live 9 with Max 4 Live (for Slave mode)
Requiring openFrameworks addons to build : ofxMaxim, ofxDatGui, ofxOSC, ofxMidi...
**TESTED on OSX El Capitan, Xcode 7.3.1
