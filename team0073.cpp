#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#include<math.h>

class team0005  //here the class name is given to be team0002 assuming that the registration no. of the participant was 2 
{
  private:      //private fns and variables defined
  int pl,ph,player_num,player_no,pl1,ph1,strmin;
  
   int preqp(int finalx,int finaly, int initialx ,int initialy )  //function which tells the strength req by player to move from 
	{float req;                                                    //place to another
    req=floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
    return (int)req;}     

  int preqbp(int finalx,int finaly, int initialx ,int initialy )   //function which tells the strength req by hitter of ball to hit
	{float req; int i;                                            //the ball from one place to another
    req=2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	//i=req;
	 return int(req);} 
    
  //public functions
  public:
    int init(int team_number, struct player *p,char farray[][51])   //the mandatory function which initialises the team no. of the 
	{                                                  //participant and tells him the initial field distribution
		player_no = team_number;
		
	}
    
    int shoot_area(int ball_player,struct player *p) //to check if player is in shooting range
    {    
        
        if( (player_no==1 && p[ball_player].x>60) || (player_no==2 && p[ball_player].x<40))
        {   int y=10,x,j;
            if(player_no==1)        
            {
                 strmin=preqbp(86,y,p[ball_player].x,p[ball_player].y);
            }
            else
            {
                 strmin=preqbp(14,y,p[ball_player].x,p[ball_player].y);
            }                           

            for(y;y<=40;y++)
            {
                           if(player_no==1)
                            {
                                x=preqbp(86,y,p[ball_player].x,p[ball_player].y);
                                 
                            }
                            else
                            {
                                 x=preqbp(14,y,p[ball_player].x,p[ball_player].y);
                            }
                            
                            if(x<strmin)
                              {
                                        strmin=x;        
                                        j=y;
                              }
             }

             if(p[ball_player].strength>=strmin)
             {
                                                // check interception        
                  if(player_no==1)
                  {
                        if(p[12].y!=j)
                        {          
                                  p[0].x=86;
                                  p[0].y=j;
                        }         
                  }                                                    
                  else
                  {
                        if(p[1].y!=j)
                        {
                                  p[0].x=14;
                                  p[0].y=j;
                        }          
                  }
                  return 0;
              }                         
              else 
              {
                   return 1;
              }     
       }              
  }    

             
              
