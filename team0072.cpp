                          #include<stdio.h>

#include<stdlib.h>
#include<string.h>
#include<math.h>

using namespace std;

class team0072  //The name of your class should be teamxxxx where xxxx is the no. u will get at the time of registration and will
{                //be unique for every participant
  private:
  
  int team,pl,ph,pl1,ph1,player_no;  //team is a variable used in player function which tells all of the functions defined by the participant what their team no. is 
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
	 
	 
  public:
   
 
int player_selection(struct player *p,int fx,int fy,int avoid)
 {
  int max=0,pos=0;                         //pos is my team player no. having maximum strength 
  
  for(int i=pl;i<=ph;i++)
   { 
          
  int req=preqp(fx,fy,p[i].x,p[i].y);
          if((p[i].strength-req)>=max&&i!=avoid)
          {max=p[i].strength-req;
             pos=i;
          }   
   }       
    
  //int req=preqp(b[0],b[1],p[pos].x,p[pos].y);
  //p[pos].strength=p[pos].strength-req;//i m reducing stength because i have made mind to use this player
  
  return pos;
}          
 
   
void Players_In_Dee(struct player*p,int a[],int team_no)
 { 
     int pos=0;
     int i=0;
    while(i<=ph)
    {
            if(team_no==2)
            {
                          if(p[i].x>=1&&p[i].x<= 14)
                          {
                                                 if(p[i].y>=5&&p[i].y<=10||p[i].y>=40&&p[i].y<=45)
                                                     {a[pos]=i;
                                                      pos++;
                                                      }
                          }
                          
                          else if(p[i].x>=15&&p[i].x<=40)
                           { if(p[i].y>=5&&p[i].y<=45)
                                                     {a[pos]=i;
                                                      pos++;
                                                      }
                          }
                                                      
            }                                                         
       
       
        else if(team_no==1)
            {
                         if(p[i].x>=86&&p[i].x<= 99)
                          {
                                                 if(p[i].y>=5&&p[i].y<=10||p[i].y>=40&&p[i].y<=45)
                                                     {a[pos]=i;
                                                      pos++;
                                                      }
                          }
                          
                          else if(p[i].x>=60&&p[i].x<=85)
                           { if(p[i].y>=5&&p[i].y<=45)
                                                     {a[pos]=i;
                                                     pos++;
                                                      }
                          }
                                                      
            }                                                         
   
          if(i==0)
            i=pl;
            
          else
            i++; 
   }//end of while loop
   
   
}  

   
   
   
   int intercept(int ix,int iy,int fx,int fy,struct player *p)
{ 
  
    int x1,x2,y1,y2;//making a copy of passed coordinates
    x1=ix;y1=iy;
    x2=fx;y2=fy;
    while(!(x1==x2&&y1==y2))    
     {
          int flag=0;
          if(x1<x2)
          {
                   x1++;
                   if(y1<y2)
                    y1++;
                    
                   else if(y1>y2)
                    y1--;
                    
              flag=1;
          }//end od if
          
          
         else if(x1>x2)
         {
             x1--;
             if(y1<y2)
                    y1++;
                    
             else if (y1>y2)
                    y1--;
             flag=1;
         }//end of else
         
        if(x1==x2&&y1!=y2&&flag==0)
          
         {    if(y1<y2)
                    y1++;
                    
             else if(y1>y2)
                    y1--;
         }
         
        if(y1==y2&&x1!=x2&&flag==0)
         {
             if(x1<x2)
                    x1++;
                    
             else if(x1>x2)
                    x1--;
         } 
         
       
       for(int i=pl1;i<=ph1;i++)             //loop checks one by one for other team player
          if(p[i].x==x1&&p[i].y==y1)
                 return i;
                 
  }//    end  of while loop
       return 0; 
    
}                         


      
   int init(int team_number, struct player *p,char farray[][51])   // this fn must be there in your program ,it will be called only 
	{                                                             //once at the beginning of the program .It will tell u whether u are 
      team=team_number;                                 //player 1 or 2 and this will also give u the basic fieldarray ie where there is  
	
           player_no=team;
          int player_num;
         
          if(player_no==1)
	 {

		pl=1;            //pl shows the lower limit and ph shows the upper limit of players in the array of structures ,i.e. if player
		ph=11;           //is 1st then his players will be 1 to 11 and if he is 2nd then his players will be 12 to 22
		pl1=12;
		ph1=22;
        player_num=1;
	 }

	 else
	 {
		  pl=12;
		  ph=22;
		  pl1=1;
		  ph1=11;
          player_num=2;
	 }
    
    
    
    }                                                  //a goal or a dee or a boundary and struct player *p gives u the initial player 
                                                 //distribution in the field
                                                 
    
    
