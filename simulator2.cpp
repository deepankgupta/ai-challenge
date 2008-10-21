#include<stdio.h>
#include<math.h>

#include<stdlib.h>
#include<string.h>
#include"common.h"








#include"team0078.cpp"
#include"team0093.cpp"
#include"team0072.cpp"
#include"team0055.cpp"
#include"team0038.cpp"
#include"team0036.cpp"
#include"team0048.cpp"
#include"team0031.cpp"













using namespace std;
class stimulator
{
 private:
  int chance,l1,u1,l2,u2,pts1,pts2,goal1,goal2;   //l1,u1 denotes the lower and upper limits of the player's of the team having 
                                         //the turn to hit the ball while l2,u2 denotes for the opponent's team
  char falocal[101][51];              //an array defined only for stimulator class of the type of the field
  struct player local[23],printable[23];//printable keeps a track of the players' and ball statistics before the move was made 
                                        //local keeps a track of the players' and ball statistics after the move is made

   int preq(int finalx,int finaly, int initialx ,int initialy )       //fn to find the str req by player to move
	{
     float req;                                                     //similar to preqp in class team
	 req=floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
	 return (int)req;
    }

   int preqb(int finalx,int finaly, int initialx ,int initialy )       // fn to find the str req by hitter to move the ball from
    {
      float req;                                                                           //one pos to another
      req=2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)))); //similar to preqpb in class team
      return (int)req;
    }     

