Skip to content
Search or jump to…
Pull requests
Issues
Marketplace
Explore
 
@stanWi14 
stanWi14
/
ExpoBot
Private
Code
Issues
Pull requests
Actions
Projects
Security
Insights
Settings
ExpoBot/ExpoBot.ino
@stanWi14
stanWi14 Initial commit
Latest commit e307353 in 10 days
 History
 1 contributor
181 lines (172 sloc)  4.64 KB

/*if you want to see the circuit and try this code visit the link below
https://www.tinkercad.com/things/7uJppjnDqGJ
*/
/*So this fun project was made to 
 entertain new student ( freshmen)
 at my university, we build a moving/kinda 
 interactive robot with arduino and a servo to let them know
 about our Internet of Things major
 If you guys interested to see the looks of the robot
 you can find it in another folder
 Thanks
*/

#include <Servo.h>
#define echoPin 2 
#define trigPin 3 
// Declaring variable for servos
// we using 2 servo, for the servo variable we are going to use an array
// servo[1] for the mouth servo
// servo[2] fot the neck servo
Servo servo[3];
int mouth= 13, neck=12;
int pos = 0;
int start =0 ;
int done =0;
int count =0;

//declaring variable for Ultrasonic Sensor
long dur; //duration variable
float dis; //distance variable


// This is function that are going to be used in this project
void moveservo (int start, int done, int num,int sped); // for sweep open a servo
void backservo (int start, int done, int num,int sped);
void openmouth(int sped,int done); // open mouth
void closemouth(int sped,int start);//close mouth
void leftneck(int sped); // move nect to left
void rightneck (int sped); // move neck to right
float takedis(); // for take and counting mean from ultrasonic sensor
void startpos(); // starting position
void hello(); // welcoming left and right
void confuse(); // angry state because too many guess :D

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); // serial monitor used as a sign for accuracy for the code logic/algorithm
  servo[1].attach(mouth); // array servo[1] for mouth servo (moving vertical)
  servo[2].attach(neck); // array servo[2] for neck servo (moving horizontal)
  //ready sign
  servo[1].write(90); 
  servo[2].write(90);
  delay(1000);
  servo[1].write(0);
}

void loop() {
  // Call the take mean distance function
  float detect =takedis();
  if(count < 5){  // we use count for the confuse function
    if( detect < 100){  // if there is people in 5 cm radius than robot do hello function
    // to see the distance measurement
    Serial.print("Distance: ");
    Serial.print(detect);
    Serial.println(" cm");
    hello();
    servo[1].write(90);
    delay(1000);
    servo[1].write(0);
    count++; //count+1
    }else{
      startpos(); // if not detected, than it's in his start position
    } 
  }else{
    // this code is for if already hello() for 5 times, then
    //the robot is going to be confuse/tired/anggry and do confuse()
    Serial.println("Tired: ");
    confuse();
    delay(1000);
    count =0; // after it reset count to 0 again
  }
}

// take distance function, 20 time measure because it's not to accurate
float takedis(){
  dis =0;
  for(int i=0;i<20;i++){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    dur = pulseIn(echoPin, HIGH);
    float cek = (float)dur * 0.034 / 20; 
    dis += cek;
  }
  return dis/20;
}
//sweeping open servo
void moveservo (int start, int done, int num,int sped){
  for (pos = start; pos <= done; pos += 1) {
    servo[num].write(pos);
    delay(sped);
  }
}
//sweeping close servo
void backservo (int done, int start, int num,int sped){
  for (pos = done; pos >= start; pos -= 1) {
    servo[num].write(pos);
    delay(sped);
  }
}
void openmouth(int sped,int done){
  //Serial.println("Buka mouth");
  int start=0;
  moveservo(start,done,1,sped);
}

void closemouth(int sped,int start){
  //Serial.println("Tutup mouth");
  int done = 0;
  backservo (start,done,1,sped);
}
void moveleft(int start,int done,int sped){
  Serial.println("Putar kiri");
  backservo (start,done,2,sped);
}
void moveright (int start,int done,int sped){
  Serial.println("Putar kanan");
  moveservo (start,done,2,sped);
}
void startpos(){
  Serial.print(".");
  servo[1].write(0);
  servo[2].write(90);
}
void hello(){
  Serial.println("Sapa sapa");
  moveright(90,150,30);
  int wide = 85;
  for(int i=0;i<3;i++){
   openmouth(5,wide);
   closemouth(5,wide); 
   wide-=10;
  }
  moveleft(150,90,30);
  wide = 85;
  for(int i=0;i<3;i++){
   openmouth(5,wide);
   closemouth(5,wide); 
   wide-=10;
  }
  moveleft(90,30,30);
  wide = 85;
  for(int i=0;i<3;i++){
   openmouth(5,wide);
   closemouth(5,wide); 
   wide-=10;
  }
  moveright(30,90,30);
}

void confuse(){
  servo[1].write(100);
  delay(1000);
  servo[1].write(10);
  servo[2].write(90);
  servo[2].write(150);
  delay(1000);
  servo[2].write(90);
  servo[2].write(30);
  delay(1000);
  servo[2].write(90);
  servo[1].write(90);
  delay(1000);
  servo[1].write(0);
   servo[1].write(90);
  delay(1000);
  servo[1].write(0);
}
Footer
© 2022 GitHub, Inc.
Footer navigation
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
