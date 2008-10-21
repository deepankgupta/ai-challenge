#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#include<math.h>

class team0102  //here the class name is given to be team0002 assuming that the registration no. of the participant was 2 
{
  private:      //private fns and variables defined
  int pl,ph,player_num,player_no,ol,oh;
  
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
    int init(int team_number,struct player *p,char farray[][51])//struct player *p,char farray[][51])   //the mandatory function which initialises the team no. of the 
	{                                                  //participant and tells him the initial field distribution
		player_no = team_number;
		
	}

int dpass(int i,struct player *p)
{
    int px=-1,j,powl,pass_player;
    for(j=pl;j<=ph;j++)
    {
                       if(p[j].x> p[i].x)
                       {
                                 powl=pleft(j,p);
                                 if(powl>px && !intercept(p[j].x,p[j].y,p[i].x,p[i].y,p))
                                 {
                                            pass_player=j;
                                            px=powl;
                                 }
                       }
    }
    if(px!=-1)
    {
     p[0].x=p[j].x;
     p[0].y=p[j].y;
     return i;
    }
    if(px==-1){
               return -1;
    }
}

int dregion1(int i,struct player *p)
{
    int j;
    for(j=40;j>=0;j--)
    {
                      if((!intercept(j,5,p[i].x,p[i].y,p)) && (preqpb(j,5,p[i].x,p[i].y)))
                      {
                                                         p[0].x=j;
                                                         p[0].y=5;
                                                         return i;
                      }
    }
    for(j=5;j<=45;j++)
    {
                       if((!intercept(40,j,p[i].x,p[i].y,p)) && (preqpb(40,j,p[i].x,p[i].y)))
                       {
                                                           p[0].x=40;
                                                           p[0].y=j;
                                                           return i;
                       }
    }
    i=dpass(i,p);
    return -1;
}

int dregion3(int i,struct player *p)
{
    int j;
    for(j=40;j>=0;j--)
    {
                      if((!intercept(j,45,p[i].x,p[i].y,p)) && (preqpb(j,45,p[i].x,p[i].y)))
                      {
                                                         p[0].x=j;
                                                         p[0].y=45;
                                                         return i;
                      }
    }
    for(j=45;j>=5;j--)
    {
                       if((!intercept(40,j,p[i].x,p[i].y,p)) && (preqpb(40,j,p[i].x,p[i].y)))
                       {
                                                           p[0].x=40;
                                                           p[0].y=j;
                                                           return i;
                       }
    }
    i=dpass(i,p);
    return -1;
}

int dregion4(int i,struct player *p)
{
    int j;
    for(j=p[i].x;j>=0;j--)
    {
                      if((!intercept(j,5,p[i].x,p[i].y,p)) && (preqpb(j,5,p[i].x,p[i].y)))
                      {
                                                         p[0].x=j;
                                                         p[0].y=5;
                                                         return i;
                      }
    }
    for(j=p[i].x;j<=40;j++)
    {
                       if((!intercept(j,5,p[i].x,p[i].y,p)) && (preqpb(j,5,p[i].x,p[i].y)))
                       {
                                                           p[0].x=j;
                                                           p[0].y=5;
                                                           return i;
                       }
    }
    i=dpass(i,p);
    return -1;
}

int dregion5(int i,struct player *p)
{
    int j;
    for(j=p[i].x;j>=0;j--)
    {
                      if((!intercept(j,45,p[i].x,p[i].y,p)) && (preqpb(j,45,p[i].x,p[i].y)))
                      {
                                                         p[0].x=j;
                                                         p[0].y=45;
                                                         return i;
                      }
    }
    for(j=p[i].x;j<=40;j++)
    {
                       if((!intercept(j,45,p[i].x,p[i].y,p)) && (preqpb(j,45,p[i].x,p[i].y)))
                       {
                                                           p[0].x=j;
                                                           p[0].y=45;
                                                           return i;
                       }
    }
    i=dpass(i,p);
    return -1;
}

int dregion2(int i,struct player *p)
{
    int j;
    for(j=p[i].y;j<=45;j++)
    {
                      if((!intercept(p[i].x,j,p[i].x,p[i].y,p)) && (preqpb(p[i].x,j,p[i].x,p[i].y)))
                      {
                                                         p[0].x=40;
                                                         p[0].y=j;
                                                         return i;
                      }
    }
    for(j=p[i].y;j>=5;j--)
    {
                       if((!intercept(40,j,p[i].x,p[i].y,p)) && (preqpb(40,j,p[i].x,p[i].y)))
                       {
                                                           p[0].x=40;
                                                           p[0].y=j;
                                                           return i;
                       }
    }
    i=dpass(i,p);
    return -1;
}

int hitd(int i,struct player*p)
{
    int strreq;
    if(p[i].y<5) //To check for region 1 and 4
    {
                  if(p[i].x>40) //To check for region 1
                  {
                                i=dregion1(i,p);
                                return i;
                  }
                  if(p[i].x<=40){ //To check for region 4
                        i=dregion4(i,p);
                        return i;
                  }
    }
    else if(p[i].y>45) //To check for region 5 and 6
    {
         if(p[i].y>40) //To check for region 3
         {
                       i=dregion3(i,p);
                       return i;
         }
         if(p[i].y<=40)//To check for region 5
         {
                      i=dregion5(i,p);
                      return i;
         }
    }
    else
    {
        i=dregion2(i,p);
        return i;
    }
}
    
int pass(int i,struct player *p)
{
    int px=-1,j,powl,pass_player;
    for(j=pl;j<=ph;j++)
    {
                       if(p[j].x< p[i].x)
                       {
                                 powl=pleft(j,p);
                                 if(powl>px && !intercept(p[j].x,p[j].y,p[i].x,p[i].y,p))
                                 {
                                            pass_player=j;
                                            px=powl;
                                 }
                       }
    }
    if(px!=-1)
    {
     p[0].x=p[j].x;
     p[0].y=p[j].y;
     return i;
    }
    if(px==-1){
               i=hitd(i,p);
               return i;
    }
}


int pleft(int j,struct player *p)
{
    int i,px,powl=99;
    for(i=ol;i<=oh;i++)
    {
                       if((p[i].x==p[j].x) && (p[i].y==p[j].y))
                       {
                                           px=p[j].strength - p[i].strength;
                                           if(px<powl)
                                                       powl=px;
                       }
    }
    if(powl==99)
                 powl=p[j].strength;
    return powl;
}
                                           
int intercept(int finalx,int finaly,int inix,int iniy,struct player*p)
{
    int validx,validy,j;
    validx=inix;
    validy=iniy;
    do{
                if(validx!=finalx)
                                  player_no==2?(validx--):(validx++);
                if(validy!=finaly){
                                   if(finaly>iniy)
                                                  validy++;
                                   else if(finaly<iniy)
                                                  validy--;
                }
                for(j=ol;j<=oh;j++)
                {
                                   if((p[j].x==validx) && (p[j].y==validy))
                                                       return 1;
                }
    }while((validx!=finalx) || (validy!=finaly));
    return 0;
}
                                   
                                  



int region1(int i,struct player *p)
{
    int j;
    for(j=14;j>=0;j--)
    {
                      if((!intercept(j,10,p[i].x,p[i].y,p)) && (preqpb(j,10,p[i].x,p[i].y)))
                      {
                                                         p[0].x=j;
                                                         p[0].y=10;
                                                         return i;
                      }
    }
    for(j=10;j<=40;j++)
    {
                       if((!intercept(14,j,p[i].x,p[i].y,p)) && (preqpb(14,j,p[i].x,p[i].y)))
                       {
                                                           p[0].x=14;
                                                           p[0].y=j;
                                                           return i;
                       }
    }
    i=pass(i,p);
    return i;
}

int region3(int i,struct player *p)
{
    int j;
    for(j=14;j>=0;j--)
    {
                      if((!intercept(j,40,p[i].x,p[i].y,p)) && (preqpb(j,40,p[i].x,p[i].y)))
                      {
                                                         p[0].x=j;
                                                         p[0].y=40;
                                                         return i;
                      }
    }
    for(j=40;j>=10;j--)
    {
                       if((!intercept(14,j,p[i].x,p[i].y,p)) && (preqpb(14,j,p[i].x,p[i].y)))
                       {
                                                           p[0].x=14;
                                                           p[0].y=j;
                                                           return i;
                       }
    }
    i=pass(i,p);
    return i;
}

int region4(int i,struct player *p)
{
    int j;
    for(j=p[i].x;j>=0;j--)
    {
                      if((!intercept(j,10,p[i].x,p[i].y,p)) && (preqpb(j,10,p[i].x,p[i].y)))
                      {
                                                         p[0].x=j;
                                                         p[0].y=10;
                                                         return i;
                      }
    }
    for(j=p[i].x;j<=14;j++)
    {
                       if((!intercept(j,10,p[i].x,p[i].y,p)) && (preqpb(j,10,p[i].x,p[i].y)))
                       {
                                                           p[0].x=j;
                                                           p[0].y=10;
                                                           return i;
                       }
    }
    i=pass(i,p);
    return i;
}

int region5(int i,struct player *p)
{
    int j;
    for(j=p[i].x;j>=0;j--)
    {
                      if((!intercept(j,40,p[i].x,p[i].y,p)) && (preqpb(j,40,p[i].x,p[i].y)))
                      {
                                                         p[0].x=j;
                                                         p[0].y=40;
                                                         return i;
                      }
    }
    for(j=p[i].x;j<=14;j++)
    {
                       if((!intercept(j,40,p[i].x,p[i].y,p)) && (preqpb(j,40,p[i].x,p[i].y)))
                       {
                                                           p[0].x=j;
                                                           p[0].y=40;
                                                           return i;
                       }
    }
    i=pass(i,p);
    return i;
}

int region2(int i,struct player *p)
{
    int j;
    for(j=p[i].y;j<=40;j++)
    {
                      if((!intercept(p[i].x,j,p[i].x,p[i].y,p)) && (preqpb(p[i].x,j,p[i].x,p[i].y)))
                      {
                                                         p[0].x=14;
                                                         p[0].y=j;
                                                         return i;
                      }
    }
    for(j=p[i].y;j>=10;j--)
    {
                       if((!intercept(14,j,p[i].x,p[i].y,p)) && (preqpb(14,j,p[i].x,p[i].y)))
                       {
                                                           p[0].x=14;
                                                           p[0].y=j;
                                                           return i;
                       }
    }
    i=pass(i,p);
    return i;
}


int case1(int i,struct player * p)//attack
{   
    int strreq;
    for(int j=pl;j<=ph;j++)
    {
            if(j!=i && p[j].strength>=40)
            p[j].x+=10;
            
    }
    if(p[i].y<10) //To check for region 1 and 4
    {
                  if(p[i].x>14) //To check for region 1
                  {
                                i=region1(i,p);
                                return i;
                  }
                  if(p[i].x<=14){ //To check for region 4
                        i=region4(i,p);
                        return i;
                  }
    }
    else if(p[i].y>40) //To check for region 5 and 6
    {
         if(p[i].y>14) //To check for region 3
         {
                       i=region3(i,p);
                       return i;
         }
         if(p[i].y<=14)//To check for region 5
         {
                      i=region5(i,p);
                      return i;
         }
    }
    else
    {
        i=region2(i,p);
        return i;
    }
}
//End of case1() fucn


int savegoal(int save_goal[],int l,int x,int y,struct player *p)
{
    int i,j,px,maxp=-1,flag=0;
    for(i=pl;i<=ph;i++)
    {
                       for(j=0;j<3;j++)
                       {
                                       if(i==save_goal[j])
                                       {
                                                          i++;
                                                          j=-1;
                                       }
                       }
                       px=p[i].strength-preqp(x,y,p[i].x,p[i].y);
                       if(px>maxp)
                       {
                                  maxp=px;
                                  save_goal[l]=i;
                                  flag=1;
                       }
    }
                       if(flag==1)
                                  return save_goal[l];
                       else 
                            return -1;
}    

void savepass(int save_pass[],int l,int inix,int iniy,int finalx,int finaly,struct player *p)
{
    int i,j,x,q,y,px;
    int validx=inix;
    int validy=iniy;
    int pmax=-1,flag=0;
    q=finalx;
    if(finalx>=60)
    finalx=59;
    label:
    do{
        if(validx!=finalx)
        finalx>inix?validx++:validx--;
        if(validy!=finaly)
        finaly>inix?validy++:validy--;
        for(i=pl;i<=ph;i++)
        {
                           for(j=0;j<=10;j++)
                           {   
                                             if(i==save_pass[j])
                                             {
                                                                i++;
                                                                j=-1;
                                             }
                           }
                           px=p[i].strength-preqp(validx,validy,p[i].x,p[i].y);
                           if(px>pmax)
                           {
                                      pmax=px;
                                      save_pass[l]=i;
                                      x=validx;
                                      y=validy;
                                      flag=1;
                           }
        }
        
    }while((validx!=finalx) && (validy!=finaly));
    
    if(flag!=1)
    goto label;
    
    if(flag==1)
    {
               p[save_pass[l]].x=x;
               p[save_pass[l]].y=y;
    }
}
               
                                           
    
// Definition of case2() func. Defend

//ball is with opp team's player
int case2(int i,struct player * p)
{   
    int a,px=-1,move_player,strreq,x,j,save_goal[3],t,save_pass[10],k;
    for(j=pl;j<=ph;j++)
    {
                       strreq=p[j].strength-preqp(p[i].x,p[i].y,p[j].x,p[j].y)-p[i].strength; 
                       if(strreq>px)
                       {
                                    px=strreq;
                                    move_player=j;
                       }
    }
    if(px!=-1)
    {
              p[move_player].x=p[i].x;
              p[move_player].y=p[i].y;
              a=case1(i,p);
              return a;
    }
    if(px==-1)
    {
              if(p[i].y<10)
              {
                           if(p[i].x<86) //region 1
                           {
                                        if(p[i].strength>=preqpb(86,10,p[i].x,p[i].y))
                                        {
                                                                                      x=traj(86,10,p[i].x,p[i].y,p);
                                                                                      if(x!=-1){
                                                                                      j=max_strength(x,10,p);
                                                                                      if(j!=-1)
                                                                                      {
                                                                                               p[j].x=x;
                                                                                               p[j].y=10;
                                                                                               return -1;
                                                                                      }
                                                                                      if(j==-1)
                                                                                      {
                                                                                               return -1;
                                                                                      }
                                                                                      }
                                                                                      else
                                                                                      return -1;
                                        }
                                        else{//save pass
                                             int l=0;
                                             for(j=0;j<10;j++)
                                             save_pass[j]=-1;
                                             for(j=ol;j<=oh;j++)
                                             {
                                                                if((preqpb(p[j].x,p[j].y,p[i].x,p[i].y)>=p[i].strength) && (p[j].x>=p[i].x))
                                                                {
                                                                    k=traj(p[j].x,p[j].y,p[i].x,p[i].y,p);
                                                                    if(k!=-1)
                                                                    {
                                                                             savepass(save_pass,l,p[i].x,p[i].y,p[j].x,p[j].y,p);
                                                                             l++;
                                                                    }
                                                                }
                                             }                   
                                             return -1;                                                                            
                                        }
                           }
                           else{//region 4
                                    if(p[i].strength>=preqpb(p[i].x,10,p[i].x,p[i].y))
                                    {
                                         for(j=0;j<3;j++)
                                         save_goal[j]=-1;
                                         
                                         t=savegoal(save_goal,0,p[i].x-1,p[i].y+1,p);
                                         if(t!=-1)
                                         {
                                                  p[t].x=p[i].x-1;
                                                  p[t].y=p[i].y+1;
                                         }                                                                                      
                                         t=savegoal(save_goal,1,p[i].x,p[i].y+1,p);
                                         if(t!=-1)
                                         {
                                                  p[t].x=p[i].x;
                                                  p[t].y=p[i].y+1;
                                         }
                                         t=savegoal(save_goal,2,p[i].x+1,p[i].y+1,p); 
                                         if(t!=-1)
                                         {
                                                  p[t].x=p[i].x+1;
                                                  p[t].y=p[i].y+1;
                                         }             
                                         return -1;         
                                    }
                                    if(p[i].strength<preqpb(p[i].x,10,p[i].x,p[i].y)){//save pass
                                         int l=0;
                                             for(j=0;j<10;j++)
                                             save_pass[j]=-1;
                                             for(j=ol;j<=oh;j++)
                                             {
                                                                if((preqpb(p[j].x,p[j].y,p[i].x,p[i].y)>=p[i].strength) && (p[j].x>=p[i].x))
                                                                {
                                                                    k=traj(p[j].x,p[j].y,p[i].x,p[i].y,p);
                                                                    if(k!=-1)
                                                                    {
                                                                             savepass(save_pass,l,p[i].x,p[i].y,p[j].x,p[j].y,p);
                                                                             l++;
                                                                    }
                                                                }
                                             }
                                             return -1;
                                    }                      
                                    
                           }
              }
              else if(p[i].y>40)
              {
                   if(p[i].x<86)//region 3
                   {
                                         if(p[i].strength>=preqpb(86,10,p[i].x,p[i].y))
                                         {
                                                                                       x=traj(86,40,p[i].x,p[i].y,p);
                                                                                       if(x!=-1){
                                                                                       j=max_strength(x,40,p);
                                                                                      if(j!=-1)
                                                                                      {
                                                                                               p[j].x=x;
                                                                                               p[j].y=40;
                                                                                               return -1;
                                                                                      }
                                                                                      if(j==-1)
                                                                                      {
                                                                                               return -1;
                                                                                      }
                                                                                      }
                                                                                      else
                                                                                      return -1;
                                         }
                                         else{//save pass
                                              int l=0;
                                             for(j=0;j<10;j++)
                                             save_pass[j]=-1;
                                             for(j=ol;j<=oh;j++)
                                             {
                                                                if((preqpb(p[j].x,p[j].y,p[i].x,p[i].y)>=p[i].strength) && (p[j].x>=p[i].x))
                                                                {
                                                                    k=traj(p[j].x,p[j].y,p[i].x,p[i].y,p);
                                                                    if(k!=-1)
                                                                    {
                                                                             savepass(save_pass,l,p[i].x,p[i].y,p[j].x,p[j].y,p);
                                                                             l++;
                                                                    }
                                                                }
                                             }
                                             return -1;
                                         }
                   }
                   else{//region 5
                   if(p[i].strength>=preqpb(p[i].x,40,p[i].x,p[i].y))
                                    {
                                         for(j=0;j<3;j++)
                                         save_goal[j]=-1;
                                         
                                         t=savegoal(save_goal,0,p[i].x-1,p[i].y-1,p);
                                         if(t!=-1)
                                         {
                                                  p[t].x=p[i].x-1;
                                                  p[t].y=p[i].y-1;
                                         }                                                                                      
                                         t=savegoal(save_goal,1,p[i].x,p[i].y-1,p);
                                         if(t!=-1)
                                         {
                                                  p[t].x=p[i].x;
                                                  p[t].y=p[i].y-1;
                                         }
                                         t=savegoal(save_goal,2,p[i].x+1,p[i].y-1,p); 
                                         if(t!=-1)
                                         {
                                                  p[t].x=p[i].x+1;
                                                  p[t].y=p[i].y-1;
                                         }                      
                                         return -1;
                                    }
                                    if(p[i].strength<preqpb(p[i].x,40,p[i].x,p[i].y)){//save pass
                                    int l=0;
                                             for(j=0;j<10;j++)
                                             save_pass[j]=-1;
                                             for(j=ol;j<=oh;j++)
                                             {
                                                                if((preqpb(p[j].x,p[j].y,p[i].x,p[i].y)>=p[i].strength) && (p[j].x>=p[i].x))
                                                                {
                                                                    k=traj(p[j].x,p[j].y,p[i].x,p[i].y,p);
                                                                    if(k!=-1)
                                                                    {
                                                                             savepass(save_pass,l,p[i].x,p[i].y,p[j].x,p[j].y,p);
                                                                             l++;
                                                                    }
                                                                }
                                             }
                                             return -1;
                                    }
                   }    
              }
              else{//region 2
                            if(p[i].strength>=preqpb(86,p[i].y,p[i].x,p[i].y))
                            {
                                         for(j=0;j<3;j++)
                                         save_goal[j]=-1;
                                         
                                         t=savegoal(save_goal,0,p[i].x+1,p[i].y-1,p);
                                         if(t!=-1)
                                         {
                                                  p[t].x=p[i].x+1;
                                                  p[t].y=p[i].y-1;
                                         }                                                                                      
                                         t=savegoal(save_goal,1,p[i].x+1,p[i].y,p);
                                         if(t!=-1)
                                         {
                                                  p[t].x=p[i].x+1;
                                                  p[t].y=p[i].y;
                                         }
                                         t=savegoal(save_goal,2,p[i].x+1,p[i].y+1,p); 
                                         if(t!=-1)
                                         {
                                                  p[t].x=p[i].x+1;
                                                  p[t].y=p[i].y+1;
                                         }
                            return -1;                                                  
                            }
                             if(p[i].strength<preqpb(86,p[i].y,p[i].x,p[i].y))
                           {//save_pass
                            int l=0;
                                             for(j=0;j<10;j++)
                                             save_pass[j]=-1;
                                             for(j=ol;j<=oh;j++)
                                             {
                                                                if((preqpb(p[j].x,p[j].y,p[i].x,p[i].y)>=p[i].strength) && (p[j].x>=p[i].x))
                                                                {
                                                                    k=traj(p[j].x,p[j].y,p[i].x,p[i].y,p);
                                                                    if(k!=-1)
                                                                    {
                                                                             savepass(save_pass,l,p[i].x,p[i].y,p[j].x,p[j].y,p);
                                                                             l++;
                                                                    }
                                                                }
                                             }
                                             return -1;
                            }
              }
    }
}//end of case2 func. defend

int traj(int finalx,int finaly,int inix,int iniy,struct player *p)
{
    int validx,validy;
    validx=inix;
    validy=iniy;
    do{
                if(validx!=finalx)
                                  finalx>inix?validx++:validx--;
                if(validy!=finaly)
                                  finaly>iniy?validy++:validy--;
                for(int j=pl;j<=ph;j++){
                        if((p[j].x==validx) && (p[j].y==validy))
                                            return -1;
                }
    }while((validx!=finalx) && (validy!=finaly));
    if(validx==finalx)
    return validx;
    else 
    return validy;
}

int max_strength(int x,int y,struct player *p)
{
    int px=-1,strleft,move_player=-1;
    for(int j=pl;j<=ph;j++)
    {
            strleft=p[j].strength-preqp(x,y,p[j].x,p[j].y);
            if(strleft>px){
                          px=strleft;
                          move_player=j;
            }
    }
    return move_player;
}
    
            





//definition of case3() func. //Neutral

//when ball is with no player

int case3(struct player * p)
{
	 int px=-1,move_player,strreq,i;
     for(int j=pl;j<=ph;j++)
     {
                 strreq=p[j].strength - preqp(p[0].x,p[0].y,p[j].x,p[j].y);
                 if(strreq>px)
                 {
                              px=strreq;
                              move_player=j;
                 }
     }
     if(px!=-1){
                p[move_player].x=p[0].x;
                p[move_player].y=p[0].y;
                i=case1(move_player,p);
                return i;
     }
     if(px==-1)
               return -1;
}
 // end of case3()
 
