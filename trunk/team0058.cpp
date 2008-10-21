#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#include<math.h>

struct player
{int x,y,strength;
 int team;
 };

char fieldarray[101][51]={0};
struct player global[23];





class team0058
{
private:
	int team,xfin,yfin;

	int preqp(int finalx,int finaly, int initialx ,int initialy )
	{
		float req;
		req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
		return (int)req;
	}


	int preqpb(int finalx,int finaly, int initialx ,int initialy )
	{
		float req;
		int i;
		req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
		i=(int)req;
		return i;
	}

public:
	int init(int team_number, struct player *p,char farray[][51])
	{
		team = team_number;
	}


	int check(int x2,int y2,int ball_player,int team_no,struct player *p)
	{
		int pl,ph,i=0,x3,y3,flag=0,k;
		if(team_no==1)
		{
			pl=1;
			ph=11;
		}
		else if(team_no==2)
		{
			pl=12;
			ph=22;
		}


		k=preqpb(x2,y2,p[ball_player].x,p[ball_player].y);

		if(p[ball_player].strength < k)
			flag=1;
		if(p[ball_player].strength >= k)
		{
			x3=p[ball_player].x;
			y3=p[ball_player].y;
			do
			{
				if(x3 < x2)
					x3++;
				else if(x3>x2)
					x3--;
				for(i=pl;i<=ph;i++)
				{
					if(p[i].x==x3 && p[i].y==y3)
					{
						flag=1;
						break;
					}
				}

				if(y3 < y2)
					y3++;
				else if(y3>y2)
					y3--;

				for(i=pl;i<=ph;i++)
				{
					if(p[i].x==x3 && p[i].y==y3)
					{
						flag=1;
						break;
					}
				}

				if(flag==1)
					break;

			}while(x3!=x2 || y3!=y2);
		}

		if(flag==0)
			return 1;
		else
			return 0;
	}


	int in_d(int no,struct player *p)
	{
		int i,shot=0,team_no=0;
		if(team==1)
		{
			xfin=60;
			team_no=2;
		}
		else
		{
			xfin=40;
			team_no=1;
		}
		yfin=p[no].y;
		for(i=0;;i++)
		{
			if(((yfin+i)<=45)||((yfin-i)>=5))
			{
				if(((yfin+i)<=45) )
				{       shot=1;
					break;
				}
				else if(((yfin-i)>=5))
				{
					shot=1;
					break;
				}
			}
			else
				break;
		}
		return shot;
	}



	void change(int no, struct player *p)
	{
		int i;
		if(p[no].strength!=0)
		{
			if(p[no].y>37)
				p[no].y=37;
			else if(p[no].y<13)
				p[no].y=13;
			else
			{       if(team==1)
				p[no].x+=1;
				else
				p[no].x-=1;
				p[no].y+=3;
			}
		}
		else
		{
			i=max_str(p[no].x,p[no].y,team,p);
			p[i].x=p[no].x;
			p[i].y=p[no].y;
		}
	}
	int max_str(int x,int y,int no,struct player *p)
	{
		int pl,ph,i,j,max=0,k,l,ball_player;

		if(no==1)
		{
			pl=1;
			ph=11;
		}
		else if(no==2)
		{
			pl=12;
			ph=22;
		}
		for(i=1;i<=22;i++)
		{
			if(p[i].x==p[0].x && p[i].y==p[0].y)
				ball_player=i;
		}

		for(i=pl;i<=ph;i++)
		{
			if(i!=ball_player)
			{
				k=preqp(x,y,p[i].x,p[i].y);
				l=p[i].strength-k;
				if(l>max)
				{
					max=l;
					j=i;
				}
			}
		}
		return j;
	}



