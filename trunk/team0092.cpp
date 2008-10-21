                          #include<stdio.h>

#include<stdlib.h>
#include<string.h>
#include<math.h>



using namespace std;

class team0092  //The name of your class should be teamxxxx where xxxx is the no. u will get at the time of registration and will
{                //be unique for every participant
  private:
  
  int team;  //team is a variable used in player function which tells all of the functions defined by the participant what their team no. is 
             //it is not mandatory for the player to use this variable .player can use any other means to satisfy the need
  //private fns 
  //this fn returns the strength req to move your player from one place to another 
  int preqp(int finalx,int finaly, int initialx ,int initialy )
	{float req;
    req=floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
    return (int)req;}     

//this fn returns the strength req by your hitter to move the ball from one place to another 
  int preqpb(int finalx,int finaly, int initialx ,int initialy )
	{float req; int i;
    req=2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	 i=req;
	 return i;} 
	 
int formcenter(int x, int y, int team, struct player *p)
{                          if(team==1)
                      {
                         p[8].x=x-1;
                         p[8].y=y-1;
                         p[4].x=x-1;
                         p[4].y=y;
                         p[9].x=x-1;
                         p[9].y=y+1;
                         p[5].x=x;
                         p[5].y=y+1;
                         p[2].x=x;
                         p[2].y=y;
                         p[6].x=x;
                         p[6].y=y-1;
                         p[3].x=x+1;
                         p[3].y=y-1;
                         p[10].x=x+1;
                         p[10].y=y;
                         p[7].x=x+1;
                         p[7].y=y+1;
                         
                         return 0;
                         }
                         
                         p[19].x=x-1;
                         p[19].y=y-1;
                         p[15].x=x-1;
                         p[15].y=y;
                         p[20].x=x-1;
                         p[20].y=y+1;
                         p[16].x=x;
                         p[16].y=y+1;
                         p[13].x=x;
                         p[13].y=y;
                         p[17].x=x;
                         p[17].y=y-1;
                         p[14].x=x+1;
                         p[14].y=y-1;
                         p[21].x=x+1;
                         p[21].y=y;
                         p[18].x=x+1;
                         p[18].y=y+1;
                        return 0; 
}//end of form centre  	
  public:
         
   int init(int team_number, struct player *p,char farray[][51])   // this fn must be there in your program ,it will be called only 
	{                                                             //once at the beginning of the program .It will tell u whether u are 
      team=team_number;                                 //player 1 or 2 and this will also give u the basic fieldarray ie where there is  
	}                                                  //a goal or a dee or a boundary and struct player *p gives u the initial player 
                                                 //distribution in the field
                                                 
