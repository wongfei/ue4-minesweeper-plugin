#include "PluginCommands.h"
#include "PluginShared.h"

#define LOCTEXT_NAMESPACE PLUGIN_NAMESPACE

FPluginCommands::FPluginCommands()
	: TCommands<FPluginCommands>(
		TEXT(PLUGIN_NAME), // ContextName
		PLUGIN_LOCTEXT(PLUGIN_NAME, PLUGIN_NAME), // ContextDesc
		NAME_None, 
		FEditorStyle::GetStyleSetName())
{
}

void FPluginCommands::RegisterCommands()
{
	PLUGIN_TRACE_DEBUG;

	UI_COMMAND(LaunchGameCmd, "Launch " PLUGIN_NAME, "Launch " PLUGIN_NAME, EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