	void accelerate(int ball_player,struct player *p)
	{
		static int chan=0;
		int i;

		if(team==1)
		{
			if(chan%2==0)
			{
				for(i=1;i<12;i++)
				{
					if(i>7 && i!=ball_player)
					{
						if(p[ball_player].x > 46)
						{
							chan++;
							if(p[ball_player].x+6 < 85)
								p[i].x=p[ball_player].x+(2*i-14);
							if(p[i].y > p[ball_player].y)
								p[i].y=p[ball_player].y+4;
							else if(p[i].y<p[ball_player].y)
								p[i].y=p[ball_player].y-4;
							else if(p[i].y==p[ball_player].y)
							{
								if(p[i].y>25)
									p[i].y-=3;
								else
									p[i].y+=3;
							}
						}
					}


					if(i>4 && i<8 && i!=ball_player)
					{
						if(p[ball_player].x <47)
							p[i].x=p[ball_player].x+3;

						if(((p[i].y-5)>p[ball_player].y)||((p[i].y+5)<p[ball_player].y))
						{
							p[i].y=p[ball_player].y-4*(i-6);
						}
					}
					if(i>1 && i<4 && i!=ball_player)
					{
						if(p[ball_player].x > 43)
							p[i].x=42;
						else
						{
							p[i].x=p[ball_player].x-1;
						}
					}
				}
			}
			
	      }

		else if(team==2)
		{
			if(chan%2==0)
			{
				for(i=12;i<=22;i++)
				{
					if(i>18 && i!=ball_player )
					{
						if(p[ball_player].x < 54)
						{
							chan++;
							if((p[ball_player].x-6) > 15 )
								p[i].x=p[ball_player].x-(2*i-14);
							if(p[i].y > p[ball_player].y)
								p[i].y=p[ball_player].y+4;
							else if(p[i].y<p[ball_player].y)
								p[i].y=p[ball_player].y-4;
							else if(p[i].y==p[ball_player].y)
							{
								if(p[i].y>25)
									p[i].y-=3;
								else
									p[i].y+=3;
							}
						}
					}


					if(i>15 && i<19 && i!=ball_player)
					{
						if(p[ball_player].x > 54)
							p[i].x=p[ball_player].x-3;

						if(((p[i].y-5)>p[ball_player].y)||((p[i].y+5)<p[ball_player].y))
						{
							p[i].y=p[ball_player].y-4*(i-17);
							p[i].x+=2;
						}
					}
					if(i>12 && i<16 && i!=ball_player )
					{
						if(p[ball_player].x < 58)
							p[i].x=58;
						else
						{
							p[i].x=p[ball_player].x-1;
						}

					}
				}
			}
		}
	}










	int in_range_y(int ball_player,struct player * p)
	{
		int finx,team_no,finy,x1,y1,i,con=0;

		if(team==1)
		{
			finx=86;
			team_no=2;
		}
		else if(team==2)
		{
			finx=14;
			team_no=1;
		}

		finy=10;

		while(con==0 && finy<41)
		{
			con=check(finx,finy,ball_player,team_no,p);
			if(con==0)
				finy++;
		}
		if(finy<41)
			return finy;
		else if(finy==41)
			return -1;
	}


	int optimum_plyr(int no,struct player *p)
	{
		int pl,ph,min=0,ret=0,i,team_no;
		if(team==1)
		{
			pl=1;
			ph=11;
			team_no=2;
		}
		if(team==2)
		{
			pl=12;
			ph=22;
			team_no=1;
		}

		for(i=pl;i<=ph;i++)
		{
			if(i!=no &&((p[i].x>p[no].x&&team==1)||(p[i].x<p[no].x && team==2)))
			{
				if((min<preqp(p[no].x,p[no].y,p[i].x,p[i].y)) && check(p[i].x,p[i].y,no,team_no,p) )
				{
					min=preqp(p[no].x,p[no].y,p[i].x,p[i].y);
					ret=i;
				}
			}
		}

		if(ret==0)
		{
			ret=no;
		}
		return ret;
	}









	int gl_scr_pos(int ball_player,struct player *p)
	{
		if(team==1)
		{
			xfin=86;
			yfin=in_range_y(ball_player,p);
		}
		else if(team==2)
		{
			xfin=14;
			yfin=in_range_y(ball_player,p);
		}
		if(yfin!=-1 )
		{
			return ball_player;
		}

		else if(yfin==-1)
			return 0;
	}


