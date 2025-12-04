#include "MyCustomGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "Framework/Commands/UIAction.h"
#include "SMyCustomGraphNode.h"

#define LOCTEXT_NAMESPACE "MyCustomGraphNode"

UMyCustomGraphNode::UMyCustomGraphNode()
{
	NodeDescription = TEXT("Custom Node");
	NodeValue = 0;
}

FText UMyCustomGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (TitleType == ENodeTitleType::FullTitle)
	{
		return FText::Format(LOCTEXT("NodeFullTitle", "Custom Node\n{0}"), FText::FromString(NodeDescription));
	}
	return LOCTEXT("NodeTitle", "Custom Node");
}

FLinearColor UMyCustomGraphNode::GetNodeTitleColor() const
{
	return FLinearColor(0.2f, 0.8f, 0.2f);
}

FSlateIcon UMyCustomGraphNode::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = FLinearColor::White;
	return FSlateIcon();
}

void UMyCustomGraphNode::AllocateDefaultPins()
{
	Pins.Empty();
	
	CreateInputPin();
	CreateDataPins();
	CreateOutputPin();
}

FText UMyCustomGraphNode::GetTooltipText() const
{
	return FText::Format(LOCTEXT("NodeTooltip", "Custom Node: {0}\nValue: {1}"), 
		FText::FromString(NodeDescription), 
		FText::AsNumber(NodeValue));
}

void UMyCustomGraphNode::CreateInputPin()
{
	UEdGraphPin* InputPin = CreatePin(
		EGPD_Input,
		TEXT("exec"),
		NAME_None,
		TEXT("Input")
	);
}

void UMyCustomGraphNode::CreateDataPins()
{
	UEdGraphPin* AIntPin = CreatePin(
		EGPD_Input,
		TEXT("int"),
		NAME_None,
		TEXT("A")
	);

	UEdGraphPin* BIntPin = CreatePin(
		EGPD_Input,
		TEXT("int"),
		NAME_None,
		TEXT("B")
	);

}

void UMyCustomGraphNode::CreateOutputPin()
{
	UEdGraphPin* OutputPin = CreatePin(
		EGPD_Output,
		TEXT("exec"),
		NAME_None,
		TEXT("Output")
	);
	
	UEdGraphPin* OutputIntPin = CreatePin(
	EGPD_Output,
	TEXT("int"),
	NAME_None,
	TEXT("Result")
);
}

TSharedPtr<SGraphNode> UMyCustomGraphNode::CreateVisualWidget()
{
	return SNew(SMyCustomGraphNode, this);
}

#undef LOCTEXT_NAMESPACE