// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDS.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, TDS, "TDS" );

namespace TDSGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_Spawned, "InitState.Spawned", "1: Actor/component has initially spawned and can be extended");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_GameplayReady, "InitState.GameplayReady", "2: The actor/component is fully ready for active gameplay");
};
