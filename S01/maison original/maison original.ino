// Tommy Harvey
// 22-08-2022
// Maison Arduino

// On ajoute les librairies
#include <Servo.h>              // Permet de gérer les moteurs
#include <Wire.h>               // Permet de gérer les connections I2C
#include <LiquidCrystal_I2C.h>  // Pour les écrans LCD avec connections I2C

// On initialise l'adresse de communication I2C à la pin 0x27
// Un maximum de 16 caractères par ligne
// Avec 2 lignes au total
LiquidCrystal_I2C mylcd(0x27, 16, 2);

// On initialise les deux moteurs aux pins digitales 9 et 10
Servo servo_10;
Servo servo_9;

int bouton1Val;     //set variable bouton1Val
int bouton2Val;     //set variable bouton2Val
int button1;        //set variable button1
int button2;        //set variable button2
String fans_char;   //string type variable fans_char
int fans_val;       //set variable fans_char
int flag;           //set variable flag
int flag2;          //set variable flag2
int flag3;          //set variable flag3
int gas;            //set variable gas
int infrar;         //set variable infrar
String led2;        //string type variable led2
int light;          //set variable light
String pass;        //string type variable pass
String passwd;      //string type variable passwd

String servo1;      //string type variable servo1
int servo1_angle;   //set variable light
String servo2;      //string type variable servo2
int servo2_angle;   //set variable servo2_angle

int soil;           //set variable soil
int val;            //set variable val
int value_led2;     //set variable value_led2
int water;          //set variable water

int length;

// Constantes des pins
const int tonepin = 3;  //set the signal end of passive buzzer to digital 3
const int servoFenetrePin = 9;

// define name of every sound frequency
const int D0 = -1;
const int D1 = 262;
const int D2 = 293;
const int D3 = 329;
const int D4 = 349;
const int D5 = 392;
const int D6 = 440;
const int D7 = 494;
const int M1 = 523;
const int M2 = 586;
const int M3 = 658;
const int M4 = 697;
const int M5 = 783;
const int M6 = 879;
const int M7 = 987;
const int H1 = 1045;
const int H2 = 1171;
const int H3 = 1316;
const int H4 = 1393;
const int H5 = 1563;
const int H6 = 1755;
const int H7 = 1971;

const int WHOLE = 1;
const int HALF = 0.5;
const int QUARTER = 0.25;
const int EIGHTH = 0.25;
const int SIXTEENTH = 0.625;

//set sound play frequency
int tune[] = {
  M3, M3, M4, M5,
  M5, M4, M3, M2,
  M1, M1, M2, M3,
  M3, M2, M2,
  M3, M3, M4, M5,
  M5, M4, M3, M2,
  M1, M1, M2, M3,
  M2, M1, M1,
  M2, M2, M3, M1,
  M2, M3, M4, M3, M1,
  M2, M3, M4, M3, M2,
  M1, M2, D5, D0,
  M3, M3, M4, M5,
  M5, M4, M3, M4, M2,
  M1, M1, M2, M3,
  M2, M1, M1
};

//set music beat
float durt[] = {
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1 + 0.5,
  0.5,
  1 + 1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1 + 0.5,
  0.5,
  1 + 1,
  1,
  1,
  1,
  1,
  1,
  0.5,
  0.5,
  1,
  1,
  1,
  0.5,
  0.5,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0.5,
  0.5,
  1,
  1,
  1,
  1,
  1 + 0.5,
  0.5,
  1 + 1,
};


void setup() {
  Serial.begin(9600); // Initialise et active la console

  mylcd.init();       // Initialise l'instance de l'écran LCD
  mylcd.backlight();  // Initialise la lumière de l'écran
  
  // On affiche une demande de mot de passe sur l'écran LCD à partir
  // de la première ligne et de la première colonne
  mylcd.setCursor(1 - 1, 1 - 1);
  mylcd.print("password:");

  servo_9.attach(servoFenetrePin);    //make servo connect to digital 9
  servo_10.attach(10);  //make servo connect to digital 10
  servo_9.write(0);     //set servo connected digital 9 to 0°
  servo_10.write(0);    //set servo connected digital 10 to 0°
  delay(300);

  pinMode(7, OUTPUT);     //set digital 7 to output
  pinMode(6, OUTPUT);     //set digital 6 to output
  digitalWrite(7, HIGH);  //set digital 7 to high level
  digitalWrite(6, HIGH);  //set digital 6 to high level

  pinMode(4, INPUT);    //set digital 4 to input
  pinMode(8, INPUT);    //set digital 8 to input
  pinMode(2, INPUT);    //set digital 2 to input
  pinMode(3, OUTPUT);   //set digital 3 to output
  pinMode(A0, INPUT);   //set A0 to input
  pinMode(A1, INPUT);   //set A1 to input
  pinMode(13, OUTPUT);  //set digital 13 to input
  pinMode(A3, INPUT);   //set A3 to input
  pinMode(A2, INPUT);   //set A2 to input

  pinMode(12, OUTPUT);                      //set digital 12 to output
  pinMode(5, OUTPUT);                       //set digital 5 to output
  pinMode(3, OUTPUT);                       //set digital 3 to output
  length = sizeof(tune) / sizeof(tune[0]);  //set the value of length
}

