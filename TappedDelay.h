#pragma once
#include "Delay.h"
#include "OnePoleLPF.h"

// derived class of CDelay
class TappedDelay : public CDelay
{
public:
	// constructor/destructor
	TappedDelay(void);
	~TappedDelay(void);

private:
	// attenuation
	float f_mAtten;

	COnePoleLPF LPF;

public:
	// overrides
	float processAudio(float* pInput, float* pOutput);
};
