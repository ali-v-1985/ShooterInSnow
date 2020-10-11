// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllShooterGameMode.h"

#include "EngineUtils.h"
#include "ShooterInSnow/Controllers/ShooterAIController.h"

void AKillThemAllShooterGameMode::PawnKilled(APawn* Pawn)
{
   Super::PawnKilled(Pawn);
   APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
   if(PlayerController != nullptr)
   {
       EndGame(false);
   }

   if(IsAllAIDead())
   {
       EndGame(true);
   }
    
    
}

void AKillThemAllShooterGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}

bool AKillThemAllShooterGameMode::IsAllAIDead()
{
    for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!AIController->IsDead())
        {
            return false;
        }
    }
    return true;
}
