#include "Ard4UEComponent.h"
#include "Ard4UE.h"
#include "engine.h"


serial::Serial mySerial;


void UArd4UEComponent::enumeratePorts(TArray<FString> &ComPorts) const
{
	std::vector<serial::PortInfo> devices_found = serial::list_ports();
	std::vector<serial::PortInfo>::iterator iter = devices_found.begin();

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

void UArd4UEComponent::initializeConnection(FName COMPort, int BAUDRate /*= 9600*/) const
{
	mySerial.setPort(std::string(TCHAR_TO_UTF8(*COMPort.ToString())));
	mySerial.setBaudrate(BAUDRate);

	//Try Catch to avoid in use devices
	try {
		mySerial.open();
	}
	catch (const std::exception&)
	{

	}
}

void UArd4UEComponent::sendCommand(FString command)
{
	if (mySerial.isOpen())
		mySerial.write(TCHAR_TO_UTF8(*command));
}

void UArd4UEComponent::autoConnect(FString controllerID, int Baud, bool &Connected)
{
	if (mySerial.isOpen())
	{
		//Try Catch to avoid in use devices
		try {
			disconnectPort();
		}
		catch (const std::exception&)
		{

		}
	}

	Connected = false;

	TArray<FString> portCollection;
	enumeratePorts(portCollection);

	for (FString portName : portCollection)
	{
		initializeConnection(FName(*portName), Baud);
		if (mySerial.isOpen())
		{
			sendCommand("id");
			std::string stringRead;

			//100ms per check per device (20*device count)(seems reliable)
			mySerial.setTimeout(serial::Timeout::max(), 100, 0, 100, 0);

			for (int i = 0; i < 20; i++)
			{
				mySerial.readline(stringRead);

				//Look for the 'i'nformation character
				if (FString(stringRead.c_str()).StartsWith("i"))
				{
					break;
				}

				//clear stringRead for next loop.
				stringRead.clear();
			}

			//Clean up and compare strings.
			FString stringConvert(stringRead.c_str());
			stringConvert.RemoveFromEnd("\r\n");
			stringConvert.RemoveFromStart("i");

			if (stringConvert.Equals(controllerID))
			{
				Connected = true;
				break;
			}

			//disconnect and check the next one
			disconnectPort();
		}
	}


}

UArd4UEComponent::UArd4UEComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UArd4UEComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (mySerial.isOpen())
		if (mySerial.available() > 1)
		{
			std::string stringRead;
			if (mySerial.readline(stringRead))
			{
				FString stringReadFS(stringRead.c_str());
				FString trimmed = stringReadFS.RightChop(1);

				trimmed.RemoveFromEnd("\r\n");

				//Float Broadcast
				if (stringReadFS.StartsWith(FString("f")))
				{
					OnSerialFloatRecieved.Broadcast(FCString::Atof(*trimmed));
				}
				//String Broadcast
				else if (stringReadFS.StartsWith(FString("s")))
				{
					OnSerialStringRecieved.Broadcast(trimmed.ReplaceEscapedCharWithChar());
				}
				//Event Broadcast
				else if (stringReadFS.StartsWith(FString("e")))
				{
					FString leftparam, rightparam;

					trimmed.Split(",", &leftparam, &rightparam);

					int eventNum = FCString::Atoi(*leftparam);
					int paramNum = FCString::Atoi(*rightparam);

					switch (eventNum)
					{
					case 1:
						OnEvent1Recieved.Broadcast(paramNum);
						break;
					case 2:
						OnEvent2Recieved.Broadcast(paramNum);
						break;
					case 3:
						OnEvent3Recieved.Broadcast(paramNum);
						break;
					case 4:
						OnEvent4Recieved.Broadcast(paramNum);
						break;
					case 5:
						OnEvent5Recieved.Broadcast(paramNum);
						break;
					case 6:
						OnEvent6Recieved.Broadcast(paramNum);
						break;
					case 7:
						OnEvent7Recieved.Broadcast(paramNum);
						break;
					case 8:
						OnEvent8Recieved.Broadcast(paramNum);
						break;
					case 9:
						OnEvent9Recieved.Broadcast(paramNum);
						break;
					case 10:
						OnEvent10Recieved.Broadcast(paramNum);
						break;

					default:
						break;
					}

				}

			}
		}
}

void UArd4UEComponent::BeginDestroy()
{
	Super::BeginDestroy();

	//Kill connection on object destroy
	if (mySerial.isOpen())
		UArd4UEComponent::disconnectPort();

}

