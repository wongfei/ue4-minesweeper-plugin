#include "MinesweeperWidget.h"
#include "MinefieldWidget.h"
#include "PluginShared.h"

#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SSpinBox.h"

void SMinesweeperWidget::Construct(const FArguments& InArgs)
{
	PLUGIN_TRACE_DEBUG;

	TabManager = InArgs._TabManager;

	ChildSlot
	[
		SNew(SScrollBox)
		+SScrollBox::Slot()
		.VAlign(VAlign_Top)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot() // Width
			.Padding(5)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.MaxWidth(100)
				[
					SNew(STextBlock)
					.Text(PLUGIN_LOCTEXT("FieldWidth", "Width:"))
				]
				+SHorizontalBox::Slot()
				.MaxWidth(100)
				[
					SNew(SSpinBox<int32>)
					.MinValue(MinWidth)
					.MaxValue(MaxWidth)
					.Value(this, &SMinesweeperWidget::GetFieldWidth)
					.OnValueChanged(this, &SMinesweeperWidget::SetFieldWidth)
				]
			]
			+SVerticalBox::Slot() // Height
			.Padding(5)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.MaxWidth(100)
				[
					SNew(STextBlock)
					.Text(PLUGIN_LOCTEXT("FieldHeight", "Height:"))
				]
				+SHorizontalBox::Slot()
				.MaxWidth(100)
				[
					SNew(SSpinBox<int32>)
					.MinValue(MinHeight)
					.MaxValue(MaxHeight)
					.Value(this, &SMinesweeperWidget::GetFieldHeight)
					.OnValueChanged(this, &SMinesweeperWidget::SetFieldHeight)
				]
			]
			+SVerticalBox::Slot() // Mine count
			.Padding(5)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.MaxWidth(100)
				[
					SNew(STextBlock)
					.Text(PLUGIN_LOCTEXT("MineDensity", "Density:"))
				]
				+SHorizontalBox::Slot()
				.MaxWidth(100)
				[
					SNew(SSpinBox<float>)
					.MinValue(0.1f)
					.MaxValue(0.4f)
					.Value(this, &SMinesweeperWidget::GetMineDensity)
					.OnValueChanged(this, &SMinesweeperWidget::SetMineDensity)
				]
			]
			+SVerticalBox::Slot() // Generate
			.Padding(5)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.MaxWidth(200)
				[
					SNew(SButton)
					.Text(PLUGIN_LOCTEXT("GenerateText", "Generate"))
					.OnClicked(this, &SMinesweeperWidget::OnGenerateClick)
				]
			]
		]
		+SScrollBox::Slot()
		.Padding(5)
		.VAlign(VAlign_Top)
		[
			SAssignNew(MinefieldWidget, SMinefieldWidget)
		]
	];

	OnGenerateClick();
}

FReply SMinesweeperWidget::OnGenerateClick()
{
	MinefieldWidget->ResizeMinefield(FieldWidth, FieldHeight, (FieldWidth * FieldHeight * MineDensity));
	return FReply::Handled();
}
