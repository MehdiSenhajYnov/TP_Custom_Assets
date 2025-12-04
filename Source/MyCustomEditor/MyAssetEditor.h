#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "IDetailsView.h"
#include "Misc/NotifyHook.h"

class UMyCustomAsset;
class UMyCustomGraph;
class SGraphEditor;
class MYCUSTOMEDITOR_API FMyAssetEditor : public FAssetEditorToolkit, public FNotifyHook
{
public:
	FMyAssetEditor();
	virtual ~FMyAssetEditor() override;

	void InitMyAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UMyCustomAsset* InAsset);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;

private:
	// Identifiants des onglets
	static const FName GraphTabId;
	static const FName PropertiesTabId;
	static const FName PaletteTabId;

	TSharedRef<SDockTab> SpawnTab_GraphEditor(const FSpawnTabArgs& Args);
	
	TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);

	void CreateGraphEditor();
	
	void CreateDetailsView();

	UMyCustomGraph* GetCurrentGraph() const;

	void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);

	TObjectPtr<UMyCustomAsset> EditingAsset;

	TObjectPtr<UMyCustomGraph> Graph;

	TSharedPtr<SGraphEditor> GraphEditor;

	TSharedPtr<IDetailsView> DetailsView;

};