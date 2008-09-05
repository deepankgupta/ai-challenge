#include<API.h>

//macros for che_def_mov_s
#define MIN_SP 550
   //MINIMUM SPELL POWER REQUIRED TO CHOOSE TO SPELL
#define MIN_AGL 400
   // MINIMUM AGILITY REQUIRED TO MOVE
#define MIN_HEA 1000
//end of macros for che_def_mov_s

//macros for che_def_mov_s
enum aglei
{ high,avg,low};
enum mov_dir
{ up,down,left,right,dia_up,dia_down,no};
//end of macros for che_def_mov_s

reply rep;
int max(int *s)
{
	int maxi=0,i=0;

	while(i<6)
	{
		if(s[i]<s[maxi])
			maxi=s[i];
		i++;
	}
	return maxi;
}
input in;//current instance
spellhistory sp;//object for spell history
arenahistory ar[15];//15 objects for previous 15 turns--i(th) is i turns back
status st;//agility,spellpower
struct pos
{
	int x;
	int y;
};//structure to find single position in an arena

pos find(char ch);//this finds character ch position
pos find_h(char ch,int k);
		//this finds character ch position from (k)th back spell
void defence();    //defense
int che_def_mov_s(); //to select wether move or cast defensive spell
		     //returns-1---use movement
		     //returns-0---cast defensive spell
		     //return -1 if no cast nor spell
int s_def();    //to select spell of defence
void set();//sets arena history
//******************************************
pos findpos(enum mov_dir);  //find position in given direction to mov
			    //retrns-0 if no possible move
			    //-1 if small move possible
int pos_s=9; //-0,if no possible move
	     //-1,if less no. of possible choices
