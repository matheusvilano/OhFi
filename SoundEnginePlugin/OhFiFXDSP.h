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

	/// @brief The minimum bit depth. Doesn't necessarily match the Wwise Authoring UI minimum value.
	static constexpr AkReal32 MIN_BIT_DEPTH = 1.f;  // Do not change this to a number lower than 1.

	/// @brief The maximum bit depth. Doesn't necessarily match the Wwise Authoring UI maximum value.
	static constexpr AkReal32 MAX_BIT_DEPTH = 24.f;  // Do not change this to a number greater than 24.

	/// @brief The maximum downsample factor. Doesn't necessarily match the Wwise Authoring UI maximum value.
	static constexpr AkReal32 MIN_DOWNSAMPLE_FACTOR = 1.f;  // Do not change this to a number lower than 1.

	/// @brief The maximum downsample factor. Doesn't necessarily match the Wwise Authoring UI maximum value.
	static constexpr AkReal32 MAX_DOWNSAMPLE_FACTOR = 160.f;  // Recommended to keep this within the [2, 64] range.

	/// @brief Process the received sample.
	/// @param out_fSample The sample (frame) to process.
	/// @param in_pFxParams Non-Game Parameters to take into account.
	/// @param in_pGameParams Game Parameters to take into account.
	static void Process(AkReal32& out_fSample, OhFiNonRTPCParams& in_rFxParams, const OhFiRTPCParams& in_rGameParams);

protected:
	/// @brief Downsample the received sample.
	/// @param out_fSample The sample (frame) to process.
	/// @param in_uCount The contextual index of this frame (e.g. `4` means "the fourth sample in a batch").
	/// @param in_pFxParams Parameters to take into account.
	/// @param in_pGameParams Game Parameters to take into account.
	static void Downsample(AkReal32& out_fSample, OhFiNonRTPCParams& in_rFxParams, const OhFiRTPCParams& in_rGameParams);

	/// @brief Bitcrush the received sample.
	/// @param out_fSample The sample (frame) to process.
	/// @param in_pGameParams Game Parameters to take into account.
	static void Bitcrush(AkReal32& out_fSample, const OhFiRTPCParams& in_rGameParams);
};

#endif