  int player( struct player *p)        //main player func 
{
	static int z=0;
	 int i,j,ball_player,a;     //ball_player is used to find which player is having the possession of the ball or whether the ball
	                             //is at empty slot
	  

	 //assigning limits according to player no.
	 if(player_no==1)
	 {

		pl=1;            //pl shows the lower limit and ph shows the upper limit of players in the array of structures ,i.e. if player
		ph=11; 
        pl1=12;
        ph1=22;          //is 1st then his players will be 1 to 11 and if he is 2nd then his players will be 12 to 22
		player_num=1;
	 }

	 else
	 {
		  pl=12;
		  ph=22;
		  pl1=1;
		  ph1=11;
		  player_num=2;
	 }

// moving my attackers from my half to opposite half
/*     if((z==0 || (p[5].x==30)&&(p[5].y==10)&&(p[6].x==30)&&(p[7].x==30)&&(p[6].y==25)&&(p[7].y==40))&& player_no==1)
     {
             p[5].x=60;
             p[5].y=11;
             p[6].x=71;
             p[6].y=21;
             p[7].x=60;
             p[7].y=39;
             p[11].x=50;
             p[11].y=25;
     
             p[0].x=60;
             p[0].y=11;
             
             z++;
             return 11;
             
     }       
     else
      if(z==0 || ((p[16].x==70)&&(p[16].y==10)&&(p[17].x==70)&&(p[18].x==70)&&(p[17].y==25)&&(p[18].y==40)))
      {
               p[16].x=40;
               p[16].y=11;
               p[17].x=29;
               p[17].x=21;
               p[18].x=40;
               p[18].y=39;
               z++;
      }         

*/
                           
	 if(z==0 || z==1)
 {
     
   if(player_num==1)
     {
            if(z==0)
            {
                            
                            p[1].x=15  ;p[1].y=25  ;
                            //   p[2].x=27  ;p[2].y=10  ;
                            //   p[3].x=27  ;p[3].y=40  ;
                            //  p[4].x=40  ;p[4].y=20  ;
                                  p[5].x=40  ;p[5].y= 30 ;
                            //   p[6].x=50  ;p[6].y=5  ;
                            p[7].x= 65 ;p[7].y= 25 ;
                            p[8].x= 50 ;p[8].y= 45 ;
                            p[9].x= 60 ;p[9].y= 10 ;
                            p[10].x= 60 ;p[10].y= 40 ;
                            p[11].x= 50 ;p[11].y= 25 ;           // positioning of players in my very first move
            }                 
     
     
     
     int min,q[4],t,s;
     q[4]={2,3,4,6};
     for(int k=pl1;k<=ph2;k++)
     {  
             if(p[k].x<=40)
             { 
                    s=0;       
                    min=strreq(p[k].x,p[k].y,p[q[i]].x,p[[q]i].y);
                    for(int y=0;y<4;y++)
                    {
                            if((strreq(p[k].x,p[k].y,p[q[i]].x,p[[q]i].y)<min)
                            {
                               min=strreq(p[k].x,p[k].y,p[q[i]],p[q[i].].y);
                               t=i;
                            }
                    }
             }
             p[t].x=p[k].x;
             p[t].y=p[k].y;
     }                           
                                   
}                         
     
   else
     {
      p[12].x=85  ;p[12].y=25  ;
     // p[12].x=73  ;p[i++].y= 10 ;
     // p[i].x=73  ;p[i++].y= 40 ;
      //p[i].x=60  ;p[i++].y= 20 ;
      p[16].x= 60 ;p[16].y= 30 ;
     // p[i].x=50  ;p[i++].y= 5 ;
      p[18].x=35  ;p[18].y= 25 ;
      p[19].x= 50 ;p[19].y=  45;
      p[20].x=40  ;p[20].y=  10;
      p[21].x= 40 ;p[21].y= 40 ;
      p[22].x=50  ;p[22].y= 25 ;           // positioning of players in my very first move
     
          int min,q[4],t,s;
     q[4]={2,3,4,6};
     int a1=
     for(int k=pl1;k<=ph2;k++)
     {  
             if(p[k].x<=40)
             { 
                    s=0;       
                    min=strreq(p[k].x,p[k].y,p[q[s]].x,p[[q]s].y);
                    for(int y=0;y<4;y++)
                    {
                            if((strreq(p[k].x,p[k].y,p[q[s]].x,p[q[s]].y)<min)
                            {
                               min=strreq(p[k].x,p[k].y,p[q[s]],p[q[s].].y);
                               t=s;
                            }
                    }
             }
             p[t].x=p[k].x;
             p[t].y=p[k].y;
             
     }

     z++;
 }      
      
	 // checking where is ball

			//player having the ball

	 for(i=1;i<23;i++)
    if( p[0].x==p[i].x && p[0].y==p[i].y )
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
    else
    {
	  a=case2(i,p);
    
    return a;
   }
    
}//end of player func.
        
    






//definition of case1() , when the ball is with my player


int case1(int ball_player,struct player * p)
{   
    
    int i=pl; 
    int j=23,max=mstrength(i,p);
    
         
          
                                          
                            
                              
      if(shoot_area(ball_player,p)!=0)
      {      
           if((player_no==1 && p[0].x<40) || (player_no==2 && p[0].x>60))
            {
                             ++i;
            } 
            for(i;i<=ph;i++)
            {
             
             if(ball_player!=i)
               {
                     if((player_no==1 && p[i].x>=p[ball_player].x) || (player_no==2 && p[i].x<=p[ball_player].x))
                     {
                            if(preqbp(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y)>=0)    
                             {  
                                                                                        
                                                                                             
                               if(mstrength(i,p)>max)
                               {
                                        max=mstrength(i,p);
                                        j=i;
                               }
                             } 
                     }
               }                            
            }
     
    
    
        if(j!=23)
        {     
              int x=p[ball_player].x;
              int y=p[ball_player].y;
                       // to check interception
              int flag=0;                   
              for(int i=pl1;i<=ph1;i++)
              {
                      if( (p[i].x>p[ball_player].x && player_no==1) || (p[i].x<p[ball_player].x && player_no==2))
                      {
                         if(p[j].y>=y)
                         {
                            while( (x>=p[j].x && player_no==2  && y<=p[j].y)  || (x<=p[j].x && player_no==1 && y<=p[j].y) )
                            {
                                 if(player_no==1)
                                  {
                                                  x++;
                                  }
                                 else
                                   {
                                                  x--;
                                   }
                                 y++;
                                 if(p[i].x==x && p[i].y==y)
                                 {
                                              ++flag;
                                              break;
                                  }
                            }// end of while

                            while (!(p[j].x==x && p[j].y==y))
                            {
                                  if(x==p[j].x)
                                  {
                                               y++;
                                               if(p[i].x==x && p[i].y==y)
                                               {
                                                   ++flag;
                                                    break;
                                                }
                                  }
                                  else
                                  {
                                      if(player_no==1)
                                      {
                                                      x++; 
                                                      if(p[i].x==x && p[i].y==y)
                                                      {
                                                             ++flag;
                                                             break;
                                                      }
                                      }
                                      else
                                      {
                                          x--;
                                          if(p[i].x==x && p[i].y==y)
                                          {
                                              ++flag;
                                              break;
                                           }  
                                      }                              
                                  }
                            }                           
                         }// end of if  
                         else
                         {
                             while( (x<=p[j].x && player_no==2 && y>=p[j].y )   || (  x>=p[j].x && player_no==1 && y>=p[j].y )  ) 

                             {
                                if(player_no==1)
                                {
                                                x++;
                                }
                                else
                                {
                                                x--;
                                }
                                y--;
                                if(p[i].x==x && p[i].y==y)
                                {
                                            ++flag;
                                            break;
                                 }
                              }// end of while  

                              while (!(p[j].x==x && p[j].y==y))
                            {
                                  if(x==p[j].x)
                                  {
                                               y--;
                                               if(p[i].x==x && p[i].y==y)
                                               {
                                                   ++flag;
                                                    break;
                                                }
                                  }
                                  else
                                  {
                                      if(player_no==1)
                                      {
                                                      x++; 
                                                      if(p[i].x==x && p[i].y==y)
                                                      {
                                                             ++flag;
                                                             break;
                                                      }
                                      }
                                      else
                                      {
                                          x--;
                                          if(p[i].x==x && p[i].y==y)
                                          {
                                              ++flag;
                                              break;
                                           }  
                                      }                              
                                  }
                            }
                          }//end of else
                             
                                               
                        
                   }    
        }//end of for
               
              if(flag!=0)// if ball is intercepted backpass the ball
              {
                     
                     for(int t=pl;t<=ph;t++)
                     {
                             if( (p[t].x<p[ball_player].x && player_no==1) || (p[t].x>p[ball_player].x && player_no==2))
                             {
                                 if( preqbp(p[t].x,p[t].y,p[ball_player].x,p[ball_player].y)-p[ball_player].strength >=0 && (fintercept_check(p[t].x,p[t].y,p[ball_player].x,p[ball_player].y,p)==0))
                                 {
                                        p[0].x=p[t].x;
                                        p[0].y=p[t].y;             
                                 }
                             }
                     }       
                             
                    
                    //p[0].y=p[ball_player].y + 1;             
                      
                      
              }
              else
              {   
                      p[0].x=p[j].x;
                      p[0].y=p[j].y;
              }       
 
         }
        

    
   
  
}  
  
// obstructing the ball by goalkeeper

 if(player_no==1)
 {
                if(p[0].x<=40)     
                 {
                           if(p[pl].strength-preqp(p[pl].x,p[0].y,p[pl].x,p[pl].y)>=0)
                           {
                                    p[pl].y=p[0].y;
                           }        
                 }          
 }
 else
 {
                if(p[0].x>=60)
                {
                     if(p[pl].strength-preqp(p[pl].x,p[0].y,p[pl].x,p[pl].y)>=0)
                      {
                               p[pl].y=p[0].y;
                      }

                }             
 }    
  


 return ball_player;
  
 
}                     // end of case1() func.
   
        



//definition of mstrength()


int mstrength(int k,struct player *p)
{   
     int q;
     int min;
     min=p[k].strength-(p[pl1].strength-preqp(p[k].x,p[k].y,p[pl1].x,p[pl1].y));
     for(int i=pl1;i<=ph1;i++)
     {
              q=( p[k].strength-(p[i].strength-preqp(p[k].x,p[k].y,p[i].x,p[i].y)));
              if(q<min)
              { 
                       min=q;
              }        
              
              
      }
      return q;
}     
// Definition of case2() func.

//ball is with opp team's player
int case2(int ball_player,struct player * p)
{   int i=pl,a;
    int strreq;
    int maxstr;
    maxstr=((p[i].strength-preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y))-p[ball_player].strength);
     
 //this for loop searches for a player who has more strength than the opponent's player having possession of the ball ,after 
 //reaching at the ball's position and if such player is found then the case becomes similar to one when my player was having the 
 //possession of the ball ,so the case1 function is called and finally the hitter of ball is returned to controller   
	 for(i=pl;i<=ph;i++)
    {
       strreq=((p[i].strength-preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y))-p[ball_player].strength);
       if(strreq>maxstr)
       {
                        maxstr=strreq;
                        a=i;
       }
       
       if( maxstr>0 )
       {
           p[a].x=p[0].x;
           p[a].y=p[0].y;
           
           return case1(a,p);
                 
       }
       else
       {
           p[a].x=p[0].x;
           p[a].y=p[0].y;
           return -1;
       }   
   
   
   
   
       //if no such player is found then it simply returns a -1 i.e. , it don't want to hit the ball and skips the turn 
   
   }//end of case2 func.


}


//definition of case3() func.

//when ball is with no player


int case3(struct player * p)
{
	 int player_n=23,i=pl,a,strreq,large=0;
	 
  
  //this for loop searches for a player of my team such that after reaching at the position of the ball it is having the maximum
  //strength left to hit the ball   
	 for(i;i<=ph;i++)
    {
           strreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);          
				
            
            if(  (p[i].strength - strreq )  >  large)  //large is having max strength of the player after reaching there 
            {                                        //player_no is having the no. of the desired player   
                 player_n=i;
                 large=p[i].strength-strreq;
            }             //end of if 
             
    }      //end of for loop
    
    
   //if such player is found having maximum and non-zero strength left after reaching the position of the ball then that player
   //is moved to ball's position and case1 function is called as the situation is similar to that when my player is having the 
   //possession of the ball 
    if(player_n!=23)
    {
      p[player_n].x=p[0].x;
      p[player_n].y=p[0].y;
      
      a=case1(player_n,p);
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
       
 ////////////////////////////////        
         
  int fintercept_check(int ix,int iy,int fx,int fy,struct player *p)//fx initial ix final
    {
      int validposx,validposy,xdiffb,ydiffb;int i;
      char status='0';      
      int l;
      
      validposx=fx;validposy=fy;
while((validposx!=ix)&&(validposy!=iy))
 {
    xdiffb=validposx-ix;   //calculates the difference between changed coordinates and initial coordinates of the
	ydiffb=validposy-iy;   //ball

	  if(validposx!=ix)
	    (xdiffb<0)?(validposx)++:(validposx)--;
	  if(validposy!=iy)
	    (ydiffb<0)?(validposy)++:(validposy)--;

	if(player_no==1)
	 {
       for(i=12;i<=22;i++)
	   {
	    if((validposx==p[i].x)&&(validposy==p[i].y))
	      {
		status='i';
		l=0;
        break;
		  }
	   }
     if(l==0)
       break;     
     } 
    else
     {
       for(i=1;i<=11;i++)
	   {
	    if((validposx==p[i].x)&&(validposy==p[i].y))
	      {
		    status='i';
            l=0;
		    break;
	      }
	   }
	   if(l==0)
         break;	   
     }     
          
 }
 
     if(status=='i')
	   return 1;
	 else
	   return 0;
    }
 
 
};   //end of the class team0002
