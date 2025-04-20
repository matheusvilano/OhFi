// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#include "OhFiFX.h"
#include "../OhFiConfig.h"
#include "OhFiFXDSP.h"
#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin* CreateOhFiFX(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, OhFiFX());
}

AK::IAkPluginParam* CreateOhFiFXParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, OhFiFXParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(OhFiFX, AkPluginTypeEffect, OhFiConfig::CompanyID, OhFiConfig::PluginID)

AKRESULT OhFiFX::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkEffectPluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (OhFiFXParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    return AK_Success;
}

AKRESULT OhFiFX::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT OhFiFX::Reset()
{
    return AK_Success;
}

AKRESULT OhFiFX::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeEffect;
    out_rPluginInfo.bIsInPlace = true;
	out_rPluginInfo.bCanProcessObjects = false;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void OhFiFX::Execute(AkAudioBuffer* io_pBuffer)
{
    const AkUInt32 uNumChannels = io_pBuffer->NumChannels();

    AkUInt16 uFramesProcessed;
    for (AkUInt32 i = 0; i < uNumChannels; ++i)
    {
        AkReal32* AK_RESTRICT pBuf = (AkReal32* AK_RESTRICT)io_pBuffer->GetChannel(i);

        uFramesProcessed = 0;
        while (uFramesProcessed < io_pBuffer->uValidFrames)
        {
            COhFiFXDSP::Process(pBuf[uFramesProcessed], uFramesProcessed, m_pParams->NonRTPC, m_pParams->RTPC);
            ++uFramesProcessed;
        }
    }
}

AKRESULT OhFiFX::TimeSkip(AkUInt32 in_uFrames)
{
    return AK_DataReady;
}
