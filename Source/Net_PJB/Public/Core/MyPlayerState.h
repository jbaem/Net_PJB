#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "MyPlayerState.generated.h"

UENUM(BlueprintType)
enum class EReadyType : uint8
{
	READY			UMETA(DisplayName = "Ready"),
	NOT_READY		UMETA(DisplayName = "Not Ready")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChangedDelegate, int32, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNameChangedDelegate, const FString&, NewName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChangedDelegate, EReadyType, NewState);


UCLASS()
class NET_PJB_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMyPlayerState();

	FOnScoreChangedDelegate OnScoreChangedDel;
	FOnNameChangedDelegate OnNameChangedDel;
	FOnStateChangedDelegate OnStateChangedDel;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UFUNCTION(BlueprintCallable, Category = "My")
	void SetReadyType(EReadyType NewReadyType);

	UFUNCTION(BlueprintCallable, Category = "My")
	void AddMyScore(int32 ScoreToAdd);

	UFUNCTION(BlueprintCallable, Category = "My")
	void ResetMyScore();
	
	UFUNCTION(BlueprintCallable, Category = "My")
	void SetMyName(const FString& NewName);


	UFUNCTION(BlueprintCallable, Category = "My")
	EReadyType GetReadyType() const { return ReadyType; }

	UFUNCTION(BlueprintCallable, Category = "My")
	int32 GetMyScore() const { return MyScore; }

	UFUNCTION(BlueprintCallable, Category = "My")
	FString GetMyName() const { return MyName; }

protected:
	UFUNCTION()
	void OnRep_ReadyType();
	
	UFUNCTION()
	void OnRep_MyScore();
	
	UFUNCTION()
	void OnRep_MyName();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_ReadyType, BlueprintReadWrite, Category = "My")
	EReadyType ReadyType = EReadyType::NOT_READY;

	UPROPERTY(ReplicatedUsing = OnRep_MyScore, BlueprintReadOnly, Category = "My")
	int32 MyScore = 0;
	
	UPROPERTY(ReplicatedUsing = OnRep_MyName, BlueprintReadOnly, Category = "My")
	FString MyName;
};
