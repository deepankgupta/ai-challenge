//248-245 when player1 and loss on strength when pl2 when i play with sample_player_final_but_hang.cpp. This has improved inranged.

#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<math.h>

using namespace std;

class team0048  
{                
  private:
  int pl,ph,player_num,player_no,strength[23];

  int team;  
// returns the strength required for moving one place to another
  int preqp(int finalx,int finaly, int initialx ,int initialy )
	{float req;
    req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
    return (int)req;}     

//returns the strength req by your hitter to move the ball from one place to another 
  int preqpb(int finalx,int finaly, int initialx ,int initialy )
	{float req; int i;
    req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	 i=(int)req;
	 return i;} 
	 
	 
  public:
         
  int init(int team_number, struct player *p,char farray[][51])  
	{          
	int i,j,x;                                                  
      	player_no=team=player_num=team_number;     
	cout<<"Your team no. is "<<team<<endl;                          
	}                                         

  int player(struct player *p) 
     { 
	int l,u,i,j,ball_player=0,a,large=0,opp_player;   
	static int fr=0;

 //assigning limits according to player num
	 if(player_num==1)
	 {
		pl=1;            
		ph=11;           
	 }

	 else
	 {
		  pl=12;
		  ph=22;
	 }
 
 // Intial Formation Here :->> 
	if(fr++==0)
	{       
		if(player_num==1)
		{
		p[1].strength-=preqp(p[1].x,p[1].y,25,25);
		p[1].x=25;p[1].y=25;
		p[2].strength-=preqp(p[2].x,p[2].y,41,15);
		p[2].x=41;p[2].y=15;	   
		p[3].strength-=preqp(p[3].x,p[3].y,41,20);
		p[3].x=41;p[3].y=20;	   
		p[4].strength-=preqp(p[4].x,p[4].y,41,35);
		p[4].x=41;p[4].y=35;	   
		p[5].strength-=preqp(p[5].x,p[5].y,41,5);
		p[5].x=41;p[5].y=5;	   
		p[6].strength-=preqp(p[6].x,p[6].y,41,30);
		p[6].x=41;p[6].y=30;	   
		p[7].strength-=preqp(p[7].x,p[7].y,41,45);
		p[7].x=41;p[7].y=45;	   
		p[8].strength-=preqp(p[8].x,p[8].y,41,10);
		p[8].x=41;p[8].y=10;	   
		p[9].strength-=preqp(p[9].x,p[9].y,41,25);
		p[9].x=41;p[9].y=25;	   
		p[10].strength-=preqp(p[10].x,p[10].y,41,40);
		p[10].x=41;p[10].y=40;	  
		}
		else
		{
		p[12].strength-=preqp(p[12].x,p[12].y,75,25);
		p[12].x=75;p[12].y=25;
		p[13].strength-=preqp(p[13].x,p[13].y,59,15);
		p[13].x=59;p[13].y=15;	   
		p[14].strength-=preqp(p[14].x,p[14].y,59,20);
		p[14].x=59;p[14].y=20;	   
		p[15].strength-=preqp(p[15].x,p[15].y,59,35);
		p[15].x=59;p[15].y=35;	   
		p[16].strength-=preqp(p[16].x,p[16].y,59,5);
		p[16].x=59;p[16].y=5;	   
		p[17].strength-=preqp(p[17].x,p[17].y,59,30);
		p[17].x=59;p[17].y=30;	   
		p[18].strength-=preqp(p[18].x,p[18].y,59,45);
		p[18].x=59;p[18].y=45;	   
		p[19].strength-=preqp(p[19].x,p[19].y,59,10);
		p[19].x=59;p[19].y=10;	   
		p[20].strength-=preqp(p[20].x,p[20].y,59,25);
		p[20].x=59;p[20].y=25;	   
		p[21].strength-=preqp(p[21].x,p[21].y,59,40);
		p[21].x=59;p[21].y=40;	  
		}
	}
 // l and u needed for calculating hitting power of a player l and u r for opp teams plys
	if(team==1)
	{ 
   	  l=12;
	  u=22;
	}
	else
	{
	  l=1;
	  u=11;
	}
// Strength[] keeps the record of strength a player has while hitting ! strength array stored for only our team
  for(j=ph;j>=pl;j--)
  {
   large=0;
   for(i=l;i<=u;i++)
     if(p[j].x==p[i].x&&p[j].y==p[i].y)
	if(large<p[i].strength)
	  large=p[i].strength;
     strength[j]=p[j].strength-large;	  
  }
 // checking where is ball
    ball_player=0;
   for(i=1;i<23;i++)
    if( p[0].x==p[i].x && p[0].y==p[i].y )         
     {
        if(ball_player==0)
	 ball_player=i;              
	else
	{
	  if(p[ball_player].strength<p[i].strength)
		ball_player=i;
	}
     }  
 // Analyzing    
    if((ball_player==0)||(ball_player<=11&&player_no==1)||(ball_player>11&&player_no==2))
    {
    	 cout<<"with us"<<endl;
	 large=0;
	 opp_player=0;
	   for(i=l;i<=u;i++)
    		if( p[0].x==p[i].x && p[0].y==p[i].y )         
     		{
        		if(opp_player==0)
	 		{ 
				opp_player=i;
				large=p[i].strength;  
			}              
			else
			{
	  			if(large<p[i].strength)
				 {
					opp_player=i;
					large=p[opp_player].strength;
				 }
			}
     		}
	 a=analyze(ball_player,p,large);
		 
	 return a;   //returns the hitter of the ball to the controller 
    }
 // ball with opp team player
          cout<<"with them";
	  a=analyze(ball_player,p,p[ball_player].strength);
    
    return a;
    
    
}//end of player func.

    
//definition of hit() , when the ball is with my player
int hit(int ball_player,struct player * p)
{   cout<<"entered hit";
    int i,u,l,large=0,x,y,inD=0,inDp=0;

    if(((team==1&&p[0].x>=60)||(team==2&&p[0].x<=40))&&(p[0].y>6&&p[0].y<46))                         //i'm in opp. D
      inD=1;



    if( in_rangeg(ball_player,p) )   //in_range will return 1 if possible and update ball coord, else will return 0 
           return ball_player;               
                                   
   for(i=ph;i>=pl;i--)     {
	if(preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y)<=strength[ball_player])
	if(interrupt(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y,p))
	if(in_rangeg(i,p))
	{
	cout<<"Ball passed to player "<<i<<endl;
	p[0].x=p[i].x;
	p[0].y=p[i].y;
        return ball_player;
	}
    }    
      
