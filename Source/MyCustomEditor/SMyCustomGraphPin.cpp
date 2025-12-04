#include "SMyCustomGraphPin.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphSchema.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"

void SMyCustomGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InPin);
}

const FSlateBrush* SMyCustomGraphPin::GetPinIcon() const
{
	return GetPinBrush(GraphPinObj->LinkedTo.Num() > 0);
}

FSlateColor SMyCustomGraphPin::GetPinColor() const
{
	if (GraphPinObj && GraphPinObj->GetSchema())
	{
		// Applique des modifications selon la catégorie de pin
		const FName& PinCategory = GraphPinObj->PinType.PinCategory;
		
		if (PinCategory == TEXT("exec"))
		{
			return FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (PinCategory == TEXT("bool"))
		{
			return FLinearColor(1.0f, 0.2f, 0.2f, 1.0f);
		}
		if (PinCategory == TEXT("int"))
		{
			return FLinearColor(0.2f, 1.0f, 0.2f, 1.0f);
		}
		if (PinCategory == TEXT("float"))
		{
			return FLinearColor(0.2f, 0.5f, 1.0f, 1.0f);
		}
		
		FLinearColor SchemaColor = GraphPinObj->GetSchema()->GetPinTypeColor(GraphPinObj->PinType);
		SchemaColor.R = FMath::Min(SchemaColor.R * 1.2f, 1.0f);
		SchemaColor.G = FMath::Min(SchemaColor.G * 1.2f, 1.0f);
		SchemaColor.B = FMath::Min(SchemaColor.B * 1.2f, 1.0f);
		
		return SchemaColor;
	}
	
	return FLinearColor::Gray;
}

TSharedRef<SWidget> SMyCustomGraphPin::GetDefaultValueWidget()
{
	if (GraphPinObj && GraphPinObj->PinType.PinCategory == TEXT("exec"))
	{
		return SNullWidget::NullWidget;
	}

	return SGraphPin::GetDefaultValueWidget();
}

const FSlateBrush* SMyCustomGraphPin::GetPinBrush(bool bIsConnected) const
{
	if (GraphPinObj)
	{
		const FName& PinCategory = GraphPinObj->PinType.PinCategory;
		
		if (PinCategory == TEXT("exec"))
		{
			if (GraphPinObj->Direction == EGPD_Input)
			{
				return bIsConnected ? 
					FAppStyle::GetBrush(TEXT("Graph.ExecPin.Connected")) : 
					FAppStyle::GetBrush(TEXT("Graph.ExecPin.Disconnected"));
			}
			return bIsConnected ? 
				FAppStyle::GetBrush(TEXT("Graph.ExecPin.Connected")) : 
				FAppStyle::GetBrush(TEXT("Graph.ExecPin.Disconnected"));
		}
		return bIsConnected ? 
			FAppStyle::GetBrush(TEXT("Graph.Pin.Connected")) : 
			FAppStyle::GetBrush(TEXT("Graph.Pin.Disconnected"));
	}
	
	return FAppStyle::GetBrush(TEXT("Graph.Pin.Disconnected"));
}

FVector2D SMyCustomGraphPin::GetPinIconSize() const
{
	if (GraphPinObj && GraphPinObj->PinType.PinCategory == TEXT("exec"))
	{
		return FVector2D(16.0f, 16.0f);
	}
	
	return FVector2D(12.0f, 12.0f);
}

