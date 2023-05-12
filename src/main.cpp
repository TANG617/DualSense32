#include "DS32.h"

int pwmPinForward1 = 26;
int pwmPinForward2 = 27;
int pwmPinForward3 = 16;
int pwmPinForward4 = 17;

int pwmPinRear1 = 32;
int pwmPinRear2 = 33;
int pwmPinRear3 = 13;
int pwmPinRear4 = 15;

// #define DEBUG

void setup()
{
    pinMode(pwmPinForward1, OUTPUT);
    pinMode(pwmPinForward2, OUTPUT);
    pinMode(pwmPinForward3, OUTPUT);
    pinMode(pwmPinForward4, OUTPUT);

    pinMode(pwmPinRear1, OUTPUT);
    pinMode(pwmPinRear2, OUTPUT);
    pinMode(pwmPinRear3, OUTPUT);
    pinMode(pwmPinRear4, OUTPUT);


    Serial.begin( 115200 ); /* prepare for possible serial debug 为可能的串行调试做准备*/
    // Screen_LVGL_UI_init();
    ps5.begin("bc:c7:46:33:11:d2");

    #ifdef DEBUG
    analogWrite(pwmPinForward1, 100);
    delay(1000);
    analogWrite(pwmPinForward1, 0);
    delay(1000);
    analogWrite(pwmPinRear1, 100);
    delay(1000);
    analogWrite(pwmPinRear1, 0);
    delay(1000);
    analogWrite(pwmPinForward2, 100);
    delay(1000);
    analogWrite(pwmPinForward2, 0);
    delay(1000);
    analogWrite(pwmPinRear2, 100);
    delay(1000);
    analogWrite(pwmPinRear2, 0);
    delay(1000);
    analogWrite(pwmPinForward3, 100);
    delay(1000);
    analogWrite(pwmPinForward3, 0);
    delay(1000);
    analogWrite(pwmPinRear3, 100);
    delay(1000);
    analogWrite(pwmPinRear3, 0);
    delay(1000);
    analogWrite(pwmPinForward4, 100);
    delay(1000);
    analogWrite(pwmPinForward4, 0);
    delay(1000);
    analogWrite(pwmPinRear4, 100);
    delay(1000);
    analogWrite(pwmPinRear4, 0);
    delay(1000);
    #endif


    analogWrite(pwmPinForward1, 0);
    analogWrite(pwmPinForward2, 0);
    analogWrite(pwmPinForward3, 0);
    analogWrite(pwmPinForward4, 0);

    analogWrite(pwmPinRear1, 0);
    analogWrite(pwmPinRear2, 0);
    analogWrite(pwmPinRear3, 0);
    analogWrite(pwmPinRear4, 0);
    
}

double LF=0,LB=0,RF=0,RB=0;

void Move(int DirectionX, int RotateSpeed , int Speed, int DirectionY, int Flip, int SpeedDirection)
{
    //int MoveSpeed(-127-128), int DirectionX(-127-128), int DirectionY(-127-128), int RotateSpeed(-255-255)
    double FinalSpeed = max(sqrt(pow(DirectionX*2,2)+pow(DirectionY*2,2)),(double)Speed)*SpeedDirection;
    LF=0;
    LB=0;
    RF=0;
    RB=0;
    
    LF += DirectionY;
    LB += DirectionY;
    RF += DirectionY;
    RB += DirectionY;

    LF -= DirectionX;
    LB += DirectionX;
    RF += DirectionX;
    RB -= DirectionX;

    LF -= RotateSpeed;
    LB -= RotateSpeed;
    RF += RotateSpeed;
    RB += RotateSpeed;

    LF*=Flip;
    RF*=Flip;
    LB*=Flip;
    RB*=Flip;
    Norm();
    Control((int)FinalSpeed);
}

void Norm()
{
    double MAX = max(max(abs(LF),abs(LB)),max(abs(RF),abs(RB)));
    if (MAX <= 8)
    {
        LF = 0;
        LB = 0;
        RF = 0;
        RB = 0;
        return ;
    }
    LF /= MAX;
    LB /= MAX;
    RF /= MAX;
    RB /= MAX;
}

void WheelControl(int Forward, int Rear, int Data)
{
    #ifdef DEBUG
    Serial.printf("%d,",Data);
    #endif
    if(Data > 0)
    {
        analogWrite(Forward, abs(Data));
        analogWrite(Rear, 0);
    } 
    else
    {
        analogWrite(Rear, abs(Data));
        analogWrite(Forward, 0);
    }
}

void Control(int Speed) //Speed:0-255
{
        WheelControl(pwmPinForward1, pwmPinRear1,(int)(LF*Speed) );//L F
        WheelControl(pwmPinForward2, pwmPinRear2,(int)(LB*Speed) );//L B
        WheelControl(pwmPinForward3, pwmPinRear3,(int)(RF*Speed) );//R F
        WheelControl(pwmPinForward4, pwmPinRear4,(int)(RB*Speed) );//R B
        #ifdef DEBUG
        Serial.printf("\n");
        #endif
        // LF*Speed > 0 ? analogWrite(pwmPinForward1, (int)Speed*LF):analogWrite(pwmPinRear1, (int)abs(Speed*LF));//L F
        // LB*Speed > 0 ? analogWrite(pwmPinForward2, (int)Speed*LB):analogWrite(pwmPinRear2, (int)abs(Speed*LB));//L B
        // RF*Speed > 0 ? analogWrite(pwmPinForward3, (int)Speed*RF):analogWrite(pwmPinRear3, (int)abs(Speed*RF));//R F
        // RB*Speed > 0 ? analogWrite(pwmPinForward4, (int)Speed*RB):analogWrite(pwmPinRear4, (int)abs(Speed*RB));//R B

}

void PS5_Control()
{
    int Speed,SpeedDirection;
    Speed  = abs(ps5.L2Value()-ps5.R2Value());
    SpeedDirection = ps5.L2Value()-ps5.R2Value() > 0 ? -1 : 1;   
    Move(ps5.LStickX(),ps5.LStickY(),Speed,ps5.RStickX(),1,SpeedDirection);
    #ifdef DEBUG
    Serial.printf("%f,%f,%f,%f,Speed:%d,Dire:%d\n",LF,LB,RF,RB,Speed,SpeedDirection);
    #endif
}

void loop()
{
    
    
    // lv_timer_handler(); /* let the GUI do its work 让 GUI 完成它的工作 */
    if(ps5.isConnected()) Serial.println("Connected!");
    while (ps5.isConnected()) {
        PS5_Control();

    }
}
