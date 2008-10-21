
#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#include<math.h>
using namespace std;


class team0101  //here the class name is given to be team0002 assuming that the registration no. of the participant was 2 
{
  private:      //private fns and variables defined
  int pl,ph,player_num,player_no;
  
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
    
int player(struct player *p) 
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
        
			a=case3(p);
		 
        return a;
    }
    
    
    // ball with opp team player
    
	  a=case2(i,p);
    
    return a;
    
    
}
int case1(int ball_player,struct player * p)
{   
int a;
if( in_range(ball_player,p) )
{
interception(ball_player,p);
place(ball_player,p);
return ball_player;
}
else
{	
a=pass_hit(ball_player,p);
printf("place");
place(ball_player,p);
return ball_player;

}


}

int case2(int ball_player,struct player * p)
{   	
int i,a;
int strreq;
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
else
{
place(ball_player,p);

return -1;
}}
}
int case3(struct player * p)
{
int player_no=0,i,a,strreq=0,large=0; 
for(i=pl;i<=ph;i++)
{
strreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);
if(  (p[i].strength - strreq )  >  large)   
{    
player_no=i;                                    
large=p[i].strength-strreq;
}
else
printf("ass");           
}      
if(player_no!=0)
{
printf("case3");
p[player_no].x=p[0].x;
p[player_no].y=p[0].y;
printf("sas");
a=case1(player_no,p);
return player_no;
}
else
{
place(player_no,p);
return -1;
}
} 



int pass_hit(int ball_player,struct player *p)
{
int i,receiver=0,large=0,dist=0;
printf("reached pass hit");

for(i=pl;i<=ph;i++)
{
dist=(int)floor(sqrt(pow((p[ball_player].x-p[i].x),2)+pow((p[ball_player].y-p[i].y),2)));
if((((p[ball_player].strength/2-dist)>0)&&((p[i].x-p[ball_player].x)>large)&&(pl==1))||(((p[ball_player].strength/2-dist)>0)&&((p[i].x-p[ball_player].x)<large)&&(pl==12)));			
{
receiver=i;
large=p[i].x-p[ball_player].x;
}
}
if(receiver!=0)
{	printf("receiver found"); 
intercept(ball_player,receiver,p);
p[0].x=p[receiver].x;
p[0].y=p[receiver].y;
return receiver;
}
else 
{printf("hit");
interception(ball_player,p);
return ball_player;
}
}					




void interception(int ball_player,struct player *p)
{
int i,g,h;printf("reached interception");
g=p[ball_player].x;
h=p[ball_player].y;
if(pl==1)
{
for(i=12;i<23;i++)
{
if((p[i].y==p[ball_player].y)&&(p[ball_player].y<10))
{
p[0].y=10;
p[0].x=86;
break;
}
if((p[i].y==p[ball_player].y)&&(p[ball_player].y>40))
{
p[0].y=40;
p[0].x=86;
break;
}
if((p[i].y==p[ball_player].y)&&(p[ball_player].y<40)&&(p[ball_player].y>=10))
{
p[0].y=h+2;
p[0].x+=p[ball_player].strength/2;
break;	
}
if((p[i].y==p[ball_player].y)&&(p[ball_player].y==40))
{
p[0].y=h-2;
p[0].x+=p[ball_player].strength/2;
break;
}
}
if(i==23)
{
if(p[ball_player].y<10)
{
p[0].y=10;
p[0].x=86;
}
if(p[ball_player].y>40)
{
p[0].y=40;
p[0].x=86;
}
if((p[ball_player].y<=40)&&(p[ball_player].y>=10))
{
p[0].y=p[ball_player].y;
p[0].x+=p[ball_player].strength/2;	
}
}		
}
if(pl==12)
{
for(i=1;i<=11;i++)
{

if((p[i].y==p[ball_player].y)&&(p[ball_player].y<10))
{
p[0].y=10;
p[0].x=14;
break;
}
else if((p[i].y==p[ball_player].y)&&(p[ball_player].y>40))
{
p[0].y=40;
p[0].x=14;
break;
}
else if((p[i].y==p[ball_player].y)&&(p[ball_player].y<40)&&(p[ball_player].y>=10))
{
p[0].y=h+2;
p[0].x-=p[ball_player].strength/2;
break;	
}
else if((p[i].y==p[ball_player].y)&&(p[ball_player].y==40))
{
p[0].y=h-2;
p[0].x-=p[ball_player].strength/2;
break;
}
}
if(i==12)
{
if(p[ball_player].y<10)
{
p[0].y=10;
p[0].x=14;
}
if(p[ball_player].y>40)
{
p[0].y=40;
p[0].x=14;
}
if((p[ball_player].y<=40)&&(p[ball_player].y>=10))
{
p[0].y=p[ball_player].y;
p[0].x-=p[ball_player].strength/2;	
}
}		

}
}		

