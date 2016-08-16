#pragma once

#include "AdsrParameters.h"

class ADSRCallback
{
public:
		virtual void OnEnvelopeChanged( AdsrParameters parameters ) = 0;
};