    int player(struct player *p)  //This fn should contain the strategies u want to implement.You can also define other fns in your 
     {                          //class but u can call them with this fn only .This fn has to receive the array of 23 structures from the controller fn which 
       
         
         
   
         int i,j,max=0,ballplayer;      //max is strength of other team player present at ball
    for(i=pl1;i<=ph1;i++)
    {
         if(p[i].x==p[0].x&&p[0].y==p[i].y)
            if(p[i].strength>max)
               max=p[i].strength;
    }                           
    ballplayer=player_selection(p,p[0].x,p[0].y,-1);//working correctly
            
            if(ballplayer==0)  //No player has strength left
             return -1;
            int reqmove=preqp(p[0].x,p[0].y,p[ballplayer].x,p[ballplayer].y);
            p[ballplayer].x=p[0].x;p[ballplayer].y=p[0].y;    //always move player  to ball defence strategy
                                  
    
    for( j=10;j<=40;j++)
     {
            if (player_no==2) 
             i=14;
            
            else
              i=86;
            int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           p[0].x=i;p[0].y=j;  
                             return ballplayer;
                 }
                
    
            }   
    }//end of for loop 
    
     if(player_no==2) 
      for(i=1;i<=14;i++)                  //loop for left side of goal
       {
            j=10;                
            
            int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             return ballplayer;
                 }
                
    
            }      
            }//end of for loop 
    
       else
            for(i=99;i>=86;i--)                  //loop for left side of goal
       {
            j=10;                
            
            int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             return ballplayer;
                 }
                
    
            }      
            }//end of for loop 
     if(player_no==2)  
     for(i=1;i<=14;i++)                  //loop for right side of goal
       {
            j=40;                
            
            int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             return ballplayer;
                 }
                
    
            }      
       }//end of for loop 
             
      else
      for(i=99;i>=86;i--)                  //loop for right side of goal
       {
            j=40;                
            
            int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             return ballplayer;
                 }
                
    
            }      
       }
      int a[11];                  //contains my players in opposite dee 
      for(i=0;i<11;i++)         //initialize elements to -1
         a[i]=-1;
      Players_In_Dee(p, a, player_no);
      
      int ball_in_dee=0;
          
           if(a[0]==0)
            ball_in_dee=1;
            
            
                     
                 
