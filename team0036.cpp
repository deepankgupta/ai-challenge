#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

class team0036  //here the class name is given to be team0002 assuming that the registration no. of the participant was 2
{
  private:      //private fns and variables defined
	int pl1,ph1,player_num,player_no,strenreq,k,flag,temp,kd,bpo,tp;
	int chk[23],totu,ball_player,i,j,pl2,ph2,x1,y1,chk2[23],temp1[23],log,ftp,c;
	int preqp(int finalx,int finaly, int initialx ,int initialy )  //function which tells the strength req by player to move from
	{
		float req;                                                    //place to another
		req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
		return (int)req;
	}

	int preqpb(int finalx,int finaly, int initialx ,int initialy )   //function which tells the strength req by hitter of ball to hit
	{
		float req;                                          //the ball from one place to another
		req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
		return (int)req;
	}
  public:
	int init(int team_number, struct player *p,char farray[][51])   //the mandatory function which initialises the team no. of the
	{                                                  //participant and tells him the initial field distribution
		player_no = team_number;

	}

	int player( struct player *p)        //main player func
	{


		int a;
		for(int i=0;i<23;i++)//initializing chk array
		{
			chk[i]=1;
			chk2[i]=1;
			temp1[i]=0;
		}
		temp=0;log=0;
		kd=1;tp=0;ftp=0;
		flag=0;
	 //assigning limits according to player no.
		if(player_no==1)
		{

			pl1=1;            //pl shows the lower limit and ph shows the upper limit of players in the array of structures ,i.e. if player
			ph1=11;
			pl2=12;
			ph2=22;           //is 1st then his players will be 1 to 11 and if he is 2nd then his players will be 12 to 22
			player_num=1;
		}

		else
		{
			pl1=12;
			ph1=22;
			pl2=1;
			ph2=11;
			player_num=2;
		}
int l=0;
ball_player=0;
		if(player_no==1)//chekin ball_player if we r pl1
		{
			for(int i=1;i<23;i++)
				if(p[0].x==p[i].x && p[0].y==p[i].y)
				{
                    if(p[i].strength>=l)              
					{
                      if(i>11 && ball_player!=0)
                              break;
                     ball_player=i;
					l=p[ball_player].strength;
					flag++;
					
                    }
					
				}
		}
		else if(player_no==2)//checkin ball_player if we r pl2
		{
			for(int i=22;i>0;i--)
				if(p[0].x==p[i].x && p[0].y==p[i].y)
				{
					if(p[i].strength>=l)
					{
                                        if(i<12 && ball_player!=0)
                                        {
                                                break;
                                        
                                        }
                                        ball_player=i;
                                        l=p[ball_player].strength;
					                    flag++;
                    }
				}
		}
		if(flag==0)  //i.e no player having ball
		{
			a=case3(p);
			return a;   //returns the hitter of the ball to the controller
		}


		if((ball_player<=11 && player_no==1)||(ball_player>11 && player_no==2)) //i.e ball wid my team
		{
			a=case1(ball_player,p);
			return a;
		}

		// ball with opp team player
		a=case2(ball_player,p);
		return a;


	}//end of player func.

	//function to chek the lest strength of player to make a goal
	int shortdistance(struct player p1)
	{
		int shortr=100,y; //cant use short it is a keyword
		if(player_no==1)
		{
			for(y=10;y<40;y++)
				if(preqpb(87,y,p1.x,p1.y)<shortr)
				{
					shortr=preqpb(87,y,p1.x,p1.y);
					x1=87;y1=y;
				 }
		}
		else if(player_no==2)
		{
			for(y=10;y<40;y++)
				if(preqpb(14,y,p1.x,p1.y)<shortr)
				{
					shortr=preqpb(14,y,p1.x,p1.y);
					x1=14;y1=y;
				 }
		}

		return shortr;
	}
	//returns 0 if intercepted
	int anti_intercept(int x,int y,struct player p1,struct player *p)
	{
		int tx,ty;
		for(tx=p1.x,ty=p1.y;tx!=x && ty!=y; )
		{
			if(x>tx && y>ty)
			{
				tx++;
				ty++;
			}
			else if(x>tx && y<ty)
			{
				tx++;
				ty--;
			}
			else if(x<tx && y<ty)
			{
				tx--;
				ty--;
			}
			else if(x<tx && y>ty)
			{
				tx--;
				ty++;
			}
			else if(tx==x && ty!=y)
			{
				if(y>ty)
					ty++;
				else
					ty--;
			}
			else if(tx!=x && ty==y)
			{
				if(x>tx)
					tx++;
				else
					tx--;
			}
			for(int i=pl2;i<=ph2;i++)
			{
				if(p[i].x==tx && p[i].y==ty)
				{
					return 0;
				}
			}
		}
		return 1;
	}

