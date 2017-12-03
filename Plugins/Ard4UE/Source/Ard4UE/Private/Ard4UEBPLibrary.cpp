// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Ard4UEBPLibrary.h"
#include "Ard4UE.h"

UArd4UEBPLibrary::UArd4UEBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


float UArd4UEBPLibrary::initializeConnection(FName COMPort, int BAUDRate)
{
	return -1;
}
