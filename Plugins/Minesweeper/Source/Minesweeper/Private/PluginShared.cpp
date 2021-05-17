#include "PluginShared.h"

#include "Interfaces/IPluginManager.h"

static FString PluginContentDir;

void InitPluginShared()
{
	PluginContentDir = GetPluginContentDir();
	PLUGIN_LOG_DEBUG(TEXT("PluginContentDir: %s"), *PluginContentDir);
}

FString GetPluginContentDir()
{
	return IPluginManager::Get().FindPlugin(TEXT(PLUGIN_NAME))->GetContentDir();
}

FString GetPluginResourcePath(const FString& RelativePath, const FString& Extension)
{
	auto Path((PluginContentDir / RelativePath) + Extension);
	PLUGIN_LOG_DEBUG(TEXT("GetPluginResourcePath: %s"), *Path);
	return Path;
}