void loop() {
  auto_sensor();
  if (Serial.available() > 0)  //serial reads the characters
  {
    val = Serial.read();  //set val to character read by serial    Serial.println(val);//output val character in new lines
    pwm_control();
  }
  switch (val) {
    case 'a':                  //if val is character 'a'，program will circulate
      digitalWrite(13, HIGH);  //set digital 13 to high level，LED 	lights up
      break;                   //exit loop
    case 'b':                  //if val is character 'b'，program will circulate
      digitalWrite(13, LOW);   //Set digital 13 to low level, LED is off
      break;                   //exit loop
    case 'c':                  //if val is character 'c'，program will circulate
      digitalWrite(12, HIGH);  //set digital 12 to high level，NO of relay is connected to COM
      break;                   //exit loop
    case 'd':                  //if val is character 'd'，program will circulate
      digitalWrite(12, LOW);   //set digital 12 to low level，NO of relay is disconnected to COM
      break;                  //exit loop
    case 'e':                 //if val is character 'e'，program will circulate
      music1();               //play birthday song
      break;                  //exit loop
    case 'f':                 //if val is character 'f'，program will circulate
      music2();               //play ode to joy song
      break;                  //exit loop
    case 'g':                 //if val is character 'g'，program will circulate
      noTone(3);              //set digital 3 to stop playing music
      break;                  //exit loop
    case 'h':                 //if val is character 'h'，program will circulate
      Serial.println(light);  //output the value of variable light in new lines
      delay(100);
      break;                //exit loop
    case 'i':               //if val is character 'i'，program will circulate
      Serial.println(gas);  //output the value of variable gas in new lines
      delay(100);
      break;                 //exit loop
    case 'j':                //if val is character 'j'，program will circulate
      Serial.println(soil);  //output the value of variable soil in new lines
      delay(100);
      break;                  //exit loop
    case 'k':                 //if val is character 'k'，program will circulate
      Serial.println(water);  //output the value of variable water in new lines
      delay(100);
      break;               //exit loop
    case 'l':              //if val is character 'l'，program will circulate
      servo_9.write(180);  //set servo connected to digital 9 to 180°
      delay(500);
      break;   //exit loop
    case 'm':  //if val is character 'm'，program will circulate
      servo_9.write(0);
      ;  //set servo connected to digital 9 to 0°
      delay(500);
      break;                //exit loop
    case 'n':               //if val is character 'n'，program will circulate
      servo_10.write(180);  //set servo connected to digital 10 to 180°
      delay(500);
      break;              //exit loop
    case 'o':             //if val is character 'o'，program will circulate
      servo_10.write(0);  //set servo connected to digital 10 to 0°
      delay(500);
      break;                  //exit loop
    case 'p':                 //if val is character 'p'，program will circulate
      digitalWrite(5, HIGH);  //set digital 5 to high level, LED is on
      break;                  //exit loop
    case 'q':                 //if val is character 'q'，program will circulate
      digitalWrite(5, LOW);   // set digital 5 to low level, LED is off
      break;                  //exit loop
    case 'r':                 //if val is character 'r'，program will circulate
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);  //fan rotates anticlockwise at the fastest speed
      break;                  //exit loop
    case 's':                 //if val is character 's'，program will circulate
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);  //fan stops rotating
      break;                 //exit loop
  }
}

////////////////////////set birthday song//////////////////////////////////
void birthday() {
  tone(3, 294);  //digital 3 outputs 294HZ sound
  delay(250);    //delay in 250ms
  tone(3, 440);
  delay(250);
  tone(3, 392);
  delay(250);
  tone(3, 532);
  delay(250);
  tone(3, 494);
  delay(500);
  tone(3, 392);
  delay(250);
  tone(3, 440);
  delay(250);
  tone(3, 392);
  delay(250);
  tone(3, 587);
  delay(250);
  tone(3, 532);
  delay(500);
  tone(3, 392);
  delay(250);
  tone(3, 784);
  delay(250);
  tone(3, 659);
  delay(250);
  tone(3, 532);
  delay(250);
  tone(3, 494);
  delay(250);
  tone(3, 440);
  delay(250);
  tone(3, 698);
  delay(375);
  tone(3, 659);
  delay(250);
  tone(3, 532);
  delay(250);
  tone(3, 587);
  delay(250);
  tone(3, 532);
  delay(500);
}



