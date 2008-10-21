#include<stdio.h>
#include<math.h>

#include<stdlib.h>
#include<string.h>

class team0055  //here the class name is given to be team0002 assuming that the registration no. of the participant was 2
{
    private:      //private fns and variables defined
	int pl,ph,player_no;
	struct initial
	{
		int x,y;
	} icoor[23];
	char field[101][51];

	int preqp(int finalx,int finaly, int initialx ,int initialy )  //function which tells the strength req by player to move from
	{
		float req;                                                    //place to another
		req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
		return (int)req;
	}

	int preqpb(int finalx,int finaly, int initialx ,int initialy )   //function which tells the strength req by hitter of ball to hit
	{
		float req;
		int i;                                            //the ball from one place to another
		req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
		i=(int)req;
		return i;
	}

    //public functions
    public:
	int init(int team_number, struct player *p,char farray[][51])   //the mandatory function which initialises the team no. of the
	{                                                  //participant and tells him the initial field distribution
		int i,j;
		player_no = team_number;
		for(i=0;i<101;i++)
		    for(j=0;j<51;j++)
			field[i][j]=farray[i][j];
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
		}

		else
		{
			pl=12;
			ph=22;
		}
		for(i=0;i<23;i++)
		{
			icoor[i].x=p[i].x;
			icoor[i].y=p[i].y;
		}

	 // checking where is ball

			//player having the ball
		ball_player=0;
		for(i=1;i<23;i++)
		    if( p[0].x==p[i].x && p[0].y==p[i].y && p[i].strength>=p[ball_player].strength)
		    {
			if(p[i].strength==p[ball_player].strength&&ball_player/12!=i/12)
			    if(player_no==2&&i>11)
				ball_player=i;
			    else continue;
			else ball_player=i;
		    }
		if(ball_player==0)
		{
       //so no player is having the ball
		    a=case3(p);

		    return a;   //returns the hitter of the ball to the controller
		}


		if((ball_player<=11&&player_no==1)||(ball_player>11&&player_no==2))
		{
	//then ball is with my team player

		    a=case1(ball_player,p);

		    return a;
		}


    // ball with opp team player

		a=case2(ball_player,p);

		return a;

}//end of player func.



//definition of case1() , when the ball is with my player


