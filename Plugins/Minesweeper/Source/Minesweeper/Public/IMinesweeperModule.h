#pragma once

#include "Modules/ModuleManager.h"

class IMinesweeperModule : public IModuleInterface
{
public:

	static inline IMinesweeperModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IMinesweeperModule>("Minesweeper");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Minesweeper");
	}
};
