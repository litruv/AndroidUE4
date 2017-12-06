// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "serial/serial.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ard4UEComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageDelegate, float, Number);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARD4UE_API UArd4UEComponent : public UActorComponent
{
	GENERATED_BODY()
		UFUNCTION(BlueprintPure, meta = (DisplayName = "Enumerate Ports", Keywords = "Ard4UE enumerate ports arduino"), Category = "Ard4UE")
		void enumeratePorts(TArray<FString> &ComPorts) const;
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Disconnect ComPort", Keywords = "Ard4UE disconnect arduino"), Category = "Ard4UE")
		void disconnectPort() const;
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Initialize Connection", Keywords = "Ard4UE initialize arduino"), Category = "Ard4UE")
		void initializeConnection(FName COMPort, int BAUDRate = 9600, int bytesize = 8) const;


	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		FMessageDelegate OnSerialFloatRecieved;
public:	
	// Sets default values for this component's properties
	UArd4UEComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
