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

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(Meta = (BindWidget))
	class UButton* JoinButton;

	UFUNCTION()
	void HostServer();

public:
	IMenuInterface* MenuInterface;
};
