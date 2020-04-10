// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Engine.h"


#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)


UPlayerWidget::UPlayerWidget(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{

}

void UPlayerWidget::NativeConstruct()
{


	if (!Player) {
		AActor* playerActor = Cast<AGTFPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AGTFPlayer::StaticClass()));
		Player = Cast<AGTFPlayer>(playerActor);

	}
	UUserWidget::NativeConstruct();

}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

	if (Player) {
		PlayerHP = Player->Hp / 100;

		FString scoreText = "Score: ";
		int totalScoreSize = 10;
		FString playerScoreString = FString::FromInt(Player->Score);
		totalScoreSize -= playerScoreString.Len();
		while (totalScoreSize > 0) {

			scoreText += "0";

			totalScoreSize--;
		}

		Score = scoreText + playerScoreString;


		int previousScore = FCString::Atoi(*ComboNumber.RightChop(7));
		if (previousScore != Player->ComboNumber && Player->ComboNumber > 0) {
			ComboNumber = "Combo: " + FString::FromInt(Player->ComboNumber);
			ComboUIVisibility = 1;
		}
		else {
			if (ComboUIVisibility > 0) {
				if (Player->ComboDurationTimer > 2) {

					ComboUIVisibility -= (InDeltaTime / 3);
					print("Reducing ComboUI Visibility", -19);

				}
			}
		}
	}

UUserWidget::NativeTick(MyGeometry, InDeltaTime);

}