	int in_dee(struct player p1)
	{
		if(player_no==1)
			if(p1.x>60 && p1.y>5 && p1.y<45)
			       return 1;
		if(player_no==2)
			if(p1.x<40 && p1.y>5 && p1.y<45)
			       return 1;
		return 0;
	}

	void movement(int x,int y,struct player *p)
	{
		int small=100;int flag=0;
		int b=0;
		for(i=pl1;i<=ph1;i++)
		{
			if(p[i].x==x && p[i].y==y)
				flag++;
		 }
		if(flag==0)
		{
			for(i=pl1;i<=ph1;i++)
			{
				if(chk2[i]==1 && i!=ball_player)
				{
					strenreq=preqp(x,y,p[i].x,p[i].y);
					if(strenreq<p[i].strength && strenreq<small)
					{
						small=strenreq;
						b=i;
					}
				}
			}
		}

		if(b!=0)
		{
			p[b].x=x;
			p[b].y=y;
			chk2[b]=0;
			temp1[b]=strenreq;
		}
	}
	int chkclash(int ball_player,struct player *p)
	{
		 for(int t=pl2;t<=ph2;t++)
		 {
			if(p[t].x==p[0].x && p[t].y==p[0].y)
			{
				bpo=t;
				return 1;
			}
		 }
		 return 0;
	}