//detect gas
void auto_sensor() {
  gas = analogRead(A0);  //assign the analog value of A0 to gas
  if (gas > 700) {
    //if variable gas>700
    flag = 1;  //set variable flag to 1
    while (flag == 1)
    //if flag is 1, program will circulate
    {
      Serial.println("danger");  //output "danger" in new lines
      tone(3, 440);
      delay(125);
      delay(100);
      noTone(3);
      delay(100);
      tone(3, 440);
      delay(125);
      delay(100);
      noTone(3);
      delay(300);
      gas = analogRead(A0);  //gas analog the value of A0 to gas
      if (gas < 100)         //if variable gas is less than 100
      {
        flag = 0;  //set variable flag to 0
        break;     //exit loop exist to loop
      }
    }

  } else
  //otherwise
  {
    noTone(3);  // digital 3 stops playing music
  }
  light = analogRead(A1);  ////Assign the analog value of A1 to light
  if (light < 300)         //if variable light is less than 300
  {
    infrar = digitalRead(2);  //assign the value of digital 2 to infrar
    Serial.println(infrar);   //output the value of variable infrar in new lines
    if (infrar == 1) // Mouvement détecté
    // if variable infra is 1
    {
      digitalWrite(13, HIGH);  //set digital 13 to high level, LED is on
    } else                     //Otherwise
    {
      digitalWrite(13, LOW);  //set digital 13 to low level, LED is off
    }
  }
  water = analogRead(A3);  //assign the analog value of A3 to variable water
  if (water > 800)
  // if variable water is larger than 800
  {
    flag2 = 1;  //if variable flag 2 to 1
    while (flag2 == 1)
    // if flag2 is 1, program will circulate
    {
      Serial.println("rain");  //output "rain" in new lines
      servo_10.write(180);     // set the servo connected to digital 10 to 180°
      delay(300);              //delay in 300ms
      delay(100);
      water = analogRead(A3);  //assign the analog value of A3 to variable water
      if (water < 30)  // if variable water is less than 30
      {
        flag2 = 0;  // set flag2 to 0
        break;      //exit loop
      }
    }

  } else  //Otherwise
  {
    if (val != 'u' && val != 'n')
    //if val is not equivalent 'u' either 'n'
    {
      servo_10.write(0);  //set servo connected to digital 10 to 0°
      delay(10);
    }
  }
  soil = analogRead(A2);  //assign the analog value of A2 to variable soil
  if (soil > 50)
  // if variable soil is greater than 50
  {
    flag3 = 1;  //set flag3 to 1
    while (flag3 == 1)
    //If set flag3 to 1, program will circulate
    {
      Serial.println("hydropenia ");  //output "hydropenia " in new lines
      tone(3, 440);
      delay(125);
      delay(100);
      noTone(3);
      delay(100);
      tone(3, 440);
      delay(125);
      delay(100);
      noTone(3);  //digital 3 stops playing sound
      delay(300);
      soil = analogRead(A2);  //Assign the analog value of A2 to variable soil
      if (soil < 10)          //If variable soil<10
      {
        flag3 = 0;  //set flag3 to 0
        break;      //exit loop
      }
    }

  } else  //Otherwise
  {
    noTone(3);  //set digital 3 to stop playing music
  }
  door();  //run subroutine
}

