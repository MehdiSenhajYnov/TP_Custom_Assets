#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "MyAssetFactory.generated.h"

class UMyCustomAsset;

UCLASS()
class MYCUSTOMEDITOR_API UMyAssetFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UMyAssetFactory();

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};