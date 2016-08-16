#pragma once

#include "LfoParameters.h"

class LFOCallback
{
public:
		virtual void OnLfoChanged( LFOParameters parameters ) = 0;
};