    cout<<"cant reach goal";
    if(inD==0)		//i'm not inD, then hit ball in D otherwise no use.
    {    
         cout<<"jk";
         for(i=ph;i>=pl;i--)
   	 if(in_rangd(i,p))
         if(preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y)<=strength[ball_player])
  	 if(interrupt(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y,p))
		{
			cout<<"Ball passed to player "<<i<<endl;
			x=p[0].x;
			y=p[0].y;
			p[0].x=p[i].x;
			p[0].y=p[i].y;
			loop(x,y,ball_player,p);
        		return ball_player;
		}
        
      if(in_ranged(ball_player,p,1))   // chking if it can hit in the D
	return ball_player;
    }	
    cout<<"will now have to pass the ball"<<endl;
   //if D is not in the range of the ball
   
              //will have to pass bal to someone outside D who can hit it inside


   for(i=ph;i>=pl;i--)
     {
	inDp=0;
	if((((team==1&&p[i].x>=60)||(team==2&&p[i].x<=40))&&(p[i].y>=5&&p[i].y<=45)))
	   inDp=1;
        
	if((inD==0)||((inD==1)&&(inDp==0)))	
	if(preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y)<=strength[ball_player])
	if(interrupt(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y,p))
	{
	   cout<<"Ball passed to player "<<i<<endl;
	   p[0].x=p[i].x;
	   p[0].y=p[i].y;
           return ball_player;
	}
     }
   large=0;
   cout<<endl;
   cout<<p[ball_player].x<<" "<<p[ball_player].y<<endl;
   for(i=ph;i>=pl;i--)
       {  
	  cout<<p[i].x<<" "<<p[i].y<<endl;
	  if(p[i].x!=p[ball_player].x||p[i].y!=p[ball_player].y)
          if(strength[i]>large)
          if(strength[ball_player]>=preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y))
	  if(interrupt(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y,p))
		{	  cout<<p[i].x<<"-"<<p[i].y<<endl;
		 x=p[i].x;
		 y=p[i].y;
		 large=strength[i];
		}
     }
      
	if(large!=0)
	{
        cout<<" "<<x<<" "<<y;
	p[0].x=x;
	p[0].y=y;      
	cout<<"Ball passed to player with co-ord "<<x<<" "<<y<<endl;
  	return ball_player;
	}     
   
   /*
   //if no such player is found then the ball is simply hit straight with max strength of the hitter of the ball
   if(player_num==1)
   p[0].x+=p[ball_player].strength/2;
   else
   p[0].x-=p[ball_player].strength/2;
   cout<<p[0].x<<" "<<p[0].y<<endl;
   //loop(ball_player,p);
   return ball_player;
   */

   return -1;
   
}                     // end of hit() func.
   
        
// Definition of analyze() func.

