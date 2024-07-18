// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Bot.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIControllerCustom.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;

UCLASS()
class TESTAI_API AAIControllerCustom : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Protected|Components")
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Protected|Bot")
	ABot* Bot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Protected|Components")
	UAIPerceptionComponent* AIPerceptionComponent;

private:
	UPROPERTY()
	UAISenseConfig_Sight* AISense_Sight;

	UPROPERTY()
	UAISenseConfig_Hearing* AISense_Hearing;

	UPROPERTY()
	UAISenseConfig_Damage* AISense_Damage;

	UPROPERTY()
	FAIStimulus StimulusCurrent;

	UPROPERTY()
	APawn* PlayerEnemy;

	UPROPERTY()
	bool IsHasPlayer = false;

public:
	explicit AAIControllerCustom(FObjectInitializer const& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

	// ������� ��������� ������ ���������
	UFUNCTION(BlueprintCallable, Category = "Public|Set")
	void SetEnableBehaviorTree(bool IsOn) const;

	// ������ ��������, ��� ��� ������� ����
	UFUNCTION(BlueprintCallable, Category = "Public|Set")
	void SetIsHearNoise(bool IsOn) const;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	// �������� �� ������� OnTargetPerceptionUpdated
	UFUNCTION(Category = "Protected|Bind")
	void BindOnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	// ������� ����� ��������������
	UFUNCTION(Category = "Private|Set")
	void SetPatrolLocations(FVector ForwardLocation, FVector BackwardLocation) const;

	// ���������� ����� ��������������
	UFUNCTION(Category = "Private")
	void CalculatePatrolLocations() const;

	// ���������� ��������� ���� � ������� �� ����
	UFUNCTION(Category = "Private")
	FVector CalculateNoiseLocation(FVector StimulusLocation, FVector ReceiverLocation) const;

	// ��������� ������
	UFUNCTION(Category = "Private")
	void BotVisionHandler();

	// ��������� �����
	UFUNCTION(Category = "Private")
	void BotHearingHandler();

	// ��������� ��������� �����
	UFUNCTION(Category = "Private")
	void BotDamageHandler();
};
