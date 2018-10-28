#include <avr/io.h>
#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

#define PWMPin 10


int PUL1=7; //define Pulse pin
int DIR1=6; //define Direction pin
int ENA1=5; //define Enable Pin

int PUL2=4; //define Pulse pin
int DIR2=3; //define Direction pin
int ENA2=2; //define Enable Pin
int a=1;


/*音階の設定*/
#define  C1  33
#define Cx1 35
#define D1  37
#define Dx1 39
#define E1  41
#define F1  44
#define Fx1 46
#define G1  49
#define Gx1 52
#define a1  55
#define ax1 58
#define b1  62
#define C2  65
#define Cx2 69
#define D2  73
#define Dx2 78
#define E2  82
#define F2  87
#define Fx2 92
#define G2  98
#define Gx2 104
#define a2  110
#define ax2 117
#define b2  123
#define C3  131
#define Cx3 139
#define D3  147
#define Dx3 156
#define E3  165
#define F3  175
#define Fx3 185
#define G3  196
#define Gx3 208
#define a3  220
#define ax3 233
#define b3  247
#define C4  262
#define Cx4 277
#define D4  294
#define Dx4 311
#define E4  330
#define F4 349
#define Fx4 370
#define G4  392
#define Gx4 415
#define a4  440
#define ax4 466
#define b4  494
#define C5  523
#define Cx5 554
#define D5  587
#define Dx5 622
#define E5  659
#define F5  698
#define Fx5 740
#define G5  784
#define Gx5 831
#define a5  880
#define ax5 932
#define b5  988
#define C6  1047
#define Cx6 1109
#define D6  1175
#define Dx6 1245
#define E6  1319
#define F6  1397
#define Fx6 1480
#define G6  1568
#define Gx6 1661
#define a6  1760
#define ax6 1865
#define b6  1976
#define C7  2093
#define Cx7 2217
#define D7  2349
#define Dx7 2489
#define E7  2637
#define F7  2794
#define Fx7 2960
#define G7  3136
#define Gx7 3322
#define a7  3520
#define ax7 3729
#define b7  3951
#define C8  4186


/*荒城の月楽譜*/
unsigned int frq_kojo[24] = {E4, E4, a4, b4, C5, b4, a4, F4, F4, E4, Dx4, E4, E4, E4, a4, b4, C5, b4, a4, F4, D4, E4, E4, a3};     /*音程*/
float y_kojo[24]={4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 1.333333333, 4, 4, 4, 4, 4, 4, 2, 4, 4, 2.666666667, 8, 1.333333333 };       /*〇分音符*/
float z_kojo[24]={100, 0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 4, 100, 0, 0, 0, 0, 0, 0, 0, 0, 100, 0, 4};       /*休符{}*/

/*カエル楽譜*/
unsigned int frq_kaeru[29] = {C5, D5, E5, F5, E5, D5, C5,   E5, F5, G5, a5, G5, F5, E5,  C5, C5, C5, C5,   C5, C5, D5, D5,    E5, E5, F5, F5,    E5, D5, C5};     /*音程*/
float y_kaeru[29]={4, 4, 4, 4, 4, 4, 4,   4, 4, 4, 4, 4, 4, 4,   4, 4, 4, 4,    8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 4};       /*〇分音符*/
float z_kaeru[29]={0, 0, 0, 0, 0, 0, 2,   0, 0, 0, 0, 0, 0, 2,   4, 4, 4, 4,    100, 0, 100, 0, 100, 0, 100, 0, 0, 0, 4};       /*休符{}*/

float pitch=5;

float duty = 0.5; // 指定したいデューティ比

std_msgs::Int32 int_msg;
ros::Publisher chatter("chatter", &int_msg);

void messageCb( const std_msgs::Int32& toggle_msg) {
  if(toggle_msg.data <= 2){
      SetSquareWave_kojo(); 
      OCR1B = 0; 
      int_msg.data = 1;
      chatter.publish( &int_msg );
  }else if (toggle_msg.data > 2){
  SetSquareWave_kaeru(); 
  OCR1B = 0; 
  int_msg.data = 1;
  chatter.publish( &int_msg );
  }else{
  
  }
}

ros::Subscriber<std_msgs::Int32> sub("toggle_song", &messageCb );

void SetSquareWave_kojo()
{
    for(int j=0; j<24; j++)    /*楽譜の長さ*/
  {                   
      // TOP値指定
  OCR1A = (float)(1000000 / frq_kojo[j]);

  // Duty比指定
  OCR1B = (unsigned int)(1000000 / frq_kojo[j] * duty);

  delay(1/y_kojo[j]*1000*pitch);
   
  if(z_kojo[j] != 0)
  {
     OCR1B = 0;
     delay(1/z_kojo[j]*1000*pitch);
     }
  }
}

void SetSquareWave_kaeru()
{
    for(int j=0; j<29; j++)    /*楽譜の長さ*/
  {                   
      // TOP値指定
  OCR1A = (float)(1000000 / frq_kaeru[j]);

  // Duty比指定
  OCR1B = (unsigned int)(1000000 / frq_kaeru[j] * duty);

  delay(1/y_kaeru[j]*1000*pitch);
   
  if(z_kaeru[j] != 0)
  {
     OCR1B = 0;
     delay(1/z_kaeru[j]*1000*pitch);
     }
  }
}


void setup() {
  pinMode(PWMPin, OUTPUT);
  pinMode (PUL1, OUTPUT);
  pinMode (DIR1, OUTPUT);
  pinMode (ENA1, OUTPUT);
  pinMode (a, OUTPUT);

  pinMode (PUL2, OUTPUT);
  pinMode (DIR2, OUTPUT);
  pinMode (ENA2, OUTPUT);

  digitalWrite(a,HIGH);
  digitalWrite(DIR1,LOW);
  digitalWrite(ENA1,HIGH);

  digitalWrite(DIR2,HIGH);
  digitalWrite(ENA2,HIGH);

     // モード指定
  TCCR1A = 0b00100001;
  TCCR1B = 0b00010010;

//ROS
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
}


void loop() {
  nh.spinOnce();
  delay(1); 
}