int case1(int ball_player,struct player * p)
{
	int i,large=0,pass=0,small=100,l_opp=0;
	ball_player=larger_str_player(ball_player,p);
	p[ball_player].x=p[0].x;
	p[ball_player].y=p[0].y;
	for(i=1;i<=22;i++)
	{
	    if(p[i].x==p[ball_player].x && p[i].y==p[ball_player].y && i!=ball_player && p[i].strength>large)
		if(player_no==1 && i>=12 || player_no==2 && i<=11)
		{
		    large=p[i].strength;
		    l_opp=i;
		}
	}
	if( can_goal(ball_player,p,l_opp) )
	    return ball_player;

	for(i=pl;i<=ph;i++)
	    if(i!=ball_player)
	    {
		if( i==8 || i==19 && p[i].strength-preqp(p[i].x,5,icoor[i].x,icoor[i].y)>=30)
		    p[i].y=5;
		else if( i==10 || i==21 && p[i].strength-preqp(p[i].x,5,icoor[i].x,icoor[i].y)>=30)
		    p[i].y=45;
	    }
	if(player_no==1&&p[0].x<30||player_no==2&&p[0].x>70)
	{
	    for(i=pl+4;i<=pl+6;i++)
		if( ball_player!=i && (player_no==1 && p[i].x<=30 || player_no==2 && p[i].x>=70) && p[i].strength-preqp(35+30*(player_no-1),p[i].y,icoor[i].x,icoor[i].y)>=20)
		    p[i].x=(player_no-1)*30+35;

	    for(i=pl+7;i<=pl+9;i++)
		if( ball_player!=i && (player_no==1 && p[i].x<=40 || player_no==2 && p[i].x>=60) && p[i].strength-preqp(45+10*(player_no-1),p[i].y,icoor[i].x,icoor[i].y)>=25)
		    p[i].x=(player_no-1)*10+45;

	    if( ball_player!=ph && (player_no==1 && p[ph].x<=50 || player_no==2 && p[ph].x>=50) && p[ph].strength-preqp(55-10*(player_no-1),p[ph].y,icoor[ph].x,icoor[ph].y)>=35)
		p[ph].x=(1-player_no)*10+55;

	}

	else if(player_no==1&&p[0].x>=30&&p[0].x<40||player_no==2&&p[0].x<=70&&p[0].x>60)
	{
	    for(i=pl+4;i<=pl+6;i++)
		if( ball_player!=i && (player_no==1 && p[i].x<=40 || player_no==2 && p[i].x>=60) && p[i].strength-preqp(45+10*(player_no-1),p[i].y,icoor[i].x,icoor[i].y)>=25)
		    p[i].x=(player_no-1)*10+45;

	    for(i=pl+7;i<=pl+9;i++)
		if( ball_player!=i && (player_no==1 && p[i].x<=50 || player_no==2 && p[i].x>=50) && p[i].strength-preqp(55-10*(player_no-1),p[i].y,icoor[i].x,icoor[i].y)>=30)
		    p[i].x=(1-player_no)*10+55;

	    if( ball_player!=ph && (player_no==1 && p[ph].x<=60 || player_no==2 && p[ph].x>=40) && p[ph].strength-preqp(65-30*(player_no-1),p[ph].y,icoor[ph].x,icoor[ph].y)>=30)
		p[ph].x=(1-player_no)*30+65;

	}

	else if(player_no==1&&p[0].x>=40&&p[0].x<50||player_no==2&&p[0].x<=60&&p[0].x>50)
	{

	    for(i=pl+7;i<=pl+9;i++)
		if( ball_player!=i && (player_no==1 && p[i].x<=60 || player_no==2 && p[i].x>=40) && p[i].strength-preqp(64-28*(player_no-1),p[i].y,icoor[i].x,icoor[i].y)>=30)
		    p[i].x=(1-player_no)*28+64;

	    if( ball_player!=ph && (player_no==1 && p[ph].x<=70 || player_no==2 && p[ph].x>=30) && p[ph].strength-preqp(74-48*(player_no-1),p[ph].y,icoor[ph].x,icoor[ph].y)>=25)
		p[ph].x=(1-player_no)*48+74;

	}

	if((ball_player%11==9 || ball_player%11==0) && ( player_no==1 && p[0].x>=49 || player_no==2 && p[0].x<=51 ))
	{
	    for(i=pl+7;i<=pl+9;i+=2)
		if((p[i].x<=60 && player_no==1 || p[i].x>=40 && player_no==2) && p[i].strength-preqp(64-28*(player_no-1),p[i].y,icoor[i].x,icoor[i].y)>=20)
		    p[i].x=(1-player_no)*28+64;
	}

   //if goal is not in the range of the ball

   //this loop searches for a player who is ahead of the presnt player having the possession of the ball and if any such player is
   //found then ball is passed to him

	large=0;
	for(i=pl;i<=ph;i++)
	    if( ( p[i].x>p[ball_player].x&&player_no==1 || p[i].x<p[ball_player].x&&player_no==2) && abs(p[ball_player].x-p[i].x)>large && p[ball_player].strength-preqp(p[i].x,p[i].y,icoor[i].x,icoor[i].y)-p[l_opp].strength>=preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y))
		if(!intersect(p[i].x,p[i].y,p))
		{
		    large=abs(p[ball_player].x-p[i].x);
		    pass=i;
		}
	if(pass)
	{
	    p[0].x=p[pass].x;
	    p[0].y=p[pass].y;
	    return ball_player;
	}

	if( (player_no==1&&field[p[ball_player].x][p[ball_player].y]!='D'||player_no==2&&field[p[ball_player].x][p[ball_player].y]!='d')&&can_dee(ball_player,p,l_opp) )
	    return ball_player;


   //if no such player is found then the ball is back-passed
	for(i=pl+1;i<=ph;i++)
	    if( i!=ball_player && (p[i].x<=p[ball_player].x&&player_no==1 || p[i].x>=p[ball_player].x&&player_no==2) && preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y)<small && p[ball_player].strength-preqp(p[ball_player].x,p[ball_player].y,icoor[ball_player].x,icoor[ball_player].y)-p[l_opp].strength>=preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y))
		if(!intersect(p[i].x,p[i].y,p))
		{
		    small=preqp(p[ball_player].x,p[ball_player].y,p[i].x,p[i].y);
		    pass=i;
		}

	if(pass)
	{
	    p[0].x=p[pass].x;
	    p[0].y=p[pass].y;
	    return ball_player;
	}

	if(p[ball_player].strength==p[l_opp].strength)
		return ball_player;

	return -1;
}                     // end of case1() func.
   



