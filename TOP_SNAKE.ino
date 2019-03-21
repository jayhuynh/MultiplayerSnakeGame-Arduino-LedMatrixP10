#include <SPI.h>        
#include <DMD.h>       
#include <TimerOne.h> 
#include "SystemFont5x7.h"


//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
byte snakelength1,snakelength2;
byte t,kt,t2,kt2,m,m1,m2,v,p,t1;
int x;
int y;
bool mang[16][32];
byte i[4][256];
char d=' ';
char d2=' ';
char d3[3]=" ";
char d4[3]=" ";
byte count1,count2,count3,count4;
bool restar=true;
bool eat=false;
byte fx=31;
byte fy=10;
//---------------------------------------------------
void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}


void setup()
{
  Serial.begin(9600); 

   pinMode(A0,INPUT);
   pinMode(A1,INPUT);  
   pinMode(4,INPUT); 
   for (int l=0;l<256;l++)
   {
        i[0][l]=99;
        i[1][l]=99;
        i[2][l]=99;
        i[3][l]=99; 
   
   }  
   
   Timer1.initialize( 3000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD);   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
  
}
//--------------------------------------------------------------------------------

void del(int a,int b)
{
       dmd.writePixel(a,b,GRAPHICS_NORMAL,0);
    
      
}
//--------------------------------------------------------------------------------
void draw(int a,int b)
{       
        dmd.writePixel(a,b,GRAPHICS_NORMAL,1);
}        
 //-----------------------------------------------------------------------------------
 
void convert(byte z)
{       
      if (z<=10)
          {      
                if ((z%10)==1) {d3[0]='1';} 
                if ((z%10)==2) {d3[0]='2';} 
                if ((z%10)==3) {d3[0]='3';} 
                if ((z%10)==4) {d3[0]='4';} 
                if ((z%10)==5) {d3[0]='5';} 
                if ((z%10)==6) {d3[0]='6';} 
                if ((z%10)==7) {d3[0]='7';} 
                if ((z%10)==8) {d3[0]='8';} 
                if ((z%10)==9) {d3[0]='9';} 
                if ((z%10)==0) {d3[0]='1';
                                d3[1]='0';} 
          }
       else 
       {
             if ((z/10)==1) {d3[0]='1';} 
             if ((z/10)==2) {d3[0]='2';} 
             if ((z%10)==1) {d3[1]='1';} 
             if ((z%10)==2) {d3[1]='2';} 
             if ((z%10)==3) {d3[1]='3';} 
             if ((z%10)==4) {d3[1]='4';} 
             if ((z%10)==5) {d3[1]='5';} 
             if ((z%10)==6) {d3[1]='6';} 
             if ((z%10)==7) {d3[1]='7';} 
             if ((z%10)==8) {d3[1]='8';} 
             if ((z%10)==9) {d3[1]='9';} 
       }
               
}        
 //-----------------------------------------------------------------------------------
 void convert2(byte z)
{       
      if (z<=10)
          {      
                if ((z%10)==1) {d4[0]='1';} 
                if ((z%10)==2) {d4[0]='2';} 
                if ((z%10)==3) {d4[0]='3';} 
                if ((z%10)==4) {d4[0]='4';} 
                if ((z%10)==5) {d4[0]='5';} 
                if ((z%10)==6) {d4[0]='6';} 
                if ((z%10)==7) {d4[0]='7';} 
                if ((z%10)==8) {d4[0]='8';} 
                if ((z%10)==9) {d4[0]='9';} 
                if ((z%10)==0) {d4[0]='1';
                                d4[1]='0';} 
          }
       else 
       {
             if ((z/10)==1) {d4[0]='1';} 
             if ((z/10)==2) {d4[0]='2';} 
             if ((z%10)==1) {d4[1]='1';} 
             if ((z%10)==2) {d4[1]='2';} 
             if ((z%10)==3) {d4[1]='3';} 
             if ((z%10)==4) {d4[1]='4';} 
             if ((z%10)==5) {d4[1]='5';} 
             if ((z%10)==6) {d4[1]='6';} 
             if ((z%10)==7) {d4[1]='7';} 
             if ((z%10)==8) {d4[1]='8';} 
             if ((z%10)==9) {d4[1]='9';} 
       }
               
}        
 //-----------------------------------------------------------------------------------
int readbutton()
{
        byte r1=0;
        byte r2=0;
        for (byte k=0;k<50;k++)
        {
            if (analogRead(A2)>0){r1++;}
            else  {r2++;}
            delay(2);  
        }
        if (r1>r2){return 1;}
        else {return 0;}

}
 //-----------------------------------------------------------------------------------
char readkey()
{ 
  x=analogRead(A0);
  y=analogRead(A1); 
  if (682<=x && x<=1023 && 341<=y && y<=682)
  {d='E';}
  else if (0<=x && x<=341 && 341<=y && y<=682) 
        {d='W';}
        else if (341<=x && x<=682 && 0<=y && y<=341) 
          {d='N';}
            else if (341<=x && x<=682 && 682<=y && y<=1023) 
                  {d='S';}
                  else {d='H';}
  return d; 
  }
//----------------------------------------------------------------------------------
char readkey2()
{ 
  x=analogRead(A3);
  y=analogRead(A4); 
  if (682<=x && x<=1023 && 341<=y && y<=682)
  {d2='E';}
  else if (0<=x && x<=341 && 341<=y && y<=682) 
        {d2='W';}
        else if (341<=x && x<=682 && 0<=y && y<=341) 
          {d2='N';}
            else if (341<=x && x<=682 && 682<=y && y<=1023) 
                  {d2='S';}
                  else {d2='H';}
  return d2; 
  }
