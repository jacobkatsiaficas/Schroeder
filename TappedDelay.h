#pragma once
#include "Delay.h"

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

public:
	// overrides
	float processAudio(float* pInput, float* pOutput);
};
