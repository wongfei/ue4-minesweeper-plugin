#include "PluginModule.h"
#include "PluginShared.h"

#include "PluginStyle.h"
#include "PluginCommands.h"
#include "PluginTabManager.h"
#include "PluginToolbar.h"

DEFINE_LOG_CATEGORY(LogMinesweeper);

void FPluginModule::StartupModule()
{
	PLUGIN_TRACE_DEBUG;
	
	InitPluginShared();
	FPluginStyle::Initialize();
	FPluginCommands::Register();

	TabManager = MakeShareable(new FPluginTabManager);
	TabManager->Startup();

	Toolbar = MakeShareable(new FPluginToolbar(TabManager));
	Toolbar->Startup();
}

void FPluginModule::ShutdownModule()
{
	PLUGIN_TRACE_DEBUG;

	Toolbar->Shutdown();
	TabManager->Shutdown();

	FPluginCommands::Unregister();
	FPluginStyle::Shutdown();
}

IMPLEMENT_MODULE(FPluginModule, Minesweeper)
