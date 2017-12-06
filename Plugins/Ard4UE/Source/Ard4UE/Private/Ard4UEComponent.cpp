// Fill out your copyright notice in the Description page of Project Settings.

#include "Ard4UEComponent.h"
#include "Ard4UE.h"
#include "engine.h"


using std::vector;
serial::Serial mySerial;

void UArd4UEComponent::enumeratePorts(TArray<FString> &ComPorts) const
{
	vector<serial::PortInfo> devices_found = serial::list_ports();
	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while (iter != devices_found.end())
	{
		serial::PortInfo device = *iter++;
		ComPorts.Add(FString(device.port.c_str()));
	}
}

void UArd4UEComponent::disconnectPort() const
{

	mySerial.flush();
	mySerial.close();
}

void UArd4UEComponent::initializeConnection(FName COMPort, int BAUDRate /*= 9600*/, int bytesize /*= 8*/) const
{
	mySerial.setPort(std::string(TCHAR_TO_UTF8(*COMPort.ToString())));
	mySerial.setBaudrate(BAUDRate);

	mySerial.setBytesize(serial::eightbits);

	mySerial.open();
}

// Sets default values for this component's properties
UArd4UEComponent::UArd4UEComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UArd4UEComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UArd4UEComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

