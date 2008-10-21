#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// if there are errors like forward declaration of struct player and like this then include the below commented code for removal of errors .
/*
struct player 
{
       int x,y,strength;
       int team_num;
       };
struct player p[22];
*/

using namespace std;

class team0046  //The name of your class should be teamxxxx where xxxx is the no. u will get at the time of registration and will
{                //be unique for every participant
  private:
  
  int team,pl,ph,player_num,ball_player;  
  int move;
             //team is a variable used in player function which tells all of the functions defined by the participant what their team no. is 
             //it is not mandatory for the player to use this variable .player can use any other means to satisfy the need
             //pl defines the lower limit of the team player.
             //ph defines the upper limit of the team player .
             //ball_player defines the player having the ball.(either of our team or of other team.)  
  //private fns 
  
  //this fn returns the strength req to move your player from one place to another 
  
  int preqp(int finalx,int finaly, int initialx ,int initialy )
	{float req;
    req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
    return (int)req;}     

//this fn returns the strength req by your hitter to move the ball from one place to another 

   int preqpb(int finalx,int finaly, int initialx ,int initialy )
	{float req; int i;
    req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	 i=(int)req;
	 return i;} 
     
     //this function returns the distance between two points 
     double distance(int finalx,int finaly,int initialx,int initialy)
	 {
      double d= sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2));      
         return d ;   
      }
   
    //this function tells about any player of opposite team coming in between .
      
	int interception (int finalx,int finaly,int initialx ,int initialy,struct player * p )
     {
     int i;
     double d1,d2,d3;
       if(team==1)//if our team is 1 then player interception due to other team is examined.
       {  
                       //player no. 12 to 22 is examined .
                for(i=12;i<=22;i++)
                {
                                   d1=distance(finalx,finaly,p[i].x,p[i].y);
                                   d2=distance(finalx,finaly,initialx,initialy);
                                   d3=distance(initialx,initialy,p[i].x,p[i].y);
                                   
                                   if(d2=d1+d3)
                                   return 1; // function returns 1 if any player found in between .
                                        
                 }
        }
        
        else
        {          //if our team is 2 then player no. 1 to 11 are examined .
                for(i=1;i<=11;i++)
                {
                                   d1=distance(finalx,finaly,p[i].x,p[i].y);
                                   d2=distance(finalx,finaly,initialx,initialy);
                                   d3=distance(initialx,initialy,p[i].x,p[i].y);
                                   
                                   //here the distances follow the given condition if player intercepts .
                                   
                                   if(d2=d1+d3)
                                   return 1;
                                   
      
                 }
            }     
                     
            return 0; // if no other opposite team player found in between then 0 is returned . 
     
     }//end of funtion 
     
  
      
  public:
         
   int init(int team_number, struct player *p,char farray[][51])   // this fn must be there in your program ,it will be called only 
	{                                                             //once at the beginning of the program .It will tell u whether u are 
      team=team_number;
      move = 1 ;                                 //here move gives the no. of move cuurrently going on .
                                                 //player 1 or 2 and this will also give u the basic fieldarray ie where there is  
	}                                                  //a goal or a dee or a boundary and struct player *p gives u the initial player 
                                                 //distribution in the field
          
          //function to change player coordinates 
          
 
  int player( struct player *p)        //main player func 
{
	       
	 int i,j,a;     //ball_player is used to find which player is having the possession of the ball or whether the ball
	                             //is at empty slot
	  

	 //assigning limits according to player no.
	 if(team==1)
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

     //initial distribution of players settled according to move no.
                 
     if(move==1)
     {    
         
          if(team==2)
            {
               for(i=12;i<=22;i++)
             
               {
                   switch (p[i].x)
                   {
                           case 60 : if(p[i].y==10)
                                      { 
                                                   p[i].x=15;
                                      
                                                   p[i].y=7;
                                       }
                                      else if (p[i].y==40)
                                      { 
                                                   p[i].x=45;
                                      
                                                   p[i].y=42;
                                       }
                                       else 
                                       { 
                                                   p[i].x=55;
                                      
                                                   p[i].y=25;
                                       }
                                       
                                      break;
                                                      
                           
                           
                           case 70 :   if(p[i].y==10)
                                      { 
                                                   p[i].x=41;
                                      
                                                   p[i].y=5;
                                       }
                                      else if (p[i].y==40)
                                      { 
                                                   p[i].x=41;
                                      
                                                   p[i].y=45;
                                       }
                                       else 
                                       { 
                                                   p[i].x=59;
                                      
                                                   p[i].y=5;
                                       }
                                        break; 
                           
                           
                           
                           
                           case 75 :   if(p[i].y==10)
                                      { 
                                                   p[i].x=70;
                                      
                                                   p[i].y=10;
                                       }
                                      else if (p[i].y==40)
                                      { 
                                                   p[i].x=70;
                                      
                                                   p[i].y=40;
                                       }
                                       else 
                                       { 
                                                   p[i].x=55;
                                      
                                                   p[i].y=45;
                                       }
                                        break; 
                           
                           
                               
                          }//end of switch statement               
                                 }      //end of for loop 
                      
                      
                      }///end of if statement 
          else 
          {   
          
              for(i=1;i<=11;i++)
                                         
              {
                   switch (p[i].x)
                   {
                           case 40 : if(p[i].y==10)
                                      { 
                                                   p[i].x=82;
                                      
                                                   p[i].y=7;
                                       }
                                      else if (p[i].y==40)
                                      { 
                                                   p[i].x=82;
                                      
                                                   p[i].y=42;
                                       }
                                       else 
                                       { 
                                                   p[i].x=44;
                                      
                                                   p[i].y=25;
                                       }
                                       
                                      break;
                                                      
                           
                           
                           case 30 :   if(p[i].y==10)
                                      { 
                                                   p[i].x=56;
                                      
                                                   p[i].y=10;
                                       }
                                      else if (p[i].y==40)
                                      { 
                                                   p[i].x=56;
                                      
                                                   p[i].y=45;
                                       }
                                       else 
                                       { 
                                                   p[i].x=45;
                                      
                                                   p[i].y=5;
                                       }
                                        break; 
                           
                           
                           
                           
                           case 25 :   if(p[i].y==10)
                                      { 
                                                   p[i].x=30;
                                      
                                                   p[i].y=10;
                                       }
                                      else if (p[i].y==40)
                                      { 
                                                   p[i].x=30;
                                      
                                                   p[i].y=40;
                                       }
                                       else 
                                       { 
                                                   p[i].x=45;
                                      
                                                   p[i].y=45;
                                       }
                                        break; 
                           
                           
                               
                          }//end of switch statement               
                                 }      //end of for loop 
                                   
          
                                        }//end of else statement 
          move++;
          
          return -1 ;
          
                }//end of moving players initially 
     


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
    
    
	 if((i<=11&&team==1)||(i>11&&team==2))
    {
        //then ball is with my team player
        
			a=case1(i,p);
		 
        return a;
    }
    
    
    // ball with opp team player
    
	  a=case2(i,p);
    
    return a;
    
    
}//end of player func.
        
       
     int case1(int ball_player,struct player * p)
     {
                int i ;
          
           // case when the ball player near the goal post within the DEE .
                  //case when player is of team 2 
           
        if (team==2)
        {    
             for(i=1;i<=14;i++)
             {
                     if(   ( distance(p[ball_player].x,p[ball_player].y,i,10)<p[ball_player].strength/2) && (! interception(p[ball_player].x,p[ball_player].y,i,10,p) ) )
                         
                      {
          
                       p[0].x = i ;
                       p[0].y =10 ;
                       return ball_player ;
                                                  }
                         
                               }//end of first for loop 
                               
             for(i=10;i<=40;i++)
             {
                     if(   ( distance(p[ball_player].x,p[ball_player].y,14,i)<p[ball_player].strength/2 ) && (! interception(p[ball_player].x,p[ball_player].y,14,i,p) ) )
                         
                      {
          
                       p[0].x = 14 ;
                       p[0].y =i ;
                       return ball_player ;
                       
                       }   // end of if condition       
                  
                  }//end of second for loop 
                                    
              for(i=14;i>=1;i--)
              {
                   if(   ( distance(p[ball_player].x,p[ball_player].y,i,40)<p[ball_player].strength/2  ) && (! interception(p[ball_player].x,p[ball_player].y,i,40,p) ) )
                         
                      {
          
                       p[0].x = i ;
                       p[0].y =40 ;
                       return ball_player ;
                       }// end of if condition 
                       
                   }//end of third for loop                  
                                            
                   //checking condition when the player team is 1
               
               if(team==1) 
               
               {
                  for(i=99;i>=86;i--)
                   {
                     if(   ( distance(p[ball_player].x,p[ball_player].y,i,10)<p[ball_player].strength/2) && (! interception(p[ball_player].x,p[ball_player].y,i,10,p) ) )
                         
                      {
          
                       p[0].x = i ;
                       p[0].y =10 ;
                       return ball_player ;
                                                  }// end of if 
                         
                               }//end of first for loop 
                               
             for(i=10;i<=40;i++)
             {
                     if(   ( distance(p[ball_player].x,p[ball_player].y,86,i)<p[ball_player].strength/2  ) && (! interception(p[ball_player].x,p[ball_player].y,86,i,p) ) )
                         
                      {
          
                       p[0].x = 86 ;
                       p[0].y =i ;
                       return ball_player ;
                       }
                                 
                  }//end of second for loop 
                                    
              for(i=86;i<=99;i++)
              {
                   if(   ( distance(p[ball_player].x,p[ball_player].y,i,40)<p[ball_player].strength/2 ) && (! interception(p[ball_player].x,p[ball_player].y,i,40,p) ) )
                         
                      {
          
                       p[0].x = i ;
                       p[0].y =40 ;
                       return ball_player ;
                       }               
                   }//end of third for loop                  
                                            
               
                    }//end of else statement 
               
                  // first three loops didnot work due to poor strength of player so goal cant be hit by him .
                 
                  //following conditions applies in that case 
                  
                // player with no interception and also ahead of him searched if found then ball passed to him  
                
             
                 for(i=pl;i<=ph;i++)
                { 
                                    if( (p[i].x>p[ball_player].x&&team==1)  ||  (p[i].x<p[ball_player].x&&team==2) && ! (interception(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y,p)) )
   
                                   {                               
                 
                                                   
                                                             p[0].x=p[i].x;
                                                             p[0].y=p[i].y;
                                                             return ball_player;
                                                      
                                   } //end of if case
                       
                         }// end of for loop                           
        
                        // the possibility is that there is interception between player or strength of player is low to pass the ball .
                          
                          // the casse when interception is there and player possessing ball is stand still and other players moved to remove interception .
                                   
                  for(i=pl;i<=ph;i++)
                 { 
                                    if( (p[i].x>p[ball_player].x&&team==1)  ||  (p[i].x<p[ball_player].x&&team==2) )
   
                                   {                               
                 
                                                   do{
                                                                   
                                                               p[i].x = p[i].x - 1 ;
                                                               p[i].y =p[i].y + 1 ;   
                                                                   
                                                                  
                                                         }while (! (interception(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y,p)));
                                                                                                         
                                    } //end of if case
                                                           
                                                           // when interception is removed then player is passed the ball and ball player is returned .
                                                            
                                                             p[0].x=p[i].x;
                                                             p[0].y=p[i].y;
                                                             return ball_player;
                                           
                                              
                         }// end of for loop                           
                           
                               
                                                   
                         
           //if no such player is found then the ball is simply hit straight with max strength of the hitter of the ball
                         
        // if by chance the whole above code fells down then only following case is applied 
        
                            if(player_num==1)
                             p[0].x+=p[ball_player].strength/2;
                               else
                                  p[0].x-=p[ball_player].strength/2;
   
                                        return ball_player;
    
         }//end of case 1 
        
}    

    /* int case2(int ball_player,struct player * p)   
     {
        return -1; 
         }    
     
     
     int case3(struct player * p)
     {
         return -1;
         }
 */
