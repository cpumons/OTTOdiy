#include <Servo.h> 
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>
#include <SoftwareSerial.h>

#define PIN_YL 2 //servo[2]
#define PIN_YR 3 //servo[3]
#define PIN_RL 4 //servo[4]
#define PIN_RR 5 //servo[5]
#define ECHOPIN 9
#define TRIGPIN 8
Otto Otto;

#define N_SERVOS 4
#define EEPROM_TRIM false 
#define TRIM_RR 7
#define TRIM_RL 4
#define TRIM_YR  4
#define TRIM_YL -7
#define INTERVALTIME 10.0 

#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS  455
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GSH  830
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_C7  2093
#define NOTE_CS7 2217

#define piezzo 2 // Le buzzer sur le Pin D2

int compteur=0;
int T=1000;
int moveId=0;
int moveSize=15;
bool obstacleDetected = false;
//rx du hc05 sur 7
//tx su hc05 sur 6
SoftwareSerial hc05(6, 7);
char data = 0;            //Variable for storing received data



void setup(){
    Serial.begin(9600);   //Sets the baud for serial data transmission
    hc05.begin(9600);                       
    
  Serial.begin(19200);
  //Set the servo pins
  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true, -1, 13, 8, 9);
  Otto.sing(S_connection); //Otto wake up!
  Otto.home();
  delay(50);
  Otto.sing(S_happy); // a happy Otto :)

  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);


  servo[0].attach(PIN_RR);
  servo[1].attach(PIN_RL);
  servo[2].attach(PIN_YR);
  servo[3].attach(PIN_YL);
  
  //EEPROM.write(0,TRIM_RR);
  //EEPROM.write(1,TRIM_RL);
  //EEPROM.write(2,TRIM_YR);
  //EEPROM.write(3,TRIM_YL);
  
  int trim;
  
  if(EEPROM_TRIM){
    for(int x=0;x<4;x++){
      trim=EEPROM.read(x);
      if(trim>128)trim=trim-256;
      Serial.print("TRIM ");
      Serial.print(x);
      Serial.print(" en ");
      Serial.println(trim);
      servo[x].SetTrim(trim);
    }
  }
  else{
    servo[0].SetTrim(TRIM_RR);
    servo[1].SetTrim(TRIM_RL);
    servo[2].SetTrim(TRIM_YR);
    servo[3].SetTrim(TRIM_YL);
  }
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
}
int t=495;
double pause=0;


void loop(){
  if (hc05.available()){
    Serial.write(hc05.read());
  }
  if (Serial.available() > 0) {  
    int message = Serial.read();     
    if (message == 'A')
    {
      Serial.println ("C'est Star Wars coté obscure");
      Starwars();
    }   
    else if (message == 'B') 
    {
      Serial.println ("C'est BarbieGirl");
      BarbieGirl();
    }
    else if (message == 'C')
    {
      Serial.println ("C'est James Bond");
      Bond();
    }
    else if (message == 'D')
    {
      Serial.println("C'est Mc Gyver");
      McGyver();
    }
    else if (message == 'E')
    {
      Serial.println("C'est Pirate des Caraïbes");
      Pirate();
    }
    else if (message == 'F')
    {
      Serial.println("il evite les obstacles");
      dance()
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
    }
  }
}


//************OBSTACLE*************//
void avoid(){
  if(obstacleDetected){ 
     Otto.sing(S_surprise);  
     Otto.playGesture(OttoFretful); 
     Otto.sing(S_fart3); 
     Otto.walk(2,1300,-1); 
     Otto.turn(2,1000,-1);                
     delay(50); 
     obstacleDetector(); 
  }        
  else{ 
    Otto.walk(1,1000,1); 
    obstacleDetector(); 
  }
}


void obstacleDetector(){
// Start Ranging
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
// Compute distance
  float distance = pulseIn(ECHOPIN, HIGH);
  distance= distance/58;
  Serial.print(distance);
  Serial.println("cm");
 if(distance<15){
          obstacleDetected = true;
          Serial.println ("Obstacle Detected! Avoid collision");
        }else{
          obstacleDetected = false;
          Serial.println ("No Obstacle detected! - Keep on walking");
        }
}

