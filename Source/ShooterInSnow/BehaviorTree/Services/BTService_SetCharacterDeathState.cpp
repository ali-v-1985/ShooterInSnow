// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetCharacterDeathState.h"


#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterInSnow/Characters/ShooterCharacter.h"

UBTService_SetCharacterDeathState::UBTService_SetCharacterDeathState()
{
    NodeName = TEXT("Set Player Is Dead");
}

void UBTService_SetCharacterDeathState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
    float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(PlayerPawn == nullptr)
    {
        return;
    }
    AShooterCharacter* PlayerShooterCharacter = Cast<AShooterCharacter>(PlayerPawn);
    if(PlayerShooterCharacter == nullptr)
    {
        return;
    }

    OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),
        PlayerShooterCharacter->IsDead());
    UE_LOG(LogTemp, Warning, TEXT("Is Player Dead %d "), PlayerShooterCharacter->IsDead());
    
}


