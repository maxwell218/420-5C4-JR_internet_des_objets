// Tommy Harvey
// 22-08-2022
// Maison Arduino

// On ajoute les librairies
#include <Servo.h>              // Permet de gérer les servomoteurs
#include <Wire.h>               // Permet de gérer les connections I2C
#include <LiquidCrystal_I2C.h>  // Pour les écrans LCD avec connections I2C

// On initialise l'adresse de communication avec l'écran I2C à la pin 0x27
// Un maximum de 16 caractères par ligne
// Avec 2 lignes au total (ligne 0 et ligne 1)
LiquidCrystal_I2C mylcd(0x27, 16, 2); // Définir l'instance I2C

// On initialise les deux moteurs aux pins digitales 9 et 10
Servo servoPorte; // Le servomoteur de la porte
Servo servoFenetre; // Le servomoteur de la fenetre

// TODO changer le commentaire de chaque var
int button1;        //set variable button1
int button2;        //set variable button2
String fans_char;   //string type variable fans_char
int fans_val;       //set variable fans_char
String led2;        //string type variable led2
String pass;        //string type variable pass
String passwd;      //string type variable passwd

String servo1;      //string type variable servo1
int servo1_angle;   //set variable light
String servo2;      //string type variable servo2
int servo2_angle;   //set variable servo2_angle

int val;            //set variable val
int value_led2;     //set variable value_led2

int longueurDeLaToune = 0; // Permet de retrouver facilement la longueur d'une toune à partir de son tableau

// Constantes des pins et variables
const int tonePin = 3;            //set the signal end of passive buzzer to digital 3
const int servoFenetrePin = 9;    //
const int servoPortePin = 10;     //
const int capteurGazPin = A0;     // Pin analogue pour le détecteur de gaz carbonique et autres
      int gaz = 0;                //set variable gaz
      int gazDrapeau = 0;         // Drapeau pour vérifier l'état du détecteur de gaz
const int gazMax = 700;           // Valeur qui permet de déclencher l'alarme de gaz
const int gazMin = 100;           // Valeur qui permet de désactiver l'alarme de gaz
const int capteurLumierePin = A1; // Pin analogue pour le détecteur de lumière
      int lumiere = 0;            //
const int lumiereMin = 300;       // Valeur qui permet de déclencher la lumière
const int infrarPin = 2;          //
      int infrar = 0;             // État du détecteur de movement
      int lumiereDrapeau = 0;     //
const int lumierePortePin = 13;   // La LED du Arduino UNO est aussi connecté à la pin 13
const int capteurPluiePin = A3;   //
      int pluie = 0;              //
      int pluieDrapeau;           //set variable pluieDrapeau
const int pluieMax = 800;         // Valeur qui permet de fermer la porte s'il pleut
const int capteurEauTerre = A2;   //
      int eauTerre = 0;           //set variable pluie
      int eauTerreDrapeau = 0;    //
const int eauTerreMax = 50;       //
const int eauTerreMin = 10;       //
      int boutonGauche = 0;       //set variable boutonGauche
      int boutonDroit = 0;        //set variable boutonDroit
const int boutonGauchePin = 4;    //set variable boutonGauche
const int boutonDroitPin = 8;     //set variable boutonDroit
void setup() {
  Serial.begin(9600); // Initialise et active la console

  mylcd.init();       // Initialise l'instance de l'écran LCD
  mylcd.backlight();  // Initialise la lumière de l'écran
  
  // On affiche une demande de mot de passe sur l'écran LCD à partir
  // de la première ligne et de la première colonne
  // TODO changer la gestion du mot de passe
  mylcd.setCursor(1 - 1, 1 - 1);
  mylcd.print("password:");

  servoFenetre.attach(servoFenetrePin);   // make servo connect to digital 9
  servoPorte.attach(servoPortePin);       // make servo connect to digital 10
  servoFenetre.write(0);                  // Servo fenetre à 0° TODO à reviser
  servoPorte.write(0);                    // Servo porte à 0°
  delay(300); // TODO à tester

  pinMode(7, OUTPUT);     //set digital 7 to output
  pinMode(6, OUTPUT);     //set digital 6 to output
  digitalWrite(7, HIGH);  //set digital 7 to high level
  digitalWrite(6, HIGH);  //set digital 6 to high level

  pinMode(boutonGauchePin, INPUT);    //set digital 4 to input
  pinMode(boutonDroitPin, INPUT);    //set digital 8 to input
  pinMode(infrarPin, INPUT);    //set digital 2 to input
  pinMode(3, OUTPUT);   //set digital 3 to output
  pinMode(capteurGazPin, INPUT);   //set capteurGazPin to input
  pinMode(capteurLumierePin, INPUT);   //set capteurLumierePin to input
  pinMode(lumierePortePin, OUTPUT);  //set digital 13 to input
  pinMode(capteurPluiePin, INPUT);   //set A3 to input
  pinMode(capteurEauTerre, INPUT);   //set A2 to input

  pinMode(12, OUTPUT);  //set digital 12 to output
  pinMode(5, OUTPUT);   //set digital 5 to output
  pinMode(3, OUTPUT);   //set digital 3 to output
  // longueurDeLaToune = sizeof(tune) / sizeof(tune[0]);  //set the value of longueurDeLaToune

  // TODO debug
  Serial.println(F("Maison original - V1.0 - Fin du setup"));
}

