// these "include" lines import other software functions for driving the motors and display
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// these "define" lines are used to make the code more readable and give meaning to the numbers
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// Pulse Width Modulation (PWM) is how the Arduino tells the motors where to position
// The Arduino board used in this project can do PWM on the following pins: 3, 5, 6, 9, 10, and 11

#define EYES_PAN  11  // Use pin 11 for the left/right eye movement
#define EYES_TILT 10  // Use pin 10 for the up/down eye movement

#define RT_EAR_TILT 5  // pin 5 does right ear forward/backward
#define RT_EAR_PAN  3  // pin 3 does right ear left/right
#define LT_EAR_TILT 9  // pin 9 does left  ear forward/backward
#define LT_EAR_PAN  6  // pin 6 does left  ear left/right

#define SW 13          // pin 13 is used to detect when the nose button is pressed

#define LETH 120       // left  ear tilt home position
#define RETH 60        // right ear tilt home position
#define LEPH 120       // left  ear pan home position
#define REPH 60        // right ear pan home position

// this function initializes the display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// this unsigned char array tells the display how to draw a star pattern
static const unsigned char PROGMEM logo_bmp[] =
{ 
  0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000
  };

// the following lines create software objects that are used to set the motor positions later in the code.
Servo eyes_pan;
Servo eyes_tilt;
Servo rt_ear_tilt; 
Servo rt_ear_pan; 
Servo lt_ear_tilt; 
Servo lt_ear_pan; 

// this function makes the eyes move left and right
void pan_eyes()
{
  delay(200); // stop and wait 200 milliseconds (.2 seconds) You have to allow the motor a bit of time to move
  eyes_pan.write(60);  // move the eyes left
  delay(200); // stop and wait 200 milliseconds (.2 seconds) You have to allow the motor a bit of time to move
  eyes_pan.write(120); // move the eyes right
  delay(200); // stop and wait 200 milliseconds (.2 seconds) You have to allow the motor a bit of time to move
  eyes_pan.write(90);  // move the eyes back to center
}

// does the same thing as above, but moves the eyes up and down instead
void tilt_eyes()
{
  delay(200);
  eyes_tilt.write(60);
  delay(200);
  eyes_tilt.write(120);
  delay(200);
  eyes_tilt.write(90);
}

// The display will show one of five different messages.
// The following functions draw the text on the display

void textTwo()
{
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("   from    "));
  display.setCursor(0, 16);
  display.println(F("  Veraxx   "));
  display.display();      // Show initial text
  delay(100);
}

void textOne()
{
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("   Merry   "));
  display.setCursor(0, 16);
  display.println(F(" Christmas "));
  display.display();      // Show initial text
  delay(100);
}
void textThree()
{
  display.clearDisplay();
  display.setTextSize(4); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("NSDQ!"));
  display.display();      // Show initial text
  delay(100);
  //display.startscrollleft(0x00, 0x0F);
}
void textFour()
{
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Again... ?"));
  display.display();      // Show initial text
  delay(100);
}
void textFive()
{
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Well hello"));
  display.setCursor(0, 16);
  display.println(F("there!"));
  display.display();      // Show initial text
  delay(100);
}


// This function runs when the reindeer isn't doing anything else.
void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Merry Xmas"));
  //display.display();      // Show initial text
  display.setCursor(0, 16);
  display.println(F("from Veraxx"));
  display.display();      // Show initial text
  delay(100);
}







/***   EYE MOVEMENT   ***/
// These functions basically do what they say.
void eyes_right()
{
  eyes_pan.write(30);
}
void eyes_left()
{
  eyes_pan.write(150);
}
void eyes_pan_home()
{
  eyes_pan.write(90);
}

void eyes_home()
{
  eyes_pan.write(90);
  eyes_tilt.write(100);
}
void eyes_up()
{
  eyes_tilt.write(30);
}
void eyes_down()
{
  eyes_tilt.write(150);
}
void eyes_tilt_home()
{
  eyes_tilt.write(90);
}


// this function uses some math to make the eyes move in a circular motion to "roll the eyes"
void roll_eyes()
{
  float theta = 0.0;
  float dtheta = 0.05;
  int dly = 20;
  float pan_range = 60.0;
  float tilt_range = 60.0;
  
  while(theta <= 3.15)
  {
    float pan_angle = 90.0 + (pan_range * (cos(theta)));
    eyes_pan.write((int)pan_angle);
    float tilt_angle = 90.0 - (tilt_range * (sin(theta)));
    eyes_tilt.write((int)tilt_angle);
    delay(dly);
    theta += dtheta;
  }
}

