/*
 * Author: Robert Cudmore
 * http://robertcudmore.org
 * 20160214
 *
 * Purpose: Run a trial based experiment
 *   
 *    
 *
 */

#include "Arduino.h"
//#include "main.h"

#include <AccelStepper.h> // http://www.airspayce.com/mikem/arduino/AccelStepper/index.html
#include <Encoder.h> // http://www.pjrc.com/teensy/td_libs_Encoder.html

struct trial
{
	boolean trialIsRunning;
	int trialNumber;
	unsigned long trialStartMillis;
	int dur; //ms
	int useMotor;
	int motorDelay; //ms
	int motorDur; //ms
};

struct steppermotor
{
   boolean useMotor;
   boolean isRunning;
   int speed;
   int maxSpeed;
   int stepPin;
   int dirPin;
   int resetPin;
};

struct rotaryencoder
{
	int pinA; // use pin 2
	int pinB; // use pin 3
};

struct simulatescanimage
{
	int isOn;
	int frameInterval; //millis
	int numFrames;
	int currentFrame;
	unsigned long lastFrameMillis;
};

typedef struct trial Trial;
typedef struct steppermotor StepperMotor;
typedef struct rotaryencoder RotaryEncoder;
typedef struct simulatescanimage SimulateScanImage;

Trial trial;
StepperMotor motor;
RotaryEncoder rotaryencoder;
SimulateScanImage si;

AccelStepper stepper(AccelStepper::DRIVER,motor.stepPin,motor.dirPin);
Encoder myEncoder(rotaryencoder.pinA, rotaryencoder.pinB);

// used in xxx callbacks
volatile int goReceived = 0;    //A0
volatile int stopReceived = 0;  //A1
volatile int siIsUp = 0;      //A2
volatile int gotFrame = 0;      //A2

/////////////////////////////////////////////////////////////
//callback for frame clock pin using xxx
void InitializeIO() {
  pinMode(A0, INPUT);
  digitalWrite(A0, LOW);
  pinMode(A1, INPUT);
  digitalWrite(A1, LOW);
  pinMode(A2, INPUT);
  digitalWrite(A2, LOW);
}
/////////////////////////////////////////////////////////////
void InitializeInterrupt() {
  cli();
  PCICR =0x02;
  PCMSK1 = 0b00000111;
  sei();
}
/////////////////////////////////////////////////////////////
ISR(PCINT1_vect) {
  if (digitalRead(A0)==1) goReceived=1; 
  if (digitalRead(A1)==1) stopReceived=1; 
  if (digitalRead(A2)==1) siIsUp=1; else gotFrame=1;
}
/////////////////////////////////////////////////////////////
void setup()
{
  //
  //trial
  trial.trialIsRunning = false;
  trial.trialNumber = 0;
  trial.trialStartMillis = 0;
  trial.dur = 5000;
  trial.useMotor = 1;
  trial.motorDelay = 2000;
  trial.motorDur = 1000;
  //
  //motor
  motor.useMotor = true;
  motor.isRunning = false;
  //motor.speed = xxx;
  //motor.maxSpeed = xxx;
  //motor.stepPin = xxx;
  //motor.dirPin = xxx;
  //motor.resetPin = xxx;
  //
  //rotary encoder
  //encoder.pinA = xxx;
  //encoder.pinB = xxx;
  //
  //simulate scan image
  si.isOn = 1;
  si.frameInterval = 400; //millis
  si.numFrames = 10;
  si.currentFrame = 0;
  si.lastFrameMillis = 0;
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  
}

