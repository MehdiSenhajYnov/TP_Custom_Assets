#pragma once

#include "CoreMinimal.h"
#include "AssetDefinition.h"
#include "MyAssetAssetDefinition.generated.h"

class UMyCustomAsset;

UCLASS()
class MYCUSTOMEDITOR_API UMyAssetAssetDefinition : public UAssetDefinition
{
	GENERATED_BODY()
	
public:
	virtual FText GetAssetDisplayName() const override;
	virtual FLinearColor GetAssetColor() const override;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
	virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
};