// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyCustomAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TP_CUSTOMASSETS_API UMyCustomAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Asset")
	FString AssetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Asset")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Asset")
	float Value;
};