#include <iostream>
#include <stdarg.h>
#include "Command.h"

typedef uint8_t byte;

bool isReceivingPacket = false;
int currentPacketByte = 0;
int expectedPacketLength = 4;
byte version;
Command cmd;
byte ID;
byte* data;
int datalen;

void DebugMessage(const char* format, ...) {

	char* buff = (char*)malloc(256);
	va_list argptr;
	va_start(argptr, format);
	snprintf(buff, 256, format, argptr);
	va_end(argptr);
	std::cout << buff << std::endl;
	free(buff);
}


int BasePacketLength(Command cmd)
{
	switch (cmd)
	{
	case Command::OK:
	case Command::Reset:
	case Command::Refresh:
	case Command::Unsupported:
	case Command::Forbidden:
	case Command::NotFound:
	case Command::TypeMismatch:
	case Command::DisplayString:
	case Command::GetInteger16:
	case Command::GetInteger32:
	case Command::GetBoolean:
	case Command::GetFloat:
	case Command::GetString:
		//no data, id
		return 4;
	case Command::VersionUnsupported:
	case Command::SetBoolean:
		//1 byte data, id
		return 5;
	case Command::SetInteger16:
		//2 byte int data, id
		return 6;
	case Command::SetInteger32:
	case Command::SetFloat:
		//4 byte int data, id
		return 8;
	case Command::SetString:
	case Command::Debug:
		//n byte string data, id
		return 6;
	default:
		return 4;
	}
}
bool HasNData(Command _cmd)
{
	switch (_cmd)
	{
	case Command::OK:
	case Command::Reset:
	case Command::Refresh:
	case Command::Unsupported:
	case Command::Forbidden:
	case Command::NotFound:
	case Command::TypeMismatch:
	case Command::DisplayString:
	case Command::GetInteger16:
	case Command::GetInteger32:
	case Command::GetBoolean:
	case Command::GetFloat:
	case Command::GetString:
	case Command::VersionUnsupported:
	case Command::SetBoolean:
	case Command::SetInteger16:
	case Command::SetInteger32:
	case Command::SetFloat:
		return false;
	case Command::SetString:
	case Command::Debug:
		return true;
	default:
		return false;
	}
}

void processByte(unsigned char temp) {

	if (isReceivingPacket) {
		if (currentPacketByte == 1) {
			version = temp;
			currentPacketByte++;
		}
		else if (currentPacketByte == 2) {
			cmd = static_cast<Command>(temp);
			expectedPacketLength = BasePacketLength(cmd);
			currentPacketByte++;
		}
		else if (currentPacketByte == 3) {
			ID = temp;
			currentPacketByte++;
		}
		else if (currentPacketByte == 4) {
			if (HasNData(cmd)) {
				datalen = temp;
			}
			else {
				datalen = expectedPacketLength - 4;
				data = new byte[datalen];
				data[0] = temp;
			}
			currentPacketByte++;
		}
		else if (currentPacketByte == 5) {
			if (HasNData(cmd)) {
				datalen += temp << 8;
			}
			else {
				data[1] = temp;
			}
			currentPacketByte++;
		}
		else if (currentPacketByte > 5) {
			if (HasNData(cmd)) {
				data = new byte[expectedPacketLength - 6];
				data[currentPacketByte - 6] = temp;
			}
			else {
				data[currentPacketByte - 4] = temp;
			}
			currentPacketByte++;
		}
		else {
			isReceivingPacket = false;
			currentPacketByte = 0;
		}
		if (currentPacketByte >= expectedPacketLength) {
			//Packet Done
			isReceivingPacket = false;
			currentPacketByte = 0;
			//HandlePacket();
			DebugMessage("Handled Packet");
			DebugMessage("Command %d",cmd);
			DebugMessage("ID: %d", ID);
			DebugMessage("datalen %d", datalen);
			DebugMessage("Value: %X",data);
			
			for (int j = 0; j < datalen; j++) {
				DebugMessage("%02X ", data[j]);
			}
			std::cout << std::endl;
		}
	}
	else {
		if (temp == 0xF0) {
			isReceivingPacket = true;
			currentPacketByte++;
			expectedPacketLength = 4;
		}
	}
}


int main() {

	byte* inputdata = new byte[6]{ 0xF0, 0x01, 0x13, 0x02, 0xec, 0x1 };

	for (int i = 0;i < 6;i++) {
		std::cout << "Feeding ";
		printf("%02X", inputdata[i]);
		std::cout << std::endl;
		processByte(inputdata[i]);
	}
	std::cout << "Done." << std::endl;
	std::cout << "Press [Enter] to continue . . ." << std::endl;
	std::cin.get();
	return 0;
}

