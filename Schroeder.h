/*
	RackAFX(TM)
	Applications Programming Interface
	Derived Class Object Definition
	Copyright(c) Tritone Systems Inc. 2006-2012

	Your plug-in must implement the constructor,
	destructor and virtual Plug-In API Functions below.
*/

#pragma once

// base class
#include "plugin.h"
#include "CombFilter.h"
#include "Delay.h"
#include "DelayAPF.h"
#include "LPFCombFilter.h"
#include "OnePoleLPF.h"
#include "TappedDelay.h"


// un-comment for advanced GUI API: see www.willpirkle.com for details and sample code
/*
#include "GUIViewAttributes.h"
#include "../vstgui4/vstgui/vstgui.h"
*/

// un-comment for pure custom VSTGUI: see www.willpirkle.com for details and sample code
//#include "VSTGUIController.h"

class CSchroeder : public CPlugIn
{
public:
	// RackAFX Plug-In API Member Methods:
	// The followung 5 methods must be impelemented for a meaningful Plug-In
	//
	// 1. One Time Initialization
	CSchroeder();

	// 2. One Time Destruction
	virtual ~CSchroeder(void);

	// 3. The Prepare For Play Function is called just before audio streams
	virtual bool __stdcall prepareForPlay();

	// 4. processAudioFrame() processes an audio input to create an audio output
	virtual bool __stdcall processAudioFrame(float* pInputBuffer, float* pOutputBuffer, UINT uNumInputChannels, UINT uNumOutputChannels);

	// 5. userInterfaceChange() occurs when the user moves a control.
	virtual bool __stdcall userInterfaceChange(int nControlIndex);


	// OPTIONAL ADVANCED METHODS ------------------------------------------------------------------------------------------------
	// These are more advanced; see the website for more details
	//
	// 6. initialize() is called once just after creation; if you need to use Plug-In -> Host methods
	//				   such as sendUpdateGUI(), you must do them here and NOT in the constructor
	virtual bool __stdcall initialize();

	// 7. joystickControlChange() occurs when the user moves a control.
	virtual bool __stdcall joystickControlChange(float fControlA, float fControlB, float fControlC, float fControlD, float fACMix, float fBDMix);

	// 8. process buffers instead of Frames:
	// NOTE: set m_bWantBuffers = true to use this function
	virtual bool __stdcall processRackAFXAudioBuffer(float* pInputBuffer, float* pOutputBuffer, UINT uNumInputChannels, UINT uNumOutputChannels, UINT uBufferSize);

	// 9. rocess buffers instead of Frames:
	// NOTE: set m_bWantVSTBuffers = true to use this function
	virtual bool __stdcall processVSTAudioBuffer(float** inBuffer, float** outBuffer, UINT uNumChannels, int inFramesToProcess);

	// 10. MIDI Note On Event
	virtual bool __stdcall midiNoteOn(UINT uChannel, UINT uMIDINote, UINT uVelocity);

	// 11. MIDI Note Off Event
	virtual bool __stdcall midiNoteOff(UINT uChannel, UINT uMIDINote, UINT uVelocity, bool bAllNotesOff);


	// 12. MIDI Modulation Wheel uModValue = 0 -> 127
	virtual bool __stdcall midiModWheel(UINT uChannel, UINT uModValue);

	// 13. MIDI Pitch Bend
	//					nActualPitchBendValue = -8192 -> 8191, 0 is center, corresponding to the 14-bit MIDI value
	//					fNormalizedPitchBendValue = -1.0 -> +1.0, 0 is at center by using only -8191 -> +8191
	virtual bool __stdcall midiPitchBend(UINT uChannel, int nActualPitchBendValue, float fNormalizedPitchBendValue);

	// 14. MIDI Timing Clock (Sunk to BPM) function called once per clock
	virtual bool __stdcall midiClock();


	// 15. all MIDI messages -
	// NOTE: set m_bWantAllMIDIMessages true to get everything else (other than note on/off)
	virtual bool __stdcall midiMessage(unsigned char cChannel, unsigned char cStatus, unsigned char cData1, unsigned char cData2);

	// 16. initUI() is called only once from the constructor; you do not need to write or call it. Do NOT modify this function
	virtual bool __stdcall initUI();

	// Custom GUI
	virtual void* __stdcall showGUI(void* pInfo);

	// --- process aux inputs (for sidechain capability; optional, not used in FX book projects)
	virtual bool __stdcall processAuxInputBus(audioProcessData* pAudioProcessData);

	// Add your code here: ----------------------------------------------------------- //
	COnePoleLPF LPF_in;
	CDelayAPF in_APF1;
	CDelayAPF in_APF2;
	CDelayAPF in_APF3;
	TappedDelay TD;
	CDelayAPF APF1;
	CDelayAPF APF2;
	CCombFilter CF1;
	CCombFilter CF2;
	CCombFilter CF3;
	CCombFilter CF4;

	COnePoleLPF LPF_out;

	void cookVariables();

	// END OF USER CODE -------------------------------------------------------------- //


	// ADDED BY RACKAFX -- DO NOT EDIT THIS CODE!!! ----------------------------------- //
	//  **--0x07FD--**

	float m_fWet_pct;
	float m_fRT60_mS;
	float m_fPredelay_mS;
	float m_fLPF_in_g;
	float m_fLPF_out_g;

	// **--0x1A7F--**
	// ------------------------------------------------------------------------------- //

};