// Definition of case2() func.

//ball is with opp team's player
int case2(int ball_player,struct player * p)
{   int i,a,small,j,k;
    int strreq,temp,large ;
   int mid [2];
   int player_no;
 //this for loop searches for a player who has more strength than the opponent's player having possession of the ball ,after 
 //reaching at the ball's position and if such player is found then the case becomes similar to one when my player was having the 
 //possession of the ball ,so the case1 function is called and finally the hitter of ball is returned to controller   
	 for(i=pl;i<=ph;i++)
    {
       strreq=preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y);
       
       if( (p[i].strength - strreq )> p[ball_player].strength )
       {
           p[i].x=p[ball_player].x;
           p[i].y=p[ball_player].y;
           
           a=case1(i,p);
           return a;       
       }
   }

   if(pl=1)
     {  
	 for(j=12;j<=22;j++)
      {
				strreq=preqp(p[j].x,p[j].y,p[0].x,p[0].y);
            
            if(  (p[j].strength - strreq )  >  large)  //large is having max strength of the player after reaching there 
            {                                        //player_no is having the no. of the desired player   
                 temp=j;
                 large=p[j].strength;
            }             //end of if 
             
       }      //end of for loo

   }  

   if(pl=12)
   {
        
	 for(j=1;j<=11;j++)
    {
				strreq=preqp(p[j].x,p[j].y,p[0].x,p[0].y);
            
            if(  (p[j].strength - strreq )  >  large)  //large is having max strength of the player after reaching there 
            {                                        //player_no is having the no. of the desired player   
                 temp=j;
                 large=p[j].strength;
            }             //end of if 
             
    }      

   }
      mid[0]=(p[ball_player].x+p[temp].x)/2;
      mid[1]=(p[ball_player].y+p[temp].y)/2;
       
	 for(i=pl;i<=ph;i++)
    {
				strreq=preqp(p[i].x,p[i].y,mid[0],mid[1]);
            
            if(  (p[i].strength - strreq )  >  large)  //large is having max strength of the player after reaching there 
            {                                        //player_no is having the no. of the desired player   
                 player_no=i;
                 large=p[i].strength;
            }             //end of if 
             
    }      //end of for loop
    p[player_no].x=mid[0];
    p[player_no].y=mid[1];


   //if no such player is found then it simply returns a -1 i.e. , it don't want to hit the ball and skips the turn 
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
				strreq=preqp(p[i].x,p[i].y,p[0].x,p[0].y);
            
            if(  (p[i].strength - strreq )  >  large)  //large is having max strength of the player after reaching there 
            {                                        //player_no is having the no. of the desired player   
                 player_no=i;
                 large=p[i].strength;
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
        
         
  
};  //end of class team0042 


//here linker error is coming as int main() function is not included .
   