	int case1(int ball_player,struct player * p) //case1 i.e ball wid my player
	{
        totu=0;
        if(player_no==1)
        {
			     movement(61,11,p);
			     movement(61,39,p);
				movement(74,11,p);
				movement(59,11,p);
				movement(74,39,p);
				movement(59,39,p);
				for(int b=pl1;b<=ph1;b++)
				{
                       if(p[b].x<40)
                       { 
                               if((p[b].strength>=preqpb(59,39,p[b].x,p[b].y)) || (p[b].strength>=preqpb(59,11,p[b].x,p[b].y ) ))
                               {
                                        totu++;
                               }
                         }
                 }   
                 if(totu==0)
                        {movement(40,25,p);}                                                      
				
            
			}
			if(player_no==2)
			{
  	            movement(39,11,p);
                movement(39,39,p);
				movement(41,11,p);
				movement(26,11,p);
				movement(41,39,p);
				movement(26,39,p);
				for(int b=pl1;b<=ph1;b++)
				  {
                          if(p[b].x>60)
                          { 
                                   if((p[b].strength>=preqpb(41,39,p[b].x,p[b].y)) ||(p[b].strength >=preqpb(41,11,p[b].x,p[b].y )) )
                                   {
                                           totu++;
                                   }
                           }   
                 }
                 if(totu==0)
                       {movement(60,25,p);}                         
				
				
			  }

		int p_player[23],shortest=100,x,y;
		p_player[log]=0;
		//try goal starts
		if(chkclash(ball_player,p)==0)
		{
			if(p[ball_player].strength<30 && kd==1)
			{
	     //		      	if(shortdistance(p[ball_player])<p[ball_player].strength+20 && anti_intercept(x1,y1,p[ball_player],p)==1)//goal if u can
				if(player_no==1)
				{x=87;}
				else if(player_no==2)
				{x=14;}
				for(y=10;y<40;y++)
				{
					strenreq=preqpb(x,y,p[ball_player].x,p[ball_player].y);
					if(strenreq<p[ball_player].strength+20 && anti_intercept(x,y,p[ball_player],p)==1)
					{
						p[0].x=x;
						p[0].y=y;
						return ball_player;

					}
				}
			   }
			if(p[ball_player].strength>=30 && kd==1)
			{
			       //	if(shortdistance(p[ball_player])<50 && anti_intercept(x1,y1,p[ball_player],p)==1)//goal if u can
				if(player_no==1)
				{x=87;}
				else if(player_no==2)
				{x=14;}
				for(y=10;y<40;y++)
				{
					strenreq=preqpb(x,y,p[ball_player].x,p[ball_player].y);
					if(strenreq<50 && anti_intercept(x,y,p[ball_player],p)==1)
					{
						p[0].x=x;
						p[0].y=y;
						return ball_player;

					}
				}
			}
			if(kd==0)
			{
			   //	if(shortdistance(p[ball_player])<p[ball_player].strength-temp && anti_intercept(x1,y1,p[ball_player],p)==1)//goal if u can
				if(player_no==1)
				{x=87;}
				else if(player_no==2)
				{x=14;}
				for(y=10;y<40;y++)
				{
					strenreq=preqpb(x,y,p[ball_player].x,p[ball_player].y);
					if(strenreq<p[ball_player].strength-temp && anti_intercept(x,y,p[ball_player],p)==1)
					{
						p[0].x=x;
						p[0].y=y;
						return ball_player;

					}
				}
			}
		}
		else if(chkclash(ball_player,p)==1)
		{
		   if(p[ball_player].strength<30 && kd==1)
		   {
			//if(shortdistance(p[ball_player])<p[ball_player].strength-p[bpo].strength && anti_intercept(x1,y1,p[ball_player],p)==1)//goal if u can
			if(player_no==1)
			{x=87;}
			else if(player_no==2)
			{x=14;}
			for(y=10;y<40;y++)
			{
				strenreq=preqpb(x,y,p[ball_player].x,p[ball_player].y);
				if(strenreq<p[ball_player].strength-p[bpo].strength && anti_intercept(x,y,p[ball_player],p)==1)
				{
					p[0].x=x;
					p[0].y=y;
					return ball_player;

				}
			}
		   }
		   if(p[ball_player].strength>=30 && kd==1)
		   {
		       //	if(shortdistance(p[ball_player])<50-p[bpo].strength && anti_intercept(x1,y1,p[ball_player],p)==1)//goal if u can
			if(player_no==1)
			{x=87;}
			else if(player_no==2)
			{x=14;}
			for(y=10;y<40;y++)
			{
				strenreq=preqpb(x,y,p[ball_player].x,p[ball_player].y);
				if(strenreq<50-p[bpo].strength && anti_intercept(x,y,p[ball_player],p)==1)
				{
					p[0].x=x;
					p[0].y=y;
					return ball_player;

				}
			}
		   }
		   if(kd==0)
		   {
			//if(shortdistance(p[ball_player])<p[ball_player].strength-temp-p[bpo].strength && anti_intercept(x1,y1,p[ball_player],p)==1)//goal if u can
			if(player_no==1)
			{x=87;}
			else if(player_no==2)
			{x=14;}
			for(y=10;y<40;y++)
			{
				strenreq=preqpb(x,y,p[ball_player].x,p[ball_player].y);
				if(strenreq<p[ball_player].strength-temp-p[bpo].strength && anti_intercept(x,y,p[ball_player],p)==1)
				{
					p[0].x=x;
					p[0].y=y;
					return ball_player;

				}
			}
		   }

		}
		//try goal ends
		
		for(i=1;i<23;i++)
		{
                         if(p[i].x==p[ball_player].x && p[i].y==p[ball_player].y)
                                       {p_player[i]=0;}
                      	 else
                           p_player[i]=1;
         }
         
		for(i=pl1;i<=ph1;i++)
		{
			if(i!=ball_player)
			{
				strenreq=preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y);
				if(kd==1 && p[ball_player].strength<30 && chk2[i]==1)
				{
					if((p[ball_player].strength+20<strenreq && chkclash(ball_player,p)==0)||(chkclash(ball_player,p)==1 && p[ball_player].strength+20-p[bpo].strength<strenreq))
					{
						p_player[i]=0;
					}
				}
				if(kd==1 && p[ball_player].strength>=30 && chk2[i]==1)
				{
					if((50<strenreq && chkclash(ball_player,p)==0)||(chkclash(ball_player,p)==1 && 50-p[bpo].strength<strenreq))
					{
    
						p_player[i]=0;
					}
				}
				if(kd==0 || chk2[i]==0)
				{
					if((p[ball_player].strength-temp1[i]<strenreq && chkclash(ball_player,p)==0) || (chkclash(ball_player,p)==1 && p[ball_player].strength-temp-p[bpo].strength<strenreq))
					{
						p_player[i]=0;
					}
				}
			}
		}
	   if(log==0)
	   {
		int fl=0,large=0,m=0,str;
		for(int he=pl1;he<=ph1;he++)
		{
			if(p_player[he]==1 && he!=ball_player && (p[he].x!=p[ball_player].x || p[he].y!=p[ball_player].y))
			{
			       fl++;
			}
		}
		if(fl==0)
		{
			for(i=pl1;i<=ph1;i++)
			{
				if(chkclash(ball_player,p)==0)
				{
					if(i!=ball_player && chk2[i]!=0 &&(p[i].x!=p[ball_player].x || p[i].y!=p[ball_player].y))
					{
						strenreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);
						str=p[i].strength-strenreq;
						if(large<str && str>p[ball_player].strength)
						{
							large=str;
							m=i;
							temp=str;
						}
					}
				}
				 c=0;
				if(chkclash(ball_player,p)==1)
				{  
					if(i!=ball_player && chk2[i]!=0 && (p[i].x!=p[ball_player].x || p[i].y!=p[ball_player].y))
					{
                        c=10;              
						strenreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);
						str=p[i].strength-strenreq;
						if(large<str && str>p[ball_player].strength && str>p[bpo].strength)
						{
							large=str;
							m=i;
							temp=str;
							c=20;
						}
					}
				}

			}
			if(m==0 && c==10)
                    return ball_player;
                  
