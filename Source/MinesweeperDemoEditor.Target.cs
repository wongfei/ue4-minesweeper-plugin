using UnrealBuildTool;
using System.Collections.Generic;

public class MinesweeperDemoEditorTarget : TargetRules
{
	public MinesweeperDemoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "MinesweeperDemo" } );
	}
}
