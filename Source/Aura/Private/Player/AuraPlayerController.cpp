// Copyright of FrankCo


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true;
    // Constructor implementation
}

void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    check(AuraContext);
    
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(Subsystem);
    Subsystem->AddMappingContext(AuraContext, 0);
    
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;

    FInputModeGameAndUI InputModeData;
    InputModeData.SetHideCursorDuringCapture(false);
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    SetInputMode(InputModeData);
}
void AAuraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Your custom input component setup code here
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    if (APawn* ControllerPawn = GetPawn<APawn>()) {
        ControllerPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
        ControllerPawn->AddMovementInput(RightDirection, InputAxisVector.X);

    }

}
