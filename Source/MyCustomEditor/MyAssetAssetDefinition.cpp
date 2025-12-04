#include "MyAssetAssetDefinition.h"
#include "MyAssetEditor.h"
#include "TP_CustomAssets/MyCustomAsset.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

FText UMyAssetAssetDefinition::GetAssetDisplayName() const
{
	return LOCTEXT("AssetTypeActions_MyAsset", "My Custom Asset");
}

FLinearColor UMyAssetAssetDefinition::GetAssetColor() const
{
	return FLinearColor(FColor(255, 196, 128));
}

TSoftClassPtr<UObject> UMyAssetAssetDefinition::GetAssetClass() const
{
	return UMyCustomAsset::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UMyAssetAssetDefinition::GetAssetCategories() const
{
	static const auto Categories = { FAssetCategoryPath(LOCTEXT("MyCustomAssetsCategory", "My Custom Assets")) };
	return Categories;
}

EAssetCommandResult UMyAssetAssetDefinition::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	for (UMyCustomAsset* Asset : OpenArgs.LoadObjects<UMyCustomAsset>())
	{
		if (Asset)
		{
			TSharedRef<FMyAssetEditor> AssetEditor = MakeShareable(new FMyAssetEditor());
			AssetEditor->InitMyAssetEditor(
				EToolkitMode::Standalone,
				OpenArgs.ToolkitHost,
				Asset
			);
		}
	}
	
	return EAssetCommandResult::Handled;
}

#undef LOCTEXT_NAMESPACE