// Definition of case2() func.

//ball is with opp team's player
int case2(int ball_player,struct player * p)
{
	int i,a;
	int strreq,large=0,strong_p=0,same_p=0;

	if(p[0].x>40 && p[0].x<60)
	{
	    for(i=pl+4;i<=pl+6;i++)
		if( (player_no==1 && p[i].x>=40 || player_no==2 && p[i].x<=60) && p[i].strength-preqp(35-30*(player_no-1),p[i].y,icoor[i].x,icoor[i].y)>=20)
		    p[i].x=(player_no-1)*30+35;

	    for(i=pl+7;i<=pl+9;i++)
		if( (player_no==1 && p[i].x>=55 || player_no==2 && p[i].x<=45) && p[i].strength-preqp(50,p[i].y,icoor[i].x,icoor[i].y)>=25)
		    p[i].x=50;

	    if( (player_no==1 && p[ph].x>=65 || player_no==2 && p[ph].x<=35) && p[ph].strength-preqp(60-20*(player_no-1),p[ph].y,icoor[ph].x,icoor[ph].y)>=30)
		p[ph].x=(1-player_no)*20+60;

	}

	else if(player_no==1 && p[0].x>30 && p[0].x<=40 || player_no==2 && p[0].x>=60 && p[0].x<70)
	{
	    for(i=pl+4;i<=pl+6;i++)
		if( (player_no==1 && p[i].x>=35 || player_no==2 && p[i].x<=65) && p[i].strength-preqp(30+40*(player_no-1),p[i].y,icoor[i].x,icoor[i].y)>=20)
		    p[i].x=(player_no-1)*40+30;

	    for(i=pl+7;i<=pl+9;i++)
		if( (player_no==1 && p[i].x>=45 || player_no==2 && p[i].x<=55) && p[i].strength-preqp(40+20*(player_no-1),p[i].y,icoor[i].x,icoor[i].y)>=25)
		    p[i].x=(player_no-1)*20+40;

	    if( (player_no==1 && p[ph].x>=55 || player_no==2 && p[ph].x<=45) && p[ph].strength-preqp(50,p[ph].y,icoor[ph].x,icoor[ph].y)>=35)
		p[ph].x=50;

	}


	for(i=1;i<=22;i++)
	    if(p[i].x==p[ball_player].x && p[i].y==p[ball_player].y && i!=ball_player && p[i].strength-preqp(p[i].x,p[i].y,icoor[i].x,icoor[i].y)>large)
		if(player_no==1 && i<=11 || player_no==2 && i>=12)
		{
		    large=p[i].strength-preqp(p[i].x,p[i].y,icoor[i].x,icoor[i].y);
		    same_p=i;
		}

	large=0;
	if(can_goal(ball_player,p,same_p))
	{
	    if(p[ball_player].y>=10&&p[ball_player].y<=40)
		for(i=pl+1;i<=pl+3;i++)
		{
		    if(player_no==1)
			p[i].x=p[ball_player].x-1;
		    else
			p[i].x=p[ball_player].x+1;

		    p[i].y=p[ball_player].y-1+(i-2)%11;
		}
	    else if( (player_no==1 && p[ball_player].x<=14) || (player_no==2 && p[ball_player].x>=86) )
		for(i=pl+1;i<=pl+3;i++)
		{
		    p[i].x=p[ball_player].x+1-(i-2)%11;

		    if(p[ball_player].y<10)
			p[i].y=p[ball_player].y+1;
		    else
			p[i].y=p[ball_player].y-1;
		}

	    else
	    {
		for(i=pl+1;i<=pl+3;i++)
		    if(p[i].strength-preqp(p[0].x,p[0].y,icoor[i].x,icoor[i].y)>large)
		    {
			large=p[i].strength-preqp(p[0].x,p[0].y,icoor[i].x,icoor[i].y);
			strong_p=i;
		    }

		if(player_no==1)
		    p[strong_p].x=p[ball_player].x-1;
		else
		    p[strong_p].x=p[ball_player].x+1;

		if(p[ball_player].y<10)
		    p[strong_p].y=p[ball_player].y+1;
		else
		    p[strong_p].y=p[ball_player].y-1;
	    }

	    large=20;
	    strong_p=0;
	    for(i=pl+1;i<=pl+3;i++)
		if(p[i].strength-preqp(p[0].x,p[0].y,p[strong_p].x,p[strong_p].y)-p[ball_player].strength>=large)
		{
		    large=p[i].strength-preqp(p[0].x,p[0].y,icoor[strong_p].x,icoor[strong_p].y)-p[ball_player].strength;
		    strong_p=i;
		}

	    if(strong_p)
	    {
		p[strong_p].x=p[0].x;
		p[strong_p].y=p[0].y;
		a=case1(strong_p,p);
		return a;
	    }
	    return -1;
	}


	int opl,oph,posx=p[0].x,posy=p[0].y,fx,fy,dx,dy,pass=0,mark=0,mx,my;

	if(player_no==1)
	{
	    opl=12;
	    oph=22;
	}
	else
	{
	    opl=1;
	    oph=11;
	}
	large=0;
	for(i=opl;i<=oph;i++)
	    if( ( p[i].x>p[ball_player].x&&player_no==2 || p[i].x<p[ball_player].x&&player_no==1) && abs(p[ball_player].x-p[i].x)>large && p[ball_player].strength-preqp(p[i].x,p[i].y,icoor[i].x,icoor[i].y)-p[same_p].strength>=preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y))
		if(!intersect(p[i].x,p[i].y,p))
		{
		    large=abs(p[ball_player].x-p[i].x);
		    pass=i;
		}

	if(pass)
	{
	    fx=p[pass].x;
	    fy=p[pass].y;
	    dx=fx-p[0].x;
	    dy=fy-p[0].y;

	    large=0;
	    while(posx!=fx||posy!=fy)
	    {

		if(posx!=fx)
		    (dx>0)?(posx)++:(posx)--;
		if(posy!=fy)
		    (dy>0)?(posy)++:(posy)--;

		if(!mark&&posx!=fx||posy!=fy)
		    for(i=pl;i<=ph;i++)
			if(p[i].strength-preqp(posx,posy,icoor[i].x,icoor[i].y)>large)
			{
			    large=p[i].strength-preqp(posx,posy,icoor[i].x,icoor[i].y);
			    mx=posx;
			    my=posy;
			    mark=i;
			}
	    }
	    if(mark)
	    {
		p[mark].x=mx;
		p[mark].y=my;
	    }
	}


 //this for loop searches for a player who has more strength than the opponent's player having possession of the ball ,after
 //reaching at the ball's position and if such player is found then the case becomes similar to one when my player was having the
 //possession of the ball ,so the case1 function is called and finally the hitter of ball is returned to controller
	large=0;
	strong_p=0;
	for(i=pl;i<=ph;i++)
	{
	    strreq=preqp(p[ball_player].x,p[ball_player].y,icoor[i].x,icoor[i].y);

	    if( (p[i].strength - strreq - p[ball_player].strength) > large)
	    {
		large=p[i].strength - strreq - p[ball_player].strength;
		strong_p=i;
	    }
	}
	if(strong_p)
	{
	    p[i].x=p[ball_player].x;
	    p[i].y=p[ball_player].y;
	    a=case1(strong_p,p);
	    return a;
	}

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


