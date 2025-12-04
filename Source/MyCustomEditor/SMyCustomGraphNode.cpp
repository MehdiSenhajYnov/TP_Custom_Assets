#include "SMyCustomGraphNode.h"
#include "MyCustomGraphNode.h"
#include "SMyCustomGraphPin.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SToolTip.h"
#include "Widgets/Text/STextBlock.h"
#include "SGraphPin.h"
#include "SNodePanel.h"

void SMyCustomGraphNode::Construct(const FArguments& InArgs, UMyCustomGraphNode* InNode)
{
	MyGraphNode = InNode;
	GraphNode = InNode;

	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}

void SMyCustomGraphNode::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	// Remet à zéro les variables exposées
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	const FSlateBrush* NodeTypeIcon = nullptr;

	FLinearColor TitleShadowColor(0.6f, 0.6f, 0.6f);

	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	IconColor = FLinearColor::White;
	const FSlateIcon Icon = MyGraphNode->GetIconAndTint(IconColor);
	NodeTypeIcon = Icon.GetOptionalIcon();

	TSharedRef<SOverlay> DefaultTitleAreaWidget =
		SNew(SOverlay)
		+SOverlay::Slot()
		[
			SNew(SImage)
			.Image(FAppStyle::GetBrush("Graph.Node.Body"))
			.ColorAndOpacity(this, &SGraphNode::GetNodeBodyColor)
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				// ICÔNE
				SNew(SBorder)
				.BorderImage(FStyleDefaults::GetNoBrush())
				.Visibility(Icon.IsSet() ? EVisibility::Visible : EVisibility::Collapsed)
				.Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
				[
					SNew(SImage)
					.Image(NodeTypeIcon)
					.ColorAndOpacity(this, &SMyCustomGraphNode::GetNodeIconColor)
				]
			]
			+SHorizontalBox::Slot()
			.Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					CreateTitleWidget(NodeTitle)
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					// Description du nœud
					SNew(STextBlock)
					.Text(this, &SMyCustomGraphNode::GetNodeDescription)
					.TextStyle(FAppStyle::Get(), "Graph.Node.NodeTitleExtraLines")
					.ColorAndOpacity(FLinearColor(0.8f, 0.8f, 0.8f))
				]
			]
		];

	SetDefaultTitleAreaWidget(DefaultTitleAreaWidget);

	TSharedRef<SWidget> ContentAreaWidget = CreateContentArea();

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);

	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
			.Padding(0)
			.BorderBackgroundColor(this, &SGraphNode::GetNodeBodyColor)
			[
				SNew(SOverlay)
				+SOverlay::Slot()
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					.Padding(20.0f, 6.0f, 10.0f, 5.0f)
					[
						DefaultTitleAreaWidget
					]
					+SVerticalBox::Slot()
					.AutoHeight()
					.Padding(1.0f)
					[
						ContentAreaWidget
					]
				]
			]
		];

	CreatePinWidgets();
}

void SMyCustomGraphNode::CreatePinWidgets()
{
	UMyCustomGraphNode* CustomNode = CastChecked<UMyCustomGraphNode>(GraphNode);

	for (int32 PinIdx = 0; PinIdx < CustomNode->Pins.Num(); PinIdx++)
	{
		UEdGraphPin* MyPin = CustomNode->Pins[PinIdx];
		if (!MyPin->bHidden)
		{
			TSharedPtr<SGraphPin> NewPin = SNew(SMyCustomGraphPin, MyPin)
				.ToolTipText(this, &SMyCustomGraphNode::GetPinTooltip, MyPin);

			AddPin(NewPin.ToSharedRef());
		}
	}
}

void SMyCustomGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();

	if (PinObj && PinObj->Direction == EGPD_Input)
	{
		LeftNodeBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			.Padding(20.0f, 0.0f)
			[
				PinToAdd
			];
		InputPins.Add(PinToAdd);
	}
	else // Output
	{
		RightNodeBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			.Padding(20.0f, 0.0f)
			[
				PinToAdd
			];
		OutputPins.Add(PinToAdd);
	}
}

bool SMyCustomGraphNode::IsNameReadOnly() const
{
	return true;
}

TSharedRef<SWidget> SMyCustomGraphNode::CreateContentArea()
{
	return SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("NoBorder"))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin(0, 3))
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.FillWidth(1.0f)
			[
				// GAUCHE
				SAssignNew(LeftNodeBox, SVerticalBox)
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			[
				// DROITE
				SAssignNew(RightNodeBox, SVerticalBox)
			]
		];
}

TSharedRef<SWidget> SMyCustomGraphNode::CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle)
{
	return SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.FillWidth(1.f)
		[
			SNew(STextBlock)
			.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
			.TextStyle(FAppStyle::Get(), "Graph.Node.NodeTitle")
			.ColorAndOpacity(FLinearColor::White)
			.Justification(ETextJustify::Center)
		];
}

FText SMyCustomGraphNode::GetNodeDescription() const
{
	if (MyGraphNode)
	{
		return FText::FromString(MyGraphNode->NodeDescription);
	}
	return FText::GetEmpty();
}

FSlateColor SMyCustomGraphNode::GetNodeIconColor() const
{
	return IconColor;
}

FText SMyCustomGraphNode::GetPinTooltip(UEdGraphPin* GraphPinObj) const
{
	if (GraphPinObj)
	{
		return FText::FromName(GraphPinObj->PinName);
	}
	return FText::GetEmpty();
}