			if(m!=0)
			{
			p[m].x=p[0].x;
			p[m].y=p[0].y;
			chk2[m]=0;
			temp1[m]=p[m].strength-temp;
			log=ball_player;
			team0036::ball_player=m;
			kd=0;
			return case1(m,p);
            }
		}
	   }
	  //	flag=0;
	  /*
		for(j=pl2;j<=ph2;j++)
		{
			if(p[j].x==p[ball_player].x && p[j].y==p[ball_player].y)
		  flag++;
			if(flag!=0)
				break;
		}
	  */

		for(i=pl1;i<=ph1;i++) //
		{
			if((player_no==1 && p[i].x>p[ball_player].x && p_player[i]==1) || (player_no==2 && p[i].x<p[ball_player].x && p_player[i]==1))
			{
				//ftp++;
				
				for(j=pl2;j<=ph2;j++)
				{;
					strenreq=preqp(p[i].x,p[i].y,p[j].x,p[j].y);
					if(strenreq<p[j].strength)
					{
					       if(p[i].strength<30 && chk2[i]!=0)
							{
       
                             if(p[i].strength+20-(p[j].strength-strenreq)<0)
								{p_player[i]=0;}
                          }
					       else if(p[i].strength>=30 && chk2[i]!=0)
							{
                                if(50-(p[j].strength-strenreq)<0)
								{p_player[i]=0;}
                          }
					       else if(chk2[i]==0)
						{	if(p[i].strength-temp1[i]-(p[j].strength-strenreq)<0)
								p_player[i]=0;
								
                            }
					}
					if(p_player[i]==0)
						break;
				}
			}
		}
		if(log==0)
	   {
		int fl=0,large=0,m=0,str;
		for(int he=pl1;he<=ph1;he++)
		{
			if(p_player[he]==1 && he!=ball_player && (p[he].x!=p[ball_player].x || p[he].y!=p[ball_player].y))
			{
                              
			       fl++;
			}
		}
		if(fl==0)
		{
			for(i=pl1;i<=ph1;i++)
			{
				if(chkclash(ball_player,p)==0)
				{
					if(i!=ball_player && chk2[i]!=0&& (p[i].x!=p[ball_player].x || p[i].y!=p[ball_player].y))
					{
						strenreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);
						str=p[i].strength-strenreq;
						if(large<str && str>p[ball_player].strength)
						{
							large=str;
							m=i;
							temp=str;
						}
					}
				}
				 c=0;
				if(chkclash(ball_player,p)==1)
				{
					if(i!=ball_player && chk2[i]!=0 && (p[i].x!=p[ball_player].x || p[i].y!=p[ball_player].y))
					{
                        c=10;
						strenreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);
						str=p[i].strength-strenreq;
						if(large<str && str>p[ball_player].strength && str>p[bpo].strength)
						{
							large=str;
							m=i;
							temp=str;
							c=20;
						}
					}
				}

			}
			if(m==0 && c==10)
			{
                       return ball_player;
             }
			if(m!=0)
			{
			p[m].x=p[0].x;
			p[m].y=p[0].y;
			chk2[m]=0;
			log=ball_player;
			team0036::ball_player=m;
			kd=0;
			return case1(m,p);
            }
		}
	   }
		for (i=pl1;i<=ph1;i++) //
		{
			if((player_no==1 && p[i].x<p[ball_player].x) || (player_no==2 && p[i].x>p[ball_player].x))
			{
			     p_player[i]=0;
			}
		}

		int l=0;k=0;int s=101;
		for(int ha=pl1;ha<=ph1;ha++)
		{
			if(p_player[ha]==1 && (p[ha].x!=p[ball_player].x || p[ha].y!=p[ball_player].y) && in_dee(p[ha])==1 && in_dee(p[ball_player])==0 && anti_intercept(p[ha].x,p[ha].y,p[0],p)==1)
			{
				k=ha;
				break;
			}
			else if(p_player[ha]==1 && (p[ha].x!=p[ball_player].x || p[ha].y!=p[ball_player].y) && anti_intercept(p[ha].x,p[ha].y,p[0],p)==1 )
			{
  
				if((player_no==1 && p[ha].x>l)||(player_no==2 && p[ha].x<s))
				{
    
					l=p[ha].x;
					s=p[ha].x;
					k=ha;
				}
			}
		}
		if(k!=0)
		{
			p[0].x=p[k].x;
			p[0].y=p[k].y;
			return(ball_player);
		}
	   
		if(k==0)//i.e when either no player ahead or none has power to shoot
		{
			
		}
		int r=pass(p);
		return r;

	}                     // end of case1() func.

