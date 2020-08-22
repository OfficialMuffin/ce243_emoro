// LCD Menu items
char obstacle[16] = "1.Obst";
char circle[16] = "2.Circle";
char squ[16] = "3.Square";
char reset[16] = "4.Reset";

unsigned char ReadSwitch(unsigned char sw);

// Declare variables
int servoPort[2] = {SERVO_0, SERVO_1};
int waitState = 1000;
int lServ = 2000;
int rServ = 1000;
int sensorPin = GPP_0;
int cm;
static int active = -1; // Check button pressed constant

// Values for moving bot back or forward
static int Lbck = 2500;
static int Rbck = 1000;
static int Lfwd = 1000;
static int Rfwd = 2000;


void setup() {

  // Initialise serial, servos, servos and IR sensors
  Serial.begin(9600);
  EmoroServo.attach(servoPort[0]);
  EmoroServo.attach(servoPort[1]);
  Ultrasonic.attach(sensorPin);

  pinMode(IO_0, INPUT_PULLUP);
  pinMode(IO_1, INPUT_PULLUP);

  // Call mainMenu function to print the main menu
  mainMenu();
}

void loop() {
  // Read sensor pin distance in CM
  cm = Ultrasonic.read(sensorPin);
  if (ReadEmoroHardware() & SW_AVAILABLE) {
    // Check if switches are pressed, if pressed, set active to x
    if (ReadSwitch(SW_1) == 1)
    {
      active = 1;
    }
    else if (ReadSwitch(SW_2) == 1)
    {
      active = 2;
    }
    else if (ReadSwitch(SW_3) == 1)
    {
      active = 3;
    }
    else if (ReadSwitch(SW_4) == 1)
    {
      active = 4;
    }
  }

  if (active == 1) {
    Serial.println("Obst");
    Lcd.clear();
    Lcd.locate(0, 0);
    Lcd.print("Moving...");
    moveBot();

    // Debug
    Serial.print("Servo pulse width: ");
    Serial.print(EmoroServo.read(servoPort[0]));
    Serial.print(" us\n");
    Serial.print("Servo pulse width: ");
    Serial.print(EmoroServo.read(servoPort[1]));
    Serial.print(" us\n");
    Serial.println("Moving...");

    // Calls the objDetected function that stops bot
    // Then moves away from the object
    objDetected();
  }
  else if (active == 2) {
    Serial.println("Switch SW_2 is activated");
    Lcd.clear();
    Lcd.locate(0, 0);
    Lcd.print("Circle Track");
	Lcd.locate(1, 0);
	Lcd.print("Following");

    doCircle();
  }
  else if (active == 3) {
    Serial.println("Switch SW_3 is activated");
    Lcd.clear();
    Lcd.locate(0, 0);
    Lcd.print("Square Track");
	Lcd.locate(1, 0);
	Lcd.print("Following");

    doSquare();
  }
  else if (active == 4) {
    Serial.println("Robot Reset");
    stopBot();
    Lcd.locate(0, 0);
    Lcd.print("Resetting...");
    Lcd.clear();
    active = -1;

    mainMenu();
  }
}

/*********************
 *  EMORO FUNCTIONS  *
 *********************/

// Function to enable return to main menu
void mainMenu()
{
  if (ReadEmoroHardware() & LCD_AVAILABLE) {  // if LCD and switch avaliable
    Serial.println("LCD Ready");
    Lcd.locate(0, 0);
    Lcd.print(obstacle);
    Lcd.locate(0, 8);
    Lcd.print(circle);
    Lcd.locate(1, 0);
    Lcd.print(squ);
    Lcd.locate(1, 9);
    Lcd.print(reset);
  } else {
    Serial.println("LCD Not Ready");
  }
}

// Function to stop the bot
void stopBot()
{
  // Set servo pulse to 1500us. For position servo motors this will set the middle position,
  // for servo motors with continuous rotation this will stop rotation
  EmoroServo.write(servoPort[0], 1500);
  EmoroServo.write(servoPort[1], 1500);
}

// Function to move bot
void moveBot()
{
  // Set servo pulse to 1000us. For position servo motors this will set the left position,
  // for servo motors with continuous rotation this will set continuous rotation in CCW direction
  EmoroServo.write(servoPort[0], lServ);
  EmoroServo.write(servoPort[1], rServ);
}

