#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
class team0089 //here the class name is given to be team0002 assuming that the registration no. of the participant was 2 
{
  private:      //private fns and variables defined
  int pl,ph,player_num,player_no;
  int team;
  
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
    
    
  int player( struct player *p)        //main player func 
{
	
	 int i,j,ball_player,a;     //ball_player is used to find which player is having the possession of the ball or whether the ball
	                             //is at empty slot
	  

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





	 // checking where is ball

			//player having the ball

	 for(i=1;i<23;i++)
    if(( p[0].x==p[i].x) && (p[0].y==p[i].y) )
    {
        ball_player=i;
        break;    
    }  
    
    if(i==23)
    {
       //so no player is having the ball
       
		  a=case3(p);
		 
		 return a;   //returns the hitter of the ball to the controller 
    }
    
    
	 if((i<=11&&player_no==1)||(i>11&&player_no==2))
    {
        //then ball is with my team player
        
			a=case1(i,p);
		 
        return a;
    }
    
    
    // ball with opp team player
    
	  a=case2(i,p);
    
    return a;
    
    
}//end of player func.
        
    






//definition of case1() , when the ball is with my player


int case1(int ball_player,struct player * p)
{   
    int i,q;
	 if( in_range(ball_player,p) )
    {
        //then player having the ball is in range of the goal,i.e. the y-coordinates or the coloumn coordinates of the player is 
        //between 10 and 40
        
        q=ballhitdir(p,ball_player);                 //hits the ball straight with max hitter strength towards the opponent's goal 
                                           //player_num tells which team the participant is and on which side the player has to hit
        return q;                               //the ball
        
          //strength is divided by 2 because strength required by ball to move from one spot to 
                                          //another is double the difference between those spots when the ball is hit straight ,and 
                       //when ball is hit at some angle then the strength req can be calculated by using the preqpb
                                          //function
   }
   
   
   //if ball is not in the range of the ball
   
   //this loop searches for a player who is ahead of the presnt player having the possession of the ball and if any such player is 
   //found then ball is passed to him
   for(i=pl;i<=ph;i++)
      {
                                      
           if( (p[i].x>p[ball_player].x&&player_num==1)  ||  (p[i].x<p[ball_player].x&&player_num==2)  )
   
             {
                
                p[0].x=p[i].x;
                p[0].y=p[i].y;
                return ball_player;
             }
       }//for
   //if no such player is found then the ball is simply hit straight with max strength of the hitter of the ball
   if(player_num==1)
   p[0].x+=p[ball_player].strength/2;
   else
   p[0].x-=p[ball_player].strength/2;
   
   
   return ball_player;
   
}                     // end of case1() func.
   
        




// Definition of case2() func.

//ball is with opp team's player
int case2(int ball_player,struct player * p)
{   int i,a;
    int strreq,large=0;
    int player_no=0;
 
 //this for loop searches for a player who has more strength than the opponent's player having possession of the ball ,after 
 //reaching at the ball's position and if such player is found then the case becomes similar to one when my player was having the 
 //possession of the ball ,so the case1 function is called and finally the hitter of ball is returned to controller   
	 for(i=pl;i<=ph;i++)
    {
       strreq=preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y);
       
       if( ((p[i].strength - strreq )> p[ball_player].strength)&&((p[i].strength-strreq)>large) )
       {  
           large=(p[i].strength-strreq); 
             player_no=i;
       }
     
   }
   if(player_no!=0)
   {  i=player_no;
    p[player_no].x=p[ball_player].x;
    p[player_no].y=p[ball_player].y;
           
    a=case1(i,p);
    return a;
   }//if
   
  //if no such player is found then it simply returns a -1 i.e. , it don't want to hit the ball and skips the turn 
   if(player_no==0)
   return -1;
   
}//end of case2 func.





//definition of case3() func.

//when ball is with no player

int case3(struct player * p)
{
	 int player_no=0,i,a,strreq,large=0;
  
  //this for loop searches for a player of my team such that after reaching at the position of the ball it is having the maximum
  //strength left to hit the ball   
	 for(i=pl;i<=ph;i++)
    {
				strreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);
            
            if(  (p[i].strength - strreq )  >  large)  //large is having max strength of the player after reaching there 
            {                                        //player_no is having the no. of the desired player   
                 player_no=i;
                 large=p[i].strength-strreq;                                                                                                                   
            }             //end of if 
             
    }      //end of for loop
    
    
   //if such player is found having maximum and non-zero strength left after reaching the position of the ball then that player
   //is moved to ball's position and case1 function is called as the situation is similar to that when my player is having the 
   //possession of the ball 
    if(player_no!=0)
    {
      p[player_no].x=p[0].x;
      p[player_no].y=p[0].y;
      
      a=case1(player_no,p);
      return a;
    }
    
    //if no player is found having non-zero strength after reaching the ball's position the move is skipped 
    return -1;
    
    
} // end of case3()






//in_range is a function defined by the participant 
//it checks wheter the ball is in the range of the goal or not and returns 1 or 0 accordingly

int in_range(int ball_player,struct player * p)
{
    if(  (p[ball_player].y>=10) && (p[ball_player].y<=40) )
    return 1;
    return 0;
}    
  
