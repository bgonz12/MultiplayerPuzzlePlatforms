// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostMainMenuButton != nullptr)) return false;
	HostMainMenuButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinMainMenuButton != nullptr)) return false;
	JoinMainMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(ConfirmJoinMenuButton != nullptr)) return false;
	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(CancelJoinMenuButton != nullptr)) return false;
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

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

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	this->RemoveFromViewport();

	if (!ensure(InWorld != nullptr)) return;

	APlayerController* PlayerController = InWorld->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputData;
	PlayerController->SetInputMode(InputData);
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::HostServer()
{
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Host();
}

void UMainMenu::JoinServer()
{
	if (!ensure(IPAddressField != nullptr)) return;
	const FString& Address = IPAddressField->GetText().ToString();

	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Join(Address);
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterfaceToSet)
{
	this->MenuInterface = MenuInterfaceToSet;
}