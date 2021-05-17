#pragma once

#include "Widgets/SCompoundWidget.h"

#define GENERATE_GET_SET(Name)\
	decltype(Name) Get##Name() const { return Name; }\
	void Set##Name(decltype(Name) NewValue) { Name = NewValue; }

class SMinesweeperWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMinesweeperWidget) {}
		SLATE_ARGUMENT(TWeakPtr<class FPluginTabManager>, TabManager)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TWeakPtr<class FPluginTabManager> TabManager;
	TSharedPtr<class SMinefieldWidget> MinefieldWidget;

	int32 MinWidth = 3;
	int32 MinHeight = 3;
	int32 MaxWidth = 32;
	int32 MaxHeight = 32;

	int32 FieldWidth = 16;
	int32 FieldHeight = 16;
	float MineDensity = 0.15625f;

	GENERATE_GET_SET(FieldWidth);
	GENERATE_GET_SET(FieldHeight);
	GENERATE_GET_SET(MineDensity);

	FReply OnGenerateClick();
};
