// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DiplomskiProject : ModuleRules
{
	public DiplomskiProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "AIModule", "GameplayTasks", "NavigationSystem" });
	}
}
