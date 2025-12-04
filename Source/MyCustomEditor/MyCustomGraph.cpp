#include "MyCustomGraph.h"
#include "MyCustomGraphSchema.h"
#include "EdGraph/EdGraphNode.h"

UMyCustomGraph::UMyCustomGraph()
{
    // Définit la classe de schéma pour ce graphe
    Schema = UMyCustomGraphSchema::StaticClass();
    GraphDescription = TEXT("My Custom Graph");
}

void UMyCustomGraph::RebuildCustomGraph()
{
    // Logique personnalisée pour reconstruire le graphe
    for (UEdGraphNode* Node : Nodes)
    {
        if (Node)
        {
            // Logique de traitement des nœuds personnalisée
        }
    }
}

const UMyCustomGraphSchema* UMyCustomGraph::GetCustomSchema() const
{
    const UEdGraphSchema* SchemaInstance = GetSchema();
    return Cast<UMyCustomGraphSchema>(SchemaInstance);
}