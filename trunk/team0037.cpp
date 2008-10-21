#include<cstdio>
#include<cstdlib>
#include<string>
#include<math.h>
#include<climits>
#include<iostream>
using namespace std;
typedef struct player Player;
void play(struct player*,int);
void make_circle(struct player*,int*,int,int,int,int,int);
void make_ball_circle(struct player,int,int*,int);
void search_max(int*,int*,int*,int*);
void run_to_pos(struct player*,int*,int,int,int,int);
void defence(struct player*,int);
int is_fielder(int,int,int,int,struct player*,int,int);
/*int preqp(int,int,int,int);
int preqpb(int,int,int,int);
*/
void play_fast(struct player*,int);

class team0037  //The name of your class should be teamxxxx where xxxx is the no. u will get at the time of registration and will
{                //be unique for every participant
  private:
  
  int team;  //team is a variable used in player function which tells all of the functions defined by the participant what their team no. is 
             //it is not mandatory for the player to use this variable .player can use any other means to satisfy the need
	 //this fn controls the defenders
  
 void mid_fielder(Player *p,int team_indicator);
 // this function controls the strikers
 void striker(Player *p,int team_indicator); 
 
   public:
         
   int init(int team_number, struct player *p,char farray[][51]);   // this fn must be there in your program ,it will be called only 
	                                                            //once at the beginning of the program .It will tell u whether u are 
                                                            //player 1 or 2 and this will also give u the basic fieldarray ie where there is  
	                                                 //a goal or a dee or a boundary and struct player *p gives u the initial player 
  
                                            //distribution in the field
  //this fn returns the strength req to move your player from one place to another 
  int preqp(int finalx,int finaly, int initialx ,int initialy ); 

//this fn returns the strength req by your hitter to move the ball from one place to another 
  int preqpb(int finalx,int finaly, int initialx ,int initialy );	
                                            
    int player(struct player *p);  //This fn should contain the strategies u want to implement.You can also define other fns in your 
                                  //class but u can call them with this fn only .This fn has to receive the array of 23 structures from the controller fn which 
                                 //contain the positions of the 22 players and the ball at that time .It is also supposed to return the 
                                 //the no of the player who will hit the ball to the controller fn
    /* int player(struct player *p)   
     {                       
     defence(p,team);
     moves++;
     return(player_hit);
     }
     include this in final code
*/                              
};//end of class

int player_hit=-1;
bool ball_hit=false;
int moves=0;
int team0037::preqp(int finalx,int finaly, int initialx ,int initialy )
{
    float req;
    req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
    return (int)req;
}

int team0037::preqpb(int finalx,int finaly, int initialx ,int initialy )
{
    float req; int i;
    req=(float)2*(floor(sqrt(pow(static_cast<float>(finalx-initialx),2)+pow(static_cast<float>(finaly-initialy),2))));
    i=(int)req;
    return i;
} 
        
int team0037::init(int team_number, Player *p,char farray[][51])
{
    team=team_number;
}
int team0037::player(Player *p)
{   player_hit=-1;
    ball_hit=false;
    int initial_ball_x=(*p).x,initial_ball_y=(*p).y;
    defence(p,team);
    if(initial_ball_x==(*p).x&&initial_ball_y==(*p).y)moves++;
    else moves=0;
    if(moves>=3)play_fast(p,team);
    
    mid_fielder(p,team);
     
    
    
    striker(p,team);
     
    return player_hit;
}
typedef struct
       {
               int ply;
               int x_cor;
       }our_striker;
static team0037 obj;
static bool inbetween(int x1,int y1,int xf,int yf,int xi,int yi);// to check whether the (x1,y1)
                                                                 // between (xi,yi) and (xf,yf)
static Player *check1(Player *,int);// whether ball is with my striker. returns my striker who has the ball
static string check2(Player *,int);// whether ball is in opponent's dee
                                // . returns true if thats the case                                   
static Player *check3(Player *,int);// whether ball is with opponent in his dee
                                // returns the opponent who has the ball if it is so. 
static void pos_yourself(Player *,int,int);// move strikers into position
                                       // without losing too much energy   
static void align_yourself(Player *,int);// align strikers to collect the ball
                                         // without losing too much energy  
static void move_yourself(Player *,int);// move strikers or ball appropiately
                                        // main goal : to score +10
                                        // secondary goals : to pass to inner striker
                                        //                  :to pass into vacant regions
                                        //                  : to move into better positions
static void pos_mid_yourself(Player *,int,int);// move strikers into position
                                       // without losing too much energy   
static void align_mid_yourself(Player *,int);// align strikers to collect the ball
                                         // without losing too much energy  
static void move_mid_yourself(Player *,int);// move strikers or ball appropiately
                                        // main goal : to score +10
                                        // secondary goals : to pass to inner striker
                                        //                  :to pass into vacant regions
                                        //                  : to move into better positions
static bool line(int finalx,int finaly,int intialx,int intialy,int,int,Player *);//check
                                           // whether there is a player between two points  
static void in_striker(Player *,Player *,int,int,int);// check whether it is possible to goal or to pass the ball 
                                             // to inner strikers 
static Player *max_energy(Player *p,int,int posx,int posy);// check which player has maximum energy after 
                                                        // reaching the position indicated by (posx,posy)                                                              
static Player *can_goal(Player *p,int,int posx,int posy,int,int);// call this fn only when your player has the ball in opponents dee
                                       // returns the player who can score from this position
void insert_sort(our_striker a[],int); // insertion sort in decreasing order
static Player *check_mid_1(Player *p,int team_indicator);
static void in_mid_fielder(Player *player,Player *p,int team_indicator,int strength,int opp_ply);
static Player *max_mid_strength(Player *p,int team_indicator,int posx,int posy);
static Player *can_pass(Player *p,int team_indicator,int posx,int posy,int strength,int opp_ply);
static void check_pos(Player *p,int team_indicator,int);
static void hit_out( Player *p,int team_indicator,int posx,int posy,int strength,int opp_ply);
void insert_sort(our_striker a[],int size)
{
     int small,key;
     for(int i=1;i<size;i++)
     {  int j;
             small=a[i].x_cor;
             key=a[i].ply;
             j=i-1;
             while(j>=0&&a[j].x_cor<small)
             { a[j+1].x_cor=a[j].x_cor;
               a[j+1].ply=a[j].ply;
               j--;
             }
             a[j+1].x_cor=small;
             a[j+1].ply=key;
             
             
     }
}
static bool line(int finalx,int finaly,int initialx,int initialy,int player1,int player2,int player3,Player *p)
{
       for(int i=1;i<23;i++)
       {       if(p[i].x==finalx&&p[i].y==finaly)
               continue;
               if(p[i].x==initialx&&p[i].y==initialy)
               continue;
               if(i!=player1&&i!=player2&&i!=player3)
               {      if(finalx!=initialx)
               {
               if(((p[i].y-finaly)==(((finaly - initialy)*(p[i].x-finalx))/(finalx-initialx)))&&inbetween(p[i].x,p[i].y,finalx,finaly,initialx,initialy))

               return true;
               }
               else
               {
                   if(p[i].x==finalx&&inbetween(p[i].x,p[i].y,finalx,finaly,initialx,initialy))

                   return true;
               }
               }
       }
       return false;
}
static void check_pos(Player *p,int team_indicator,int indicate)
{
      bool flag=false;
      int str_req,y_diff,x_diff,count=11,x,y;
       float distance;
       Player *ptr;
       
       if(team_indicator==1)
       {            ptr=check1(p,team_indicator);
                            // first striker
                    if(ptr!=NULL)
                    {
                    if(!(ptr->x==p[8].x&&ptr->y==p[8].y)||flag)
                    {str_req=obj.preqp(67,8,p[8].x,p[8].y);
                    if(p[8].strength-str_req>=indicate)
                    {
                                                 p[8].x=67;
                                                 p[8].y=8;
                    }
                    else
                    {
                        while(p[8].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=8-p[8].y;
                          x_diff=67-p[8].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((p[8].x+((count*x_diff)/distance))),static_cast<int>((p[8].y+((count*y_diff)/distance))),p[8].x,p[8].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {x=p[8].x;
                    y=p[8].y;
                    p[8].x=static_cast<int>(p[8].x+((count*x_diff)/distance));
                    p[8].y=static_cast<int>(p[8].y+((count*y_diff)/distance));
                    p[8].strength-=obj.preqp(p[8].x,p[8].y,x,y);
                    }
                    }
                    flag=true;
                    }
                     if(!(ptr->x==p[9].x&&ptr->y==p[9].y)||flag)
                    {// second striker
                    count=11;
                    str_req=obj.preqp(62,25,p[9].x,p[9].y);
                    if(p[9].strength-str_req>=indicate)
                    {
                                                 p[9].x=62;
                                                 p[9].y=25;
                    }
                    else
                    {
                        while(p[9].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[9].y;
                          x_diff=62-p[9].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[9].x+((count*x_diff)/distance)),static_cast<int>(p[9].y+((count*y_diff)/distance)),p[9].x,p[9].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    x=p[9].x;
                    y=p[9].y;
                    p[9].x=static_cast<int>(p[9].x+((count*x_diff)/distance));
                    p[9].y=static_cast<int>(p[9].y+((count*y_diff)/distance));
                    p[9].strength-=obj.preqp(p[9].x,p[9].y,x,y);
                    }
                    }
                    flag=true;
                    }
                     if(!(ptr->x==p[10].x&&ptr->y==p[10].y)||flag)
                    { // third striker
                    count=11;
                    str_req=obj.preqp(67,40,p[10].x,p[10].y);
                    if(p[10].strength-str_req>=indicate)
                    {
                                                 p[10].x=67;
                                                 p[10].y=40;
                    }
                    else
                    {
                        while(p[10].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=40-p[10].y;
                          x_diff=67-p[10].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[10].x+((count*x_diff)/distance)),static_cast<int>(p[10].y+((count*y_diff)/distance)),p[10].x,p[10].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {x=p[10].x;
                    y=p[10].y;
                    p[10].x=static_cast<int>(p[10].x+((count*x_diff)/distance));
                    p[10].y=static_cast<int>(p[10].y+((count*y_diff)/distance));
                     p[10].strength-=obj.preqp(p[10].x,p[10].y,x,y);
                    } 
                    } 
                    flag=true;
                    }
                     if(!(ptr->x==p[11].x&&ptr->y==p[11].y)||flag)
                     {
                     // fourth striker
                    count=11;
                    str_req=obj.preqp(80,25,p[11].x,p[11].y);
                    if(p[11].strength-str_req>=indicate)
                    {
                                                 p[11].x=80;
                                                 p[11].y=25;
                    }
                    else
                    {
                        while(p[11].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[11].y;
                          x_diff=80-p[11].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[11].x+((count*x_diff)/distance)),static_cast<int>(p[11].y+((count*y_diff)/distance)),p[11].x,p[11].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {x=p[11].x;
                    y=p[11].y;
                    p[11].x=static_cast<int>(p[11].x+((count*x_diff)/distance));
                    p[11].y=static_cast<int>(p[11].y+((count*y_diff)/distance));
                    p[11].strength-=obj.preqp(p[11].x,p[11].y,x,y);
                    
                    }
                    } 
         
                    }  
                    }
                    else
                    {                    // first striker
                    str_req=obj.preqp(67,8,p[8].x,p[8].y);
                    if(p[8].strength-str_req>=indicate)
                    {
                                                 p[8].x=67;
                                                 p[8].y=8;
                    }
                    else
                    {
                        while(p[8].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=8-p[8].y;
                          x_diff=67-p[8].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((p[8].x+((count*x_diff)/distance))),static_cast<int>((p[8].y+((count*y_diff)/distance))),p[8].x,p[8].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[8].x=static_cast<int>(p[8].x+((count*x_diff)/distance));
                    p[8].y=static_cast<int>(p[8].y+((count*y_diff)/distance));
                    }
                    }
                    
                    // second striker
                    count=11;
                    str_req=obj.preqp(62,25,p[9].x,p[9].y);
                    if(p[9].strength-str_req>=indicate)
                    {
                                                 p[9].x=62;
                                                 p[9].y=25;
                    }
                    else
                    {
                        while(p[9].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[9].y;
                          x_diff=62-p[9].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[9].x+((count*x_diff)/distance)),static_cast<int>(p[9].y+((count*y_diff)/distance)),p[9].x,p[9].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[9].x=static_cast<int>(p[9].x+((count*x_diff)/distance));
                    p[9].y=static_cast<int>(p[9].y+((count*y_diff)/distance));
                    }
                    }
                     // third striker
                    count=11;
                    str_req=obj.preqp(67,40,p[10].x,p[10].y);
                    if(p[10].strength-str_req>=indicate)
                    {
                                                 p[10].x=67;
                                                 p[10].y=40;
                    }
                    else
                    {
                        while(p[10].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=40-p[10].y;
                          x_diff=67-p[10].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[10].x+((count*x_diff)/distance)),static_cast<int>(p[10].y+((count*y_diff)/distance)),p[10].x,p[10].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[10].x=static_cast<int>(p[10].x+((count*x_diff)/distance));
                    p[10].y=static_cast<int>(p[10].y+((count*y_diff)/distance));
                    } 
                    } 
                     // fourth striker
                    count=11;
                    str_req=obj.preqp(80,25,p[11].x,p[11].y);
                    if(p[11].strength-str_req>=indicate)
                    {
                                                 p[11].x=80;
                                                 p[11].y=25;
                    }
                    else
                    {
                        while(p[11].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[11].y;
                          x_diff=80-p[11].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[11].x+((count*x_diff)/distance)),static_cast<int>(p[11].y+((count*y_diff)/distance)),p[11].x,p[11].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[11].x=static_cast<int>(p[11].x+((count*x_diff)/distance));
                    p[11].y=static_cast<int>(p[11].y+((count*y_diff)/distance));
                    }
                    }    
                    
                    }  
                    }  
             if(team_indicator==2)
             {
                    ptr=check1(p,team_indicator);
                    if(ptr!=NULL)
                    {
                    if(!(ptr->x==p[19].x&&ptr->y==p[19].y)||flag)
                    {
                    // first striker]
                    count=11;
                    str_req=obj.preqp(33,8,p[19].x,p[19].y);
                    if(p[8].strength-str_req>=indicate)
                    {
                                                 p[19].x=33;
                                                 p[19].y=8;
                    }
                    else
                    {
                        while(p[19].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=8-p[19].y;
                          x_diff=33-p[19].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[19].x+((count*x_diff)/distance)),static_cast<int>(p[19].y+((count*y_diff)/distance)),p[19].x,p[19].y);
                          count--;
                    }
                    if(count!=-1)
                    {x=p[19].x;
                    y=p[19].y;
                    p[19].x=static_cast<int>(p[19].x+((count*x_diff)/distance));
                    p[19].y=static_cast<int>(p[19].y+((count*y_diff)/distance));
                    
                     p[19].strength-=obj.preqp(p[19].x,p[19].y,x,y);
                     }
                    }
                    flag=true;
                    }
                    if(!(ptr->x==p[20].x&&ptr->y==p[20].y)||flag)
                    
                   { // second striker
                    count=11;
                    str_req=obj.preqp(38,25,p[20].x,p[20].y);
                    if(p[20].strength-str_req>=indicate)
                    {
                                                 p[20].x=38;
                                                 p[20].y=25;
                    }
                    else
                    {
                        while(p[20].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[20].y;
                          x_diff=38-p[20].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[20].x+((count*x_diff)/distance)),static_cast<int>(p[20].y+((count*y_diff)/distance)),p[20].x,p[20].y);
                          count--;
                    }
                    if(count!=-1)
                    {x=p[20].x;
                    y=p[20].y;
                    p[20].x=static_cast<int>(p[20].x+((count*x_diff)/distance));
                    p[20].y=static_cast<int>(p[20].y+((count*y_diff)/distance));
                    p[20].strength-=obj.preqp(p[20].x,p[20].y,x,y);
                    }
                    }
                    flag=true;
                    }
                    if(!(ptr->x==p[21].x&&ptr->y==p[21].y)||flag)
                    {
                     // third striker
                    count=11;
                    str_req=obj.preqp(33,40,p[21].x,p[21].y);
                    if(p[21].strength-str_req>=indicate)
                    {
                                                 p[21].x=33;
                                                 p[21].y=40;
                    }
                    else
                    {
                        while(p[21].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=40-p[21].y;
                          x_diff=33-p[21].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[21].x+((count*x_diff)/distance)),static_cast<int>(p[21].y+((count*y_diff)/distance)),p[21].x,p[21].y);
                          count--;
                    }
                    if(count!=-1)
                    {x=p[21].x;
                    y=p[21].y;
                    p[21].x=static_cast<int>(p[21].x+((count*x_diff)/distance));
                    p[21].y=static_cast<int>(p[21].y+((count*y_diff)/distance));
                    p[21].strength-=obj.preqp(p[21].x,p[21].y,x,y);
                    }  
                    }
                    flag=true;
                    }
                    if(!(ptr->x==p[22].x&&ptr->y==p[22].y)||flag)
                    {
                     // fourth striker
                    count=11;
                    str_req=obj.preqp(20,25,p[22].x,p[22].y);
                    if(p[22].strength-str_req>=indicate)
                    {
                                                 p[22].x=20;
                                                 p[22].y=25;
                    }
                    else
                    {
                        while(p[22].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[22].y;
                          x_diff=20-p[22].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[22].x+((count*x_diff)/distance)),static_cast<int>(p[22].y+((count*y_diff)/distance)),p[22].x,p[22].y);
                          count--;
                    }
                    if(count!=-1)
                    {x=p[22].x;
                    y=p[22].y;
                    p[22].x=static_cast<int>(p[22].x+((count*x_diff)/distance));
                    p[22].y=static_cast<int>(p[22].y+((count*y_diff)/distance));
                    p[22].strength-=obj.preqp(p[22].x,p[22].y,x,y);
                    }
                    }  
                    }  
                    }
                    else
                    pos_yourself(p,team_indicator,indicate);
                    
                    }
}                                            
static bool inbetween(int x1,int y1,int xf,int yf,int xi,int yi)
{
       if(xf>=xi&&yf>=yi)
       {              
                       if(x1>=xi&&x1<=xf&&y1>=yi&&y1<=yf)
                       return true;
       }
       if(xf>=xi&&yi>=yf)
       {
                         if(x1>=xi&&x1<=xf&&y1>=yf&&y1<=yi)
                         return true;
       }
       if(xf<=xi&&yi>=yf)
       {
                         if(x1>=xf&&x1<=xi&&y1>=yf&&y1<=yi)
                         return true;
       }
       if(xf<=xi&&yf>=yi)
       {
                         if(x1>=xf&&x1<=xi&&y1>=yi&&y1<=yf)
                         return true;
       }
       return false;
}
                         
       
               
