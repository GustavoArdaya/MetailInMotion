// Copyright Epic Games, Inc. All Rights Reserved.

#include "MetalInMotion.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MetalInMotion, "MetalInMotion" );

/**
Demo console variable for extra force controlling player ball bearings.
*********************************************************************************/

static TAutoConsoleVariable<int32> CVarExtraMagnetism(
	TEXT("OurGame.ExtraMagnetism"),
	0,
	TEXT("Defines whether we should cheat in getting our bearings into their goals.\n")
	TEXT("  0: no extra magnetism\n")
	TEXT("  1: extra magnetism\n"),
	ECVF_Scalability | ECVF_RenderThreadSafe);
