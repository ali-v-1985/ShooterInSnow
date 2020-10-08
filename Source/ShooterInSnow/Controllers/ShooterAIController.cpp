// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
        const auto ActorLocation = GetPawn()->GetActorLocation();
        GetBlackboardComponent()->SetValueAsVector(TEXT("InitialLocation"),
            ActorLocation);
        
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(LineOfSightTo(PlayerPawn))
    {
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),
            PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLastKnowLocation"),
            PlayerPawn->GetActorLocation());
    }
    else
    {
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
        
    }
}
