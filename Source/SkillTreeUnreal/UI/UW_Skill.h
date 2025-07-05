// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Skill.generated.h"

class UCanvasPanel;
class UUW_Modal;
class UImage;
class ASkillTreeUnrealCharacter;
class UButton;

UENUM()
enum class ESkillType
{
	MovementSpeed UMETA(DisplayName = "Movement Speed"),
	Health UMETA(DisplayName = "Health"),
	Damage UMETA(DisplayName = "Damage"),
	JumpSpeed UMETA(DisplayName = "Jump Speed"),
};
/**
 * 
 */
UCLASS()
class SKILLTREEUNREAL_API UUW_Skill : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UCanvasPanel* Canvas;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UButton* SkillButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UImage* SkillIcon;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UUW_Modal* Modal;

	UPROPERTY()
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, Category="Skills")
	int32 Cost;

	UPROPERTY(EditAnywhere, Category="Skills")
	ESkillType SkillType;

	UPROPERTY(EditAnywhere, Category="Skills")
	bool bSkillUnlocked = false;

	UPROPERTY(EditAnywhere, Category="Skills")
	TArray<UUW_Skill*> PreviousSkills;
	
	UPROPERTY()
	ASkillTreeUnrealCharacter* CharacterReference;

	UFUNCTION()
	void OnButtomClicked();

	UFUNCTION()
	void UnlockAbility();

	void SetSkillICon();

	void ChangeBrushFromTextiure(const TCHAR* TextureName);
protected:
	virtual void NativeConstruct() override;
	
};