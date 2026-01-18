#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "MyHUD.generated.h"

UCLASS()
class NET_PJB_API AMyHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


public:
	UUserWidget* GetMainWidget() const { return MainWidget; }

	void InitMainWidget();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|UI")
	TSubclassOf<class UUserWidget> MainWidgetClass;
	UPROPERTY()
	TObjectPtr<class UUserWidget> MainWidget;
};
