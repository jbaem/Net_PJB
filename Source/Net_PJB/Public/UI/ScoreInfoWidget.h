#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ScoreInfoWidget.generated.h"

UCLASS()
class NET_PJB_API UScoreInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateName(const FString& InName);
	void UpdateScore(int32 InScore);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Name;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Score;
};
