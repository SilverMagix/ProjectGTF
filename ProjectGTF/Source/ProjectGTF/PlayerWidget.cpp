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
		PlayerHP = player->hp / 100;

		FString scoreText = "Score: ";
		int totalScoreSize = 10;
		FString playerScoreString = FString::FromInt(player->score);
		totalScoreSize -= playerScoreString.Len();
		while (totalScoreSize > 0) {

			scoreText += "0";

			totalScoreSize--;
		}

		Score = scoreText + playerScoreString;


		int previousScore = FCString::Atoi(*ComboNumber.RightChop(7));
		if (previousScore != player->comboNumber && player->comboNumber > 0) {
			ComboNumber = "Combo: " + FString::FromInt(player->comboNumber);
			ComboUIVisibility = 1;
		}
		else {
			if (ComboUIVisibility > 0) {
				if (player->comboDurationTimer > 2) {

					ComboUIVisibility -= (InDeltaTime / 3);
					print("Reducing ComboUI Visibility", -19);

				}
			}
		}
	}

UUserWidget::NativeTick(MyGeometry, InDeltaTime);

}