int in_range(int ball_player,struct player *p)
{
int goalstr=0;
printf("reached in range");
if(pl==12)
{
goalstr=preqpb(14,p[ball_player].y,p[ball_player].x,p[ball_player].y );
}
else if(pl==1)
{
goalstr=preqpb(86,p[ball_player].y,p[ball_player].x,p[ball_player].y );
}
if(p[ball_player].strength>=goalstr)
return 1;
return 0;
}

void intercept(int ball_player,int receiver,struct player *p)
{printf("no entry");
int g,h;
g=p[ball_player].x;
h=p[ball_player].y;			

while((g!=p[receiver].x)&&(h!=p[receiver].y))
{
	int i,xdif,ydif;
	xdif=p[receiver].x-p[ball_player].x;
	ydif=p[receiver].y-p[ball_player].y;
	
	if(xdif>0)
	g++;
	else
	g--;
	if(ydif>0)
	h++;
	else
	h--;
	if(pl==1)
	{	
		for(i=12;i<23;i++)
		{
		                  if((p[i].x==g)&&(p[i].y==h))
		                  {
			               interception(ball_player,p);
                           break;
                          }
		                  else
		                  printf(" ");
        }
		if(g==p[receiver].x||h==p[receiver].y)
		{
         if(g==p[receiver].x)
         { 
            while(h!=p[receiver].y)
            {
             if(ydif>0)
             h++;
	         else
             h--;
             for(i=12;i<23;i++)
		     {
              if((p[i].x==g)&&(p[i].y==h))
		      {
			   interception(ball_player,p);
			   break;
               }
		       else
		       printf(" ");
             }
            }
         }
         else if(h==p[receiver].y)
         {  
               while(g!=p[receiver].x)
               {
                if(xdif>0)
                g++;
	            else
                g--;
                for(i=12;i<23;i++)
		        {
                 if((p[i].x==g)&&(p[i].y==h))
		         {
			      interception(ball_player,p);
			      break;
		        }
		        else
		        printf(" ");
                }
              }
         }
         else
         printf("no interception found");
         }
            
        	
	}
	
	else if(pl==12)
	{
		
		for(i=1;i<12;i++)
		{
		if((p[i].x==g)&&(p[i].y==h))
		{
			interception(ball_player,p);
			break;
		}
		else
		printf(" ");
        }
		if(g==p[receiver].x||h==p[receiver].y)
		{
         if(g==p[receiver].x)
         {   while(h!=p[receiver].y)
         {
         if(ydif>0)
         h++;
	     else
         h--;
         for(i=1;i<12;i++)
		 {
         if((p[i].x==g)&&(p[i].y==h))
		 {
			interception(ball_player,p);
			break;
		 }
		 else
		 printf(" ");
         }
         }
         }
         else if(h==p[receiver].y)
         {   while(g!=p[receiver].x)
         {
         if(xdif>0)
         g++;
	     else
         g--;
         for(i=1;i<12;i++)
		 {
         if((p[i].x==g)&&(p[i].y==h))
		 {
			interception(ball_player,p);
			break;
		 }
		 else
		 printf(" ");
         }
         }
         }
         else
         printf("no interception found");
         }
            
        	
	}
}


}