//pass function to backwards
	int pass(struct player *p)
	{
		int p_player[23];//plausible players
		flag=0;
		for(i=1;i<=23;i++)
		{
                          if(p[i].x==p[ball_player].x && p[i].y==p[ball_player].y)
                                                      p_player[i]=0;
                          else
                          	p_player[i]=1;
        }
		p_player[log]=0;
		for(i=pl1;i<=ph1;i++)
		{ 
			if(i!=ball_player)
			{
				strenreq=preqpb(p[i].x,p[i].y,p[ball_player].x,p[ball_player].y);
				if(kd==1 && p[ball_player].strength<30)
				{
					if((p[ball_player].strength+20<strenreq && chkclash(ball_player,p)==0)||(chkclash(ball_player,p)==1 && p[ball_player].strength+20-p[bpo].strength<strenreq))
					{
						p_player[i]=0;
					}
				}
				if(kd==1 && p[ball_player].strength>=30)
				{
					if((50<strenreq && chkclash(ball_player,p)==0)||(chkclash(ball_player,p)==1 && 50-p[bpo].strength<strenreq))
					{
						p_player[i]=0;
					}
				}
				if(kd==0)
				{ 
					if((p[ball_player].strength-temp<strenreq && chkclash(ball_player,p)==0) || (chkclash(ball_player,p)==1 && p[ball_player].strength-temp-p[bpo].strength<strenreq))
					{
						p_player[i]=0;
					}
				}
			}
		}


		if(50-shortdistance(p[ball_player])>0 && in_dee(p[ball_player])==1 && ((p[ball_player].strength<50 && kd==0)||(p[ball_player].strength<30 && kd==1)))
			 return -1;

		if(in_dee(p[ball_player])==1)
		{
			for(int j=pl1;j<=ph1;j++)
			{
				if(in_dee(p[j])==1)
					p_player[j]=0;
			}
		 }

	//if(in_dee(player_ball)==0)//do nothing

		for(j=pl1;j<=ph1;j++)
		{
			if (p_player[j]==1 && j!=ball_player)
			{
				flag=player_threat(p[j],j,p);
			if(flag==0)//i.e ball can be passed
				p_player[j]=0;
			}
		}      	//pass the ball to player with max strength out of the p_players
		//and nearest

		int small=100,d,k=0;
		for(int f=pl1;f<=ph1;f++)
			if(p_player[f]==1 && (p[f].x!=p[ball_player].x || p[f].y!=p[ball_player].y) && anti_intercept(p[f].x,p[f].y,p[ball_player],p)==1)
			{
				d=preqpb(p[f].x,p[f].y,p[ball_player].x,p[ball_player].y);
				if(d<small)
				{
					small=d;
					k=f;
				}
			}
			
			if(k!=0)
      {
		if(p[k].strength>30)
		{
			p[0].x=p[k].x;
			p[0].y=p[k].y;
			return ball_player;
		}
		else
		{
			int large=0,g=0;
			for(i=pl1;i<=ph1;i++)
				if(p_player[i]==1&&(p[i].x!=p[ball_player].x || p[i].y!=p[ball_player].y)&& anti_intercept(p[i].x,p[i].y,p[ball_player],p)==1)
					if(p[i].strength>large)
					{
						large=p[i].strength;
						g=i;
					}
			p[0].x=p[g].x;
			p[0].y=p[g].y;
			return ball_player;
		}
      }
		return -1;
	}

	int player_threat(struct player p1,int b,struct player *p)//for all players in p_player,it chks which players can
	{              //get the ball without problem
		       int h=1;
		if(b!=ball_player)
		{
			for(int t=pl2;t<=ph2;t++)
			{
				strenreq=preqp(p1.x,p1.y,p[t].x,p[t].y);
				if(strenreq<p[t].strength)
				{
					if(p1.strength<30 && chk2[b]==1)
					{	if(p1.strength+20-(p[t].strength-strenreq)<0)
							h=0;
                 }
					else if(p1.strength>=30 && chk2[b]==1)
					{	if(50-(p[t].strength-strenreq)<0)
							h=0;
							
                        }
					else if(chk2[b]==0)
					{
                         	if(p1.strength-temp1[b]-(p[t].strength-strenreq)<0)
							h=0;
                     }
				}
	 //		        if(p[t].strength-strenreq>p1.strength)
	 //				h=0;
			}
	 //		strenreq=preqpb(p1.x,p1.y,p[ball_player].x,p[ball_player].y);
	 //		if(p[ball_player].strength-strenreq-temp<0)
	 //			h=0;
		}
		int f=0;
		if(h==1)
			f++;
		return (f);
	}


