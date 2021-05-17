#pragma once

#include "IMinesweeperModule.h"

class FPluginModule : public IMinesweeperModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
private:
	TSharedPtr<class FPluginTabManager> TabManager;
	TSharedPtr<class FPluginToolbar> Toolbar;
};
