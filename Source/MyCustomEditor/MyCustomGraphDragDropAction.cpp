#include "MyCustomGraphDragDropAction.h"
#include "MyCustomGraphNode.h"
#include "MyCustomGraph.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "SGraphNode.h"
#include "SGraphPanel.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SWidget.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "MyCustomGraphDragDropAction"

TSharedRef<FMyCustomGraphDragDropAction> FMyCustomGraphDragDropAction::New(const FText& InNodeTypeDisplayName, const FString& InNodeTypeName)
{
	TSharedRef<FMyCustomGraphDragDropAction> Operation = MakeShareable(new FMyCustomGraphDragDropAction);
	Operation->Initialize(InNodeTypeDisplayName, InNodeTypeName);
	Operation->Construct();
	return Operation;
}

FMyCustomGraphDragDropAction::FMyCustomGraphDragDropAction()
	: NodeTypeName(TEXT(""))
	, NodeTypeDisplayName(FText::GetEmpty())
	, IconBrush(nullptr)
{
}

void FMyCustomGraphDragDropAction::Initialize(const FText& InNodeTypeDisplayName, const FString& InNodeTypeName)
{
	NodeTypeDisplayName = InNodeTypeDisplayName;
	NodeTypeName = InNodeTypeName;
	
	// Définit l'icône appropriée pour le type de nœud
	if (InNodeTypeName == TEXT("CustomNode"))
	{
		IconBrush = FAppStyle::GetBrush("GraphEditor.Default_16x");
	}
	else
	{
		IconBrush = FAppStyle::GetBrush("GraphEditor.EventGraph_16x");
	}
}

void FMyCustomGraphDragDropAction::HoverTargetChanged()
{
	FGraphEditorDragDropAction::HoverTargetChanged();

	FText HoverMessage = FText::GetEmpty();
	
	if (GetHoveredGraph())
	{
		HoverMessage = FText::Format(LOCTEXT("DropNodeOnGraph", "Create {0} node"), NodeTypeDisplayName);
	}
	else if (GetHoveredNode())
	{
		HoverMessage = FText::Format(LOCTEXT("DropNodeOnNode", "Replace {0} with {1}"), 
			GetHoveredNode()->GetNodeTitle(ENodeTitleType::ListView),
			NodeTypeDisplayName);
	}
	else if (GetHoveredPin())
	{
		HoverMessage = FText::Format(LOCTEXT("DropNodeOnPin", "Create {0} node and connect to pin"), NodeTypeDisplayName);
	}

	SetSimpleFeedbackMessage(GetIcon(), FLinearColor::White, HoverMessage);
}

FReply FMyCustomGraphDragDropAction::DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition)
{
	UEdGraphPin* DropPin = GetHoveredPin();
	UEdGraph* Graph = GetHoveredGraph();

	if (DropPin && Graph)
	{
		// Crée le nœud
		UMyCustomGraphNode* NewNode = CreateNode(*Graph, {GraphPosition.X, GraphPosition.Y});
		if (NewNode)
		{
			// Essaie de connecter au pin approprié
			UEdGraphPin* ConnectPin = nullptr;
			
			// Trouve un pin compatible sur le nouveau nœud
			for (UEdGraphPin* Pin : NewNode->Pins)
			{
				if (Pin && Pin->Direction != DropPin->Direction)
				{
					// Logique de connexion simple
					if (Pin->PinType.PinCategory == DropPin->PinType.PinCategory)
					{
						ConnectPin = Pin;
						break;
					}
				}
			}
			
			// Effectue la connexion si un pin compatible est trouvé
			if (ConnectPin && Graph->GetSchema())
			{
				Graph->GetSchema()->TryCreateConnection(DropPin, ConnectPin);
			}
		}
		
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply FMyCustomGraphDragDropAction::DroppedOnNode(const FVector2f& ScreenPosition, const FVector2f& GraphPosition)
{
	UEdGraphNode* DropNode = GetHoveredNode();
	UEdGraph* Graph = GetHoveredGraph();

	if (DropNode && Graph)
	{
		// Crée un nouveau nœud près du nœud de destination
		FVector2D NewNodePosition = FVector2D(
			GraphPosition.X + 200.0f, // Décalage vers la droite
			GraphPosition.Y
		);
		
		CreateNode(*Graph, NewNodePosition);
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply FMyCustomGraphDragDropAction::DroppedOnPanel(const TSharedRef<SWidget>& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph)
{
	// Crée un nouveau nœud à l'emplacement de dépôt
	CreateNode(Graph, {GraphPosition.X, GraphPosition.Y});
	return FReply::Handled();
}

// void FMyCustomGraphDragDropAction::OnDragBegin(const TSharedRef<class SGraphPin>& InPin)
// {
// 	// This is called when starting a drag from a pin
// 	// We don't use this for our node creation drag drop
// }

void FMyCustomGraphDragDropAction::OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent)
{
	FGraphEditorDragDropAction::OnDrop(bDropWasHandled, MouseEvent);
}

UMyCustomGraphNode* FMyCustomGraphDragDropAction::CreateNode(UEdGraph& Graph, FVector2D GraphPosition)
{
	// Crée un nouveau nœud personnalisé
	UMyCustomGraphNode* NewNode = NewObject<UMyCustomGraphNode>(&Graph, UMyCustomGraphNode::StaticClass());
	
	if (NewNode)
	{
		// Définit la position du nœud
		NewNode->NodePosX = GraphPosition.X;
		NewNode->NodePosY = GraphPosition.Y;

		// Ajoute le nœud au graphe
		Graph.AddNode(NewNode, true);

		// Alloue les pins par défaut
		NewNode->AllocateDefaultPins();

		// Marque le graphe comme modifié
		// FEdGraphUtilities::SetNodeMetaData(NewNode, FNodeMetadata::DefaultGraphNode);

		// Sélectionne le nouveau nœud
		if (UMyCustomGraph* CustomGraph = Cast<UMyCustomGraph>(&Graph))
		{
			CustomGraph->RebuildCustomGraph();
		}

		return NewNode;
	}

	return nullptr;
}

const FSlateBrush* FMyCustomGraphDragDropAction::GetIcon() const
{
	return IconBrush ? IconBrush : FAppStyle::GetBrush("GraphEditor.Default_16x");
}

FText FMyCustomGraphDragDropAction::GetHoverText() const
{
	if (GetHoveredGraph())
	{
		return FText::Format(LOCTEXT("CreateNodeInGraph", "Create {0}"), NodeTypeDisplayName);
	}
	
	return FText::Format(LOCTEXT("DragNodeType", "Drag {0}"), NodeTypeDisplayName);
}

#undef LOCTEXT_NAMESPACE