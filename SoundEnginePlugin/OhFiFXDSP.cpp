// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#include "OhFiFXDSP.h"
#include <algorithm>
#include <cmath>

void COhFiFXDSP::Process(AkReal32& out_fSample, OhFiNonRTPCParams& in_rFxParams, const OhFiRTPCParams& in_rGameParams)
{
    if (in_rGameParams.sOutput.fWetDryMix <= 0)
    {
        return; // Optimization (early-out).
    }

    const AkReal32 fOriginalSample = out_fSample;

    switch (in_rGameParams.sInput.eSignalFlow)
    {
        default:
        case ESignalFlow::SIGNALFLOW_SERIES_BIDO:
        Bitcrush(out_fSample, in_rGameParams.sBitcrusher);
        Downsample(out_fSample, in_rFxParams.sDownsampler, in_rGameParams.sDownsampler);
        break;
        
        case ESignalFlow::SIGNALFLOW_SERIES_DOBI:
        Downsample(out_fSample, in_rFxParams.sDownsampler, in_rGameParams.sDownsampler);
        Bitcrush(out_fSample, in_rGameParams.sBitcrusher);
        break;

        case ESignalFlow::SIGNALFLOW_PARALLEL:
            AkReal32 fSample = out_fSample;  // Duplicate.
            Bitcrush(fSample, in_rGameParams.sBitcrusher);  // Using duplicate.
            Downsample(out_fSample, in_rFxParams.sDownsampler, in_rGameParams.sDownsampler);
            out_fSample = (out_fSample * 0.5f) + (fSample * 0.5f);  // Sum signals at a 1:1 ratio.
            break;
    }

    const AkReal32 fWetMix = in_rGameParams.sOutput.fWetDryMix / 100;
    const AkReal32 fDryMix = 1 - fWetMix;

    out_fSample = (out_fSample * fWetMix * AK_DBTOLIN(in_rGameParams.sOutput.fGainReduction)) + (fOriginalSample * fDryMix);
}

void COhFiFXDSP::Downsample(AkReal32& out_fSample, OhFiNonRTPCParams::Downsampler& in_rFxParams, const OhFiRTPCParams::Downsampler& in_rGameParams, const bool& in_bForce)
{
    if (in_rGameParams.fFactor <= MIN_DOWNSAMPLE_FACTOR || in_rGameParams.fWetDryMix <= 0)
    {
        return;
    }

    const AkReal32 fRate = std::clamp(in_rGameParams.fFactor, MIN_DOWNSAMPLE_FACTOR, MAX_DOWNSAMPLE_FACTOR);
    const AkReal32 fAlpha = in_rFxParams.fSampleCounter / fRate;

    if (++in_rFxParams.fSampleCounter >= fRate || in_bForce)
    {
        in_rFxParams.fHeldSample = out_fSample;
        in_rFxParams.fSampleCounter -= fRate; // Carry remainder

        if (in_rFxParams.fSampleCounter < 0)
        {
            in_rFxParams.fSampleCounter = 0.f;
        }
    }

    const AkReal32 fWetMix = in_rGameParams.fWetDryMix / 100;
    const AkReal32 fDryMix = 1 - fWetMix;

    if (in_rGameParams.bInterpolation)
    {
        out_fSample = ((out_fSample + (fAlpha * (in_rFxParams.fHeldSample - out_fSample)) * fWetMix)) + (out_fSample * fDryMix);
    }
    else
    {
        out_fSample = (in_rFxParams.fHeldSample * fWetMix) + (out_fSample * fDryMix);
    }
}

void COhFiFXDSP::Bitcrush(AkReal32& out_fSample, const OhFiRTPCParams::Bitcrusher& in_rGameParams)
{
    if (in_rGameParams.fBitDepth <= MIN_BIT_DEPTH || in_rGameParams.fWetDryMix < 0)
    {
        return;
    }

    const AkReal32 fBitDepth = std::clamp(in_rGameParams.fBitDepth, MIN_BIT_DEPTH, MAX_BIT_DEPTH);
    const AkReal32 fLevel = std::pow(2.0f, fBitDepth);
    const AkReal32 fStepSize = 2.0f / fLevel;

    const AkReal32 Dither = in_rGameParams.bApplyDither ? ((rand() / (AkReal32)RAND_MAX) - 0.5f) * fStepSize : 0.f;

    const AkReal32 fWetMix = in_rGameParams.fWetDryMix / 100;
    const AkReal32 fDryMix = 1 - fWetMix;

    out_fSample = (((std::round(out_fSample / fStepSize) * fStepSize) + Dither) * fWetMix) + (out_fSample * fDryMix);
}
