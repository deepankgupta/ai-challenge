#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


class team0059  
{
  private:      //private fns and variables defined
  int pl,ph,player_num,player_no,ball_player,r,g;;
  
   int preqp(int finalx,int finaly, int initialx ,int initialy )  //function which tells the strength req by player to move from 
	{float req;                                                    //place to another
    req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
    return (int)req;}     

  int preqpb(int finalx,int finaly, int initialx ,int initialy )   //function which tells the strength req by hitter of ball to hit
	{float req; int i;                                            //the ball from one place to another
    req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	 i=(int)req;
	 return i;} 
    
  //public functions
  public:
    int init(int team_number, struct player *p,char farray[][51])   //the mandatory function which initialises the team no. of the 
	{                                                  //participant and tells him the initial field distribution
		player_no = team_number;
		
	}
  void nochance(int ball_player,struct player * p)
{
     int o,w,d,v=1000;
     if (player_no==1)
     {
          for (o=1;o<=11;o++)
          {
                          
             d=preqp(p[ball_player].x,p[ball_player].y,p[o].x,p[o].y);
             if(d<v)
             {
                v=d;
                w=o;
             }  
          }
          p[0].x=p[w].x;p[0].y=p[w].y;        
     }   
     if (player_no==2)
     {
          for (o=12;o<=22;o++)
          {
                          
             d=preqp(p[ball_player].x,p[ball_player].y,p[o].x,p[o].y);
             if(d<v)
             {
                v=d;
                w=o;
             }  
          }
          p[0].x=p[w].x;p[0].y=p[w].y;        
     }   
}//end of no chance function  
  int checkintercept(int ball_player,int r,struct player *p)
 {
     int l,m,o;
     if((p[ball_player].x >p[r].x)&&(p[ball_player].y>p[r].y))
     {
      for (l=p[ball_player].x,m=p[ball_player].y;l>=p[r].x,m>=p[r].y;l--,m--)
      {
          for( o=1;o<=22;o++)
          {
               if(p[o].x==l && p[o].y==m)
                {
                             if (player_no==1)
                             {
                                              if (11<o<23)
                                              return 1;
                             }
                             if (player_no==2)
                             {
                                              if (0<o<12)
                                              return 1;
                             }           
               }         
          
          }
          return 0;
      }       
     }
     if((p[ball_player].x >p[r].x)&&(p[ball_player].y<p[r].y))
     {
      for (l=p[ball_player].x,m=p[ball_player].y;l>=p[r].x,m<=p[r].y;l--,m++)
      {
          for( o=1;o<=22;o++)
          {
               if(p[o].x==l && p[o].y==m)
               {
                             if (player_no==1)
                             {
                                              if (11<o<23)
                                              return 1;
                             }
                             if (player_no==2)
                             {
                                              if (0<o<12)
                                              return 1;
                             }           
               }         
          }
          return 0;
      }       
     }
     if((p[ball_player].x <p[r].x)&&(p[ball_player].y>p[r].y))
     {
      for (l=p[ball_player].x,m=p[ball_player].y;l<=p[r].x,m>=p[r].y;l++,m--)
      {
          for( o=1;o<=22;o++)
          {
               if(p[o].x==l && p[o].y==m)
                {
                             if (player_no==1)
                             {
                                              if (11<o<23)
                                              return 1;
                             }
                             if (player_no==2)
                             {
                                              if (0<o<12)
                                              return 1;
                             }           
               }         
          
          }
          return 0;
      }       
     }
     if((p[ball_player].x <p[r].x)&&(p[ball_player].y<p[r].y))
     {
      for (l=p[ball_player].x,m=p[ball_player].y;l<=p[r].x, m<=p[r].y;l++,m++)
      {
          for( o=1;o<=22;o++)
          {
               if(p[o].x==l && p[o].y==m)
                 {
                             if (player_no==1)
                             {
                                              if (11<o<23)
                                              return 1;
                             }
                             if (player_no==2)
                             {
                                              if (0<o<12)
                                              return 1;
                             }           
               }         
                           
 
          }
          return 0;
      }       
     }
     
}//end of checkintercept function  
  int player( struct player *p)        //main player func 
{
	
	 int a,j,i,flag=1;     //ball_player is used to find which player is having the possession of the ball or whether the ball
	 register int s=0;                            //is at empty slot
	  

	 //assigning limits according to player no.
	 if(player_no==1)
	 {

		pl=1;            //pl shows the lower limit and ph shows the upper limit of players in the array of structures ,i.e. if player
		ph=11;           //is 1st then his players will be 1 to 11 and if he is 2nd then his players will be 12 to 22
		player_num=1;
	 }

	 else
	 {
		  pl=12;
		  ph=22;
		  player_num=2;
	 }

      check(p);
      
      //moving the goal keeper
      
      if(player_no==1)
      {
       if (p[0].x>40)
       {
                    p[1].x=15;
                    p[1].y=p[0].y;
                    ball_player=1;
       
       }
       if(p[0].x<40)
       {
                    p[1].x=p[0].x;
                    p[1].y=p[0].y;
                    
       }
      }    
      if(player_no==2)
      {
                     if(p[0].x<59)
                      {p[12].x=85;
                      p[12].y=p[0].y;}
                      if(p[0].x>59)
                      {
                                   p[12].x=p[0].x;
                                   p[12].y=p[0].y;
                                   ball_player=12;
                      }  
      }               
             
	 // checking where is ball

			//player having the ball

    for(i=1;i<23;i++)
    if( p[0].x==p[i].x && p[0].y==p[i].y )
    {
        ball_player=i;
        break;    
    }  
    
    if (i==23)
    {
       //so no player is having the ball
       
		  a=case3(p);
        		 
		 return a;   //returns the hitter of the ball to the controller 
    }
    
    
	 if((i<=11&&player_no==1)||(i>11&&player_no==2))
    {
        //then ball is with my team player
        
			a=case1(i,p);
			check(p);
		 
        return a;
    }
    
    
    // ball with opp team player
    
	  a=case2(i,p);
    check(p);
    return a;
    
    
}//end of player func.
        
    






//definition of case1() , when the ball is with my player


int case1(int ball_player,struct player * p)
{   
     //moving the goal keeper
        
              int i,j,k,leave[11];
    if(player_no==1)
    
    { 
                    if(ball_player ==1)
    {
                    
      if(p[2].strength>=p[3].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      p[0].x=p[2].x;
                                      p[0].y=p[2].y;
                                      
                                      return 1;
      }
      if(p[3].strength>p[2].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[3].x;
                                      p[0].y=p[3].y;
                                      
                                      return 1;
      }
    }                                                                    
     if(ball_player==2)
     {
                        if(p[4].strength>=p[5].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[4].x;
                                      p[0].y=p[4].y;
                                      
                                      return 2;
      }
      if(p[5].strength>p[4].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[5].x;
                                      p[0].y=p[5].y;
                                      
                                      return 2;
      }
     }
     if(ball_player==3)
     {
                        if(p[4].strength>=p[6].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[4].x;
                                      p[0].y=p[4].y;
                                      
                                      return 3;
      }
      if(p[6].strength>p[4].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[6].x;
                                      p[0].y=p[6].y;
                                      
                                      return 3;
      }
     }
     if(ball_player==4)
     {
              if(p[7].strength>=p[8].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[7].x;
                                      p[0].y=p[7].y;
                                      
                                      return 4;
      }
      if(p[8].strength>p[7].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[8].x;
                                      p[0].y=p[8].y;
                                      return 4;
      }         
     }
     if(ball_player==5)
     {
                       if(p[7].strength>=p[4].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[7].x;
                                      p[0].y=p[7].y;
                                      return 5;
      }
      if(p[4].strength>p[7].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[4].x;
                                      p[0].y=p[4].y;
                                      return 5;
      }
                       }
     if(ball_player==6)
     {if(p[8].strength>=p[4].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[8].x;
                                      p[0].y=p[8].y;
                                      return 6;
      }
      if(p[4].strength>p[8].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[4].x;
                                      p[0].y=p[4].y;
                                      return 6;
      }}
     if(ball_player==7)
     {if(p[9].strength>=p[8].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[9].x;
                                      p[0].y=p[9].y;
                                      return 7;
      }
      if(p[8].strength>p[9].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[8].x;
                                      p[0].y=p[8].y;
                                      return 7;
      }}
     if(ball_player==8)
     {
                       if(p[9].strength>=p[7].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[9].x;
                                      p[0].y=p[9].y;
                                      return 8;
      }
      if(p[7].strength>p[9].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[7].x;
                                      p[0].y=p[7].y;
                                      return 8;
      }
     }
     if(ball_player==9)
     {                  if(p[11].strength>=p[10].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[11].x;
                                      p[0].y=p[11].y;
                                      return 9;
      }
      if(p[10].strength>p[11].strength)
      {
                                      //r=2;
                                      //g=checkintercept(ball_player,r,p);
                                      //if(g==1)
                                      //{nochance(ball_player,p);
                                      //return 1;}
                                      
                                      p[0].x=p[10].x;
                                      p[0].y=p[10].y;
                                      return 9;
      }
     }
   
     if(ball_player==10)
     { 
        j=0;
       int c=0;
     
       for(i=12;i<22;i++)
       { 
                          
                 if(p[i].x=14)
                 leave[j]=p[i].y;
             j++;
                      c++;
                          
    }
  for(k=10;k<=40;k++)
   {
    for(j=0;j<=c;j++)
    {
                   if(k==leave[j])
                 continue;
             else
           p[0].y=k;p[0].x=14;
           return 10;
    }
   }    
}

 


     if(ball_player==11)
     { 
        j=0;
       int c=0;
 
       for(i=12;i<22;i++)
       { 
                          
                 if(p[i].x=14)
                 leave[j]=p[i].y;
             j++;
                      c++;
                          
    }
  for(k=10;k<=40;k++)
   {
    for(j=0;j<=c;j++)
    {
                   if(k==leave[j])
                 continue;
             else
           p[0].y=k;p[0].x=14;
           return 11;
    }
   }
}
    
} 
//end of if player_no==1 
     
                        
 //( in_range(ball_player,p) )
   //
       //then player having the ball is in range of the goal,i.e. the y-coordinates or the coloumn coordinates of the player is 
        //between 10 and 40
        
    //  if(player_num==1)                  //hits the ball straight with max hitter strength towards the opponent's goal 
      //p[0].x+=p[ball_player].strength/2;
                                           //player_num tells which team the participant is and on which side the player has to hit
     // else                               //the ball
        
     // p[0].x-=p[ball_player].strength/2;   //strength is divided by 2 because strength required by ball to move from one spot to 
                                          //another is double the difference between those spots when the ball is hit straight ,and 
                     //when ball is hit at some angle then the strength req can be calculated by using the preqpb
                                          //function
  
   
   
   //if ball is not in the range of the ball
   
   //this loop searches for a player who is ahead of the presnt player having the possession of the ball and if any such player is 
   //found then ball is passed to him
  // for(i=pl;i<=ph;i++)
   //if( (p[i].x>p[ball_player].x&&player_num==1)/*||  (p[i].x<p[ball_player].x&&player_num==2)*/)
   
  // {
    //   p[0].x=p[i].x;
      // p[0].y=p[i].y;
    //   return ball_player;
  // }
   
   //if no such player is found then the ball is simply hit straight with max strength of the hitter of the ball
// if(player_num==1)
// p[0].x+=p[ball_player].strength/2;
// else
// p[0].x-=p[ball_player].strength/2;
   
   
   //return ball_player;
   //if(p[0].x=p[10].x&&p[0].y=p[10].y || p[0].x=p[11].x&&p[0].y=p[11].y)
 if(player_no==2)
    
    { 
                    if(ball_player ==12)
    {
      if(p[13].strength>=p[14].strength)
      {
                                      r=13;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 12;}
                                      p[0].x=p[13].x;
                                      p[0].y=p[13].y;
                                      
                                      return 12;
      }
      if(p[14].strength>p[13].strength)
      {
                                      r=14;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 12;}
                                      
                                      p[0].x=p[14].x;
                                      p[0].y=p[14].y;
                                      
                                      return 12;
      }
    }                                                                    
     if(ball_player==13)
     {
                        if(p[15].strength>=p[16].strength)
      {
                                      r=15;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 13;}
                                      
                                      p[0].x=p[15].x;
                                      p[0].y=p[15].y;
                                      
                                      return 13;
      }
      if(p[16].strength>p[15].strength)
      {
                                      r=16;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 13;}
                                      
