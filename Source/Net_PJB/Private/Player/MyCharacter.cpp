#include "Player/MyCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "UI/MyNameWidget.h"
#include "Core/MyPlayerState.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	InitCharacterMovement();

	InitComponents();

}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitWidgetInfo();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateNameWidgetRotation();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		}
		if(LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		}
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}
	}
}

void AMyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitWidgetInfo();
}

void AMyCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AMyCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController())
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AMyCharacter::DoJumpStart()
{
	Jump();
}

void AMyCharacter::DoJumpStop()
{
	StopJumping();
}

void AMyCharacter::Move(const FInputActionValue & Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void AMyCharacter::Look(const FInputActionValue & Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AMyCharacter::InitCharacterMovement()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void AMyCharacter::InitComponents()
{
	InitCameraComponent();
	InitWidgetComponent();
}

void AMyCharacter::InitCameraComponent()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AMyCharacter::InitWidgetComponent()
{
	NameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameWidget"));
	NameWidgetComponent->SetupAttachment(RootComponent);
}

void AMyCharacter::UpdateNameWidgetRotation()
{
	if (!NameWidgetComponent)
	{
		return;
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC && PC->PlayerCameraManager)
	{
		FVector CameraForwrd = PC->PlayerCameraManager->GetCameraRotation().Vector();
		FRotator LookAtRotation = FRotationMatrix::MakeFromX(-CameraForwrd).Rotator();
		NameWidgetComponent->SetWorldRotation(LookAtRotation);
	}
}

void AMyCharacter::InitWidgetInfo()
{
	if (!IsLocallyControlled())
	{
		return;
	}

	AMyPlayerState* MyPS = Cast<AMyPlayerState>(GetPlayerState());
	if (!MyPS)
	{
		return;
	}

	if(APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if(UMyNameWidget* NameWidget = Cast<UMyNameWidget>(NameWidgetComponent->GetUserWidgetObject()))
		{
			NameWidget->SetPlayerStateInfo(MyPS);
		}
	}
}
