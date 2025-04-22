// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#include "OhFiFXParams.h"

#include <AK/Tools/Common/AkBankReadHelpers.h>

OhFiFXParams::OhFiFXParams(const OhFiFXParams& in_rParams)
{
    RTPC = in_rParams.RTPC;
    NonRTPC = in_rParams.NonRTPC;
    m_paramChangeHandler.SetAllParamChanges();
}

AK::IAkPluginParam* OhFiFXParams::Clone(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, OhFiFXParams(*this));
}

AKRESULT OhFiFXParams::Init(AK::IAkPluginMemAlloc* in_pAllocator, const void* in_pParamsBlock, AkUInt32 in_ulBlockSize)
{
    if (in_ulBlockSize == 0)
    {
        RTPC.sInput.bProcessLfe = OHFIFXPARAM_INPUT_PROCESSLFE_DEF;
        RTPC.sInput.eSignalFlow = OHFIFXPARAM_INPUT_SIGNALFLOW_DEF;

        RTPC.sBitcrusher.fBitDepth = OHFIFXPARAM_BITCRUSHER_BITDEPTH_DEF;
        RTPC.sBitcrusher.bApplyDither = OHFIFXPARAM_BITCRUSHER_APPLYDITHER_DEF;
        RTPC.sBitcrusher.fWetDryMix = OHFIFXPARAM_BITCRUSHER_WETDRYMIX_DEF;

        RTPC.sDownsampler.fFactor = OHFIFXPARAM_DOWNSAMPLER_FACTOR_DEF;
        RTPC.sDownsampler.bInterpolation = OHFIFXPARAM_DOWNSAMPLER_INTERPOLATION_DEF;
        RTPC.sDownsampler.fWetDryMix = OHFIFXPARAM_DOWNSAMPLER_WETDRYMIX_DEF;

        RTPC.sOutput.fGainReduction = OHFIFXPARAM_OUTPUT_GAINREDUCTION_DEF;
        RTPC.sOutput.fWetDryMix = OHFIFXPARAM_OUTPUT_WETDRYMIX_DEF;

        m_paramChangeHandler.SetAllParamChanges();

        return AK_Success;
    }

    return SetParamsBlock(in_pParamsBlock, in_ulBlockSize);
}

AKRESULT OhFiFXParams::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT OhFiFXParams::SetParamsBlock(const void* in_pParamsBlock, AkUInt32 in_ulBlockSize)
{
    AKRESULT eResult = AK_Success;
    AkUInt8* pParamsBlock = (AkUInt8*)in_pParamsBlock;

    RTPC.sInput.bProcessLfe = READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
    RTPC.sInput.eSignalFlow = (ESignalFlow) READBANKDATA(AkInt32, pParamsBlock, in_ulBlockSize);
    
    RTPC.sBitcrusher.fBitDepth = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
    RTPC.sBitcrusher.bApplyDither = READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
    RTPC.sBitcrusher.fWetDryMix = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
    
    RTPC.sDownsampler.fFactor = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
    RTPC.sDownsampler.bInterpolation = READBANKDATA(bool, pParamsBlock, in_ulBlockSize);
    RTPC.sDownsampler.fWetDryMix = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
    
    RTPC.sOutput.fGainReduction = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
    RTPC.sOutput.fWetDryMix = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);

    CHECKBANKDATASIZE(in_ulBlockSize, eResult);
    m_paramChangeHandler.SetAllParamChanges();

    return eResult;
}

AKRESULT OhFiFXParams::SetParam(AkPluginParamID in_paramID, const void* in_pValue, AkUInt32 in_ulParamSize)
{
    AKRESULT eResult = AK_Success;

    // Handle parameter change here
    switch (in_paramID)
    {
    case LONY_OHFIFXPARAM_INPUT_PROCESSLFE_ID:
        RTPC.sInput.bProcessLfe = *((bool*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_INPUT_PROCESSLFE_ID);
        break;
    case LONY_OHFIFXPARAM_INPUT_SIGNALFLOW_ID:
        RTPC.sInput.eSignalFlow = (ESignalFlow) *((AkInt32*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_INPUT_SIGNALFLOW_ID);
        break;
    case LONY_OHFIFXPARAM_BITCRUSHER_BITDEPTH_ID:
        RTPC.sBitcrusher.fBitDepth = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_BITCRUSHER_BITDEPTH_ID);
        break;
    case LONY_OHFIFXPARAM_BITCRUSHER_APPLYDITHER:
        RTPC.sBitcrusher.bApplyDither = *((bool*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_BITCRUSHER_APPLYDITHER);
        break;
    case LONY_OHFIFXPARAM_BITCRUSHER_WETDRYMIX:
        RTPC.sBitcrusher.fWetDryMix = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_BITCRUSHER_WETDRYMIX);
        break;
    case LONY_OHFIFXPARAM_DOWNSAMPLER_FACTOR_ID:
        RTPC.sDownsampler.fFactor = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_DOWNSAMPLER_FACTOR_ID);
        break;
    case LONY_OHFIFXPARAM_DOWNSAMPLER_INTERPOLATION_ID:
        RTPC.sDownsampler.bInterpolation = *((bool*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_DOWNSAMPLER_INTERPOLATION_ID);
        break;
    case LONY_OHFIFXPARAM_DOWNSAMPLER_WETDRYMIX_ID:
        RTPC.sDownsampler.fWetDryMix = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_DOWNSAMPLER_WETDRYMIX_ID);
        break;
    case LONY_OHFIFXPARAM_OUTPUT_GAINREDUCTION_ID:
        RTPC.sOutput.fGainReduction = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_OUTPUT_GAINREDUCTION_ID);
        break;
    case LONY_OHFIFXPARAM_OUTPUT_WETDRYMIX_ID:
        RTPC.sOutput.fWetDryMix = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_OUTPUT_WETDRYMIX_ID);
        break;
    default:
        eResult = AK_InvalidParameter;
        break;
    }

    return eResult;
}
