// preferred compiler is turboc

#include"api.h"

void move();
reply rep;
int main()
{
	spellhistory sh;
	input in = getparameters();
	int myhealth,myagility,myspellpower;
	int opphealth,oppagility,oppspellpower;
	myhealth=in.myhealth;
	myagility=in.myagility;
	myspellpower=in.myspellpower;
	int spellcasted=in.spellcasted;
	opphealth=in.opphealth;
	oppagility=in.oppagility;
	oppspellpower=in.oppspellpower;
	int i,j;
	int moveflag=0;
	arenahistory ah;



	if((spellcasted>=1)&&(spellcasted<=5))
	{
		if(myagility<=1500)
		{
			rep.defspellused=spellcasted;  moveflag=1;
		}
		else
		{
			move();
		}
	}
	else if((spellcasted==10)||(spellcasted==16))
	{
		rep.defspellused=0;            moveflag=1;
	}
	else if((spellcasted==13)||(spellcasted==14)||(spellcasted==17))
	{
		if(myspellpower>=1200)
		{
			rep.defspellused=spellcasted;   moveflag=1;
		}
		else
		{
			move();
			move();
		}
	}
	else if(spellcasted==8||spellcasted==12||spellcasted==7||spellcasted==15)
	{
		move();
		move();
	}
	else if(spellcasted==6||spellcasted==9)
	{
		move();
	}
	else if(spellcasted==11)
	{
		move();
		move();
	}


	if(moveflag==1)
	{
		for( i=0; i<=14; i++)
		{
			for( j=0;j<=14;j++)
			{
				if(in.arena[i][j]=='P'||in.arena[i][j]=='*')
				{
					rep.xmovefinal=i;
					rep.ymovefinal=j;
				}
			}
		}


	}




	int attackflag=0;
	if(myhealth<500||myspellpower<500)
	{
		rep.offspellused=10;
	}





	for(i=0;i<=14;i++)
	{
		for(j=0;j<=14;j++)
		{
			if(in.arena[i][j]=='@')
				goto out1;
		}
	}
	out1:
	if((i==6)&&(j==14))
	{
		rep.offspellused=1;
		rep.xspellfinal=6;
		rep.yspellfinal=14;
		attackflag=1;
	}
	else if((i==8)&&(j==0))
	{
		rep.offspellused=1;
		rep.xspellfinal=8;
		rep.yspellfinal=0;
		attackflag=1;
	}

	else if((i==4)&&(j==4))
	{
		rep.offspellused=1;
		rep.xspellfinal=4;
		rep.yspellfinal=4;
		attackflag=1;
	}


	else if((i==10)&&(j==10))
	{
		rep.offspellused=1;
		rep.xspellfinal=10;
		rep.yspellfinal=10;
		attackflag=1;
	}

	else if((i==1)&&(j==13))
	{
		rep.offspellused=8;
		rep.xspellfinal=0;
		rep.yspellfinal=14;
		attackflag=1;
	}
	else if((i==13)&&(j==1))
	{
		rep.offspellused=8;
		rep.xspellfinal=14;
		rep.yspellfinal=0;
		attackflag=1;
	}


	else if(sh.lastspellhitopp()==7)
	{
		rep.offspellused=13;
	}

	else if(oppagility==0)
	{
		rep.offspellused=7;
	}




	else if(sh.offspellplayer(1)==8)



	{
		rep.offspellused=3;

	}
	else if(sh.offspellplayer(1)==3)
	{
		rep.offspellused=5;

	}
	else if(sh.offspellplayer(1)==5)
	{
		rep.offspellused=8;

	}
	else
	{
		rep.offspellused=8;
	}


	int t,q,r,m,p,d1,d2,d3,d4,c=0,xopp_curr_pos,yopp_curr_pos;
	int x[2],y[2];

	for(i=0;i<=14;i++)
	{
		for(j=0;j<=14;j++)
		{
			if((in.arena[i][j]=='O')||(in.arena[i][j]=='@')||(in.arena[i][j]=='$'))
			{
				xopp_curr_pos=i;
				yopp_curr_pos=j;
			}
		}
	}

/*	ah.arenasituation(1);
	for(i=0;i<=14;i++)
	{
		for(j=0;j<=14;j++)
		{
			if((ah.arena[i][j]=='O')||(ah.arena[i][j]=='$')||(ah.arena[i][j]=='@'))
			{
				d1=xopp_curr_pos-i;
				d2=yopp_curr_pos-j;
			}
		}
	}


	if(!attackflag)
	{


	for(i=9;i>0;i--)
	{
		q=0;r=0;
		for(j=0;j<2;j++)
		{
			t=i;
			ah.arenasituation(t);
			for(m=0;m<=14;m++)
			{
				for(p=0;p<=14;p++)
				{
					if((ah.arena[m][p]=='O')||(ah.arena[m][p]=='$'))
					{
						x[q]=m;y[r]=p;
						q++;r++;
					}

				}

			}
			t--;
		}
		if(((x[1]-x[0])==d1)&&((y[1]-y[0])==d2))
		{
			ah.arenasituation(t);
			for(m=0;m<=14;m++)
			{
				for(p=0;p<=14;p++)
				{
					if((ah.arena[m][p]=='O')||(ah.arena[m][p]=='$')||(ah.arena[m][p]=='@'))
					{
						d3=m-x[1];
						d4=p-y[1];
						rep.xspellfinal=xopp_curr_pos+d3;
						rep.yspellfinal=yopp_curr_pos+d4;
						c++;

					}
				}
			}
		}
	}



	if(c==0)  */

		rep.xspellfinal=xopp_curr_pos;
		rep.yspellfinal=yopp_curr_pos;


	saveparameters(rep);
return 0;
}



