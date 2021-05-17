#pragma once

#include "CoreMinimal.h"

#define PLUGIN_NAME "Minesweeper"
#define PLUGIN_NAMESPACE PLUGIN_NAME
#define PLUGIN_LOCTEXT(Key, Text) NSLOCTEXT(PLUGIN_NAMESPACE, Key, Text)

DECLARE_LOG_CATEGORY_EXTERN(LogMinesweeper, Log, All);

#define PLUGIN_LOG(Verbosity, Format, ...) UE_LOG(LogMinesweeper, Verbosity, Format, __VA_ARGS__)

#if !UE_BUILD_SHIPPING
	#define PLUGIN_DEBUG_LEVEL Warning
#else
	#define PLUGIN_DEBUG_LEVEL Verbose
#endif

#define PLUGIN_LOG_DEBUG(Format, ...) UE_LOG(LogMinesweeper, PLUGIN_DEBUG_LEVEL, Format, __VA_ARGS__)
#define PLUGIN_TRACE_DEBUG PLUGIN_LOG_DEBUG(TEXT("%S"), __FUNCTION__)

void InitPluginShared();
FString GetPluginContentDir();
FString GetPluginResourcePath(const FString& RelativePath, const FString& Extension);
