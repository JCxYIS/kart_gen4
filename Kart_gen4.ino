//#include <Servo.h>
//#include <Ultrasonic.h>
#include <SoftwareSerial.h>

#define L1 2
#define L2 3
#define R1 4
#define R2 5
#define B1 6
#define B2 7
SoftwareSerial BT(12, 13); // RX | TX 
char driveMode = 's';

void setup() 
{
  Serial.begin(9600);

  BT.begin(9600);// 設定藍牙模組的連線速率
  Serial.println("BT(Bluetooth) is ready! type AT+VERSION to set func!");
  
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
}
void loop() 
{
   BluetoothHandler();
   MotorHandler();
}

void MotorHandler()
{
    if(driveMode == 'f')
      DriveForward();
    else if(driveMode == 'b')
      DriveBackward();
    else if(driveMode == 'l')
      DriveLeftward();
    else if(driveMode == 'r')
      DriveRightward();
    else if(driveMode == 'c')
      Serial.flush();
    else if(driveMode == 's')
      DriveStop();
}
//這裡處理藍芽事宜
void BluetoothHandler()
{
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) 
  {
    char val = Serial.read();
    BT.print(val);
    Serial.print(val);
  }
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」，並加入command。注意結尾一定要是'\n'
  if (BT.available())
  {
    int inSize = BT.available();
    for (int i = 0; i < inSize; i++)
    {
        char tmp = BT.read();
        //command[commandBuffer] = tmp;
        if(tmp == '\n')//this command is done
        {
          
        }
        else
        {
          driveMode = tmp;
        }
        
        Serial.print(tmp);
    }
  }
}




void DriveBackward(){
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  Serial.println("Drive Backward");
}
void DriveForward(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  Serial.println("Drive Forward");
}
void DriveRightward(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  Serial.println("Drive Rightward");
}
void DriveLeftward(){
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  Serial.println("Drive Leftward");
}
void DriveStop(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  Serial.println("Drive Stop");
}