//*********MUSIQUE*********//


void firstSection()
{
  tone(piezzo,NOTE_A4, 500);
  tone(piezzo,NOTE_A4, 500);    
  tone(piezzo,NOTE_A4, 500);
  tone(piezzo,NOTE_F4, 350);
  tone(piezzo,NOTE_C5, 150);  
  tone(piezzo,NOTE_A4, 500);
  tone(piezzo,NOTE_F4, 350);
  tone(piezzo,NOTE_C5, 150);
  tone(piezzo,NOTE_A4, 650); 
  delay(500); 
  tone(piezzo,NOTE_E5, 500);
  tone(piezzo,NOTE_E5, 500);
  tone(piezzo,NOTE_E5, 500);  
  tone(piezzo,NOTE_F5, 350);
  tone(piezzo,NOTE_C5, 150);
  tone(piezzo,NOTE_GS4, 500);
  tone(piezzo,NOTE_F4, 350);
  tone(piezzo,NOTE_C5, 150);
  tone(piezzo,NOTE_A4, 650); 
  delay(500);
}
 
void secondSection()
{
  tone(piezzo,NOTE_A5, 500);
  tone(piezzo,NOTE_A4, 300);
  tone(piezzo,NOTE_A4, 150);
  tone(piezzo,NOTE_A5, 500);
  tone(piezzo,NOTE_GSH, 325);
  tone(piezzo,NOTE_G5, 175);
  tone(piezzo,NOTE_FS5, 125);
  tone(piezzo,NOTE_F5, 125);    
  tone(piezzo,NOTE_FS5, 250); 
  delay(325); 
  tone(piezzo,NOTE_AS, 250);
  tone(piezzo,NOTE_DS5, 500);
  tone(piezzo,NOTE_D5, 325);  
  tone(piezzo,NOTE_CS5, 175);  
  tone(piezzo,NOTE_C5, 125);  
  tone(piezzo,NOTE_AS4, 125);  
  tone(piezzo,NOTE_C5, 250);   
  delay(350);
}

void Starwars() 
{    
  firstSection();  
  secondSection(); 
  //Variant 1
  tone(piezzo,NOTE_F4, 250);  
  tone(piezzo,NOTE_GS4, 500);  
  tone(piezzo,NOTE_F4, 350);  
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_C5, 500);
  tone(piezzo,NOTE_A4, 375);  
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_E5, 650); 
  delay(500);  
  secondSection(); 
  //Variant 2
  tone(piezzo,NOTE_F4, 250);  
  tone(piezzo,NOTE_GS4, 500);  
  tone(piezzo,NOTE_F4, 375);  
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_A4, 500);  
  tone(piezzo,NOTE_F4, 375);  
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_A4, 650); 
  delay(650);
  compteur = 0;
}