	int can_scr(int plr_no,struct player *p)
	{
		int no,scr,x,y,num;

		x=p[plr_no].x;
		y=p[plr_no].y;
		yfin=10;
		if(team==1)
		{
			xfin=86;
			num=2;
		}
		else
		{
			xfin=14;
			num=1;
		}
		no=max_str(x,y,num,p);

		p[plr_no].strength-=p[no].strength;

		scr=gl_scr_pos(plr_no,p);

		p[plr_no].strength+=p[no].strength;

		if(scr!=0)
			return scr;
		else
			return 0;
	}








	int case1(int ball_player,struct player * p)
	{
		int i,j,pl,ph,temp=0,flag=0,l=0,a=0,m,b=0,k,my_plr=0,ol,oh,opp_num,max=0,plyr=-1,team_no,pass,ret=0,strreq=50,x,y,strlft=0,min=50,chan=0;
		pass=max_str(x,y,team,p);
		xfin=0;
		yfin=0;

		if(team==1)
		{
			pl=1;
			ph=11;
			ol=12;
			oh=22;
			team_no=2;
		}
		else if(team==2)
		{
			pl=12;
			ph=22;
			ol=1;
			oh=11;
			team_no=1;
		}
		my_plr=max_str(p[ball_player].x,p[ball_player].y,team,p);
		strlft=p[my_plr].strength - preqp(p[my_plr].x,p[my_plr].y,p[ball_player].x,p[ball_player].y);

		if(p[ball_player].strength<strlft )
		{
			p[my_plr].x=p[ball_player].x;
			p[my_plr].y=p[ball_player].y;
			if(strlft>p[ball_player].strength)
			{
				temp=my_plr;
				my_plr=ball_player;
				ball_player=temp;
			}

		}

		accelerate(ball_player,p);

		for(i=pl;i<=ph;i++)
		{
			for(j=1;j<23;j++)
			{
				if(p[i].x==p[j].x &&p[i].y==p[j].y &&i!=j)
				{
					if(i!=ball_player && i!=1);
						change(i,p);
				}
			}
		}

		if((p[ball_player].x<40&&team==1)||(p[ball_player].x>60&&team==2))
		{
			if(p[ball_player].y<=25)
				p[0].y=9;
			else
				p[0].y=41;
			if(team==1)
				p[0].x=40;
			else
				p[0].x=60;

			return ball_player;
		}

		a=gl_scr_pos(ball_player,p);

		if(a!=0)
		{
			p[0].x=xfin;
			p[0].y=yfin;

			return ball_player;
		}

		else if(a==0)
		{
			for(i=pl;i<=ph;i++)
			{
				b=can_scr(i,p);
				if(b!=0)
				{
					break;
				}
			}
			if(i<=ph)
			{
				p[0].x=p[i].x;
				p[0].y=p[i].y;
				return ball_player;
			}
		 }
		if(b==0)
		{
			temp=in_d(ball_player,p);
			if(temp>0 && check(xfin,yfin,ball_player,team_no,p))
			{
				p[0].x=xfin;
				p[0].y=yfin;
				return ball_player;
			}
		}

		if(temp==0)
		{
			a=optimum_plyr(ball_player,p);
			p[0].x=p[a].x;
			p[0].y=p[a].y;
			if(a!=ball_player)
			{	ret=1;
				return ball_player;
			}
		}

		if(ret==0)
		{
			if(team==1)
			{
				x=60;
				if(p[ball_player].y<=25)
					y=17;
				else
					y=32;
			}
			if(team==2)
			{
				x=40;
				if(p[ball_player].y<=25)
					y=17;
				else
					y=32;
			}
			k=preqpb(x,y,p[ball_player].x,p[ball_player].y);
			if(k<p[ball_player].strength)
			{
				pass=max_str(x,y,team,p);
				temp=preqpb(x,y,p[pass].x,p[pass].y);
				if(temp<30)
				{	p[pass].x=x;
					p[pass].y=y;
				}
				p[0].x=x;
				p[0].y=y;

				return ball_player;
			}



			for(i=ol;i<=oh;i++)
			{
				if(((p[i].x==(p[ball_player].x+1) && team==1)||(p[i].x==(p[ball_player].x-1) && team==2))&&p[i].y==p[ball_player].y)
				{
					flag=100;
					break;
				}
			}


			if(flag==100)
			{
				for(j=pl;j<=ph;j++)
				{
					if(p[j].x<=p[ball_player].x && j!=ball_player)
					{
						k=preqpb(p[ball_player].x,p[j].y,p[ball_player].x,p[ball_player].y);
						m=preqp(p[ball_player].x,p[j].y,p[j].x,p[j].y);
						if((k+m)<min&&p[j].y!=p[ball_player].y)
						{
							min=(k+m);
							l=j;
						}
					}
				}
				p[l].x=p[ball_player].x;
				p[l].y=32;
				p[0].x=p[l].x;
				p[0].y=p[l].y;
				flag=0;
				return ball_player;
			}

			else if((p[pass].strength-preqp(p[0].x,p[0].y,p[pass].x,p[pass].y))>p[ball_player].strength-2)
			{
				p[pass].x=p[ball_player].x;
				p[pass].y=p[ball_player].y;

				if(team==1)
					p[0].x+=p[pass].strength/2;
				else if(team==2)
					p[0].x-=p[pass].strength/2;
				return pass;
			}


			else
			{
				return -1;
			}
		}

	}



