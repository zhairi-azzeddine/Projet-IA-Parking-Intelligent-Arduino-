#include <Servo.h> //includes the servo library
#include <Wire.h> 
#include <LCD.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //définit les broches que l'Arduino utilise pour se connecter à l'écran LCD. 
                                                               //Vous pouvez utiliser n'importe quelle broche numérique d'Arduino pour contrôler l'écran LCD. De plus, dans cette fonction, 
                                                               //vous devez spécifier le nom de votre module LCD, dans ce cas, le nom est LCD.
                                                               //// initialize the library with the numbers of the interface pins 

Servo myservo;

#define ir_enter 2 // donner un nom à une valeur constante avant que le programme ne soit compilé
#define ir_back  4

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
#define ir_car5 9
#define ir_car6 10

int S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;
int flag1=0, flag2=0; 
int slot = 6;  

void setup(){
Serial.begin(9600); //La bibliothèque Serial (incluse dans le langage Arduino) est utilisée pour les communications séries asynchrones basées sur le circuit UART. Ce circuit utilise des ports numériques de la carte 

pinMode(ir_car1, INPUT); //permet de configurer le comportement (entrée ou sortie) de la broche passée en paramètre
pinMode(ir_car2, INPUT); //Exemple : pinMode(13, OUTPUT); digitalWrite(pin, value) : écrit une valeur (HIGH ou LOW) sur une broche configurée en tant que sortie (OUTPUT). Exemple : digitalWrite(13, HIGH);
pinMode(ir_car3, INPUT);
pinMode(ir_car4, INPUT);
pinMode(ir_car5, INPUT);
pinMode(ir_car6, INPUT);

pinMode(ir_enter, INPUT);
pinMode(ir_back, INPUT);
  
myservo.attach(3); //Attache un objet de type Servo à une broche
myservo.write(90);

lcd.begin(20, 4);  
lcd.setCursor (0,1);
lcd.print("    CIT Parking  ");
lcd.setCursor (0,2);
lcd.print("    Intelligent     ");
delay (2000); //permet de suspendre l'exécution de votre programme Arduino pendant une période déterminée
lcd.clear();   

Read_Sensor();

int total = S1+S2+S3+S4+S5+S6; //calculer le totatl de places et les place vide
slot = slot-total; 
}

void loop(){

Read_Sensor();

lcd.setCursor (0,0);
lcd.print("   Places : "); 
lcd.print(slot);
lcd.print("    ");  

lcd.setCursor (0,1); //Un curseur est un indicateur mobile sur l'écran LCD qui définit la position à partir de laquelle le texte doit être affiché sur l'écran LCD où l'écran LCD est un appareil qui est interfacé avec Arduino pour afficher la sortie.
if(S1==1){lcd.print("P1:Fill ");}
     else{lcd.print("P1:vide");}

lcd.setCursor (10,1);
if(S2==1){lcd.print("P2:Fill ");}
     else{lcd.print("P2:vide");}

lcd.setCursor (0,2);
if(S3==1){lcd.print("P3:Fill ");}
     else{lcd.print("P3:vide");}

lcd.setCursor (10,2);
if(S4==1){lcd.print("P4:Fill ");}
     else{lcd.print("P4:vide");}

 lcd.setCursor (0,3);
if(S5==1){lcd.print("P5:Fill ");}
     else{lcd.print("P5:vide");}

lcd.setCursor (10,3);
if(S6==1){lcd.print("P6:Fill ");}
     else{lcd.print("P6:vide");}    

if(digitalRead (ir_enter) == 0 && flag1==0){
if(slot>0){flag1=1;
if(flag2==0){myservo.write(180); slot = slot-1;}
}else{
lcd.setCursor (0,0);
lcd.print(" Parking Plein ");  
delay(1500);
}   
}

if(digitalRead (ir_back) == 0 && flag2==0){flag2=1;
if(flag1==0){myservo.write(180); slot = slot+1;}
}

if(flag1==1 && flag2==1){
delay (1000);
myservo.write(90);
flag1=0, flag2=0;
}

delay(1);
}

void Read_Sensor(){
S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;

if(digitalRead(ir_car1) == 0){S1=1;}  //Le digitalRead permet d'écouter les informations que va recevoir la carte Arduino. 
if(digitalRead(ir_car2) == 0){S2=1;}  //Elle est très utile pour savoir si on a appuyé sur un bouton poussoir par exemple. 
if(digitalRead(ir_car3) == 0){S3=1;}  //Le digitalRead va informer la carte Arduino si il y a de la tension dans la broche
if(digitalRead(ir_car4) == 0){S4=1;}
if(digitalRead(ir_car5) == 0){S5=1;}
if(digitalRead(ir_car6) == 0){S6=1;}  
}
