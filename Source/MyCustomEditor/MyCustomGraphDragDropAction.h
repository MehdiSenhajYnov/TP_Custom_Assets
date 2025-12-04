#pragma once

#include "CoreMinimal.h"
#include "GraphEditorDragDropAction.h"
#include "Engine/Texture2D.h"

class UMyCustomGraphNode;
class UEdGraph;

class MYCUSTOMEDITOR_API FMyCustomGraphDragDropAction : public FGraphEditorDragDropAction
{
public:
	DRAG_DROP_OPERATOR_TYPE(FMyCustomGraphDragDropAction, FGraphEditorDragDropAction)

	static TSharedRef<FMyCustomGraphDragDropAction> New(const FText& InNodeTypeDisplayName, const FString& InNodeTypeName);

	virtual void HoverTargetChanged() override;
	virtual FReply DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;
	
	virtual FReply DroppedOnNode(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;
	virtual FReply DroppedOnPanel(const TSharedRef<SWidget>& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;

	virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;

protected:
	FMyCustomGraphDragDropAction();

	virtual UMyCustomGraphNode* CreateNode(UEdGraph& Graph, FVector2D GraphPosition);

	virtual const FSlateBrush* GetIcon() const;

	virtual FText GetHoverText() const;

	FString NodeTypeName;

	FText NodeTypeDisplayName;

	const FSlateBrush* IconBrush;

private:
	void Initialize(const FText& InNodeTypeDisplayName, const FString& InNodeTypeName);
};