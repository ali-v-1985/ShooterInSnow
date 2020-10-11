// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

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

