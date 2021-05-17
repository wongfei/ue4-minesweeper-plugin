#include "PluginStyle.h"
#include "PluginShared.h"

#include "Styling/SlateStyleRegistry.h"
#include "Brushes/SlateImageBrush.h"

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(GetPluginResourcePath(RelativePath, ".png"), __VA_ARGS__)

TSharedPtr<FSlateStyleSet> FPluginStyle::StyleSet = NULL;
TArray<const FSlateBrush*> FPluginStyle::MinefieldBrushes;

void FPluginStyle::Initialize()
{
	if (StyleSet.IsValid())
		return;

	PLUGIN_TRACE_DEBUG;

	StyleSet = Create();

	StyleSet->Set("ToolbarIcon", new IMAGE_BRUSH("Icons/icon_toolbar_40x", FVector2D(40, 40)));
	StyleSet->Set("TabIcon", new IMAGE_BRUSH("Icons/icon_tab_16x", FVector2D(16, 16)));

	InitMinefieldBrushes();

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FPluginStyle::Shutdown()
{
	if (!StyleSet.IsValid())
		return;

	PLUGIN_TRACE_DEBUG;

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	StyleSet.Reset();
}

TSharedRef<FSlateStyleSet> FPluginStyle::Create()
{
	PLUGIN_TRACE_DEBUG;

	return MakeShareable(new FSlateStyleSet(PLUGIN_NAME "Style"));
}

const ISlateStyle& FPluginStyle::Get()
{
	return *StyleSet;
}

const FName& FPluginStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT(PLUGIN_NAME "Style"));
	return StyleSetName;
}

void FPluginStyle::InitMinefieldBrushes()
{
	PLUGIN_TRACE_DEBUG;

	const float TileSize = 16;
	MinefieldBrushes.SetNum((int)EMinefieldBrushId::_COUNT);

	const int Tile0 = (int)EMinefieldBrushId::Tile0;
	for (int i = 0; i <= 8; ++i)
	{
		auto Name = FString::Printf(TEXT("tile_%d"), i);
		InitMinefieldBrush((EMinefieldBrushId)(Tile0 + i), Name, TileSize);
	}

	InitMinefieldBrush(EMinefieldBrushId::Hidden, "tile_hidden", TileSize);
	InitMinefieldBrush(EMinefieldBrushId::Unknown, "tile_unknown", TileSize);
	InitMinefieldBrush(EMinefieldBrushId::Flag, "tile_flag", TileSize);
	InitMinefieldBrush(EMinefieldBrushId::Mine, "tile_mine", TileSize);
	InitMinefieldBrush(EMinefieldBrushId::MineRip, "tile_mine_rip", TileSize);
}

void FPluginStyle::InitMinefieldBrush(EMinefieldBrushId Id, const FString& Name, float Size)
{
	FString RelativePath("Sprites/");
	RelativePath.Append(Name);

	FSlateImageBrush* Brush = new IMAGE_BRUSH(RelativePath, FVector2D(Size, Size));
	StyleSet->Set(*Name, Brush);
	MinefieldBrushes[(int)Id] = Brush;
}

const FSlateBrush* FPluginStyle::GetMinefieldBrush(EMinefieldBrushId Id)
{
	return MinefieldBrushes[(int)Id];
}
