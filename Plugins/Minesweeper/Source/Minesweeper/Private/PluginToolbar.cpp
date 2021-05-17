#include "PluginToolbar.h"
#include "PluginShared.h"

#include "PluginStyle.h"
#include "PluginCommands.h"
#include "PluginTabManager.h"

#include "LevelEditor.h"

FPluginToolbar::FPluginToolbar(TSharedPtr<class FPluginTabManager>& InTabManager)
{
	TabManager = InTabManager;
}

void FPluginToolbar::Startup()
{
	PLUGIN_TRACE_DEBUG;

	TSharedPtr<FUICommandInfo> Command = FPluginCommands::Get().LaunchGameCmd;

	Commands = MakeShareable(new FUICommandList);
	Commands->MapAction(Command, FExecuteAction::CreateRaw(this, &FPluginToolbar::OnOpenTabCmd));

	TSharedPtr<FExtender> NewToolbarExtender = MakeShareable(new FExtender);

	NewToolbarExtender->AddToolBarExtension("Content", EExtensionHook::Before, Commands, 
		FToolBarExtensionDelegate::CreateLambda([this, Command](FToolBarBuilder& Builder)
		{
			FText ButtonText(PLUGIN_LOCTEXT(PLUGIN_NAME, PLUGIN_NAME));

			Builder.AddToolBarButton(Command, NAME_None, ButtonText, Command->GetDescription(), 
				FSlateIcon(FPluginStyle::GetStyleSetName(), "ToolbarIcon"), NAME_None);
		})
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(NewToolbarExtender);
}

void FPluginToolbar::Shutdown()
{
	PLUGIN_TRACE_DEBUG;
}

void FPluginToolbar::OnOpenTabCmd()
{
	PLUGIN_TRACE_DEBUG;

	FGlobalTabmanager::Get()->TryInvokeTab(TabManager->GetTabId());
}