public:  //public functions of stimulator class
  
  void initialize()        //function called by main to initialize the private variables of stimulator class to 0
   {
       goal1=0;goal2=0;pts1=0;pts2=0;
   }
  void controller()
   {


	 int i,j,k,move,phitter,ball,players,sum_pstr_1=0,sum_pstr_2=0;
	 char check;
	 team0093 p1;     //defining objects of the class teamxxxx and team0002 where xxxx is your registration no. and team0002 is the
	 team0048 p2;     //test player given by us
     
    


	 for(i=0;i<=22;i++)
	 {
       local[i]=global[i];
       printable[i]=global[i];
      }     //copying player struct array as initialised in main to the local and printable arrays

	 for(i=0;i<=100;i++)
	 for(j=0;j<=50;j++)
	 falocal[i][j]=fieldarray[i][j]; //copying field array to local field array as initialised in main
	 
	  p1.init(1,global,fieldarray);    //calling the init functions of both the teams to send them their team no. and passing them
     p2.init(2,global,fieldarray);    //the initial field distribution and the basic field array
       
     chance=0;    //value of chance is randomly selected 
	  
      
    for(move=1;move<=500;move++)  /*loop to take care of the no of turns*/
     {
        printf("\nmove=%d\n",move);
	   
     //set the parameters and calling player's function according to the value of chance (toss)
        if(chance==0)
        {
          phitter=p1.player(global);  chance=1; l1=1; u1=11; l2=12; u2=22;
        }
		else 
        {
          phitter=p2.player(global); chance=0; l1=12; u1=22; l2=1; u2=11;
        }
		
		//calling functions in stimulator class
		playerpos(phitter); 
		ballpos(phitter);
		
        


     for(i=0;i<=22;i++)
	    {
          global[i]=local[i];
         }//copying player struct array

   for(i=0;i<=100;i++)
	 for(j=0;j<=50;j++)
	    fieldarray[i][j]=falocal[i][j]; //copying field array to local field array
	
    //statements to print the output array after every move
    
	 for(i=0;i<=100;i++)
      {
        printf("\n");
       for(j=0;j<=50;j++)
       {
          ball=0;         //to find whether any player or ball is present at falocal[i][j]
	      players=0;
        
        if((global[0].x==i)&&(global[0].y==j))   //to check whether the ball's coordinates matches with the value of i and j
          ball++;
        
        //to check whether any player's coordinates matches with the value of i and j
        for(k=1;k<=22;k++)
         {
           if((global[k].x==i)&&(global[k].y==j))players++;
         }
        
        if((fieldarray[i][j]=='B')||(fieldarray[i][j]=='g')||(fieldarray[i][j]=='G'))
          printf("%c",fieldarray[i][j]);
          
        else if((ball==0)&&(players==0))     //if no player or ball is present at global[i][j]
          {
            if((fieldarray[i][j]=='d')||(fieldarray[i][j]=='D'))
               printf("%c",fieldarray[i][j]);
           
            else printf("f");      //if the global[i][j] is not inside dee region and is a simple region
          }
           
          
        else       //if ball or player is present at global[i][j]
         {
           if(ball==1)
             printf("0");
            
           else if(players<=9)
             printf("%d",players);
            
           else
             printf("e");
          }//end of else
          
        }//end of 2nd for loop
      }//end of 1st for loop
    
    //to tell the significance of symbols used in array representation 
     printf("\n\ng signifies the 1st player's goal\nG signifies 2nd player's goal\nd signifies 1st player's dee\nD signifies 2nd player's goal\n");
     printf("\n1 signifies presence of 1 player at the spot ,2 signifies presence of 2 players at that spot and so on....\n");
     printf("e signifies that more than 9 players are present at that spot\n"); 
     printf("0 signifies that the ball is present at that spot.The no. of players is not   shown in this case.\n\nB signifies boundary\n\nf signifies a normal field region\n\n");    
	 
    //to print the positions of the ball and players
	if(chance==1)
      printf("\n\nteam1 turn , hitter of ball=%d",phitter);
	else         
       printf("\n\nteam2 turn , hitter of ball=%d",phitter);
    
     printf("\n\n");
     printf("ball-\n");     //printing ball's statistics 
	 printf("init posx=%d init posy=%d finalposx=%d finalposy=%d\n\n",printable[0].x,printable[0].y,local[0].x,local[0].y);
	 
     printf("team1-\n");   //printing statistics of team 1 players
	 printf("player initx inity finalx finaly initstr finalstr\n");
	 for(i=1;i<=11;i++)
	   printf("%6d %5d %5d %6d %6d %7d %8d\n",i,printable[i].x,printable[i].y,local[i].x,local[i].y,printable[i].strength,local[i].strength);
	   
     printf("\nteam2-\n");   //printing statistics of team 2 players
	 printf("player initx inity finalx finaly initstr finalstr\n");
	 for(i=12;i<=22;i++)
	   printf("%6d %5d %5d %6d %6d %7d %8d\n",i,printable[i].x,printable[i].y,local[i].x,local[i].y,printable[i].strength,local[i].strength);
	 
     printf("SCORE--\n");
     printf("team1 goal=%d\nteam1 pts=%d\n team2 goal=%d\n team2 pts=%d\n",goal1,pts1,goal2,pts2);
      
      //to directly view the final result of the game remove this  portion
     printf("press enter to continue\npress N or n to exit the program ");  
       fflush(stdin);
       
       /*if(check=='N'||check=='n') 
          exit(1);*/                  
	 
	  for(i=0;i<=22;i++)
	   printable[i]=local[i];//to update the printable array
	   
      
   }/*to end the move loop*/

      printf("\nGAME FINISHED\nFINAL SCORES--\n");
      printf("team1 goal=%d\nteam1 pts=%d\n team2 goal=%d\n team2 pts=%d\n",goal1,pts1,goal2,pts2);//to print the no of goals
  
  //to print the winner of the game 
     if(pts1>pts2)
       printf("\n\nTEAM 1 WINS THE MATCH\n\n");
     else if(pts1<pts2)
       printf("\n\nTEAM 2 WINS THE MATCH\n\n");
     else
      {
        printf("\n\nBoth team have equal points. Game will be decided on the basis of the sum of the strengths of each team's players'\n\n");
        sum_pstr_1=0;sum_pstr_2=0;
        for(i=1;i<=11;i++)
         {
           sum_pstr_1+=local[i].strength;
           sum_pstr_2+=local[i+11].strength;
         }//loop to sum left over strengths of each team players
        
        printf("\nleft over strength of team1=%d\nleft over strength of team2=%d\n",sum_pstr_1,sum_pstr_2);
        
        if(sum_pstr_1>sum_pstr_2)
          printf("\n\nleft over strength of 1st team players' is more than 2nd team and hence 1st TEAM IS THE WINNER\n\n");
        else if(sum_pstr_1<sum_pstr_2)
          printf("\n\nleft over strength of 1st team players' is less than 2nd team and hence 2nd TEAM IS THE WINNER\n\n");
        else 
          printf("\n\nleft over strength of both teams is equal and hence THE GAME IS A DRAW\n\n"); 
       
       }//end of else
		
  }//end of fn controller

  //this function checks whether the changes made by the teams in the position of their players' in the array global are 
  //valid or not and if they are then changes are updated in the local array and strength is decreased accordingly of the 
  //players 
	void playerpos(int phitter)
	{

      int k,xdiff,ydiff,powerreq;
		
       for(k=l1;k<=u1;k++) //to compare each player's global pos with the one inside local
		{
          xdiff=(global[k].x)-(local[k].x);     //xdiff and ydiff finds the difference between the player's initial and final 
          ydiff=(global[k].y)-(local[k].y);     //coordinates
		 
         if(((xdiff==0)&&(ydiff==0))||(global[k].strength==0))
		  {
            if(local[k].strength<=30)
              local[k].strength=local[k].strength+20;
			else if ((local[k].strength>30)&&(local[k].strength<50))
              local[k].strength=50;
           }/*end of if loop in case player has not moved*/

		 else /*else when the player has moved*/
		 {
           powerreq=preq(global[k].x,global[k].y,local[k].x,local[k].y);
		  
	   //if case to check whether the coordinates of player changed by the participant are legal or not
         if((global[k].x<=100)&&(global[k].x>=0)&&(global[k].y<=50)&&(global[k].y>=0)&&(falocal[global[k].x][global[k].y]!='g')&&(falocal[global[k].x][global[k].y]!='G')&&(falocal[global[k].x][global[k].y]!='B'))
           {
               from_else_of_boundary:/*label for goto*/
			    if(local[k].strength>=powerreq)
                 {
                    local[k].x=global[k].x;
                    local[k].y=global[k].y;
			        local[k].strength=local[k].strength-powerreq;
			     } //if player strength is more than or sufficient than req to move

			    else //if power req is not sufficient
	             {
                    while(powerreq>local[k].strength)
			         { 
                       if(local[k].x!=global[k].x)
                       { 
                          (xdiff>0)?(global[k].x)--:(global[k].x)++;
                       }
				      if(local[k].y!=global[k].y)
                       {
                          (ydiff>0)?(global[k].y)--:(global[k].y)++;
                       }
				       
                       powerreq=preq(global[k].x,global[k].y,local[k].x,local[k].y);
			         
                     }//end of while loop

			         local[k].x=global[k].x;
		             local[k].y=global[k].y;
			         local[k].strength=local[k].strength-powerreq;

                  }  //end of else when power req is not sufficient

		     }  //to end the if case when the final coordinates of player are not in boundary or goal or out of field array

		else //when the final coordinates of player are  illegal
		{
			while((global[k].x>100)||(global[k].x<0)||(global[k].y>50)||(global[k].y<0)||(falocal[global[k].x][global[k].y]=='g')||(falocal[global[k].x][global[k].y]=='G')||(falocal[global[k].x][global[k].y]=='B'))   //to end else when finla cooordinates r illegal
			{
			  if(local[k].x!=global[k].x)
                (xdiff>0)?(global[k].x)--:(global[k].x)++;
			  if(local[k].y!=global[k].y)
                (ydiff>0)?(global[k].y)--:(global[k].y)++;
			}  //end of while

		    powerreq=preq(global[k].x,global[k].y,local[k].x,local[k].y);
		  
            goto from_else_of_boundary;  //to check whether player has the power to reach the valid pos                                                                                                                                                                                                            }
	  
         }     //to end the else when the final coordinates of player are illegal

       } //to end the else loop of whether player has moved
      
      } //to end checking all players of the team
		  
    } //to end playerpos fn