void move(void)
{
	input in = getparameters();
	int i,j,t,p1,p2,d1,d2,xmy_curr_pos,ymy_curr_pos;
	arenahistory ah;
	int x[2],y[2];
	int a[9]={1,1,-1,-1,1,0,0,-1,1};
	int b[9]={0,-1,0,1,1,-1,1,-1,1};


	for(i=0;i<=14;i++)
	{
		for(j=0;j<=14;j++)
		{
			if((in.arena[i][j]=='P')||(in.arena[i][j]=='*'))
			{
				xmy_curr_pos=i;
				ymy_curr_pos=j;

			}
		}
	}


	ah.arenasituation(1);
	for(i=0;i<=14;i++)
	{
		for(j=0;j<=14;j++)
		{
			if((ah.arena[i][j]=='P')||(ah.arena[i][j]=='*'))
			{
				d1=xmy_curr_pos-i;
				d2=ymy_curr_pos-j;
			}

		}
	}



	while(1)
	{

		if((d1==0)&&(d2==0))
		{
			p1=xmy_curr_pos+a[0];
			p2=ymy_curr_pos+b[0];
	/*		if((in.arena[p1][p2]=='X')||(in.arena[p1][p2]=='B')||(in.arena[p1][p2]=='D')||(in.arena[p1][p2]=='O')||(in.arena[p1][p2]=='$')||(in.arena[p1][p2]=='@')||(p1<0)||(p1>14)||(p2<0)||(p2>14))
			{
				d1=1;
				d2=1;
			}

			else
				break; */
		}
		if(d1==1&&d2==1)
		{
			p1=xmy_curr_pos+a[1];
			p2=ymy_curr_pos+b[1];
	/*		if((in.arena[p1][p2]=='X')||(in.arena[p1][p2]=='B')||(in.arena[p1][p2]=='D')||(in.arena[p1][p2]=='O')||(in.arena[p1][p2]=='$')||(in.arena[p1][p2]=='@')||(p1<0)||(p1>14)||(p2<0)||(p2>14))
	//		if(in.arena[p1][p2]=='X'||in.arena[p1][p2]=='B'||in.arena[p1][p2]=='D'||in.arena[p1][p2]=='O'||in.arena[p1][p2]=='$'||in.arena[p1][p2]=='@'||(p1<0)||p1>14||p2<0||p2>14)
			{
				d1=0;
				d2=-1;
			}
			else
				break;   */
		}
		if(d1==0&&d2==-1)
		{
			p1=xmy_curr_pos+a[2];
			p2=ymy_curr_pos+b[2];
	/*		if((in.arena[p1][p2]=='X')||(in.arena[p1][p2]=='B')||(in.arena[p1][p2]=='D')||(in.arena[p1][p2]=='O')||(in.arena[p1][p2]=='$')||(in.arena[p1][p2]=='@')||(p1<0)||(p1>14)||(p2<0)||(p2>14))
	//		if(in.arena[p1][p2]=='X'||in.arena[p1][p2]=='B'||in.arena[p1][p2]=='D'||in.arena[p1][p2]=='O'||in.arena[p1][p2]=='$'||in.arena[p1][p2]=='@'||(p1<0)||p1>14||p2<0||p2>14)
			{
				d1=-1;
				d2=-1;
			}
			else
				break;  */
		}
		if(d1==-1&&d2==-1)
		{
			p1=xmy_curr_pos+a[3];
			p2=ymy_curr_pos+b[3];
	/*		if((in.arena[p1][p2]=='X')||(in.arena[p1][p2]=='B')||(in.arena[p1][p2]=='D')||(in.arena[p1][p2]=='O')||(in.arena[p1][p2]=='$')||(in.arena[p1][p2]=='@')||(p1<0)||(p1>14)||(p2<0)||(p2>14))
	//		if(in.arena[p1][p2]=='X'||in.arena[p1][p2]=='B'||in.arena[p1][p2]=='D'||in.arena[p1][p2]=='O'||in.arena[p1][p2]=='$'||in.arena[p1][p2]=='@'||(p1<0)||p1>14||p2<0||p2>14)
			{
				d1=-1;
				d2=0;
			}
			else
				break;  */
		}
		if(d1==-1&&d2==0)
		{
			p1=xmy_curr_pos+a[4];
			p2=ymy_curr_pos+b[4];
/*			if((in.arena[p1][p2]=='X')||(in.arena[p1][p2]=='B')||(in.arena[p1][p2]=='D')||(in.arena[p1][p2]=='O')||(in.arena[p1][p2]=='$')||(in.arena[p1][p2]=='@')||(p1<0)||(p1>14)||(p2<0)||(p2>14))
	//		if(in.arena[p1][p2]=='X'||in.arena[p1][p2]=='B'||in.arena[p1][p2]=='D'||in.arena[p1][p2]=='O'||in.arena[p1][p2]=='$'||in.arena[p1][p2]=='@'||(p1<0)||p1>14||p2<0||p2>14)
			{
				d1=0;
				d2=1;
			}
			else
				break;  */
		}
		if(d1==0&&d2==1)
		{
			p1=xmy_curr_pos+a[5];
			p2=ymy_curr_pos+b[5];
/*			if((in.arena[p1][p2]=='X')||(in.arena[p1][p2]=='B')||(in.arena[p1][p2]=='D')||(in.arena[p1][p2]=='O')||(in.arena[p1][p2]=='$')||(in.arena[p1][p2]=='@')||(p1<0)||(p1>14)||(p2<0)||(p2>14))
	//		if(in.arena[p1][p2]=='X'||in.arena[p1][p2]=='B'||in.arena[p1][p2]=='D'||in.arena[p1][p2]=='O'||in.arena[p1][p2]=='$'||in.arena[p1][p2]=='@'||(p1<0)||p1>14||p2<0||p2>14)
			{
				d1=1;
				d2=-1;
			}
			else
				break;  */
		}
		if(d1==1&&d2==-1)
		{
			p1=xmy_curr_pos+a[6];
			p2=ymy_curr_pos+b[6];
	/*		if((in.arena[p1][p2]=='X')||(in.arena[p1][p2]=='B')||(in.arena[p1][p2]=='D')||(in.arena[p1][p2]=='O')||(in.arena[p1][p2]=='$')||(in.arena[p1][p2]=='@')||(p1<0)||(p1>14)||(p2<0)||(p2>14))
//			if(in.arena[p1][p2]=='X'||in.arena[p1][p2]=='B'||in.arena[p1][p2]=='D'||in.arena[p1][p2]=='O'||in.arena[p1][p2]=='$'||in.arena[p1][p2]=='@'||(p1<0)||p1>14||p2<0||p2>14)
			{
				d1=-1;
				d2=1;
			}
			else
				break; */
		}
		if(d1==-1&&d2==1)
		{
			p1=xmy_curr_pos+a[7];
			p2=ymy_curr_pos+b[7];
/*			if((in.arena[p1][p2]=='X')||(in.arena[p1][p2]=='B')||(in.arena[p1][p2]=='D')||(in.arena[p1][p2]=='O')||(in.arena[p1][p2]=='$')||(in.arena[p1][p2]=='@')||(p1<0)||(p1>14)||(p2<0)||(p2>14))
//			if(in.arena[p1][p2]=='X'||in.arena[p1][p2]=='B'||in.arena[p1][p2]=='D'||in.arena[p1][p2]=='O'||in.arena[p1][p2]=='$'||in.arena[p1][p2]=='@'||(p1<0)||p1>14||p2<0||p2>14)
			{
				d1=1;
				d2=0;
			}
			else
				break;   */
		}
		if(d1==1&&d2==0)
		{
			p1=xmy_curr_pos+a[8];
			p2=ymy_curr_pos+b[8];
	/*		if((in.arena[p1][p2]=='X')||(in.arena[p1][p2]=='B')||(in.arena[p1][p2]=='D')||(in.arena[p1][p2]=='O')||(in.arena[p1][p2]=='$')||(in.arena[p1][p2]=='@')||(p1<0)||(p1>14)||(p2<0)||(p2>14))
//			if(in.arena[p1][p2]=='X'||in.arena[p1][p2]=='B'||in.arena[p1][p2]=='D'||in.arena[p1][p2]=='O'||in.arena[p1][p2]=='$'||in.arena[p1][p2]=='@'||(p1<0)||p1>14||p2<0||p2>14)
			{
				d1=0;
				d2=0;
			}
			else
				break;   */
		}
	}


	rep.xmovefinal=p1;
	rep.ymovefinal=p2;

}
