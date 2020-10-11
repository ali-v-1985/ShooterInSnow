// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    ShowHUD();
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    HUD->RemoveFromViewport();
    if (bIsWinner)
    {
        ShowWinScreen();
    }
    else
    {
        ShowLoseScreen();
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::ShowLoseScreen()
{
    UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
    if(LoseScreen != nullptr)
    {
        LoseScreen->AddToViewport();
    }
}

void AShooterPlayerController::ShowWinScreen()
{
    UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
    if(WinScreen != nullptr)
    {
        WinScreen->AddToViewport();
    }
}

void AShooterPlayerController::ShowHUD()
{
    HUD = CreateWidget(this, HUDClass);
    if(HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}