// Definition of case2() func.

//ball is with opp team's player
	int case2(int ball_player,struct player *p)
	{
		int x4,y4,large=0,z=0;
		for(int jk=pl1;jk<=ph1;jk++)
		{
			if(in_dee(p[jk])==1)
				chk[jk]=0;
			chk[jk]=1;
		}
		for(int jk=pl1;jk<=ph1;jk++)
		{
			strenreq=preqp(p[ball_player].x,p[ball_player].y,p[jk].x,p[jk].y);
			if( (p[jk].strength -strenreq)> large && chk[jk]==1)
			{
				large=p[jk].strength-strenreq;
				z=jk;
			}
		}
		if(z>=1 && z<=22)
		{
			p[z].x=p[ball_player].x;
			p[z].y=p[ball_player].y;
			chk[z]=0;
		}
		if(player_no==1 && (p[z].strength<p[ball_player].strength || z==0))
		{
			x4=p[ball_player].x-1;
			y4=p[ball_player].y-1;
			marlo(x4,y4,p);
			y4=p[ball_player].y;
			marlo(x4,y4,p);
			y4=p[ball_player].y+1;
			marlo(x4,y4,p);
			x4=p[ball_player].x+1;
			y4=p[ball_player].y-1;
			marlo(x4,y4,p);
			y4=p[ball_player].y;
			marlo(x4,y4,p);
			y4=p[ball_player].y+1;
			marlo(x4,y4,p);
			
		}
		if(player_no==2 && (p[z].strength<p[ball_player].strength || z==0))
		{
			x4=p[ball_player].x+1;
			y4=p[ball_player].y-1;
			marlo(x4,y4,p);
			y4=p[ball_player].y;
			marlo(x4,y4,p);
			y4=p[ball_player].y+1;
			marlo(x4,y4,p);
			x4=p[ball_player].x-1;
			y4=p[ball_player].y-1;
			marlo(x4,y4,p);
			y4=p[ball_player].y;
			marlo(x4,y4,p);
			y4=p[ball_player].y+1;
			marlo(x4,y4,p);
		}
		if(p[z].strength-strenreq>p[ball_player].strength)
		{
			team0036::ball_player=z;
			kd=0;
			case1(z,p);
		}
		return -1;
	}
	void marlo(int x4,int y4,struct player *p)
	{
		int g,small=100,strenreq2;
		for(int t=pl1;t<=ph1;t++)
		{
			if((player_no==1 && p[ball_player].x<=60)||(player_no==2 && p[ball_player].x>=40))
			{
				if(chk[t]==1)
				{
					strenreq2=preqp(x4,y4,p[t].x,p[t].y);
					if(small>strenreq2)
					{
						small=strenreq2;
						g=t;
					}
				}
			}
		}
		p[g].x=x4;
		p[g].y=y4;
		chk[g]=0;
		chk2[g]=0;
		temp1[g]=small;
	}