//******* Pirate des caraïbes ****************
void Pirate()
{  
  tone(piezzo,NOTE_E4, 125);
  tone(piezzo,NOTE_G4, 125);
  tone(piezzo,NOTE_A4, 250);
  tone(piezzo,NOTE_A4, 125);
  delay(50); 
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_B4, 125); 
  tone(piezzo,NOTE_C5, 250); 
  tone(piezzo,NOTE_C5, 125);
  delay(50);
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_D5, 125);
  tone(piezzo,NOTE_B4, 250);
  tone(piezzo,NOTE_B4, 125);
  delay(50);
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_G4, 125);
  tone(piezzo,NOTE_A4, 375);
  delay(50);  
  tone(piezzo,NOTE_E4, 125);
  tone(piezzo,NOTE_G4, 125);
  tone(piezzo,NOTE_A4, 250);
  tone(piezzo,NOTE_A4, 125);
  delay(50);
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_B4, 125);
  tone(piezzo,NOTE_C5, 250);
  tone(piezzo,NOTE_C5, 125);
  delay(50);
  tone(piezzo,NOTE_C5,125); 
  tone(piezzo,NOTE_D5, 125);
  tone(piezzo,NOTE_B4, 250);
  tone(piezzo,NOTE_B4, 125);
  delay(50);
  tone(piezzo,NOTE_A4, 125); 
  tone(piezzo,NOTE_G4, 125);
  tone(piezzo,NOTE_A4, 375);
  delay(50);    
  tone(piezzo,NOTE_E4, 125);
  tone(piezzo,NOTE_G4, 125);
  tone(piezzo,NOTE_A4, 250);
  tone(piezzo,NOTE_A4, 125);
  delay(50);
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_D5, 250);
  tone(piezzo,NOTE_D5, 125);
  delay(50);
  tone(piezzo,NOTE_D5, 125); 
  tone(piezzo,NOTE_E5, 125);
  tone(piezzo,NOTE_F5,250);
  tone(piezzo,NOTE_F5, 125);
  delay(50);
  tone(piezzo,NOTE_E5, 125); 
  tone(piezzo,NOTE_D5, 125);
  tone(piezzo,NOTE_E5, 125);
  tone(piezzo,NOTE_A4, 250);
  delay(50);  
  tone(piezzo,NOTE_A4,125); 
  tone(piezzo,NOTE_B4, 125);
  tone(piezzo,NOTE_C5, 250);
  tone(piezzo,NOTE_C5, 125);
  delay(50);
  tone(piezzo,NOTE_D5, 250);
  tone(piezzo,NOTE_E5, 125);
  tone(piezzo,NOTE_A4, 250);
  delay(50);
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_B4, 250);
  tone(piezzo,NOTE_B4, 125);
  delay(50);
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_B4, 375);
  delay(200);
  tone(piezzo,NOTE_A4, 250); 
  tone(piezzo,NOTE_A4, 125);     
  tone(piezzo,NOTE_E4, 125);
  tone(piezzo,NOTE_G4, 125);
  tone(piezzo,NOTE_A4, 250);
  tone(piezzo,NOTE_A4, 125);
  delay(50); 
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_B4, 125); 
  tone(piezzo,NOTE_C5, 250); 
  tone(piezzo,NOTE_C5, 125);
  delay(50);
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_D5, 125);
  tone(piezzo,NOTE_B4, 250);
  tone(piezzo,NOTE_B4, 125);
  delay(50);
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_G4, 125);
  tone(piezzo,NOTE_A4, 375);
  delay(50);  
  tone(piezzo,NOTE_E4, 125);
  tone(piezzo,NOTE_G4, 125);
  tone(piezzo,NOTE_A4, 250);
  tone(piezzo,NOTE_A4, 125);
  delay(50);
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_B4, 125);
  tone(piezzo,NOTE_C5, 250);
  tone(piezzo,NOTE_C5, 125);
  delay(50);
  tone(piezzo,NOTE_C5,125); 
  tone(piezzo,NOTE_D5, 125);
  tone(piezzo,NOTE_B4, 250);
  tone(piezzo,NOTE_B4, 125);
  delay(50);
  tone(piezzo,NOTE_A4, 125); 
  tone(piezzo,NOTE_G4, 125);
  tone(piezzo,NOTE_A4, 375);
  delay(50);    
  tone(piezzo,NOTE_E4, 125);
  tone(piezzo,NOTE_G4, 125);
  tone(piezzo,NOTE_A4, 250);
  tone(piezzo,NOTE_A4, 125);
  delay(50);
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_D5, 250);
  tone(piezzo,NOTE_D5, 125);
  delay(50);
  tone(piezzo,NOTE_D5, 125); 
  tone(piezzo,NOTE_E5, 125);
  tone(piezzo,NOTE_F5, 250);
  tone(piezzo,NOTE_F5, 125);
  delay(50);
  tone(piezzo,NOTE_E5, 125); 
  tone(piezzo,NOTE_D5, 125);
  tone(piezzo,NOTE_E5, 125);
  tone(piezzo,NOTE_A4, 250);
  delay(50);  
  tone(piezzo,NOTE_A4,125); 
  tone(piezzo,NOTE_B4, 125);
  tone(piezzo,NOTE_C5, 250);
  tone(piezzo,NOTE_C5, 125);
  delay(50);
  tone(piezzo,NOTE_D5, 250);
  tone(piezzo,NOTE_E5, 125);
  tone(piezzo,NOTE_A4, 250);
  delay(50);
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_B4, 250);
  tone(piezzo,NOTE_B4, 125);
  delay(50);
  tone(piezzo,NOTE_C5, 125);
  tone(piezzo,NOTE_A4, 125);
  tone(piezzo,NOTE_B4, 375);
  delay(200);
  tone(piezzo,NOTE_E5, 250);
  delay(400);
  tone(piezzo,NOTE_F5, 250);
  delay(400); 
  tone(piezzo,NOTE_E5, 125);
  tone(piezzo,NOTE_E5, 125);
  delay(50);
  tone(piezzo,NOTE_G5, 125);
  delay(50);
  tone(piezzo,NOTE_E5, 125);  
  tone(piezzo,NOTE_D5, 125);
  delay(400);    
  tone(piezzo,NOTE_D5, 250);
  delay(400);
  tone(piezzo,NOTE_C5, 250);
  delay(400);  
  tone(piezzo,NOTE_B4, 125);  
  tone(piezzo,NOTE_C5, 125);
  delay(50);
  tone(piezzo,NOTE_B4, 125);
  delay(50);
  tone(piezzo,NOTE_A4,  500);    
  tone(piezzo,NOTE_E5, 250);  
  delay(400);
  tone(piezzo,NOTE_F5, 250);
  delay(400);    
  tone(piezzo,NOTE_E5, 125);
  tone(piezzo,NOTE_E5, 125);
  delay(50);
  tone(piezzo,NOTE_G5, 125);
  delay(50);
  tone(piezzo,NOTE_E5, 125);
  tone(piezzo,NOTE_D5, 125);
  delay(400);  
  tone(piezzo,NOTE_D5, 250);
  delay(400);
  tone(piezzo,NOTE_C5, 250);
  delay(400);  
  tone(piezzo,NOTE_B4, 125);
  tone(piezzo,NOTE_C5, 125);
  delay(50);
  tone(piezzo,NOTE_B4, 125);
  delay(50);
  tone(piezzo,NOTE_A4, 500);
  compteur = 0;
}