int larger_str_player(int ball_player,struct player * p)
{
	int i,large=p[ball_player].strength;
	for(i=pl;i<=ph;i++)
	    if(p[i].strength-preqp(p[0].x,p[0].y,icoor[i].x,icoor[i].y)>large)
	    {
		large=p[i].strength-preqp(p[0].x,p[0].y,icoor[i].x,icoor[i].y);
		ball_player=i;
	    }

	return ball_player;
}


int intersect(int fx,int fy,struct player * p)
{
	int i,posx=p[0].x,posy=p[0].y;
	int dx=fx-p[0].x,dy=fy-p[0].y;

	while(posx!=fx||posy!=fy)
	{

	    if(posx!=fx)
		(dx>0)?(posx)++:(posx)--;
	    if(posy!=fy)
		(dy>0)?(posy)++:(posy)--;

	    for(i=1;i<=22;i++)
		if(posx==p[i].x && posy==p[i].y)
		{
		    if(posx==fx&&posy==fy&&(player_no==1&&i<=11||player_no==2&&i>=12))
			continue;
		    return i;
		}
	}      //loop to check whether any of the player intersect the ball
	return 0;
}

//can_goal is a function defined by the participant
//it checks wheter the ball is in the range of the goal or not and returns 1 or 0 accordingly

