// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_SkillTree.generated.h"

class UUW_Skill;
class UTextBlock;
class UImage;
class UCanvasPanel;
class ASkillTreeUnrealCharacter;

/**
 * 
 */
UCLASS()
class SKILLTREEUNREAL_API UUW_SkillTree : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UCanvasPanel* CanvasPanel;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UImage* BackgroundColor;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UTextBlock* PointsText;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UTextBlock* PointsCounter;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UUW_Skill* MainSkillMovement;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UUW_Skill* MainSkillHealth;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UUW_Skill* MainSkillDamage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UUW_Skill* SubSkillMovement;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UUW_Skill* SubSkillMovement_1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UUW_Skill* SubSkillHealth;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UUW_Skill* SubSkillDamage;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UImage* Branch_Movement_0;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UImage* Branch_Movement_1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UImage* Branch_Health_0;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UImage* Branch_Damage_0;
	

	UPROPERTY()
	ASkillTreeUnrealCharacter* CharacterReference;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void UpdateSkillPoints() const;

	void SetPointsCounter(int32 NewPoints) const;
protected:
	virtual void NativeConstruct() override;
};
