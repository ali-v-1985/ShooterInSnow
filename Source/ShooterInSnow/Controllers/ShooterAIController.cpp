// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterInSnow/Characters/ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    const auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    SetFocus(PlayerPawn);
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    MoveToActor(PlayerPawn, 200);
}
