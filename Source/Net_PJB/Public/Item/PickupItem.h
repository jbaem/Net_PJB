#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PickupItem.generated.h"

UCLASS()
class NET_PJB_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupItem();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void FinishedDestory();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My")
	TObjectPtr<class UStaticMeshComponent> Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My")
	TObjectPtr<class USphereComponent> Collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Score")
	int32 MyScore = 1;
};
