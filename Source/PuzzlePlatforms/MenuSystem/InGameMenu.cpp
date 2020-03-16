// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	this->bIsFocusable = true;
	this->AddToViewport();

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return false;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return false;

	FInputModeUIOnly InputData;
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputData.SetWidgetToFocus(this->TakeWidget());

	PlayerController->SetInputMode(InputData);
	PlayerController->bShowMouseCursor = true;

	return true;
}