int intercept(int initx, int inity, int finx, int finy,struct player *p)
{
     int i=inity;
     int j=initx;
     if(player_num==1)
     {
       if(finy==inity)
        {
         while(j<=finx)
         {             
          for(int k=12;k<=22;k++)
           {
             
               if(j==p[k].x)
                {return 1;
                } 
           }//for 
           j++; 
         }//while             
          return 0;
        }//if loop              
      else if(finy>inity)
      {                 
       while(i<=finy || j<=finx)
      {
        for(int k=12;k<=22;k++)
        {
             if(i==p[k].y&&j==p[k].x)
              {return 1;
               break;
               } 
        }//for                 
        if(i!=finy&&j!=finx)
         {i++;
          j++;
         }
         else if(i==finy&&j!=finx)
          j++;
           else if(i!=finy&&j==finx)
            i++;
            else if(i==finy&&j==finx)
              return 0;
     }//while
     }//if
     else if(finy<inity)
     {
        while(i>=finy && j<=finx)
        {
         for(int k=12;k<=22;k++)
         {
              if(i==p[k].y&&j==p[k].x)
               {return 1;
                break;
                } 
         }//for                 
         if(i!=finy&&j!=finx)
          {i--;
           j++;
          }
          else if(i==finy&&j!=finx)
           j++;
            else if(i!=finy&&j==finx)
             i--;
             else if(i==finy&&j==finx)
               return 0;
     }//while  
     }//else if
     }//if
     else if(player_num==2)
     {
          

       if(finy==inity)
        {
         while(j>=finx)
         {             
          for(int k=1;k<=11;k++)
           {
             
               if(j==p[k].x)
                {return 1;
                 
                } 
           }//for 
           j--; 
         }//while             
          return 0;
        }//if loop    
       if(finy<inity)
      {
      while(i>=finy || j>=finx)
      {
        for(int k=1;k<=11;k++)
        {
             if(i==p[k].y&&j==p[k].x)
              {return 1;
               break;
               } 
        }//for                 
        if(i!=finy&&j!=finx)
         {i--;
          j--;
         }
         else if(i==finy&&j!=finx)
          j--;
           else if(i!=finy&&j==finx)
            i--;
            else if(i==finy&&j==finx)
               return 0;
      }//while
      }//if
      else if(finy>inity)
      {
        while((i<=finy) || (j>=finx))
         {
          for(int k=1;k<=11;k++)
           {
              if(i==p[k].y&&j==p[k].x)
              {return 1;
               
               } 
           }//for                 
        if(i!=finy&&j!=finx)
         {i++;
          j--;
         }
         else if(i==finy&&j!=finx)
          j--;
           else if(i!=finy&&j==finx)
            i++;
            else if(i==finy&&j==finx)
            {
                  return 0;
            }
                 
      }//while        
      }//else if
      }//elseif     
     
}  
       
int balloutside(int finx)  
{
    if( ( finx<0 && player_num==2 ) || ( finx>100 && player_num==1 ) )
    return 1;
    else
    return 0;
}//balloutside    
    

int ballhitdir(struct player*p,int ball_player)
{
    int k,m,b,c,i,j,d,a;
    int dir=0;
    int check;
    k=p[ball_player].x+p[ball_player].strength/2;
    m=p[ball_player].y;
    b=p[ball_player].x-p[ball_player].strength/2;
    c=p[ball_player].y;
    if(player_num==1)
    a=intercept(p[ball_player].x,p[ball_player].y,k,m,p);
    else if(player_num==2)
    a=intercept(p[ball_player].x,p[ball_player].y,b,m,p);
        if(a==0)
        {
           check=balloutside(p[ball_player].x+p[ball_player].strength/2);
           if(check==1)
           {
             if(player_num==1)
             {
              p[0].x=86;
              return ball_player;
             }
             else if(player_num==2)
             {
                  p[0].x=14;
                  return ball_player;
             }
           }  
            else if(check==0)
            {
                               
               if(player_num==1)     
               p[0].x=k;
               else if(player_num==2)
               p[0].x=b;
               return ball_player;
            }   
        }
        j=a;  
         while(a==1) // field se bahar jaane ki cndition
         {
             dir++;
             
              m=m+dir;
              if(player_no==1)
              a=intercept(p[ball_player].x,p[ball_player].y,k,m,p);
              else if(player_no==2)
              a=intercept(p[ball_player].x,p[ball_player].y,b,m,p);    
                    
         }
         d=dir;
         dir=0;
         while(j==1)
         {
             dir--;
             m=m-dir;
             if(player_no==1)
             j=intercept(p[ball_player].x,p[ball_player].y,k,m,p);
             else if(player_no==2)
             j=intercept(p[ball_player].x,p[ball_player].y,b,m,p);
         }     
         if(d<abs(dir))
         {
 
            check=balloutside(p[ball_player].x+p[ball_player].strength/2);
            if(check==1)
             {
               if(player_num==1)
               {
                p[0].x=86;
                return ball_player;
               }
               else if(player_num==2)
               {
                   p[0].x=14;
                   return ball_player;
               }
             }//if    
            else if(check==0)
            {            
               if(player_num==1)
               {
                  p[0].x=k;
                  p[0].y+=d;
                  return ball_player;   
               }
              else if(player_num==2)
               {
                   p[0].x=b;
                   p[0].y+=d;
                   return ball_player;
               }
            } 
         }          
         else if(d>abs(dir))
         {
            check=balloutside(p[ball_player].x+p[ball_player].strength/2);
            if(check==1)
             {
               if(player_num==1)
               {
                p[0].x=86;
                return ball_player;
               }
               else if(player_num==2)
               {
                   p[0].x=14;
                   return ball_player;
               }
             }
            else if(check==0)
            {    
             if(player_num==1)
             {
              p[0].x=k;
              p[0].y+=dir;
              return ball_player;
             }
             else if(player_num==2)
             {
                  p[0].x=b;
                  p[0].y+=dir;
                  return ball_player;
             }
            } 
          }//else                     
return ball_player;

         
}      
         
         };   //end of the class team0002
