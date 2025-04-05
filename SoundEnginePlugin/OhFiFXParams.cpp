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
        RTPC.fBitDepth = OHFIFXPARAM_BITDEPTH_DEF;
        RTPC.fDownsampleFactor = OHFIFXPARAM_DOWNSAMPLEFACTOR_DEF;
        RTPC.fWetDryMix = OHFIFXPARAM_WETDRYMIX_DEF;
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

    RTPC.fBitDepth = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
    RTPC.fDownsampleFactor = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
    RTPC.fWetDryMix = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);

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
    case LONY_OHFIFXPARAM_BITDEPTH_ID:
        RTPC.fBitDepth = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_BITDEPTH_ID);
        break;
    case LONY_OHFIFXPARAM_DOWNSAMPLEFACTOR_ID:
        RTPC.fDownsampleFactor = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_DOWNSAMPLEFACTOR_ID);
        break;
    case LONY_OHFIFXPARAM_WETDRYMIX_ID:
        RTPC.fWetDryMix = *((AkReal32*)in_pValue);
        m_paramChangeHandler.SetParamChange(LONY_OHFIFXPARAM_WETDRYMIX_ID);
        break;
    default:
        eResult = AK_InvalidParameter;
        break;
    }

    return eResult;
}