void door() {
  button1 = digitalRead(4);  // assign the value of digital 4 to button1
  button2 = digitalRead(8);  //assign the value of digital 8 to button2


  if (button1 == 0)  //if variablebutton1 is 0
  {
    delay(10);            //delay in 10ms
    while (button1 == 0)  //if variablebutton1 is 0，program will circulate
    {
      button1 = digitalRead(4);  // assign the value of digital 4 to button1
      bouton1Val = bouton1Val + 1;   //variable bouton1Val plus 1
      delay(100);                // delay in 100ms
    }
  }
  if (bouton1Val >= 1 && bouton1Val < 5)  //1≤if variablebouton1Val<5
  {
    Serial.print(".");
    Serial.print("");
    passwd = String(passwd) + String(".");  //set passwd
    pass = String(pass) + String(".");      //set pass
    //LCD shows pass at the first row and column
    mylcd.setCursor(1 - 1, 2 - 1);
    mylcd.print(pass);
  }
  if (bouton1Val >= 5)
  //if variablebouton1Val ≥5
  {
    Serial.print("-");
    passwd = String(passwd) + String("-");  //Set passwd
    pass = String(pass) + String("-");      //set pass
    //LCD shows pass at the first row and column
    mylcd.setCursor(1 - 1, 2 - 1);
    mylcd.print(pass);
  }
  if (button2 == 0)  //if variablebutton2 is 0
  {
    delay(10);
    if (button2 == 0)  //if variablebutton2 is 0
    {
      if (passwd == ".--.-.")  //if passwd is ".--.-."
      {
        mylcd.clear();  //clear LCD screen
        //LCD shows "open!" at first character on second row
        mylcd.setCursor(1 - 1, 2 - 1);
        mylcd.print("open!");
        servo_9.write(100);  //set servo connected to digital 9 to 100°
        delay(300);
        delay(5000);
        passwd = "";
        pass = "";
        mylcd.clear();  //clear LCD screen
        //LCD shows "password:"at first character on first row
        mylcd.setCursor(1 - 1, 1 - 1);
        mylcd.print("password:");

      } else  //Otherwise
      {
        mylcd.clear();  //clear LCD screen
        //LCD shows "error!"at first character on first row
        mylcd.setCursor(1 - 1, 1 - 1);
        mylcd.print("error!");
        passwd = "";
        pass = "";
        delay(2000);
        //LCD shows "again" at first character on first row
        mylcd.setCursor(1 - 1, 1 - 1);
        mylcd.print("again");
      }
    }
  }
  infrar = digitalRead(2);  //assign the value of digital 2 to infrar
  if (infrar == 0 && (val != 'l' && val != 't'))
  //if variable infrar is 0 and val is not 'l' either 't'
  {
    servo_9.write(0);  //set servo connected to digital 9 to 0°
    delay(50);
  }
  if (button2 == 0)  //if variablebutton2 is 0
  {
    delay(10);
    while (button2 == 0)  //if variablebutton2 is 0，program will circulate
    {
      button2 = digitalRead(8);  //assign the value of digital 8 to button2
      bouton2Val = bouton2Val + 1;   //variable bouton2Val plus 1
      delay(100);
      if (bouton2Val >= 15)  //if variablebouton2Val ≥15
      {
        tone(3, 532);
        delay(125);
        mylcd.clear();  //clear LCD screen
        //LCD shows "password:" at the first character on first row
        mylcd.setCursor(1 - 1, 1 - 1);
        mylcd.print("password:");
        //LCD shows "wait" at the first character on first row
        mylcd.setCursor(1 - 1, 1 - 1);
        mylcd.print("wait");
      } else  //Otherwise
      {
        noTone(3);  //digital 3 stops playing music
      }
    }
  }
  bouton1Val = 0;  //set bouton1Val to 0
  bouton2Val = 0;  //set bouton2Val to 0
}

// Birthday song
void music1() {
  birthday();
}
//Ode to joy
void music2() {
  Ode_to_Joy();
}
void Ode_to_Joy()  //play Ode to joy song
{
  for (int x = 0; x < length; x++) {
    tone(tonepin, tune[x]);
    delay(300 * durt[x]);
  }
}

//PWM control
void pwm_control() {
  switch (val) {
    case 't':  //if val is 't'，program will circulate
      servo1 = Serial.readStringUntil('#');
      servo1_angle = String(servo1).toInt();
      servo_9.write(servo1_angle);  //set the angle of servo connected to digital 9 to servo1_angle
      delay(300);
      break;   //exit loop
    case 'u':  //if val is 'u'，program will circulate
      servo2 = Serial.readStringUntil('#');
      servo2_angle = String(servo2).toInt();
      servo_10.write(servo2_angle);  //set the angle of servo connected to digital 10 to servo2_angle
      delay(300);
      break;   //exit loop
    case 'v':  //if val is 'v'，program will circulate
      led2 = Serial.readStringUntil('#');
      value_led2 = String(led2).toInt();
      analogWrite(5, value_led2);  //PWM value of digital 5 is value_led2
      break;                       //exit loop
    case 'w':                      //if val is 'w'，program will circulate
      fans_char = Serial.readStringUntil('#');
      fans_val = String(fans_char).toInt();
      digitalWrite(7, LOW);
      analogWrite(6, fans_val);  //set PWM value of digital 6 to fans_val，the larger the value, the faster the fan
      break;                     //exit loop
  }
}
