#include<iostream.h>
#include<math.h>
#include"API.h"
void move(int &xmovefinal,int &ymovefinal)
{
	arenahistory a;
	input in=getparameters();
	a.arenasituation(1);
	int i,j,xdiffprev=0,ydiffprev=0,stepcode=0;
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			if(a.arena[i][j]=='P'||a.arena[i][j]=='*'||a.arena[i][j]=='#')
			goto out1;
		}
	}
	out1:
	xdiffprev=i;
	ydiffprev=j;
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			if(in.arena[i][j]=='P'||in.arena[i][j]=='*'||in.arena[i][j]=='#')
			goto out2;
		}
	}
	out2:
	xdiffprev=i-xdiffprev;
	ydiffprev=j-ydiffprev;
	if(xdiffprev==0||ydiffprev==0)
	{
		stepcode=0;
	}
	if(xdiffprev==1||ydiffprev==1)
	{
		stepcode=1;
	}
	if(xdiffprev==1||ydiffprev==0)
	{
		stepcode=2;
	}
	if(xdiffprev==1||ydiffprev==-1)
	{
		stepcode=3;
	}
	if(xdiffprev==0||ydiffprev==-1)
	{
		stepcode=4;
	}
	if(xdiffprev==-1||ydiffprev==-1)
	{
		stepcode=5;
	}
	if(xdiffprev==-1||ydiffprev==0)
	{
		stepcode=6;
	}
	if(xdiffprev==-1||ydiffprev==1)
	{
		stepcode=7;
	}
	if(xdiffprev==0||ydiffprev==1)
	{
		stepcode=8;
	}
	switch(stepcode)
	{
		case 0:
		xmovefinal=i+1;
		ymovefinal=j+1;
		if(in.arena[xmovefinal][ymovefinal]=='E'||in.arena[xmovefinal][ymovefinal]=='S'||in.arena[xmovefinal][ymovefinal]=='T')
		{
			goto out3;
		}
		case 1:
		xmovefinal=i+1;
		ymovefinal=j;
		if(in.arena[xmovefinal][ymovefinal]=='E'||in.arena[xmovefinal][ymovefinal]=='S'||in.arena[xmovefinal][ymovefinal]=='T')
		{
			goto out3;
		}
		case 2:
		xmovefinal=i+1;
		ymovefinal=j-1;
		if(in.arena[xmovefinal][ymovefinal]=='E'||in.arena[xmovefinal][ymovefinal]=='S'||in.arena[xmovefinal][ymovefinal]=='T')
		{
			goto out3;
		}
		case 3:
		xmovefinal=i;
		ymovefinal=j-1;
		if(in.arena[xmovefinal][ymovefinal]=='E'||in.arena[xmovefinal][ymovefinal]=='S'||in.arena[xmovefinal][ymovefinal]=='T')
		{
			goto out3;
		}
		case 4:
		xmovefinal=i-1;
		ymovefinal=j-1;
		if(in.arena[xmovefinal][ymovefinal]=='E'||in.arena[xmovefinal][ymovefinal]=='S'||in.arena[xmovefinal][ymovefinal]=='T')
		{
			goto out3;
		}
		case 5:
		xmovefinal=i-1;
		ymovefinal=j;
		if(in.arena[xmovefinal][ymovefinal]=='E'||in.arena[xmovefinal][ymovefinal]=='S'||in.arena[xmovefinal][ymovefinal]=='T')
		{
			goto out3;
		}
		case 6:
		xmovefinal=i-1;
		ymovefinal=j+1;
		if(in.arena[xmovefinal][ymovefinal]=='E'||in.arena[xmovefinal][ymovefinal]=='S'||in.arena[xmovefinal][ymovefinal]=='T')
		{
			goto out3;
		}
		case 7:
		xmovefinal=i;
		ymovefinal=j+1;
		if(in.arena[xmovefinal][ymovefinal]=='E'||in.arena[xmovefinal][ymovefinal]=='S'||in.arena[xmovefinal][ymovefinal]=='T')
		{
			goto out3;
		}
		case 8:
		xmovefinal=i+1;
		ymovefinal=j+1;
		if(in.arena[xmovefinal][ymovefinal]=='E'||in.arena[xmovefinal][ymovefinal]=='S'||in.arena[xmovefinal][ymovefinal]=='T')
		{
			goto out3;
		}
	}
	out3:
}
void main()
{
cout<<"$$$$$$$";
input in=getparameters();
reply rep;
status s;
spellhistory sh;
int finalx,finaly,defspellflag=0,defspellcode=0,offspellcode=0;
for(int k=0;k<15;k++)
{
	for(int j=0;j<15;j++)
	{
		if(in.arena[k][j]=='P'||in.arena[k][j]=='*'||in.arena[k][j]=='#')
		{
			rep.xmovefinal=k;
			rep.ymovefinal=j;
		}
	}
}
if((s.agilitystatusplayer()==0)&&(in.arena[rep.xmovefinal][rep.ymovefinal]!='*'))
{


	if(in.spellcasted==1||in.spellcasted==2)
	{
		if(sh.lastspellhitplayer()==1||sh.lastspellhitplayer()==2)
		{
			if(s.spellpowerstatusplayer()==0)
			{
				defspellflag=1;
			}
			else
			{
				move(rep.xmovefinal,rep.ymovefinal);
			}

		}

	}


	if(in.spellcasted==3||in.spellcasted==4)
	{
		if(s.agilityreductionstatusplayer()==0)
		{
			if(sh.lastspellhitplayer()==0||sh.lastspellhitplayer()==1||sh.lastspellhitplayer()==2)
			{
				move(rep.xmovefinal,rep.ymovefinal);
			}
		}
		if(s.agilityreductionstatusplayer()>0)
		{
			if(sh.lastspellhitplayer()==0||sh.lastspellhitplayer()==1||sh.lastspellhitplayer()==2)
			{
				if(s.spellpowerstatusplayer()==0)
				{
					defspellflag=1;
				}
				else
				{
					move(rep.xmovefinal,rep.ymovefinal);
				}
			}
		}
	}


	if(in.spellcasted==6)
	{
		if(sh.lastspellhitplayer()==0||sh.lastspellhitplayer()==1||sh.lastspellhitplayer()==2)
		{
			move(rep.xmovefinal,rep.ymovefinal);
		}
	}


	if(in.spellcasted==5||in.spellcasted==7||in.spellcasted==8||in.spellcasted==9)
	{       for(int y=0;y<2;y++)
		{
			move(rep.xmovefinal,rep.ymovefinal);
		}
	}
}


if(s.agilitystatusplayer()>0)
{
	if((in.spellcasted>=1)&&(in.spellcasted<=5))
	{
		defspellcode=in.spellcasted;
	}
}


if(defspellflag==1)
{
	defspellcode=in.spellcasted;
}

rep.defspellused=defspellcode;















if((in.myagility>3300)||(in.myspellpower>4000))
{
	if(sh.offspellplayer(1)==0)
	{
		offspellcode=1;
	}
	else
	{
		offspellcode=0;
	}
}
if((in.myagility<=3300)||(in.myspellpower<=4000))
{
	if(s.agilitystatusopp()>0)
	{
		if(sh.lastspellhitopp()!=7&&s.spellpowerstatusopp()==0)
		{
			offspellcode=7;
		}
		if(sh.offspellplayer(1)!=9)
		{
			offspellcode=9;
		}
		if(sh.offspellplayer(1)==9)
		{
			offspellcode=5;
		}
	}

	if(in.myhealth<800&&in.opphealth>400)
	{
		offspellcode=10;
	}
	if(sh.offspellplayer(1)==9||sh.offspellplayer(1)==1)
	{
		offspellcode=4;
	}
	if(sh.offspellplayer(1)==4)
	{
		offspellcode=3;
	}
	if(sh.offspellplayer(1)==3)
	{
		offspellcode=9;
	}
}
rep.offspellused=offspellcode;
for(int i=0;i<15;i++)
{
	for(int j=0;j<15;j++)
	{
		if(in.arena[i][j]=='O'||in.arena[i][j]=='@'||in.arena[i][j]=='$')
		{
			rep.xspellfinal=i;
			rep.yspellfinal=j;
		}
	}
}
saveparameters(rep);
}