#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "Engine/Blueprint.h"
#include "MyCustomGraphSchema.generated.h"

UCLASS()
class MYCUSTOMEDITOR_API UMyCustomGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	UMyCustomGraphSchema();

	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;
	virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;

	// Catégorie par défaut pour les nouveaux nœuds
	static FText GetDefaultCategory() { return NSLOCTEXT("MyCustomGraphSchema", "DefaultCategory", "Custom Nodes"); }
};