//definition of case3() func.

//when ball is with no player

	int case3(struct player * p)
	{

		int a,large=0;
		k=0;
		

  //this for loop searches for a player of my team such that after reaching at the position of the ball it is having the maximum
  //strength left to hit the ball
		for(i=pl1;i<=ph1;i++)
		{
			strenreq=preqp(p[0].x,p[0].y,p[i].x,p[i].y);
			if((p[i].strength - strenreq) >  large)  //large is having max strength of the player after reaching there
			{                                        //player_no is having the no. of the desired player
				k=i;
				large=(p[i].strength-strenreq);
			}             //end of if

		}     //end of for loop


   //if such player is found having maximum and non-zero strength left after reaching the position of the ball then that player
   //is moved to ball's position and case1 function is called as the situation is similar to that when my player is having the
   //possession of the ball
		if(k!=0)
		{
			temp=preqp(p[0].x,p[0].y,p[k].x,p[k].y);
            p[k].x=p[0].x;
			p[k].y=p[0].y;
			chk2[k]=0;
			
			team0036::ball_player=k;
			temp1[k]=temp;
			kd=0;
			a=case1(k,p);
			return a;
		}

    //if no player is found having non-zero strength after reaching the ball's position the move is skipped
		return -1;
	} // end of case3()

};




//in_range is a function defined by the participant
//it checks wheter the ball is in the range of the goal or not and returns 1 or 0 accordingly




   //end of the class team0002
