#include "MinefieldWidget.h"
#include "MinefieldState.h"
#include "PluginShared.h"

void SMinefieldWidget::Construct(const FArguments& InArgs)
{
	PLUGIN_TRACE_DEBUG;

	GameState = MakeShared<MinefieldState>();

	SetWidthOverride(1.0f);
	SetHeightOverride(1.0f);
}

void SMinefieldWidget::ResizeMinefield(int NumX, int NumY, int NumMines)
{
	PLUGIN_TRACE_DEBUG;

	const bool Valid = (NumX > 1 && NumY > 1); check(Valid);
	if (!Valid)
		return;

	GridX = NumX;
	GridY = NumY;
	GameState->Resize(NumX, NumY, NumMines);

	const auto* Brush = FPluginStyle::GetMinefieldBrush(EMinefieldBrushId::Hidden);
	TileSize = (Brush ? Brush->GetImageSize().X : 1);

	SetWidthOverride((float)(GridX * TileSize));
	SetHeightOverride((float)(GridY * TileSize));

	WidgetEnabled = true;
}

EMinefieldBrushId SMinefieldWidget::GetBrushId(const struct MinefieldCell& Cell) const
{
	if (Cell.IsVisible)
	{
		if (Cell.IsMine)
			return Cell.IsBlown ? EMinefieldBrushId::MineRip : EMinefieldBrushId::Mine;
		
		// adjacent mine counter
		return (EMinefieldBrushId)((int)EMinefieldBrushId::Tile0 + Cell.NumAdjacentMines);
	}
	else
	{
		if (Cell.Flag == EMinefieldFlag::Unknown)
			return EMinefieldBrushId::Unknown;

		if (Cell.Flag == EMinefieldFlag::PossibleMine)
			return EMinefieldBrushId::Flag;
	}

	return EMinefieldBrushId::Hidden;
}

int32 SMinefieldWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, 
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	for (int y = 0; y < GridY; ++y)
	{
		for (int x = 0; x < GridX; ++x)
		{
			auto BrushId = GetBrushId(GameState->GetCell(x, y));
			const auto* Brush = FPluginStyle::GetMinefieldBrush(BrushId);

			if (Brush)
			{
				FSlateDrawElement::MakeBox(
					OutDrawElements,
					LayerId,
					AllottedGeometry.ToPaintGeometry(FVector2D(x * TileSize, y * TileSize), FVector2D(TileSize, TileSize)),
					Brush,
					ESlateDrawEffect::None,
					FLinearColor(1, 1, 1, 1)
					//InWidgetStyle.GetColorAndOpacityTint()
				);
			}
		}
	}

	return LayerId;
}

FReply SMinefieldWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	HandleMouseClick(MyGeometry, MouseEvent);
	return FReply::Handled();
}

FReply SMinefieldWidget::OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	HandleMouseClick(MyGeometry, MouseEvent);
	return FReply::Handled();
}

void SMinefieldWidget::HandleMouseClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (!WidgetEnabled)
		return;

	const FVector2D LocalPos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
	const int CellX = (int)floorf(LocalPos.X / (float)TileSize);
	const int CellY = (int)floorf(LocalPos.Y / (float)TileSize);

	const bool Valid = (CellX >= 0 && CellX < GridX && CellY >= 0 && CellY < GridY);
	if (Valid)
	{
		if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			PLUGIN_LOG_DEBUG(TEXT("Click: %d %d"), CellX, CellY);
			const auto Res = GameState->Dig(CellX, CellY);

			if (Res == EDigResult::SapperWin || Res == EDigResult::MinesWin)
			{
				WidgetEnabled = false;
				GameState->RevealMinefield();

				const TCHAR* Msg = (Res == EDigResult::SapperWin ? TEXT("YOU WIN") : TEXT("YOU DIED"));
				PLUGIN_LOG_DEBUG(TEXT("%s"), Msg);
			}
		}
		else if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			if (!GameState->IsVisible(CellX, CellY))
			{
				int Flag = (int)GameState->GetFlag(CellX, CellY);
				if (++Flag >= (int)EMinefieldFlag::_COUNT)
					Flag = 0;
				GameState->SetFlag(CellX, CellY, (EMinefieldFlag)Flag);
			}
		}
	}
}
