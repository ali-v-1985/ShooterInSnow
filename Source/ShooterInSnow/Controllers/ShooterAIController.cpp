// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (LineOfSightTo(PlayerPawn))
    {
        MoveToActor(PlayerPawn, AcceptanceRadius);
        SetFocus(PlayerPawn);
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
        
    }

    
}
