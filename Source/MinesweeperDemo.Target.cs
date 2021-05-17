using UnrealBuildTool;
using System.Collections.Generic;

public class MinesweeperDemoTarget : TargetRules
{
	public MinesweeperDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "MinesweeperDemo" } );
	}
}
