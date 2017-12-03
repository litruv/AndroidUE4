// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Ard4UEBPLibrary.generated.h"


UCLASS()
class UArd4UEBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Initialize Connection", Keywords = "Ard4UE initialize arduino"), Category = "Ard4UE")
	static float initializeConnection(FName COMPort, int BAUDRate);
};