//******************************************
pos mov();       //select positon after movement
void offence();   //offensive-----attack
void main()
{

	set();
	//in.spellcasted=10;
	defence();
       //	printf("%d\n",rep.defspellused);
	//in.arena[10][12]='O';
	//printf("-%d-%d-",find('O').x,find('O').y);
	//getch();
	offence();
	#ifdef TEST

       #endif
	saveparameters(rep);
}
int che_def_mov_s()
{		     //to select wether move or cast defensive spell
		     //returns-(1)---use movement
		     //returns-(0)---cast defensive spell
		     //returns-(-1)---if no need to defence

	/*if(in.myspellpower<MIN_SP)
		return 1;
	if(in.myagility<MIN_AGL)
		return 1; MIN_HEA*/
	#ifdef TEST
		//printf("%d-%d",find('P').x,find('P').y);
		in.spellcasted=3;
		in.myhealth=2500;
		in.myagility=2500;
		in.myspellpower=200;
		in.opphealth=3000;
		in.oppagility=3000;
		in.oppspellpower=4500;
		in.arena[8][10]='P';
		in.arena[8][11]='B';
		in.arena[9][10]='D';
		in.arena[4][8]='O';
	#endif
	int k=in.spellcasted;//to save coding time
	int a=in.myhealth;
	int b=in.myspellpower;
	int c=in.myagility;
	if((k<0)||(k>17)||(k==10))
		return -1;
	if((st.agilitystatusplayer())||(in.myagility<25))
		return 0;
	if((st.spellpowerstatusplayer())||(in.myspellpower<35))
		return 1;
	pos temp;
	temp=find('*'); //player standing at safety point
	if((temp.x>-1)&&(temp.x<16)&&(temp.y>-1)&&(temp.y<16))
		return -1;

	if((k>0)&&(k<6))
	{
		if((a<MIN_HEA)&&(b<MIN_SP)&&(c<MIN_AGL))
			return 1;
		if((a<MIN_HEA)&&(b<MIN_SP)&&(c>MIN_AGL))
			return 1;
		if((a<MIN_HEA)&&(b>MIN_SP)&&(c<MIN_AGL))
			return 0;
		if((a<MIN_HEA)&&(b>MIN_SP)&&(c>MIN_AGL))
			return 0;
		if((a>MIN_HEA)&&(b<MIN_SP)&&(c<MIN_AGL))
			return 1;
		if((a>MIN_HEA)&&(b<MIN_SP)&&(c>MIN_AGL))
			return 1;
		if((a>MIN_HEA)&&(b>MIN_SP)&&(c<MIN_AGL))
			return 0;
		if((a>MIN_HEA)&&(b>MIN_SP)&&(c>MIN_AGL))
		{
			return 0;
			//if(((c-b)<500)&&(b<1500)&&(c<1500))
			  //	return 1;
			//else
			//	return 0;
		}
	  }
	  else
		if((in.spellcasted==13)&&(in.myspellpower>250))
			return 0;
		if((in.spellcasted>9)&&(in.spellcasted<18))
			if(in.myspellpower>1200)
			return 0;
			else
			return 1;
		else
			return 1;
}
pos find(char ch)   //this finds character ch position
{
	pos t={-1,-1};
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
		{
			if(in.arena[i][j]==ch)
			{
				t.x=i;
				t.y=j;
				return t;
			}
		}
	return t;
}
int s_def()    //to select spell of defence
{
	int k=in.spellcasted;
	//int a=in.myhealth;
	int b=in.myspellpower;
	//int c=in.myagility;
	if((k>-1)&&(k<6))
	{
		return k;
	}
	if((k>11)&&(k<16))
	{
		if(b>350)
		return 16;
		else
			//if(c>100);
		//*********AGILITY***********
			//else
				return 16;
	}
	else
		return 16;
}
void set()
{
	in=getparameters();
	for(int i=0;i<15;i++)
	{
		ar[i].arenasituation(i);
	}
}
pos mov()       //select positon after movement
{
	pos final;
	//enum aglei age;
	/*if(st.agilitystatusplayer())
		age=low;
	else
		if(in.myagility>2000)
			age=high;
		else
		if((in.myagility>900)&&(in.myagility<=2000))
			age=avg;
		else
		if(in.myagility<=900)
			age=low;*/
	int off_s[15];
	pos temp_h[15];
	for(int i=0;i<16;i++)
	{
		off_s[i]=sp.offspellopp(i);
		temp_h[i]=find_h('P',i);
	}

	enum mov_dir mov_h[15];//history movement at i(th)turns
	for(i=0;i<15;i++)
	{
		if((temp_h[i].y==temp_h[i+1].y)&&
		(temp_h[i].x==temp_h[i+1].x))
			mov_h[i+1]=no;
		else
		if(temp_h[i].y==temp_h[i+1].y)
		{
			if((temp_h[i].x-temp_h[i+1].x)>0)
				mov_h[i+1]=down;
			else
				mov_h[i+1]=up;
		}
		else
		if(temp_h[i].x==temp_h[i+1].x)
		{
			if((temp_h[i].y-temp_h[i+1].y)>0)
				mov_h[i+1]=left;
			else
				mov_h[i+1]=right;
		}
		else
		if(temp_h[i].x>temp_h[i+1].x)
			mov_h[i+1]=dia_down;
		else
			mov_h[i+1]=dia_up;
	}
		int s[6];//for s---6 directions
			//s[0]-----left
			//s[1]-----right
			//s[2]-----up
			//s[3]-----down
			//s[4]-----dia_up
			//s[5]-----dia_down
		for(i=0;i<6;i++)
		{
			s[0]=0;
		}

		for(i=1;i<16;i++)
		{
			if(mov_h[i]==left)
				s[0]+=(16-i);
			if(mov_h[i]==right)
				s[1]+=(16-i);
			if(mov_h[i]==up)
				s[2]+=(16-i);
			if(mov_h[i]==down)
				s[3]+=(16-i);
			if(mov_h[i]==dia_up)
				s[4]+=(16-i);
			if(mov_h[i]==dia_down)
				s[5]+=(16-i);
		}
		//if((in.spellcasted>5)&&(in.spellcasted<18))
		//{
		int dum=max(s);
		if(dum==0)
			final=findpos(left);
		if(dum==1)
			final=findpos(right);
		if(dum==2)
			final=findpos(up);
		if(dum==3)
			final=findpos(down);
		//if(dum==4)
		  //	final=findpos(dia_up);
		//if(dum==5)
		     //	final=findpos(dia_down);
	 int k1=find('P').x;
	 int k2=find('P').y;
	 if(in.myhealth>9000)
	 {
	 if((dum<4)&&(dum>-1))
	 {
		//exit(1);
		if((final.x==k1)||(final.y==k2))
		{
			return final;
		}
	 }}
	 pos t;
	 t.x=find('P').x;
	 t.y=find('P').y;
	 //if(in.spellcasted>5)
	 //{
		if((t.x+t.y)%2==0)
		{	if((in.arena[t.x+1][t.y]!='B')
			&&(in.arena[t.x+1][t.y]!='X')
			&&(in.arena[t.x+1][t.y]!='D'))
			{
				if((t.x+1)<14)
				{
					t.x=t.x+1;
					return t;
				}
			}
			if((in.arena[t.x][t.y+1]!='B')
			&&(in.arena[t.x][t.y+1]!='X')
			&&(in.arena[t.x][t.y+1]!='D'))
			{
				if((t.y+1)<14)
				{
					t.y=t.y+1;
					return t;
				}
			}
			if((in.arena[t.x-1][t.y]!='B')
			&&(in.arena[t.x-1][t.y]!='X')
			&&(in.arena[t.x-1][t.y]!='D'))
			{
				if((t.x-1)>0)
				{
					t.x=t.x-1;
					return t;
				}
			}
			if((in.arena[t.x][t.y-1]!='B')&&
			(in.arena[t.x][t.y-1]!='X')&&
			(in.arena[t.x][t.y-1]!='D')&&(t.y-1>0))
			{
				t.y=t.y-1;
				return t;
			}
		}
		else
		{
			if((in.arena[t.x][t.y+1]!='B')
			&&(in.arena[t.x][t.y+1]!='X')
			&&(in.arena[t.x][t.y+1]!='D'))
			{
				if((t.y+1)<14)
				{
					t.y=t.y+1;
					return t;
				}
			}
			if((in.arena[t.x-1][t.y]!='B')
			&&(in.arena[t.x-1][t.y]!='X')
			&&(in.arena[t.x-1][t.y]!='D'))
			{
				if((t.x-1)>0)
				{
					t.x=t.x-1;
					return t;
				}
			}
			if((in.arena[t.x+1][t.y]!='B')
			&&(in.arena[t.x+1][t.y]!='X')
			&&(in.arena[t.x+1][t.y]!='D'))
			{
				if((t.x+1)<14)
				{
					t.x=t.x+1;
					return t;
				}
			}
			if((in.arena[t.x][t.y-1]!='B')&&
			(in.arena[t.x][t.y-1]!='X')&&
			(in.arena[t.x][t.y-1]!='D')&&(t.y-1>0))
			{
				t.y=t.y-1;
				return t;
			}
		}

	 //if(t.x)
	 return t;
}




