// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class pf_pw : ModuleRules
{
	public pf_pw(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AnimGraphRuntime",
            "AIModule",
            "NavigationSystem"
        });

        PublicIncludePaths.Add(ModuleDirectory);

        PrivateDependencyModuleNames.AddRange(new string[] {
        "Slate",
        "SlateCore"
        });

    }
}