//this function changes the position of the ball according to the changes made by the user in the position of the ball in the 
//global array and checks whether the ball is interrupted in between or reaches goal ,dee or boundary and accordingly changes the
//points of both the teams and changes the strength of the hitter of the ball 
void ballpos(int phitter)
 {
    int patspot,patspotstr,xdiffb;int ydiffb,validposx,validposy,found,powerreqb,i,j,a,p,ball,players,k;
    char status,dee,goal; 
 
    //if the hitter as returned by the player function has 0 strength or is an illegal no.
    if((phitter<1)||(phitter>22)||(local[phitter].strength==0))
      return;
      
    if((chance==1)&&(phitter>11)||(chance==0)&&(phitter<12))
      return;
  
    if(((local[phitter].x!=local[0].x)||(local[phitter].y!=local[0].y))&&((printable[phitter].x!=local[0].x)||(printable[phitter].y!=local[0].y)))
      return;
  //to return in case phitter final coordinates and initial coordinates of ball or phitter's initial coordinates and 
  //final coordinates of the ball don't meet

    patspot=-1;patspotstr=0;

  for(a=l2;a<=u2;a++)
   {
     if((local[a].x==local[0].x)&&(local[a].y==local[0].y))
	   {
         if(local[a].strength>patspotstr)
	      {
            patspot=a; 
		    patspotstr=local[a].strength;
	      }
	   }
   }/*for loop to check whether any of opponent's player is present at the ball's pos and to calculate max strength in case the no */
	 /*is more than 1*/
    
		
  if((patspot==-1)||(patspotstr<=local[phitter].strength))//to check whether phitter's strength is more than maximum
                                                           //opponent's strength or he the only one with the ball
   {
     //strength of hitter of ball decreases by an amt equal to opponent's strength while taking the possession of the ball
     //and the opposition's player's strength having the possession of the ball becomes 0
	  local[phitter].strength-=patspotstr ;
	  local[patspot].strength=0;
		
      status='f';  //tells the region in which the ball is present after every step 
                  //'f' when the ball is in the normal region ,'d' or 'D' when the ball is in the dee of either of the teams, 'g' or 'G'
                  //when the ball is in the goal of any of the teams , 'B' when ball reaches the boundary, ''i if the ball is 
                  //interrupted by any of the player and 'r' if the ball reaches the desired position as changed by the participant
		 
		xdiffb=global[0].x-local[0].x;   //calculates the difference between changed coordinates and initial coordinates of the 
        ydiffb=global[0].y-local[0].y;   //ball
      
		validposx=local[0].x;  //validposx and validposy keeps a track of the step by step movement of the ball from its 
        validposy=local[0].y;  //initial position to the desired position
      
      while((status=='f')||(status=='D')||(status=='d'))
      {
		  if(validposx!=global[0].x)
            (xdiffb>0)?(validposx)++:(validposx)--;
          if(validposy!=global[0].y)
            (ydiffb>0)?(validposy)++:(validposy)--;
        
         for(i=1;i<=22;i++)
          {
            if((validposx==local[i].x)&&(validposy==local[i].y))
              {
                status='i';
                break;
              }
          }      //loop to check whether any of the player intersect the ball
           if(status=='i')
             break;
         if(falocal[validposx][validposy]!=0)
           {
             status=falocal[validposx][validposy];
           }     //to give status=d or D or g or G according to the position of the ball in field array
        
         if((status=='B')||(status=='G')||(status=='g')||(status=='i'))
           break;
       
          if((validposx==global[0].x)&&(validposy==global[0].y))            //when ball reaches its desired position
            {
              status='r';
               break;
            }
       
       }//end of while loop which operates until ball is interrupted or reaches its desired pos or enters goal or boundary
          
      
	     chance==1?(dee='D'):(dee='d');     //sets the varibles dee and goal according to the player's turn
         chance==1?(goal='G'):(goal='g');
     
    /*switch case is applied to check whether ball is interupted or reached its destination or got into goal or crossed the boundary*/
     
    switch(status)
     {
        //when ball reaches the desired position
       case 'r':
            
            powerreqb=preqb(global[0].x,global[0].y,local[0].x,local[0].y);
            
            validposx=global[0].x;
            validposy=global[0].y;            
            
            //while loop to find the valid pos when hitter has enough power to make the ball reach there
            while(powerreqb>local[phitter].strength)
                                                    
             {
				  if(validposx!=local[0].x)
                     (xdiffb>0)?(validposx)--:(validposx)++;
                  if(validposy!=local[0].y)
                     (ydiffb>0)?(validposy)--:(validposy)++;
                  
                  powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
             }//end of while loop 
            
           if((falocal[validposx][validposy]==dee)&&(falocal[local[0].x][local[0].y]!=dee))
             {
               (chance==1)?(pts1++):(pts2++);
             }               //increases pts if ball lands in the dee and was not in the dee earlier
            
            local[0].x=validposx;
            local[0].y=validposy;   
            (local[phitter].strength)-=powerreqb;           //update the array accordingly
           
            break;                                                  
         
       //when the ball is interrupted by any of the player    
        case 'i':
            powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            
            //while loop to find the valid pos when hitter has enough power to make the ball reach there
              while(powerreqb>local[phitter].strength)
               {
				  if(validposx!=local[0].x)
                    (xdiffb>0)?(validposx)--:(validposx)++;
                  if(validposy!=local[0].y)
                     (ydiffb>0)?(validposy)--:(validposy)++;
              
                  powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            
                }//end of while loop 
            //inc pts if ball lands in the dee and was not in the dee earlier)
			  if((falocal[validposx][validposy]==dee)&&(falocal[local[0].x][local[0].y]!=dee))
                 chance==1?pts1++:pts2++;
            
               
           
     //strength is dec on the basis of coordinates given by user irrespective of where the ball stops  
           powerreqb=preqb(global[0].x,global[0].y,local[0].x,local[0].y);
           
            local[0].x=validposx;
                 local[0].y=validposy;
           
           if(powerreqb>=local[phitter].strength)
             local[phitter].strength=0;
                                                                           
            else (local[phitter].strength)-=powerreqb;
           
            break;
           
        case 'G':
            
            powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            
        //while loop to find the valid pos when hitter has enough power to make the ball reach there
            while(powerreqb>local[phitter].strength)
             {
				  if(validposx!=local[0].x)
                    (xdiffb>0)?(validposx)--:(validposx)++;
                  if(validposy!=local[0].y)
                     (ydiffb>0)?(validposy)--:(validposy)++;
                  
                  powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
              }//end of while loop
            
            //if the ball is not in the goal now
             if(falocal[validposx][validposy]!='G')
               {
                  if(falocal[validposx][validposy]=='D')  //if the ball is still inside the opponent's dee
                    {  
                      //if the ball was initially not in the opponent's dee ,so points of the team are increased
                       if(chance==1&&falocal[local[0].x][local[0].y]!='D')
                         pts1++;
                    }
                  local[0].x=validposx;
                  local[0].y=validposy;  
              
               }//end of if case when the ball is not in the goal now
          
           //if the ball is still in the goal   
        else 
          {
               //to print the status of the field when the ball reaches the goal 
               //printed in the same way as printed earlier
               
                printf("\n\nHURRAY 1ST TEAM MADE A GOAL\nfigure shows the position of ball at the time of goal\n to view detailed result of the move and final position of ball press any key\n\n");
	        for(i=0;i<=100;i++)
              {
                 printf("\n");
                 for(j=0;j<=50;j++)
                   {
                     ball=0;
	                 players=0;
                     
                     if((validposx==i)&&(validposy==j))
                       ball++;
                     
                     for(k=1;k<=22;k++)
                      {
                        if((global[k].x==i)&&(global[k].y==j))players++;
                      }
                     
                      if(ball==1)
                         printf("0");
        
                       else if((fieldarray[i][j]=='B')||(fieldarray[i][j]=='g')||(fieldarray[i][j]=='G'))
                         printf("%c",fieldarray[i][j]);
          
                       else if((ball==0)&&(players==0))
                         {
                           if((fieldarray[i][j]=='d')||(fieldarray[i][j]=='D'))
                              printf("%c",fieldarray[i][j]);
           
                           else printf("f");
                         }
           
          
                       else
                        {
          
                          if(players<=9)
                            printf("%d",players);
            
                          else
                            printf("e");
                        }//end of else
          
                     }//end of 2nd for loop
                
                }//end of 1st for loop
         
               
                 goal1++;
                 pts1+=10;
               
                 found=0;   /*found is to break the loop when a correct place is found to place the ball once goal happens*/
                
				  for(i=25;(found==0)&&(i<51);i++)
                    {
                      for(j=1;j<=11;j++)
						{
                          if((local[j].x==50)&&(local[j].y==i))
                             break;
                        }   //end of for
                  
                      if(j==12)
                        {
                          local[0].x=50;
                          local[0].y=i;
                          found++;
                        }         //end of if
                    }        //end of for
                
              }       //end of else when the ball was still in the goal 
          
            
           
               //strength is dec on the basis of coordinates given by user irrespective of where the ball stops
              powerreqb=preqb(global[0].x,global[0].y,local[0].x,local[0].y);
               
              if(powerreqb>=local[phitter].strength)
                local[phitter].strength=0;
                                                                        
              else 
                (local[phitter].strength)-=powerreqb;
           
            break;
           
          
          case 'g':
                  
               //designed in a way almost similar to case 'G'
                  powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            
            //while loop to find the valid pos when hitter has enough power to make the ball reach there
               while(powerreqb>local[phitter].strength)
                {
				   if(validposx!=local[0].x)
                     (xdiffb>0)?(validposx)--:(validposx)++;
                   if(validposy!=local[0].y)
                      (ydiffb>0)?(validposy)--:(validposy)++;
              
                    powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
                
                }//end of while loop
            
               if(falocal[validposx][validposy]!='g')
                {
                  if(falocal[validposx][validposy]=='d')
                    {
                      if(chance==0&&falocal[local[0].x][local[0].y]!='d')
                        pts2++;
                     }
                    local[0].x=validposx;
                     local[0].y=validposy;  
                  }//end of if case when the ball is not in the goal now 
            
      //if the ball is still in the goal 
       else 
        {
           //to print the status of the field when the ball reaches the goal 
               //printed in the same way as printed earlier
            printf("\n\nHURRAY 2nd TEAM MADE A GOAL\nfigure shows the position of ball at the time of goal\n to view detailed result of the move and final position of ball press any key\n\n");
	        for(i=0;i<=100;i++)
              {
                printf("\n");
                 for(j=0;j<=50;j++)
                  {
                    ball=0;
                    players=0;
                    
                    if((validposx==i)&&(validposy==j))
                       ball++;
            
                     for(k=1;k<=22;k++)
                        {
                          if((global[k].x==i)&&(global[k].y==j))
                            players++;
                        }
                      
                      if(ball==1)
                           printf("0");
        
                      else if((fieldarray[i][j]=='B')||(fieldarray[i][j]=='g')||(fieldarray[i][j]=='G'))
                           printf("%c",fieldarray[i][j]);
          
                      else if((ball==0)&&(players==0))
                        {
                           if((fieldarray[i][j]=='d')||(fieldarray[i][j]=='D'))
                              printf("%c",fieldarray[i][j]);
           
                           else
                               printf("f");
                         }      //end of if else
           
          
                      else
                       {
          
            
                         if(players<=9)
                            printf("%d",players);
            
                         else
                            printf("e");
                       }//end of else
          
                   }//end of 2nd for loop
      
               }//end of 1st for loop 
               
                 goal2++;
                 pts2+=10;
               
                 found=0;/*found is to break the loop when a correct place is found to place the ball once goal happens*/
                
                for(i=25;found==0&&i<51;i++)
                {
                  for(j=12;j<=22;j++)
                  {
                    if((local[j].x==50)&&(local[j].y==i))
                      break;
                  }//end of for
                  
                   if(j==23)
                    {
                       local[0].x=50;
                       local[0].y=i;
                       found++;
                     }//end of if
                  
                 }//end of for
                
          }//end of else
              
               //strength is dec on the basis of coordinates given by user irrespective of where the ball stops
              powerreqb=preqb(global[0].x,global[0].y,local[0].x,local[0].y);
                
                if(powerreqb>=local[phitter].strength)
                   local[phitter].strength=0;
                                                                        
                 else 
                   (local[phitter].strength)-=powerreqb;
           
               break; 
           
         case 'B':
               powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
              
              //to decrement pts in case a team hits the ball in boundary 
               if(powerreqb<=local[phitter].strength)
					{
                       chance==1?pts1--:pts2--;
                    }
               
              //do while loop to find the valid pos when hitter has enough power to make the ball reach there 
              do 
                {
				    if(validposx!=local[0].x)
                      (xdiffb>0)?(validposx)--:(validposx)++;
                    if(validposy!=local[0].y)
                      (ydiffb>0)?(validposy)--:(validposy)++;
                    
                    powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
                 
                 }while(powerreqb>local[phitter].strength);
																	 
                //strength is dec on the basis of coordinates given by user irrespective of where the ball stops
                                                    
                powerreqb=preqb(global[0].x,global[0].y,local[0].x,local[0].y);
                
                if(powerreqb>=local[phitter].strength)
                   local[phitter].strength=0;
                      
                 else 
                   (local[phitter].strength)-=powerreqb;
           
           
                 local[0].x=validposx;     //to update the array accordingly
                 local[0].y=validposy;
           
               break;                                       
             
     };//end of switch case
             
   } //to end the if to check whether phitter's strength is more than opponent's strength
   
   
  } //end of ballpos fn
        
        
        
 };     //end of stimulator class