//----------------------------------------------------------------------------------
void ending(byte p, byte q)
{
          t1=0;
          while (t1<4)
          {
                v=0;
                kt=5;
                restar=true;
                del(p,q);
                delay(500);
                draw(p,q);
                delay(500);
                t1++;
               // Serial.print(analogRead(A2));
                //Serial.print(" ");
                
                  
          }
          dmd.clearScreen( true );
          while (readbutton()==1)
          //
                {
                dmd.selectFont(System5x7);
              //     dmd.drawString(  0,  0, "Snake",5, GRAPHICS_NORMAL );
                 //  dmd.drawString(  0,  9, "A win",5, GRAPHICS_NORMAL );
                 convert(snakelength1);
                 convert2(snakelength2);
                 dmd.drawChar(  0,  0, 'A', GRAPHICS_NORMAL );
                 dmd.drawChar(  9,  0, d3[0], GRAPHICS_NORMAL );
                 dmd.drawChar(  18,  0, d3[1], GRAPHICS_NORMAL );
              //   dmd.drawString(  9, 0 ,d3 ,strlen(d3), GRAPHICS_NORMAL );
                 dmd.drawChar(  0,  9, 'B', GRAPHICS_NORMAL );
                 dmd.drawChar(  9,  9, d4[0], GRAPHICS_NORMAL );
                 dmd.drawChar(  18,  9, d4[1], GRAPHICS_NORMAL );
                 
                 //dmd.drawString(  9,  9,d4 ,strlen(d4), GRAPHICS_NORMAL );
                }
                         
}
//---------------------------------------------------------------------------------
void food()
{
     while ( m == 1 )
     { 
            m1 = random(16);
            m2 = random(32);
            if (snakelength1>snakelength2)
                {
                      for (byte k=0;k<snakelength1;k++)
                      {
                            if (i[0][k] == m1 && i[2][k] == m2)
                            {
                              m = 1;
                              k=snakelength1;
                  
                            }
                            else 
                            {
                                  if (i[1][k] == m1 && i[3][k] == m2)
                                  {
                                    m = 1;
                                    k=snakelength1;                  
                                  }                                                                   
                                  else m=0;
                            }
                      }
                }
            else
                 {
                      for (byte k=0;k<snakelength2;k++)
                      {
                            if (i[0][k] == m1 && i[2][k] == m2)
                            {
                              m = 1;
                              k=snakelength2;
                  
                            }
                            else 
                            {
                                  if (i[1][k] == m1 && i[3][k] == m2)
                                  {
                                    m = 1;
                                    k=snakelength2;                  
                                  }                                                                   
                                  else m=0;
                            }
                      }
                }
      }
      m=1;
      fx=m2;
      fy=m1;
      draw(fx,fy);

}
//--------------------------------------------------------------------------------
 void star() 
{
        dmd.clearScreen( true );
        p=0; 
        snakelength1=4;
        snakelength2=4;
        kt2=2;
        t2=2;
        for (int k=0;k<snakelength1;k++)
        {
            i[2][k]=3+k;
            i[0][k]=2;
            i[3][k]=3+k;
            i[1][k]=9;       
            draw(i[2][k],i[0][k]);  
            draw(i[3][k],i[1][k]);                 
        }
        count1=snakelength1-2;
        count2=0;
        count3=snakelength2-2;
        count4=0;   
        restar=false;
        v=1;
}
//--------------------------------------------------------------------------------
void right()
{    
    //    while (readkey() == 'H' || readkey() == 'E' || readkey() == 'W')
     //   { 
           //   if (v==0) break;
                       
              count1++;
              if (count1>(snakelength1-1))
              {
                  count1=0;
              }  
              if ((i[2][count1]+1) == fx && i[0][count1] == fy)                                   //check if the head has same position with food then increase snake length 
                  {
                        eat=true;
                        snakelength1++;
                        for (byte k=(snakelength1-2);k>count1;k--)                    
                        {
                              i[2][k+1] = i[2][k];
                              i[0][k+1] = i[0][k];
                        }
                        i[2][count1+1] = fx;
                        i[0][count1+1] = fy;
                        if ((count2 == 0) || (count2 == (snakelength1-1))) {count2--;}
                        else {count2++;}
                        if (count2>(snakelength1-1))
                        {
                            count2=0;
                        }
                        food();
         
                       
                  }
              else   
                    if ((i[2][count1]+1-32) == fx && i[0][count1] == fy)                  //check if the head has same position with food then increase snake length
                    {
                              eat=true;
                              snakelength1++;
                              for (byte k=(snakelength1-2);k>count1;k--)                    
                              {
                                    i[2][k+1] = i[2][k];
                                    i[0][k+1] = i[0][k];
                              }
                              i[2][count1+1] = fx;
                              i[0][count1+1] = fy;
                              if ((count2 == 0) || (count2 == (snakelength1-1))) {count2--;}
                              else {count2++;}
                              if (count2>(snakelength1-1))
                              {
                                  count2=0;
                              }
                              food();
                            
                      }
                      else 
                      
                      
                      {    
                                    
                                                for (byte k=0;k<snakelength1;k++)                            //check if the head has same position with body then end the game
                                                {
                                                      if ((i[2][count1]+1) == i[2][k] || (i[2][count1]+1-32) == i[2][k])
                                                      {
                                                            if (i[0][count1] ==  i[0][k])
                                                            {
                                                                Serial.println("SNAKE B WIN");
                                                                ending(i[2][k],i[0][k]);
                                                                
                                                            } 
                                                      }
                                                }
                                                for (byte k=0;k<snakelength2;k++)
                                                {
                                                       if ((i[2][count1]+1) == i[3][k] || (i[2][count1]+1-32) == i[3][k])
                                                      {
                                                            if (i[0][count1] ==  i[1][k])
                                                            {
                                                                 if ((count3 + 1)==k)
                                                                {
                                                                      if (snakelength1>snakelength2)
                                                                      {Serial.println("SNAKE A WIN");}
                                                                      else  {Serial.println("SNAKE B WIN");}
                                                                }
                                                                else                                                               
                                                                {Serial.println("SNAKE B WIN");}
                                                                ending(i[3][k],i[1][k]);
                                                               
                                                            } 
                                                      }
                                                  
                                                }
                                    
                         
                                
                            if (restar==false)
                                      
                                      {
                                            if ((i[2][count1]+1)>31)                  //base on the array and draw new head position and delete old tail
                                            {                
                                              draw(i[2][count1]+1-32,i[0][count1]);
                                            } 
                                            else  draw(i[2][count1]+1,i[0][count1]);
                                            delay(100);
                                            del(i[2][count2],i[0][count2]);
                                            if ((i[2][count1]+1)>31)
                                            {
                                                i[2][count2]=i[2][count1]+1-32;
                                                i[0][count2]=i[0][count1];
                                            }
                                            else
                                            {
                                                i[2][count2]=i[2][count1]+1;
                                                i[0][count2]=i[0][count1];
                                            }
                                            count2++;
                                            
                                            if (count2>(snakelength1-1))
                                            {
                                                count2=0;
                                            }
                                            kt=2;
                                            t=2;
                                            if (readkey() == 'N')                         //check read key in order to find new direction
                                            { 
                                                kt=1;
                                               // break;
                                            }
                                            if (readkey() == 'S')                         //check read key in order to find new direction
                                            { 
                                                kt=3;
                                               // break;
                                            }
                                            //Serial.println(millis());
                                        }
                      }
             
      //  }
       
}
//--------------------------------------------------------------------------------
void left()
{    
   //     while (readkey() == 'H' || readkey() == 'E' || readkey() == 'W')
    //    { 

          //    if (v==0) break;
              count1++;
              if (count1>(snakelength1-1))
              {
                  count1=0;
              }  
               if ((i[2][count1]-1) == fx && i[0][count1] == fy)
              {
                    eat=true;
                    snakelength1++;
                    for (byte k=(snakelength1-2);k>count1;k--)                    
                    {
                          i[2][k+1] = i[2][k];
                          i[0][k+1] = i[0][k];
                    }
                    i[2][count1+1] = fx;
                    i[0][count1+1] = fy;
                    if ((count2 == 0) || (count2 == (snakelength1-1))) {count2--;}
                    else {count2++;}
                    if (count2>(snakelength1-1))
                    {
                        count2=0;
                    }
                    food();
                   
                   
              }
              else
                        if ((i[2][count1]-1+32) == fx && i[0][count1] == fy)
                    {
                              eat=true;
                              snakelength1++;
                              for (byte k=(snakelength1-2);k>count1;k--)                    
                              {
                                    i[2][k+1] = i[2][k];
                                    i[0][k+1] = i[0][k];
                              }
                              i[2][count1+1] = fx;
                              i[0][count1+1] = fy;
                              if ((count2 == 0) || (count2 == (snakelength1-1))) {count2--;}
                              else {count2++;}
                              if (count2>(snakelength1-1))
                              {
                                  count2=0;
                              }
                              food();
                            
                      }
                      else
                      {
                            
                                       for (byte k=0;k<snakelength1;k++)
                                            {
                                                  if ((i[2][count1]-1) == i[2][k] || (i[2][count1]-1+32) == i[2][k])
                                                  {
                                                        if (i[0][count1] ==  i[0][k])
                                                        {
                                                              Serial.println("SNAKE B WIN");
                                                            ending(i[2][k],i[0][k]);
                                                          
                                                        } 
                                                  }
                                            }
                                        for (byte k=0;k<snakelength2;k++) 
                                        {
                                                  if ((i[2][count1]-1) == i[3][k] || (i[2][count1]-1+32) == i[3][k])
                                                      {
                                                            if (i[0][count1] ==  i[1][k])
                                                            {
                                                                 if ((count3 + 1)==k)
                                                                {
                                                                      if (snakelength1>snakelength2)
                                                                      {Serial.println("SNAKE A WIN");}
                                                                      else  {Serial.println("SNAKE B WIN");}
                                                                }
                                                                else                                                               
                                                                {Serial.println("SNAKE B WIN");}
                                                                ending(i[3][k],i[1][k]);
                                                               
                                                            } 
                                                      }
                                                  
                                              
                                            }
                                   
                         
                            if (restar==false)
              
                                            {
                                                      if ((i[2][count1]-1)<0)
                                                      {                
                                                        draw(i[2][count1]-1+32,i[0][count1]);
                                                      } 
                                                      else  draw(i[2][count1]-1,i[0][count1]);
                                                      delay(100);
                                                      del(i[2][count2],i[0][count2]);
                                                      if ((i[2][count1]-1)<0)
                                                      {
                                                          i[2][count2]=i[2][count1]-1+32;
                                                          i[0][count2]=i[0][count1];
                                                      }
                                                      else
                                                      {
                                                          i[2][count2]=i[2][count1]-1;
                                                          i[0][count2]=i[0][count1];
                                                      }
                                                      count2++;
                                                      
                                                      if (count2>(snakelength1-1))
                                                      {
                                                          count2=0;
                                                      }
                                                      kt=4;
                                                      t=4;
                                                       if (readkey() == 'N')
                                                      { 
                                                          kt=1;
                                                        //  break;
                                                      }
                                                      if (readkey() == 'S')
                                                      { 
                                                          kt=3;
                                                        //  break;
                                                      }
                                          }
                      }

    //    }
 
}
//--------------------------------------------------------------------------------
void up()
{    
    //    while (readkey() == 'H' || readkey() == 'N' || readkey() == 'S')
      //  { 

         //     if (v==0) break;
              count1++;
              if (count1>(snakelength1-1))
              {
                  count1=0;
              }
               if (i[2][count1] == fx && (i[0][count1]-1) == fy)
              {
                    eat=true;
                    snakelength1++;
                    for (byte k=(snakelength1-2);k>count1;k--)                    
                    {
                          i[2][k+1] = i[2][k];
                          i[0][k+1] = i[0][k];
                    }
                    i[2][count1+1] = fx;
                    i[0][count1+1] = fy;
                    if ((count2 == 0) || (count2 == (snakelength1-1))) {count2--;}
                    else {count2++;}
                    if (count2>(snakelength1-1))
                    {
                        count2=0;
                    }
                    food();
                 
                   
              }
              else
                      if (i[2][count1] == fx && (i[0][count1]-1+16) == fy)
                    {
                              eat=true;
                              snakelength1++;
                              for (byte k=(snakelength1-2);k>count1;k--)                    
                              {
                                    i[2][k+1] = i[2][k];
                                    i[0][k+1] = i[0][k];
                              }
                              i[2][count1+1] = fx;
                              i[0][count1+1] = fy;
                              if ((count2 == 0) || (count2 == (snakelength1-1))) {count2--;}
                              else {count2++;}
                              if (count2>(snakelength1-1))
                              {
                                  count2=0;
                              }
                              food();
                            
                            
                      }
                      else
                      {
                          
                                       for (byte k=0;k<snakelength1;k++)
                                            {
                                                  if ((i[0][count1]-1) == i[0][k] || (i[0][count1]-1+16) == i[0][k])
                                                  {
                                                        if (i[2][count1] ==  i[2][k])
                                                        {
                                                            Serial.println("SNAKE B WIN");
                                                            ending(i[2][k],i[0][k]);
                                                            
                                                        } 
                                                  }
                                            }
                                            for (byte k=0;k<snakelength2;k++)
                                            {
                                                  if ((i[0][count1]-1) == i[1][k] || (i[0][count1]-1+16) == i[1][k])
                                                      {
                                                            if (i[2][count1] ==  i[3][k])
                                                            {
                                                                 if ((count3 + 1)==k)
                                                                {
                                                                      if (snakelength1>snakelength2)
                                                                      {Serial.println("SNAKE A WIN");}
                                                                      else  {Serial.println("SNAKE B WIN");}
                                                                }
                                                                else                                                               
                                                                {Serial.println("SNAKE B WIN");}
                                                                ending(i[3][k],i[1][k]);
                                                               
                                                            } 
                                                      }
                                                  
                                              
                                            }
                                  
                         
                          
                            if (restar==false)
                                                    {
                                                              if ((i[0][count1]-1)<0)
                                                              {                
                                                                draw(i[2][count1],i[0][count1]-1+16);
                                                              } 
                                                              else  draw(i[2][count1],i[0][count1]-1);
                                                              delay(100);
                                                              del(i[2][count2],i[0][count2]);
                                                              if ((i[0][count1]-1)<0)
                                                              {
                                                                  i[2][count2]=i[2][count1];
                                                                  i[0][count2]=i[0][count1]-1+16;
                                                              }
                                                              else
                                                              {
                                                                  i[2][count2]=i[2][count1];
                                                                  i[0][count2]=i[0][count1]-1;
                                                              }
                                                              count2++;
                                                              
                                                              if (count2>(snakelength1-1))
                                                              {
                                                                  count2=0;
                                                              }
                                                              t=1;
                                                              kt=1;
                                                               if (readkey() == 'W')
                                                              { 
                                                                  kt=4;
                                                         //         break;
                                                              }
                                                              if (readkey() == 'E')
                                                              { 
                                                                  kt=2;
                                                              //    break;
                                                              }
                                                    }
                      }

      //  }

    
}
//--------------------------------------------------------------------------------
void down()
{    
     //   while (readkey() == 'H' || readkey() == 'N' || readkey() == 'S')
     //   { 
       //       if (v==0) break;
              count1++;
              if (count1>(snakelength1-1))
              {
                  count1=0;
              } 
              if (i[2][count1] == fx && (i[0][count1]+1) == fy)
              {
                    eat=true;
                    snakelength1++;
                    for (byte k=(snakelength1-2);k>count1;k--)                    
                    {
                          i[2][k+1] = i[2][k];
                          i[0][k+1] = i[0][k];
                    }
                    i[2][count1+1] = fx;
                    i[0][count1+1] = fy;
                    if ((count2 == 0) || (count2 == (snakelength1-1))) {count2--;}
                    else {count2++;}
                    if (count2>(snakelength1-1))
                    {
                        count2=0;
                    }
                    food();
                   
                   
              }

              else

                      if (i[2][count1] == fx && (i[0][count1]+1-16) == fy)
                    {
                              eat=true;
                              snakelength1++;
                              for (byte k=(snakelength1-2);k>count1;k--)                    
                              {
                                    i[2][k+1] = i[2][k];
                                    i[0][k+1] = i[0][k];
                              }
                              i[2][count1+1] = fx;
                              i[0][count1+1] = fy;
                              if ((count2 == 0) || (count2 == (snakelength1-1))) {count2--;}
                              else {count2++;}
                              if (count2>(snakelength1-1))
                              {
                                  count2=0;
                              }
                              food();
                             
                            
                      }
                      else
                      {
                       
                                    for (byte k=0;k<snakelength1;k++)
                                        {
                                              if ((i[0][count1]+1) == i[0][k] || (i[0][count1]+1-16) == i[0][k])
                                              {
                                                    if (i[2][count1] ==  i[2][k])
                                                    {
                                                        
                                                         Serial.println("SNAKE B WIN");
                                                        ending(i[2][k],i[0][k]);
                                                       
                                                    } 
                                              }
                                        }
                                  for (byte k=0;k<snakelength2;k++)
                                        {
                                              if ((i[0][count1]+1) == i[1][k] || (i[0][count1]+1-16) == i[1][k])
                                                              {
                                                                    if (i[2][count1] ==  i[3][k])
                                                                    {
                                                                   /*     Serial.print(i[2][0]);
                                                                        Serial.print(" ");
                                                                        Serial.print(i[2][2]);
                                                                        Serial.print(" ");
                                                                        Serial.print(i[2][3]);
                                                                        Serial.print(" ");
                                                                        Serial.print(i[2][4]);
                                                                        Serial.print(" ");
                                                                        Serial.print(i[2][5]);
                                                                        Serial.println(" ");
                                                                        Serial.print(i[3][0]);
                                                                        Serial.print(" ");
                                                                        Serial.print(i[3][1]);
                                                                        Serial.print(" ");
                                                                        Serial.print(i[3][2]);
                                                                        Serial.print(" ");
                                                                        Serial.print(i[3][3]);
                                                                        Serial.println(" ");
                                                                        Serial.println("YOOOOOOOO");
                                                                        Serial.println(count1);
                                                                        Serial.println(k);
                                                                        */
                                                                         if ((count3 + 1)==k)
                                                                {
                                                                      if (snakelength1>snakelength2)
                                                                      {Serial.println("SNAKE A WIN");}
                                                                      else  {Serial.println("SNAKE B WIN");}
                                                                }
                                                                else                                                               
                                                                {Serial.println("SNAKE B WIN");}
                                                                        ending(i[3][k],i[1][k]);
                                                                        
                                                                    } 
                                                              }
                                          
                                        }
        
                                
                         
                            if (restar==false)
                                                          {
                                                           
                                                                              if ((i[0][count1]+1)>15)
                                                                              {                
                                                                                draw(i[2][count1],i[0][count1]+1-16);
                                                                              } 
                                                                              else  draw(i[2][count1],i[0][count1]+1);
                                                                              delay(100);
                                                                              del(i[2][count2],i[0][count2]);
                                                                              if ((i[0][count1]+1)>15)
                                                                              {
                                                                                  i[2][count2]=i[2][count1];
                                                                                  i[0][count2]=i[0][count1]+1-16;
                                                                              }
                                                                              else
                                                                              {
                                                                                  i[2][count2]=i[2][count1];
                                                                                  i[0][count2]=i[0][count1]+1;
                                                                              }
                                                                              count2++;
                                                                              
                                                                              if (count2>(snakelength1-1))
                                                                              {
                                                                                  count2=0;
                                                                              }
                                                                              kt=3;
                                                                              t=3;  
                                                                              if (readkey() == 'W')
                                                                              { 
                                                                                  kt=4;
                                                                            //      break;
                                                                              }
                                                                              if (readkey() == 'E')
                                                                              { 
                                                                                  kt=2;
                                                                              //    break;
                                                                              }
                                                         
                                                          }
                      }
       // }

       
}
//--------------------------------------------------------------------------------
void right2()
{    
    //    while (readkey() == 'H' || readkey() == 'E' || readkey() == 'W')
     //   { 
           //   if (v==0) break;
                       
              count3++;
              if (count3>(snakelength2-1))
              {
                  count3=0;
              }  
              if ((i[3][count3]+1) == fx && i[1][count3] == fy)                                   //check if the head has same position with food then increase snake length 
                  {
                        eat=true;
                        snakelength2++;
                        for (byte k=(snakelength2-2);k>count3;k--)                    
                        {
                              i[3][k+1] = i[3][k];
                              i[1][k+1] = i[1][k];
                        }
                        i[3][count3+1] = fx;
                        i[1][count3+1] = fy;
                        if ((count4 == 0) || (count4 == (snakelength2-1))) {count4--;}
                        else {count4++;}
                        if (count4>(snakelength2-1))
                        {
                            count4=0;
                        }
                        food();
         
                       
                  }
              else   
                    if ((i[3][count3]+1-32) == fx && i[1][count3] == fy)                  //check if the head has same position with food then increase snake length
                    {
                              eat=true;
                              snakelength2++;
                              for (byte k=(snakelength2-2);k>count3;k--)                    
                              {
                                    i[3][k+1] = i[3][k];
                                    i[1][k+1] = i[1][k];
                              }
                              i[3][count3+1] = fx;
                              i[1][count3+1] = fy;
                              if ((count4 == 0) || (count4 == (snakelength2-1))) {count4--;}
                              else {count4++;}
                              if (count4>(snakelength2-1))
                              {
                                  count4=0;
                              }
                              food();
                            
                      }
                      else 
                      
                      
                      {
                                 //Serial.println("Osadas");
                                                for (byte k=0;k<snakelength2;k++)                            //check if the head has same position with body then end the game
                                                {
                                                      if ((i[3][count3]+1) == i[3][k] || (i[3][count3]+1-32) == i[3][k])
                                                      {
                                                          //  Serial.println("1111");
                                                            if (i[1][count3] ==  i[1][k])
                                                            {
                                                                Serial.println("SNAKE A WIN");
                                                                ending(i[3][k],i[1][k]);
                                                                
                                                            } 
                                                      }
                                                }
                                                     for (byte k=0;k<snakelength1;k++)                            //check if the head has same position with body then end the game
                                                {
                                                       if ((i[3][count3]+1) == i[2][k] || (i[3][count3]+1-32) == i[2][k])
                                                      {
                                                            //Serial.println("2222");
                                                            if (i[1][count3] ==  i[0][k])
                                                            {
                                                                       if ((count1 + 1)==k)
                                                                {
                                                                      if (snakelength1>snakelength2)
                                                                      {Serial.println("SNAKE A WIN");}
                                                                      else  {Serial.println("SNAKE B WIN");}
                                                                }
                                                                else                                                               
                                                                {Serial.println("SNAKE A WIN");}
                                                                ending(i[2][k],i[0][k]);
                                                                
                                                                
                                                            } 
                                                      }
                                                  
                                                }
                                    
                            
                            if (restar==false)
                                      
                                      {
                                            if ((i[3][count3]+1)>31)                  //base on the array and draw new head position and delete old tail
                                            {                
                                              draw(i[3][count3]+1-32,i[1][count3]);
                                            } 
                                            else  draw(i[3][count3]+1,i[1][count3]);
                                            delay(100);
                                            del(i[3][count4],i[1][count4]);
                                            if ((i[3][count3]+1)>31)
                                            {
                                                i[3][count4]=i[3][count3]+1-32;
                                                i[1][count4]=i[1][count3];
                                            }
                                            else
                                            {
                                                i[3][count4]=i[3][count3]+1;
                                                i[1][count4]=i[1][count3];
                                            }
                                            count4++;
                                            
                                            if (count4>(snakelength2-1))
                                            {
                                                count4=0;
                                            }
                                            kt2=2;
                                            t2=2;
                                            if (readkey2() == 'N')                         //check read key in order to find new direction
                                            { 
                                                kt2=1;
                                               // break;
                                            }
                                            if (readkey2() == 'S')                         //check read key in order to find new direction
                                            { 
                                                kt2=3;
                                               // break;
                                            }
                                           // Serial.println(millis());
                                        }
                      }
             
      //  }
       
}
//--------------------------------------------------------------------------------
void left2()
{    
   //     while (readkey() == 'H' || readkey() == 'E' || readkey() == 'W')
    //    { 

          //    if (v==0) break;
              count3++;
              if (count3>(snakelength2-1))
              {
                  count3=0;
              }  
               if ((i[3][count3]-1) == fx && i[1][count3] == fy)
              {
                    eat=true;
                    snakelength2++;
                    for (byte k=(snakelength2-2);k>count3;k--)                    
                    {
                          i[3][k+1] = i[3][k];
                          i[1][k+1] = i[1][k];
                    }
                    i[3][count3+1] = fx;
                    i[1][count3+1] = fy;
                    if ((count4 == 0) || (count4 == (snakelength2-1))) {count4--;}
                    else {count4++;}
                    if (count4>(snakelength2-1))
                    {
                        count4=0;
                    }
                    food();
                   
                   
              }
              else
                        if ((i[3][count3]-1+32) == fx && i[1][count3] == fy)
                    {
                              eat=true;
                              snakelength2++;
                              for (byte k=(snakelength2-2);k>count3;k--)                    
                              {
                                    i[3][k+1] = i[3][k];
                                    i[1][k+1] = i[1][k];
                              }
                              i[3][count3+1] = fx;
                              i[1][count3+1] = fy;
                              if ((count4 == 0) || (count4 == (snakelength2-1))) {count4--;}
                              else {count4++;}
                              if (count4>(snakelength2-1))
                              {
                                  count4=0;
                              }
                              food();
                            
                      }
                      else
                      {
                               
                                                for (byte k=0;k<snakelength2;k++)                            //check if the head has same position with body then end the game
                                                {
                                                      if ((i[3][count3]-1) == i[3][k] || (i[3][count3]-1+32) == i[3][k])
                                                      {
                                                            if (i[1][count3] ==  i[1][k])
                                                            {
                                                                Serial.println("SNAKE A WIN");
                                                                ending(i[3][k],i[1][k]);
                                                                
                                                            } 
                                                      }
                                                }
                                                for (byte k=0;k<snakelength1;k++)                            //check if the head has same position with body then end the game
                                                {
                                                       if ((i[3][count3]-1) == i[2][k] || (i[3][count3]-1+32) == i[2][k])
                                                      {
                                                            if (i[1][count3] ==  i[0][k])
                                                            {
                                                                if (i[1][count3] ==  i[0][k])
                                                            {
                                                                       if ((count1 + 1)==k)
                                                                {
                                                                      if (snakelength1>snakelength2)
                                                                      {Serial.println("SNAKE A WIN");}
                                                                      else  {Serial.println("SNAKE B WIN");}
                                                                }
                                                                else                                                               
                                                                {Serial.println("SNAKE A WIN");}
                                                                ending(i[2][k],i[0][k]);
                                                            }
                                                                
                                                            } 
                                                      }
                                                  
                                                }
                                    
                          
                            if (restar==false)
              
                                            {
                                                      if ((i[3][count3]-1)<0)
                                                      {                
                                                        draw(i[3][count3]-1+32,i[1][count3]);
                                                      } 
                                                      else  draw(i[3][count3]-1,i[1][count3]);
                                                      delay(100);
                                                      del(i[3][count4],i[1][count4]);
                                                      if ((i[3][count3]-1)<0)
                                                      {
                                                          i[3][count4]=i[3][count3]-1+32;
                                                          i[1][count4]=i[1][count3];
                                                      }
                                                      else
                                                      {
                                                          i[3][count4]=i[3][count3]-1;
                                                          i[1][count4]=i[1][count3];
                                                      }
                                                      count4++;
                                                      
                                                      if (count4>(snakelength2-1))
                                                      {
                                                          count4=0;
                                                      }
                                                      kt2=4;
                                                      t2=4;
                                                       if (readkey2() == 'N')
                                                      { 
                                                          kt2=1;
                                                        //  break;
                                                      }
                                                      if (readkey2() == 'S')
                                                      { 
                                                          kt2=3;
                                                        //  break;
                                                      }
                                          }
                      }

    //    }
 
}
//-------------------------------------------------------------------------------
void up2()
{    
    //    while (readkey() == 'H' || readkey() == 'N' || readkey() == 'S')
      //  { 

         //     if (v==0) break;
              count3++;
              if (count3>(snakelength2-1))
              {
                  count3=0;
              }
               if (i[3][count3] == fx && (i[1][count3]-1) == fy)
              {
                    eat=true;
                    snakelength2++;
                    for (byte k=(snakelength2-2);k>count3;k--)                    
                    {
                          i[3][k+1] = i[3][k];
                          i[1][k+1] = i[1][k];
                    }
                    i[3][count3+1] = fx;
                    i[1][count3+1] = fy;
                    if ((count4 == 0) || (count4 == (snakelength2-1))) {count4--;}
                    else {count4++;}
                    if (count4>(snakelength2-1))
                    {
                        count4=0;
                    }
                    food();
                 
                   
              }
              else
                      if (i[3][count3] == fx && (i[1][count3]-1+16) == fy)
                    {
                              eat=true;
                              snakelength2++;
                              for (byte k=(snakelength2-2);k>count3;k--)                    
                              {
                                    i[3][k+1] = i[3][k];
                                    i[1][k+1] = i[1][k];
                              }
                              i[3][count3+1] = fx;
                              i[1][count3+1] = fy;
                              if ((count4 == 0) || (count4 == (snakelength2-1))) {count4--;}
                              else {count4++;}
                              if (count4>(snakelength2-1))
                              {
                                  count4=0;
                              }
                              food();
                            
                            
                      }
                      else
                      {    
                                     for (byte k=0;k<snakelength2;k++)
                                  {
                                        if ((i[1][count3]-1) == i[1][k] || (i[1][count3]-1+16) == i[1][k])
                                        {
                                              if (i[3][count3] ==  i[3][k])
                                              {
                                                  Serial.println("SNAKE A WIN");
                                                  ending(i[3][k],i[1][k]);
                                                  
                                              } 
                                        }
                                  }
                                    for (byte k=0;k<snakelength1;k++)
                                  {
                                        if ((i[1][count3]-1) == i[0][k] || (i[1][count3]-1+16) == i[0][k])
                                                      {
                                                            if (i[3][count3] ==  i[2][k])
                                                            {
                                                                if (i[1][count3] ==  i[0][k])
                                                                {
                                                                       if ((count1 + 1)==k)
                                                                {
                                                                      if (snakelength1>snakelength2)
                                                                      {Serial.println("SNAKE A WIN");}
                                                                      else  {Serial.println("SNAKE B WIN");}
                                                                }
                                                                else                                                               
                                                                {Serial.println("SNAKE A WIN");}
                                                                ending(i[2][k],i[0][k]);
                                                                }
                                                               
                                                            } 
                                                      }
                                                  
                                    
                                  }
                            
                          
                            if (restar==false)
                                                    {
                                                              if ((i[1][count3]-1)<0)
                                                              {                
                                                                draw(i[3][count3],i[1][count3]-1+16);
                                                              } 
                                                              else  draw(i[3][count3],i[1][count3]-1);
                                                              delay(100);
                                                              del(i[3][count4],i[1][count4]);
                                                              if ((i[1][count3]-1)<0)
                                                              {
                                                                  i[3][count4]=i[3][count3];
                                                                  i[1][count4]=i[1][count3]-1+16;
                                                              }
                                                              else
                                                              {
                                                                  i[3][count4]=i[3][count3];
                                                                  i[1][count4]=i[1][count3]-1;
                                                              }
                                                              count4++;
                                                              
                                                              if (count4>(snakelength2-1))
                                                              {
                                                                  count4=0;
                                                              }
                                                              t2=1;
                                                              kt2=1;
                                                               if (readkey2() == 'W')
                                                              { 
                                                                  kt2=4;
                                                         //         break;
                                                              }
                                                              if (readkey2() == 'E')
                                                              { 
                                                                  kt2=2;
                                                              //    break;
                                                              }
                                                    }
                      }

      //  }

    
}

