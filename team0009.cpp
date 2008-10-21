#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define REGION1(x,y) \
        (x>=1 && x<=29 && y>=1 && y<=16)
#define REGION2(x,y) \
        (x>=15 && x<=29 && y>=17 && y<=32)
#define REGION3(x,y) \
        (x>=1 && x<=29 && y>=33 && y<=49)
#define REGION4(x,y) \
        (x>=30 && x<=43 && y>=1 && y<=24)
#define REGION5(x,y) \
        (x>=30 && x<=43 && y>=25 && y<=49)
#define REGION6(x,y) \
        (x>=44 && x<=57 && y>=1 && y<=24)
#define REGION7(x,y) \
        (x>=44 && x<=57 && y>=25 && y<=49)
#define REGION8(x,y) \
        (x>=58 && x<=71 && y>=1 && y<=24)
#define REGION9(x,y) \
        (x>=58 && x<=71 && y>=25 && y<=49)
#define REGION10(x,y) \
        (x>=72 && x<=85 && y>=1 && y<=24)
#define REGION11(x,y) \
        (x>=72 && x<=85 && y>=25 && y<=49)

#define REGION1R(x,y) \
        (x>=71 && x<=99 && y>=1 && y<=16)
#define REGION2R(x,y) \
        (x>=71 && x<=85 && y>=17 && y<=32)
#define REGION3R(x,y) \
        (x>=71 && x<=99 && y>=33 && y<=49)
#define REGION4R(x,y) \
        (x>=57 && x<=70 && y>=1 && y<=24)
#define REGION5R(x,y) \
        (x>=57 && x<=70 && y>=25 && y<=49)
#define REGION6R(x,y) \
        (x>=43 && x<=56 && y>=1 && y<=24)
#define REGION7R(x,y) \
        (x>=43 && x<=56 && y>=25 && y<=49)
#define REGION8R(x,y) \
        (x>=29 && x<=42 && y>=1 && y<=24)
#define REGION9R(x,y) \
        (x>=29 && x<=42 && y>=25 && y<=49)
#define REGION10R(x,y) \
        (x>=15 && x<=28 && y>=1 && y<=24)
#define REGION11R(x,y) \
        (x>=15 && x<=28 && y>=25 && y<=49)


#define POSESS(i) \
		(p[i].x==p[0].x && p[i].y==p[0].y)

using namespace std;

class team0009  //The name of your class should be teamxxxx where xxxx is the no. u will get at the time of registration and will
{                //be unique for every participant
  private:
  
  int team;  //team is a variable used in player function which tells all of the functions defined by the participant what their team no. is 
             //it is not mandatory for the player to use this variable .player can use any other means to satisfy the need
  //private fns 
  //this fn returns the strength req to move your player from one place to another 
  int final_x,final_y;

  int preqp(int finalx,int finaly, int initialx ,int initialy )
	{float req;
    req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
    return (int)req;}     

//this fn returns the strength req by your hitter to move the ball from one place to another 
  int preqpb(int finalx,int finaly, int initialx ,int initialy )
	{float req; int i;
    req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	 i=(int)req;
	 return i;} 
	 
	 
  public:
        