if(ball_in_dee==0)//ball is not in dee 
{
    
    int b[11],pos=0;
    
    for(i=0;a[i]!=-1&&i<11;i++)
     {
         
         
          
         int req=preqpb(p[a[i]].x,p[a[i]].y,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,p[a[i]].x,p[a[i]].y,p);                
                if(status==0)
                 {           
                     if(a[i]!=ballplayer)
                    { b[pos]=a[i];
                     pos++; }                        }
            
            }//end of if
                      
                                   
     }//end of foor loop or if i dont know
      int max1=0,use=-1;
     
     for(i=0;i<pos&&i<11;i++)     //selects player with max strength
           if(p[b[i]].strength>max1)
              use=i;
    
    if(use !=-1)
    {   
      p[0].x=p[b[use]].x;p[0].y=p[b[use]].y;  
      return ballplayer;
    }     
           
   if(player_no==2)  //Hit ball in dee
    {for(i=40;i>=15;i--)
      {
         for(j=5;j<=45;j++)
         {
                   int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of for
  
  
     }// end of outer for 
  //}//end of ball not in dee 
    
     for(i=14;i>=1;i--)
      {
         for(j=10;j<=5;j--)
         {
                   int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of for
  
  
     }// end of outer for 
  
     
       for(i=14;i>=1;i--)
      {
         for(j=40;j<=45;j++)
         {
                   int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of for
  
  
     }// end of outer for 

     
     
     } //end of if for team =2
  
  
  if(player_no==1)  //Hit ball in dee
    {for(i=60;i<86;i++)
      {
         for(j=5;j<=45;j++)
         {
                   int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of for
  
  
     }// end of outer for 
  
    
     for(i=86;i<=99;i++)
      {
         for(j=10;j<=5;j--)
         {
                   int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of for
  
  
     }// end of outer for 
  
     
       for(i=86;i<=99;i++)
      {
         for(j=40;j<=45;j++)
         {
                   int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of for
  
  
     }// end of outer for 

     
     
     } //end of if for team =1
  
  if(player_no==2)       //hit outside of dee
  {for(i=1;i<40;i++)
    {
           for(j=1;j<5;j++)
            {             
              int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for                    
             for(j=45;j<50;j++)
            {             
              int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for   
  
  
        }//end of outer for loop
  
       for(i=40;i<p[ballplayer].x;i++)
       {
             for(j=1;j<50;j++)
             {
                int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for 
            }//end of outer for loop              
            
           
           i=p[ballplayer].x;
           for(j=1;j<50;j++)
           {
              int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i--;
                             if(++j<50)
                             p[play_move].y=j++;
                             
                             else
                             p[play_move].y=j--;
                             
                             play_move=player_selection(p,i,j,play_move);
                             if(play_move!=ballplayer)
                             {  p[play_move].x=i;p[play_move].y=j;
                             }
                             
                             return ballplayer;
                 }
                
    
            }                               
            }//end of forloop   
  }///end of if for tem=2 
   
  
  if(player_no==1)       //hit outside of dee
  {for(i=60;i<100;i++)
    {
           for(j=1;j<5;j++)
            {             
              int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for                    
             for(j=45;j<50;j++)
            {             
              int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for   
  
  
        }//end of outer for loop
  
       for(i=60;i>p[ballplayer].x;i--)
       {
             for(j=1;j<50;j++)
             {
                int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for 
            }//end of outer for loop              
            
           
           i=p[ballplayer].x;
           for(j=1;j<50;j++)
           {
              int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i++;
                             if(++j<50)
                             p[play_move].y=j++;
                             
                             else
                             p[play_move].y=j--;
                             
                             play_move=player_selection(p,i,j,play_move);
                             if(play_move!=ballplayer)
                             {  p[play_move].x=i;p[play_move].y=j;
                             }
                             
                             return ballplayer;
                 }
                
    
            }                               
            }//end of forloop   
  }///end of if for tem=1
   
  
  
  }//end of ball not in dee 
    
    
   if(ball_in_dee =1)     //ball in dee
   {
              int b[11],pos=0;    //pass to my player outside dee
             int c[11],pos2=0;
             
           for(i=0;i<11;i++)
           {
                b[i]=-1;c[i]=-1;
           }     //initializ to -1            
           
           
           for(i=pl;i<=ph;i++)
             { int flag=0; 
              for(j=0;a[j]!=-1&&j<11;j++) 
                 if(i==a[j])
                    flag=1;
                    
              if(flag==0)
               {
                   c[pos2]=i;
                   pos2++;
               }
           }//end of for loop              
                    
    for(i=0;c[i]!=-1&&i<11;i++)
     {
          
          
         int req=preqpb(p[c[i]].x,p[c[i]].y,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,p[c[i]].x,p[c[i]].y,p);                
                if(status==0)
                 {  if(c[i]==ballplayer)
                     {         
                     b[pos]=c[i];
                     pos++;                         }
                     }             
            }//end of if
                      
                                   
     }//end of foor loop or if i dont know
      int max1=0,use=-1;
     
     for(i=0;i<pos&&i<11;i++)     //selects player with max strength
           if(p[b[i]].strength>max1)
              use=i;
    
    
    
       if(use!=-1)
      {p[0].x=p[b[use]].x;p[0].y=p[b[use]].y;  
      return ballplayer;}
            
                  
                  
     if(player_no==2)
      {
                     
           for(i=1;i<=40;i++)
              {
           for(j=1;j<5;j++)
            {             
              int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for                    
             for(j=45;j<50;j++)
            {             
              int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for   
  
  
        }//end of outer for loop
  
        for(i=41;i<50;i++)
        {             
           for(j=1;j<50;j++)
            {
               int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for   
  
  
        }//end of outer for loop
                         
      }//end of team 2                            
   
   
   else
   {
       for(i=60;i<100;i++)
    {
           for(j=1;j<5;j++)
            {             
              int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for                    
             for(j=45;j<50;j++)
            {             
              int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for   
  
  
        }//end of outer for loop
   
             for(i=60;i<50;i--)
                { 
                     for(j=1;j<50;j++)
                       { int req=preqpb(i,j,p[0].x,p[0].y);
            //cout<<req<<"\n";
            //cout<<p[ballplayer].strength-reqmove<<"\n";
            
            if(req<p[ballplayer].strength-reqmove-max)
             { 
                int status=intercept(p[0].x,p[0].y,i,j,p);
                
                if(status==0)
                 {           
                             p[0].x=i;p[0].y=j;  
                             int play_move;
                             play_move=player_selection(p,i,j,ballplayer);
                             p[play_move].x=i;p[play_move].y=j;
                             return ballplayer;
                 }
                
    
            }                               
            }//end of  inner for   
  
  
        }//end of outer for loop
             
      }//end of else for team=1
   }//end of ball in dee               
    
    
    return -1;
     
       
       
       
       }                          //contain the positions of the 22 players and the ball at that time .It is also supposed to return the 
                                 //the no of the player who will hit the ball to the controller fn
};//end of class  
