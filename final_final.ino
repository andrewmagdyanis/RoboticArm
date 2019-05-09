#include <Servo.h>

#define rx0 0
#define tx0 1

#define rx1 19
#define tx1 18

char c[10] ;
char c1[10] ;
int j = 0;

Servo servo;
 
int pos = 0;  // Stores the position (angle) of the servo. Range is [0, 180].
int pos1 = 0; // Stores the position (angle) of the DC motor 1. Range is [0, 360].
int pos2 = 0; // Stores the position (angle) of the DC motor 2. Range is [0, 360].

int enA = 3;
int in1 = 5;
int in2 = 9;
int enB = 6;
int in3 = 11;
int in4 = 12;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  servo.attach(10);  // Attaches the servo on pin 9 to the servo object.
  servo.write(0);  // Resets the position.

  // DC motor control pins --> output :
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(tx0, OUTPUT);
  pinMode(rx0, INPUT);

  pinMode(tx1, OUTPUT);
  pinMode(rx1, INPUT);

  Serial.write("0,0,0,");
  Serial.println();
}

void loop() {

if (Serial1.available()) {  // Returns true if there is serial input.
   
    char ch = Serial1.read();
    //servo motor clockwise
    switch (ch) {
    case 'e' : 
      for (int i = 0; i <= 180; i++) { 
      // Make sure not to exceed the mechanical limitation.
      if (pos < 180) {
        pos += 1;
        servo.write(pos);
        Serial.print(pos2); Serial.print(","); Serial.print( pos1 ); Serial.print(","); Serial.print(pos); Serial.println();
        delay (100) ; 
        char ch = Serial1.read();
        if (ch == 's') {goto out ; }
      }
      }
    break ; 

   //servo motor anti clockwise
   case 'd' :
    for (int i = 0; i <= 180; i++) {
      // Make sure not to exceed the mechanical limitation.
      if (pos > 0) {
        pos -= 1;
        servo.write(pos);
        Serial.print(pos2); Serial.print(","); Serial.print( pos1 ); Serial.print(","); Serial.print(pos); Serial.println();
        delay (100) ;  
        char ch = Serial1.read();
        if (ch == 's') {goto out ; }
      }
      }
    break ; 

    //DC motor 1 clockwise
    case 'w' :
    for (int i = 0; i <= 360; i++) {
     pos1 = pos1 + (i) ;
     motor_1_forward ();
     Serial.print(pos2); Serial.print(","); Serial.print( pos1 ); Serial.print(","); Serial.print(pos); Serial.println();
     delay (30) ;  
     char ch = Serial1.read();
     if (ch == 's') {motor_1_break (); goto out ; }  
    }
    break ;

    //DC motor 1 anti clockwise
    case 'q' :
    for (int i = 0; i <= 360; i++) {
     pos1 = pos1 - (i) ;
     motor_1_backword ();
     Serial.print(pos2); Serial.print(","); Serial.print( pos1 ); Serial.print(","); Serial.print(pos); Serial.println();
     delay (30) ;  
     char ch = Serial1.read();
     if (ch == 's') {motor_1_break (); goto out ; }  
    }
    break ;

    //DC motor 2 clockwise
    case 'v' :
    for (int i = 0; i <= 360; i++) {
     pos2 = pos2 - i ;
     motor_2_forward();
     Serial.print(pos2); Serial.print(","); Serial.print( pos1 ); Serial.print(","); Serial.print(pos); Serial.println();
     delay (20) ;  
     char ch = Serial1.read();
     if (ch == 's') {motor_2_break (); goto out ; }  
    }
    break ;

    //DC motor 2 anti clockwise
    case 'c' : 
    for (int i = 0; i <= 360; i++) {
     pos2 = pos2 + i ;
     motor_2_backword ();
     Serial.print(pos2); Serial.print(","); Serial.print( pos1 ); Serial.print(","); Serial.print(pos); Serial.println();
     delay (20) ;  
     char ch = Serial1.read();
     if (ch == 's') {motor_2_break (); goto out ; }  
    }
    break ;
    
    out :
   
    delay(50);
  }

}
}

void motor_1_forward () {
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Set speed to 100 out of possible range 0~255

  analogWrite(enA, 120);
}


void motor_1_backword () {
  // Turn on Motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set speed to 100 out of possible range 0~255

  analogWrite(enA, 120);
}

void motor_1_break () {
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  // Set speed to 100 out of possible range 0~255

  analogWrite(enA, 255);
}

void motor_2_forward(){
  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  // Set speed to 100 out of possible range 0~255

  analogWrite(enB, 100);
}


void motor_2_backword () {
  
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  // Set speed to 100 out of possible range 0~255

  analogWrite(enB, 100);
}

void motor_2_break () {
  // Turn on Motor A
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  // Set speed to 100 out of possible range 0~255

  analogWrite(enB, 255);
}
