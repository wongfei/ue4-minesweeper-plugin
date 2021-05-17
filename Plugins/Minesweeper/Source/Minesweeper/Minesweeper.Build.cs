using UnrealBuildTool;
using System.IO;

public class Minesweeper : ModuleRules
{
    public Minesweeper(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        //bEnableUndefinedIdentifierWarnings = false;

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "Slate",
                "SlateCore",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Projects",
                "EditorStyle",
                "LevelEditor",
            }
        );
    }
}