void loop() {
  auto_sensor();
  door();
  if (Serial.available() > 0)  //serial reads the characters
  {
    val = Serial.read();  //set val to character read by serial    Serial.println(val);//output val character in new lines
    pwm_control();
  }
  switch (val) {
    case 'a':                  //if val is character 'a'，program will circulate
      digitalWrite(lumierePortePin, HIGH);  //set digital 13 to high level，LED 	lights up
      break;                   //exit loop
    case 'b':                  //if val is character 'b'，program will circulate
      digitalWrite(lumierePortePin, LOW);   //Set digital 13 to low level, LED is off
      break;                   //exit loop
    case 'c':                  //if val is character 'c'，program will circulate
      digitalWrite(12, HIGH);  //set digital 12 to high level，NO of relay is connected to COM
      break;                   //exit loop
    case 'd':                  //if val is character 'd'，program will circulate
      digitalWrite(12, LOW);   //set digital 12 to low level，NO of relay is disconnected to COM
      break;                  //exit loop
    case 'e':                 //if val is character 'e'，program will circulate
      // music1();               //play birthday song
      break;                  //exit loop
    case 'f':                 //if val is character 'f'，program will circulate
      // music2();               //play ode to joy song
      break;                  //exit loop
    case 'g':                 //if val is character 'g'，program will circulate
      noTone(3);              //set digital 3 to stop playing music
      break;                  //exit loop
    case 'h':                 //if val is character 'h'，program will circulate
      Serial.println(lumiere);  //output the value of variable light in new lines
      delay(100);
      break;                //exit loop
    case 'i':               //if val is character 'i'，program will circulate
      Serial.println(gaz);  //output the value of variable gaz in new lines
      delay(100);
      break;                 //exit loop
    case 'j':                //if val is character 'j'，program will circulate
      Serial.println(eauTerre);  //output the value of variable eauTerre in new lines
      delay(100);
      break;                  //exit loop
    case 'k':                 //if val is character 'k'，program will circulate
      Serial.println(pluie);  //output the value of variable pluie in new lines
      delay(100);
      break;               //exit loop
    case 'l':              //if val is character 'l'，program will circulate
      servoFenetre.write(180);  //set servo connected to digital 9 to 180°
      delay(500);
      break;   //exit loop
    case 'm':  //if val is character 'm'，program will circulate
      servoFenetre.write(0);
      ;  //set servo connected to digital 9 to 0°
      delay(500);
      break;                //exit loop
    case 'n':               //if val is character 'n'，program will circulate
      servoPorte.write(180);  //set servo connected to digital 10 to 180°
      delay(500);
      break;              //exit loop
    case 'o':             //if val is character 'o'，program will circulate
      servoPorte.write(0);  //set servo connected to digital 10 to 0°
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

//detect gaz
void auto_sensor() {
  gaz = analogRead(capteurGazPin);  // Lecture de la valeur de gaz
  if (gaz > gazMax) 
  {
    gazDrapeau = 1;
    // while (gazDrapeau == 1)
    // //if gazDrapeau is 1, program will circulate
    // {
    //   Serial.println("danger");  //output "danger" in new lines
    //   tone(3, 440);
    //   delay(125);
    //   delay(100);
    //   noTone(3);
    //   delay(100);
    //   tone(3, 440);
    //   delay(125);
    //   delay(100);
    //   noTone(3);
    //   delay(300);
    //   gaz = analogRead(capteurGazPin);  //gaz analog the value of capteurGazPin to gaz
    //   noTone(3);
  }
  else if (gaz < gazMin)
  {
    gazDrapeau = 0;
  }

  lumiere = analogRead(capteurLumierePin); // Lecture de la valeur du détecteur de lumière
  if (lumiere < lumiereMin) // S'il fait noir dehors
  {
    lumiereDrapeau = 1;
    infrar = digitalRead(infrarPin);  //assign the value of digital 2 to infrar
    Serial.println(infrar);   //output the value of variable infrar in new lines

    if (infrar == 1) // Mouvement détecté
    {
      digitalWrite(lumierePortePin, HIGH);  //set digital 13 to high level, LED is on
    } 
    else
    {
      digitalWrite(lumierePortePin, LOW);  //set digital 13 to low level, LED is off
    }
  }
  else
  {
    lumiereDrapeau = 0; // TODO à tester avec une alarme
  }  

  pluie = analogRead(capteurPluiePin);  //assign the analog value of A3 to variable pluie
  if (pluie > pluieMax)
  {
    pluieDrapeau = 1;
    // TODO à déplacer avec le traitement des alarmes
    // TODO peut-on lire l'état d'un servomoteur
    // while (pluieDrapeau == 1)
    // // if pluieDrapeau is 1, program will circulate
    // {
    Serial.println("Il pleut");
    servoPorte.write(180);     // set the servo connected to digital 10 to 180°
    //   delay(300);              //delay in 300ms
    //   delay(100);
    pluie = analogRead(capteurPluiePin);  //assign the analog value of A3 to variable pluie
    //   if (pluie < 30)  // if variable pluie is less than 30
    //   {
    //     pluieDrapeau = 0;  // set pluieDrapeau to 0
    //     break;      //exit loop
    //   }
    // }
  }
  else if (pluie < 30) 
  {
    pluieDrapeau = 0;
  }
  else
  {
    // TODO à tester
    if (val != 'u' && val != 'n')
    //if val is not equivalent 'u' either 'n'
    {
      servoPorte.write(0);  //set servo connected to digital 10 to 0°
      delay(10);
    }
  }

  eauTerre = analogRead(capteurEauTerre);  //assign the analog value of A2 to variable eauTerre
  if (eauTerre > eauTerreMax)
  {
    eauTerreDrapeau = 1;  //set eauTerreDrapeau to 1
    // while (eauTerreDrapeau == 1)
    // //If set eauTerreDrapeau to 1, program will circulate
    // {
    //   Serial.println("hydropenia ");  //output "hydropenia " in new lines
    //   tone(3, 440);
    //   delay(125);
    //   delay(100);
    //   noTone(3);
    //   delay(100);
    //   tone(3, 440);
    //   delay(125);
    //   delay(100);
    //   noTone(3);  //digital 3 stops playing sound
    //   delay(300);
    //   eauTerre = analogRead(A2);  //Assign the analog value of A2 to variable eauTerre
    //   if (eauTerre < 10)          //If variable eauTerre<10
    //   {
    //     eauTerreDrapeau = 0;  //set eauTerreDrapeau to 0
    //     break;      //exit loop
    //   }
    // }

  } 
  else if (eauTerre < eauTerreMin)
  {
    eauTerreDrapeau = 0;
    // noTone(3);
  }
}

void door() {
  button1 = digitalRead(boutonGauchePin);  // assign the value of digital 4 to button1
  button2 = digitalRead(8);  //assign the value of digital 8 to button2

  if (button1 == 0)  //if variablebutton1 is 0
  {
    delay(10);            //delay in 10ms
    while (button1 == 0)  //if variablebutton1 is 0，program will circulate
    {
      button1 = digitalRead(boutonGauchePin);  // assign the value of digital 4 to button1
      boutonGauche = boutonGauche + 1;   //variable boutonGauche plus 1
      delay(100);                // delay in 100ms
    }
  }
  if (boutonGauche >= 1 && boutonGauche < 5)  //1≤if variableboutonGauche<5
  {
    Serial.print(".");
    Serial.print("");
    passwd = String(passwd) + String(".");  //set passwd
    pass = String(pass) + String(".");      //set pass
    //LCD shows pass at the first row and column
    mylcd.setCursor(1 - 1, 2 - 1);
    mylcd.print(pass);
  }
  if (boutonGauche >= 5)
  //if variableboutonGauche ≥5
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
        servoFenetre.write(100);  //set servo connected to digital 9 to 100°
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
    servoFenetre.write(0);  //set servo connected to digital 9 to 0°
    delay(50);
  }
  if (button2 == 0)  //if variablebutton2 is 0
  {
    delay(10);
    while (button2 == 0)  //if variablebutton2 is 0，program will circulate
    {
      button2 = digitalRead(8);  //assign the value of digital 8 to button2
      boutonDroit = boutonDroit + 1;   //variable boutonDroit plus 1
      delay(100);
      if (boutonDroit >= 15)  //if variableboutonDroit ≥15
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
  boutonGauche = 0;  //set boutonGauche to 0
  boutonDroit = 0;  //set boutonDroit to 0
}

//PWM control
void pwm_control() {
  switch (val) {
    case 't':  //if val is 't'，program will circulate
      servo1 = Serial.readStringUntil('#');
      servo1_angle = String(servo1).toInt();
      servoFenetre.write(servo1_angle);  //set the angle of servo connected to digital 9 to servo1_angle
      delay(300);
      break;   //exit loop
    case 'u':  //if val is 'u'，program will circulate
      servo2 = Serial.readStringUntil('#');
      servo2_angle = String(servo2).toInt();
      servoPorte.write(servo2_angle);  //set the angle of servo connected to digital 10 to servo2_angle
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
