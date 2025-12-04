#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "EdGraph/EdGraph.h"
#include "MyCustomGraph.generated.h"

class UMyCustomGraphSchema;

UCLASS()
class MYCUSTOMEDITOR_API UMyCustomGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UMyCustomGraph();

	const UMyCustomGraphSchema* GetCustomSchema() const;

	// Reconstruit la logique du graphe
	void RebuildCustomGraph();

protected:
	UPROPERTY()
	FString GraphDescription;
};