// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class SHOOTERINSNOW_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;


protected:
	virtual void BeginPlay() override;
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5;

	FTimerHandle RestartTimer;

	UUserWidget* HUD;

	void ShowLoseScreen();
	void ShowWinScreen();
	void ShowHUD();
};
