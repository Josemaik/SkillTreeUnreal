// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Skill.h"

#include "UW_Modal.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "SkillTreeUnreal/SkillTreeUnrealCharacter.h"


void UUW_Skill::NativeConstruct()
{
	Super::NativeConstruct();
	
	CharacterReference = Cast<ASkillTreeUnrealCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	//load Icon
	SetSkillICon();

	//button event on pressed
	SkillButton->OnPressed.AddDynamic(this, &UUW_Skill::OnButtomClicked);


	Modal->SetVisibility(ESlateVisibility::Collapsed);
	Modal->ConfirmButton->OnPressed.AddDynamic(this, &UUW_Skill::UnlockAbility);
	
	//skillds already unlocked
	if (bSkillUnlocked)
	{
		UnlockAbility();
	}
}

void UUW_Skill::OnButtomClicked()
{
	//Check if is unlocked
	if (bSkillUnlocked)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Skill already unlocked");
		return;
	}
	
	//check skill points
	if (CharacterReference->GetSkillPoints() < Cost)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Puntos insuficientes");
		return;
	}

	//check previoius skills
	if (PreviousSkills.Num() > 0)
	{   //if there are more than 0, check if are unlocked
		for (UUW_Skill* Skill : PreviousSkills)
		{   //if one of them is locked, fail
			if (IsValid(Skill) && !Skill->bSkillUnlocked)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Previous Skills Locked");
				return;
			}
		}
	}

	//Unlock Ability
	//UnlockAbility();
	Modal->SetVisibility(ESlateVisibility::Visible);
}

void UUW_Skill::UnlockAbility()
{
	Modal->SetVisibility(ESlateVisibility::Collapsed);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Unlock ability");
	bSkillUnlocked = true;
	
	if (!IsValid(CharacterReference))
	{
		return;
	}
	
	//remove cost
	CharacterReference->RemoveSkillsPoints(Cost);

	//change style
	FButtonStyle NewButtonStyle = SkillButton->GetStyle();
	FSlateColor OnNormalColor;
	FSlateColor OnHoverColor;
	
	switch (SkillType)
	{
	case ESkillType::Damage:
		{
			OnNormalColor = FSlateColor(FLinearColor::Red);
			OnHoverColor = FSlateColor(FLinearColor::Red);
		}
		break;
	case ESkillType::Health:
		{
			OnNormalColor = FSlateColor(FLinearColor::Green);
			OnHoverColor = FSlateColor(FLinearColor::Green);
		}
		break;
	case ESkillType::MovementSpeed:
		{
			OnNormalColor = FSlateColor(FLinearColor::Blue);
			OnHoverColor = FSlateColor(FLinearColor::Blue);
		}
		break;
	case ESkillType::JumpSpeed:
		{
			OnNormalColor = FSlateColor(FLinearColor::Blue);
			OnHoverColor = FSlateColor(FLinearColor::Blue);
		}
		break;
	default:
		break;
	}
	
	NewButtonStyle.Normal.TintColor = OnNormalColor;
	NewButtonStyle.Hovered.TintColor = OnHoverColor;

	SkillButton->SetStyle(NewButtonStyle);
}

void UUW_Skill::SetSkillICon()
{
	switch (SkillType)
	{
		case ESkillType::Damage: ChangeBrushFromTextiure(TEXT("/Game/Icons/damage.damage"));
			break;
		case ESkillType::MovementSpeed: ChangeBrushFromTextiure(TEXT("/Game/Icons/sprint_icon.sprint_icon"));
			break;
		case ESkillType::Health: ChangeBrushFromTextiure(TEXT("/Game/Icons/health.health"));
			break;
		case ESkillType::JumpSpeed: ChangeBrushFromTextiure(TEXT("/Game/Icons/jump.jump"));
			break;
		default:
			break;
	}
}

void UUW_Skill::ChangeBrushFromTextiure(const TCHAR* TextureName)
{
	Icon = LoadObject<UTexture2D>(nullptr, TextureName);
	if (Icon)
	{
		SkillIcon->SetBrushFromTexture(Icon);
	}
}
