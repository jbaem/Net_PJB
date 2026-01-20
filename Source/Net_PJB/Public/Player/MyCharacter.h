#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MyCharacter.generated.h"

UCLASS()
class NET_PJB_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnRep_PlayerState() override;

public:
	UFUNCTION(BlueprintCallable, Category = "My|Input")
	virtual void DoMove(float Right, float Forward);
	
	UFUNCTION(BlueprintCallable, Category = "My|Input")
	virtual void DoLook(float Yaw, float Pitch);
	
	UFUNCTION(BlueprintCallable, Category = "My|Input")
	virtual void DoJumpStart();

	UFUNCTION(BlueprintCallable, Category = "My|Input")
	virtual void DoJumpStop();

protected:
	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Widget")
	TObjectPtr<class UWidgetComponent> NameWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Input")
	TObjectPtr<class UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Input")
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Input")
	TObjectPtr<class UInputAction> LookAction;

private:
	void InitCharacterMovement();

	void InitComponents();
	void InitCameraComponent();
	void InitWidgetComponent();

	void UpdateNameWidgetRotation();
	void UpdateName(const FString& InName);
	void UpdateWidgetInfo();
};
