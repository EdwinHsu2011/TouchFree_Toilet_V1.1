#include <DFRobot_MGC3130.h>
#include <Servo.h>

const uint8_t DPin = A1;
const uint8_t MCLRPin = A0;
DFRobot_MGC3130 myGesture(DPin, MCLRPin);

const uint8_t ServoPIN_Poo = 5;
const uint8_t ServoPIN_Pee = 6;
const uint8_t ServoNomalPos_Pee = 10;
const uint8_t ServoPushPos_Pee = 90;
const uint8_t ServoNomalPos_Poo = 90;
const uint8_t ServoPushPos_Poo = 10;

Servo Servo_Poo; // create servo object to control a servo
Servo Servo_Pee; // create servo object to control a servo

const uint8_t LedRed_SystemOn = 9;
const uint8_t LedGreen_Pee = 7;
const uint8_t LedBlue_Poo = 8;

const uint16_t FlushTime_Poo = 1000;
const uint16_t FlushTime_Pee = 1000;
uint8_t PreviousAirWheelInfo = 0;
uint8_t CurrentAirWheelInfo = 0;

void setup()
{

    // initialize GPIO.
    pinMode(LedBlue_Poo, OUTPUT);
    pinMode(LedGreen_Pee, OUTPUT);
    pinMode(LedRed_SystemOn, OUTPUT);

    Servo_Poo.attach(ServoPIN_Poo);
    Servo_Pee.attach(ServoPIN_Pee);

    Serial.begin(115200);

    Servo_Poo.write(ServoNomalPos_Poo);
    Servo_Pee.write(ServoNomalPos_Pee);

    //Start the system self-test.
    while (!myGesture.begin())
    {
        Serial.println("System error! Please check whether the connection is correct");
        LED_Test();
    };
    Serial.println("Gesture begin success!!!");
    LED_Test();
    while (myGesture.enableAirWheel() != 0){delay(100);}
    while (myGesture.enableGestures() != 0){delay(100);}
    Serial.println("System self-test & Config completed !!!");
    // System Test Completed
    digitalWrite(LedRed_SystemOn, HIGH); // turn the LED on (HIGH is the voltage level)
}

void loop()
{
    myGesture.sensorDataRecv();
    switch (myGesture.getGestureInfo())
    {
    case myGesture.eFilckR:
        Serial.println("Flick Left to Right");
        Get_Pee();
        break;
    case myGesture.eFilckL:
        Serial.println("Flick Right to Left");
        Get_Pee();
        break;
    case myGesture.eFilckU:
        Serial.println("Flick Down to Up");
        Get_Pee();
        break;
    case myGesture.eFilckD:
        Serial.println("Flick Up to Down");
        Get_Pee();
        break;
    case myGesture.eCircleClockwise:
        Serial.println("Circle clockwise");
        // Get_Poo();
        break;
    case myGesture.eCircleCounterclockwise:
        Serial.println("Circle counterclockwise");
        // Get_Poo();
        break;
    default:
        CurrentAirWheelInfo = myGesture.getAirWheelInfo();
        if ((PreviousAirWheelInfo == 0) && (CurrentAirWheelInfo > 0))
        {
            Serial.println("AirWheel");
            Get_Poo();
        }
        PreviousAirWheelInfo = CurrentAirWheelInfo;
        break;
    }
}
void Get_Poo()
{
    digitalWrite(LedBlue_Poo, HIGH); // turn the LED on (HIGH is the voltage level)
    Servo_Poo.write(ServoPushPos_Poo);
    delay(FlushTime_Poo);
    digitalWrite(LedBlue_Poo, LOW); // turn the LED off by making the voltage LOW
    Servo_Poo.write(ServoNomalPos_Poo);
    delay(FlushTime_Poo);
}
void Get_Pee()
{
    digitalWrite(LedGreen_Pee, HIGH); // turn the LED on (HIGH is the voltage level)
    Servo_Pee.write(ServoPushPos_Pee);
    delay(FlushTime_Pee);
    digitalWrite(LedGreen_Pee, LOW); // turn the LED off by making the voltage LOW
    Servo_Pee.write(ServoNomalPos_Pee);
    delay(FlushTime_Pee);
}
void LED_Test()
{
    digitalWrite(LedRed_SystemOn, HIGH);
    digitalWrite(LedBlue_Poo, HIGH);
    digitalWrite(LedGreen_Pee, HIGH);
    delay(500);
    digitalWrite(LedRed_SystemOn, LOW);
    digitalWrite(LedBlue_Poo, LOW);
    digitalWrite(LedGreen_Pee, LOW);
    delay(500);
}
