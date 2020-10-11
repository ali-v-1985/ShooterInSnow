// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetCharacterDeathState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERINSNOW_API UBTService_SetCharacterDeathState : public UBTService_BlackboardBase
{
	GENERATED_BODY()


public:
	UBTService_SetCharacterDeathState();


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
