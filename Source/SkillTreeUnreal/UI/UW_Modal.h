// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Modal.generated.h"

class UCanvasPanel;
class UTextBlock;
class UBorder;
class UButton;
class UVerticalBox;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class SKILLTREEUNREAL_API UUW_Modal : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UBorder* BorderBackground;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UCanvasPanel* CanvasPanel;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UVerticalBox* VerticalBox;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UHorizontalBox* HorizontalBox;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UTextBlock* ModalText;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UButton* CancelButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UTextBlock* CancelText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UTextBlock* ConfirmText;

	UFUNCTION()
	void OnCancelButtonPressed();
	
protected:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UButton* ConfirmButton;
};
