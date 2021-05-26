// Copyright (c) 2014-2021 Sombusta, All Rights Reserved.
// SomWorks :D // MIT LICENSE // Epic VR Template Convert C++ Open Source Project.

using UnrealBuildTool;
using System.Collections.Generic;

public class PrayVREditorTarget : TargetRules
{
	public PrayVREditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "PrayVR" } );
	}
}
