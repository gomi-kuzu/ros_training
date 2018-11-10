#include <avr/io.h>
#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

#define PWMPin4 45
#define PWMPin5 7


int ENA1=2; //define Enable Pin
int ENA2=50; //define Enable Pin


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



/*エリーゼ悲しい*/
unsigned short int frq_eli[95] =      {E5, Dx5, E5, Dx5, E5, b4, D5, C5, a4, C4, E4, a4, b4, E4, Gx4, b4, C5, E4, E5, Dx5, E5, Dx5, E5, b5, D5, C5, a4, C4, E4, a4, b4, E4, C5, b4, a4, a4, b4, C5, D5, E5, G4, F5, E5, D5, F4, E5, D5, C5, E4, D5, C5, b4, E4, E5, E5, E6, Dx5, E5, Dx5, E5, Dx5, E5, b4, D5, C5, a4, C4, E4, a4, b4, E4, Gx4, b4, C5, E4, E5, Dx5, E5, Dx5, E5, b5, D5, C5, a4, C4, E4, a4, b4, E4, C5, b4, a4, b4, C5, D5};     /*音程*/
unsigned short int frq_eli_high[95] = {E6, Dx6, E6, Dx6, E6, b5, D6, C6, a5, C5, E5, a5, b5, E5, Gx5, b5, C6, E5, E6, Dx6, E6, Dx6, E6, b6, D6, C6, a5, C5, E5, a5, b5, E5, C6, b5, a5, a5, b5, C6, D6, E6, G5, F6, E6, D6, F5, E6, D6, C6, E5, D6, C6, b5, E5, E6, E6, E7, Dx6, E6, Dx6, E6, Dx6, E6, b5, D6, C6, a5, C5, E5, a5, b5, E5, Gx5, b5, C6, E5, E6, Dx6, E6, Dx6, E6, b6, D6, C6, a5, C5, E5, a5, b5, E5, C6, b5, a5, b5, C6, D6};     /*音程*/
int y_eli[95]={16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16, 16, 8, 8, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16, 16, 8, 16, 16, 16};       /*〇分音符*/
int z_eli[95]={0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 0, 8, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 8, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 0} ;       /*休符{}*/
int pitch_eli=30;

/*darth badar怒り*/
unsigned short int frq_darth[66]={G3, G3, G3, Dx3, ax3, G3, Dx3, ax3, G3, D4, D4, D4, Dx4, a3, Fx3, Dx3, ax3, G3, G4, G3, G3, G4, Fx4, F4, E4, Dx4, E4, Gx3, Cx4, C4, b3, ax3, a3, ax3, Dx3, Fx3, Dx3, Fx3, ax3, G3, ax3, D4, G4, G3, G3, G4, Fx4, F4, E4, Dx4, E4, Gx3, Cx4, C4, b3, ax3, a3, ax3, Dx3, Fx3, Dx3, ax3, G3, Dx3, ax3, G3};
unsigned short int frq_darth_high[66]={G4, G4, G4, Dx4, ax4, G4, Dx4, ax4, G4, D5, D5, D5, Dx5, a4, Fx4, Dx4, ax4, G4, G5, G4, G4, G5, Fx5, F5, E5, Dx5, E5, Gx4, Cx5, C5, b4, ax4, a4, ax4, Dx4, Fx4, Dx4, Fx4, ax4, G4, ax4, D5, G4, G4, G4, G5, Fx5, F5, E5, Dx5, E5, Gx4, Cx5, C5, b4, ax4, a4, ax4, Dx4, Fx4, Dx4, ax4, G4, Dx4, ax4, G4};
int y_darth[66]={500, 500, 500, 375, 125, 500, 375, 125, 750, 500, 500, 500, 375, 125, 500, 375, 125, 750, 500, 125, 125, 500, 375, 125, 125, 125, 125, 125, 500, 375, 125, 125, 125, 125, 125, 500, 375, 125, 500, 375, 125, 750, 500, 125, 125, 500, 375, 125, 125, 125, 125, 125, 500, 375, 125, 125, 125, 125, 125, 500, 375, 125, 500, 375, 125, 750};
int z_darth[66]={10, 10, 0, 0, 0, 0, 0, 0, 250, 10, 10, 0, 0, 0, 0, 0, 0, 250, 0, 250, 0, 0, 0, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 500, 125, 0, 0, 0, 0, 0, 0, 250, 0, 250, 0, 0, 0, 0, 0, 0, 375, 125, 0, 0, 0, 0, 0, 375, 125, 0, 0, 0, 0, 0, 0, 0};
int pitch_darth=15;