int main()
 {
	 int i,j;
     stimulator c1;
     
     c1.initialize();  //initializing the variables goal1,goal2,pts1,pts2 to 0
	
	 //to set boundary
	 
	  for(i=0;i<=100;i++)
	    {
		    fieldarray[i][0]='B';
	        fieldarray[i][50]='B';
		    if(i<=50)
		      {
			    fieldarray[0][i]='B';
		        fieldarray[100][i]='B';
		       }//end of if
	     }//end of for loop

   //to set the dee
	 for(i=5;i<=45;i++)
	  {
		for(j=0;j<=40;j++)
		  fieldarray[j][i]='d';

		 for(j=60;j<=100;j++)
		   fieldarray[j][i]='D';

	  }                          //end of for loop

    //to set the goal
	  for(i=10;i<=40;i++)
	   {
	     for(j=0;j<=14;j++)
		    fieldarray[j][i]='g';

	     for(j=86;j<=100;j++)
		    fieldarray[j][i]='G';
	   }						//end of for loop
	 
	
     
     //to set the initial strength of the players
	   for(i=1;i<=22;i++)  
		  global[i].strength=50;
      
      //set strength of ball to 0
	    global[0].strength=0;
      
      // to set the team name
	 for(i=1;i<=11;i++)
	   global[i].team=1;    //1 for 1st team

	 for(i=12;i<=22;i++)   
	   global[i].team=2;     //2 for 2nd team

	   global[0].team=0;     //0 for ball



   //to set player pos
   
	 global[1].x=15;global[1].y=25;
	 global[2].x=25;global[2].y=10;
	 global[3].x=25;global[3].y=25;
	 global[4].x=25;global[4].y=40;
	 global[5].x=30;global[5].y=10;
	 global[6].x=30;global[6].y=25;
	 global[7].x=30;global[7].y=40;
	 global[8].x=40;global[8].y=10;
	 global[9].x=40;global[9].y=25;
	 global[10].x=40;global[10].y=40;
	 global[11].x=49;global[11].y=25;
	 global[12].x=85;global[12].y=25;
	 global[13].x=75;global[13].y=10;
	 global[14].x=75;global[14].y=25;
	 global[15].x=75;global[15].y=40;
	 global[16].x=70;global[16].y=10;
	 global[17].x=70;global[17].y=25;
	 global[18].x=70;global[18].y=40;
	 global[19].x=60;global[19].y=10;
	 global[20].x=60;global[20].y=25;
	 global[21].x=60;global[21].y=40;
	 global[22].x=51;global[22].y=25;

	 global[0].x=50;global[0].y=25;           //to set ball's pos


    c1.controller();        //calling the function



//    getch();                 //to hold the screen

}              //end of main function
