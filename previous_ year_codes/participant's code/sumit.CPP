#include"API.h"
int getmindist(int curx,int cury,int finalx,int finaly)
{
	int diffx=0, diffy=0;
	diffx=finalx-curx;
	diffy=finaly-cury;
	if(diffx<0)
	{
		diffx=(-1)*diffx;
	}
	if(diffy<0)
	{
		diffy=(-1)*diffy;
	}
	if(diffx>diffy)
	{
	return diffx;
	}
	if(diffy>=diffx)
	{
	return diffy;
	}
	
}
void movemindist(int n,int curx,int cury,int finalx,int finaly,int &xmovefinal,int &ymovefinal)
{
	int stepcode[8],stepcode2[8],i=0,diststepcode=10000,dist,k=0;
	int movefinalx=xmovefinal,movefinaly=ymovefinal,spellreport=0;
	input in=getparameters();




	spellreport=0;
	for(k=1;k<=n;k++)
	{
		if(!(in.arena[curx+k][cury]=='E'||in.arena[curx+k][cury]=='S'||in.arena[curx+k][cury]=='T'))
		{
			spellreport=1;
		 }
	}
	if(spellreport==0)
	{	
		stepcode[i]=2;
		++i;
	}
	
	spellreport=0;
	for(k=1;k<=n;k++)
	{
		if(!(in.arena[curx+k][cury-k]=='E'||in.arena[curx+k][cury-k]=='S'||in.arena[curx+k][cury-k]=='T'))
		{
			spellreport=1;
		 }
	}
	if(spellreport==0)
	{	
		stepcode[i]=3;
		++i;
	}
	
	spellreport=0;
	for(k=1;k<=n;k++)
	{
		if(!(in.arena[curx][cury-k]=='E'||in.arena[curx][cury-k]=='S'||in.arena[curx][cury-k]=='T'))
		{
			spellreport=1;
		 }
	}
	if(spellreport==0)
	{	
		stepcode[i]=4;
		++i;
	}
	
	spellreport=0;
	for(k=1;k<=n;k++)
	{
		if(!(in.arena[curx-k][cury-k]=='E'||in.arena[curx-k][cury-k]=='S'||in.arena[curx-k][cury-k]=='T'))
		{
			spellreport=1;
		 }
	}
	if(spellreport==0)
	{	
		stepcode[i]=5;
		++i;
	}
	
	spellreport=0;
	for(k=1;k<=n;k++)
	{
		if(!(in.arena[curx-k][cury]=='E'||in.arena[curx-k][cury]=='S'||in.arena[curx-k][cury]=='T'))
		{
			spellreport=1;
		 }
	}
	if(spellreport==0)
	{	
		stepcode[i]=6;
		++i;
	}
	
	spellreport=0;
	for(k=1;k<=n;k++)
	{
		if(!(in.arena[curx-k][cury+k]=='E'||in.arena[curx-k][cury+k]=='S'||in.arena[curx-k][cury+k]=='T'))
		{
			spellreport=1;
		 }
	}
	if(spellreport==0)
	{	
		stepcode[i]=7;
		++i;
	}
	
	spellreport=0;
	for(k=1;k<=n;k++)
	{
		if(!(in.arena[curx][cury+k]=='E'||in.arena[curx][cury+k]=='S'||in.arena[curx][cury+k]=='T'))
		{
			spellreport=1;
		 }
	}
	if(spellreport==0)
	{	
		stepcode[i]=8;
		++i;
	}
	
	spellreport=0;
	for(k=1;k<=n;k++)
	{
		if(!(in.arena[curx+k][cury+k]=='E'||in.arena[curx+k][cury+k]=='S'||in.arena[curx+k][cury+k]=='T'))
		{
			spellreport=1;
		 }
	}
	if(spellreport==0)
	{	
		stepcode[i]=1;
		++i;
	}
	
	if(i<8)
	{
	stepcode[i]=0;
	}





	i=0;
	for(int y=0;stepcode[y]!=0;y++)
	{
		switch(stepcode[y])
		{
			case 2:
			movefinalx=curx+n;
			movefinaly=cury;
			break;
			case 3:
			movefinalx=curx+n;
			movefinaly=cury-n;
			break;
			case 4:
			movefinalx=curx;
			movefinaly=cury-n;
			break;
			case 5:
			movefinalx=curx-n;
			movefinaly=cury-n;
			break;
			case 6:
			movefinalx=curx-n;
			movefinaly=cury;
			break;
			case 7:
			movefinalx=curx-n;
			movefinaly=cury+n;
			break;
			case 8:
			movefinalx=curx;
			movefinaly=cury+n;
			break;
			case 1:
			movefinalx=curx+n;
			movefinaly=cury+n;
			break;
		}
		dist=getmindist(movefinalx,movefinaly,finalx,finaly);
		if(dist<diststepcode)
		{
			i=0;
			diststepcode=dist;
			stepcode2[i]=stepcode[y];
		}
		if(dist==diststepcode)
		{
			++i;
			stepcode2[i]=stepcode[y];
		}
	}
	switch(stepcode2[0])
	{
		case 2:
		xmovefinal=curx+n;
		ymovefinal=cury;
		break;
		case 3:
		xmovefinal=curx+n;
		ymovefinal=cury-n;
		break;
		case 4:
		xmovefinal=curx;
		ymovefinal=cury-n;
		break;
		case 5:
		xmovefinal=curx-n;
		ymovefinal=cury-n;
		break;
		case 6:
		xmovefinal=curx-n;
		ymovefinal=cury;
		break;
		case 7:
		xmovefinal=curx-n;
		ymovefinal=cury+n;
		break;
		case 8:
		xmovefinal=curx;
		ymovefinal=cury+n;
		break;
		case 1:
		xmovefinal=curx+n;
		ymovefinal=cury+n;
		break;
		default:
		xmovefinal=curx;
		ymovefinal=cury;
	}
}
	
		