static Player *check1(Player *p,int team_indicator)
{   int large=INT_MIN;
    Player *ply;
       if(team_indicator==1)
       {
                            for(int i=0;i<4;i++)
                            if(p[0].x==p[i+8].x&&p[0].y==p[i+8].y&&p[8+i].strength>large)
                            {large=p[8+i].strength;
                            ply=p+i+8;
                            }
                            if(large!=INT_MIN)
                            return ply;
       }
       if(team_indicator==2)
       {
                            for(int i=0;i<4;i++)
                            if(p[0].x==p[i+19].x&&p[0].y==p[i+19].y&&p[19+i].strength>large)
                            {large=p[19+i].strength;
                            ply=p+i+19;
                            }
                            if(large!=INT_MIN)
                            return ply;
                            
       }
       return NULL;
}
static string check2(Player *p,int team_indicator)
{    
       if(team_indicator==1)
       {

                            if(p[0].x>60)
                            return "striker";
                            if(p[0].x<=60&&p[0].x>=40)
                            return "mid fielder";

       }
       if(team_indicator==2)
       {
       
                            if(p[0].x<40)
                            return "striker";
                            if(p[0].x<=60&&p[0].x>=40)
                            return "mid fielder";
       }
       return "defender";
}
static Player *check3(Player *p,int team_indicator)
{   int large=INT_MIN;
    Player *ply;
       if(team_indicator==1)
       {
                            for(int i=0;i<11;i++) 
                            if(p[12+i].x==p[0].x&&p[12+i].y==p[0].y&&p[12+i].strength>large)
                            {large=p[12+i].strength;
                            ply=p+i+12;
                            }
                            if(large!=INT_MIN)
                            return ply;
       }                                                        
       if(team_indicator==2)
       {
                            for(int i=0;i<11;i++)
                            if(p[i+1].x==p[0].x&&p[i+1].y==p[0].y&&p[1+i].strength>large)
                            {large=p[1+i].strength;
                            ply=p+i+1;
                            }
                            if(large!=INT_MIN)
                            return ply;
       }
       return NULL;
}
static void pos_yourself(Player *p,int team_indicator,int indicate)
{      int str_req,y_diff,x_diff,count=11;
       float distance;
       
       if(team_indicator==1)
       {                    // first striker
                    str_req=obj.preqp(67,8,p[8].x,p[8].y);
                    if(p[8].strength-str_req>=indicate)
                    {
                                                 p[8].x=67;
                                                 p[8].y=8;
                    }
                    else
                    {
                        while(p[8].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=8-p[8].y;
                          x_diff=67-p[8].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((p[8].x+((count*x_diff)/distance))),static_cast<int>((p[8].y+((count*y_diff)/distance))),p[8].x,p[8].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[8].x=static_cast<int>(p[8].x+((count*x_diff)/distance));
                    p[8].y=static_cast<int>(p[8].y+((count*y_diff)/distance));
                    }
                    }
                    
                    // second striker
                    count=11;
                    str_req=obj.preqp(62,25,p[9].x,p[9].y);
                    if(p[9].strength-str_req>=indicate)
                    {
                                                 p[9].x=62;
                                                 p[9].y=25;
                    }
                    else
                    {
                        while(p[9].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[9].y;
                          x_diff=62-p[9].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[9].x+((count*x_diff)/distance)),static_cast<int>(p[9].y+((count*y_diff)/distance)),p[9].x,p[9].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[9].x=static_cast<int>(p[9].x+((count*x_diff)/distance));
                    p[9].y=static_cast<int>(p[9].y+((count*y_diff)/distance));
                    }
                    }
                     // third striker
                    count=11;
                    str_req=obj.preqp(67,40,p[10].x,p[10].y);
                    if(p[10].strength-str_req>=indicate)
                    {
                                                 p[10].x=67;
                                                 p[10].y=40;
                    }
                    else
                    {
                        while(p[10].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=40-p[10].y;
                          x_diff=67-p[10].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[10].x+((count*x_diff)/distance)),static_cast<int>(p[10].y+((count*y_diff)/distance)),p[10].x,p[10].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[10].x=static_cast<int>(p[10].x+((count*x_diff)/distance));
                    p[10].y=static_cast<int>(p[10].y+((count*y_diff)/distance));
                    } 
                    } 
                     // fourth striker
                    count=11;
                    str_req=obj.preqp(80,25,p[11].x,p[11].y);
                    if(p[11].strength-str_req>=indicate)
                    {
                                                 p[11].x=80;
                                                 p[11].y=25;
                    }
                    else
                    {
                        while(p[11].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[11].y;
                          x_diff=80-p[11].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[11].x+((count*x_diff)/distance)),static_cast<int>(p[11].y+((count*y_diff)/distance)),p[11].x,p[11].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[11].x=static_cast<int>(p[11].x+((count*x_diff)/distance));
                    p[11].y=static_cast<int>(p[11].y+((count*y_diff)/distance));
                    }
                    }    
                    
                    }  
             if(team_indicator==2)
             {
                    // first striker]
                    count=11;
                    str_req=obj.preqp(33,8,p[19].x,p[19].y);
                    if(p[19].strength-str_req>=indicate)
                    {
                                                 p[19].x=33;
                                                 p[19].y=8;
                    }
                    else
                    {
                        while(p[19].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=8-p[19].y;
                          x_diff=33-p[19].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[19].x+((count*x_diff)/distance)),static_cast<int>(p[19].y+((count*y_diff)/distance)),p[19].x,p[19].y);
                          count--;
                    }
                    if(count!=-1)
                    {
                    p[19].x=static_cast<int>(p[19].x+((count*x_diff)/distance));
                    p[19].y=static_cast<int>(p[19].y+((count*y_diff)/distance));
                    }
                    }
                    
                    // second striker
                    count=11;
                    str_req=obj.preqp(38,25,p[20].x,p[20].y);
                    if(p[20].strength-str_req>=indicate)
                    {
                                                 p[20].x=38;
                                                 p[20].y=25;
                    }
                    else
                    {
                        while(p[20].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[20].y;
                          x_diff=38-p[20].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[20].x+((count*x_diff)/distance)),static_cast<int>(p[20].y+((count*y_diff)/distance)),p[20].x,p[20].y);
                          count--;
                    }
                    if(count!=-1)
                    {
                    p[20].x=static_cast<int>(p[20].x+((count*x_diff)/distance));
                    p[20].y=static_cast<int>(p[20].y+((count*y_diff)/distance));
                    }
                    }
                     // third striker
                    count=11;
                    str_req=obj.preqp(33,40,p[21].x,p[21].y);
                    if(p[21].strength-str_req>=indicate)
                    {
                                                 p[21].x=33;
                                                 p[21].y=40;
                    }
                    else
                    {
                        while(p[21].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=40-p[21].y;
                          x_diff=33-p[21].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[21].x+((count*x_diff)/distance)),static_cast<int>(p[21].y+((count*y_diff)/distance)),p[21].x,p[21].y);
                          count--;
                    }
                    if(count!=-1)
                    {
                    p[21].x=static_cast<int>(p[21].x+((count*x_diff)/distance));
                    p[21].y=static_cast<int>(p[21].y+((count*y_diff)/distance));
                    }  
                    }
                     // fourth striker
                    count=11;
                    str_req=obj.preqp(20,25,p[22].x,p[22].y);
                    if(p[22].strength-str_req>=indicate)
                    {
                                                 p[22].x=20;
                                                 p[22].y=25;
                    }
                    else
                    {
                        while(p[22].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[22].y;
                          x_diff=20-p[22].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[22].x+((count*x_diff)/distance)),static_cast<int>(p[22].y+((count*y_diff)/distance)),p[22].x,p[22].y);
                          count--;
                    }
                    if(count!=-1)
                    {
                    p[22].x=static_cast<int>(p[22].x+((count*x_diff)/distance));
                    p[22].y=static_cast<int>(p[22].y+((count*y_diff)/distance));
                    }
                    }    
                    
                    }
}                                                                       
static void align_yourself(Player *p,int team_indicator)
{ int str_req,x_diff,y_diff,count=11;
  float distance;
         if(team_indicator==1)
         { for(int i=0;i<2;i++)
          {        
                   count=11;
                   str_req=obj.preqp(0,p[0].y,0,p[8+i].y);
                  
                   if(p[0].y<=(16+16*i)&&p[0].y>(16*i))
                   {if(p[8+i].strength-str_req>=40)
                   {
                       p[8+i].y=p[0].y;
                   }
                   else
                   {
                    while(p[8+i].strength-str_req<40&&count>-1)
                        {
                          y_diff=p[0].y-p[8+i].y;
                          x_diff=0;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(((count*x_diff)/distance)),static_cast<int>(p[8+i].y+((count*y_diff)/distance)),0,p[8+i].y);
                         
                          count--;
                    }
                    if(count!=-1)
                    {
                    p[8+i].x=static_cast<int>(p[8+i].x+(count*x_diff)/distance);
                    p[8+i].y=static_cast<int>(p[8+i].y+((count*y_diff)/distance));
                   
                    } 
                    }
                   }
                   }
                   count =11;
                   str_req=obj.preqp(0,p[0].y,0,p[10].y);
                   if(p[0].y<=49&&p[0].y>32)
                   {
                    if(p[10].strength - str_req>=40)
                    {
                                      p[10].y=p[0].y;
                    }
                    else
                    {
                        while(p[10].strength - str_req<40&&count>-1)
                        {
                          y_diff=p[0].y-p[10].y;
                          x_diff=0;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((count*x_diff)/distance),static_cast<int>(p[10].y+((count*y_diff)/distance)),0,p[10].y);                                          
                          count--;
                    }
                    {
                    if(count!=-1)
                                 p[10].x=static_cast<int>(p[10].x+(count*x_diff)/distance);
                                 p[10].y=static_cast<int>(p[10].y + ((count*y_diff)/distance));
                    }
                    }
                             
          } 
          }
          if(team_indicator==2)
          {
            for(int i=0;i<2;i++)
          {        count=11;
                   str_req=obj.preqp(0,p[0].y,0,p[19+i].y);
                   if(p[0].y<=(16+16*i)&&p[0].y>(16*i))
                   {if(p[19+i].strength-str_req>=40)
                   {
                       p[19+i].y=p[0].y;
                   }
                   else
                   {
                    while(p[19+i].strength-str_req<40&&count>-1)
                        {
                          y_diff=p[0].y-p[19+i].y;
                          x_diff=0;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(((count*x_diff)/distance)),static_cast<int>(p[19+i].y+((count*y_diff)/distance)),0,p[19+i].y);
                          count--;
                    }
                    if(count!=-1)
                    {
                    p[19+i].x=static_cast<int>(p[19+i].x+(count*x_diff)/distance);
                    p[19+i].y=static_cast<int>(p[19+i].y+((count*y_diff)/distance));
                    } 
                    }
                   }
                   }                   
                    count =11;
                   str_req=obj.preqp(0,p[0].y,0,p[21].y);
                   if(p[0].y<=49&&p[0].y>32)
                   {
                    if(p[21].strength - str_req>=40)
                    {
                                      p[21].y=p[0].y;
                    }
                    else
                    {
                        while(p[21].strength - str_req<40&&count>-1)
                        {
                          y_diff=p[0].y-p[21].y;
                          x_diff=0;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((count*x_diff)/distance),static_cast<int>(p[21].y+((count*y_diff)/distance)),0,p[21].y);                                          
                          count--;
                    }
                    {
                    if(count!=-1)
                                 p[21].x=static_cast<int>(p[21].x+(count*x_diff)/distance);
                                 p[21].y=static_cast<int>(p[21].y + ((count*y_diff)/distance));
                    }
                    }
                             
          } 
          } 
}
static Player *max_strength(Player *p,int team_indicator,int posx,int posy)
{int str_req,large=INT_MIN,player;
 
       if(team_indicator==1)
       {
          for(int i=0;i<4;i++)
          {
                          str_req=obj.preqp(posx,posy,p[i+8].x,p[8+i].y);
                          
                          if((p[i+8].strength-str_req)>large&&(p[i+8].strength-str_req)>0)
                          {large=p[i+8].strength-str_req;
                          player = 8+i;
                          }
                           
          }  
          
          return p+player;
          }
         if(team_indicator==2)
         {
            for(int i=0;i<4;i++)
            {
                     str_req=obj.preqp(posx,posy,p[19+i].x,p[19+i].y);
                     if((p[i+19].strength-str_req)>large&&(p[i+19].strength-str_req)>0)
                     {
                     large=p[i+19].strength-str_req;
                     player=19+i;
                     }
                     
            }
            return p+player;
            }
         return NULL;
}
 static Player *can_goal(Player *p,int team_indicator,int posx,int posy,int strength,int opp_ply)
 {    int str_req,farthest=INT_MIN,far_player,x_diff,y_diff;
       float distance;
       if(team_indicator==1)
       {              // the case when the striker in possestion of ball has a possibility to score
                            for(int k=0;k<4;k++)
                            for(int i=14;i>0;i--)
                            for(int j=40;j>9;j--)
                            {
                             str_req=obj.preqpb(posx,posy,p[8+k].x,p[8+k].y);
                             
                            
                                    
                            str_req+=obj.preqpb(85+i,j,posx,posy);
                            str_req+=strength;
                           
                            
                            if(str_req<p[8+k].strength&&!line(85+i,j,p[8+k].x,p[8+k].y,8+k,0,opp_ply,p))
                            {    
                                 p[0].x=i+85;
                                 p[0].y=j;
                                 p[8+k].x=posx;
                                 p[8+k].y=posy;
                                 ball_hit=true;
                                 player_hit=8+k;
                                 pos_yourself(p,team_indicator,0);
                                 pos_mid_yourself(p,team_indicator,0);
                                 return p+player_hit;   
                            }
                            }
       }
      
       if(team_indicator==2)
       {
                            // the case when the striker in possestion of ball has a possibility to score
                            for(int k=0;k<4;k++)
                            for(int i=14;i>0;i--)
                            for(int j=40;j>9;j--)
                            {
                             str_req=obj.preqpb(posx,posy,p[19+k].x,p[19+k].y);
                                    
                            str_req+=obj.preqpb(i,j,posx,posy);
                            str_req+=strength;
                            
                            if(str_req<p[19+k].strength&&!line(i,j,p[19+k].x,p[19+k].y,19+k,0,opp_ply,p))
                            {     
                                
                                 
                                 p[0].x=i;
                                 p[0].y=j;
                                 p[19+k].x=posx;
                                 p[19+k].y=posy;
                                 ball_hit=true;
                                 player_hit=19+k;
                                 pos_yourself(p,team_indicator,0);
                                 pos_mid_yourself(p,team_indicator,0);
                                 return p+player_hit;   
                            }
                            }
       }
        return NULL; 
}           
static void hit_out( Player *p,int team_indicator,int posx,int posy,int strength,int opp_ply)
{
       int str_req,farthest=INT_MIN,large=INT_MIN,far_player,x_diff,y_diff,player;
       float distance;
       Player *obj_ptr;
       if(team_indicator==1)
       {              // the case when the striker in possestion of ball has a possibility to score
       obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
       
        
       
       obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
       obj_ptr->x=p[0].x;
       obj_ptr->y=p[0].y;
       
       for(int i=8;i<12;i++)
       if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
       {if(p[i].strength>large)
       player=i;
    
       }   
                            for(int i=86;i>=p[i].x;i--)
                            for(int j=49;j>0;j--)
                            {
                             str_req=obj.preqpb(posx,posy,p[player].x,p[player].y);
                                    
                            str_req+=obj.preqpb(i,j,posx,posy);
                            str_req+=strength;
                            
                            if(str_req<p[player].strength&&!line(i,j,p[player].x,p[player].y,player,0,opp_ply,p))
                            {     
                                
                                 
                                 p[0].x=i;
                                 p[0].y=j;
                                 p[player].x=posx;
                                 p[player].y=posy;
                                 ball_hit=true;
                                 player_hit=player;
                                 goto label;
                                
                                 
                            }
                            }
       label:;
       
                 
       }
      
       if(team_indicator==2)
       {
                       /*     // the case when the striker in possestion of ball has a possibility to score
                            for(int k=0;k<4;k++)
                            for(int i=14;i<p[i].x;i++)
                            for(int j=49;j>0;j--)
                            {
                             str_req=obj.preqpb(posx,posy,p[19+k].x,p[19+k].y);
                                    
                            str_req+=obj.preqpb(i,j,posx,posy);
                            str_req+=strength;
                            
                            if(str_req<p[19+k].strength&&!line(i,j,p[19+k].x,p[19+k].y,19+k,0,opp_ply,p))
                            {     
                                
                                 
                                 p[0].x=i;
                                 p[0].y=j;
                                 p[19+k].x=posx;
                                 p[19+k].y=posy;
                                 ball_hit=true;
                                 player_hit=19+k;
                                
                                 
                            }
                            }
                            */
                      // the case when the striker in possestion of ball has a possibility to score
       obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
     
        
       
       obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
       obj_ptr->x=p[0].x;
       obj_ptr->y=p[0].y;
       for(int i=19;i<23;i++)
       if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
       {if(p[i].strength>large)
       player=i;
    
       }   
      
                            for(int i=14;i<=p[i].x;i++)
                            for(int j=49;j>0;j--)
                            {
                             str_req=obj.preqpb(posx,posy,p[player].x,p[player].y);
                                    
                            str_req+=obj.preqpb(i,j,posx,posy);
                            str_req+=strength;
                            
                            if(str_req<p[player].strength&&!line(i,j,p[player].x,p[player].y,player,0,opp_ply,p))
                            {     
                                
                                 
                                 p[0].x=i;
                                 p[0].y=j;
                                 p[player].x=posx;
                                 p[player].y=posy;
                                 ball_hit=true;
                                 player_hit=player;
                                 goto label1;
                                
                                 
                            }
                            }
       label1:;
                          
       }
        
        
}
             
                            
static void in_striker(Player *player,Player *p,int team_indicator,int strength,int opp_ply)
{
       int str_req,farthest=INT_MIN,x_diff,y_diff,temp;
       
       our_striker far_player[4];
       float distance;
       Player *ptr;
       if(team_indicator==1)
       {              // the case when the striker in possestion of ball has a possibility to score
                          if(!(ptr=can_goal(p,team_indicator,p[0].x,p[0].y,strength,opp_ply)))
                          
                      //  the general case : this striker passes the ball to a striker who is in best position
                      
                         {   
                              for(int i=0;i<4;i++)
                              {far_player[i].x_cor=p[8+i].x;
                              far_player[i].ply=8+i;
                              }
                             
                              insert_sort(far_player,4);
                              
                             int i=0;
                                                              
                          while(i!=4&&(p[far_player[i].ply].x!=(*player).x||p[far_player[i].ply].y!=(*player).y))
                              
                        { 
                          
                          str_req=obj.preqpb(p[far_player[i].ply].x,p[far_player[i].ply].y,player->x,player->y);
                          str_req+=strength;                                               
                          if(str_req<(*player).strength&&!(line(p[far_player[i].ply].x,p[far_player[i].ply].y,player->x,player->y,player-p,far_player[i].ply,opp_ply,p)))
                          {       
                                  p[0].x=p[far_player[i].ply].x;
                                  p[0].y=p[far_player[i].ply].y;
                                  ball_hit=true;
                                  player_hit=player-p;
                                  return;
                          }
                          else
                          {
                              if(!line(p[far_player[i].ply].x,p[far_player[i].ply].y,(*player).x,(*player).y,player-p,far_player[i].ply,opp_ply,p))
                              {
                                       
                                       x_diff=p[far_player[i].ply].x-(*player).x;
                                       y_diff=p[far_player[i].ply].y-(*player).y;
                                       distance= sqrt((x_diff*x_diff)+(y_diff*y_diff));
                                       str_req=0;
                                       int r=1;
                                      
                                       while(((*player).strength-str_req)>0&&((*player).x!=p[far_player[i].ply].x||(*player).y!=p[far_player[i].ply].y))
                                       { 
                                          str_req=obj.preqpb(static_cast<int>((*player).x+((x_diff*r)/distance)),static_cast<int>((*player).y+((y_diff*r)/distance)),(*player).x,(*player).y);
                                          str_req+=strength;
                                          r++;
                                       }  
                                      
                                        str_req=obj.preqp(static_cast<int>((*player).x+((x_diff*(r-2))/distance)),static_cast<int>((*player).y+((y_diff*(r-2))/distance)),p[far_player[i].ply].x,p[far_player[i].ply].y);
                                       if(r!=1&&p[far_player[i].ply].strength-str_req>0)
                                       {
                                               r=r-2;
                                               p[0].x=static_cast<int>((*player).x+((x_diff*r)/distance));                                                                                  
                                               p[0].y=static_cast<int>((*player).y+((y_diff*r)/distance));
                                               player_hit=player-p;
                                               ball_hit=true;
                                                p[far_player[i].ply].x=p[0].x;
                                                p[far_player[i].ply].y=p[0].y;
                                                return;
                                              
                                               
                                      }
                                      }
                                       
                                       
                                       
                                       
                              }
                            i++;
                         
                            }
                           
                            
                            hit_out(p,team_indicator,p[0].x,p[0].y,strength,opp_ply);
                              
                              }
                          }
        farthest=INT_MAX;
       if(team_indicator==2)
       {
                      // the case when the striker in possestion of ball has a possibility to score
                          if(!(ptr=can_goal(p,team_indicator,p[0].x,p[0].y,strength,opp_ply)))
                          
                      //  the general case : this striker passes te ball to a striker who is in best position
                      
                         {  
                              for(int i=0;i<4;i++)
                              {far_player[i].x_cor=p[19+i].x;
                              far_player[i].ply=19+i;
                              }
                             
                              insert_sort(far_player,4);
                             int i=3;
                             while(i!=-1&&p[far_player[i].ply].x!=(*player).x||p[far_player[i].ply].y!=(*player).y)
                          {
                          str_req=obj.preqpb(p[far_player[i].ply].x,p[far_player[i].ply].y,player->x,player->y);                                                                                         str_req=obj.preqpb(p[far_player[i].ply].x,p[far_player[i].ply].y,(*player).x,(*player).y);
                          str_req+=strength;
                          if(str_req<(*player).strength&&!line(p[far_player[i].ply].x,p[far_player[i].ply].y,(*player).x,(*player).y,player-p,far_player[i].ply,opp_ply,p))
                          {
                                  p[0].x=p[far_player[i].ply].x;
                                  p[0].y=p[far_player[i].ply].y;
                                  ball_hit=true;
                                  player_hit= player-p;
                                  return;
                          }
                          else
                          {
                              if(!line(p[far_player[i].ply].x,p[far_player[i].ply].y,(*player).x,(*player).y,player-p,far_player[i].ply,opp_ply,p))
                              {
                                       
                                       x_diff=p[far_player[i].ply].x-(*player).x;
                                       y_diff=p[far_player[i].ply].y-(*player).y;
                                       distance= sqrt((x_diff*x_diff)+(y_diff*y_diff));
                                       str_req=0;
                                       int r=1;
                                       while((*player).strength-str_req>0&&((*player).x!=p[far_player[i].ply].x||(*player).y!=p[far_player[i].ply].y))
                                       { 
                                          str_req=obj.preqpb(static_cast<int>((*player).x+((x_diff*r)/distance))\
                                          ,static_cast<int>((*player).y+((y_diff*r)/distance)),(*player).x,(*player).y);
                                          str_req+=strength;
                                          r++;
                                       }  
                                       str_req=obj.preqp(static_cast<int>((*player).x+((x_diff*(r-2))/distance)),static_cast<int>((*player).y+((y_diff*(r-2))/distance)),p[far_player[i].ply].x,p[far_player[i].ply].y);
                                       if(r!=1&&p[far_player[i].ply].strength-str_req>0)
                                       {
                                               r=r-2;
                                               p[0].x=static_cast<int>((*player).x+((x_diff*r)/distance));                                                                                  
                                               p[0].y=static_cast<int>((*player).y+((y_diff*r)/distance));
                                               player_hit=player-p;
                                               ball_hit=true;
                                               p[far_player[i].ply].x=p[0].x;
                                               p[far_player[i].ply].y=p[0].y;
                                               return;
                                               
                                       }
                                      
                                       
                              }
                              }
                              i--;
                              }
                              hit_out(p,team_indicator,p[0].x,p[0].y,strength,opp_ply);
                              }
                              }
}
       