//******* McGyver ****************
void McGyver()
{
  tone(piezzo,NOTE_B4, 200);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 400);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_B4, 200);
  delay(200);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_B4, 400);
  delay(200);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 400);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_B4, 200);
  delay(200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_D6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_D6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_B4, 200);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 400);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_B4, 200);
  delay(200);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_B4, 400);
  delay(200);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 400);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_B4, 200);
  delay(200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_D6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_D6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_B5, 400);
  delay(200);
  tone(piezzo,NOTE_B5, 800);
  delay(200);
  tone(piezzo,NOTE_B5, 400);
  delay(200);
  tone(piezzo,NOTE_A5, 400);
  tone(piezzo,NOTE_D6, 600);
  tone(piezzo,NOTE_B5, 400);
  delay(200);
  tone(piezzo,NOTE_B5, 800);
  delay(200);
  tone(piezzo,NOTE_B5, 200);
  delay(200);
  tone(piezzo,NOTE_A5, 800);
  delay(400);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_B5, 800);
  delay(100);
  tone(piezzo,NOTE_FS5, 200);
  tone(piezzo,NOTE_A5, 200);
  delay(200);
  tone(piezzo,NOTE_G5, 800);
  delay(200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_C6, 200);
  delay(200);
  tone(piezzo,NOTE_B5, 400);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_G5, 200);
  delay(200);
  tone(piezzo,NOTE_E6, 400);
  tone(piezzo,NOTE_A5, 800);
  delay(100);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_C6, 200);
  delay(200);
  tone(piezzo,NOTE_B5, 800);
  delay(200);
  tone(piezzo,NOTE_FS5, 200);
  tone(piezzo,NOTE_A5, 200);
  delay(200);
  tone(piezzo,NOTE_G5, 800);
  delay(200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_C6, 200);
  delay(200);
  tone(piezzo,NOTE_B5, 400);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_G5, 200);
  delay(200);
  tone(piezzo,NOTE_E6, 400);
  tone(piezzo,NOTE_A5, 800);
  tone(piezzo,NOTE_B5, 800);
  delay(50);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_C6, 400);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_D6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_D6, 400);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_E6, 400);
  tone(piezzo,NOTE_D6, 200);
  tone(piezzo,NOTE_E6, 200);
  tone(piezzo,NOTE_FS6, 400);
  tone(piezzo,NOTE_B5, 400);
  tone(piezzo,NOTE_G6, 400);
  delay(200);
  tone(piezzo,NOTE_FS6, 400);
  tone(piezzo,NOTE_F6, 400);
  tone(piezzo,NOTE_B5, 400);
  tone(piezzo,NOTE_G6, 200);
  tone(piezzo,NOTE_E6, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_FS6, 200);
  tone(piezzo,NOTE_D6, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_E6, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_G5, 200);
  tone(piezzo,NOTE_D6, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_G5, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_E5, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_D5, 200);
  tone(piezzo,NOTE_C6, 200);
  tone(piezzo,NOTE_B5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_G5, 200);
  tone(piezzo,NOTE_AS5, 400);
  tone(piezzo,NOTE_A5, 400);
  tone(piezzo,NOTE_G6, 200);
  tone(piezzo,NOTE_G5, 200);
  tone(piezzo,NOTE_D6, 200);
  tone(piezzo,NOTE_G5, 200);
  tone(piezzo,NOTE_DS6, 200);
  tone(piezzo,NOTE_DS5, 200);
  tone(piezzo,NOTE_AS5, 200);
  tone(piezzo,NOTE_A5, 200);
  tone(piezzo,NOTE_G5, 200);
  tone(piezzo,NOTE_G4, 200);
  tone(piezzo,NOTE_D5, 200);
  tone(piezzo,NOTE_G4, 200);
  tone(piezzo,NOTE_DS5, 200);
  tone(piezzo,NOTE_G4, 200);
  tone(piezzo,NOTE_AS4, 200);
  tone(piezzo,NOTE_A4, 200);
  tone(piezzo,NOTE_G4, 200);
  tone(piezzo,NOTE_G4, 200);
  tone(piezzo,NOTE_G4, 200);
  tone(piezzo,NOTE_G4, 200);
  tone(piezzo,NOTE_G4, 200);
  tone(piezzo,NOTE_G4, 200);
  tone(piezzo,NOTE_G4, 200);
  delay(200);
  compteur = 0;
}