void move(int n,int &xmovefinal,int &ymovefinal)
{
	arenahistory a;
	input in=getparameters();
	int i,j,l=1,k=0,xdiffprev=0,ydiffprev=0,stepcode=0,nooftemps=0,noofsf=0,tempx[2],tempy[2],sfx[2],sfy[2];
	int curx,cury,prevx,prevy,tempmindist[2],sfmindist[2];
	tempmindist[0]=0;
	tempmindist[1]=0;
	sfmindist[0]=0;
	sfmindist[1]=0;
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			if(in.arena[i][j]=='P'||in.arena[i][j]=='*'||in.arena[i][j]=='#')
			{
			curx=i;
			cury=j;
			}
		}
	}






	k=0;
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			if(in.arena[i][j]=='T')
			{
			tempx[k]=i;
			tempy[k]=j;
			tempmindist[k]=getmindist(curx,cury,i,j);
			nooftemps++;
			}
		}
	}
	if(tempmindist[1]==0)
	{
	movemindist(n,curx,cury,tempx[0],tempy[0],xmovefinal,ymovefinal);
	}
	if(tempmindist[0]<tempmindist[1])
	{
	movemindist(n,curx,cury,tempx[0],tempy[0],xmovefinal,ymovefinal);
	}
	else
	{
	movemindist(n,curx,cury,tempx[1],tempy[1],xmovefinal,ymovefinal);
	}		










	
	if(nooftemps==0)
	{
		k=0;
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				if(in.arena[i][j]=='S')
				{
				sfx[k]=i;
				sfy[k]=j;
				sfmindist[k]=getmindist(curx,cury,i,j);
				noofsf++;
				}
			}
		}
		if(sfmindist[1]==0)
		{
		movemindist(n,curx,cury,sfx[0],sfy[0],xmovefinal,ymovefinal);
		}
		if(sfmindist[0]<sfmindist[1])
		{
		movemindist(n,curx,cury,sfx[0],sfy[0],xmovefinal,ymovefinal);
		}
		else
		{
		movemindist(n,curx,cury,sfx[1],sfy[1],xmovefinal,ymovefinal);
		}		
	}























	if(nooftemps==0&&noofsf==0)
	{
		repeat:
		a.arenasituation(l);
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				if(a.arena[i][j]=='P'||a.arena[i][j]=='*'||a.arena[i][j]=='#')
				{
				prevx=i;
				prevy=j;
				}
			}
		}
		xdiffprev=curx-prevx;
		ydiffprev=cury-prevy;
		if(xdiffprev==0&&ydiffprev==0)
		{
			++l;
			goto repeat;
		}
	
	
	
	
		if((xdiffprev==1&&ydiffprev==1)||(xdiffprev==2&&ydiffprev==2))
		{
			stepcode=1;
		}
		if((xdiffprev==1&&ydiffprev==0)||(xdiffprev==2&&ydiffprev==0))
		{
			stepcode=2;
		}
		if((xdiffprev==1&&ydiffprev==-1)||(xdiffprev==2&&ydiffprev==-2))
		{
			stepcode=3;
		}
		if((xdiffprev==0&&ydiffprev==-1)||(xdiffprev==0&&ydiffprev==-2))
		{
			stepcode=4;
		}
		if((xdiffprev==-1&&ydiffprev==-1)||(xdiffprev==-2&&ydiffprev==-2))
		{
			stepcode=5;
		}
		if((xdiffprev==-1&&ydiffprev==0)||(xdiffprev==-2&&ydiffprev==0))
		{
			stepcode=6;
		}
		if((xdiffprev==-1&&ydiffprev==1)||(xdiffprev==-2&&ydiffprev==2))
		{
			stepcode=7;
		}
		if((xdiffprev==0&&ydiffprev==1)||(xdiffprev==0&&ydiffprev==2))
		{
			stepcode=8;
		}
		switch(stepcode)
		{
			case 1:
			movemindist(n,i,j,i+n,j,xmovefinal,ymovefinal);
			if((xmovefinal==i+n)&&(ymovefinal==j))
			{
				goto outer;
			}
			case 2:
			movemindist(n,i,j,i+n,j-n,xmovefinal,ymovefinal);
			if((xmovefinal==i+n)&&(ymovefinal==j-n))
			{
				goto outer;
			}
			case 3:
			movemindist(n,i,j,i,j-n,xmovefinal,ymovefinal);
			if((xmovefinal==i)&&(ymovefinal==j-n))
			{
				goto outer;
			}
			case 4:
			movemindist(n,i,j,i-n,j-n,xmovefinal,ymovefinal);
			if((xmovefinal==i-n)&&(ymovefinal==j-n))
			{
				goto outer;
			}
			case 5:
			movemindist(n,i,j,i-n,j,xmovefinal,ymovefinal);
			if((xmovefinal==i-n)&&(ymovefinal==j))
			{
				goto outer;
			}
			case 6:
			movemindist(n,i,j,i-n,j+n,xmovefinal,ymovefinal);
			if((xmovefinal==i-n)&&(ymovefinal==j+n))
			{
				goto outer;
			}
			case 7:
			movemindist(n,i,j,i,j+n,xmovefinal,ymovefinal);
			if((xmovefinal==i)&&(ymovefinal==j+n))
			{
				goto outer;
			}
			case 8:
			movemindist(n,i,j,i+n,j+n,xmovefinal,ymovefinal);
			if((xmovefinal==i+n)&&(ymovefinal==j+n))
			{
				goto outer;
			}
			default:
			xmovefinal=i;
			ymovefinal=j;
		}
		outer:
	}
}













