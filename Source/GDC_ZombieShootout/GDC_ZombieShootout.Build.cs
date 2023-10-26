// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GDC_ZombieShootout : ModuleRules
{
	public GDC_ZombieShootout(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