//******* BarbieGirl ****************
void BarbieGirl()
{
  tone(piezzo,NOTE_GS5, 240);
  tone(piezzo,NOTE_E5, 240);
  tone(piezzo,NOTE_GS5, 240);
  tone(piezzo,NOTE_CS6, 240);
  tone(piezzo,NOTE_A5, 480);
  delay(480);
  tone(piezzo,NOTE_FS5, 240);
  tone(piezzo,NOTE_DS5, 240);
  tone(piezzo,NOTE_FS5, 240);
  tone(piezzo,NOTE_B5, 240);
  tone(piezzo,NOTE_GS5, 480);
  tone(piezzo,NOTE_FS5, 240);
  tone(piezzo,NOTE_E5, 240);
  delay(480);
  tone(piezzo,NOTE_E5, 240);
  tone(piezzo,NOTE_CS5, 240);
  tone(piezzo,NOTE_FS5, 480);
  tone(piezzo,NOTE_CS5, 480);
  delay(480);
  tone(piezzo,NOTE_FS5, 240);
  tone(piezzo,NOTE_E5, 240);
  tone(piezzo,NOTE_GS5, 480);
  tone(piezzo,NOTE_FS5, 480);
  compteur = 0;
}


//******* James Bond *******************

void Bond()
{
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_DS6, 93);
  tone(piezzo,NOTE_DS6, 93);
  tone(piezzo,NOTE_DS6, 187);
  tone(piezzo,NOTE_DS6, 375);
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_E6, 93);
  tone(piezzo,NOTE_E6, 93);
  tone(piezzo,NOTE_E6, 187);
  tone(piezzo,NOTE_E6, 375);
  tone(piezzo,NOTE_DS6, 187);
  tone(piezzo,NOTE_DS6, 187);
  tone(piezzo,NOTE_DS6, 187);
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_DS6, 93);
  tone(piezzo,NOTE_DS6, 93);
  tone(piezzo,NOTE_DS6, 187);
  tone(piezzo,NOTE_DS6, 375);
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_E6, 93);
  tone(piezzo,NOTE_E6, 93);
  tone(piezzo,NOTE_E6, 187);
  tone(piezzo,NOTE_E6, 375);
  tone(piezzo,NOTE_DS6, 187);
  tone(piezzo,NOTE_D6, 187);
  tone(piezzo,NOTE_CS6, 187);
  tone(piezzo,NOTE_CS7, 187);
  tone(piezzo,NOTE_C7, 1125);
  tone(piezzo,NOTE_GS6, 187);
  tone(piezzo,NOTE_FS6, 187);
  tone(piezzo,NOTE_GS6, 1125);
  compteur = 0;
}


