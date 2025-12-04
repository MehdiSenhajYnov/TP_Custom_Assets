#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class UMyCustomGraphNode;

class MYCUSTOMEDITOR_API SMyCustomGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SMyCustomGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UMyCustomGraphNode* InNode);

	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	virtual bool IsNameReadOnly() const override;

protected:
	virtual TSharedRef<SWidget> CreateContentArea();
	virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle) override;

	FText GetNodeDescription() const;
	FSlateColor GetNodeIconColor() const;
	FText GetPinTooltip(UEdGraphPin* GraphPinObj) const;

	UMyCustomGraphNode* MyGraphNode = nullptr;
	FLinearColor IconColor = {};
};