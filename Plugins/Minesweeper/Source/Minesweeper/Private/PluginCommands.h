#pragma once

#include "Framework/Commands/Commands.h"

class FPluginCommands : public TCommands<FPluginCommands>
{
public:
	FPluginCommands();
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> LaunchGameCmd;
};