//********danse***********

void dance(){
  primera_parte();
  segunda_parte();
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  primera_parte(); 
  crusaito(1,t*8);
  crusaito(1,t*7);

  for (int i=0; i<16; i++){
    flapping(1,t/4);
    delay(3*t/4);
  }
 
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);

  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  kickLeft(t);
  kickRight(t);
  drunk(t*8);
  drunk(t*4);
  drunk(t/2);
  delay(t*4); 

  drunk(t/2);

  delay(t*4); 
  walk(2,t*2);
  backyard(2,t*2);
  goingUp(t*2);
  goingUp(t*1);
  noGravity(t*2);
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*3);

  delay(t);
  primera_parte();
    for (int i=0; i<32; i++){
    flapping(1,t/2);
    delay(t/2);
  }
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
}




////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////FUNCIONES DE CONTROL//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T, double phase_diff[N_SERVOS]){
  for (int i=0; i<4; i++) {
    servo[i].SetO(O[i]);
    servo[i].SetA(A[i]);
    servo[i].SetT(T);
    servo[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<4; i++){
        servo[i].refresh();
     }
  }
}

unsigned long final_time;
unsigned long interval_time;
int oneTime;
int iteration;
float increment[N_SERVOS]; 
int oldPosition[]={90,90,90,90};

void moveNServos(int time, int  newPosition[]){
  for(int i=0;i<N_SERVOS;i++)  increment[i] = ((newPosition[i])-oldPosition[i])/(time/INTERVALTIME);
  
  final_time =  millis() + time; 
  
  iteration = 1; 
  while(millis() < final_time){ //Javi del futuro cambia esto  
      interval_time = millis()+INTERVALTIME;  
      
      oneTime=0;      
      while(millis()<interval_time){    
          if(oneTime<1){ 
              for(int i=0;i<N_SERVOS;i++){
                  servo[i].SetPosition(oldPosition[i] + (iteration * increment[i]));
              }     
              iteration++;
              oneTime++;
          }
      }     
  }   

  for(int i=0;i<N_SERVOS;i++){  
    oldPosition[i] = newPosition[i];
  }   
}


//////////////////////////////////////////////////////////////////////////////
////////////////////////////////PASOS DE BAILE////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void goingUp(int tempo){
  
      pause=millis();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
      delay(tempo);
      servo[0].SetPosition(80);
      servo[1].SetPosition(100);
      delay(tempo);
      servo[0].SetPosition(70);
      servo[1].SetPosition(110);
      delay(tempo);
      servo[0].SetPosition(60);
      servo[1].SetPosition(120);
      delay(tempo);
      servo[0].SetPosition(50);
      servo[1].SetPosition(130);
      delay(tempo);
      servo[0].SetPosition(40);
      servo[1].SetPosition(140);
      delay(tempo);
      servo[0].SetPosition(30);
      servo[1].SetPosition(150);
      delay(tempo);
      servo[0].SetPosition(20);
      servo[1].SetPosition(160);
      delay(tempo);
      
      while(millis()<pause+8*t);

}

