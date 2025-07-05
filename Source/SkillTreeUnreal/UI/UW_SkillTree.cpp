// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_SkillTree.h"

#include <string>

#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "SkillTreeUnreal/SkillTreeUnrealCharacter.h"

FReply UUW_SkillTree::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}


void UUW_SkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterReference = Cast<ASkillTreeUnrealCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	if (!IsValid(CharacterReference))
	{
		return;
	}

	//Initialize with default value
	SetPointsCounter(100.f);
	
	//notify when skill points changed
	CharacterReference->OnSkillUnlocked.BindUObject(this, &UUW_SkillTree::UpdateSkillPoints);
	
}
void UUW_SkillTree::UpdateSkillPoints() const
{
	SetPointsCounter(CharacterReference->GetSkillPoints());
}

void UUW_SkillTree::SetPointsCounter(int32 NewPoints) const
{
	FText SkillPointsText = FText::AsNumber(NewPoints);
	PointsCounter->SetText(SkillPointsText);
}
