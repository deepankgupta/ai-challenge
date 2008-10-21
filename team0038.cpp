#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

using namespace std;
class team0038 
{
      public:
             int init(int team_number, struct player *p,char farray[][51])	         
             {
                 team_no=team_number;
                 if(team_no==1)
                 {
                               ol=12;oh=22;
                 }
                 else
                 {
                               ol=1;oh=11;
                 }
             }
             //this fn implements our stratergy and should call all other fns which we define                            
             int player(struct player *p)
             {
                 if(team_no==1)
                 {
                               pl=1;
                               ph=11;
                 }
                 else
                 {
                               pl=12;
                               ph=22;
                 }
             
                 //check if the ball is with any player
                 int ball_player=0;
                 for(int i=1;i<23;i++)
                         if((p[0].x==p[i].x)&&(p[0].y==p[i].y))
                         {
                                                ball_player=i;
                                                break;
                         }
                 if(ball_player==0)//no player is having the ball
                                        return(no_plyr_ball(p));
                 else if((ball_player<=11&&team_no==1)||(ball_player>11&&team_no==2))//ball is with my player
                                        return (my_plyr_ball(ball_player,p));
                 else//ball is with opposite team
                                        return (opp_plyr_ball(ball_player,p));                                                                                               
             }
      private:
              int team_no,pl,ph,ol,oh;  
              //this fn returns the strength req to move your player from one place to another 
              int preqp(int finalx,int finaly, int initialx ,int initialy )
              {
                  float req;
                  req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
                  return (int)req;
              }     
              //this fn returns the strength req by your hitter to move the ball from one place to another 
              int preqpb(int finalx,int finaly, int initialx ,int initialy )
              {
                  float req; int i;
                  req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	              i=(int)req;
	              return i;
               }
              //in_range is a function defined by the participant 
             //it checks wheter the ball is in the range of the goal or not and returns 1 or 0 accordingly
             int in_drange(int ball_player,struct player * p)
             {
                 if(  (p[ball_player].y>=5) && (p[ball_player].y<=45) )
                      return 1;
                 return 0;
             }
             //fn to check if the ball will be intercepted if hit straight
             int intercept1(int a, int ball_player, struct player * p)
             {
                 for(int i = ol;i<=oh;i++)
                 {
                         if(a==p[i].y)
                         {
                                                     if(team_no==1)
                                                     {
                                                                   if(p[i].x > p[ball_player].x)
                                                                             return 1;
                                                     }
                                                     else
                                                     {
                                                                   if(p[i].x < p[ball_player].x)
                                                                             return 1;
                                                     }          
                         }
                 }
                 //no such player
                 return 0;             
             }
             //fn to find the first opposite team player that will intercept the ball if the ball is hit straight
             int intercept2(int ball_player, struct player * p)
             {
                 int a=100, k=0, b=0, f=0;
                 for(int i=ol;i<=oh;i++)
                 {        if(p[ball_player].y==p[i].y)
                          {
                                                     if(team_no==1)//shoot south
                                                     {
                                                                   // the i'th plyr x coord shld be least but greater than ball_player 
                                                                   //xcoord i.e. shoul be in front of ball_player
                                                                   if(p[i].x<a && p[i].x > p[ball_player].x)
                                                                   {
                                                                               f=1;
                                                                               a=p[i].x;
                                                                               k=i;
                                                                   }
                                                     }
                                                     //team no 2 shoot north
                                                     else
                                                     {
                                                                   // the i'th plyr x coord shld be max but smaller than ball_player 
                                                                   //xcoord i.e. shoul be in front of ball_player
                                                                   if(p[i].x>b && p[i].x < p[ball_player].x)
                                                                   {
                                                                               f=1;
                                                                               b=p[i].x;
                                                                               k=i;
                                                                   }
                                                     }
                          }
                 }
                 if(f==0)
                         return 0;
                 else
                 {
                    // printf("\n%d\n",k);
                     return k;
                     }
             }
             //fn to check if the ball will be intercepted if hit straight. Here only those opp team layers will 
             //be checked which are in front of the ball_player                                                             
             int intercept(int ball_player, struct player * p)
             {
                 for(int i = ol;i<=oh;i++)
                 {
                         if(p[ball_player].y==p[i].y)
                         {
                                                     if(team_no==1)
                                                     {
                                                                   if(p[i].x > p[ball_player].x)
                                                                             return 1;
                                                     }
                                                     else
                                                     {
                                                                   if(p[i].x < p[ball_player].x)
                                                                             return 1;
                                                     }          
                         }
                 }
                 //no such player
                 return 0;
             }
             // Opposite team have the ball
              int opp_plyr_ball(int ball_player,struct player * p)
              {   
                 int i,a;
                 int strreq;
                 int str[23]={0};
                 for(i=pl;i<=ph;i++)
                 {
                                    strreq=preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y);
                                    if( (p[i].strength - strreq )> p[ball_player].strength )
                                    {
                                        p[i].x=p[ball_player].x;
                                        p[i].y=p[ball_player].y;
           
                                        a=my_plyr_ball(i,p);
                                        return a;       
                                        }
                 }
                 for(i=pl;i<=ph;i++)
                 {
                                    str[i]=p[i].strength-preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y);
                 }
                 int temp=0;
                 for(i=pl;i<=ph;i++)
                 for(int j= i+1;j<=ph;j++)
                         if(str[j]>str[i])
                         {
                                          temp=str[i];
                                          str[i]=str[j];
                                          str[j]=temp;
                         }
                            
                 int k;
                 for(i=pl;i<=ph;i++)
                 {
                                    if((p[i].strength-preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y))==str[pl+1])
                                    {
                                     if(team_no==1)
                                     {
                                                      p[i].x=p[ball_player].x-1;
                                                      p[i].y=p[ball_player].y;
                                     }
                                     else
                                     {
                                         p[i].x=p[ball_player].x+1;
                                         p[i].y=p[ball_player].y;
                                         }
                                     break;
                 }
                          k = i;
           } 
           int b;
           for(i=pl;i<=ph;i++)
           { 
             if(i!=k)
             if((p[i].strength-preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y))==str[pl+2])
             {
              if(team_no==1)
              {
               p[i].x=p[ball_player].x-1;
               p[i].y=p[ball_player].y-1;
              }
              else
              {
               p[i].x=p[ball_player].x+1;
               p[i].y=p[ball_player].y-1;
              }
              break;
             }
             b=i;
           } 
           for(i=pl;i<=ph;i++)
           { 
             if(i!=k && i!=b)
             if((p[i].strength-preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y))==str[pl+3])
             {
              if(team_no==1)
              {
               p[i].x=p[ball_player].x-1;
               p[i].y=p[ball_player].y+1;
              }
              else
              {
               p[i].x=p[ball_player].x+1;
               p[i].y=p[ball_player].y+1;
              }
              break;
             }
           } 
      return -1; 
}//end of case2 func.

          int my_plyr_ball(int ball_player, struct player* p)
             {
                 int max=0, strreq, plyr_no=0;
                 if(in_drange(ball_player,p))//the current player is in range of the dee(instead of goal)
                 {
                                       //check if there is any oppposite team player in front of the player having the ball
                                       if(!intercept(ball_player, p))
                                       {
                                                               if(team_no==1)
                                                                             p[0].x+=(p[ball_player].strength/2);
                                                               else
                                                                             p[0].x-=(p[ball_player].strength/2);
                                                               return ball_player;
                                       }
                                       else//there is an opposite team player in front
                                       {
                                                   //opp team kth player CAN intercept the ball if hit straight
                                                   int k=intercept2(ball_player, p);
                                                   //if hit diagonally with full strength the max x displacement can be a = strength by 3
                                                   int a = p[ball_player].strength/3;
                                                   //we have to maximise the x displacement
                                                   if(team_no==1)
                                                   {
                                                   //case 1: if hit straight with full strength then x displacement = strength/2
                                                   // and if the opp team player is beyond tat then it is better to hit straight
                                                   //than hit diagonally.Also bring another player just behind the ball
                                                                 if(p[k].x>(p[ball_player].x + p[ball_player].strength/2))
                                                                 {
                                                                                             //hit straight with full str
                                                                                             p[0].x+=(p[ball_player].strength/2);
                                                                                             int plyr_no = 0, large =0;
                                                                                             //find a plyr with str left after reaching the position just before the ball
                                                                                             for(int g=pl;g<=ph;g++)
                                                                                             {
                                                                                                     
                                                                                                     if(g==ball_player)
                                                                                                               continue;
                                                                                                     int strreq = preqp(p[0].x-1,p[0].y,p[g].x,p[g].y);
                                                                                                     if(p[g].strength - strreq > large)
                                                                                                     {
                                                                                                                      plyr_no = g;
                                                                                                                      large = p[g].strength -strreq;
                                                                                                     }
                                                                                             }
                                                                                             //bring that player behind the ball
                                                                                             if(plyr_no!=0)
                                                                                             {
                                                                                                           p[plyr_no].x=p[0].x-1;
                                                                                                           p[plyr_no].y=p[0].y;                                                                                                           
                                                                                             }
                                                                                             return ball_player;
                                                                                             //no such player found dont bring any player
                                                                                             //it will be interceptd with the ball_player
                                                                 }
                                                   //case 2 : when str/3<p[k].x-p[ball_player].x<str/2 then its better to hit the ball straight and
                                                   //place the ball just before opp team player(this will save strength)
                                                           if((p[k].x > (p[ball_player].x + p[ball_player].strength/3))&& (p[k].x < (p[ball_player].x + p[ball_player].strength/2)))
                                                           {
                                                                     //hit till p[k].x-1
                                                                     p[0].x=p[k].x-1;
                                                                     //find closest player behind the ball
                                                                     int plyr_no = 0, large =0;
                                                                     //find a plyr with str left after reaching the position just before the ball
                                                                     for(int g=pl;g<=ph;g++)
                                                                     {
                                                                                            if(g==ball_player)
                                                                                                              continue;
                                                                                            int strreq = preqp(p[0].x-1,p[0].y,p[g].x,p[g].y);
                                                                                            if(p[g].strength - strreq > large)
                                                                                            {
                                                                                                             plyr_no = g;
                                                                                                             large = p[g].strength -strreq;
                                                                                            }
                                                                     }
                                                                     //bring that player behind the ball
                                                                     if(plyr_no!=0)
                                                                     {
                                                                                   p[plyr_no].x=p[0].x-1;
                                                                                   p[plyr_no].y=p[0].y;
                                                                                   
                                                                     }
                                                                     //no such player found dont bring any player
                                                                     //it will be interceptd with the ball_player
                                                                     return ball_player;
                                                           }
                                                   //case 3 : its better to hit diagonally with full strength than hit straight
                                                   }
                                                   //team no = 2
                                                   else
                                                   {
                                                   //case 1: if hit straight with full strength then x displacement = strength/2
                                                   // and if the opp team player is beyond tat then it is better to hit straight
                                                   //than hit diagonally.Also bring another player just behind the ball
                                                                 if(p[k].x<(p[ball_player].x - p[ball_player].strength/2))
                                                                 {
                                                                                             //hit straight with full str
                                                                                             p[0].x-=(p[ball_player].strength/2);
                                                                                             int plyr_no = 0, large =0;
                                                                                             //find a plyr with str left after reaching the position just before the ball
                                                                                             for(int g=pl;g<=ph;g++)
                                                                                             {
                                                                                                     if(g==ball_player)
                                                                                                              continue;
                                                                                                     int strreq = preqp(p[0].x+1,p[0].y,p[g].x,p[g].y);
                                                                                                     if(p[g].strength - strreq > large)
                                                                                                     {
                                                                                                                      plyr_no = g;
                                                                                                                      large = p[g].strength -strreq;
                                                                                                     }
                                                                                             }
                                                                                             //bring that player behind the ball
                                                                                             if(plyr_no!=0)
                                                                                             {
                                                                                                           p[plyr_no].x=p[0].x+1;
                                                                                                           p[plyr_no].y=p[0].y;
                                                                                        
                                                                                             }
                                                                                                                return ball_player;
                                                                                             //no such player found dont bring any player
                                                                                             //it will be interceptd with the ball_player
                                                                 }
                                                   //case 2 : when str/3<p[k].x-p[ball_player].x<str/2 then its better to hit the ball straight and
                                                   //place the ball just before opp team player(this will save strength)
                                                           if((p[k].x < (p[ball_player].x - p[ball_player].strength/3)) && (p[k].x > (p[ball_player].x - p[ball_player].strength/2)))
                                                           {
                                                                     //hit till p[k].x-1
                                                                     p[0].x=p[k].x+1;
                                                                     //find closest player behind the ball
                                                                     int plyr_no = 0, large =0;
                                                                     //find a plyr with str left after reaching the position just before the ball
                                                                     for(int g=pl;g<=ph;g++)
                                                                     {
                                                                                            if(g==ball_player)
                                                                                                              continue;
                                                                                            int strreq = preqp(p[0].x+1,p[0].y,p[g].x,p[g].y);
                                                                                            if(p[g].strength - strreq > large)
                                                                                            {
                                                                                                             plyr_no = g;
                                                                                                             large = p[g].strength -strreq;
                                                                                            }
                                                                     }
                                                                     //bring that player behind the ball
                                                                     if(plyr_no!=0)
                                                                     {
                                                                                   p[plyr_no].x=p[0].x+1;
                                                                                   p[plyr_no].y=p[0].y;

                                                                     }
                                                                     return ball_player;
                                                                     //no such player found dont bring any player
                                                                     //it will be interceptd with the ball_player
                                                           }
                                                   //case 3 : its better to hit diagonally with full strength than hit straight
                                                   }                                               
                                                   //case 3 of both teams
                                                   //chk if both diagonals are available free, then choose between either of two
                                                   if(!intercept1((p[ball_player].y)-1,ball_player,p)&&!intercept1((p[ball_player].y)+1,ball_player,p))
                                                   {
                                                                                         if(p[ball_player].y<25)//should shoot east
                                                                                         {
                                                                                                          if(team_no==1)//shoot SE
                                                                                                          {
                                                                                                                      p[0].x+=p[ball_player].strength/3;
                                                                                                                      p[0].y+=p[ball_player].strength/3;
                                                                                                                      return ball_player;
                                                                                                          }
                                                                                                          if(team_no==2)//shoot NE
                                                                                                          {
                                                                                                                      p[0].x-=p[ball_player].strength/3;
                                                                                                                      p[0].y+=p[ball_player].strength/3;
                                                                                                                      return ball_player;                                                                                            
                                                                                                          }
                                                                                         }
                                                                                         //else shoot in west
                                                                                         if(team_no==1)//shoot SW
                                                                                         {
                                                                                                       p[0].x+=p[ball_player].strength/3;
                                                                                                   p[0].y-=p[ball_player].strength/3;
                                                                                                   return ball_player;
                                                                                         }
                                                                                         if(team_no==2)//shoot NW
                                                                                         {
                                                                                                       p[0].x-=p[ball_player].strength/3;
                                                                                                   p[0].y-=p[ball_player].strength/3;
                                                                                                   return ball_player;
                                                                                         }        
                                                   }
                                                   //chk if there is an opp player on NW/SW/SE?NE
                                                   if(!intercept1((p[ball_player].y)-1,ball_player,p))//there is no opp team player on NW/SW
                                                   {
                                                                                         if(team_no==1)//no player on SW so hit the ball with full strength
                                                                                         //equally in either direction i.e. strength/3 in +X and -Y
                                                                                         {
                                                                                                   p[0].x+=p[ball_player].strength/3;
                                                                                                   p[0].y-=p[ball_player].strength/3;
                                                                                                   return ball_player;
                                                                                         }
                                                                                         if(team_no==2)//no player on NW so hit the ball with full strength
                                                                                         //equally in either direction i.e. strength/3 in -x and -Y          
                                                                                         {
                                                                                                   p[0].x-=p[ball_player].strength/3;
                                                                                                   p[0].y-=p[ball_player].strength/3;
                                                                                                   return ball_player;
                                                                                         }                                                                                        
                                                   }
                                                   //chk if there is an opp plater on NE/SE
                                                   if(!intercept1((p[ball_player].y)+1,ball_player,p))
                                                   {
                                                                                         if(team_no==1)//no player on SE so hit the ball with full strength
                                                                                         //equally in either direction i.e. strength/3 in +X and +Y
                                                                                         {
                                                                                                   p[0].x+=p[ball_player].strength/3;
                                                                                                   p[0].y+=p[ball_player].strength/3;
                                                                                                   return ball_player;
                                                                                         }
                                                                                         if(team_no==2)//no player on NE so hit the ball with full strength
                                                                                         //equally in either direction i.e. strength/3 in -x and +Y          
                                                                                         {
                                                                                                   p[0].x-=p[ball_player].strength/3;
                                                                                                   p[0].y+=p[ball_player].strength/3;
                                                                                                   return ball_player;
                                                                                         }                                                                                        
                                                   }
                                                   //my player is covered in N/NW/NE or S/SW/SE
                                                   //hence find a closest player with maximum strength after reaching a step behind 
                                                   //my player to intercept the ball
                                                   //int max=0, strreq, plyr_no=0;
                                                   if(team_no==1)//bring a plyer to the N of the ball_player
                                                   {
                                                                         //search for a player having max and non zero strength after reachng that posn
                                                                         for(int i=pl;i<=ph;i++)
                                                                         {
                                                                                 strreq=preqp(p[ball_player].x-1,p[ball_player].y,p[i].x,p[i].y);
                                                                                 if((p[i].strength-strreq)>max)
                                                                                 {
                                                                                                               plyr_no=i;
                                                                                                               max=p[i].strength - strreq;
                                                                                 }
                                                                         }
                                                                         //if such a player found
                                                                         if(plyr_no!=0)
                                                                         {              p[plyr_no].x=p[ball_player].x-1;
                                                                                       p[plyr_no].y=p[ball_player].y;
                                                                                       return -1;//ball didnt moved
                                                                                       }
                                                                         //if no such player found do nothing                                                                                                    
                                                                         return -1;
                                                   }
                                                   //bring a player to the S of the ball_player
                                                   for(int i=pl;i<=ph;i++)
                                                   {
                                                           strreq=preqp(p[ball_player].x+1,p[ball_player].y,p[i].x,p[i].y);
                                                                          if((p[i].strength-strreq)>max)
                                                                          {
                                                                                                        plyr_no=i;
                                                                                                        max=p[i].strength - strreq;
                                                                          }
                                                   }
                                                   if(plyr_no!=0)
                                                   {              p[plyr_no].x=p[ball_player].x+1;
                                                                 p[plyr_no].y=p[ball_player].y;
                                                                 return -1;//ball didnt moved
                                                   }
                                                   //if no such player found do nothing                                                                                                                          
                                                   return -1;
                                       }
                 }
                 else//the player having the ball is not in the goal/dee range, then find the player in my team 
                 //most ahead currently with maximum streangth, is in the goal/dee range and pass the ball 
                 //to him also bring another player just behind that player for support      
                 {
                      //this loop searches for a player who is outside our dee having maximum strength
                      //and is in the drange and if any such player is found then ball is passed to him
                      int max=0,u=0;
                      for(int i=pl;i<=ph;i++)
                      if( (p[i].x>p[ball_player].x&&team_no==1&&in_drange(i,p))  ||  (p[i].x<p[ball_player].x&&team_no==2&&in_drange(i,p))  )
                      {
                          if(p[i].strength>max)
                          {
                                               max=p[i].strength;
                                               u=i;
                          }
                      }
                      if(u!=0)
                      {
                          p[0].x=p[u].x;
                          p[0].y=p[u].y;
                          return ball_player;
                      }
   
                      //if no such player is found then the ball is simply hit straight with max strength of the hitter of the ball
                      if(team_no==1)
                                       p[0].x+=p[ball_player].strength/2;
                      else
                                       p[0].x-=p[ball_player].strength/2;
   
                      return ball_player;  
                 }
             }

//when ball is with no player
int no_plyr_ball(struct player * p)
{
	 int player_no=0,a,strreq,large=0;
  
  //this for loop searches for a player of my team such that after reaching at the position of the ball it is having the maximum
  //strength left to hit the ball   
	 for(int i=pl;i<=ph;i++)
    {
				strreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);
            
            if(  (p[i].strength - strreq )  >  large)  //large is having max strength of the player after reaching there 
            {                                        //player_no is having the no. of the desired player   
                 player_no=i;
                 large=(p[i].strength - strreq);
            }             //end of if 
             
    }      //end of for loop
    
    
   //if such player is found having maximum and non-zero strength left after reaching the position of the ball then that player
   //is moved to ball's position and case1 function is called as the situation is similar to that when my player is having the 
   //possession of the ball 
    if(player_no!=0)
    {
      p[player_no].x=p[0].x;
      p[player_no].y=p[0].y;
      
      a=my_plyr_ball(player_no,p);
      return a;
    }
    
    //if no player is found having non-zero strength after reaching the ball's position the move is skipped 
    return -1;
    
    
} // end of case3()
             
      
};
