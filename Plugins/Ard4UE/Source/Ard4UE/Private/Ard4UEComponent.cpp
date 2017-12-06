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
	if (mySerial.isOpen())
	{
		mySerial.flush();
		mySerial.close();
	}
}

void UArd4UEComponent::initializeConnection(FName COMPort, int BAUDRate /*= 9600*/, int bytesize /*= 8*/) const
{
	mySerial.setPort(std::string(TCHAR_TO_UTF8(*COMPort.ToString())));
	mySerial.setBaudrate(BAUDRate);

	mySerial.setBytesize(serial::eightbits);

	mySerial.open();
}

UArd4UEComponent::UArd4UEComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UArd4UEComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UArd4UEComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (mySerial.isOpen())
	{
		if (mySerial.available() > 1)
		{
			std::string stringRead;
			if (mySerial.readline(stringRead))
			{
				FString stringReadFS(stringRead.c_str());
				FString trimmed = stringReadFS.RightChop(1);

				if (stringReadFS.StartsWith(FString("f")))
				{
					OnSerialFloatRecieved.Broadcast(FCString::Atof(*trimmed));
				}
				else if (stringReadFS.StartsWith(FString("s")))
				{
					OnSerialStringRecieved.Broadcast(trimmed.ReplaceEscapedCharWithChar());
				}
					
			}
		}
	}


}

void UArd4UEComponent::BeginDestroy()
{

	Super::BeginDestroy();

		if ( mySerial.isOpen())
		UArd4UEComponent::disconnectPort();
}

