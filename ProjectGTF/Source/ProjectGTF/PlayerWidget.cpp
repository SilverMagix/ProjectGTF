// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Engine.h"


#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)


UPlayerWidget::UPlayerWidget(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer) 
{

}

void UPlayerWidget::NativeConstruct()
{


	if (!player) {
		AActor* playerActor = Cast<AGTFPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AGTFPlayer::StaticClass()));
		player = Cast<AGTFPlayer>(playerActor);
		
	}
	UUserWidget::NativeConstruct();

}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

	if (player) {
		PlayerHP = player->hp/100;
		
		Score = player->score;

		ComboNumber = player->comboNumber;

	
	}
	else {
	
		//print("No Player", 12);

	}
	
	UUserWidget::NativeTick(MyGeometry, InDeltaTime);

}