                                      p[0].x=p[16].x;
                                      p[0].y=p[16].y;
                                      
                                      return 13;
      }
     }
     if(ball_player==14)
     {
                        if(p[15].strength>=p[17].strength)
      {
                                      r=15;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 14;}
                                      
                                      p[0].x=p[15].x;
                                      p[0].y=p[15].y;
                                      
                                      return 14;
      }
      if(p[17].strength>p[15].strength)
      {
                                      r=17;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 14;}
                                      
                                      p[0].x=p[17].x;
                                      p[0].y=p[17].y;
                                      
                                      return 14;
      }
     }
     if(ball_player==15)
     {
              if(p[18].strength>=p[19].strength)
      {
                                      r=18;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 15;}
                                      
                                      p[0].x=p[18].x;
                                      p[0].y=p[18].y;
                                      
                                      return 15;
      }
      if(p[19].strength>p[18].strength)
      {
                                      r=19;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 15;}
                                      
                                      p[0].x=p[19].x;
                                      p[0].y=p[19].y;
                                      return 15;
      }         
     }
     if(ball_player==16)
     {
                       if(p[18].strength>=p[15].strength)
      {
                                      r=18;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 16;}
                                      
                                      p[0].x=p[18].x;
                                      p[0].y=p[18].y;
                                      return 16;
      }
      if(p[15].strength>p[18].strength)
      {
                                      r=15;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 16;}
                                      
                                      p[0].x=p[15].x;
                                      p[0].y=p[15].y;
                                      return 16;
      }
                       }
     if(ball_player==17)
     {if(p[19].strength>=p[15].strength)
      {
                                      r=19;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 17;}
                                      
                                      p[0].x=p[19].x;
                                      p[0].y=p[19].y;
                                      return 17;
      }
      if(p[15].strength>p[19].strength)
      {
                                      r=15;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 17;}
                                      
                                      p[0].x=p[15].x;
                                      p[0].y=p[15].y;
                                      return 17;
      }}
     if(ball_player==18)
     {if(p[20].strength>=p[19].strength)
      {
                                      r=18;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 18;}
                                      
                                      p[0].x=p[20].x;
                                      p[0].y=p[20].y;
                                      return 18;
      }
      if(p[19].strength>p[20].strength)
      {
                                      r=19;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 18;}
                                      
                                      p[0].x=p[19].x;
                                      p[0].y=p[19].y;
                                      return 18;
      }}
     if(ball_player==19)
     {
                       if(p[20].strength>=p[18].strength)
      {
                                      r=20;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 19;}
                                      
                                      p[0].x=p[20].x;
                                      p[0].y=p[20].y;
                                      return 19;
      }
      if(p[18].strength>p[20].strength)
      {
                                      r=18;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 19;}
                                      
                                      p[0].x=p[18].x;
                                      p[0].y=p[18].y;
                                      return 19;
      }
     }
     if(ball_player==20)
     {                  if(p[22].strength>=p[21].strength)
      {
                                      r=22;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 20;}
                                      
                                      p[0].x=p[22].x;
                                      p[0].y=p[22].y;
                                      return 20;
      }
      if(p[21].strength>p[22].strength)
      {
                                      r=21;
                                      g=checkintercept(ball_player,r,p);
                                      if(g==1)
                                      {nochance(ball_player,p);
                                      return 20;}
                                      
                                      p[0].x=p[21].x;
                                      p[0].y=p[21].y;
                                      return 20;
      }
     }
    
     if(ball_player==21)
     { 
        j=0;
       int c=0;
       for(i=1;i<11;i++)
       { 
                          
                 if(p[i].x=86)
                 leave[j]=p[i].y;
             j++;
                      c++;
                          
    }
  for(k=10;k<=40;k++)
   {
    for(j=0;j<=c;j++)
    {
                   if(k==leave[j])
                 continue;
             else
           p[0].y=k;p[0].x=86;
           return 21;
    }
   }    
}

 


     if(ball_player==22)
     { 
        j=0;
       int c=0;
       for(i=1;i<11;i++)
       { 
                          
                 if(p[i].x=86)
                 leave[j]=p[i].y;
             j++;
                      c++;
                          
    }
  for(k=10;k<=40;k++)
   {
    for(j=0;j<=c;j++)
    {
                   if(k==leave[j])
                 continue;
             else
           p[0].y=k;p[0].x=86;
           return 22;
    }
   }
}
    
  
}
     
      
       
                      
     
}                     // end of case1() func.
   
        




