// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "../OhFiPlugin.h"

/// @brief Graphical User Interface for the Authoring plugin.
class OhFiPluginGUI final
	: public AK::Wwise::Plugin::PluginMFCWindows<>
	, public AK::Wwise::Plugin::GUIWindows
{
public:
	/// @brief Default constructor.
	OhFiPluginGUI() = default;
};
