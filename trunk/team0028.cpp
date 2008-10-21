#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


int couple[11][11];
int d[22];
static int move=1;


using namespace std;

class team0028  //The name of your class should be teamxxxx where xxxx is the no. u will get at the time of registration and will
{                //be unique for every participant
  private:
  int pl,ph,player_no,team;
  
    //team is a variable used in player function which tells all of the functions defined by the participant what their team no. is
	     //it is not mandatory for the player to use this variable .player can use any other means to satisfy the need
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


  public:
  
   int init(int team_number, struct player *p,char farray[][51])   // this fn must be there in your program ,it will be called only
	{                                                             //once at the beginning of the program .It will tell u whether u are
      team=team_number;                                 //player 1 or 2 and this will also give u the basic fieldarray ie where there is
	}                                                  //a goal or a dee or a boundary and struct player *p gives u the initial player
						 //distribution in the field

    int player(struct player *p)  //This fn should contain the strategies u want to implement.You can also define other fns in your
				   //class but u can call them with this fn only .This fn has to receive the array of 23 structures from the controller fn which
				 //contain the positions of the 22 players and the ball at that time .It is also supposed to return the
				 //the no of the player who will hit the ball to the controller fn
     {
	      int i,j,ball_player,a;     //ball_player is used to find which player is having the possession of the ball or whether the ball
				     //is at empty slot


	 //assigning limits according to player no.
	 if(team==1)
	 {

		pl=1;            //pl shows the lower limit and ph shows the upper limit of players in the array of structures ,i.e. if player
		ph=11;           //is 1st then his players will be 1 to 11 and if he is 2nd then his players will be 12 to 22
		player_no=1;
	 }

	 else
	 {
		  pl=12;
		  ph=22;
          player_no=2;		  
		  
	 }
	 
	     cover(p);
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
//case1 ball in my possession
   int case1(int ball_player,struct player * p)
{
    int i,strreq,b,y2;
  if(team==1)
  {
      for(i=1;i<5;i++)
      {
          if(d[i]==0 && d[i]==ball_player)
          return -1;
          } 
}
 if(team==2)
 {
            for(i=12;i<16;i++)
      {
          if(d[i]==0 && d[i]==ball_player)
          return -1;
          } 
}                                          
    if(move==1)
    {
        movep(p,team);
        move++;
        }
         if(team==1)
   {   
     for(i=12;i<=22;i++) 
      if((p[ball_player].strength==p[i].strength) && (p[ball_player].x==p[i].x) && (p[ball_player].y==p[i].y))
        return ball_player;
   } 
   else if(team==2)
   {
        for(i=1;i<=11;i++)
        if((p[ball_player].strength==p[i].strength) && (p[ball_player].x==p[i].x) && (p[ball_player].y==p[i].y))
           return ball_player;
   }   
	 if( in_range(ball_player,p) )
	{
	//then player having the ball is in range of the goal,i.e. the y-coordinates or the coloumn coordinates of the player is
	//between 10 and 40
	for(y2=10;y2<=40;y2++)
	   { 
         if(team==1)
         {                 
	     b=obstruct(p[ball_player].x,p[ball_player].y,86,y2,p);
	     if(b==1)
	     {
	       strreq=preqpb(86,y2,p[ball_player].x,p[ball_player].y );
	       if(p[ball_player].strength >= strreq)
		 {
		   p[0].x=86;
		   p[0].y=y2;
		   return ball_player;
		 }
	      }
       }
       else //team=2
       {                 
	     b=obstruct(p[ball_player].x,p[ball_player].y,14,y2,p);
	     if(b==1)
	     {
	       strreq=preqpb(14,y2,p[ball_player].x,p[ball_player].y );
	       if(p[ball_player].strength >= strreq)
		 {
		   p[0].x=14;
		   p[0].y=y2;
		   return ball_player;
		 }
	      }
       }
       
       }       
	   	}
       // ball is not in range pass ball to player ahead of u

       if(team==1)
       {
       for(i=pl;i<=ph;i++)
	  {
	       if( (p[i].x>=p[ball_player].x) )
	       {
		 strreq=preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y);
		 if(p[ball_player].strength>=strreq)
		 {
		    b=obstruct(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y,p);
		    if(b==1)
		    {
		      p[0].x=p[i].x;
		      p[0].y=p[i].y;
		      return ball_player;
		    }
		 }
	      }
	   }



	if(i==(ph+1) && (p[ball_player].x<60))  
	 {
 	 for(y2=5;y2<=45;y2++)
	   { 
                         
	     b=obstruct(p[ball_player].x,p[ball_player].y,60,y2,p);
	     if(b==1)
	     {
	       strreq=preqpb(60,y2,p[ball_player].x,p[ball_player].y );
	       if(p[ball_player].strength >= strreq)
		 {
		   p[0].x=60;
		   p[0].y=y2;
		   return ball_player;
		 }
        }
       
      
       
       }       
	          
  	 if(y2==46) //if no player ahead then pass it to player behind u
  	 {
                   
       for(i=5;i<=ph;i++)                                    
	   {
	     if (  (p[i].x<=p[ball_player].x))
		  {
		    strreq=preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y);
		    if(p[ball_player].strength>=strreq)
		    {
		       b=obstruct(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y,p);
		       if(b==1)
		       {
		      p[0].x=p[i].x;
		      p[0].y=p[i].y;
		      return ball_player;
		       }
		    }
		  }
	     }
	  }
    }  
   }     // if team=1 ends
   else if ( team==2)
   {
       for(i=pl;i<=ph;i++) //pass to player ahead of u
	  {
	       if( (p[i].x<=p[ball_player].x) )
	       {
		 strreq=preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y);
		 if(p[ball_player].strength>=strreq)
		 {
		    b=obstruct(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y,p);
		    if(b==1)
		    {
		      p[0].x=p[i].x;
		      p[0].y=p[i].y;
		      return ball_player;
		    }
		 }
	      }
	   }
if(i==(ph+1) && (p[ball_player].x>40))  //if no player ahead then pass it to player behind u
	 {   
        for(y2=5;y2<=45;y2++)
        {               
	     b=obstruct(p[ball_player].x,p[ball_player].y,40,y2,p);
	     if(b==1)
	     {
	       strreq=preqpb(40,y2,p[ball_player].x,p[ball_player].y );
	       if(p[ball_player].strength >= strreq)
		 {
		   p[0].x=40;
		   p[0].y=y2;
		   return ball_player;
		 }
	      }
       } 
              
       for(i=pl;i>=ph;i++)
	   {
	     if (  (p[i].x>=p[ball_player].x) || (p[i].x<=p[ball_player].x) && (i<12 && i>15)  )
		  {
		    strreq=preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y);
		    if(p[ball_player].strength>=strreq)
		    {
		       b=obstruct(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y,p);
		       if(b==1)
		       {
		      p[0].x=p[i].x;
		      p[0].y=p[i].y;
		      return ball_player;
		       }
		    }
		  }
	     }
	
    }  
   }   //else if ends
