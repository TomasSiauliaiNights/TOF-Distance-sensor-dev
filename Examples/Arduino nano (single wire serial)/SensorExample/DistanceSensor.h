
class DistanceSensor
{
  public:
  DistanceSensor(Stream* stream, uint8_t deviceIndex) : stream(stream), mDeviceIndex(deviceIndex)
  {}

  int writeRead(char* out, char* in, int max)
  {
    stream->print(out);
    int len = stream->readBytesUntil('\n', in, max);
    return len;
  }

  bool readRegister(uint8_t index, uint16_t* result)
  {
    char buffer[11];
    sprintf(buffer, "R%02X%02X\n",mDeviceIndex, index);
    int len = writeRead(buffer, buffer, sizeof(buffer));
    if (len <= 0 || len > 4) return false;
    buffer[len] = 0;
    *result = strtol(buffer, 0, 16);
    return true;
  }

  bool writeRegister(uint8_t index, uint16_t value)
  {
    char buffer[15];
    sprintf(buffer, "W%02X%02X%03X\n",mDeviceIndex, index, value);
    int len = writeRead(buffer, buffer, sizeof(buffer));
    if (len != 1) return false;
    buffer[len] = 0;
    if (strtol(buffer, 0, 16) != 0xA) return false;
    return true;
  }

  bool saveConfiguration()
  {
    char buffer[5];
    sprintf(buffer, "S%02X\n",mDeviceIndex);
    int len = writeRead(buffer, buffer, sizeof(buffer));
    if (len != 1) return false;
    buffer[len] = 0;
    if (strtol(buffer, 0, 16) != 0xA) return false;
    return true;
  }

  bool rsetartSensor()
  {
    char buffer[5];
    sprintf(buffer, "U%02X\n",mDeviceIndex);
    int len = writeRead(buffer, buffer, sizeof(buffer));
    if (len != 1) return false;
    buffer[len] = 0;
    if (strtol(buffer, 0, 16) != 0xA) return false;
    return true;
  }

  bool resetConfiguration()
  {
    char buffer[5];
    sprintf(buffer, "Z%02X\n",mDeviceIndex);
    int len = writeRead(buffer, buffer, sizeof(buffer));
    if (len != 1) return false;
    buffer[len] = 0;
    if (strtol(buffer, 0, 16) != 0xA) return false;
    return true;
  }

  unsigned int readDistance_mm()
  {
    int res = 0;
    bool ok = readRegister(0x01, &res);
    if (!ok) return 0xFFF;
    return res;
  }

  unsigned int readDistance_cm()
  {
    int res = 0;
    bool ok = readRegister(0x06, &res);
    if (!ok) return 0xFF;
    return res;
  }

  bool waitForBoot(int timeout = 500)
  {
    for (int i = timeout; i > 0; i -= 50)
    {
      uint16_t tmp;
      if (readRegister(0x00, &tmp))
      {
        return true;
      }
      delay(50);
    }
    return false;
  }

  uint8_t mDeviceIndex;

  private:
  Stream* stream;
};
