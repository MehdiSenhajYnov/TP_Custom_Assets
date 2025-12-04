#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "MyCustomGraphNode.generated.h"

UCLASS()
class MYCUSTOMEDITOR_API UMyCustomGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UMyCustomGraphNode();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual void AllocateDefaultPins() override;
	virtual FText GetTooltipText() const override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Node")
	FString NodeDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Node")
	int32 NodeValue;

protected:
	void CreateInputPin();
	
	void CreateDataPins();
	
	void CreateOutputPin();
};