   int player( struct player *p)        //main player func 
{
	
	 int i,j,ball_player,a;     //ball_player is used to find which player is having the possession of the ball or whether the ball
	                             //is at empty slot
	  static int move=-1;
	  move++;
	  

	 //assigning limits according to player no.
	 if(player_no==1)
	 {

		pl=1;            //pl shows the lower limit and ph shows the upper limit of players in the array of structures ,i.e. if player
		ph=11; 
        ol=12;
        oh=22;          //is 1st then his players will be 1 to 11 and if he is 2nd then his players will be 12 to 22
		player_num=1;
	 }

	 else
	 {
		  pl=12;
		  ph=22;
		  ol=1;
		  oh=11;
		  player_num=2;
	 }
	 if(move==1)
	 {
                for(i=pl;i<=ph;i++)
                {
                                   if(p[i].x==60)
                                   p[i].x=40;
                                   else if(p[i].x==70)
                                   p[i].x+=15;
                                   else if(p[i].x==85 || p[i].x==75)
                                   p[i].x+=15;
                }
  }
   int largeh=-1;
	 for(i=pl;i<=ph;i++)
   { if( (p[0].x==p[i].x) &&( p[0].y==p[i].y) )
    {  printf("in loop");
        if(p[i].strength>largeh){
        ball_player=i;
        largeh=p[i].strength;
        }    
    }  }
     int largeo=-1;
	 for(i=ol;i<=oh;i++)
    if( p[0].x==p[i].x && p[0].y==p[i].y )
    {
        if(p[i].strength>largeo){
        ball_player=i;
        largeo=p[i].strength;
        }    
    }  printf("largeh=%d  largeo=%d",largeh,largeo);
  if(largeh>largeo){printf("with me");
                   a=case1(ball_player,p);printf("recieved from");
                   return a;
  }
  if(largeo>largeh){
      a=case2(ball_player,p);
      return a;
  }
  if(largeo==largeh)
  {
   a=case3(p);
   return a;
  }
}//end of player function

    
};   //end of the class team0002
