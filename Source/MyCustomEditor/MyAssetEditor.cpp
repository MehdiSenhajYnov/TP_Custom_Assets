#include "MyAssetEditor.h"
#include "TP_CustomAssets/MyCustomAsset.h"
#include "MyCustomGraph.h"
#include "MyCustomGraphSchema.h"
// #include "SMyCustomGraphPalette.h"
#include "GraphEditorActions.h"
#include "GraphEditor.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "FMyAssetEditor"

// Identifiants des onglets
const FName FMyAssetEditor::GraphTabId(TEXT("MyAssetEditor_Graph"));
const FName FMyAssetEditor::PropertiesTabId(TEXT("MyAssetEditor_Properties"));

FMyAssetEditor::FMyAssetEditor()
	: EditingAsset(nullptr)
	, Graph(nullptr)
{
}

FMyAssetEditor::~FMyAssetEditor()
{
}

void FMyAssetEditor::InitMyAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UMyCustomAsset* InAsset)
{
	EditingAsset = InAsset;

	// Crée un nouveau graphe si l'asset n'en a pas
	if (!Graph)
	{
		Graph = NewObject<UMyCustomGraph>(EditingAsset, UMyCustomGraph::StaticClass(), NAME_None, RF_Transactional);
		Graph->Schema = UMyCustomGraphSchema::StaticClass();
	}

	CreateDetailsView();
	CreateGraphEditor();

	// Définition du layout pour l'éditeur avec 3 panneaux
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_MyAssetEditor_Layout_v1")->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)->SetSizeCoefficient(0.9f)->Split
				(
					FTabManager::NewStack()->SetSizeCoefficient(0.65f)->AddTab(GraphTabId, ETabState::OpenedTab)
				)->Split(FTabManager::NewStack()->SetSizeCoefficient(0.20f)->AddTab(PropertiesTabId, ETabState::OpenedTab))
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;

	FAssetEditorToolkit::InitAssetEditor(
		Mode,
		InitToolkitHost,
		FName(TEXT("MyAssetEditor")),
		StandaloneDefaultLayout,
		bCreateDefaultStandaloneMenu,
		bCreateDefaultToolbar,
		EditingAsset
	);
}

void FMyAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_MyAssetEditor", "My Asset Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(GraphTabId, FOnSpawnTab::CreateSP(this, &FMyAssetEditor::SpawnTab_GraphEditor))
		.SetDisplayName(LOCTEXT("GraphTab", "Graph"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.EventGraph_16x"));

	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FMyAssetEditor::SpawnTab_Properties))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));

}

void FMyAssetEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(GraphTabId);
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
}

FName FMyAssetEditor::GetToolkitFName() const
{
	return FName("MyAssetEditor");
}

FText FMyAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "My Asset Editor");
}

FString FMyAssetEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "MyAsset ").ToString();
}

FLinearColor FMyAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

void FMyAssetEditor::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged)
{
	if (PropertyThatChanged && EditingAsset)
	{
		EditingAsset->MarkPackageDirty();

		if (GraphEditor.IsValid())
		{
			GraphEditor->NotifyGraphChanged();
		}
	}
}

TSharedRef<SDockTab> FMyAssetEditor::SpawnTab_GraphEditor(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == GraphTabId);

	return SNew(SDockTab)
		.Label(LOCTEXT("GraphEditorTitle", "Graph"))
		[
			GraphEditor.ToSharedRef()
		];
}

TSharedRef<SDockTab> FMyAssetEditor::SpawnTab_Properties(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PropertiesTabId);

	return SNew(SDockTab)
		.Label(LOCTEXT("PropertiesTitle", "Details"))
		[
			DetailsView.ToSharedRef()
		];
}

void FMyAssetEditor::CreateGraphEditor()
{
	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FMyAssetEditor::OnSelectedNodesChanged);

	GraphEditor = SNew(SGraphEditor)
		.AdditionalCommands(TSharedPtr<FUICommandList>())
		.IsEditable(true)
		.GraphToEdit(Graph)
		.GraphEvents(InEvents)
		.ShowGraphStateOverlay(false);
}

void FMyAssetEditor::CreateDetailsView()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.bAllowSearch = true;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bHideSelectionTip = true;
	DetailsViewArgs.NotifyHook = this;

	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(EditingAsset);
}

UMyCustomGraph* FMyAssetEditor::GetCurrentGraph() const
{
	return Graph;
}

void FMyAssetEditor::OnSelectedNodesChanged(const TSet<UObject*>& NewSelection)
{
	TArray<UObject*> SelectedObjects;
	
	if (NewSelection.Num() > 0)
	{
		for (UObject* Object : NewSelection)
		{
			SelectedObjects.Add(Object);
		}
	}
	else
	{
		// Si rien n'est sélectionné, affiche les propriétés de l'asset
		SelectedObjects.Add(EditingAsset);
	}

	if (DetailsView.IsValid())
	{
		DetailsView->SetObjects(SelectedObjects);
	}
}

#undef LOCTEXT_NAMESPACE