// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MainMenu.h"

#include "PlatformTrigger.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuWBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuWBPClass.Class != nullptr)) return;

	MenuClass = MenuWBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->bIsFocusable = true;
	Menu->AddToViewport();

	UMainMenu* MainMenu = Cast<UMainMenu>(Menu);
	if (!ensure(MainMenu != nullptr)) return;

	MainMenu->MenuInterface = this;

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputData;
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputData.SetWidgetToFocus(Menu->TakeWidget());

	PlayerController->SetInputMode(InputData);
	PlayerController->bShowMouseCursor = true;
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& IpAddress)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, FString::Printf(TEXT("Joining %s"), *IpAddress));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(IpAddress, ETravelType::TRAVEL_Absolute);
}
