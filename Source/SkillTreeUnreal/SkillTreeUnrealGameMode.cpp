// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkillTreeUnrealGameMode.h"
#include "SkillTreeUnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASkillTreeUnrealGameMode::ASkillTreeUnrealGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
