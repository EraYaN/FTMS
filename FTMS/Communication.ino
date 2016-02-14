#include "Communication.h"
#include <stdarg.h>

//Function Declarations for Communication
/// <summary>
///  Constructor of the Communication class.
/// </summary>
Communication::Communication()
{

}
void Communication::Init() {
  //contruct
  Serial.begin(115200);
}

void Communication::CheckForData() {
  if(isReceivingPacket)
    iterations++;
  if(!Serial.available()&&iterations>MAX_ITERATIONS){
    DebugMessage("Packet receiver timed out.");
    ResetCurrentPacket();
  }
  while (Serial.available()) {
    temp = Serial.read();

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
        //bad byte
        ResetCurrentPacket();
      }
      if (currentPacketByte >= expectedPacketLength) {
        //Packet Done
        HandlePacket();
        ResetCurrentPacket();
      }
    }
    else {
      if (temp == 0xF0) {
        isReceivingPacket = true;
        currentPacketByte++;
        expectedPacketLength = 4;
      }
    }
    /*DebugMessage(String(currentPacketByte));
      DebugMessage(String(expectedPacketLength));
      DebugMessage(String(temp));
      DebugMessage("Got a byte #%d-%d :%02X", currentPacketByte, expectedPacketLength, temp);*/

  }
  temp = 0;
}
void Communication::SetBoolean(byte id, bool val) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::SetBoolean);
  Serial.write(id);
  Serial.write(reinterpret_cast<byte*>(&val), sizeof(bool));
}
void Communication::SetInteger16(byte id, int val) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::SetInteger16);
  Serial.write(id);
  Serial.write(reinterpret_cast<byte*>(&val), sizeof(int));
}
void Communication::SetInteger32(byte id, long val) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::SetInteger32);
  Serial.write(id);
  Serial.write(reinterpret_cast<byte*>(&val), sizeof(long));
}
void Communication::SetFloat(byte id, double val) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::SetFloat);
  Serial.write(id);
  Serial.write(reinterpret_cast<byte*>(&val), sizeof(double));
}
void Communication::SetString(byte id, String val) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::SetString);
  Serial.write(id);
  int len = val.length();
  Serial.write(len & 0x00FF);
  Serial.write((len & 0xFF00) >> 8);
  for (int i = 0; i < len; i++) {
    Serial.write(val.charAt(i));
  }
}
void Communication::GetBoolean(byte id) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::GetBoolean);
  Serial.write(id);
}
void Communication::GetInteger16(byte id) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::GetInteger16);
  Serial.write(id);
}
void Communication::GetInteger32(byte id) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::GetInteger32);
  Serial.write(id);
}
void Communication::GetFloat(byte id) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::GetFloat);
  Serial.write(id);
}
void Communication::GetString(byte id) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::GetString);
  Serial.write(id);
}
void Communication::DebugMessage(String msg) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::Debug);
  Serial.write(0);
  int len = msg.length();
  Serial.write(len & 0x00FF);
  Serial.write((len & 0xFF00) >> 8);
  for (int i = 0; i < len; i++) {
    Serial.write(msg.charAt(i));
  }
}

void Communication::DebugMessage(const char* format, ...) {

  char* buff = (char*)safeMalloc(256);
  va_list argptr;
  va_start(argptr, format);
  snprintf(buff, 256, format, argptr);
  va_end(argptr);
  DebugMessage(String(buff));
  safeFree(buff);
}

void Communication::OK() {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::OK);
  Serial.write(0);
}

void Communication::Reset() {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::Reset);
  Serial.write(0);
}

void Communication::Refresh() {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::Reset);
  Serial.write(0);
}

void Communication::Forbidden(byte id) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::Forbidden);
  Serial.write(id);
}
void Communication::NotFound(byte id) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::NotFound);
  Serial.write(id);
}
void Communication::TypeMismatch(byte id) {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::TypeMismatch);
  Serial.write(id);
}
void Communication::Unsupported() {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::Unsupported);
  Serial.write(0);
}
void Communication::VersionUnsupported() {
  Serial.write(0xF0);
  Serial.write(PROTOCOL_VERSION);
  Serial.write(Command::VersionUnsupported);
  Serial.write(0);
  Serial.write(PROTOCOL_VERSION);
}

int Communication::BasePacketLength(Command cmd)
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
bool Communication::HasNData(Command _cmd)
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

void Communication::HandlePacket() {
  switch (cmd)
  {
    case Command::OK:
      //nothing
      break;
    case Command::Reset:
      //todo
      break;
    case Command::Refresh:
      //todo resend
      break;
    case Command::Unsupported:
    case Command::Forbidden:
    case Command::NotFound:
    case Command::TypeMismatch:
      //did something bad
      break;
    case Command::DisplayString:
      //todo put string with id on screen
      break;
    case Command::GetBoolean:
      drctr.ProcessBoolean(false, ID);
      break;
    case Command::GetInteger16:
      drctr.ProcessInteger16(false, ID);
      break;
    case Command::GetInteger32:
      drctr.ProcessInteger32(false, ID);
      break;
    case Command::GetFloat:
      drctr.ProcessFloat(false, ID);
      break;
    case Command::GetString:
      //todo respond
      break;
    case Command::VersionUnsupported:
      //Okay we are fucked now.
      break;
    case Command::SetBoolean:
      //Handle value
      drctr.ProcessBoolean(true, ID, reinterpret_cast<bool*>(data));
      break;
    case Command::SetInteger16:
      //Handle value
      drctr.ProcessInteger16(true, ID, reinterpret_cast<int*>(data)); //((data[1]<<8)+data[0]));
      break;
    case Command::SetInteger32:
      //Handle value
      drctr.ProcessInteger32(true, ID, reinterpret_cast<long*>(data)); //((data[3]<<24)+(data[2]<<16)+(data[1]<<8)+data[0]));
      break;
    case Command::SetFloat:
      //Handle value
      drctr.ProcessFloat(true, ID, reinterpret_cast<double*>(data));
      break;
    case Command::SetString:
      //Handle value
      drctr.ProcessString(true, ID, new String(reinterpret_cast<char*>(data)));
      break;
    case Command::Debug:
      //nothing to do with this string
      break;
    default:
      //nothing
      DebugMessage("Got unknown Packet");
      break;
  }

}
void Communication::ResetCurrentPacket() {
  delete data;
  cmd = Command::Unsupported;
  ID = 0;
  datalen = 0;
  isReceivingPacket = false;
  currentPacketByte = 0;
  iterations = 0;
}


