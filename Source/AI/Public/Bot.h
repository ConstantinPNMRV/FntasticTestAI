// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "GameFramework/Character.h"
#include "Bot.generated.h"

UCLASS()
class TESTAI_API ABot : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCrowdFollowingComponent* CrowdFollowingComponent;

private:
	UPROPERTY()
	int32 HitCounter = 0;

public:
	ABot();

	virtual void Tick(float DeltaTime) override;

	// ��������� ������ ���������
	UFUNCTION(BlueprintCallable, Category = "Public|Set")
	UBehaviorTree* GetBehaviorTree() const;

	// ������� ��������� ������ ���������
	UFUNCTION(BlueprintCallable, Category = "Public|Set")
	void SetEnableBehaviorTree(bool IsOn);

protected:
	virtual void BeginPlay() override;

	// �������� ��������� �����
	UFUNCTION(Category = "Protected|Bind")
	void BindOnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
};