    int player(struct player *p)  //This fn should contain the strategies u want to implement.You can also define other fns in your 
     {
                      int centerx, centery,strrem,large=0,tomove=-1,temp,reserve[200],done[20],d=0,b;
                      static int move=1,t=0;
                      if(team==1)
                      reserve[t]=11;
                      else
                      reserve[t]=22;
                      if(team==1&&move==1)
                      {
                         formcenter(60,5,1,p);                       
                         p[11].x=p[0].x;
                         p[11].y=p[0].y;
                         p[0].x=60;
                         p[0].y=5;
                         move++;
                         return 11;
                         }
                         if(team==1)//if control comes here than it is my 2nd or other move
                         {    
                             if(p[0].x!=60||p[0].y!=5)
                             {
                                  for(int i=1;i<=11;i++)
                                  if(p[i].x==p[0].x&&p[i].y==p[0].y)
                                  {  
                                     if(p[i].strength>=2)
                                     {
                                     p[0].x=60;
                                     p[0].y=5;
                                     return i;
                                     }
                                                 p[reserve[t]].x=p[0].x;
                                     p[reserve[t]].y=p[0].y;
                                     p[0].x=60;
                                     p[0].y=5;
                                     temp=reserve[t];
                                     t++;
                                     reserve[t]=i;
                                                                   return temp;
                                     }
                             }
                             
                             return -1;
                         }
                         
                         //if control comes here then i am team 2
                         
                         if(move==1)
                         {
                         
                         if(p[0].x==50&&p[0].y==25)
                         {
                         centerx=40;
                         centery=5;
                         p[19].x=41;
                         p[19].y=4;
                         p[15].x=41;
                         p[15].y=5;
                         p[20].x=41;
                         p[20].y=6;
                         p[16].x=40;
                         p[16].y=6;
                         p[13].x=40;
                         p[13].y=5;
                         p[17].x=40;
                         p[17].y=4;
                         p[14].x=39;
                         p[14].y=4;
                         p[21].x=39;
                         p[21].y=5;
                         p[18].x=39;
                         p[18].y=6;
                         p[22].x=p[0].x;
                         p[22].y=p[0].y;
                         p[0].x=40;
                         p[0].y=5;
                         move++;
                         return 22;
                         }
            
                               
                               //team 2, ball not in center, move1
                                /* if( (p[0].x!=60||p[0].y|=5) && move==2)
                             {
                                  for(int i=1;i<=11;i++)
                                  if(p[i].x==p[0].x&&p[i].y==p[0].y)
                                  {
                                     p[0].x=60;
                                     p[0].y=5;
                                     return i;
                                     }
                             }
                             if(move==2)
                             return -1;*/
                   
                   for(int j=12;j<=22;j++)
                   {
                           strrem=p[j].strength-preqp(p[0].x,p[0].y,p[j].x,p[j].y);
                           if(strrem>large)
                           {
                              large=strrem;
                              tomove=j;
                              }
                }
                
                
                
                if(large>=preqpb(40,5,p[0].x,p[0].y) )
                {
                   
                   p[tomove].x=p[0].x;
                   p[tomove].y=p[0].y;
                   p[0].x=40;
                   p[0].y=5;
                   t++;
                   reserve[t]=tomove;
                   
                   for(int g=39;g<=41;g++)
                   for(int h=4;h<=6;h++)
                   {
                      for(int k=12;k<=22;k++)
                     {
                      for(b=0;b<=d;b++)
                      if(k==done[b])
                      break;
                      if(k!=tomove&&b>d &&  (p[k].strength>=preqp(g,h,p[k].x,p[k].y) ))
                   {
                   
                   p[k].x=g;
                   p[k].y=h;
                   done[d]=k;
                   d++;
                   break;
                   }
                   }
                   }
                   
                   move++;      
                   return tomove;
                         
                         }
                         
                         if(large>=preqpb(40,45,p[0].x,p[0].y) )
                         {
                           p[tomove].x=p[0].x;
                   p[tomove].y=p[0].y;
                   p[0].x=40;
                   p[0].y=45;
                   t++;
                   reserve[t]=tomove;
                   
                   for(int g=39;g<=41;g++)
                   for(int h=44;h<=46;h++)
                   {
                      for(int k=12;k<=22;k++)
                     {
                      for(b=0;b<=d;b++)
                      if(k==done[b])
                      break;
                      if(k!=tomove&&b>d &&  (p[k].strength>=preqp(g,h,p[k].x,p[k].y) ))
                   {
                   
                   p[k].x=g;
                   p[k].y=h;
                   done[d]=k;
                   d++;
                   break;
                   }
                   }
                   }
                   
                   move++;      
                   return tomove;
}
                       return -1;
                         }// end of if(move==1)
                         
                         
                   //team 2 move 2
                   
                   
                   
                   
                                  if(p[0].x!=40||p[0].y!=5)
                                  {
                                  for(int i=12;i<=22;i++)
                                  if(p[i].x==p[0].x&&p[i].y==p[0].y)
                                  {  
                                                                    
                                     if(p[i].strength>=2)
                                     {                               
                                     p[0].x=40;
                                     p[0].y=5;
                                     return i;
                                     }
                                     
                                      
                                     p[reserve[t]].x=p[0].x;
                                     p[reserve[t]].y=p[0].y;
                                     p[0].x=40;
                                     p[0].y=5;
                                     temp=reserve[t];
                                     t++;
                                     reserve[t]=i;
                                     
                                     
                                     return temp;

                                     }

                                     }
                                     return -1;
                              
       }                          //contain the positions of the 22 players and the ball at that time .It is also supposed to return the 
                                 //the no of the player who will hit the ball to the controller fn
};//end of class  