int analyze(int ball_player,struct player * p,int large)
{   
    int i,a;
    int strreq;                      // strength required for moving from orignal position to new positon
    int larger,pos=0;		     // larger : stores the max strength available for hitting and pos the player who hits 
    larger=large;
 
    for(i=ph;i>=pl;i--)
      {
         strreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);
       
         if( (p[i].strength - strreq )> larger )
          {
             larger=p[i].strength-strreq;
	     pos=i;
          }
      }
    if(pos!=0)
     { 
        cout<<"Calling case 1 from case 2 with player no "<<pos<<endl;
	p[pos].x=p[0].x;
	p[pos].y=p[0].y;
	p[pos].strength=larger;
	cout<<"large"<<large;
	strength[pos]=p[pos].strength-large;
        cout<<"his strength"<<strength[pos];
        a=hit(pos,p);
        return a;       
     }

  if(large!=0)
  loop(p[0].x,p[0].y,0,p);
 

   return -1;
   
}//end of analyze func.






//in_range is a function defined by the participant 
//it checks wheter the ball is in the range of the goal or not and returns 1 or 0 accordingly

 int interrupt(int finalx,int finaly,int initialx, int initialy,struct player *p) //return 1 on reaching destination
 {
		 
	if((finalx==initialx)&&(finaly==initialy))
	{ cout<<"it is here "<<endl;
          return 0;
        }

	int xdiffb,ydiffb,validposx,validposy,i;

	xdiffb=finalx-initialx;   
        ydiffb=finaly-initialy;   
	validposx=initialx;  
        validposy=initialy;  
      
      while(1)
      {
	if(validposx!=finalx)
            (xdiffb>0)?(validposx)++:(validposx)--;
        if(validposy!=finaly)
            (ydiffb>0)?(validposy)++:(validposy)--;

        if((validposx==finalx)&&(validposy==finaly))            //when ball reaches its desired position
            {
                return 1;
            }        
        for(i=1;i<=22;i++)
          {
            if((validposx==p[i].x)&&(validposy==p[i].y))
              { 
                
                return 0;
                
              }
          }      //loop to check whether any of the player intersect the ball

       
      }//end of while loop which operates until ball is interrupted or reaches its desired pos or enters goal or boundary
      
 }
 
 int interrupti(int kx,int ky,int finalx,int finaly,int initialx, int initialy,struct player *p) //return 1 on reaching destination
 {
		 
	if((finalx==initialx)&&(finaly==initialy))
	return 1;

	int xdiffb,ydiffb,validposx,validposy,i;

	xdiffb=finalx-initialx;   
        ydiffb=finaly-initialy;   
	validposx=initialx;  
        validposy=initialy;  
      
      while(1)
      {
	if(validposx!=finalx)
            (xdiffb>0)?(validposx)++:(validposx)--;
        if(validposy!=finaly)
            (ydiffb>0)?(validposy)++:(validposy)--;
        
         if((validposx==finalx)&&(validposy==finaly))            //when ball reaches its desired position
            {
                return 1;
            }      

            if((validposx==kx)&&(validposy==ky))
              {
                return 0;
                
              }
                //loop to check whether any of the player intersect the ball

       
      }//end of while loop which operates until ball is interrupted or reaches its desired pos or enters goal or boundary
      
 }
  int in_rangeg(int ball_player,struct player * p)   
  {

    int i,x;
     if(player_num==1)
       x=86;
     else
       x=14;

     if(preqpb(x,p[ball_player].y,p[ball_player].x,p[ball_player].y)>strength[ball_player])
        return 0;

     while(x<100&&x>0)
       {
 	for(i=10;i<=40;i++)
 	{
  	 if((preqpb(x,i,p[ball_player].x,p[ball_player].y)<=strength[ball_player]))
  	 {
   		if((interrupt(x,i,p[ball_player].x,p[ball_player].y,p)==1))
   		{ p[0].x=x;
		  p[0].y=i;
		  return 1; 
 	  	}
         }	
  	 else if(p[ball_player].y<i)
  		break;
        }//end of for
        (x>85)?x++:x--;
       }//end of while

    return 0;
 }    

 int in_rangd(int num , struct player*p)
 {       
	if((p[num].y>4)&&(p[num].y<46))
	if((player_num==1 && p[num].x>59)||(player_num==2 && p[num].x<41))
			return 1;
        return 0;
 } 

 int in_ranged(int ball_player,struct player * p,int strat)   //return 1 if can reach D, update ball coord also. else return 0
 {

   int i,x,tempx,tempy;
    if(player_num==1)
	x=60;
    else
	x=40;


   while(x<86&&x>14)
	{
 	for(i=0;(p[ball_player].y+i<=45)&&(p[ball_player].y-i>=5);i++)
 	{
  	 if(p[ball_player].y+i<=45)
  	 if((preqpb(x,p[ball_player].y+i,p[ball_player].x,p[ball_player].y)<=strength[ball_player]))
  	  {
   		if((interrupt(x,p[ball_player].y+i,p[ball_player].x,p[ball_player].y,p)==1))
   		{ 
			tempx=p[0].x;
			tempy=p[0].y;
			p[0].x=x;
			p[0].y=p[ball_player].y+i;
			//p[ball_player].strength=50;
			cout<<"hitter"<<ball_player<<"to"<<p[0].x<<" "<<p[0].y;	
			if(strat)		//if i'm hitting in D then loop, if only passing to a player who might hit in next chance in D the n no need of loop
			loop(tempx,tempy,ball_player,p);
			return 1; 
   		}
  	  }
 	 else if(i==0)
   	  return 0;
 	
  	 if(p[ball_player].y-i>=5)
  	 if((preqpb(x,p[ball_player].y-i,p[ball_player].x,p[ball_player].y)<=strength[ball_player]))
  		{
   		if((interrupt(x,p[ball_player].y-i,p[ball_player].x,p[ball_player].y,p)==1))
   		{       
			tempx=p[0].x;
			tempy=p[0].y;
			p[0].x=x;
			p[0].y=p[ball_player].y-i;
			//p[ball_player].strength=50;
			cout<<"hitter"<<ball_player<<"to"<<p[0].x<<" "<<p[0].y;
			if(strat)			
			loop(tempx,tempy,ball_player,p);
			return 1; 
   		}
  		}	
 	}//end of for
 	(x>59)?x++:x--;
	}//end of while

 return 0;
 }    

 void loop(int ballx , int bally ,int ball_player,struct player *p)
 {
   int lpl[4],small=50,strreq,k,m,i,player_no,x,fx=0,d,de;
   lpl[2]=0;
   lpl[0]=0;
   k=(player_num==1)?-1:1; 

   for(m=-1;m<2;m+=2)
    {
      small=50;
      player_no=0;
      if(p[0].y+m > 0 && p[0].y+m < 50 )
      if(interrupti(p[0].x+k,p[0].y+m,p[0].x,p[0].y,ballx,bally,p))
      for(i=pl;i<=ph;i++)
        {   
	     if(i!=lpl[0]&& i!=ball_player)
             { 
               strreq=preqp(p[0].x+k,p[0].y+m,p[i].x,p[i].y);
            
               if(((p[i].strength - strreq )>=0) && (strreq<small)) 
                {                                        //player_no is having the no. of the desired player   
                 player_no=i;
                 small=strreq;
                }             //end of if 
             }	
             
        }     
      if(player_no<ph+1 && player_no>0)
      { cout<<" jhjkjhjkhjk "<<player_no;
        lpl[m+1]=player_no; 
        p[player_no].x=p[0].x+k;
        p[player_no].y=p[0].y+m;
        //p[player_no].strength=small;	
      }
   }
  player_no=0;
  small=50;
  if(player_num==1)
   {
	d=41;
	de=59;
   }
  else
   {
	d=59;
	de=41;
   }

 if((p[0].x >d && player_num==1 )||(p[0].x < d && player_num==2))
  for(i=pl;i<=ph;i++)
    {   for(x=d;x!=de;x=x-k)
	if(interrupti(x,p[0].y,p[0].x,p[0].y,ballx,bally,p))
	if(interrupt(p[0].x,p[0].y,x,p[0].y,p))
	if((x<p[0].x && player_num==1)|| (x>p[0].x && player_num==2)) 
        if((i!=lpl[0]) && (i!=lpl[2]) && (i!=ball_player))
          {  
             strreq=preqp(x,p[0].y,p[i].x,p[i].y);
            
             if(((p[i].strength - strreq )>=0) && (strreq <small)) 
             {                                          //player_no is having the no. of the desired player   
                 player_no=i;
		 fx=x;
                 small=strreq;
             }             //end of if 
          }	
             
    }  
  else if((p[0].x <= d && player_num==1 )||(p[0].x >= d && player_num==2))   
	for(i=pl;i<=ph;i++)
    	{   for(x=d;x!=d+k*26;x=x+k)
		if(interrupti(x,p[0].y,p[0].x,p[0].y,ballx,bally,p))
		if(interrupt(p[0].x,p[0].y,x,p[0].y,p))
		if((x<p[0].x && player_num==1)|| (x>p[0].x && player_num==2)) 
        	if((i!=lpl[0]) && (i!=lpl[2]) && (i!=ball_player))
          	{  
             	strreq=preqp(x,p[0].y,p[i].x,p[i].y);
            
             	if(((p[i].strength - strreq )>=0) && (strreq <small)) 
             	{                                          //player_no is having the no. of the desired player   
                 player_no=i;
		 fx=x;
                 small=strreq;
             	}             //end of if 
          	}	
             
    	}  
     

  if(player_no!=0)
     { 
	p[player_no].y=p[0].y;
	p[player_no].x=fx;
	cout<<"HERE"<<endl;
   }	
     

  cout<<"looping with players "<<lpl[0]<<" "<<lpl[2]<<" "<<player_no<<endl;
}
    
};//end of class