// This function makes the eyes pan up slowly
void eyes_up_slow()
{
  float theta = 0.0;
  float dtheta = 0.05;
  int dly = 20;
  float tilt_range = 60.0;
  
  while(theta <= 3.15)
  {
    float tilt_angle = 90.0 + (tilt_range * (sin(theta)));
    eyes_tilt.write((int)tilt_angle);
    delay(dly);
    theta += dtheta;
  }
}


/*** EAR MOVEMENT ***/

void ears_right()
{
  rt_ear_pan.write(100);
  lt_ear_pan.write(100);
}
void ears_left()
{
  rt_ear_pan.write(80);
  lt_ear_pan.write(80);
}
void ears_pan_home()
{
  rt_ear_pan.write(90);
  lt_ear_pan.write(90);
}

void ears_down()
{
  rt_ear_tilt.write(30);
  lt_ear_tilt.write(150);
  
}

void ears_up()
{
  rt_ear_tilt.write(RETH);
  lt_ear_tilt.write(LETH);
}


void ears_home()
{
  rt_ear_tilt.write(RETH);
  rt_ear_pan.write(REPH);
  lt_ear_tilt.write(LETH);
  lt_ear_pan.write(REPH);
  
}


/***** HERE IS WHERE THE PROGRAM ACTUALLY STARTS ********/


// The setup() function runs one time, when you first turn it on
void setup() {

  Serial.begin(9600);

  // this just checks that the display is detected
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();

  // This is part of the setup to make the motors move later
  eyes_pan.attach(EYES_PAN);
  eyes_tilt.attach(EYES_TILT);
  rt_ear_tilt.attach(RT_EAR_TILT);
  rt_ear_pan.attach(RT_EAR_PAN);
  lt_ear_tilt.attach(LT_EAR_TILT);
  lt_ear_pan.attach(LT_EAR_PAN);

  // tell the motors to center the eyes and ears
  ears_home();
  eyes_home();

  // Remeber that "SW" actually means pin 13. Pin 13 is wired to the nose button.
  // The pinMode function tells the Arduino we will be using pin 13 for input.
  pinMode(SW, INPUT_PULLUP);
}


// create some variables to save which message and animation is being used
unsigned long textMsg = 0;
unsigned int animation = 0;


// This is the MAIN function that runs over and over as long as the device is powered
void loop() {
  
  // first, we see if the button has been pressed.
  // a bool variable can only be true or false (1 or 0)
  bool button_press = !digitalRead(SW);


  // these lines cycle the display through the "Merry Christmas" message
  // This happens when the button has not been pressed
  if(textMsg == 0)
    textOne();
  else if (textMsg == 250000)
    textTwo();
  else if (textMsg == 500000)
    textThree();
  textMsg++;
  if(textMsg > 750000 )
  {
    textMsg = 0;
  }

  // If the button was pressed, then the following lines will run
  // the animation variable is used to figure out which animation to do
  // It cycles through the three animations (and display messages) in order.
  // After it gets to the third one, it resets animation to zero and starts over.
  if(button_press)
  {
    if(animation == 0)
    {
      eyes_right();
      delay(800);
      eyes_left();
      delay(800);
      eyes_pan_home();
      delay(100);
      textMsg = 0;
    }
    else if(animation == 1)
    {
      textFive();
      eyes_up();
      delay(400);
      eyes_down();
      delay(400);
      eyes_up_slow();
      delay(100);
      textMsg = 0;
    }
    else if(animation == 2)
    {
      textFour();
      roll_eyes();
      delay(200);
      eyes_home();
      delay(100);
      textMsg = 0;
    }

    animation++;
    
    if(animation > 2)
      animation = 0;
    
    int emintvl = 175;  // ear movement interval
    ears_down();
    delay(emintvl);
    ears_up();
    delay(emintvl);
    ears_down();
    delay(emintvl);
    ears_up();
    delay(emintvl);
    ears_down();
    delay(emintvl);
    ears_up();
    delay(emintvl);
    ears_down();
    delay(emintvl);
    ears_up();
  }

}
