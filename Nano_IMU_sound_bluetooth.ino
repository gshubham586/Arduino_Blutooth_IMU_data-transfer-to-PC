
#include<SoftwareSerial.h>
#include <Wire.h>
#include <MPU9250.h>
#define TxD 2
#define RxD 3
SoftwareSerial blue(TxD, RxD);

MPU9250 IMU(Wire,0x68);                          // Register address for I2C communication
int status;

int i=1;
String datasensor; 
int soundVal=0;     





void setup() {
  
  Serial.begin(9600);    //Now 8-9 data per second,   Change Baudrate to receive data at different speed
  blue.begin(9600);
  //pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(A6,INPUT);                     
 
  
 while(!Serial) {}

   
  status = IMU.begin();                                             // Starting communication with IMU (MPU9250)
  if (status < 0) {                                                 // If communication with MPU9250 is not established then inform the user
    
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);                        // setting the accelerometer full scale range to +/-8G 
 
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);                      // setting the gyroscope full scale range to +/-500 deg/s
  
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_92HZ);                // setting DLPF bandwidth to 92 Hz
  
  IMU.setSrd(4);                                                     // Here sampling frequency should be Double or more than Double of the DLPF Bandwidth to get accurate data and formula 
                                                                     // for sampling frequency is SF=1000/(SRD+1). So choose srd according to above DLPF Bandwidth.

}

char dataPublish[150];
void publishblue(String data){
   data.toCharArray(dataPublish, data.length() + 1);
   blue.print(dataPublish);
   blue.print('\n');
}



void loop() {
  
   

 IMU.readSensor();                              //Reading Data From MPU9250 Sensor
float  GyroX = IMU.getGyroX_rads();             // Reading X-axis data of gyrometer.
float  GyroY = IMU.getGyroY_rads();             // Reading Y-axis data of gyrometer.
float  GyroZ = IMU.getGyroZ_rads();             // Reading Z-axis data of gyrometer.
float  AccX = IMU.getAccelX_mss();              // Reading X-axis data of Accelerometer.
float  AccY = IMU.getAccelY_mss();              // Reading Y-axis data of Accelerometer.
float  AccZ = IMU.getAccelZ_mss();              // Reading Z-axis data of Accelerometer.
float  MagX = IMU.getMagX_uT();                 // Reading X-axis data of Magnetometer.
float  MagY = IMU.getMagY_uT();                 // Reading Y-axis data of Magnetometer.
float  MagZ = IMU.getMagZ_uT();                 // Reading Z-axis data of Magnetometer.
float Temp = IMU.getTemperature_C();            // Reading Temperature in Degree Celsius.


soundVal=analogRead(A6); 

// Data to send through nodemcu using mqtt protocol..
// Here string(var,6) is used because it gives the value of  "var" upto 6 place after decimal.
  datasensor = String(AccX,6)+"  "+String(AccY,6)+"  "+String(AccZ,6)+"  "+String(GyroX,6)+"  "+String(GyroY,6)+"  "+String(GyroZ,6)+"  "+String(MagX,6)+"  "+String(MagY,6)+"  "+String(MagZ,6)+" "+String(Temp)+" "+String(soundVal);
  
        // Publishing Data through MQTT   
          
  // Printing the Data on Serial Monitor.

 publishblue(datasensor);
  Serial.println(datasensor);

  
}