static void move_yourself(Player *p,int team_indicator)
{      Player *obj_ptr,*ptr1;
       int player,large=INT_MIN;
       int str_req;
       if(team_indicator==1)
       {
       if(ball_hit==false&&(obj_ptr=check1(p,team_indicator))&&(ptr1=check3(p,team_indicator)))
       {  obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
       
          obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
      
          
          if(obj_ptr->strength-ptr1->strength>0)
          {
                                                
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
        
           for(int i=8;i<12;i++)
              if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
              {if(p[i].strength>large)
              player=i;
              
               }
               
             
              {
              in_striker(p+player,p,team_indicator,ptr1->strength,ptr1-p); 
       
              }
             
          }
          else
          obj_ptr->strength+=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y); 
       }   
       else                                                                                
       if(ball_hit==false&&(obj_ptr=check1(p,team_indicator)))
       {obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
      
        obj_ptr->x=p[0].x;
       obj_ptr->y=p[0].y;
      
       
       obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
       for(int i=8;i<12;i++)
       if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
       {if(p[i].strength>large)
       player=i;
    
       }
       
       
       {
            in_striker(p+player,p,team_indicator,0,0); 
       
       }
      
       }
       else
       if(ball_hit==true&&(check2(p,team_indicator)=="striker"))
       {
          obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
          
          if(obj_ptr!=NULL)
          {
          
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
         
          }
       }
       else
       if(ball_hit==false&&(ptr1=check3(p,team_indicator)))
       {  
          obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
          if(obj_ptr!=NULL)
          {obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
          
          
          if(obj_ptr->strength-ptr1->strength>0)
          {   
              for(int i=8;i<12;i++)
              if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
              {if(p[i].strength>large)
              player=i;
               
              }
               
              
            
              
              {
              in_striker(p+player,p,team_indicator,ptr1->strength,ptr1-p); 
       
              }
           
          }
          
       }
       }
       else
       if(ball_hit==false)
       { 
            obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
           
          if(obj_ptr!=NULL)
          {obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
          for(int i=8;i<12;i++)
         if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
         {if(p[i].strength>large)
           player=i;
        
         }
        
        
        {
            in_striker(p+player,p,team_indicator,0,0); 
       
        }
        
       
       
        }
        }
        }
        if(team_indicator==2)
        {
        if(ball_hit==false&&(obj_ptr=check1(p,team_indicator))&&(ptr1=check3(p,team_indicator)))
       {  obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
          obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
          if(obj_ptr->strength-ptr1->strength>0)
          { obj_ptr->x=p[0].x;
            obj_ptr->y=p[0].y;
           for(int i=8;i<12;i++)
              if(p[i+11].x==obj_ptr->x&&p[i+11].y==obj_ptr->y)
              {if(p[i+11].strength>large)
              player=i+11;
              
               }
              
             
              
              {
              in_striker(p+player,p,team_indicator,ptr1->strength,ptr1-p); 
       
              }
             
          }
          else
          obj_ptr->strength+=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y); 
       }   
       else                                                                                
       if(ball_hit==false&&(obj_ptr=check1(p,team_indicator)))
       {obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
       obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
       obj_ptr->x=p[0].x;
       obj_ptr->y=p[0].y;
       for(int i=8;i<12;i++)
       if(p[i+11].x==obj_ptr->x&&p[i+11].y==obj_ptr->y)
       {if(p[i+11].strength>large)
       player=i+11;
    
       }
       
        
       {
            in_striker(p+player,p,team_indicator,0,0); 
       
       }
      
       }
       else
       if(ball_hit==true&&(check2(p,team_indicator)=="striker"))
       {
          obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
          
          if(obj_ptr!=NULL)
          {
          
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
         
          }
       }
       else
       if(ball_hit==false&&(ptr1=check3(p,team_indicator)))
       {  
          obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
          if(obj_ptr!=NULL)
          {obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
          
          
          if(obj_ptr->strength-ptr1->strength>0)
          {   
              for(int i=8;i<12;i++)
              if(p[i+11].x==obj_ptr->x&&p[i+11].y==obj_ptr->y)
              {if(p[i+11].strength>large)
              player=i+11;
               
              }
             
              
            
              
              {
              in_striker(p+player,p,team_indicator,ptr1->strength,ptr1-p); 
       
              }
           
          }
          
       }
       }
       else
       if(ball_hit==false)
       { 
            obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
           
          if(obj_ptr!=NULL)
          {obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
          for(int i=8;i<12;i++)
         if(p[i+11].x==obj_ptr->x&&p[i+11].y==obj_ptr->y)
         {if(p[i+11].strength>large)
           player=i+11;
        
         }
         
        
        {
            in_striker(p+player,p,team_indicator,0,0); 
       
        }
        
       
       
        }
        }
        }
}


