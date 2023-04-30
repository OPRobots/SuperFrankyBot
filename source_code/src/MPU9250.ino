//GND - GND
//VCC - VCC
//SDA - Pin A4
//SCL - Pin A5

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18



Madgwick filter;
unsigned long microsPerReading, microsPrevious;

void MPU9250_init(){
     // Configurar acelerometro
     I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_2_G);
     // Configurar giroscopio
     I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_250_DPS);
     microsPerReading = 5;
}


//Funcion auxiliar lectura
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
   Wire.beginTransmission(Address);
   Wire.write(Register);
   Wire.endTransmission();

   Wire.requestFrom(Address, Nbytes);
   uint8_t index = 0;
   while (Wire.available())
      Data[index++] = Wire.read();
}


// Funcion auxiliar de escritura
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
   Wire.beginTransmission(Address);
   Wire.write(Register);
   Wire.write(Data);
   Wire.endTransmission();
}


void updateIMU()
{
  if (micros() - microsPrevious >= microsPerReading) {
    uint8_t Buf[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

    // Convertir registros acelerometro
    int16_t aix = -(Buf[0] << 8 | Buf[1]);
    int16_t aiy = -(Buf[2] << 8 | Buf[3]);
    int16_t aiz = Buf[4] << 8 | Buf[5];

    // Convertir registros giroscopio
    int16_t gix = -(Buf[8] << 8 | Buf[9]);
    int16_t giy = -(Buf[10] << 8 | Buf[11]);
    int16_t giz = Buf[12] << 8 | Buf[13];

    float ax = convertRawAcceleration(aix);
    float ay = convertRawAcceleration(aiy);
    float az = convertRawAcceleration(aiz);
    float gx = convertRawGyro(gix);
    float gy = convertRawGyro(giy);
    float gz = convertRawGyro(giz);

    filter.updateIMU(gx, gy, gz, ax, ay, az);
    float roll = filter.getRoll();
    float pitch = filter.getPitch();
    float heading = filter.getYaw();
    Serial.print("Orientation: ");
    Serial.print(heading);
    Serial.print(" ");
    Serial.print(pitch);
    Serial.print(" ");
    Serial.println(roll);
    microsPrevious = microsPrevious + microsPerReading;
  }
   // ---  Lectura acelerometro y giroscopio ---
   // uint8_t Buf[14];
   // I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);
   //
   // // Convertir registros acelerometro
   // int16_t ax = -(Buf[0] << 8 | Buf[1]);
   // int16_t ay = -(Buf[2] << 8 | Buf[3]);
   // int16_t az = Buf[4] << 8 | Buf[5];
   //
   // // Convertir registros giroscopio
   // int16_t gx = -(Buf[8] << 8 | Buf[9]);
   // int16_t gy = -(Buf[10] << 8 | Buf[11]);
   // int16_t gz = Buf[12] << 8 | Buf[13];


   // --- Mostrar valores ---

   // Acelerometro
   // Serial.print(ax, DEC);
   // Serial.print("\t");
   // Serial.print(ay, DEC);
   // Serial.print("\t");
   // Serial.print(az, DEC);
   // Serial.print("\t");
   //
   // // Giroscopio
   // Serial.print(gx, DEC);
   // Serial.print("\t");
   // Serial.print(gy, DEC);
   // Serial.print("\t");
   // Serial.print(gz, DEC);
   // Serial.print("\t");

   // Fin medicion
   // Serial.println("");
}

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767

  float a = (aRaw * 2.0) / 32768.0;
  return a;
}

float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767

  float g = (gRaw * 250.0) / 32768.0;
  return g;
}
