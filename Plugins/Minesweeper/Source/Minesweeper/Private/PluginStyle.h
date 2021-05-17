#pragma once

#include "Styling/SlateStyle.h"

enum class EMinefieldBrushId : int32
{
	Tile0 = 0,
	Tile1,
	Tile2,
	Tile3,
	Tile4,
	Tile5,
	Tile6,
	Tile7,
	Tile8,
	Hidden,
	Unknown,
	Flag,
	Mine,
	MineRip,
	_COUNT // LAST
};

class FPluginStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static const ISlateStyle& Get();
	static const FName& GetStyleSetName();

	static const FSlateBrush* GetMinefieldBrush(EMinefieldBrushId Id);

private:
	static void InitMinefieldBrushes();
	static void InitMinefieldBrush(EMinefieldBrushId Id, const FString& Name, float Size);

private:
	static TSharedRef<FSlateStyleSet> Create();
	static TSharedPtr<FSlateStyleSet> StyleSet;
	static TArray<const FSlateBrush*> MinefieldBrushes;
};