void team0037::striker(Player *p,int team_indicator)
{
Player *obj_ptr;
   
                            if(moves==1)
                            {pos_yourself(p,team,0);
                            
                            }
                          if(check2(p,team)=="defender")
                          {    
                                                pos_yourself(p,team,30);
                                                align_yourself(p,team);  
                                                 move_yourself(p,team);
                                                
                               
                          }
                          if(check2(p,team)=="mid fielder")
                          {   //if(!(obj_ptr=check1(p,team_indicator)))      
                            
                                                 pos_yourself(p,team,35);
                                                 align_yourself(p,team);
                                                  
                               //else
                               move_yourself(p,team);
                               
                          }
                          if(check2(p,team)=="striker")
                          { check_pos(p,team,35);
                                                  move_yourself(p,team);
                          }
}

void play(struct player*,int);
void make_circle(struct player*,int*,int,int,int,int,int);
void make_ball_circle(struct player,int,int*,int);
void search_max(int*,int*,int*,int*);
void run_to_pos(struct player*,int*,int,int,int,int);
void defence(struct player*,int);
int is_fielder(int,int,int,int,struct player*,int,int);
/*int preqp(int,int,int,int);
int preqpb(int,int,int,int);
*/
void play_fast(struct player*,int);
int move[4],pow_team_our[101][51],pow_team_opp[101][51];
void defence(struct player*p,int team){
 int i;
	if(team==1&&(*p).x<=40&&(*p).x>=0)play(p,1);
	else if(team==2&&(*p).x<=99&&(*p).x>=60)play(p,2);
	else{
	player_hit=-1;
	ball_hit=false;
	}
}
void play(struct player*p,int team){
 int j,i,max_power,max_power_player,max_power1,initial_x,initial_y,m,n,a,b,min_point[101][51],xc,yc,pl,ball_circle[101][51],l_our,u_our,l_opp,u_opp,k,o,l,po,powe;
 for(k=0;k<4;k++)move[k]=0;
 for(m=0;m<=100;m++)for(n=0;n<=50;n++)min_point[m][n]=0;
	if(team==1){
	l_our=1;
	u_our=11;
	l_opp=12;
	u_opp=22;
	}
	else{
	l_our=12;
	u_our=22;
	l_opp=1;
	u_opp=11;
	}
	for(a=l_our,po=0,j=u_our-6;a<=u_our-7;a++){
		if((*(p+a)).x==(*p).x&&(*(p+a)).y==(*p).y&&(*(p+a)).strength>po){
		j=a;
		po=(*(p+a)).strength;
		}
	}
	for(b=l_opp,po=0,i=u_opp+1,m=0;b<=u_opp;b++){
		if((*(p+b)).x==(*p).x&&(*(p+b)).y==(*p).y&&(*(p+b)).strength>po){
		i=b;
		po=(*(p+b)).strength;
		}
	}
	if(i>u_opp&&j>u_our-7){
		for(k=0,max_power=0,max_power_player=-1,l=l_our+k;l<=u_our-7;k++){
		l=l_our+k;
		po=(*(p+l)).strength-obj.preqp((*(p+l)).x,(*(p+l)).y,(*p).x,(*p).y);
			if(po>max_power){
			max_power=po;
			max_power_player=l;
			}
		}
		if(max_power>0){
		l=max_power_player;
		(*(p+l)).x=(*p).x;
		(*(p+l)).y=(*p).y;
		k=l-l_our;
		move[k]=1;
		if(max_power>=30)po=30;
		else po=max_power;
		make_circle(p,&pow_team_our[0][0],l_our,u_our,1,l,team);
		make_circle(p,&pow_team_opp[0][0],l_opp,u_opp,-1,-1,team);
		make_ball_circle((*(p+l)),po,&ball_circle[0][0],team);
			if(team==1)
			for(m=1;m<60;m++)for(n=1;n<50;n++)min_point[m][n]=pow_team_our[m][n]+pow_team_opp[m][n]+(2*(m-(*p).x));
			else
			for(m=41;m<=99;m++)for(n=1;n<50;n++)min_point[m][n]=pow_team_our[m][n]+pow_team_opp[m][n]+(2*((*p).x-m));
			for(m=0;m<100;m++){
			search_max(&ball_circle[0][0],&min_point[0][0],&xc,&yc);
			po=min_point[xc][yc];
			if(is_fielder(xc,yc,(*(p+l)).x,(*(p+l)).y,p,l_our,u_our)==0&&po>0)break;
			else if(po<=0)m=100;
			}
			if(m<100){
			(*p).x=xc;
			(*p).y=yc;
			ball_hit=true;
			player_hit=l;
			run_to_pos(p,move,l_our,u_our,(*p).x,(*p).y);
			}
			else{
			ball_hit=false;
			player_hit=-1;
			}
		}
	}
	else if(i<=u_opp){
		if(j>u_our-7){
			for(k=0,max_power=0,max_power_player=-1,l=l_our+k;l<=u_our-7;k++){
			l=l_our+k;
			po=(*(p+l)).strength-obj.preqp((*p).x,(*p).y,(*(p+l)).x,(*(p+l)).y);
				if(po>max_power){
				max_power=po;
				max_power_player=l;
				}
			}
		l=max_power_player;
		max_power1=max_power;
			if(l!=-1){
			(*(p+l)).x=(*p).x;
			(*(p+l)).y=(*p).y;
			pl=l;
			k=l-l_our;
			move[k]=1;
			}
		}
		else if(j<=u_our-7){
		max_power1=(*(p+j)).strength;
		l=j;
		k=l-l_our;
		move[k]=1;
		}
		if(max_power1>=(*(p+i)).strength&&l!=-1){
		make_circle(p,&pow_team_our[0][0],l_our,u_our,o,l,team);
		make_circle(p,&pow_team_opp[0][0],l_opp,u_opp,o,-1,team);
		if(team==1)for(m=1;m<60;m++)for(n=1;n<50;n++)min_point[m][n]=pow_team_our[m][n]+pow_team_opp[m][n]+(2*(m-(*p).x));
		else for(m=41;m<=99;m++)for(n=1;n<50;n++)min_point[m][n]=pow_team_our[m][n]+pow_team_opp[m][n]+(2*((*p).x-m));
		make_ball_circle((*(p+l)),max_power1-(*(p+i)).strength,&ball_circle[0][0],team);
			for(m=0,max_power=0,max_power_player=-1;m<100;m++){
			search_max(&ball_circle[0][0],&min_point[0][0],&xc,&yc);
			powe=min_point[xc][yc];
			if(is_fielder(xc,yc,(*(p+l)).x,(*(p+l)).y,p,l_opp,u_opp)==0&&powe>0)break;
			else if(powe<=0)m=100;
			}
			if(m<100){
			(*p).x=xc;
			(*p).y=yc;
			ball_hit=true;
			player_hit=pl;
			run_to_pos(p,move,l_our,u_our,(*p).x,(*p).y);
			}
			else if(m>=100){
			ball_hit=false;
			player_hit=-1;
			}
		}
		else if(max_power1<(*(p+l)).strength){
		ball_hit=false;
		player_hit=-1;
			for(k=0,l=l_our+k,max_power=0;l<=u_our-7;k++){
			l=l_our+k;
			po=(*(p+l)).strength-obj.preqp((*p).x,(*p).y,(*(p+l)).x,(*(p+l)).y);
				if(po>max_power&&move[k]==0){
				max_power=po;
				max_power_player=l;
				}
			}
			l=max_power_player;
			if(max_power!=0){
			(*(p+l)).x=(*p).x;
			(*(p+l)).y=(*p).y;
			k=l-l_our;
			move[k]=1;
			}
		}
	}
	else if(j<=u_our-7){
	move[j]=1;
	make_circle(p,&pow_team_our[0][0],l_our,u_our,o,j,team);
	make_circle(p,&pow_team_opp[0][0],l_opp,u_opp,o,-1,team);
	if(team==1)for(m=1;m<60;m++)for(n=1;n<50;n++)min_point[m][n]=pow_team_our[m][n]+pow_team_opp[m][n]+(2*(m-(*p).x));
	if(team==2)for(m=41;m<=99;m++)for(n=1;n<50;n++)min_point[m][n]=pow_team_our[m][n]+pow_team_opp[m][n]+(2*((*p).x-m));
	make_ball_circle((*(p+j)),(*(p+j)).strength,&ball_circle[0][0],team);
		for(m=0;m<100;m++){
		search_max(&ball_circle[0][0],&min_point[0][0],&xc,&yc);
		po=min_point[xc][yc];
		if(is_fielder(xc,yc,(*(p+j)).x,(*(p+j)).y,p,l_opp,u_opp)==0&&po>0)break;
		else if(po<=0)m=100;
		}
		if(m<100){
		(*p).x=xc;
		(*p).y=yc;
		run_to_pos(p,move,l_our,u_our,(*p).x,(*p).y);
		ball_hit=true;
		player_hit=j;
		}
		else if(m>=100){
		ball_hit=false;
		player_hit=-1;
		}
	}
}
void make_circle(struct player*q,int*pow,int l,int u,int o,int pl,int team){
 int i,xc,yc,power,j;
 struct player p;
 for(i=0;i<=100;i++)for(j=0;j<=50;j++)*(pow+51*i+j)=0;
	for(i=l;i<=u;i++){
	p=*(q+i);
		if(i!=pl){
			for(xc=p.x;p.strength-obj.preqp(xc,p.y,p.x,p.y)>0&&xc<=99;xc++){
				for(yc=p.y;p.strength-obj.preqp(xc,yc,p.x,p.y)>0&&yc<50;yc++){
				power=o*(p.strength-obj.preqp(xc,yc,p.x,p.y));
				if(power>0&&*(pow+51*xc+yc)<power)*(pow+51*xc+yc)=power;
				else if(power<0&&*(pow+51*xc+yc)>power)*(pow+51*xc+yc)=power;
				}
			}
			for(xc=p.x;p.strength-obj.preqp(xc,p.y,p.x,p.y)>0&&xc>0;xc--){
				for(yc=p.y;p.strength-obj.preqp(xc,yc,p.x,p.y)>0&&yc<50;yc++){
				power=o*(p.strength-obj.preqp(xc,yc,p.x,p.y));
				if(power>0&&*(pow+51*xc+yc)<power)*(pow+51*xc+yc)=power;
				else if(power<0&&*(pow+51*xc+yc)>power)*(pow+51*xc+yc)=power;
				}
			}
			for(xc=p.x;p.strength-obj.preqp(xc,p.y,p.x,p.y)>0&&xc>0;xc--){
				for(yc=p.y;p.strength-obj.preqp(xc,yc,p.x,p.y)>0&&yc>0;yc--){
				power=o*(p.strength-obj.preqp(xc,yc,p.x,p.y));
				if(power>0&&*(pow+51*xc+yc)<power)*(pow+51*xc+yc)=power;
				else if(power<0&&*(pow+51*xc+yc)>power)*(pow+51*xc+yc)=power;
				}
			}
			for(xc=p.x;p.strength-obj.preqp(xc,p.y,p.x,p.y)>0&&xc<100;xc++){
				for(yc=p.y;p.strength-obj.preqp(xc,yc,p.x,p.y)>0&&yc>0;yc--){
				power=o*(p.strength-obj.preqp(xc,yc,p.x,p.y));
				if(power>0&&*(pow+51*xc+yc)<power)*(pow+51*xc+yc)=power;
				else if(power<0&&*(pow+51*xc+yc)>power)*(pow+51*xc+yc)=power;
				}
			}
		}
	}
	if(team==1){
	for(i=1;i<=14;i++)for(j=10;j<=40;j++)pow_team_opp[i][j]=-99;
	for(i=85;i<=99;i++)for(j=10;j<=40;j++)pow_team_our[i][j]=0;
	}
	else{
	for(i=1;i<=14;i++)for(j=10;j<=40;j++)pow_team_our[i][j]=0;
	for(i=85;i<=99;i++)for(j=10;j<=40;j++)pow_team_opp[i][j]=-99;
	}
	for(i=0,j=0;j<51;j++)pow_team_opp[i][j]=-30;
	for(i=100,j=0;j<51;j++)pow_team_opp[i][j]=-30;
	for(i=0,j=0;i<101;i++)pow_team_opp[i][j]=-30;
	for(i=0,j=50;i<101;i++)pow_team_opp[i][j]=-30;
}
void make_ball_circle(struct player pl,int po,int*ball_circle,int team){
 int i,j,xc,yc;
 for(i=0;i<=100;i++)for(j=0;j<=50;j++)*(ball_circle+51*i+j)=-1;
 for(xc=pl.x;po-obj.preqpb(xc,pl.y,pl.x,pl.y)>0&&xc<100;xc++)for(yc=pl.y;po-obj.preqpb(xc,yc,pl.x,pl.y)>0&&yc<=49;yc++)*(ball_circle+51*xc+yc)=po-obj.preqpb(xc,yc,pl.x,pl.y);
 for(xc=pl.x;po-obj.preqpb(xc,pl.y,pl.x,pl.y)>0&&xc>0;xc--)for(yc=pl.y;po-obj.preqpb(xc,yc,pl.x,pl.y)>0&&yc<50;yc++)*(ball_circle+51*xc+yc)=po-obj.preqpb(xc,yc,pl.x,pl.y);
 for(xc=pl.x;po-obj.preqpb(xc,pl.y,pl.x,pl.y)>0&&xc>0;xc--)for(yc=pl.y;po-obj.preqpb(xc,yc,pl.x,pl.y)>0&&yc>0;yc--)*(ball_circle+51*xc+yc)=po-obj.preqpb(xc,yc,pl.x,pl.y);
 for(xc=pl.x;po-obj.preqpb(xc,pl.y,pl.x,pl.y)>0&&xc<100;xc++)for(yc=pl.y;po-obj.preqpb(xc,yc,pl.x,pl.y)>0&&yc>0;yc--)*(ball_circle+51*xc+yc)=po-obj.preqpb(xc,yc,pl.x,pl.y);
 if(team==1)for(i=60;i<=100;i++)for(j=0;j<51;j++)*(ball_circle+51*i+j)=-1;
 else if(team==2)for(i=0;i<40;i++)for(j=0;j<51;j++)*(ball_circle+51*i+j)=-1;
}
void search_max(int*ball_circle,int*min_point,int*pxc,int*pyc){
 int i,j,power,max_power=0;
 *pxc=*pyc=0;
	for(i=0;i<100;i++){
		for(j=0;j<50;j++){
			if(*(ball_circle+51*i+j)!=-1){
			power=*(min_point+i*51+j);
				if(power>max_power){
				max_power=power;
				*pxc=i;
				*pyc=j;
				}
				if(power==max_power&&*(ball_circle+51*(*pxc)+(*pyc))<*(ball_circle+51*i+j)){
				*pxc=i;
				*pyc=j;
				}
			}
		}
	}
 *(ball_circle+(*pxc)*51+(*pyc))=-1;
}
void run_to_pos(struct player*p,int*move,int l_our,int u_our,int xc,int yc){
 int k,l,m=0,max_power=0,max_power_player=-1,po;
 if((l_our==1&&(*p).x<=40)||(l_our==12&&(*p).x>=60))m=1;
	if(m==1){
		for(k=0,l=l_our+k;l<=u_our-7;k++){
		l=l_our+k;
			if(move[k]==0){
			po=(*(p+l)).strength-obj.preqp(xc,yc,(*(p+l)).x,(*(p+l)).y);
				if(po>max_power){
				max_power=po;
				max_power_player=l;
				}
			}
		}
		l=max_power_player;
		if(l!=-1){
		(*(p+l)).x=(*p).x;
		(*(p+l)).y=(*p).y;
		k=l-l_our;
		move[k]=1;
		}
	}
}
int is_fielder(int final_x,int final_y,int initial_x,int initial_y,struct player*p,int l_opp,int u_opp){
 int i,j,m,n,u=1,v=1,k;
 float incr;
 if(initial_x==final_x&&initial_y==final_y)return(0);
	if(final_x!=initial_x)incr=(final_y-initial_y)/(final_x-initial_x);
	else {
	u=0;
	incr=1;
	}
 if(incr<0)incr*=-1;
 if(final_x<initial_x)u=-1;
 if(final_y<initial_y)v=-1;
	for(i=initial_x,j=initial_y,k=0;i!=final_x&&j!=final_y;k++){
	i=i+k*u;
	j=j+(int)(v*k*incr);
		for(m=0,n=l_opp+m;n<=u_opp;m++){
		n=l_opp+m;
		if((*(p+n)).x==i&&(*(p+n)).y==j)return(1);
		}
	}
 return(0);
}
/*int preqp(int finalx,int finaly,int initialx,int initialy){
 float req;
 req=floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
 return(int)req;
}
int preqpb(int finalx,int finaly,int initialx,int initialy){
 float req;
 req=2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
 return(int)req;
}
*/
void play_fast(struct player*p,int team){
 int i,m[4],l,u,xc,yc,po,max_power=-100,max_power_player,x,y;
 if(team==1&&(*p).x>40)return;
 else if(team==2&&(*p).x<60)return;
 for(i=0;i<4;i++)m[i]=0;
	if(team==1){
	l=1;
	u=4;
	}
	else{
	l=12;
	u=16;
	}
 for(i=l;i<=u;i++)if((*(p+i)).x==(*p).x&&(*(p+i)).y==(*p).y)m[i-l]=1;
	for(i=l;i<=u;i++){
		if(m[i-l]==0){
		xc=int(((*p).x+(*(p+i)).x)/2);
		yc=int(((*p).y+(*(p+i)).y)/2);
		if(xc<0)xc*=-1;
		if(yc<0)yc*=-1;
		po=(*(p+i)).strength-obj.preqp(xc,yc,(*(p+i)).x,(*(p+i)).y);
			if(po>max_power){
			max_power=po;
			max_power_player=i;
			x=xc;
			y=yc;
			}
		}
	}
	i=max_power_player;
	if(max_power>-100){
	(*(p+i)).x=x;
	(*(p+i)).y=y;
	}
}	