// Definition of case2() func.

//ball is with opp team's player
int case2(int ball_player,struct player * p)
{   
    int i,a;
    int strreq;
    int f,z,flag=0;
 //this for loop searches for a player who has more strength than the opponent's player having possession of the ball ,after 
 //reaching at the ball's position and if such player is found then the case becomes similar to one when my player was having the 
 //possession of the ball ,so the case1 function is called and finally the hitter of ball is returned to controller   
	 int v=preqp(p[ball_player].x,p[ball_player].y,p[1].x,p[1].y);
	 int l=p[1].strength-v-p[ball_player].strength;
       
     for(i=pl;i<=ph;i++)
    {
       strreq=preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y);
       z=p[i].strength - strreq - p[ball_player].strength; 
       if( z>l)
       {
          f=i;
          l=z;
          flag=1;
       }
    }
    if(flag=0)
    f=1;
    p[f].x=p[ball_player].x;
    p[f].y=p[ball_player].y;
    a=case1(f,p);
   
   
   
  //if no such player is found then it simply returns a -1 i.e. , it don't want to hit the ball and skips the turn 
   return -1;
   
}//end of case2 func.





//definition of case3() func.

//when ball is with no player

int case3(struct player * p)
{
	 int player_num=0,i,a,strreq,large=0;
  
  //this for loop searches for a player of my team such that after reaching at the position of the ball it is having the maximum
  //strength left to hit the ball   
	 for(i=pl;i<=ph;i++)
    {
				strreq=preqp(p[i].x,p[i].y,p[0].x,p[0].y);
                                              
            if(  (p[i].strength - strreq )  >  large)  //large is having max strength of the player after reaching there 
            {                                        //player_no is having the no. of the desired player   
                 player_num=i;
                 large=p[i].strength-strreq;
            }             //end of if 
             
    }      //end of for loop
    
    
   //if such player is found having maximum and non-zero strength left after reaching the position of the ball then that player
   //is moved to ball's position and case1 function is called as the situation is similar to that when my player is having the 
   //possession of the ball 
    if(player_num!=0)
    {
      p[player_num].x=p[0].x;
      p[player_num].y=p[0].y;
      
      a=case1(player_num,p);
      return a;
    }
    
    //if no player is found having non-zero strength after reaching the ball's position the move is skipped 
    return -1;
    
    
} // end of case3()