int can_goal(int ball_player,struct player * p,int l_opp)
{
	int i,j,gxl,gxh;

	if(ball_player/12==0)
	{
	    gxl=86;
	    gxh=99;
	}
	else
	{
	    gxl=1;
	    gxh=14;
	}

	for(i=gxl;i<=gxh;i++)
	    for(j=10;j<=40;j++)
		if(preqpb(i,j,p[ball_player].x,p[ball_player].y)<=p[ball_player].strength-preqp(p[ball_player].x,p[ball_player].y,icoor[ball_player].x,icoor[ball_player].y)-p[l_opp].strength)
		    if(!intersect(i,j,p))
		    {
			p[0].x=i;
			p[0].y=j;
			return 1;
		    }
	return 0;
}

int can_dee(int ball_player,struct player * p,int l_opp)
{
	int i,j,gxl,gxh,max=59,min=41;

	if(ball_player/12==0)
	{
	    gxl=60;
	    gxh=99;
	}
	else
	{
	    gxl=1;
	    gxh=40;
	}

	for(i=gxl;i<=gxh;i++)
	    for(j=5;j<=45;j++)
		if(preqpb(i,j,p[ball_player].x,p[ball_player].y)<=p[ball_player].strength-preqp(p[ball_player].x,p[ball_player].y,icoor[ball_player].x,icoor[ball_player].y)-p[l_opp].strength)
		    if(!intersect(i,j,p))
			if(player_no==1&&i>max)
			{
			    max=i;
			    p[0].x=i;
			    p[0].y=j;
			}
			else if(player_no==2&&i<min)
			{
			    min=i;
			    p[0].x=i;
			    p[0].y=j;
			}
	if(max!=59||min!=41)
		return 1;
	return 0;
}



};   //end of the class team0002