else
return -1;//if no such player is found return -1	  
}
    //case1ends
///////////////////////////////////////////////////////////////////
//case2 when ball is not in my possession
 int case2(int ball_player,struct player * p)
{   int i,a;
    int strreq;
     
if(move==1)
{
   movep(p,team);
   move++;
}          
    if(team==1)
   {   
     for(i=1;i<=11;i++) 
      if((p[ball_player].strength==50) && (p[ball_player].x==p[i].x) && (p[ball_player].y==p[i].y))
        return -1;
   } 
   else if(team==2)
   {
        for(i=11;i<=22;i++)
        if((p[ball_player].strength==50) && (p[ball_player].x==p[i].x) && (p[ball_player].y==p[i].y))
           return -1;
   } 

       
          
              
 //this for loop searches for a player who has more strength than the opponent's player having possession of the ball ,after
 //reaching at the ball's position and if such player is found then the case becomes similar to one when my player was having the
 //possession of the ball ,so the case1 function is called and finally the hitter of ball is returned to controller
	 for(i=pl;i<=ph;i++)
    {
       strreq=preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y);

       if( (p[i].strength - strreq )> p[ball_player].strength && d[i]==i)
       {
       
	   p[i].x=p[ball_player].x;
	   p[i].y=p[ball_player].y;

	   a=case1(i,p);
	   return a;
       }
   }

//if no such player is found then it simply returns a -1 i.e. , it don't want to hit the ball and skips the turn
   return -1;

}//end of case2 func.
/////////////////////////////////////////////////
//definition of case3() func.

//when ball is with no player