	int case2(int ball_player,struct player *p)
	{
		int i,a,strreq,pl,ph;
		i=ball_player;
		if(team==1)
		{
			pl=1;
			ph=11;
		}
		else if(team==2)
		{
			pl=12;
			ph=22;
		}

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

		return -1;
	}



	int case3(struct player * p)
	{
		int plr_no=0,i,a=-1,strreq,large=0,pl,ph;

  //this for loop searches for a player of my team such that after reaching at the position of the ball it is having the maximum
  //strength left to hit the ball



		if(team==1)
		{
			pl=1;
			ph=11;
		}
		else if(team==2)
		{
			pl=12;
			ph=22;
		}





		for(i=pl;i<=ph;i++)
		{
			strreq=preqp(p[i].x,p[i].y,p[0].x,p[0].y);

			if(  (p[i].strength - strreq )  >  large)  //large is having max strength of the player after reaching there
			{                                        //team is having the no. of the desired player
				plr_no=i;
				large=p[i].strength-strreq;
			}             //end of if

		}      //end of for loop


   //if such player is found having maximum and non-zero strength left after reaching the position of the ball then that player
   //is moved to ball's position and case1 function is called as the situation is similar to that when my player is having the
   //possession of the ball
		if(plr_no!=0)
		{
			p[plr_no].x=p[0].x;
			p[plr_no].y=p[0].y;

			a=case1(plr_no,p);
			return a;
		}

    //if no player is found having non-zero strength after reaching the ball's position the move is skipped
		return -1;


	} // end of case3()

	void position(int pl,struct player *p)
	{
		int plr;
		plr=max_str((p[0].x-2),p[0].y,team,p);

		if(plr!=pl)
		{
			p[plr].x=p[0].x-1;
			p[plr].y=p[0].y;
		}
		if(pl!=1)
		{
			p[1].y=p[0].y;
		}
	}

	int player( struct player *p)
	{
		int i,j,ball_player,a;

		for(i=1;i<23;i++)
		{
			if( p[0].x==p[i].x && p[0].y==p[i].y )
			{
				if(p[i].strength!=0)
				{
					ball_player=i;
					break;
				}
			}
		 }
		if(i==23)
		{
			a=case3(p);
			position(a,p);
			return a;
		}

		else if((i<=11&&team==1)||(i>11&&team==2))
		{
			a=case1(i,p);
			position(a,p);
			return a;
		}
		else
		{
			a=case2(i,p);
			position(a,p);
			return a;
		}
	}
};