// Function to detect obstacles
void objDetected()
{
  cm = Ultrasonic.read(sensorPin);
  // Stop robot if less than 25cm
  if (cm <= 25)
  {
    Serial.println("Object Detected!");
    Lcd.clear();
    Lcd.locate(2, 0);
    Lcd.print("Object Detected!");

    // Calls stopBot function to stop bot if less than 25cm
    stopBot();
    delay(85);
    // Moves the bot back
    EmoroServo.write(servoPort[0], 500);
    EmoroServo.write(servoPort[1], 2500);
    delay(200);
    // Turns bot
    EmoroServo.write(servoPort[0], 500);
    EmoroServo.write(servoPort[1], 500);
    delay(250);
    // Moves forward and away form the object
    EmoroServo.write(servoPort[0], lServ);
    EmoroServo.write(servoPort[1], rServ);
    //delay(100);
  }
}

// Function for following circle
void doCircle()
{
  // If Both sensors detect white, go forward.
  if (digitalRead(IO_0) == 1 && digitalRead(IO_1) == 1) {
    EmoroServo.write(servoPort[0], Lfwd);
    EmoroServo.write(servoPort[1], Rfwd);
    Lcd.locate(0, 0);
    Serial.print("White");
    Lcd.print("White");
    Lcd.locate(1, 0);
    Lcd.print(digitalRead(IO_0));
    Lcd.locate(1, 2);
    Lcd.print(digitalRead(IO_1));
  }
  // Only left sensor is on the black, turn right.
  else if (digitalRead(IO_0) == 1) {
    EmoroServo.write(SERVO_0, Lbck);
    EmoroServo.write(SERVO_1, Rfwd);
    Lcd.locate(0, 0);
    Lcd.print("Left Sensor");
    Lcd.locate(1, 0);
    Lcd.print(digitalRead(IO_0));
    Lcd.locate(1, 2);
    Lcd.print(digitalRead(IO_1));
    delay(10);   
  }
  // Only right sensor is on the black, turn left.
  else if (digitalRead(IO_1) == 1) {
    EmoroServo.write(SERVO_0, Lfwd);
    EmoroServo.write(SERVO_1, Rbck);
    Lcd.locate(0, 0);
    Lcd.print("Right Sensor");
    Lcd.locate(1, 0);
    Lcd.print(digitalRead(IO_0));
    Lcd.locate(1, 2);
    Lcd.print(digitalRead(IO_1));
    delay(10);   
  }
}
// Function for following square
void doSquare()
{
    // If Both sensors detect white, go forward.
  if (digitalRead(IO_0) == 1 && digitalRead(IO_1) == 1) {
    EmoroServo.write(servoPort[0], Lfwd);
    EmoroServo.write(servoPort[1], Rfwd);
    Lcd.locate(0, 0);
    Serial.print("White");
    Lcd.print("White");
    Lcd.locate(1, 0);
    Lcd.print(digitalRead(IO_0));
    Lcd.locate(1, 2);
    Lcd.print(digitalRead(IO_1));
  }
  // Only left sensor is on the black, turn 90 deg right.
  else if (digitalRead(IO_0) == 1) {
    EmoroServo.write(SERVO_0, Lbck);
    EmoroServo.write(SERVO_1, Rfwd);
    delay(500);
    Lcd.locate(0, 0);
    Lcd.print("Left Sensor");
    Lcd.locate(1, 0);
    Lcd.print(digitalRead(IO_0));
    Lcd.locate(1, 2);
    Lcd.print(digitalRead(IO_1));
  }
  // Only right sensor is on the black, turn 90 deg left.
  else if (digitalRead(IO_1) == 1) {
    EmoroServo.write(SERVO_0, Lfwd);
    EmoroServo.write(SERVO_1, Rbck);
    delay(500);
    Lcd.locate(0, 0);
    Lcd.print("Right Sensor");
    Lcd.locate(1, 0);
    Lcd.print(digitalRead(IO_0));
    Lcd.locate(1, 2);
    Lcd.print(digitalRead(IO_1));
  }
}
