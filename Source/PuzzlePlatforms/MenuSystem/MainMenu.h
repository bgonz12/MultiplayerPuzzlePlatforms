// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* HostMainMenuButton;

	UPROPERTY(Meta = (BindWidget))
	class UButton* JoinMainMenuButton;

	UPROPERTY(Meta = (BindWidget))
	class UButton* CancelJoinMenuButton;

	UPROPERTY(Meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(Meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(Meta = (BindWidget))
	class UWidget* JoinMenu;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenJoinMenu();


private:
	IMenuInterface* MenuInterface;

public:
	void SetMenuInterface(IMenuInterface* MenuInterfaceToSet);
};
