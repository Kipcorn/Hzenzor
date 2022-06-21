#include <Mapf.h>

#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Empty.h>


const int xstepPin = 2;    // X.STEP
const int xdirPin = 5;     // X.DIR
const int ystepPin = 3;    // Y.STEP
const int ydirPin = 6;     // Y.DIR
const int lockrange = 5;  // range in degrees on when stepper is allowed to turn

float sensorValue;        // value from potentiometer 0 - 1023 
float positionValue;      // Converted value potentiometer

int motorstep;            // counter for amount of steps needed for a degree
int lock;                 // signal to check if position is locked
int desiredPos;           // desired position
int currentPos;           // current position
int distance;             // distance between desiredPos and currentPos

ros::NodeHandle nh;

void messageCb( const std_msgs::Float32& toggle_msg){
  positionValue = toggle_msg.data;
}

std_msgs::Float32 str_msg;

ros::Subscriber<std_msgs::Float32> sub("/vel", &messageCb );
ros::Publisher chatter("chatter", &str_msg);

void setup()
{
    nh.getHardware()->setBaud(9600);
    nh.initNode();
    nh.advertise(chatter);
    nh.subscribe(sub);
    
//    pinMode(A4, INPUT);
    pinMode(xstepPin, OUTPUT);
    pinMode(xdirPin, OUTPUT);
    pinMode(ystepPin, OUTPUT);
    pinMode(ydirPin, OUTPUT);
//    Serial.begin(9600);
    
    //TODO make func that sets motor to start position with switch
    setMotorStart();
    lock = 0;
}

void loop()
{
    
    //get corect input value from potmeter (-1 to 1)
//    positionValue = readInput();
    //transform recieved value to degrees (-180 to 180)
    desiredPos = transformToDegrees(positionValue);

    //calculate amount of degrees the motor needs to turn
    distance = calcdistance(currentPos, desiredPos);
    //turn motor amount of degrees
    currentPos = turnMotor(currentPos, desiredPos, distance);

    str_msg.data = desiredPos;
    chatter.publish( &str_msg );
    nh.spinOnce();
    delay(1);
}


/*
 * Read input from analog port A4
 * ----------------------------------------
 * return mapf
 */
float readInput()
{
  sensorValue = analogRead(A4);
  return (mapf(sensorValue, 0, 1023, -1, 1));   
}


/* Transform input from float value 1 to -1 to degrees)
 * -------------------------------------------------------
 * PosValue = float from potmeter
 * return Posvalue multiplied by 180
 */
float transformToDegrees(float PosValue)
{
  return PosValue * 180;
}

int calcdistance(int currentPos, int desiredPos)
{
    int turn;
        
    // NEGATIVE
    if (currentPos > desiredPos)
    {
        turn = -(currentPos - desiredPos);
    }
    // {POSITIVE
    if (currentPos < desiredPos)
    {
        turn = (desiredPos - currentPos);
    }
    // NEUTRAL
    if (currentPos == desiredPos)
    {
        turn = 0;
    }
    
    return turn;
}


int turnMotor(int currentPos, int desiredPos, int distance)
{
     
    if (distance == 0 && lock != 1)
    {
        lock = 1;
    }

    if (distance < 0)
    {
        if (distance < -lockrange || lock == 0)
        {
            turnMotorRight();
            Serial.println("RIGHT");
            lock = 0;
        }
        
        if (lock == 0)
        {
            currentPos--;
        }
    }

    if (distance > 0)
    {
        if (distance > lockrange || lock == 0)
        {

            turnMotorLeft();
            Serial.println("LEFT");
            lock = 0;
        }
        
        if (lock == 0)
        {
            currentPos++;
        }
    }
    return currentPos;
}

void turnMotorRight()
{
  digitalWrite(xdirPin, HIGH);
  digitalWrite(ydirPin, HIGH);
  delaymotor();
}

void turnMotorLeft()
{
  digitalWrite(xdirPin, LOW);
  digitalWrite(ydirPin, LOW);
  delaymotor();
}

void delaymotor()
{
    for (motorstep = 0; motorstep < (29 * 2); motorstep++)
    {
        digitalWrite(xstepPin, HIGH);
        digitalWrite(ystepPin, HIGH);
        delayMicroseconds(700);
        digitalWrite(xstepPin, LOW);
        digitalWrite(ystepPin, LOW);
        delayMicroseconds(700);
    }
    return;
}

void setMotorStart()
{
    currentPos = 0;
    return;
}