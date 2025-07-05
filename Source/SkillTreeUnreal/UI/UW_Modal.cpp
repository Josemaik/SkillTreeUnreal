// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Modal.h"

#include "Components/Button.h"


void UUW_Modal::NativeConstruct()
{
	Super::NativeConstruct();

	//ConfirmButton->OnPressed.AddDynamic(this,&UUW_Modal::OnConfirmButtonPressed);
	CancelButton->OnPressed.AddDynamic(this, &UUW_Modal::OnCancelButtonPressed);
}


// void UUW_Modal::OnConfirmButtonPressed()
// {
// 	
// }

void UUW_Modal::OnCancelButtonPressed()
{
	SetVisibility(ESlateVisibility::Collapsed);
}