//--------------------------------------------------------------------------------
void down2()
{    
     //   while (readkey() == 'H' || readkey() == 'N' || readkey() == 'S')
     //   { 
       //       if (v==0) break;
              count3++;
              if (count3>(snakelength2-1))
              {
                  count3=0;
              } 
              if (i[3][count3] == fx && (i[1][count3]+1) == fy)
              {
                    eat=true;
                    snakelength2++;
                    for (byte k=(snakelength2-2);k>count3;k--)                    
                    {
                          i[3][k+1] = i[3][k];
                          i[1][k+1] = i[1][k];
                    }
                    i[3][count3+1] = fx;
                    i[1][count3+1] = fy;
                    if ((count4 == 0) || (count4 == (snakelength2-1))) {count4--;}
                    else {count4++;}
                    if (count4>(snakelength2-1))
                    {
                        count4=0;
                    }
                    food();
                   
                   
              }

              else

                      if (i[3][count3] == fx && (i[1][count3]+1-16) == fy)
                    {
                              eat=true;
                              snakelength2++;
                              for (byte k=(snakelength2-2);k>count3;k--)                    
                              {
                                    i[3][k+1] = i[3][k];
                                    i[1][k+1] = i[1][k];
                              }
                              i[3][count3+1] = fx;
                              i[1][count3+1] = fy;
                              if ((count4 == 0) || (count4 == (snakelength2-1))) {count4--;}
                              else {count4++;}
                              if (count4>(snakelength2-1))
                              {
                                  count4=0;
                              }
                              food();
                             
                            
                      }
                      else
                      {
                       
                                     for (byte k=0;k<snakelength2;k++)
                                  {
                                        if ((i[1][count3]+1) == i[1][k] || (i[1][count3]+1-16) == i[1][k])
                                        {
                                              if (i[3][count3] ==  i[3][k])
                                              {
                                                  Serial.println("SNAKE A WIN");
                                                  ending(i[3][k],i[1][k]);
                                                  
                                              } 
                                        }
                                  }
                                        
                                     for (byte k=0;k<snakelength1;k++)
                                  {
                                        if ((i[1][count3]+1) == i[0][k] || (i[1][count3]+1-16) == i[0][k])
                                                      {
                                                            if (i[3][count3] ==  i[2][k])
                                                            {
                                                                 if (i[1][count3] ==  i[0][k])
                                                                {
                                                                       if ((count1 + 1)==k)
                                                                {
                                                                      if (snakelength1>snakelength2)
                                                                      {Serial.println("SNAKE A WIN");}
                                                                      else  {Serial.println("SNAKE B WIN");}
                                                                }
                                                                else                                                               
                                                                {Serial.println("SNAKE A WIN");}
                                                                ending(i[2][k],i[0][k]);
                                                                }
                                                               
                                                            } 
                                                      }
                                                  
                                    
                                  }
                            
                            if (restar==false)
                                                          {
                                                           
                                                                              if ((i[1][count3]+1)>15)
                                                                              {                
                                                                                draw(i[3][count3],i[1][count3]+1-16);
                                                                              } 
                                                                              else  draw(i[3][count3],i[1][count3]+1);
                                                                              delay(100);
                                                                              del(i[3][count4],i[1][count4]);
                                                                              if ((i[1][count3]+1)>15)
                                                                              {
                                                                                  i[3][count4]=i[3][count3];
                                                                                  i[1][count4]=i[1][count3]+1-16;
                                                                              }
                                                                              else
                                                                              {
                                                                                  i[3][count4]=i[3][count3];
                                                                                  i[1][count4]=i[1][count3]+1;
                                                                              }
                                                                              count4++;
                                                                              
                                                                              if (count4>(snakelength2-1))
                                                                              {
                                                                                  count4=0;
                                                                              }
                                                                              kt2=3;
                                                                              t2=3;  
                                                                              if (readkey2() == 'W')
                                                                              { 
                                                                                  kt2=4;
                                                                            //      break;
                                                                              }
                                                                              if (readkey2() == 'E')
                                                                              { 
                                                                                  kt2=2;
                                                                              //    break;
                                                                              }
                                                         
                                                          }
                      }
       // }

       

}
//--------------------------------------------------------------------------------
void loop()
{
                 if (restar) 
                  {
                      //Serial.println(millis());
                      dmd.clearScreen( true );     
                      dmd.selectFont(System5x7);
                      
                      dmd.drawString(  2,  0, "SNAKE",5, GRAPHICS_NORMAL );
                      dmd.drawString(  5,  9, "GAME",5, GRAPHICS_NORMAL );
                      delay(2000);
                      d3[4]=' ';
                      d3[3]=' ';
                      d3[2]=' ';
                      d3[1]=' ';
                      d3[0]=' ';
                      d4[4]=' ';
                      d4[3]=' ';
                      d4[2]=' ';
                      d4[1]=' ';
                      d4[0]=' ';
                      star();
                      draw(fx,fy);
                      right();
                      //Serial.println("ONE");
                      right2();
                  }
                  if (kt == 2 && t != 4 ) {right();}
                  if (kt == 4 && t != 2 ) {left();}
                  if (kt == 1 && t != 3 ) {up();}
                  if (kt == 3 && t != 1 ) {down();}
                   
  

                  if (kt2 == 2 && t2 != 4 ) {right2();}
                  if (kt2 == 4 && t2 != 2 ) {left2();}
                  if (kt2 == 1 && t2 != 3 ) {up2();}
                  if (kt2 == 3 && t2 != 1 ) {down2();}
  
                /*  if (millis() >= p*1000)
                  {
                    Serial.print("Time: ");
                    Serial.println(p);
                    p++;
                  }

                  if (p>=120)
                  {                                                           
                          ending(fx,fy);   
                  }*/

                  

 
  
 
}



