// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Ard4UEBPLibrary.h"
#include "Ard4UE.h"
#include "engine.h"

using std::vector;

UArd4UEBPLibrary::UArd4UEBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


float UArd4UEBPLibrary::initializeConnection(FName COMPort, int BAUDRate)
{
	
	return -1;
}

void UArd4UEBPLibrary::enumeratePorts(TArray<FString> &ComPorts)
{
	vector<serial::PortInfo> devices_found = serial::list_ports();

	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	

	while (iter != devices_found.end())
	{
		serial::PortInfo device = *iter++;
		FString cp(device.port.c_str());
		ComPorts.Add(cp);
	}
}
