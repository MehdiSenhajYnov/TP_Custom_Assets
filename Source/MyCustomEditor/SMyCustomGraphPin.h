#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class MYCUSTOMEDITOR_API SMyCustomGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SMyCustomGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);

protected:
	virtual const FSlateBrush* GetPinIcon() const override;
	virtual FSlateColor GetPinColor() const override;
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;

	const FSlateBrush* GetPinBrush(bool bIsConnected) const;
	FVector2D GetPinIconSize() const;
	
};