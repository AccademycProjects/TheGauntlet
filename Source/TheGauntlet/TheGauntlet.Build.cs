// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheGauntlet : ModuleRules
{
	public TheGauntlet(ReadOnlyTargetRules Target) : base(Target)
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
			"TheGauntlet",
			"TheGauntlet/Variant_Platforming",
			"TheGauntlet/Variant_Platforming/Animation",
			"TheGauntlet/Variant_Combat",
			"TheGauntlet/Variant_Combat/AI",
			"TheGauntlet/Variant_Combat/Animation",
			"TheGauntlet/Variant_Combat/Gameplay",
			"TheGauntlet/Variant_Combat/Interfaces",
			"TheGauntlet/Variant_Combat/UI",
			"TheGauntlet/Variant_SideScrolling",
			"TheGauntlet/Variant_SideScrolling/AI",
			"TheGauntlet/Variant_SideScrolling/Gameplay",
			"TheGauntlet/Variant_SideScrolling/Interfaces",
			"TheGauntlet/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
