#include "TappedDelay.h"
#include <math.h>

TappedDelay::TappedDelay(void) :CDelay()
{
	f_mAtten = 0.27;
	LPF.init();
}

TappedDelay::~TappedDelay(void)
{
}

float TappedDelay::processAudio(float* pInput, float* pOutput)
{
	// Read the Input
	float xn = *pInput;
	float yn = 0.0;

	// read delayed output
	if (m_fDelayInSamples == 0) {
		yn = xn;
		// write to the delay line
		writeDelayAndInc(xn);

		// output attenuation
		*pOutput = m_fOutputAttenuation*yn;

		return xn;
	}
	else {
		yn = f_mAtten * readDelay();

		float f_tap_samples = 0.0;
		float f_tap_mS = 0.0;
		float f_tap_val = 0.0;
		
		float f_decayAtten = f_mAtten;

		// generate 12 multitaps at small intervals greater than the original pre-delay to simulate early reflections
		for (int i = 0; i < 12; i++) {

			float f_inc = ((float)i * 0.0907) + 1;
			f_tap_samples = m_fDelayInSamples * f_inc;
			f_tap_mS = (f_tap_samples * 1000.0)/m_nSampleRate;
			f_tap_val = readDelayAt(f_tap_mS);
			f_decayAtten = f_mAtten * exp(-1.0 * ((float)i / 4));
			yn += (f_decayAtten * f_tap_val);
		}

		// put the pointer in but return one of these for feeding into another
		// filter chain

		float f_tapOne_samples = m_fDelayInSamples;
		float f_tapTwo_samples = f_tapOne_samples * 1.11;
		float f_tapThree_samples = f_tapOne_samples * 1.17;
		float f_tapFour_samples = f_tapOne_samples * 1.31;
		float f_tapFive_samples = f_tapOne_samples * 1.43;

		float f_tapOne_mS = (f_tapOne_samples * 1000.0) / m_nSampleRate;
		float f_tapTwo_mS = (f_tapTwo_samples * 1000.0) / m_nSampleRate;
		float f_tapThree_mS = (f_tapThree_samples * 1000.0) / m_nSampleRate;
		float f_tapFour_mS = (f_tapFour_samples * 1000.0) / m_nSampleRate;
		float f_tapFive_mS = (f_tapFive_samples * 1000.0) / m_nSampleRate;

		float f_tapOne_val = readDelayAt(f_tapOne_mS);
		float f_tapTwo_val = readDelayAt(f_tapTwo_mS);
		float f_tapThree_val = readDelayAt(f_tapThree_mS);
		float f_tapFour_val = readDelayAt(f_tapFour_mS);
		float f_tapFive_val = readDelayAt(f_tapFive_mS);

		yn = (f_mAtten * f_tapOne_val) + ((f_mAtten - .04) * f_tapTwo_val) + ((f_mAtten - .07) * f_tapThree_val) + 
			((f_mAtten - .09) * f_tapFour_val) + ((f_mAtten - .13)* f_tapFive_val);
		
		// write to the delay line
		writeDelayAndInc(xn);

		// output attenuation
		*pOutput = m_fOutputAttenuation*yn;

		return f_tapThree_val;
	}
}
