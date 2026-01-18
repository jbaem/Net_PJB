#include "Item/PickupItem.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/Character.h"

#include "Core/MyPlayerState.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;


	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void APickupItem::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		OnActorBeginOverlap.AddDynamic(this, &APickupItem::OnOverlapBegin);
	}
}

void APickupItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(OnActorBeginOverlap.IsBound())
	{
		OnActorBeginOverlap.RemoveDynamic(this, &APickupItem::OnOverlapBegin);
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