void place(int ball_player,struct player *p)
{int i;
printf("placement");
if (pl==1)
{
//choice=ball_player;
printf("hello");
switch(ball_player)
{
              
case 1://p[1].x=28;p[1].y=25;

p[2].x=30;p[2].y=10;
p[3].x=40;p[3].y=25;
p[4].x=74;p[4].y=26;
p[5].x=45;p[5].y=10;
p[6].x=50;p[6].y=25;
p[7].x=45;p[7].y=40;
p[8].x=60;p[8].y=10;
p[9].x=60;p[9].y=25;
p[10].x=60;p[10].y=40;
p[11].x=70;p[11].y=27;
break;
case 2:p[1].x=28;p[1].y=25;

//p[2].x=30;p[2].y=10;
p[3].x=40;p[3].y=25;
p[4].x=74;p[4].y=26;
p[5].x=45;p[5].y=10;
p[6].x=50;p[6].y=25;
p[7].x=45;p[7].y=40;
p[8].x=60;p[8].y=10;
p[9].x=60;p[9].y=25;
p[10].x=60;p[10].y=40;
p[11].x=70;p[11].y=27;break;
case 3:p[1].x=28;p[1].y=25;

p[2].x=30;p[2].y=10;
//p[3].x=40;p[3].y=25;
p[4].x=74;p[4].y=26;
p[5].x=45;p[5].y=10;
p[6].x=50;p[6].y=25;
p[7].x=45;p[7].y=40;
p[8].x=60;p[8].y=10;
p[9].x=60;p[9].y=25;
p[10].x=60;p[10].y=40;
p[11].x=70;p[11].y=27;break;
case 4:p[1].x=28;p[1].y=25;

p[2].x=30;p[2].y=10;
p[3].x=40;p[3].y=25;
//p[4].x=30;p[4].y=40;
p[5].x=45;p[5].y=10;
p[6].x=50;p[6].y=25;
p[7].x=45;p[7].y=40;
p[8].x=60;p[8].y=10;
p[9].x=60;p[9].y=25;
p[10].x=60;p[10].y=40;
p[11].x=70;p[11].y=27;break;
case 5:p[1].x=28;p[1].y=25;

p[2].x=30;p[2].y=10;
p[3].x=40;p[3].y=25;
p[4].x=74;p[4].y=26;
//p[5].x=45;p[5].y=10;
p[6].x=50;p[6].y=25;
p[7].x=45;p[7].y=40;
p[8].x=60;p[8].y=10;
p[9].x=60;p[9].y=25;
p[10].x=60;p[10].y=40;
p[11].x=70;p[11].y=27;break;
case 6:p[1].x=28;p[1].y=25;

p[2].x=30;p[2].y=10;
p[3].x=40;p[3].y=25;
p[4].x=74;p[4].y=26;
p[5].x=45;p[5].y=10;
//p[6].x=50;p[6].y=25;
p[7].x=45;p[7].y=40;
p[8].x=60;p[8].y=10;
p[9].x=60;p[9].y=25;
p[10].x=60;p[10].y=40;
p[11].x=70;p[11].y=27;break;
case 7:p[1].x=28;p[1].y=25;

p[2].x=30;p[2].y=10;
p[3].x=40;p[3].y=25;
p[4].x=74;p[4].y=26;
p[5].x=45;p[5].y=10;
p[6].x=50;p[6].y=25;
//p[7].x=45;p[7].y=40;
p[8].x=60;p[8].y=10;
p[9].x=60;p[9].y=25;
p[10].x=60;p[10].y=40;
p[11].x=70;p[11].y=27;break;
case 8:p[1].x=28;p[1].y=25;

p[2].x=30;p[2].y=10;
p[3].x=40;p[3].y=25;
p[4].x=74;p[4].y=26;
p[5].x=45;p[5].y=10;
p[6].x=50;p[6].y=25;
p[7].x=45;p[7].y=40;
//p[8].x=60;p[8].y=10;
p[9].x=60;p[9].y=25;
p[10].x=60;p[10].y=40;
p[11].x=70;p[11].y=27;break;
case 9:p[1].x=28;p[1].y=25;

p[2].x=30;p[2].y=10;
p[3].x=40;p[3].y=25;
p[4].x=74;p[4].y=26;
p[5].x=45;p[5].y=10;
p[6].x=50;p[6].y=25;
p[7].x=45;p[7].y=40;
p[8].x=60;p[8].y=10;
//p[9].x=60;p[9].y=25;
p[10].x=60;p[10].y=40;
p[11].x=70;p[11].y=27;break;
case 10:p[1].x=28;p[1].y=25;

p[2].x=30;p[2].y=10;
p[3].x=40;p[3].y=25;
p[4].x=74;p[4].y=26;
p[5].x=45;p[5].y=10;
p[6].x=50;p[6].y=25;
p[7].x=45;p[7].y=40;
p[8].x=60;p[8].y=10;
p[9].x=60;p[9].y=25;
//p[10].x=60;p[10].y=40;
p[11].x=70;p[11].y=27;break;
case 11:printf("11");
       p[1].x=28;p[1].y=25;

p[2].x=30;p[2].y=10;
p[3].x=40;p[3].y=25;
p[4].x=74;p[4].y=26;
p[5].x=45;p[5].y=10;
p[6].x=50;p[6].y=25;
p[7].x=45;p[7].y=40;
p[8].x=60;p[8].y=10;
p[9].x=60;p[9].y=25;
p[10].x=60;p[10].y=40;
//p[11].x=70;p[11].y=27;
break;
}
}
else 
{
p[12].x=72;p[12].y=25;
p[13].x=70;p[13].y=10;
p[14].x=60;p[14].y=25;
p[15].x=70;p[15].y=40;
p[16].x=55;p[16].y=10;
p[17].x=50;p[17].y=25;
p[18].x=55;p[18].y=40;
p[19].x=40;p[19].y=10;
p[20].x=40;p[20].y=25;
p[21].x=40;p[21].y=40;
p[22].x=30;p[22].y=30;


}

}


};

//end of class