int case3(struct player * p)
{
                
    if(move==1)
    {
movep(p,team);
move++;
}

	 int player_no=0,i,a,strreq,large=0;

  //this for loop searches for a player of my team such that after reaching at the position of the ball it is having the maximum
  //strength left to hit the ball
	 for(i=pl;i<=ph;i++)
    {
				strreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);

	    if(  (p[i].strength - strreq )  >  large && d[i]==i)  //large is having max strength of the player after reaching there
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


void movep(struct player *p,int t)
{    
    if(t==1)
    {    
     p[1].x=41;p[1].y=25;p[1].strength-=preqp(41,25,15,25);
     p[2].x=42;p[2].y=10;p[2].strength-=preqp(42,10,25,10);
     p[3].x=41;p[3].y=25;p[3].strength-=preqp(41,25,25,25);
     p[4].x=42;p[4].y=40;p[4].strength-=preqp(42,40,25,40);
     p[5].x=47;p[5].y=10;p[5].strength-=preqp(47,10,30,10);
     p[6].x=49;p[6].y=22;p[6].strength-=preqp(49,22,30,25);
     p[7].x=45;p[7].y=40;p[7].strength-=preqp(45,40,30,40);
     p[8].x=61;p[8].y=10;p[8].strength-=preqp(61,10,40,10);
     p[9].x=62;p[9].y=15;p[9].strength-=preqp(62,15,40,25);
     p[10].x=63;p[10].y=30;p[10].strength-=preqp(63,30,40,40);
     p[11].x=49;p[11].y=25;p[11].strength-=preqp(49,25,49,25);

     }
  else if(t==2)
  {
    p[12].x=59;p[12].y=25;p[12].strength-=preqp(59,25,85,25);
     p[13].x=58;p[13].y=10;p[13].strength-=preqp(58,10,75,10);
     p[14].x=59;p[14].y=25;p[14].strength-=preqp(59,25,75,25);
     p[15].x=58;p[15].y=40;p[15].strength-=preqp(58,40,75,40);
     p[16].x=53;p[16].y=10;p[16].strength-=preqp(53,10,70,10);
     p[17].x=51;p[17].y=22;p[17].strength-=preqp(51,22,70,25);
     p[18].x=55;p[18].y=40;p[18].strength-=preqp(55,40,70,40);
     p[19].x=39;p[19].y=10;p[19].strength-=preqp(39,10,60,10);
     p[20].x=38;p[20].y=15;p[20].strength-=preqp(38,15,60,25);
     p[21].x=37;p[21].y=30;p[21].strength-=preqp(37,30,60,40);
     p[22].x=51;p[22].y=25;p[22].strength-=preqp(51,25,51,25);
   }
}









//obstruct checks whether there is obstruction in the path of player hitting the ball or not
int obstruct(int x1,int  y1,int x2,int y2,struct player *p)
{
int i,j=x1,k=y1;
if(team==1)
{
if(x2>x1 && y2>y1)
{
for(i=12;i<=22;i++)
{    j=x1,k=y1;
     while(j!=x2 || k!=y2)
	 {


		   if(p[i].x==j && p[i].y==k)
		      return 0;
		   else
		   {
		    if(j==x2)
            k++;
            else if(k==y2)
            j++;
            else
            {
                j++;
		    k++;
           }
           }
	  }
}
if(i==(23))
return 1;
}
else if(x2>x1 && y2<y1)
{
for(i=12;i<=22;i++)
{     j=x1,k=y1;
     while(j!=x2 || k!=y2)
	 {


		   if(p[i].x==j && p[i].y==k)
		      return 0;
		   else
		   {if(j==x2)
		   k--;
		   else if(k==y2)
		   j++;
		   else
		   {
		   j++;
		   k--;
         }
           }
	 }
}
if(i==(23))
return 1;
}
else if(x2<x1 && y2>y1)
{  
for(i=12;i<=22;i++)
{  j=x1,k=y1;
     while(j!=x2 || k!=y2)

	       {

		   if(p[i].x==j && p[i].y==k)
		      return 0;
		   else
		   {
		   if(j==x2)
           k++;
          else if(k==y2)
           j--;
           else
           {
               j--;
               k++;
               
           }
		  
		   }
	       }
}
if(i==(23))
return 1;
}
  else if(x2<x1 && y2<y1)
{
for(i=12;i<=22;i++)
{   j=x1;k=y1;
      while(j!=x2 || k!=y2)
	 {


		   if(p[i].x==j && p[i].y==k)
		      return 0;
		   else
		   {
		   if(j==x2)
           k--;
		   else if(k==y2)
		   j--;
		   else
		   {
               j--;
           k--;
           }
           }
	 }
}
if(i==(23))
return 1;
}
}
else
{
 if(x2>x1 && y2>y1)
{
for(i=1;i<=11;i++)
{ j=x1,k=y1;
     while(j!=x2 || k!=y2)
	 {


		   if(p[i].x==j && p[i].y==k)
		      return 0;
		   else
		   {
		    if(j==x2)
            k++;
            else if(k==y2)
            j++;
            else
            {
                j++;
		    k++;
           }
           }
	  }
}
if(i==(12))
return 1;
}
else if(x2>x1 && y2<y1)
{
for(i=1;i<=11;i++)
{  j=x1,k=y1;
     while(j!=x2 || k!=y2)
	 {


		   if(p[i].x==j && p[i].y==k)
		      return 0;
		   else
		   {if(j==x2)
		   k--;
		   else if(k==y2)
		   j++;
		   else
		   {
		   j++;
		   k--;
         }
           }
	 }
}
if(i==(11))
return 1;
}
else if(x2<x1 && y2>y1)
{
for(i=1;i<=11;i++)
{  j=x1,k=y1;
     while(j!=x2 || k!=y2)

	       {

		   if(p[i].x==j && p[i].y==k)
		      return 0;
		   else
		   {
		   if(j==x2)
           k++;
          else if(k==y2)
           j--;
           else
           {
               j--;
               k++;
               
           }
		  
		   }
	       }
}
if(i==(12))
return 1;
}
  else if(x2<x1 && y2<y1)
{
for(i=1;i<=11;i++)
{  j=x1,k=y1;
      while(j!=x2 || k!=y2)
	 {


		   if(p[i].x==j && p[i].y==k)
		      return 0;
		   else
		   {
		   if(j==x2)
           k--;
		   else if(k==y2)
		   j--;
		   else
		   {
               j--;
           k--;
           }
           }
	 }
}
if(i==(12))
return 1;
}
}   
}
//end of obstruct
////in_range function checks whether ball is in range or not
  int in_range(int ball_player,struct player * p)
{
    if(  ( (p[ball_player].x>=61) && (team==1)) || ( (p[ball_player].x<=39) && (team==2)))
    return 1;
    return 0;
}
//end of in_range function
/////////////////////////////////////////////////////
//cover function to cover opponents players in our D
void cover(struct player *p)
{
     int strreq,bound=0;
   int j=0,i;
    for(i=1;i<23;i++)
       d[i]=i;
     
  
   for(i=0;i<11;i++)
      for(j=0;j<11;j++)
         couple[i][j]=0;
  if(team==1)
  { 
   for(i=11;i<=22;i++)
   {
       if(p[i].x<=45)
        for(j=1;j<10;j++)
         if(j==1 || j==2 || j==3 || j==4)
         {   
          strreq=preqp(p[i].x,p[i].y,p[j].x,p[j].y);     
             if(couple[i][j]!=1 && p[j].strength>=strreq)
              {  couple[i][j]=1;
                 p[j].x=p[i].y;
                 p[j].y=p[i].y; 
                  break;
              }
         }
    }
       if(p[i].x>45)
        for(i=11;i<=22;i++) 
         for(j=1;j<10;j++)
	   if(j==1 || j==2 || j==3 ||j==4 )
           {
              if(couple[i][j]==1)
                  couple[i][j]=0;
           }
    for(j=1;j<10;j++)
         if(j==1 || j==2 || j==3 || j==4)
         {   bound=0;
            for(i=11;i<=22;i++)
            {
               if(couple[i][j]==1)
                 {        
                   bound=1;
                   break;}
            }
           if(bound) 
            d[j]=0;
         }
   }         
   
   else if(team==2)
   {
      for(i=1;i<=11;i++)
     {
       if(p[i].x>=55)
        for(j=11;j<23;j++)
         if(j==12 || j==13 || j==14 || j==15)
         {   
          strreq=preqp(p[i].x,p[i].y,p[j].x,p[j].y);     
             if(couple[i][j]!=1 && p[j].strength>=strreq)
              {  couple[i][j]=1;
                 p[j].x=p[i].x;
                 p[j].y=p[i].y; 
                  break;
              }
         }
      }
       if(p[i].x<55)
        for(i=11;i<=22;i++) 
         for(j=1;j<10;j++)
	   if(j==12 || j==13 || j==14 ||j==15 )
           {
              if(couple[i][j]==1)
                  couple[i][j]=0;
           }
           for(j=11;j<22;j++)
         if(j==12 || j==13 || j==14 || j==15)
         {   bound=0;
            for(i=1;i<=11;i++)
            {
               if(couple[i][j]==1)
                 {        
                   bound=1;
                   break;}
            }
           if(bound) 
            d[j]=0;
            
         }
  }
         
}

};//end of class