/*exciting tomorrow無表情*/
unsigned short int frq_exciting[33]={a4 , a4 , D5 , b4 , G4 , G4 , C5 , G4 , a4 , a4 , a4 , D5 , b4 , D5 , D5 , C5 , C5 , C5 , E5 , D5 , C5 , a4 , a4 , D5 , b4 , D5 , D5 , C5 , C5 , C5 , E5 , D5 , C5};
unsigned short int frq_exciting_high[33]={a5 , a5 , D6, b5, G5 , G5 , C6, G5, a5 , a5 , a5 , D6, b5, D6 , D6 , C6 , C6 , C6 , E6, D6, C6, a5 , a5 , D6, b5, D6 , D6 , C6 , C6 , C6 , E6, D6, C6}; 
int y_exciting[33]={1500, 500, 500, 1250, 250, 250, 1250, 500, 2000, 1500, 500, 500, 1250, 250, 250, 1250, 250, 250, 250, 500, 1250, 1500, 500, 500, 1250, 250, 250, 1250, 250, 250, 250, 500, 1250};
int z_exciting[33]={10, 0, 0, 0, 10, 0, 0, 0, 10, 10, 0, 0, 0, 10, 0, 10, 10, 0, 0, 0, 0, 10, 0, 0, 0, 10, 0, 10, 10, 0, 0, 0, 0};
int pitch_exciting=10;

/*恋楽しい*/
unsigned short int frq_koi[52]={C4 , Dx4 , C4 , Dx4 , F4 , Dx4 , C4 , Gx3 , ax3 , C4 , C4 , Dx4 , C4 , Gx4 , G4 , F4 , Dx4 , F4 , Dx4 , Gx3 , ax3 , C4 , Dx4 , C4 , Dx4 , F4 , Dx4 , C4 , Gx3 , G4 , Gx4 , F4 , Dx4 , Dx4 , C4 , Dx4 , F4 , F4 , Dx4 , Dx4 , C4 , Dx4 , F4 , F4 , Dx4 , Dx4 , F4 , C4 , ax3 , Gx3 , F3 , Gx3 };
unsigned short int frq_koi_high[52]={C5, Dx5, C5, Dx5, F5, Dx5, C5, Gx4, ax4, C5 , C5 , Dx5, C5, Gx5, G5, F5, Dx5, F5, Dx5, Gx4, ax4, C5, Dx5, C5, Dx5, F5, Dx5, C5, Gx4, G5, Gx5, F5, Dx5 , Dx5 , C5, Dx5, F5 , F5 , Dx5 , Dx5 , C5, Dx5, F5, F5, Dx5 , Dx5, F5, C5, ax4, Gx4, F4, Gx4};
int y_koi[52]={240, 240, 240, 240, 479, 240, 240, 479, 479, 838, 240, 240, 240, 240, 479, 240, 240, 479, 479, 479, 479, 240, 240, 240, 240, 479, 240, 240, 479, 479, 719, 479, 240, 240, 240, 240, 479, 479, 240, 240, 240, 240, 479, 479, 240, 240, 240, 240, 240, 240, 240, 1916};
int z_koi[52]={0, 0, 0, 0, 0, 0, 0, 0, 0, 122, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 10, 0, 10, 0, 0, 0, 10, 0, 10, 0, 0, 0, 0, 0, 0, 0};
int pitch_koi=10;