//in_range is a function defined by the participant 
//it checks wheter the ball is in the range of the goal or not and returns 1 or 0 accordingly

//int in_range(int ball_player,struct player * p)
//{
//    if(  (p[ball_player].y>=10) && (p[ball_player].y<=40) )
//    return 1;
//    return 0;
//}    
void check(struct player *p)
{    
     int i;
     if (player_no==1)
     {
                   for(i=1;i<=11;i++)
                   {
                                    if(i==1)
                                     p[1].x=15;p[1].y=25;
                                     if(i==2)
                                     p[2].x=28;p[2].y=15;
                                     if(i==3)
                                     p[3].x=28;p[3].y=35;
                                     if(i==4)
                                     p[4].x=41;p[4].y=25;
                                     if(i==5)
                                     p[5].x=40;p[5].y=5;
                                     if(i==6)
                                     p[6].x=40;p[6].y=45;
                                     if(i==7)
                                     p[7].x=51;p[7].y=15;
                                     if(i==8)
                                     p[8].x=51;p[8].y=35;
                                     if(i==9)
                                     p[9].x=60;p[9].y=26;
                                     if(i==10)
                                     p[10].x=73;p[10].y=20;
                                     if(i==11)
                                     p[11].x=73;p[11].y=30;
                   }                                  
         
         }
          if (player_no==2)
     {
                   for(i=12;i<=22;i++)
                   {
                                    
                                    
                                     if(i==12)
                                     p[12].x=85;p[12].y=25;
                                     if(i==13)
                                     p[13].x=72;p[13].y=15;
                                     if(i==14)
                                     p[14].x=72;p[14].y=35;
                                     if(i==15)
                                     p[15].x=59;p[15].y=25;
                                     if(i==16)
                                     p[16].x=60;p[16].y=5;
                                     if(i==17)
                                     p[17].x=60;p[17].y=45;
                                     if(i==18)
                                     p[18].x=49;p[18].y=15;
                                     if(i==19)
                                     p[19].x=49;p[19].y=35;
                                     if(i==20)
                                     p[20].x=40;p[20].y=26;
                                     if(i==10)
                                     p[21].x=27;p[21].y=20;
                                     if(i==22)
                                     p[22].x=27;p[22].y=30;
                   }                                  
         
         }



         }};   //end of the class team0002
