#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "MyGameModeBase.generated.h"

UCLASS()
class NET_PJB_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

};