/////////////////////////////////////////////////////////////
void serialOut(long now, String str, long val) {
	Serial.println(String(now) + "," + str + "," + val);
}
/////////////////////////////////////////////////////////////
void scanImageStart_(long now) {
	if (si.isOn) {
		si.currentFrame = 0;
		si.lastFrameMillis = millis();
		serialOut(now, "scanimagestart", si.currentFrame);
	}
}
/////////////////////////////////////////////////////////////
void scanImageFrame_(long now) {
	if (trial.trialIsRunning && si.isOn) {
		if (now > (si.lastFrameMillis + si.frameInterval)) {
			serialOut(now, "scanimageframe", si.currentFrame);
			si.lastFrameMillis = millis();
			si.currentFrame += 1;
		}
	}
}
/////////////////////////////////////////////////////////////
void scanImageStop_() {

}
/////////////////////////////////////////////////////////////
void startTrial(long now) {
	if (trial.trialIsRunning==0) {
		trial.trialStartMillis = now;
		trial.trialNumber += 1;

		serialOut(now, "startTrial", trial.trialNumber);

		trial.trialIsRunning = 1;
		
		scanImageStart_(now);
		
	}
}
/////////////////////////////////////////////////////////////
void stopTrial(long now) {
	if (trial.trialIsRunning==1) {
		trial.trialIsRunning = 0;
		serialOut(now, "stopTrial", trial.trialNumber);
	}
}
/////////////////////////////////////////////////////////////
void GetState() {
	//trial
	Serial.println("trial.trialNumber=" + String(trial.trialNumber));
	Serial.println("trial.dur=" + String(trial.dur));
	Serial.println("trial.useMotor=" + String(trial.useMotor));
	Serial.println("trial.motorDelay=" + String(trial.motorDelay));
	Serial.println("trial.motorDur=" + String(trial.motorDur));
	//motor
	Serial.println("motor.speed=" + String(motor.speed));
	Serial.println("motor.maxSpeed=" + String(motor.maxSpeed));
	//scanimage
	Serial.println("si.isOn=" + String(si.isOn));
	Serial.println("si.frameInterval=" + String(si.frameInterval));
	Serial.println("si.numFrames=" + String(si.numFrames));
}
/////////////////////////////////////////////////////////////
void SetValue(String name, String strValue) {
	int value = strValue.toInt();
	//trial
	if (name == "trial.dur") {
		trial.dur = value;
	} else if (name=="trial.useMotor") {
		trial.useMotor = value;
	} else if (name=="trial.motorDelay") {
		trial.motorDelay = value;
	} else if (name=="trial.motorDur") {
		trial.motorDur = value;
	//scanimage
	} else if (name == "si.isOn") {
		si.isOn = value;
	} else if (name == "si.frameInterval") {
		si.frameInterval = value;
	} else if (name == "si.numFrames") {
		si.numFrames = value;
	//error
	} else {
		Serial.println("SetValue() did not handle '" + name + "'");
	}
	
}
/////////////////////////////////////////////////////////////
//respond to incoming serial
void SerialIn(long now, String str) {
	String delimStr = ",";
	
	if (str.length()==0) {
		return;
	}
	if (str == "startTrial") {
		startTrial(now);
	}
	else if (str == "stopTrial") {
		stopTrial(now);
	}
	else if (str.startsWith("getState")) {
		GetState();
	}
	else if (str.startsWith("set")) {
		//set is {set,name,value}
		int firstComma = str.indexOf(delimStr,0);
		int secondComma = str.indexOf(delimStr,firstComma+1);
		String nameStr = str.substring(firstComma+1,secondComma); //first is inclusive, second is exclusive
		String valueStr = str.substring(secondComma+1,str.length());
		SetValue(nameStr, valueStr);
	}
	else {
		Serial.println("SerialIn() did not handle:" + str);
	}
		
}

/////////////////////////////////////////////////////////////
void updateMotor(long now) {
	//maybe add a global 'useMotor' state variable
	if (trial.trialIsRunning) {
		long motorStart = trial.trialStartMillis + trial.motorDelay;
		long motorStop = motorStart + trial.motorDur;
		if (!motor.isRunning && now >= motorStart && now < motorStop) {
			motor.isRunning = true;
			serialOut(now, "motorstart", 1);
		} else if (motor.isRunning && now > motorStop) {
			motor.isRunning = false;
			serialOut(now, "motorstop", 1);
		}
	}
}
/////////////////////////////////////////////////////////////
void loop()
{
  //digitalWrite(LED_BUILTIN, HIGH); //so we can see if the code is running

	long now = millis();
	
	if (Serial.available() > 0) {
		String inString = Serial.readStringUntil('\n');
		SerialIn(now, inString);
	}

	//for now just simulate some data
	int a1_value = random(255);
	int a2_value = random(255);

	if (now > (trial.trialStartMillis + trial.dur)) {
		stopTrial(now);
	}
	
	if (trial.trialIsRunning==1) {
  		//Serial.println(String(millis()) + "," + "analogEvent" + "," + String (a1_value) + "," + String (a2_value)); 
	}
  
	scanImageFrame_(now);
  
  	updateMotor(now);
  	
	delay(50); //ms

	//digitalWrite(LED_BUILTIN, LOW); //so we can see if the code is running
}