void main()
{
input in=getparameters();
spells spellcasted(in.spellcasted);
reply rep;
status s;
spellhistory sh;
int finalx,finaly,defspellflag=0,defspellcode=0,offspellcode=0;
int playercurx,playercury,oppcurx,oppcury;
for(int k=0;k<15;k++)
{
	for(int j=0;j<15;j++)
	{
		if(in.arena[k][j]=='P'||in.arena[k][j]=='*'||in.arena[k][j]=='#')
		{
			playercurx=k;
			playercury=j;
			rep.xmovefinal=k;
			rep.ymovefinal=j;
		}
		if(in.arena[k][j]=='O'||in.arena[k][j]=='@'||in.arena[k][j]=='$')
		{
		    oppcurx=k;
		    oppcury=j;
        }
	}
}
if((s.agilitystatusplayer()==0)&&(in.arena[rep.xmovefinal][rep.ymovefinal]!='*'))
{


	if(in.spellcasted==1||in.spellcasted==2)
	{
		if((s.spellpowerstatusplayer()==0)&&((in.myspellpower-spellcasted.spellpower())>0))
		{
			defspellflag=1;
		}
		else
		{
			move(1,rep.xmovefinal,rep.ymovefinal);
		}
	}


	if(in.spellcasted==3||in.spellcasted==4||in.spellcasted==5)
	{
		if(s.agilityreductionstatusplayer()==0)
		{
			move(1,rep.xmovefinal,rep.ymovefinal);
		}
		if(s.agilityreductionstatusplayer()>0)
		{
			if((s.spellpowerstatusplayer()==0)&&((in.myspellpower-spellcasted.spellpower())>0))

			{
				defspellflag=1;
			}
			else
			{
				move(1,rep.xmovefinal,rep.ymovefinal);
			}
		}
	}


	if(in.spellcasted==6||in.spellcasted==8||in.spellcasted==11)
	{
	         move(2,rep.xmovefinal,rep.ymovefinal);
	         if((rep.xmovefinal==playercurx)&&(rep.xmovefinal==playercury)&&(in.spellcasted==11)&&((in.myspellpower-spellcasted.spellpower())>0))
                          {
		defspellflag=1;
	        }
	        if((rep.xmovefinal==playercurx)&&(rep.xmovefinal==playercury)&&(in.spellcasted!=11))
	       {
		move(1,rep.xmovefinal,rep.ymovefinal);
	       }
		
		
	}

	if((in.spellcasted==7)||(in.spellcasted==17))
	{
		move(3,rep.xmovefinal,rep.ymovefinal);
		if((rep.xmovefinal==playercurx)&&(rep.xmovefinal==playercury)&&(in.spellcasted!=17))
		{
			move(2,rep.xmovefinal,rep.ymovefinal);
		}
		if((rep.xmovefinal==playercurx)&&(rep.xmovefinal==playercury)&&(in.spellcasted!=17))
		{
			move(1,rep.xmovefinal,rep.ymovefinal);
		}
		if((rep.xmovefinal==playercurx)&&(rep.xmovefinal==playercury)&&(in.spellcasted==17))
		{
			move(2,rep.xmovefinal,rep.ymovefinal);
		}
		if((rep.xmovefinal==playercurx)&&(rep.xmovefinal==playercury)&&(in.spellcasted==17))
		{
			if((s.spellpowerstatusplayer()==0)&&((in.myspellpower-250)>0))
			{
				defspellcode=16;
			}
			else
			{
				move(1,rep.xmovefinal,rep.ymovefinal);
			}
		}
	}
	
	if((in.spellcasted==9)||(in.spellcasted==12)||(in.spellcasted==13)||(in.spellcasted==14)||(in.spellcasted==15))
	{
		if((s.spellpowerstatusplayer()==0)&&((in.myspellpower-250)>0))
		{
			defspellcode=16;
		}
		else
		{
			move(3,rep.xmovefinal,rep.ymovefinal);
			if((rep.xmovefinal==playercurx)&&(rep.xmovefinal==playercury))
			{
				move(2,rep.xmovefinal,rep.ymovefinal);
			}
			if((rep.xmovefinal==playercurx)&&(rep.xmovefinal==playercury))
			{
				move(1,rep.xmovefinal,rep.ymovefinal);
			}
		}				
	}		
		
}



if(defspellcode==16)
{
	goto assign;
}



if((s.agilitystatusplayer()>0)&&(s.spellpowerstatusplayer()==0))
{
	if((((in.spellcasted>=1)&&(in.spellcasted<=5))||(in.spellcasted==11)||(in.spellcasted==17))&&((in.myspellpower-spellcasted.spellpower())>0))
	{
		defspellcode=in.spellcasted;
	}
	if((in.spellcasted==7)||(in.spellcasted==9)||(in.spellcasted==12)||(in.spellcasted==13)||(in.spellcasted==14)||(in.spellcasted==15))
	{
		defspellcode=16;
	}
}


if(defspellflag==1)
{
	defspellcode=in.spellcasted;
}


assign:
rep.defspellused=defspellcode;








spells defspell(rep.defspellused);
int nooftemp=0,noofsf=0;
for(int x1=0;x1<15;x1++)
{
	for(int y1=0;y1<15;y1++)
	{
		if(in.arena[x1][y1]=='T')
		{
			nooftemp++;
		}
		if(in.arena[x1][y1]=='S')
		{
			noofsf++;
		}
	}
}

int sfflag=0,x3,y3;


if(nooftemp==0)
{
    if((in.myhealth<1000)&&(in.opphealth>1000)&&(in.myspellpower>(defspell.spellhealth()-250)))
    {
	offspellcode=10;
	goto end;
    }
	if(in.myspellpower>1500)
	{
		offspellcode=1;
	}
	if(in.myspellpower<=1500)
	{
	    if((s.agilitystatusopp()<=1)&&(in.myspellpower>(defspell.spellpower()-150)))
	    {
		  offspellcode=9;
		  goto end;
	}
	if((s.agilitystatusopp()>0)&&(s.spellpowerstatusopp()>0)&&(in.myspellpower>(defspell.spellpower()-750)))
	{
		offspellcode=13;
		goto end;
	}
	if((s.agilitystatusopp()>0)&&(s.spellpowerstatusopp()>0)&&(in.myspellpower>(defspell.spellpower()-400)))
	{
		offspellcode=14;
		goto end;
	}
	if((s.agilitystatusopp()>0)&&(s.spellpowerstatusopp()>0)&&(in.myspellpower>(defspell.spellpower()-150)))
	{
		offspellcode=11;
		goto end;
	}
	if((s.agilitystatusopp()>0)&&(in.myspellpower>(defspell.spellpower()-125)))
	{
		offspellcode=8;
		goto end;
	}
      }
}
end:
if(in.arena[oppcurx][oppcury]=='@')
{
    offspellcode=1;
    rep.xmovefinal=oppcurx;
    rep.ymovefinal=oppcury;
    goto final;
}
for(x3=-1;x3<=1;x3++)
    {
    for(y3=-1;y3<=1;y3++)
	{
		if(in.arena[oppcurx+x3][oppcury+y3]=='S')
		{
				sfflag=1;
				rep.xspellfinal=oppcurx+x3;
				rep.yspellfinal=oppcury+y3;
		}
	}
    }
if(sfflag==1)
{
    offspellcode=1;
    goto final;
}
rep.offspellused=offspellcode;
rep.xspellfinal=oppcurx;
rep.yspellfinal=oppcury;
final:


saveparameters(rep);
}
