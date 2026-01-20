#include "Item/ScoreItemSpawner.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"
#include "Core/MyGameStateBase.h"

AScoreItemSpawner::AScoreItemSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	SpawnVolume->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));
}

void AScoreItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (AMyGameStateBase* GS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		GS->OnGameStartDel.AddDynamic(this, &AScoreItemSpawner::StartSpawning);
		GS->OnGameFinishDel.AddDynamic(this, &AScoreItemSpawner::StopSpawning);
	}
}

void AScoreItemSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

	if (AMyGameStateBase* GS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		GS->OnGameStartDel.RemoveDynamic(this, &AScoreItemSpawner::StartSpawning);
		GS->OnGameFinishDel.RemoveDynamic(this, &AScoreItemSpawner::StopSpawning);
	}

	Super::EndPlay(EndPlayReason);
}

void AScoreItemSpawner::StartSpawning()
{
	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&AScoreItemSpawner::SpawnItems,
			SpawnInterval,
			true,
			SpawnDelay
		);
	}
}

void AScoreItemSpawner::StopSpawning()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
}

void AScoreItemSpawner::SpawnItems()
{
	for (int i = 0; i < SpawnCount; ++i)
	{
		SpawnEachItem();
	}
}

void AScoreItemSpawner::SpawnEachItem()
{
	if (!ScoreItemClass)
	{
		return;
	}

	UWorld* World = GetWorld();
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	if(!World || !NavSys)
	{
		return;
	}

	//FVector SpawnLocation = GetRandomPointInVolume();
	FVector SpawnLocation = FVector::ZeroVector;
	
	bool bFoundValidLocation = false;
	const int32 MaxAttempts = 10;
	
	FVector SpawnExtent = SpawnVolume->GetScaledBoxExtent();
	for (int32 i = 0; i < MaxAttempts; ++i)
	{
		FVector RandomPoint = GetRandomPointInVolume();
		FNavLocation ResultLocation;

		if (NavSys->ProjectPointToNavigation(RandomPoint, ResultLocation, SpawnExtent))
		{
			SpawnLocation = ResultLocation.Location;

			SpawnLocation.Z += 200.0f;

			bFoundValidLocation = true;
			break;
		}
	}

	if (bFoundValidLocation)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		World->SpawnActor<AActor>(
			ScoreItemClass,
			SpawnLocation,
			FRotator::ZeroRotator,
			SpawnParams
		);
	}
}

FVector AScoreItemSpawner::GetRandomPointInVolume() const
{
	FVector Origin = SpawnVolume->GetComponentLocation();
	FVector BoxExtent = SpawnVolume->GetScaledBoxExtent();

	return UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
}
