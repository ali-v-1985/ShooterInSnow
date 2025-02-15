// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameModeBase.h"
#include "KillThemAllShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERINSNOW_API AKillThemAllShooterGameMode : public AShooterGameModeBase
{
	GENERATED_BODY()


public:
	bool IsAllAIDead();
	virtual void PawnKilled(class APawn* Pawn) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
