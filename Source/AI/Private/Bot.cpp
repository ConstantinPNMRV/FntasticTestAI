// Fill out your copyright notice in the Description page of Project Settings.

#include "Bot.h"
#include "AIControllerCustom.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/NavMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ABot::ABot()
{
	PrimaryActorTick.bCanEverTick = true;

	// ������������� SkeletalMesh
	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	SkeletalMeshComponent->SetRelativeLocation(FVector(0, 0, -89));
	SkeletalMeshComponent->SetRelativeRotation(FRotator(0, 270, 0));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BotSkeletalMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'"));
	if (BotSkeletalMesh.Succeeded())
		SkeletalMeshComponent->SetSkeletalMesh(BotSkeletalMesh.Object);

	// ������� AnimBlueprint ��� SkeletalMesh
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> BotAnimBlueprint(TEXT("AnimBlueprint'/Game/Characters/Mannequins/Animations/ABP_Manny.ABP_Manny'"));
	if (BotAnimBlueprint.Succeeded())
		SkeletalMeshComponent->SetAnimClass(BotAnimBlueprint.Object->GeneratedClass);

	// ������������� BehaviorTree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BotBehaviorTree(TEXT("BehaviorTree'/Game/Blueprints/BT_BotCharacter.BT_BotCharacter'"));
	if (BotBehaviorTree.Succeeded())
		BehaviorTree = BotBehaviorTree.Object;

	// ���������� ������ AIController �� ���������
	static ConstructorHelpers::FClassFinder<AAIControllerCustom> BotAIControllerCustom(TEXT("/Script/CoreUObject.Class'/Script/TestAI.AIControllerCustom'"));
	if (BotAIControllerCustom.Succeeded())
		AIControllerClass = BotAIControllerCustom.Class;

	// ������������� �� OnComponentHit �� �������
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABot::BindOnComponentHit);

	// ������������� ���������� ��� ����� �������� �����
	CrowdFollowingComponent = CreateDefaultSubobject<UCrowdFollowingComponent>("CrowdFollowingComponent");

	// ������� �������� ��������� � ����
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void ABot::BeginPlay()
{
	Super::BeginPlay();
}

void ABot::BindOnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (UKismetSystemLibrary::GetClassDisplayName(OtherActor->GetClass()) == "BP_FirstPersonProjectile_C")
	{
		HitCounter++;
		if (HitCounter == 4)
		{
			UE_LOG(LogTemp, Display, TEXT("Enemy is Dead"));
			SetEnableBehaviorTree(false);
		}
		else if (HitCounter < 4)
		{
			UE_LOG(LogTemp, Display, TEXT("-25 hp"));
		}
	}
}

void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UBehaviorTree* ABot::GetBehaviorTree() const
{
	return BehaviorTree;
}

void ABot::SetEnableBehaviorTree(bool IsOn)
{
	AAIControllerCustom* AIControllerCustom = Cast<AAIControllerCustom>(GetController());
	AIControllerCustom->SetEnableBehaviorTree(IsOn);

	if (IsOn)
		HitCounter = 0;
}