/*紅驚き*/
unsigned short int frq_kurenai[54]={ax4 , ax4 , a4 , ax4 , C5 , D5 , C5 , ax4 , a4 , G4 , ax4 , C5 , ax4 , a4 , ax4 , ax4 , a4 , ax4 , C5 , D5 , C5 , ax4 , a4 , G4 , F4 , a4 , G4 , ax4 , ax4 , a4 , ax4 , C5 , D5 , C5 , ax4 , a4 , G4 , ax4 , C5 , ax4 , a4 , ax4 , ax4 , a4 , ax4 , C5 , D5 , C5 , ax4 , a4 , G4 , F4 , a4 , G4 };
unsigned short int frq_kurenai_high[54]{ax5 , ax5 , a5, ax5, C6, D6, C6, ax5, a5, G5, ax5, C6, ax5, a5, ax5 , ax5 , a5, ax5, C6, D6, C6, ax5, a5, G5, F5, a5, G5, ax5 , ax5 , a5, ax5, C6, D6, C6, ax5, a5, G5, ax5, C6, ax5, a5, ax5 , ax5 , a5, ax5, C6, D6, C6, ax5, a5, G5, F5, a5, G5};
int y_kurenai[54]={250, 125, 125, 375, 125, 250, 125, 125, 500, 375, 125, 250, 250, 1000, 250, 125, 125, 375, 125, 250, 125, 125, 500, 500, 250, 250, 1000, 250, 125, 125, 375, 125, 250, 125, 125, 500, 375, 125, 250, 250, 1000, 250, 125, 125, 375, 125, 250, 125, 125, 500, 500, 250, 250, 1000};
int z_kurenai[54]={10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int pitch_kurenai=13;

/*空も飛べるはずうれしい*/
unsigned short int frq_sora[73]={G3 , C4 , D4 , E4 , E4 , D4 , E4 , F4 , E4 , C4 , C4 , a4 , a4 , b3 , C4 , D4 , a4 , a4 , G4 , E4 , G4 , F4 , G4 , a4 , D4 , D4 , G3 , G4 , C4 , C4 , C4 , b3 , a3 , b3 , C4 , E4 , C4 , D4 , G3 , C4 , D4 , E4 , E4 , D4 , E4 , F4 , E4 , C4 , C4 , a4 , a4 , b3 , C4 , D4 , a4 , a4 , G4 , E4 , G4 , F4 , G4 , a4 , D4 , D4 , G3 , G4 , C4 , C4 , F4 , a3 , b3 , E4 , C4 };
unsigned short int frq_sora_high[73]={G4, C5, D5, E5 , E5 , D5, E5, F5, E5, C5 , C5 , a5 , a5, b4, C5, D5, a5 , a5 , G5, E5, G5, F5, G5, a5, D5 , D5 , G3 , G4 , C5, C5, C5, b4, a4, b4, C5, E5, C5, D5, G4, C5, D5, E5, E5, D5, E5, F5, E5, C5, C5, a5, a5, b4, C5, D5, a5, a5, G5, E5, G5, F5, G5, a5, D5, D5, G3 , G4 , C5, C5, F5, a4, b4, E5, C5};
int y_sora[73]={250, 250, 250, 500, 500, 250, 250, 500, 750, 250, 750, 500, 500, 250, 250, 250, 250, 250, 250, 250, 500, 250, 250, 750, 250, 750, 250, 750, 250, 500, 250, 250, 500, 250, 500, 250, 250, 1250, 250, 250, 250, 500, 500, 250, 250, 500, 750, 250, 750, 500, 500, 250, 250, 250, 250, 250, 250, 250, 500, 250, 250, 750, 250, 750, 250, 750, 250, 1000, 1500, 500, 1000, 1000, 2000};
int z_sora[73]={0, 0, 0, 10, 0, 0, 0, 0, 0, 10, 210, 10, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 190, 0, 0, 0, 10, 0, 0, 0, 0, 0, 10, 210, 10, 0, 0, 0, 0, 10, 0, 0, 0, 0, 230, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0};
int pitch_sora=10;





float pitch=2.0;
float duty = 0.5; // 指定したいデューティ比



std_msgs::Int32 int_msg;
ros::Publisher chatter("chatter", &int_msg);

void messageCb( const std_msgs::Int32& toggle_msg) {
  if(toggle_msg.data == 0){
      SetSquareWave_exciting(); 
      OCR4B = 0; 
      OCR5B = 0; 
      int_msg.data = 2;
      chatter.publish( &int_msg );
  }else if (toggle_msg.data == 1){
  SetSquareWave_kurenai(); 
      OCR4B = 0; 
      OCR5B = 0;  
  int_msg.data = 1;
  chatter.publish( &int_msg );
  }else if (toggle_msg.data == 2){
  SetSquareWave_darth(); 
      OCR4B = 0; 
      OCR5B = 0;  
  int_msg.data = 1;
  chatter.publish( &int_msg );
  }else if (toggle_msg.data == 3){
  SetSquareWave_soratobe(); 
      OCR4B = 0; 
      OCR5B = 0;  
  int_msg.data = 1;
  chatter.publish( &int_msg );
  }else if (toggle_msg.data == 4){
  SetSquareWave_eli(); 
      OCR4B = 0; 
      OCR5B = 0;  
  int_msg.data = 1;
  chatter.publish( &int_msg );
  }else if (toggle_msg.data == 5){
  SetSquareWave_koi(); 
      OCR4B = 0; 
      OCR5B = 0;  
  int_msg.data = 1;
  chatter.publish( &int_msg );
  }else{
  
  }
}

ros::Subscriber<std_msgs::Int32> sub("toggle_song", &messageCb );

void SetSquareWave_eli()
{
  pitch=pitch_eli;
  
    for(int j=0; j<95; j++)    /*楽譜の長さ*/
  {                   
      // TOP値指定

  OCR4A = (float)(1000000 / frq_eli[j]);
  OCR5A = (float)(1000000 / frq_eli_high[j]);

  // Duty比指定
  OCR4B = (unsigned int)(1000000 / frq_eli[j] * duty*0.1);
  OCR5B = (unsigned int)(1000000 / frq_eli_high[j] * duty*0.1);
  
  delay((float)1/y_eli[j]*1000*pitch*0.1);
   
  if(z_eli[j] != 0)
  {
     OCR4B = 0;
     OCR5B = 0;
     delay((float)1/z_eli[j]*1000*pitch*0.1);
     }
  }
}

void SetSquareWave_darth()
{
  pitch=pitch_darth;
  
    for(int j=0; j<66; j++)    /*楽譜の長さ*/
  {                   
      // TOP値指定

  OCR4A = (float)(1000000 / frq_darth[j]);
  OCR5A = (float)(1000000 / frq_darth_high[j]);

  // Duty比指定
  OCR4B = (unsigned int)(1000000 / frq_darth[j] * duty*0.1);
  OCR5B = (unsigned int)(1000000 / frq_darth_high[j] * duty*0.1);
 
  
  delay((float)y_darth[j]*pitch*0.1);
   
  if(z_darth[j] != 0)
  {
     OCR4B = 0;
     OCR5B = 0;
     delay((float)z_darth[j]*pitch*0.1);
     }
  }
}

void SetSquareWave_exciting()
{
  pitch=pitch_exciting;
  
    for(int j=0; j<33; j++)    /*楽譜の長さ*/
  {                   
      // TOP値指定

  OCR4A = (float)(1000000 / frq_exciting[j]);
  OCR5A = (float)(1000000 / frq_exciting_high[j]);

  // Duty比指定
  OCR4B = (unsigned int)(1000000 / frq_exciting[j] * duty*0.1);
  OCR5B = (unsigned int)(1000000 / frq_exciting_high[j] * duty*0.1);
 
  
  delay((float)y_exciting[j]*pitch*0.1);
   
  if(z_exciting[j] != 0)
  {
     OCR3B = 0;
     OCR4B = 0;
     OCR5B = 0;
     delay((float)z_exciting[j]*pitch*0.1);
     }
  }
}

void SetSquareWave_koi()
{
  pitch=pitch_koi;
  
    for(int j=0; j<52; j++)    /*楽譜の長さ*/
  {                   
      // TOP値指定

  OCR4A = (float)(1000000 / frq_koi[j]);
  OCR5A = (float)(1000000 / frq_koi_high[j]);

  // Duty比指定
  OCR4B = (unsigned int)(1000000 / frq_koi[j] * duty*0.1);
  OCR5B = (unsigned int)(1000000 / frq_koi_high[j] * duty*0.1);
 
  
  delay((float)y_koi[j]*pitch*0.1);
   
  if(z_koi[j] != 0)
  {

     OCR4B = 0;
     OCR5B = 0;
     delay((float)z_koi[j]*pitch*0.1);
     }
  }
}

void SetSquareWave_kurenai()
{
  pitch=pitch_kurenai;
  
    for(int j=0; j<54; j++)    /*楽譜の長さ*/
  {                   
      // TOP値指定

  OCR4A = (float)(1000000 / frq_kurenai[j]);
  OCR5A = (float)(1000000 / frq_kurenai_high[j]);

  // Duty比指定
  OCR4B = (unsigned int)(1000000 / frq_kurenai[j] * duty*0.1);
  OCR5B = (unsigned int)(1000000 / frq_kurenai_high[j] * duty*0.1);
 
  
  delay((float)y_kurenai[j]*pitch*0.1);
   
  if(z_kurenai[j] != 0)
  {

     OCR4B = 0;
     OCR5B = 0;
     delay((float)z_kurenai[j]*pitch*0.1);
     }
  }
}


void SetSquareWave_soratobe()
{
  pitch=pitch_sora;
  
    for(int j=0; j<73; j++)    /*楽譜の長さ*/
  {                   
      // TOP値指定

  OCR4A = (float)(1000000 / frq_sora[j]);
  OCR5A = (float)(1000000 / frq_sora_high[j]);

  // Duty比指定
  OCR4B = (unsigned int)(1000000 / frq_sora[j] * duty*0.1);
  OCR5B = (unsigned int)(1000000 / frq_sora_high[j] * duty*0.1);
 
  
  delay((float)y_sora[j]*pitch*0.1);
   
  if(z_sora[j] != 0)
  {

     OCR4B = 0;
     OCR5B = 0;
     delay((float)z_sora[j]*pitch*0.1);
     }
  }
}


void setup() {


  pinMode(PWMPin4, OUTPUT);
  pinMode(PWMPin5, OUTPUT);

  pinMode (ENA1, OUTPUT);
  pinMode (ENA2, OUTPUT);


     // モード指定

  TCCR4A = 0b00100001;
  TCCR4B = 0b00010010;
  TCCR5A = 0b00100001;
  TCCR5B = 0b00010010;

//ROS
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
}


void loop() {
  nh.spinOnce();
  delay(1); 
}
