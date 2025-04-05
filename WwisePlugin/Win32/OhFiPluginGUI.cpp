// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#include "OhFiPluginGUI.h"

ADD_AUDIOPLUGIN_CLASS_TO_CONTAINER(
    OhFi,            // Name of the plug-in container for this shared library
    OhFiPluginGUI,   // Authoring plug-in class to add to the plug-in container
    OhFiFX           // Corresponding Sound Engine plug-in class
);