void team0037::mid_fielder(Player *p,int team_indicator)
{ Player *obj_ptr;       
                           
                            
                        if(check2(p,team)=="defender")
                          { 
                          pos_mid_yourself(p,team,30);
                          
                                                      
                          }
                          if(check2(p,team)=="mid fielder")
                          {
                         // pos_mid_yourself(p,team_indicator,40);
                          move_mid_yourself(p,team); 
                          }
                          if(check2(p,team)=="striker")
                          { if(!(obj_ptr=check_mid_1(p,team_indicator)))
                                                 align_mid_yourself(p,team); 
                          else
                          move_mid_yourself(p,team);   
                          }
}

static void pos_mid_yourself(Player *p,int team_indicator,int indicate)
{
  int str_req,y_diff,x_diff,count=11,x,y;
       float distance;
       bool flag=false;
       Player *ptr;
       
       if(team_indicator==1)
       {           ptr=check_mid_1(p,team_indicator);
                            // first mid_fielder
                    if(ptr!=NULL)
                    {
                    if(!(ptr->x==p[5].x&&ptr->y==p[5].y)||flag)
                    {
                    str_req=obj.preqp(45,8,p[5].x,p[5].y);
                    if(p[5].strength-str_req>=indicate)
                    {
                                                 p[5].x=45;
                                                 p[5].y=8;
                    }
                    else
                    {
                        while(p[5].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=8-p[5].y;
                          x_diff=45-p[5].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((p[5].x+((count*x_diff)/distance))),static_cast<int>((p[5].y+((count*y_diff)/distance))),p[5].x,p[5].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {x=p[5].x;
                    y=p[5].y;
                    p[5].x=static_cast<int>(p[5].x+((count*x_diff)/distance));
                    p[5].y=static_cast<int>(p[5].y+((count*y_diff)/distance));
                    p[5].strength-=obj.preqp(p[5].x,p[5].y,x,y);
                    }
                    }
                    flag=true;
                    }
                     if(!(ptr->x==p[6].x&&ptr->y==p[6].y)||flag)
                    {// second mid_fielder
                    count=11;
                    str_req=obj.preqp(45,25,p[6].x,p[6].y);
                    if(p[6].strength-str_req>=indicate)
                    {
                                                 p[6].x=45;
                                                 p[6].y=25;
                    }
                    else
                    {
                        while(p[6].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[6].y;
                          x_diff=45-p[6].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[6].x+((count*x_diff)/distance)),static_cast<int>(p[6].y+((count*y_diff)/distance)),p[6].x,p[6].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {x=p[6].x;
                    y=p[6].y;
                    p[6].x=static_cast<int>(p[6].x+((count*x_diff)/distance));
                    p[6].y=static_cast<int>(p[6].y+((count*y_diff)/distance));
                    p[6].strength-=obj.preqp(p[6].x,p[6].y,x,y);
                    }
                    }
                    flag=true;
                    }
                     if(!(ptr->x==p[7].x&&ptr->y==p[7].y)||flag)
                    { // third mid_fielder
                    count=11;
                    str_req=obj.preqp(45,40,p[7].x,p[7].y);
                    if(p[7].strength-str_req>=indicate)
                    {
                                                 p[7].x=45;
                                                 p[7].y=40;
                    }
                    else
                    {
                        while(p[7].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=40-p[7].y;
                          x_diff=45-p[7].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[7].x+((count*x_diff)/distance)),static_cast<int>(p[7].y+((count*y_diff)/distance)),p[7].x,p[7].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {x=p[7].x;
                    y=p[7].y;
                    p[7].x=static_cast<int>(p[7].x+((count*x_diff)/distance));
                    p[7].y=static_cast<int>(p[7].y+((count*y_diff)/distance));
                    p[7].strength-=obj.preqp(p[7].x,p[7].y,x,y);
                    } 
                    } 
                    }
                    }
                    else
                     {                    // first striker
                    str_req=obj.preqp(45,8,p[5].x,p[5].y);
                    if(p[5].strength-str_req>=indicate)
                    {
                                                 p[5].x=45;
                                                 p[5].y=8;
                    }
                    else
                    {
                        while(p[5].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=8-p[5].y;
                          x_diff=45-p[5].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((p[5].x+((count*x_diff)/distance))),static_cast<int>((p[5].y+((count*y_diff)/distance))),p[5].x,p[5].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[5].x=static_cast<int>(p[5].x+((count*x_diff)/distance));
                    p[5].y=static_cast<int>(p[5].y+((count*y_diff)/distance));
                    }
                    }
                    
                    // second striker
                    count=11;
                    str_req=obj.preqp(45,25,p[6].x,p[6].y);
                    if(p[6].strength-str_req>=indicate)
                    {
                                                 p[9].x=45;
                                                 p[9].y=25;
                    }
                    else
                    {
                        while(p[6].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[6].y;
                          x_diff=45-p[6].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[6].x+((count*x_diff)/distance)),static_cast<int>(p[6].y+((count*y_diff)/distance)),p[6].x,p[6].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[6].x=static_cast<int>(p[6].x+((count*x_diff)/distance));
                    p[6].y=static_cast<int>(p[6].y+((count*y_diff)/distance));
                    }
                    }
                     // third striker
                    count=11;
                    str_req=obj.preqp(45,40,p[7].x,p[7].y);
                    if(p[7].strength-str_req>=indicate)
                    {
                                                 p[7].x=45;
                                                 p[7].y=40;
                    }
                    else
                    {
                        while(p[7].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=40-p[7].y;
                          x_diff=45-p[7].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[7].x+((count*x_diff)/distance)),static_cast<int>(p[7].y+((count*y_diff)/distance)),p[7].x,p[7].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[7].x=static_cast<int>(p[7].x+((count*x_diff)/distance));
                    p[7].y=static_cast<int>(p[7].y+((count*y_diff)/distance));
                    } 
                    } 
                    
                    }  
                                     
                    }  
             if(team_indicator==2)
             {
                    ptr=check_mid_1(p,team_indicator);
                            // first mid_fielder
                    if(ptr!=NULL)
                    {
                    if(!(ptr->x==p[16].x&&ptr->y==p[16].y)||flag)
                    {
                    count=11;
                    str_req=obj.preqp(55,8,p[16].x,p[16].y);
                    if(p[16].strength-str_req>=indicate)
                    {
                                                 p[16].x=55;
                                                 p[16].y=8;
                    }
                    else
                    {
                        while(p[16].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=8-p[16].y;
                          x_diff=55-p[16].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[16].x+((count*x_diff)/distance)),static_cast<int>(p[16].y+((count*y_diff)/distance)),p[16].x,p[16].y);
                          count--;
                    }
                    if(count!=-1)
                    {x=p[16].x;
                    y=p[16].y;
                    p[16].x=static_cast<int>(p[16].x+((count*x_diff)/distance));
                    p[16].y=static_cast<int>(p[16].y+((count*y_diff)/distance));
                    p[16].strength-=obj.preqp(p[16].x,p[16].y,x,y);
                    }
                    }
                    flag=true;
                    }
                    if(!(ptr->x==p[17].x&&ptr->y==p[17].y)||flag)
                    {// second mid_fielder
                    count=11;
                    str_req=obj.preqp(55,25,p[17].x,p[17].y);
                    if(p[17].strength-str_req>=indicate)
                    {
                                                 p[17].x=55;
                                                 p[17].y=25;
                    }
                    else
                    {
                        while(p[17].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[17].y;
                          x_diff=55-p[17].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[17].x+((count*x_diff)/distance)),static_cast<int>(p[17].y+((count*y_diff)/distance)),p[17].x,p[17].y);
                          count--;
                    }
                    if(count!=-1)
                    {x=p[17].x;
                    y=p[17].y;
                    p[17].x=static_cast<int>(p[17].x+((count*x_diff)/distance));
                    p[17].y=static_cast<int>(p[17].y+((count*y_diff)/distance));
                    p[17].strength-=obj.preqp(p[17].x,p[17].y,x,y);
                    }
                    }
                    flag=true;
                    }
                    if(!(ptr->x==p[18].x&&ptr->y==p[18].y)||flag)
                    { // third mid_fielder
                    count=11;
                    str_req=obj.preqp(55,40,p[18].x,p[18].y);
                    if(p[18].strength-str_req>=indicate)
                    {
                                                 p[18].x=55;
                                                 p[18].y=40;
                    }
                    else
                    {
                        while(p[18].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=40-p[18].y;
                          x_diff=55-p[18].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[18].x+((count*x_diff)/distance)),static_cast<int>(p[18].y+((count*y_diff)/distance)),p[18].x,p[18].y);
                          count--;
                    }
                    if(count!=-1)
                    {x=p[18].x;
                    y=p[18].y;
                    p[18].x=static_cast<int>(p[18].x+((count*x_diff)/distance));
                    p[18].y=static_cast<int>(p[18].y+((count*y_diff)/distance));
                    p[18].strength-=obj.preqp(p[18].x,p[18].y,x,y);
                    }  
                    }
                    }
                    }
                    else
                     {                    // first striker
                    str_req=obj.preqp(55,8,p[16].x,p[16].y);
                    if(p[16].strength-str_req>=indicate)
                    {
                                                 p[16].x=55;
                                                 p[16].y=8;
                    }
                    else
                    {
                        while(p[16].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=8-p[16].y;
                          x_diff=55-p[16].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((p[16].x+((count*x_diff)/distance))),static_cast<int>((p[16].y+((count*y_diff)/distance))),p[16].x,p[16].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[16].x=static_cast<int>(p[16].x+((count*x_diff)/distance));
                    p[16].y=static_cast<int>(p[16].y+((count*y_diff)/distance));
                    }
                    }
                    
                    // second striker
                    count=11;
                    str_req=obj.preqp(55,25,p[7].x,p[17].y);
                    if(p[17].strength-str_req>=indicate)
                    {
                                                 p[17].x=55;
                                                 p[17].y=25;
                    }
                    else
                    {
                        while(p[17].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=25-p[17].y;
                          x_diff=55-p[17].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[17].x+((count*x_diff)/distance)),static_cast<int>(p[17].y+((count*y_diff)/distance)),p[17].x,p[17].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[17].x=static_cast<int>(p[17].x+((count*x_diff)/distance));
                    p[17].y=static_cast<int>(p[17].y+((count*y_diff)/distance));
                    }
                    }
                     // third striker
                    count=11;
                    str_req=obj.preqp(55,40,p[18].x,p[18].y);
                    if(p[18].strength-str_req>=indicate)
                    {
                                                 p[18].x=55;
                                                 p[18].y=40;
                    }
                    else
                    {
                        while(p[18].strength-str_req<indicate&&count>-1)
                        {
                          y_diff=40-p[18].y;
                          x_diff=45-p[18].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[18].x+((count*x_diff)/distance)),static_cast<int>(p[18].y+((count*y_diff)/distance)),p[18].x,p[18].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[18].x=static_cast<int>(p[18].x+((count*x_diff)/distance));
                    p[18].y=static_cast<int>(p[18].y+((count*y_diff)/distance));
                    } 
                    } 
                    
                    
                    }  
                    
                    }
}                                                                            
static void align_mid_yourself(Player *p,int team_indicator)
{
  int str_req,y_diff,x_diff,count=11,x,y;
       float distance;
       bool flag = false;
       Player *ptr;
       if(team_indicator==1)
       {            ptr=check_mid_1(p,team_indicator);
                    if(ptr!=NULL)
                    {
                    if(!(ptr->x==p[5].x&&ptr->y==p[5].y)||flag) 
                     {       // first mid_fielder
                    str_req=obj.preqp(55,8,p[5].x,p[5].y);
                    if(p[5].strength-str_req>=40)
                    {
                                                 p[5].x=55;
                                                 p[5].y=8;
                    }
                    else
                    {
                        while(p[5].strength-str_req<40&&count>-1)
                        {
                          y_diff=8-p[5].y;
                          x_diff=55-p[5].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((p[5].x+((count*x_diff)/distance))),static_cast<int>((p[5].y+((count*y_diff)/distance))),p[5].x,p[5].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {x=p[5].x;
                    y=p[5].y;
                    p[5].x=static_cast<int>(p[5].x+((count*x_diff)/distance));
                    p[5].y=static_cast<int>(p[5].y+((count*y_diff)/distance));
                     p[5].strength-=obj.preqp(p[5].x,p[5].y,x,y);
                    }
                    }
                    flag=true;
                    }
                    if(!(ptr->x==p[6].x&&ptr->y==p[6].y)||flag) 
                    {// second mid_fielder
                    count=11;
                    str_req=obj.preqp(55,25,p[6].x,p[6].y);
                    if(p[6].strength-str_req>=40)
                    {
                                                 p[6].x=55;
                                                 p[6].y=25;
                    }
                    else
                    {
                        while(p[6].strength-str_req<40&&count>-1)
                        {
                          y_diff=25-p[6].y;
                          x_diff=55-p[6].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[6].x+((count*x_diff)/distance)),static_cast<int>(p[6].y+((count*y_diff)/distance)),p[6].x,p[6].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {x=p[6].x;
                    y=p[6].y;
                    p[6].x=static_cast<int>(p[6].x+((count*x_diff)/distance));
                    p[6].y=static_cast<int>(p[6].y+((count*y_diff)/distance));
                    p[6].strength-=obj.preqp(p[6].x,p[6].y,x,y);
                    }
                    }
                    flag=true;
                    }
                    if(!(ptr->x==p[7].x&&ptr->y==p[7].y)||flag) 
                    { // third mid_fielder
                    count=11;
                    str_req=obj.preqp(55,40,p[7].x,p[7].y);
                    if(p[7].strength-str_req>=40)
                    {
                                                 p[7].x=55;
                                                 p[7].y=40;
                    }
                    else
                    {
                        while(p[7].strength-str_req<40&&count>-1)
                        {
                          y_diff=40-p[7].y;
                          x_diff=55-p[7].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[7].x+((count*x_diff)/distance)),static_cast<int>(p[7].y+((count*y_diff)/distance)),p[7].x,p[7].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {x=p[7].x;
                    y=p[7].y;
                    p[7].x=static_cast<int>(p[7].x+((count*x_diff)/distance));
                    p[7].y=static_cast<int>(p[7].y+((count*y_diff)/distance));
                    p[7].strength-=obj.preqp(p[7].x,p[7].y,x,y);
                    } 
                    } 
                    }
                    }
                    else
                     {                    // first striker
                    str_req=obj.preqp(55,8,p[5].x,p[5].y);
                    if(p[5].strength-str_req>=40)
                    {
                                                 p[8].x=55;
                                                 p[8].y=8;
                    }
                    else
                    {
                        while(p[5].strength-str_req<40&&count>-1)
                        {
                          y_diff=8-p[5].y;
                          x_diff=55-p[5].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((p[5].x+((count*x_diff)/distance))),static_cast<int>((p[5].y+((count*y_diff)/distance))),p[5].x,p[5].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[5].x=static_cast<int>(p[5].x+((count*x_diff)/distance));
                    p[5].y=static_cast<int>(p[5].y+((count*y_diff)/distance));
                    }
                    }
                    
                    // second striker
                    count=11;
                    str_req=obj.preqp(55,25,p[6].x,p[6].y);
                    if(p[6].strength-str_req>=40)
                    {
                                                 p[6].x=55;
                                                 p[6].y=25;
                    }
                    else
                    {
                        while(p[6].strength-str_req<40&&count>-1)
                        {
                          y_diff=25-p[6].y;
                          x_diff=55-p[6].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[6].x+((count*x_diff)/distance)),static_cast<int>(p[6].y+((count*y_diff)/distance)),p[6].x,p[6].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[6].x=static_cast<int>(p[6].x+((count*x_diff)/distance));
                    p[6].y=static_cast<int>(p[6].y+((count*y_diff)/distance));
                    }
                    }
                     // third striker
                    count=11;
                    str_req=obj.preqp(55,40,p[7].x,p[7].y);
                    if(p[7].strength-str_req>=40)
                    {
                                                 p[7].x=55;
                                                 p[7].y=40;
                    }
                    else
                    {
                        while(p[7].strength-str_req<40&&count>-1)
                        {
                          y_diff=40-p[7].y;
                          x_diff=55-p[7].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[7].x+((count*x_diff)/distance)),static_cast<int>(p[7].y+((count*y_diff)/distance)),p[7].x,p[7].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[7].x=static_cast<int>(p[7].x+((count*x_diff)/distance));
                    p[7].y=static_cast<int>(p[7].y+((count*y_diff)/distance));
                    } 
                    } 
                   
                    
                    }  
                                     
                    }  
             if(team_indicator==2)
             {      ptr=check_mid_1(p,team_indicator);
                    if(ptr!=NULL)
                    {
                    if(!(ptr->x==p[16].x&&ptr->y==p[16].y)||flag) 
                     {       // first mid_fielder  
                    
                    count=11;
                    str_req=obj.preqp(45,8,p[16].x,p[16].y);
                    if(p[16].strength-str_req>=40)
                    {
                                                 p[16].x=45;
                                                 p[16].y=8;
                    }
                    else
                    {
                        while(p[16].strength-str_req<40&&count>-1)
                        {
                          y_diff=8-p[16].y;
                          x_diff=45-p[16].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[16].x+((count*x_diff)/distance)),static_cast<int>(p[16].y+((count*y_diff)/distance)),p[16].x,p[16].y);
                          count--;
                    }
                    if(count!=-1)
                    {x=p[16].x;
                    y=p[16].y;
                    p[16].x=static_cast<int>(p[16].x+((count*x_diff)/distance));
                    p[16].y=static_cast<int>(p[16].y+((count*y_diff)/distance));
                     p[16].strength-=obj.preqp(p[16].x,p[16].y,x,y);
                    }
                    }
                    flag=true;
                    }
                    
                    
                    if(!(ptr->x==p[17].x&&ptr->y==p[17].y)||flag) 
                    {       
                    // second mid_fielder
                    count=11;
                    str_req=obj.preqp(45,25,p[17].x,p[17].y);
                    if(p[17].strength-str_req>=40)
                    {
                                                 p[17].x=45;
                                                 p[17].y=25;
                    }
                    else
                    {
                        while(p[17].strength-str_req<40&&count>-1)
                        {
                          y_diff=25-p[17].y;
                          x_diff=45-p[17].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[17].x+((count*x_diff)/distance)),static_cast<int>(p[17].y+((count*y_diff)/distance)),p[17].x,p[17].y);
                          count--;
                    }
                    if(count!=-1)
                    {x=p[17].x;
                    y=p[17].y;
                    p[17].x=static_cast<int>(p[17].x+((count*x_diff)/distance));
                    p[17].y=static_cast<int>(p[17].y+((count*y_diff)/distance));
                    p[17].strength-=obj.preqp(p[17].x,p[17].y,x,y);
                    }
                    }
                    flag=true;
                    }
                   
                  
                    if(!(ptr->x==p[18].x&&ptr->y==p[18].y)||flag) 
                     {       
                     // third mid_fielder
                    count=11;
                    str_req=obj.preqp(45,40,p[18].x,p[18].y);
                    if(p[18].strength-str_req>=40)
                    {
                                                 p[18].x=45;
                                                 p[18].y=40;
                    }
                    else
                    {
                        while(p[18].strength-str_req<40&&count>-1)
                        {
                          y_diff=40-p[18].y;
                          x_diff=45-p[18].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[18].x+((count*x_diff)/distance)),static_cast<int>(p[18].y+((count*y_diff)/distance)),p[18].x,p[18].y);
                          count--;
                    }
                    if(count!=-1)
                    {x=p[18].x;
                    y=p[18].y;
                    p[18].x=static_cast<int>(p[18].x+((count*x_diff)/distance));
                    p[18].y=static_cast<int>(p[18].y+((count*y_diff)/distance));
                    p[18].strength-=obj.preqp(p[18].x,p[18].y,x,y);
                    }  
                    }
                    }
                    }
                    else
                     {                    // first striker
                    str_req=obj.preqp(45,8,p[16].x,p[16].y);
                    if(p[16].strength-str_req>=40)
                    {
                                                 p[16].x=45;
                                                 p[16].y=8;
                    }
                    else
                    {
                        while(p[16].strength-str_req<40&&count>-1)
                        {
                          y_diff=8-p[16].y;
                          x_diff=45-p[16].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>((p[16].x+((count*x_diff)/distance))),static_cast<int>((p[16].y+((count*y_diff)/distance))),p[16].x,p[16].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[16].x=static_cast<int>(p[16].x+((count*x_diff)/distance));
                    p[16].y=static_cast<int>(p[16].y+((count*y_diff)/distance));
                    }
                    }
                    
                    // second striker
                    count=11;
                    str_req=obj.preqp(45,25,p[17].x,p[17].y);
                    if(p[17].strength-str_req>=40)
                    {
                                                 p[17].x=45;
                                                 p[17].y=25;
                    }
                    else
                    {
                        while(p[17].strength-str_req<40&&count>-1)
                        {
                          y_diff=25-p[17].y;
                          x_diff=45-p[17].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[17].x+((count*x_diff)/distance)),static_cast<int>(p[17].y+((count*y_diff)/distance)),p[17].x,p[17].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[17].x=static_cast<int>(p[17].x+((count*x_diff)/distance));
                    p[17].y=static_cast<int>(p[17].y+((count*y_diff)/distance));
                    }
                    }
                     // third striker
                    count=11;
                    str_req=obj.preqp(45,40,p[18].x,p[18].y);
                    if(p[18].strength-str_req>=40)
                    {
                                                 p[18].x=45;
                                                 p[18].y=40;
                    }
                    else
                    {
                        while(p[18].strength-str_req<40&&count>-1)
                        {
                          y_diff=40-p[18].y;
                          x_diff=45-p[18].x;
                          distance=sqrt((x_diff*x_diff)+(y_diff*y_diff));
                          str_req=obj.preqp(static_cast<int>(p[18].x+((count*x_diff)/distance)),static_cast<int>(p[18].y+((count*y_diff)/distance)),p[18].x,p[18].y);
                          count--;
                    }
                    
                    if(count!=-1)
                    {
                    p[18].x=static_cast<int>(p[18].x+((count*x_diff)/distance));
                    p[18].y=static_cast<int>(p[18].y+((count*y_diff)/distance));
                    } 
                    } 
                    
                    
                    }  
                    
                    }
}         

                                                                                        
static void move_mid_yourself(Player *p,int team_indicator)
{     
     Player *obj_ptr,*ptr1;
       int player,large=INT_MIN;
       int str_req;
       if(team_indicator==1)
       {
       if(ball_hit==false&&(obj_ptr=check_mid_1(p,team_indicator))&&(ptr1=check3(p,team_indicator)))
       {  obj_ptr=max_mid_strength(p,team_indicator,p[0].x,p[0].y);
          obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x,obj_ptr->y);
            
              
          if(obj_ptr->strength-ptr1->strength>0)
          {obj_ptr->x=p[0].x;
              obj_ptr->y=p[0].y;
           for(int i=5;i<8;i++)
              if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
              {if(p[i].strength>large)
              player=i;
              
              }
            
              in_mid_fielder(p+player,p,team_indicator,ptr1->strength,ptr1-p); 
       
           
          }
          else
        obj_ptr->strength+=obj.preqp(p[0].x,p[0].y,obj_ptr->x,obj_ptr->y);
       }    
       else                                                                                
       if(ball_hit==false&&(obj_ptr=check_mid_1(p,team_indicator)))
       {obj_ptr=max_mid_strength(p,team_indicator,p[0].x,p[0].y);
       obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x,obj_ptr->y);
       obj_ptr->x=p[0].x;
       obj_ptr->y=p[0].y;
       for(int i=5;i<8;i++)
       if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
       {if(p[i].strength>large)
       player=i;
      
      
       }
       
       
       in_mid_fielder(p+player,p,team_indicator,0,0); 
       
      
       }
       else
       if(ball_hit==true&&(check2(p,team_indicator)=="mid fielder"))
       {
          obj_ptr=max_mid_strength(p,team_indicator,p[0].x,p[0].y);
          if(obj_ptr!=NULL)
          {
          
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
          }
       }
       else
       if(ball_hit==false&&(ptr1=check3(p,team_indicator)))
       {  
          obj_ptr=max_mid_strength(p,team_indicator,p[0].x,p[0].y);
          if(obj_ptr!=NULL)
          {obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
          
          
          if(obj_ptr->strength-ptr1->strength>0)
          {   
              for(int i=5;i<8;i++)
              if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
              {player=i;
               break;
              }
              
            
              
              in_mid_fielder(p+player,p,team_indicator,ptr1->strength,ptr1-p); 
       
             
          }
          
       }
       }
       else
       if(ball_hit==false)
       {    
            obj_ptr=max_mid_strength(p,team_indicator,p[0].x,p[0].y);
          
          
           
          if(obj_ptr!=NULL)
          { 
          obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
         
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
         for(int i=5;i<8;i++) 
         if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
         {player=i;
         break;
         }
         
        
            in_mid_fielder(p+player,p,team_indicator,0,0); 
       
      
       
        }
        }
        }
        if(team_indicator==2)
        {if(ball_hit==false&&(obj_ptr=check_mid_1(p,team_indicator))&&(ptr1=check3(p,team_indicator)))
       {  obj_ptr=max_mid_strength(p,team_indicator,p[0].x,p[0].y);
          obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x,obj_ptr->y);
           
              
          if(obj_ptr->strength-ptr1->strength>0)
          {obj_ptr->x=p[0].x;
              obj_ptr->y=p[0].y;
           for(int i=5;i<8;i++)
              if(p[i+11].x==obj_ptr->x&&p[i+11].y==obj_ptr->y)
              {if(p[i+11].strength>large)
              player=i+11;
              
              }
             
              in_mid_fielder(p+player,p,team_indicator,ptr1->strength,ptr1-p); 
       
           
          }
          else
        obj_ptr->strength+=obj.preqp(p[0].x,p[0].y,obj_ptr->x,obj_ptr->y);
       }    
       else                                                                                
       if(ball_hit==false&&(obj_ptr=check_mid_1(p,team_indicator)))
       {obj_ptr=max_mid_strength(p,team_indicator,p[0].x,p[0].y);
       obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x,obj_ptr->y);
       obj_ptr->x=p[0].x;
       obj_ptr->y=p[0].y;
       for(int i=5;i<8;i++)
       if(p[i+11].x==obj_ptr->x&&p[i+11].y==obj_ptr->y)
       {if(p[i+11].strength>large)
       player=i+11;
      
      
       }
     
       
       in_mid_fielder(p+player,p,team_indicator,0,0); 
       
      
       }
       else
       if(ball_hit==true&&(check2(p,team_indicator)=="mid fielder"))
       {
          obj_ptr=max_mid_strength(p,team_indicator,p[0].x,p[0].y);
          if(obj_ptr!=NULL)
          {
          
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
          }
       }
       else
       if(ball_hit==false&&(ptr1=check3(p,team_indicator)))
       {  
          obj_ptr=max_mid_strength(p,team_indicator,p[0].x,p[0].y);
          if(obj_ptr!=NULL)
          {obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
          
          
          if(obj_ptr->strength-ptr1->strength>0)
          {   
              for(int i=5;i<8;i++)
              if(p[i+11].x==obj_ptr->x&&p[i+11].y==obj_ptr->y)
              {player=i+11;
               break;
              }
              
            
              
              in_mid_fielder(p+player,p,team_indicator,ptr1->strength,ptr1-p); 
       
             
          }
          
       }
       }
       else
       if(ball_hit==false)
       {    
            obj_ptr=max_mid_strength(p,team_indicator,p[0].x,p[0].y);
          
           
          if(obj_ptr!=NULL)
          { 
          obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
         
          obj_ptr->x=p[0].x;
          obj_ptr->y=p[0].y;
          for(int i=5;i<8;i++)
         if(p[i+11].x==obj_ptr->x&&p[i+11].y==obj_ptr->y)
         {player=i+11;
         break;
         }
        
            in_mid_fielder(p+player,p,team_indicator,0,0); 
       
      
       
        }
        }
        }
        
}   
static Player *check_mid_1(Player *p,int team_indicator)
{   int large=INT_MIN;
    Player *ply;
       if(team_indicator==1)
       {
                            for(int i=0;i<3;i++)
                            if(p[0].x==p[i+5].x&&p[0].y==p[i+5].y&&p[5+i].strength>large)
                            {large=p[5+i].strength;
                            ply=p+i+5;
                            }
                            if(large!=INT_MIN)
                            return ply;
       }
       if(team_indicator==2)
       {
                            for(int i=0;i<3;i++)
                            if(p[0].x==p[i+16].x&&p[0].y==p[i+16].y&&p[16+i].strength>large)
                            {large=p[16+i].strength;
                            ply=p+i+16;
                            }
                            if(large!=INT_MIN)
                            return ply;
                            
       }
       return NULL;
}
static void in_mid_fielder(Player *player,Player *p,int team_indicator,int strength,int opp_ply)
{
       int str_req,farthest=INT_MIN,x_diff,y_diff,temp;
       
       our_striker far_player[7];
       float distance;
       Player *ptr;
       if(team_indicator==1)
       {             
                          
                      //  the general case : this striker passes the ball to a striker who is in best position
                      
                          if(!(ptr=can_pass( p,team_indicator,p[0].x,p[0].y,strength,opp_ply))) 
                           
                           { 
                                   for(int i=0;i<7;i++)
                              {far_player[i].x_cor=p[5+i].x;
                              far_player[i].ply=5+i;
                              }
                             
                              insert_sort(far_player,7);
                              
                             int i=0;
                                                              
                          while(i!=7&&(p[far_player[i].ply].x!=(*player).x||p[far_player[i].ply].y!=(*player).y))
                              
                        { 
                          
                          str_req=obj.preqpb(p[far_player[i].ply].x,p[far_player[i].ply].y,player->x,player->y);
                          str_req+=strength;                                               
                          if(str_req<(*player).strength&&!(line(p[far_player[i].ply].x,p[far_player[i].ply].y,player->x,player->y,player-p,far_player[i].ply,opp_ply,p)))
                          {       
                                  p[0].x=p[far_player[i].ply].x;
                                  p[0].y=p[far_player[i].ply].y;
                                  ball_hit=true;
                                  player_hit=player-p;
                                  
                                  return;
                          }
                          else
                          {
                              if(!line(p[far_player[i].ply].x,p[far_player[i].ply].y,(*player).x,(*player).y,player-p,far_player[i].ply,opp_ply,p))
                              {
                                       
                                       x_diff=p[far_player[i].ply].x-(*player).x;
                                       y_diff=p[far_player[i].ply].y-(*player).y;
                                       distance= sqrt((x_diff*x_diff)+(y_diff*y_diff));
                                       str_req=0;
                                       int r=1;
                                      
                                       while(((*player).strength-str_req)>0&&((*player).x!=p[far_player[i].ply].x||(*player).y!=p[far_player[i].ply].y))
                                       { 
                                          str_req=obj.preqpb(static_cast<int>((*player).x+((x_diff*r)/distance)),static_cast<int>((*player).y+((y_diff*r)/distance)),(*player).x,(*player).y);
                                          str_req+=strength;
                                          r++;
                                       }  
                                      
                                        str_req=obj.preqp(static_cast<int>((*player).x+((x_diff*(r-2))/distance)),static_cast<int>((*player).y+((y_diff*(r-2))/distance)),p[far_player[i].ply].x,p[far_player[i].ply].y);
                                       if(r!=1&&p[far_player[i].ply].strength-str_req>0)
                                       {
                                               r=r-2;
                                               p[0].x=static_cast<int>((*player).x+((x_diff*r)/distance));                                                                                  
                                               p[0].y=static_cast<int>((*player).y+((y_diff*r)/distance));
                                               player_hit=player-p;
                                               ball_hit=true;
                                                p[far_player[i].ply].x=p[0].x;
                                                p[far_player[i].ply].y=p[0].y;
                                                
                                                return;
                                              
                                               
                                      }
                                      }
                                       
                                       
                                       
                                       
                              }
                            i++;
                                                
                            }
                            }
                          }
        farthest=INT_MAX;
       if(team_indicator==2)
       {
                      
                          
                      //  the general case : this striker passes te ball to a striker who is in best position
                      if(!(ptr=can_pass( p,team_indicator,p[0].x,p[0].y,strength,opp_ply)))
                         
                             { for(int i=0;i<7;i++)
                              {far_player[i].x_cor=p[16+i].x;
                              far_player[i].ply=16+i;
                              }
                             
                              insert_sort(far_player,7);
                             int i=6;
                             while(i!=-1&&p[far_player[i].ply].x!=(*player).x||p[far_player[i].ply].y!=(*player).y)
                          {
                          str_req=obj.preqpb(p[far_player[i].ply].x,p[far_player[i].ply].y,player->x,player->y);                                                                                         str_req=obj.preqpb(p[far_player[i].ply].x,p[far_player[i].ply].y,(*player).x,(*player).y);
                          str_req+=strength;
                          if(str_req<(*player).strength&&!line(p[far_player[i].ply].x,p[far_player[i].ply].y,(*player).x,(*player).y,player-p,far_player[i].ply,opp_ply,p))
                          {
                                  p[0].x=p[far_player[i].ply].x;
                                  p[0].y=p[far_player[i].ply].y;
                                  ball_hit=true;
                                  player_hit= player-p;
                                  return;
                          }
                          else
                          {
                              if(!line(p[far_player[i].ply].x,p[far_player[i].ply].y,(*player).x,(*player).y,player-p,far_player[i].ply,opp_ply,p))
                              {
                                       
                                       x_diff=p[far_player[i].ply].x-(*player).x;
                                       y_diff=p[far_player[i].ply].y-(*player).y;
                                       distance= sqrt((x_diff*x_diff)+(y_diff*y_diff));
                                       str_req=0;
                                       int r=1;
                                       while((*player).strength-str_req>0&&((*player).x!=p[far_player[i].ply].x||(*player).y!=p[far_player[i].ply].y))
                                       { 
                                          str_req=obj.preqpb(static_cast<int>((*player).x+((x_diff*r)/distance))\
                                          ,static_cast<int>((*player).y+((y_diff*r)/distance)),(*player).x,(*player).y);
                                          str_req+=strength;
                                          r++;
                                       }  
                                       str_req=obj.preqp(static_cast<int>((*player).x+((x_diff*(r-2))/distance)),static_cast<int>((*player).y+((y_diff*(r-2))/distance)),p[far_player[i].ply].x,p[far_player[i].ply].y);
                                       if(r!=1&&p[far_player[i].ply].strength-str_req>0)
                                       {
                                               r=r-2;
                                               p[0].x=static_cast<int>((*player).x+((x_diff*r)/distance));                                                                                  
                                               p[0].y=static_cast<int>((*player).y+((y_diff*r)/distance));
                                               player_hit=player-p;
                                               ball_hit=true;
                                               p[far_player[i].ply].x=p[0].x;
                                               p[far_player[i].ply].y=p[0].y;
                                               return;
                                               
                                       }
                                      
                                       
                              }
                              }
                              i--;
                              }
                              }
                              }
}                             
static Player *max_mid_strength(Player *p,int team_indicator,int posx,int posy)
{int str_req,large=INT_MIN,player;
 
       if(team_indicator==1)
       {
          for(int i=0;i<3;i++)
          {
                          str_req=obj.preqp(posx,posy,p[i+5].x,p[5+i].y);
                         
                          if((p[i+5].strength-str_req)>large&&(p[i+5].strength-str_req)>0)
                          {large=p[i+5].strength-str_req;
                          player = 5+i;
                          }
                           
          }  
          
          return p+player;
          }
         if(team_indicator==2)
         {
            for(int i=0;i<3;i++)
            {
                     str_req=obj.preqp(posx,posy,p[16+i].x,p[16+i].y);
                     if((p[i+16].strength-str_req)>large&&(p[i+16].strength-str_req)>0)
                     {
                     large=p[i+16].strength-str_req;
                     player=16+i;
                     }
                     
            }
            return p+player;
            }
         return NULL;    
}                                              
static Player *can_pass(Player *p,int team_indicator,int posx,int posy,int strength,int opp_ply)
 {    /*int str_req,farthest=INT_MIN,far_player,x_diff,y_diff;
       float distance;
       if(team_indicator==1)
       {              // the case when the striker in possestion of ball has a possibility to score
                            for(int k=0;k<3;k++)
                            for(int i=86;i>60;i--)
                            for(int j=1;j<50;j++)
                            {
                             str_req=obj.preqpb(posx,posy,p[5+k].x,p[5+k].y);
                             
                            
                                    
                            str_req+=obj.preqpb(i,j,posx,posy);
                            str_req+=strength;
                           
                            
                            if(str_req<p[5+k].strength&&!line(i,j,p[8+k].x,p[8+k].y,8+k,0,opp_ply,p))
                            {    
                                 p[0].x=i;
                                 p[0].y=j;
                                 p[5+k].x=posx;
                                 p[5+k].y=posy;
                                 ball_hit=true;
                                 player_hit=5+k;
                                 
                                 return p+player_hit;   
                            }
                            }
       }
       */
        int str_req,farthest=INT_MIN,large=INT_MIN,far_player,x_diff,y_diff,player;
       float distance;
       Player *obj_ptr;
       if(team_indicator==1)
       {              // the case when the striker in possestion of ball has a possibility to score
       obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
      
        
      
       
       obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
       obj_ptr->x=p[0].x;
       obj_ptr->y=p[0].y;
       for(int i=5;i<8;i++)
       if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
       {if(p[i].strength>large)
       player=i;
    
       }   
      
                            for(int i=86;i>=61;i--)
                            for(int j=49;j>0;j--)
                            {
                             str_req=obj.preqpb(posx,posy,p[player].x,p[player].y);
                                    
                            str_req+=obj.preqpb(i,j,posx,posy);
                            str_req+=strength;
                            
                            if(str_req<p[player].strength&&!line(i,j,p[player].x,p[player].y,player,0,opp_ply,p))
                            {     
                                
                                 
                                 p[0].x=i;
                                 p[0].y=j;
                                 p[player].x=posx;
                                 p[player].y=posy;
                                 ball_hit=true;
                                 player_hit=player;
                                 goto label;
                                
                                 
                            }
                            }
       label:;
       
                 
       }
      
       if(team_indicator==2)
       {
                /*            // the case when the striker in possestion of ball has a possibility to score
                            for(int k=0;k<3;k++)
                            for(int i=14;i<40;i++)
                            for(int j=1;j<50;j++)
                            {
                             str_req=obj.preqpb(posx,posy,p[16+k].x,p[16+k].y);
                                    
                            str_req+=obj.preqpb(i,j,posx,posy);
                            str_req+=strength;
                            
                            if(str_req<p[16+k].strength&&!line(i,j,p[16+k].x,p[16+k].y,16+k,0,opp_ply,p))
                            {     
                                
                                 
                                 p[0].x=i;
                                 p[0].y=j;
                                 p[16+k].x=posx;
                                 p[16+k].y=posy;
                                 ball_hit=true;
                                 player_hit=16+k;
                                 return p+player_hit;   
                            }
                            }
                            */
        obj_ptr=max_strength(p,team_indicator,p[0].x,p[0].y);
      
        
       
       
       obj_ptr->strength-=obj.preqp(p[0].x,p[0].y,obj_ptr->x, obj_ptr->y);
       obj_ptr->x=p[0].x;
       obj_ptr->y=p[0].y;
       for(int i=16;i<19;i++)
       if(p[i].x==obj_ptr->x&&p[i].y==obj_ptr->y)
       {if(p[i].strength>large)
       player=i;
    
       }   
       
                            for(int i=14;i<40;i++)
                            for(int j=49;j>0;j--)
                            {
                             str_req=obj.preqpb(posx,posy,p[player].x,p[player].y);
                                    
                            str_req+=obj.preqpb(i,j,posx,posy);
                            str_req+=strength;
                            
                            if(str_req<p[player].strength&&!line(i,j,p[player].x,p[player].y,player,0,opp_ply,p))
                            {     
                               
                                 
                                 p[0].x=i;
                                 p[0].y=j;
                                 p[player].x=posx;
                                 p[player].y=posy;
                                 ball_hit=true;
                                 player_hit=player;
                                 goto label1;
                                
                                 
                            }
                            } 
       label1:;
                        
       }
        return NULL; 
}                    
                                           
                          


