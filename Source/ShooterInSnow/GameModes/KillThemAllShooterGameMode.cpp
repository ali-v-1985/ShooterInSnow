// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllShooterGameMode.h"

void AKillThemAllShooterGameMode::PawnKilled(APawn* Pawn)
{
   Super::PawnKilled(Pawn);
   APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
   if(PlayerController != nullptr)
   {
      PlayerController->GameHasEnded(nullptr, false);
   }
   else
   {
      
   }
}
