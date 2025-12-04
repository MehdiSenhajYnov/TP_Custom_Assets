#include "MyCustomGraphSchema.h"
#include "ToolMenu.h"
#include "Framework/Commands/UIAction.h"
#include "EdGraph/EdGraphNode.h"
#include "MyCustomGraphNode.h"

#define LOCTEXT_NAMESPACE "MyCustomGraphSchema"

UMyCustomGraphSchema::UMyCustomGraphSchema()
{
}

void UMyCustomGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	// Actions disponibles lors du clic droit sur le graphe
	const FText MenuCategory = GetDefaultCategory();
	const FText MenuDescription = LOCTEXT("AddCustomNode", "Add Custom Node");
	const FText Tooltip = LOCTEXT("AddCustomNodeTooltip", "Adds a new custom node to the graph");
	
	// Crée l'action pour ajouter un nouveau nœud personnalisé
	TSharedPtr<FEdGraphSchemaAction_NewNode> NewNodeAction = MakeShared<FEdGraphSchemaAction_NewNode>(
		MenuCategory, MenuDescription, Tooltip, 0);
	
	NewNodeAction->NodeTemplate = NewObject<UMyCustomGraphNode>();
	ContextMenuBuilder.AddAction(NewNodeAction);
}

void UMyCustomGraphSchema::GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	// Ajoute les actions du menu contextuel pour les nœuds
	if (Context && Context->Node)
	{
		FToolMenuSection& Section = Menu->AddSection("MyCustomGraphNode", LOCTEXT("NodeActionsMenuHeader", "Node Actions"));
		
		Section.AddMenuEntry(
			"DeleteNode",
			LOCTEXT("DeleteNode", "Delete Node"),
			LOCTEXT("DeleteNodeTooltip", "Delete this node"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateLambda([Context]()
			{
				if (Context->Node && Context->Graph)
				{
					// Supprime la constness pour l'appel RemoveNode
					UEdGraph* MutableGraph = static_cast<UEdGraph*>(Context->Graph);
					UEdGraphNode* MutableNode = static_cast<UEdGraphNode*>(Context->Node);
					MutableGraph->RemoveNode(MutableNode, true);
				}
			}))
		);
	}
}

const FPinConnectionResponse UMyCustomGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	// Définit les règles de connexion des pins
	if (!A || !B)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("InvalidPins", "Invalid pins"));
	}
	
	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("SameDirection", "Cannot connect pins with same direction"));
	}
	
	if (A->PinType != B->PinType)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("Different type", "Cannot connect pins with different types"));
	}
	
	// Ajouter plus de règles si nécessaire
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, FText::GetEmpty());
}

FLinearColor UMyCustomGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	// Définit les couleurs pour les différents types de pins
	const FName& PinCategory = PinType.PinCategory;
	
	// Utilise des comparaisons de chaînes simples
	if (PinCategory == TEXT("exec"))
	{
		return FLinearColor::White;
	}
	if (PinCategory == TEXT("bool"))
	{
		return FLinearColor::Red;
	}
	if (PinCategory == TEXT("int"))
	{
		return FLinearColor::Green;
	}
	if (PinCategory == TEXT("float"))
	{
		return FLinearColor::Blue;
	}
	
	return FLinearColor::Gray;
}

bool UMyCustomGraphSchema::ShouldHidePinDefaultValue(UEdGraphPin* Pin) const
{
	// Définit quand les valeurs par défaut doivent être masquées
	return Pin && Pin->bDefaultValueIsIgnored;
}

#undef LOCTEXT_NAMESPACE