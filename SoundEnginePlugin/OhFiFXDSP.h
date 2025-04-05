// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#ifndef _OHFIFXDSP_H_
#define _OHFIFXDSP_H_

#include <AK/SoundEngine/Common/AkTypes.h>
#include <AK/SoundEngine/Common/IAkPluginMemAlloc.h>
#include <AK/SoundEngine/Common/AkCommonDefs.h>
#include "OhFiFXParams.h"

/// @brief OhFi DSP Processing class
class COhFiFXDSP
{
public:
	/// @brief Default constructor.
	COhFiFXDSP() = delete;

	/// @brief Process the received buffer.
	/// @param io_pBuffer The buffer to process.
	/// @param pCurrentParams Parameters to take into account.
	static void Process(AkAudioBuffer* io_pBuffer, OhFiFXParams* pCurrentParams);
};

#endif  // _OHFIFXDSP_H_
