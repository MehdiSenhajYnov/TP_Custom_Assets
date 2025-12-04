#include "MyAssetFactory.h"

#include "TP_CustomAssets/MyCustomAsset.h"

UMyAssetFactory::UMyAssetFactory()
{
	SupportedClass = UMyCustomAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UMyAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UMyCustomAsset>(InParent, InClass, InName, Flags);
}