   int goalable1(struct player *p, int hitter)
   {
       int i,j,k,flag,deviation=0,dest_x,dest_y;
             
       dest_x=86;

       dest_y=p[0].y;
       
       if(p[hitter].strength>=preqpb(dest_x,dest_y,p[0].x,p[0].y))
       for(;deviation<20;deviation++)
       {
               i=p[0].x;
               j=p[0].y;
               dest_y=dest_y+deviation;                    
               flag=1;
                          if(dest_y>=10 && dest_y<=40)
                                     while(i!=dest_x || j!=dest_y)
                                     {
                                                      if(i!=dest_x)
                                                      i++;
                                                      if(j!=dest_y)
                                                      j++;
            
                                                      flag=0;
                                                      for(k=1;k<=22;k++)
                                                      {
                                                              if(i==p[k].x&&j==p[k].y)
                                                              {
                                                                              flag=1;
                                                                              break;
                                                              }
                                                      }
                                                      if(flag==1)
                                                      break;      
                                     }
                 
                 if(flag==0)
                 {
                            final_x=dest_x;
                            final_y=dest_y;
                            if(p[hitter].strength>=preqpb(dest_x,dest_y,p[0].x,p[0].y))
                            return 1;
                 }
          
                 i=p[0].x;
                 j=p[0].y;
                 dest_y=dest_y-2*deviation;       
                 flag=1;
                          if(dest_y>=10 && dest_y<=40)
                                     while(i!=dest_x || j!=dest_y)
                                     {
                                                      if(i!=dest_x)
                                                      i++;
                                                      if(j!=dest_y)
                                                      j--;
            
                                                      flag=0;
                                                      for(k=1;k<=22;k++)
                                                      {
                                                              if(i==p[k].x&&j==p[k].y)
                                                              {
                                                                              flag=1;
                                                                              break;
                                                              }
                                                      }      
                                                      if(flag==1)
                                                      break;
                                     }
                 if(flag==0)
                 {
                            final_x=dest_x;
                            final_y=dest_y;
                            if(p[hitter].strength>=preqpb(dest_x,dest_y,p[0].x,p[0].y))
                            return 1;
                 }
                 dest_y=dest_y+deviation;
       }
    return 0;
    }     
         
    int goalable2(struct player *p, int hitter)
    {
       int i,j,k,flag,deviation=0,dest_x,dest_y;
             
       dest_x=14;
       dest_y=p[0].y;
       
       if(p[hitter].strength>=preqpb(dest_x,dest_y,p[0].x,p[0].y))
       for(;deviation<20;deviation++)
       {
               i=p[0].x;
               j=p[0].y;
               dest_y=dest_y+deviation;                    
               flag=1;
                          if(dest_y>=10 && dest_y<=40)
                                     while(i!=dest_x || j!=dest_y)
                                     {
                                                      if(i!=dest_x)
                                                      i--;
                                                      if(j!=dest_y)
                                                      j++;
            
                                                      flag=0;
                                                      for(k=1;k<=22;k++)
                                                      {
                                                              if(i==p[k].x&&j==p[k].y)
                                                              {
                                                                              flag=1;
                                                                              break;
                                                              }
                                                      }
                                                      if(flag==1)
                                                      break;      
                                     }
                 
                 if(flag==0)
                 {
                            final_x=dest_x;
                            final_y=dest_y;
//                            if(p[hitter].strength>=preqpb(dest_x,dest_y,p[0].x,p[0].y))
                            return 1;
                 }
          
                 i=p[0].x;
                 j=p[0].y;
                 dest_y=dest_y-2*deviation;       
                 flag=1;
                          if(dest_y>=10 && dest_y<=40)
                                     while(i!=dest_x || j!=dest_y)
                                     {
                                                      if(i!=dest_x)
                                                      i--;
                                                      if(j!=dest_y)
                                                      j--;
            
                                                      flag=0;
                                                      for(k=1;k<=22;k++)
                                                      {
                                                              if(i==p[k].x&&j==p[k].y)
                                                              {
                                                                              flag=1;
                                                                              break;
                                                              }
                                                      }      
                                                      if(flag==1)
                                                      break;
                                     }
                 if(flag==0)
                 {
                            final_x=dest_x;
                            final_y=dest_y;
//                            if(p[hitter].strength>=preqpb(dest_x,dest_y,p[0].x,p[0].y))
                            return 1;
                 }
                 dest_y=dest_y+deviation;
       }
    return 0;
    }  

    int passable(struct player *p,int hitter, int recvr)
    {
        int i,j,k,finali,finalj,xdiff,ydiff;
      
		finali=p[recvr].x;
        finalj=p[recvr].y;
        i=p[hitter].x;
        j=p[hitter].y;
        xdiff=finali-i;   
        ydiff=finalj-j;   
      
        while(!(i==finali&&j==finalj))
        {
              if(i!=finali)
                 (xdiff>0)?i++:i--;
              if(j!=finalj)
                 (ydiff>0)?j++:j--;
        
              if(!(i==finali&&j==finalj))
                 for(k=1;k<=22;k++)
                 {
                                   if((i==p[k].x)&&(j==p[k].y))
                                   return 0;
                 }      //loop to check whether any of the player intersect the ball
        }
        return 1;
     }
    