pos find_h(char ch,int k)
		//this finds character ch position from (i)th back arena
{
	pos t={-1,-1};
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
		{
			if(ar[k].arena[i][j]==ch)
			{
				t.x=i;
				t.y=j;
				return t;
			}
		}
	return t;
}

pos findpos(enum mov_dir a)
{
	int k=1;
	int mov=1;
	if(in.myagility>4000)
		mov=3;
	else
	if((in.myagility<=4000)&&(in.myagility>3000))
		mov=2;
		else
	if((in.myagility<=3000)&&(in.myagility>2000))
		mov=2;
	else
	if((in.myagility<=2000)&&(in.myagility>1250))
		mov=2;
	if(in.spellcasted<=5)
	mov=1;
	if((in.myagility<=1250))
		mov=1;
	char temp;
	pos t;
	if(a==left)
	{
		k=1;
		while(k<=mov)
		{
		temp=in.arena[find('P').x][find('P').y+k];
		if((temp!='B')&&(temp!='X')&&(temp!='D')
		&&((find('P').y+k)<15))
		{

			if(temp=='S')
			{	//t= {find('P').x,find('P').y+k};
				t.x=find('P').x;
				t.y=find('P').y+k;
				return t;
			}
			k++;
		}
		else
		{
			if(k==1)
				k=-1;
			break;

		}
		}
		if(k!=-1)
		{	t.x=find('P').x;
			t.y=find('P').y+k-1;
			return t;
		}
	}
	if((a==right)||(k==-1))
	{
		k=1;
		while(k<=mov)
		{
		temp=in.arena[find('P').x][find('P').y-k];
		if((temp!='B')&&(temp!='X')&&(temp!='D')
		&&((find('P').y-k)>0))
		{

			//if(temp=='S')
				//;
			k++;
		}
		else
		{
			if(k==1)
				k=-1;
			break;

		}
		}
		if(k!=-1)
			t.x=find('P').x;
			t.y=find('P').y-k+1;
			return t;
	}
	if((a==up)||(k==-1))
	{
		k=1;
		while(k<=mov)
		{
		temp=in.arena[find('P').x-k][find('P').y];
		if((temp!='B')&&(temp!='X')&&(temp!='D')
		&&((find('P').x-k)>0))
		{

		      //	if(temp=='S')
			//	return {temp.x,temp.y};
			k++;
		}
		else
		{
			if(k==1)
				k=-1;
			break;

		}
		}
		if(k!=-1)
		{
			t.x=find('P').x-k+1;
			t.y=find('P').y;
			return t;
		}
	}
	if((a==down)||(k==-1))
	{
		k=1;
		while(k<=mov)
		{
		temp=in.arena[find('P').x+k][find('P').y];
		if((temp!='B')&&(temp!='X')&&(temp!='D')
		&&((find('P').x+k)<15))
		{

		       //	if(temp=='S')
			 //	return {temp.x,temp.y};
			k++;
		}
		else
		{
			if(k==1)
				k=-1;
			break;

		}
		}
		if(k!=-1)
		{
			t.x=find('P').x+k-1;
			t.y=find('P').y;
			return t;
		}
	}

	//pos t;
	t.x=find('P').x;
	t.y=find('P').y;
	return t;
}
void defence()    //defense
{


	if(che_def_mov_s()==0) //to select wether move or cast defensive spell
		     //returns-1---use movement
		     //returns-0---cast defensive spell
		     //return -1 if no cast nor spell
	{
		//s_def();    //to select spell of defence
		rep.defspellused=s_def();
	}
	else
	if(che_def_mov_s()==-1)
	;
	else
	if(che_def_mov_s()==1)
	{
		 rep.xmovefinal=mov().x;       //select positon after movement
		 rep.ymovefinal=mov().y;
	}
}
void offence()
{
	//pos t;
	//t.x=find('@').x;
	//t.y=find('@').y;
	if(in.myhealth<500)
	{
			if(in.myspellpower>250)
				rep.offspellused=10;
			else
				if(in.myspellpower>200)
				{
					rep.xspellfinal=find('O').x;
					rep.yspellfinal=find('O').y;
					rep.offspellused=9;
				}
				else
				{
					rep.xspellfinal=find('O').x;
					rep.yspellfinal=find('O').y;
					rep.offspellused=1;
				}

	}
	/*else
	if((t.x!=-1)&&(t.y!=-1))
	{

		rep.xspellfinal=find('@').x;
		rep.yspellfinal=find('@').y;
		rep.offspellused=1;
	}*/
	else
	if(in.myspellpower==5000)
	{
		rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=15;
	}
	else
	if((sp.lastspellhitopp()==12)||(sp.lastspellhitopp()==15))
	{
		if(in.myspellpower>750)
		{
			rep.offspellused=13;
			rep.xspellfinal=find('O').x;
			rep.yspellfinal=find('O').y;
		}
		else
		{
			rep.offspellused=1;
			rep.xspellfinal=find('O').x;
			rep.yspellfinal=find('O').y;
		}
	}
      /*	if(st.agilitystatusopp())
	{
		rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		if()
	}*/
      else
	if(in.myspellpower>4500)
	{
		rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=12;
	}
	else
	if(in.myspellpower>4100)
	{
		rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=15;
	}
	else
	if(in.myspellpower>4050)
	{
		rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=17;
	}
	else
	if(in.myspellpower>4010)
	{
		rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=12;
	}
	else
	if(in.myspellpower>3400)
	{
		rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=12;
	}
	else
	if(in.myspellpower>3000)
	{
		rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=5;
	}
	else

	if(in.myspellpower>2000)
	{
		rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=4;
	}
	else

		if(in.myspellpower>1500)
	      {	rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=3;
	}
	else

		if(in.myspellpower>800)
	{	rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=2;
	}
	else

		if(in.myspellpower<=800)
	{	rep.xspellfinal=find('O').x;
		rep.yspellfinal=find('O').y;
		rep.offspellused=1;
	}
}
