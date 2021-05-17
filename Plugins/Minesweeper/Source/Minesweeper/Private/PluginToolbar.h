#pragma once

#include "CoreMinimal.h"

class FPluginToolbar
{
public:
	FPluginToolbar(TSharedPtr<class FPluginTabManager>& InTabManager);
	void Startup();
	void Shutdown();
	void OnOpenTabCmd();

private:
	TSharedPtr<class FPluginTabManager> TabManager;
	TSharedPtr<class FUICommandList> Commands;
};