    int init(int team_number, struct player *p,char farray[][51])   // this fn must be there in your program ,it will be called only 
	{                                                             //once at the beginning of the program .It will tell u whether u are 
      team=team_number;                                 //player 1 or 2 and this will also give u the basic fieldarray ie where there is  
	}                                                  //a goal or a dee or a boundary and struct player *p gives u the initial player 
                                                 //distribution in the field
                                                 
int player(struct player *p)  //This fn should contain the strategies u want to implement.You can also define other fns in your 
{   
                                //class but u can call them with this fn only .This fn has to receive the array of 23 structures from the controller fn which 
                                 //contain the positions of the 22 players and the ball at that time .It is also supposed to return the 
                                 //the no of the player who will hit the ball to the controller fn

	int player_with_ball,i;


	if(team==1)
    {
			 if (REGION1(p[0].x,p[0].y))
             { 
                              player_with_ball=2;
                              
                              if(p[2].strength!=0)
                              {
							   p[2].x=p[0].x;
							   p[2].y=p[0].y;
                              }
			 }
             else if (REGION2(p[0].x,p[0].y))
             {
                              player_with_ball=1;
                              if(p[1].strength!=0)
                              {
							   p[1].x=p[0].x;
							   p[1].y=p[0].y;
                              }
			 }
			 else if (REGION3(p[0].x,p[0].y))
			 {
							  player_with_ball=4;
                              if(p[4].strength!=0)
                              {
                               p[4].x=p[0].x;
							   p[4].y=p[0].y;
                              }
             }
             else if (REGION4(p[0].x,p[0].y))
             {
							  player_with_ball=5;
							  if(p[5].strength!=0)
                              {
                               p[5].x=p[0].x;
							   p[5].y=p[0].y;
                              }
             }
			 else if (REGION5(p[0].x,p[0].y))
			 {
							  player_with_ball=7;
                              if(p[7].strength!=0)
                              {
                               p[7].x=p[0].x;
							   p[7].y=p[0].y;
                              }
             }
			 else if (REGION6(p[0].x,p[0].y))
			 {
                  			  player_with_ball=8;
                              if(p[8].strength!=0)
                              {
							  p[8].x=p[0].x;
							  p[8].y=p[0].y;
                              }
             }	
			 else if (REGION7(p[0].x,p[0].y))
			 {
					          player_with_ball=10;
                              if(p[10].strength!=0)
                              {
                              p[10].x=p[0].x;
							  p[10].y=p[0].y;
                              }
             }
			 else if (REGION8(p[0].x,p[0].y))
			 {
							  player_with_ball=11;
                              if(p[11].strength!=0)
                              {		  
                              p[11].x=p[0].x;
							  p[11].y=p[0].y;
                              }
             }
	         else if (REGION9(p[0].x,p[0].y))
	         {
							  player_with_ball=9;
                              if(p[9].strength!=0)
                              {
                              p[9].x=p[0].x;
							  p[9].y=p[0].y;
                              }
             }
			 else if (REGION10(p[0].x,p[0].y))
			 {
							  player_with_ball=3;
                              if(p[3].strength!=0)
                              {
							  p[3].x=p[0].x;
							  p[3].y=p[0].y;
                              }
             }
			 else if (REGION11(p[0].x,p[0].y))
             {	     		  
                              player_with_ball=6;
                              if(p[6].strength!=0)
                              {                        
							  p[6].x=p[0].x;
							  p[6].y=p[0].y;
                              }
             }

			 for(i=1;i<=11;i++)
			 {
				if(player_with_ball!=i)
				{
					switch(i)
					{
						case 2:	
                               if(p[2].strength!=0)
                               { 
                                p[2].x=29;
								p[2].y=10;
                               }
                            	break;
						case 1:	
                                if(p[1].strength!=0)
                                {
                                p[1].x=29;
								p[1].y=25;
                                }
                                break;
						case 4:	
                                if(p[4].strength!=0)
                                {
                                p[4].x=29;
								p[4].y=40;
                                }
                                break;
						case 5:	
                                if(p[5].strength!=0)
                                {
                                 p[5].x=43;
								 p[5].y=15;
                                }
                                break;
						case 7:	
                                if(p[7].strength!=0)
                                {
                                p[7].x=43;
								p[7].y=35;
                                }
                                break;
						case 8:	
                                if(p[8].strength!=0)
                                {
                                p[8].x=57;
								p[8].y=15;
                                }
                                break;
						case 10:	
                                if(p[10].strength!=0)
                                {
                                p[10].x=57;
								p[10].y=35;
                                }
                                break;
						case 11:	
                                if(p[11].strength!=0)
                                {
                                p[11].x=71;
								p[11].y=15;
                                }
                                break;
						case 9:	
                                if(p[9].strength!=0)
                                {
                                p[9].x=71;
								p[9].y=35;
                                }
                                break;
						case 3:
                                if(p[3].strength!=0)
                                {
                                p[3].x=80;
								p[3].y=15;
                                }
                                break;
						case 6:
                                if(p[6].strength!=0)
                                {
                                p[6].x=80;
								p[6].y=35;
                                } 
                                break;
					}
				}
			 }


             if (POSESS(2))
             {
                           if(goalable1(p,2))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 2;                  
                           }
                           else
                           {
                                   if(p[2].strength!=0)
                                   {
                                                       if(passable(p,2,5))
                                                       {
                                                        p[0].x=p[5].x;
                                                        p[0].y=p[5].y;                  
                                                        return 2;                  
                                                       }
                                                       else
                                                       {
                                                        p[0].x=p[1].x;
                                                        p[0].y=p[1].y;                  
                                                        return 2;                  
                                                       }
                                   }
                           } 
             }
             else if (POSESS(1))
             {
                           if(goalable1(p,1))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 1;                  
                           }
                           else
                           {
                               if(p[1].y<25)
                               {
                                            if(p[1].strength!=0)
                                            {
                                                         if(passable(p,1,5))
                                                         {
                                                         p[0].x=p[5].x;
                                                         p[0].y=p[5].y;                  
                                                         return 1; 
                                                         }       
                                                         else
                                                         {
                                                         p[0].x=p[2].x;
                                                         p[0].y=p[2].y;                  
                                                         return 1;                  
                                                         }          
                                            }
                               }
                               else
                               {
                                            if(p[1].strength!=0)
                                            {
                                                         if(passable(p,1,7))
                                                         {
                                                         p[0].x=p[7].x;
                                                         p[0].y=p[7].y;                  
                                                         return 1;                  
                                                         }
                                                         else
                                                         {
                                                         p[0].x=p[4].x;
                                                         p[0].y=p[4].y;                  
                                                         return 1;                  
                                                         }
                                            }
                               }
                           } 

			 }
			 else if (POSESS(4))
			 {
                           if(goalable1(p,4))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 4;                  
                           }
                           else
                           {
                                            if(p[4].strength!=0)
                                            {
                                                        if(passable(p,4,7))
                                                        {
                                                        p[0].x=p[7].x;
                                                        p[0].y=p[7].y;                  
                                                        return 4;        
                                                        }
                                                        else
                                                        {
                                                        p[0].x=p[1].x;
                                                        p[0].y=p[1].y;                  
                                                        return 4;                  
                                                        }
                                             }          
                           } 

			 }
             else if (POSESS(5))
             {
                           if(goalable1(p,5))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 5;                  
                           }
                           else
                           {
                                            if(p[5].strength!=0)
                                            {                               
                                                                if(passable(p,5,8))
                                                                {
                                                                p[0].x=p[8].x;
                                                                p[0].y=p[8].y;                  
                                                                return 5;        
                                                                }
                                                                else
                                                                {
                                                                p[0].x=p[7].x;
                                                                p[0].y=p[7].y;                  
                                                                return 5;                  
                                                                }
                                             }          
                           } 

			 }
			 else if (POSESS(7))
			 {
                           if(goalable1(p,7))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 7;                  
                           }
                           else
                           {
                                            if(p[7].strength!=0)
                                            {                            
                                                                if(passable(p,7,10))
                                                                {
                                                                p[0].x=p[10].x;
                                                                p[0].y=p[10].y;                  
                                                                return 7;        
                                                                }
                                                                else
                                                                {
                                                                p[0].x=p[5].x;
                                                                p[0].y=p[5].y;                  
                                                                return 7;                  
                                                                }
                                            }          
                           } 

			 }
			 else if (POSESS(8))
			 {
                           if(goalable1(p,8))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 8;                  
                           }
                           else
                           {
                                            if(p[8].strength!=0)
                                            {
                                                                if(passable(p,8,11))
                                                                {
                                                                p[0].x=p[11].x;
                                                                p[0].y=p[11].y;                  
                                                                return 8;        
                                                                }
                                                                else
                                                                {
                                                                p[0].x=p[10].x;
                                                                p[0].y=p[10].y;                  
                                                                return 8;                  
                                                                }
                                            }          
                           } 

             }	
			 else if (POSESS(10))
			 {
                           if(goalable1(p,10))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 10;                  
                           }
                           else
                           {
                                            if(p[10].strength!=0)                                   
                                            {
                                                               if(passable(p,10,9))
                                                               {
                                                               p[0].x=p[9].x;
                                                               p[0].y=p[9].y;                  
                                                               return 10;
                                                               }
                                                               else
                                                               {
                                                               p[0].x=p[8].x;
                                                               p[0].y=p[8].y;                  
                                                               return 10;                  
                                                               }
                                            }
                           } 

			 }
			 else if (POSESS(11))
			 {
                           if(goalable1(p,11))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 11;                  
                           }
                           else
                           {
                                            if(p[11].strength!=0)
                                            {                            
                                                             if(passable(p,11,3))
                                                             {
                                                             p[0].x=p[3].x;
                                                             p[0].y=p[3].y;                  
                                                             return 11;                  
                                                             }
                                                             else
                                                             {
                                                             p[0].x=p[9].x;
                                                             p[0].y=p[9].y;                  
                                                             return 11;                  
                                                             }
                                            }
                           } 

		     }
	         else if (POSESS(9))
	         {
                           if(goalable1(p,9))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 9;                  
                           }
                           else
                           {
                                            if(p[9].strength!=0)
                                            {                            
                                                            if(passable(p,9,6))
                                                            {
                                                            p[0].x=p[6].x;
                                                            p[0].y=p[6].y;                  
                                                            return 9;
                                                            }
                                                            else
                                                            {
                                                            p[0].x=p[11].x;
                                                            p[0].y=p[11].y;                  
                                                            return 9;                  
                                                            }
                                            }                  
                           } 

	         }
			 else if (POSESS(3))
			 {
                           if(goalable1(p,3))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 3;                  
                           }
			 }
			 else if (POSESS(6))
             {
                           if(goalable1(p,6))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 6;                  
                           }
             }
    return -1;
    }
             
    else if(team==2)
    {
			 if (REGION1R(p[0].x,p[0].y))
             { 
                              player_with_ball=13;
                              if(p[13].strength!=0)
                              {
							   p[13].x=p[0].x;
							   p[13].y=p[0].y;
                              }
			 }
             else if (REGION2R(p[0].x,p[0].y))
             {
                              player_with_ball=12;
                              if(p[12].strength!=0)
                              {
							   p[12].x=p[0].x;
							   p[12].y=p[0].y;
                              }
			 }
			 else if (REGION3R(p[0].x,p[0].y))
			 {
							  player_with_ball=15;
                              if(p[15].strength!=0)
                              {
                               p[15].x=p[0].x;
							   p[15].y=p[0].y;
                              }
             }
             else if (REGION4R(p[0].x,p[0].y))
             {
							  player_with_ball=16;
							  if(p[16].strength!=0)
                              {
                               p[16].x=p[0].x;
							   p[16].y=p[0].y;
                              }
             }
			 else if (REGION5R(p[0].x,p[0].y))
			 {
							  player_with_ball=18;
                              if(p[18].strength!=0)
                              {
                               p[18].x=p[0].x;
							   p[18].y=p[0].y;
                              }
             }
			 else if (REGION6R(p[0].x,p[0].y))
			 {
                  			  player_with_ball=19;
                              if(p[19].strength!=0)
                              {
							  p[19].x=p[0].x;
							  p[19].y=p[0].y;
                              }
             }	
			 else if (REGION7R(p[0].x,p[0].y))
			 {
					          player_with_ball=21;
                              if(p[21].strength!=0)
                              {
                              p[21].x=p[0].x;
							  p[21].y=p[0].y;
                              }
             }
			 else if (REGION8R(p[0].x,p[0].y))
			 {
							  player_with_ball=22;
                              if(p[22].strength!=0)
                              {		  
                              p[22].x=p[0].x;
							  p[22].y=p[0].y;
                              }
             }
	         else if (REGION9R(p[0].x,p[0].y))
	         {
							  player_with_ball=20;
                              if(p[20].strength!=0)
                              {
                              p[20].x=p[0].x;
							  p[20].y=p[0].y;
                              }
             }
			 else if (REGION10R(p[0].x,p[0].y))
			 {
							  player_with_ball=14;
                              if(p[14].strength!=0)
                              {
							  p[14].x=p[0].x;
							  p[14].y=p[0].y;
                              }
             }
			 else if (REGION11R(p[0].x,p[0].y))
             {	     		  
                              player_with_ball=17;
                              if(p[17].strength!=0)
                              {                        
							  p[17].x=p[0].x;
							  p[17].y=p[0].y;
                              }
             }

			 for(i=12;i<=22;i++)
			 {
				if(player_with_ball!=i)
				{
					switch(i)
					{
						case 13:	
                               if(p[13].strength!=0)
                               { 
                                p[13].x=71;
								p[13].y=10;
                               }
                            	break;
						case 12:	
                                if(p[12].strength!=0)
                                {
                                p[12].x=71;
								p[12].y=25;
                                }
                                break;
						case 15:	
                                if(p[15].strength!=0)
                                {
                                p[15].x=71;
								p[15].y=40;
                                }
                                break;
						case 16:	
                                if(p[16].strength!=0)
                                {
                                 p[16].x=57;
								 p[16].y=15;
                                }
                                break;
						case 18:	
                                if(p[18].strength!=0)
                                {
                                p[18].x=57;
								p[18].y=35;
                                }
                                break;
						case 19:	
                                if(p[19].strength!=0)
                                {
                                p[19].x=43;
								p[19].y=15;
                                }
                                break;
						case 21:	
                                if(p[21].strength!=0)
                                {
                                p[21].x=43;
								p[21].y=35;
                                }
                                break;
						case 22:	
                                if(p[22].strength!=0)
                                {
                                p[22].x=29;
								p[22].y=15;
                                }
                                break;
						case 20:	
                                if(p[20].strength!=0)
                                {
                                p[20].x=29;
								p[20].y=35;
                                }
                                break;
						case 14:
                                if(p[14].strength!=0)
                                {
                                p[14].x=20;
								p[14].y=15;
                                }
                                break;
						case 17:
                                if(p[17].strength!=0)
                                {
                                p[17].x=20;
								p[17].y=35;
                                } 
                                break;
					}
				}
			 }


             if (POSESS(13))
             {
                           if(goalable2(p,13))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 13;                  
                           }
                           else
                           {
                                   if(p[13].strength!=0)
                                   {
                                                       if(passable(p,13,16))
                                                       {                                                    
                                                        p[0].x=p[16].x;
                                                        p[0].y=p[16].y;                  
                                                        return 13;                  
                                                       }
                                                       else
                                                       {
                                                        p[0].x=p[12].x;
                                                        p[0].y=p[12].y;                  
                                                        return 13;                  
                                                       }
                                   }
                           } 
             }
             else if (POSESS(12))
             {
                           if(goalable2(p,12))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 12;                  
                           }
                           else
                           {
                               if(p[12].y<25)
                               {
                                            if(p[12].strength!=0)
                                            {
                                                         if(passable(p,12,16))
                                                         {
                                                         p[0].x=p[16].x;
                                                         p[0].y=p[16].y;                  
                                                         return 12;                  
                                                         }
                                                         else
                                                         {
                                                         p[0].x=p[13].x;
                                                         p[0].y=p[13].y;                  
                                                         return 12;                  
                                                         }
                                            }
                               }
                               else
                               {
                                            if(p[12].strength!=0)
                                            {
                                                         if(passable(p,12,18))
                                                         {
                                                         p[0].x=p[18].x;
                                                         p[0].y=p[18].y;                  
                                                         return 12;                  
                                                         }
                                                         else
                                                         {
                                                         p[0].x=p[15].x;
                                                         p[0].y=p[15].y;                  
                                                         return 12;                  
                                                         }
                                            }
                               }
                           } 

			 }
			 else if (POSESS(15))
			 {
                           if(goalable2(p,15))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 15;                  
                           }
                           else
                           {
                                            if(p[15].strength!=0)
                                            {
                                                        if(passable(p,15,18))
                                                        {
                                                        p[0].x=p[18].x;
                                                        p[0].y=p[18].y;                  
                                                        return 15;        
                                                        }
                                                        else
                                                        {
                                                        p[0].x=p[12].x;
                                                        p[0].y=p[12].y;                  
                                                        return 15;                  
                                                        }
                                             }          
                           } 

			 }
             else if (POSESS(16))
             {
                           if(goalable2(p,16))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 16;                  
                           }
                           else
                           {
                                            if(p[16].strength!=0)
                                            {                               
                                                         
                                                      if(passable(p,16,19))
                                                      {
                                                                p[0].x=p[19].x;
                                                                p[0].y=p[19].y;                  
                                                                return 16;        
                                                      }
                                                      else
                                                      {
                                                          p[0].x=p[18].x;
                                                          p[0].y=p[18].y;                  
                                                          return 16;                  
                                                      }
                                             }          
                           } 

			 }
			 else if (POSESS(18))
			 {
                           if(goalable2(p,18))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 18;                  
                           }
                           else
                           {
                                            if(p[18].strength!=0)
                                            {                            
                                                      if(passable(p,18,21))
                                                      {
                                                                p[0].x=p[21].x;
                                                                p[0].y=p[21].y;                  
                                                                return 18;        
                                                      }
                                                      else
                                                      {
                                                        p[0].x=p[16].x;
                                                        p[0].y=p[16].y;                  
                                                        return 18;                  
                                                      }
                                            }          
                           } 

			 }
			 else if (POSESS(19))
			 {
                           if(goalable2(p,19))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 19;                  
                           }
                           else
                           {
                                            if(p[19].strength!=0)
                                            {
                                                      if(passable(p,19,22))
                                                      {
                                                                p[0].x=p[22].x;
                                                                p[0].y=p[22].y;                  
                                                                return 19;        
                                                      }
                                                      else
                                                      {
                                                        p[0].x=p[21].x;
                                                        p[0].y=p[21].y;                  
                                                        return 19;                  
                                                      }
                                            }          
                           } 

             }	
			 else if (POSESS(21))
			 {
                           if(goalable2(p,21))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 21;                  
                           }
                           else
                           {
                                            if(p[21].strength!=0)                                   
                                            {
                                                      if(passable(p,21,20))
                                                      {
                                                               p[0].x=p[20].x;
                                                               p[0].y=p[20].y;                  
                                                               return 21;
                                                      }
                                                      else
                                                      {
                                                        p[0].x=p[19].x;
                                                        p[0].y=p[19].y;                  
                                                        return 21;                  
                                                       }
                                            }
                           } 

			 }
			 else if (POSESS(22))
			 {
                           if(goalable2(p,22))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 22;                  
                           }
                           else
                           {
                                            if(p[22].strength!=0)
                                            {                            
                                                      if(passable(p,22,14))
                                                      {
                                                             p[0].x=p[14].x;
                                                             p[0].y=p[14].y;                  
                                                             return 22;                  
                                                      }
                                                      else
                                                      {
                                                        p[0].x=p[20].x;
                                                        p[0].y=p[20].y;                  
                                                        return 22;                  
                                                      }
                                            }
                           } 

		     }
	         else if (POSESS(20))
	         {
                           if(goalable2(p,20))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 20;                  
                           }
                           else
                           {
                                            if(p[20].strength!=0)
                                            {                            
                                                      if(passable(p,20,17))
                                                      {
                                                            p[0].x=p[17].x;
                                                            p[0].y=p[17].y;                  
                                                            return 20;
                                                      }
                                                      else
                                                      {
                                                        p[0].x=p[22].x;
                                                        p[0].y=p[22].y;           
                                                        return 20;                  
                                                      }
                                            }                  
                           } 

	         }
			 else if (POSESS(14))
			 {
                           if(goalable2(p,14))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 14;                  
                           }
			 }
			 else if (POSESS(17))
             {
                           if(goalable2(p,17))
                           {
                            p[0].x=final_x;
                            p[0].y=final_y;                  
                            return 17;                  
                           }
             }
    
    }
                      
   return -1;
}

};//end of class
