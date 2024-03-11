// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "GameFramework/Character.h"
#include "Bot.generated.h"



UCLASS()
class TESTAI_API ABot : public ACharacter
{
	GENERATED_BODY()

public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCrowdFollowingComponent* CrowdFollowingComponent;

private:
	UPROPERTY()
	int32 HitCounter = 0;

public:
	// Sets default values for this character's properties
	ABot();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Получение дерева поведения
	UFUNCTION(BlueprintCallable, Category = "Public|Set")
	UBehaviorTree* GetBehaviorTree() const;

	// Задание активации дерева поведения
	UFUNCTION(BlueprintCallable, Category = "Public|Set")
	void SetEnableBehaviorTree(bool IsOn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Фиксация получения урона
	UFUNCTION(Category = "Protected|Bind")
	void BindOnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
};
