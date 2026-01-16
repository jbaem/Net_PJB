// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Net_PJB : ModuleRules
{
	public Net_PJB(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Net_PJB",
			"Net_PJB/Variant_Platforming",
			"Net_PJB/Variant_Platforming/Animation",
			"Net_PJB/Variant_Combat",
			"Net_PJB/Variant_Combat/AI",
			"Net_PJB/Variant_Combat/Animation",
			"Net_PJB/Variant_Combat/Gameplay",
			"Net_PJB/Variant_Combat/Interfaces",
			"Net_PJB/Variant_Combat/UI",
			"Net_PJB/Variant_SideScrolling",
			"Net_PJB/Variant_SideScrolling/AI",
			"Net_PJB/Variant_SideScrolling/Gameplay",
			"Net_PJB/Variant_SideScrolling/Interfaces",
			"Net_PJB/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
