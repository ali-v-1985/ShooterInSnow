// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterInSnow/Characters/ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
        const auto ShooterPawn = Cast<AShooterCharacter>(GetPawn());
        if (ShooterPawn == nullptr)
        {
            return;
        }
        GetBlackboardComponent()->SetValueAsVector(TEXT("InitialLocation"),
            ShooterPawn->GetActorLocation());

        GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolStartLocation"),
            ShooterPawn->GetActorLocation());

        GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolEndLocation"),
            ShooterPawn->GetPatrolEndLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(GetPawn());
    if(ShooterCharacter != nullptr)
    {
        return ShooterCharacter->IsDead();
    }
    return true;
}
