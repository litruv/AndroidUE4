// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "serial/serial.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ard4UEComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageFloatDelegate, float, Number);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageStringDelegate, FString, String);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageEventDelegate, int32, IntParam);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARD4UE_API UArd4UEComponent : public UActorComponent
{
	GENERATED_BODY()
		UFUNCTION(BlueprintPure, meta = (DisplayName = "Enumerate Ports", Keywords = "Ard4UE enumerate ports arduino"), Category = "Ard4UE")
		//************************************
		// Returns A list of COM Ports
		// Method:    enumeratePorts
		// FullName:  UArd4UEComponent::enumeratePorts
		// Access:    private 
		// Returns:   void
		// Qualifier: const
		// Parameter: TArray<FString> & ComPorts
		//************************************
		void enumeratePorts(TArray<FString> &ComPorts) const;
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Disconnect ComPort", Keywords = "Ard4UE disconnect arduino"), Category = "Ard4UE")
		//************************************
		// Disconnect the current COM Port
		// Method:    disconnectPort
		// FullName:  UArd4UEComponent::disconnectPort
		// Access:    private 
		// Returns:   void
		// Qualifier: const
		//************************************
		void disconnectPort() const;
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Initialize Connection", Keywords = "Ard4UE initialize arduino"), Category = "Ard4UE")
		//************************************
		// Connect to a port (Will disconnect previous one)
		// Method:    initializeConnection
		// FullName:  UArd4UEComponent::initializeConnection
		// Access:    private 
		// Returns:   void
		// Qualifier: const
		// Parameter: FName COMPort
		// Parameter: int BAUDRate
		//************************************
		void initializeConnection(FName COMPort, int BAUDRate = 9600) const;
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Auto Connect", Keywords = "Ard4UE auto connect arduino"), Category = "Ard4UE")
		//************************************
		// Connect to a COM port with the specified device ID
		// Method:    autoConnect
		// FullName:  UArd4UEComponent::autoConnect
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: FString controllerID
		// Parameter: int Baud
		// Parameter: bool & Connected
		//************************************
		void autoConnect(FString controllerID, int Baud, bool &Connected);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Send Command", Keywords = "Ard4UE send command arduino"), Category = "Ard4UE")
		//************************************
		// Send command via serial
		// Method:    sendCommand
		// FullName:  UArd4UEComponent::sendCommand
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: FString command
		//************************************
		void sendCommand(FString command);



	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
	// Float Received delegate
		FMessageFloatDelegate OnSerialFloatRecieved;
	
	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// String Received delegate
		FMessageStringDelegate OnSerialStringRecieved;

	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// Event 1
		FMessageEventDelegate OnEvent1Recieved;

	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// Event 2
		FMessageEventDelegate OnEvent2Recieved;

	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// Event 3
		FMessageEventDelegate OnEvent3Recieved;

	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// Event 4
		FMessageEventDelegate OnEvent4Recieved;

	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// Event 5
		FMessageEventDelegate OnEvent5Recieved;

	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// Event 6
		FMessageEventDelegate OnEvent6Recieved;

	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// Event 7
		FMessageEventDelegate OnEvent7Recieved;

	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// Event 8
		FMessageEventDelegate OnEvent8Recieved;

	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// Event 9
		FMessageEventDelegate OnEvent9Recieved;

	UPROPERTY(BlueprintAssignable, Category = "Ard4UE")
		// Event 10
		FMessageEventDelegate OnEvent10Recieved;

public:
	// Sets default values for this component's properties
	UArd4UEComponent();

protected:

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	virtual void BeginDestroy() override;

};
