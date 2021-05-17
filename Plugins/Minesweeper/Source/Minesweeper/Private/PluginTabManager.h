#pragma once

#include "CoreMinimal.h"

class FPluginTabManager : public TSharedFromThis<FPluginTabManager>
{
public:
	void Startup();
	void Shutdown();
	TSharedRef<class SDockTab> SpawnTab(const class FSpawnTabArgs& TabSpawnArgs);
	const FName& GetTabId() const { return TabId; }

private:
	FName TabId;
};