void primera_parte(){
  
  int move1[4] = {60,120,90,90};
  int move2[4] = {90,90,90,90};
  int move3[4] = {40,140,90,90};
  
  for(int x=0; x<3; x++){
    for(int i=0; i<3; i++){
      lateral_fuerte(1,t/2);
      lateral_fuerte(0,t/4);
      lateral_fuerte(1,t/4);
      delay(t);
    }
  
    pause=millis();
    for(int i=0;i<4;i++) servo[i].SetPosition(90);
    moveNServos(t*0.4,move1);
    moveNServos(t*0.4,move2);
    while(millis()<(pause+t*2));
  }
  
  for(int i=0; i<2; i++){
    lateral_fuerte(1,t/2);
    lateral_fuerte(0,t/4);
    lateral_fuerte(1,t/4);
    delay(t);
  }
    
  pause=millis();
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  crusaito(1,t*1.4);
  moveNServos(t*1,move3);
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  while(millis()<(pause+t*4));
}

void segunda_parte(){
  
  int move1[4] = {90,90,80,100};
  int move2[4] = {90,90,100,80};
  int move3[4] = {90,90,80,100};
  int move4[4] = {90,90,100,80};
    
  int move5[4] = {40,140,80,100};
  int move6[4] = {40,140,100,80};
  int move7[4] = {90,90,80,100};
  int move8[4] = {90,90,100,80};
       
  int move9[4] = {40,140,80,100};
  int move10[4] = {40,140,100,80};
  int move11[4] = {90,90,80,100};
  int move12[4] = {90,90,100,80};
  
  for(int x=0; x<7; x++){ 
    for(int i=0; i<3; i++){
      pause=millis();
      moveNServos(t*0.15,move1);
      moveNServos(t*0.15,move2);
      moveNServos(t*0.15,move3);
      moveNServos(t*0.15,move4);
      while(millis()<(pause+t));
    }
    pause=millis();
    moveNServos(t*0.15,move5);
    moveNServos(t*0.15,move6);
    moveNServos(t*0.15,move7);
    moveNServos(t*0.15,move8);
    while(millis()<(pause+t));
  }
 
  for(int i=0; i<3; i++){
    pause=millis();
    moveNServos(t*0.15,move9);
    moveNServos(t*0.15,move10);
    moveNServos(t*0.15,move11);
    moveNServos(t*0.15,move12);
    while(millis()<(pause+t));
  }
}

void lateral_fuerte(boolean side, int tempo){
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  if (side) servo[0].SetPosition(40);
  else servo[1].SetPosition(140);
  delay(tempo/2);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo/2);

}

void drunk (int tempo){
  
  pause=millis();
  
  int move1[] = {60,70,90,90};
  int move2[] = {110,120,90,90};
  int move3[] = {60,70,90,90};
  int move4[] = {110,120,90,90};
  
  moveNServos(tempo*0.235,move1);
  moveNServos(tempo*0.235,move2);
  moveNServos(tempo*0.235,move3);
  moveNServos(tempo*0.235,move4);
  while(millis()<(pause+tempo));

}


void noGravity(int tempo){
  
  int move1[4] = {120,140,90,90};
  int move2[4] = {140,140,90,90};
  int move3[4] = {120,140,90,90};
  int move4[4] = {90,90,90,90};
  
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  for(int i=0;i<N_SERVOS;i++) oldPosition[i]=90;
  moveNServos(tempo*2,move1);
  moveNServos(tempo*2,move2);
  delay(tempo*2);
  moveNServos(tempo*2,move3);
  moveNServos(tempo*2,move4);

 

}

void kickLeft(int tempo){
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
}

void kickRight(int tempo){
for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(80); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}

void walk(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void run(int steps, int T){
    int A[4]= {10, 10, 10, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyard(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyardSlow(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}


void turnLeft(int steps, int T){
    int A[4]= {20, 20, 10, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void turnRight(int steps, int T){
    int A[4]= {20, 20, 30, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkRight(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15 ,15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkLeft(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void crusaito(int steps, int T){
    int A[4]= {25, 25, 30, 30};
    int O[4] = {- 15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void swing(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(180), DEG2RAD(0), DEG2RAD(270), DEG2RAD(270)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void flapping(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0], A[1], 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void test(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0] + 10, A[1] - 10, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
