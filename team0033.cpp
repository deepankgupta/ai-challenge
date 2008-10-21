#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

class team0033			// REGISTRATION NUMBER
{

private:				// Private Parts
int pl,ph,player_num,player_no, turn, pbx, pby, score, spirit[3],phitter;

int preqp(int finalx,int finaly, int initialx ,int initialy )	// functions from test player
{
	float req;
	req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
	return (int)req;
} 
    
int preqpb(int finalx,int finaly, int initialx ,int initialy )   // functions from test player
{
	float req;
	int i;
	req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	i=(int)req;
	return i;
} 
void points(struct player *p)
{
     int i;
     if     ((p[0].x>=60)&&(p[0].y>=5&&p[0].y<=45)&&!((pbx>=60)&&(pby>=5&&pby<=45)))
       if(player_num==2)
         score--;
     else if((p[0].x<=40)&&(p[0].y>=5&&p[0].y<=45)&&!((pbx<=40)&&(pby>=5&&pby<=45)))
       if(player_num==1)
         score--;
}
bool freeze(struct player *p)
{
    int i, hitman, hitmanstr, strreq, ball_player;
    for(i=pl;i<=ph;i++)
    {
      if(p[i].x==p[0].x && p[i].y==p[0].y && p[i].strength>=30)
         return true;
    }
	for(i=1;i<23;i++)                            // Who will get d shot?
	{
       strreq=preqp(p[0].x, p[0].y, p[i].x, p[i].y);
       if(i>=pl && i<=ph)
       {
         if(p[i].strength-strreq >= hitmanstr || ((p[i].x==p[0].x && p[i].y==p[0].y) && p[i].strength-strreq>=hitmanstr-20))
         {
           hitman=i;
           ball_player=i;
           if(p[hitman].x==p[0].x && p[hitman].y==p[0].y)
             hitmanstr=p[i].strength+20;                 // If player is on ball
           else
             hitmanstr=p[i].strength-strreq;             // if player has 2 move
         }
       }
       else
       {
           if(p[i].strength-strreq > hitmanstr)
           {
             hitman=i;
             ball_player=i;
             hitmanstr=p[i].strength-strreq;             // Opponent player
           }
       }
    }
    if(hitman<=ph && hitman>=pl)                         // Is my player hitman?
    {
       p[hitman].x=p[0].x;
       p[hitman].y=p[0].y;
       return true;
    }
    return false;
}

void spirits(struct player *p)                                  // Best Fit
{
     int i, strreq, str0=0, str1=0, str2=0;
     if(p[0].x<40||p[0].x>60)
        return;
     for(i=0;i<3;i++)
         spirit[i]=0;        // Set initial value to zero
     for(i=pl;i<=ph;i++)
     {
        strreq=preqp(p[0].x, p[0].y, p[i].x, p[i].y);
        if(p[i].strength-strreq>0 && i!=phitter)
        {
          if(p[i].strength-strreq>p[spirit[0]].strength-str0)
          {
            spirit[2]=spirit[1]; str2=str1;
            spirit[1]=spirit[0]; str1=str0;
            spirit[0]=i;  str0=strreq;
          }
          else if(p[i].strength-strreq>p[spirit[1]].strength-str1)
          {
            spirit[2]=spirit[1]; str2=str1;
            spirit[1]=i;  str1=strreq;
          }
          else if(p[i].strength-strreq>p[spirit[2]].strength-str2)
            spirit[2]=i;  str2=strreq;
        }
     }
     if(spirit[0]==0)
        return;
     for(i=0;i<3;i++)
     {
        if(spirit[i]==0)
           break;
        if(player_num==1)
           p[spirit[i]].x=p[0].x-1;
        else 
           p[spirit[i]].x=p[0].x+1;
     }
     p[spirit[0]].y=p[0].y;
     if(p[0].y-25>0)
     {
        if(spirit[1]!=0)
           p[spirit[1]].y=p[0].y-1;
        if(spirit[2]!=0)
           p[spirit[2]].y=p[0].y+1;
     }
     else
     {
        if(spirit[1]!=0)
           p[spirit[1]].y=p[0].y+1;
        if(spirit[2]!=0)
           p[spirit[2]].y=p[0].y-1;
     }
}

/*void firewall(struct player *p)
{
    int i,j=0,strreq,desired=0, shotx;
    int avail[11], availstrq[11];
    for(i=pl;i<=ph&&j<=10;i++)
    {
      if(p[i].strength>5 && i!=spirit[0] && i!=spirit[1] && i!=spirit[2] && i!=phitter)
         avail[j]=i;
      else
         avail[j]=0;
      j++;
      availstrq[j]=0;
    }
    if(player_num==1)
      shotx=41;
    else
      shotx=59;
    for(j=1;j<=6;j++)
    {
      desired=0;
      for(i=0;i<=10;i++)
      {
        strreq=preqp(p[0].x, p[0].y, p[avail[i]].x, p[avail[i]].y);
        if(p[avail[i]].x=shotx && p[avail[i]].y==7*j)
           strreq=strreq-20;
        else if(p[avail[i]].strength-strreq>p[avail[desired]].strength-availstrq[desired])
        {
          desired=i;
          availstrq[desired]=strreq;

        }
      }

      if(player_num==1)
        p[avail[desired]].x=41;
      else
        p[avail[desired]].x=59;
      p[avail[desired]].y=7*j;
      for(i=0;i<=10;i++)
      {
        if(i==desired)
          avail[i]=0;
        availstrq[i]=0;
      }
    }
}   //  */

int insanity(struct player *p)
{
    int i,hitman=0,hitmanstr=0,strreq, shotx, shoty;
    for(i=pl;i<=ph;i++)
    {
      strreq=preqp(p[0].x, p[0].y, p[i].x, p[i].y);
      if(p[i].strength-strreq>p[hitman].strength-hitmanstr)
      {
         hitman=i;
         hitmanstr=strreq;
      }
    }
    if(player_num==1)
       shotx=60;
    else
       shotx=40;
    phitter=hitman;
    for(i=5;i<=45;i++)
    {
       strreq=preqpb(shotx,i, p[0].x, p[0].y);
       if(p[hitman].strength-hitmanstr>strreq)
       {
          if(intrusion(p, hitman, shotx, i))
          {
             p[hitman].x=p[0].x;
             p[hitman].y=p[0].y;
             p[0].x=shotx;
             p[0].y=i;
             score++;
             return hitman;
          }
       }
    }
    
    if(hitman==0)
       return -1;
    
    p[hitman].x=p[0].x;
    p[hitman].y=p[0].y;
    if(player_num==1)
       p[0].x=p[0].x+p[hitman].strength/2;
    else
       p[0].x=p[0].x-p[hitman].strength/2;
    p[0].y=p[0].y+1;
    
    return hitman;
}
       
    

bool intrusion(struct player *p, int phitter, int xpx, int xpy)
{
    char status;
    int validposx, validposy, i, xdiffb, ydiffb;
    status='f';  //tells the region in which the ball is present after every step 
                 //'f' when the ball is in the normal region ,'d' or 'D' when the ball is in the dee of either of the teams, 'g' or 'G'
                 //when the ball is in the goal of any of the teams , 'B' when ball reaches the boundary, ''i if the ball is 
                 //interrupted by any of the player and 'r' if the ball reaches the desired position as changed by the participant
		 
	xdiffb=xpx-p[0].x;   //calculates the difference between changed coordinates and initial coordinates of the 
	ydiffb=xpy-p[0].y;   //ball
      
	validposx=p[0].x;  //validposx and validposy keeps a track of the step by step movement of the ball from its 
	validposy=p[0].y;  //initial position to the desired position
      
	while((status=='f')||(status=='D')||(status=='d'))
	{
		if(validposx!=xpx)
			(xdiffb>0)?(validposx)++:(validposx)--;
		if(validposy!=xpy)
			(ydiffb>0)?(validposy)++:(validposy)--;
       
		for(i=1;i<=22;i++)
		{
			if((validposx==p[i].x)&&(validposy==p[i].y))
			{
				status='i';
				break;
			}
		}      //loop to check whether any of the player intersect the ball
       
		if((validposx==xpx)||(validposy==xpy))            //when ball reaches its desired position
		{
			return true;
		}
	}//end of while loop which operates until ball is interrupted or reaches its desired pos or enters goal or boundary
    return false;
}
    
//*/
public:					// Public
int init(int team_number, struct player *p,char farray[][51])   // mandatory function from test player
{
	int i;
	player_no = team_number;
	turn=0;			// No of turns....
	if(player_no==1)
	{
		pl=1;			// pl = lower limit
		ph=11;			// ph = higher limit
		player_num=1;
	}
	else
	{
		pl=12;
		ph=22;
		player_num=2;
	}
	score=0;
	pbx=p[0].x;
	pby=p[0].y;
}


int player( struct player *p)        //MAIN PART
{
	turn++;						// No. of Turns
	int a=-1;
	points(p);                // Update points on basis of dee

	if(score>0)
	   if(freeze(p))          // If I m on top, deep-freeze d ball
	      return -1;
    a=insanity(p);            // InSaNe Kick*/
    
    spirits(p);            // A big check on balls movement

    pbx=p[0].x;               // Updating history
    pby=p[0].y;               // of ball coordinates
    
    
    return a;  //*/  return -1;
}
};   //end of the class
