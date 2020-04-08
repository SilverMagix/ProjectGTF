// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GTFPlayer.h"
#include "PlayerWidget.generated.h"
/**
 *
 */
UCLASS()
class PROJECTGTF_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UPlayerWidget(const FObjectInitializer& ObjectInitializer);

	//Player variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerStats)
		float PlayerHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerRef)
		float ComboNumber;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerRef)
		float Score;

private:
	AGTFPlayer* player;

public:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
