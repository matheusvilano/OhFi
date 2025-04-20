// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#include "OhFiFXDSP.h"
#include <algorithm>
#include <cmath>

void COhFiFXDSP::Process(AkReal32 &out_fSample, const AkUInt16 &in_uCount, OhFiNonRTPCParams &in_rFxParams, const OhFiRTPCParams &in_rGameParams)
{
    if (in_rGameParams.fWetDryMix <= 0)
    {
        return; // Optimization (early-out).
    }

    const AkReal32 fWetMix = in_rGameParams.fWetDryMix / 100;
    const AkReal32 fDryMix = 1 - fWetMix;

    const AkReal32 fOriginalSample = out_fSample;

    if (in_rGameParams.fDownsampleFactor > MIN_DOWNSAMPLE_FACTOR)
    {
        Downsample(out_fSample, in_uCount, in_rFxParams, in_rGameParams);
    }

    if (in_rGameParams.fBitDepth > MIN_BIT_DEPTH)
    {
        Bitcrush(out_fSample, in_rGameParams);
    }

    out_fSample = (out_fSample * fWetMix) + (fOriginalSample * fDryMix);
}

void COhFiFXDSP::Downsample(AkReal32 &out_fSample, const AkUInt16 &in_uCount, OhFiNonRTPCParams &in_rFxParams, const OhFiRTPCParams &in_rGameParams)
{
    const AkReal32 fRate = std::clamp(in_rGameParams.fDownsampleFactor, MIN_DOWNSAMPLE_FACTOR, MAX_DOWNSAMPLE_FACTOR);

    if (++in_rFxParams.fSampleCounter >= fRate)
    {
        in_rFxParams.fHeldSample = out_fSample;
        in_rFxParams.fSampleCounter -= fRate; // Carry remainder
    }

    out_fSample = in_rFxParams.fHeldSample;
}

void COhFiFXDSP::Bitcrush(AkReal32 &out_fSample, const OhFiRTPCParams &in_rGameParams)
{
    const AkReal32 fBitDepth = std::clamp(in_rGameParams.fBitDepth, MIN_BIT_DEPTH, MAX_BIT_DEPTH);
    const AkReal32 fLevel = std::pow(2.0f, fBitDepth);

    if (fLevel <= 0)
    {
        return; // To prevent crashes with edge cases where the number is somehow invalid.
    }

    const AkReal32 fStepSize = 2.0f / fLevel;

    out_fSample = std::round(out_fSample / fStepSize) * fStepSize;
}
