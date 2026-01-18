#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MyMainWidget.generated.h"

UCLASS()
class NET_PJB_API UMyMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	UFUNCTION()
	void UpdateMyName(const FString& InName);

	UFUNCTION()
	void UpdateMyScore(int32 InScore);

	UFUNCTION()
	void UpdateOtherName(const FString& InName);

	UFUNCTION()
	void UpdateOtherScore(int32 InScore);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> MainTimer;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScoreInfoWidget> MyScoreInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScoreInfoWidget> OtherScoreInfo;

	UPROPERTY()
	TWeakObjectPtr<class AMyGameStateBase> CachedGameState;

private:
	FTimerHandle PlayerCheckTimer;

	void SetCachedGameState(class AMyGameStateBase* InGameStateBase);
	void UpdateTimerText();
	void FindAndBindPlayers();
};
