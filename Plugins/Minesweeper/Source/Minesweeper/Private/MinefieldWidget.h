#pragma once

#include "PluginStyle.h"
#include "Widgets/Layout/SBox.h"

class SMinefieldWidget : public SBox
{
public:
	SLATE_BEGIN_ARGS(SMinefieldWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void ResizeMinefield(int NumX, int NumY, int NumMines);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, 
		FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

private:
	EMinefieldBrushId GetBrushId(const struct MinefieldCell& Cell) const;
	void HandleMouseClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

private:
	TSharedPtr<class MinefieldState> GameState;
	int GridX = 0;
	int GridY = 0;
	int TileSize = 0;
	bool WidgetEnabled = false;
};
