// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()


	UPROPERTY(Meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(Meta = (BindWidget))
	class UButton* JoinButton;
};
