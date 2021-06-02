// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../WETypes.h"
#include "WEEggRoller.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnEggOut, AWEEggRoller*, EWECornerDirection, bool);

UCLASS()
class WOLFANDEGGS_API AWEEggRoller : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWEEggRoller();

	virtual void BeginDestroy() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		TArray<class UPaperSpriteComponent*> SpriteComponents;
	
	/** Unique EggRoller idetnifier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EggRoller")
		EWECornerDirection EggRollerPosition;
	
	/** Should Egg roller be activated on spawn? */
	UPROPERTY(EditDefaultsOnly, Category = "EggRoller")
		bool bActivateOnSpawn;

	/** Should Egg roller spawn egg on spawn activation? */
	UPROPERTY(EditDefaultsOnly, Category = "EggRoller")
		bool bShouldAddEggOnSpawn;

	/** Activate Egg Roller */
	UFUNCTION(BlueprintCallable, Category = "EggRoller")
		void Activate(bool bActivate);

	/** Change Push Egg Time. If Immediately is True, then current active timer will be reset */
	UFUNCTION(BlueprintCallable, Category = "EggRoller")
		void SetPushEggTime(float NewTime, bool bImmediately);

	/** Spawn New Egg to Roll, If egg is spawned when first pos is locked, then all positions will be shifted */
	UFUNCTION(BlueprintCallable, Category = "EggRoller")
		void AddEgg();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Control Egg Shifting */
	bool bIsActive;

	/** Move all eggs to next one position */
	void ShiftEggs();

	/** Function On Timer, 
	  * checking if we can catch egg before it fall,
	  * eggs shifting,
	  * then check if we should restart timer */
	UFUNCTION()
		void PushEgg();

	/** Check if we can catch egg, if so -> notify EggOut with bCatched = true.
	  * If Allow Drop, When egg catch fail egg will drop
	  * case when TryToCatchEgg() run on BasketDirectionChange bAllowDrop should be false;
	  * case when TryToCatchEgg() run before ShiftEggs() bAllowDrop should be true
	  */
	void TryToCatchEgg(bool bAllowEggDrop);

	UPROPERTY(EditDefaultsOnly, Category = "EggRoller")
		float PushEggTime;

	FTimerHandle TimerHandle_EggPush;

public:

	/** Delegate to notify when egg is out. 
	  * Fired when eggs falls or when is cached with corresponding isCached flag */
	static FOnEggOut NotifyOnEggOut;

	/** Cache current Basket Direction */
	static EWECornerDirection BasketDirecitonCurrent;

	/** Observer Wolf Basket Direction Change, used to catch egg */
	UFUNCTION()
		void OnWolfBasketDirectionChange(class AWEWolf* Wolf, EWECornerDirection BasketDirection);

private:

	class FDelegateHandle DelegateHandle_BasketDirectionChange;

};
