#include "Item/PickupItem.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/Character.h"

#include "Core/MyPlayerState.h"
#include "Core/MyGameStateBase.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
}

void APickupItem::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		OnActorBeginOverlap.AddDynamic(this, &APickupItem::OnOverlapBegin);
		if (AMyGameStateBase* GS = GetWorld()->GetGameState<AMyGameStateBase>())
		{
			GS->OnGameFinishDel.AddDynamic(this, &APickupItem::FinishedDestory);
		}
	}
}

void APickupItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(OnActorBeginOverlap.IsBound())
	{
		OnActorBeginOverlap.RemoveDynamic(this, &APickupItem::OnOverlapBegin);
	}
	
	if (AMyGameStateBase* GS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		GS->OnGameFinishDel.RemoveDynamic(this, &APickupItem::FinishedDestory);
	}

	Super::EndPlay(EndPlayReason);
}

void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupItem::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HasAuthority())
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character)
		{
			AMyPlayerState* PS = Character->GetPlayerState<AMyPlayerState>();
			if (PS)
			{
				PS->AddMyScore(10);
				Destroy();
			}
		}
	}
}

void APickupItem::FinishedDestory()
{
	if (HasAuthority())
	{
		Destroy();
	}
}
