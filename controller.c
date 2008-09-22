int preq(int,int,int,int);
int preqb(int,int,int,int);

struct player
{int x,y,strength;
 char team[6];
 };

int main()
{controller();

int controller()
{
    char falocal[101][51];
    struct player local[23];
    int i,j,k,move,chance,l1,u1,l2,u2,phitter,pts1=0,pts2=0,goal1=0,goal2=0;
    
    void playerpos();  \\fn declarations
    void ballpos();
    
    for(i=0;i<=22;i++)
    {local[i]=global[i];}\\copying player struct array
    
    for(i=0;i<=100;i++)
    for(j=0;j<=50;j++)
    falocal[i][j]=fieldarray[i][j]; \\copying field array to local field array
    
     chance=rand(1);
     
     for(move=1;(move<2000)&&(pts1<100)&&(pts2<100);move++)  \*loop to take care of the no of turns*\
     {if(chance==0){phitter=player1(0);chance=1;l1=1;u1=11;l2=12;u2=22;}
      else {phitter=player2(1);chance=0;l1=12;u1=22;l2=1;u2=11;} 
      
      playerpos();
      ballpos(); 
      
      }\*to end the move loop*\
      
      
       for(i=0;i<=22;i++)
    {global[i]=local[i];}\\copying player struct array
    
    for(i=0;i<=100;i++)
    for(j=0;j<=50;j++)
    fieldarray[i][j]=falocal[i][j]; \\copying field array to local field array
     
      }\\end of fn controller
   
   void playerpos()
   {
      int k,xdiff,ydiff,powerreq;
      for(k=l1;k<=u1;k++) \\to compare each player's global pos with the one inside local 
      {xdiff=(global[k].x)-(local[k].x); ydiff=(global[k].y)-(local[k].y);
       if((xdiff==0)&&(ydiff==0))
        {if(local[k].strength<=40)local[k].strength+=10;
         else if ((local[k].strength>40)&&(local[k].strength<50))local[k].strength=50;}\*end of if loop in case player has not moved*\
         
       else \*if the player has moved*\
       {powerreq=preq(global[k].x,global[k].y,local[k].x,local[k].y);
        if((global[k].x<=100)&&(global[k].x>=0)&&(global[k].y<=50)&&(global[k].y>=0)&&(falocal[global[k].x][global[k].y]!='g')&&(falocal[global[k].x][global[k].y]!='G')&&(falocal[global[k].x][global[k].y]!='B'))
        {fromelseofboundary:\*label for goto*\
         if(local[k].strength>=powerreq)
         {local[k].x=global[k].x;
          local[k].y=global[k].y;
          local[k].strength=local[k].strength-powerreq;
         }\\if player strength is more than or sufficient than req to move  
         
         else \\if power req is not sufficient
         {while(powerreq>local[k].strength)
          { if(local[k].x!=global[k].x)(xdiff>0)?(global[k].x)--:(global[k].x)++;
            if(local[k].y!=global[k].y)(ydiff>0)?(global[k].y)--:(global[k].y)++;
            powerreq=preq(global[k].x,global[k].y,local[k].x,local[k].y);
          }\\end of while loop
          
          local[k].x=global[k].x;
          local[k].y=global[k].y;
          local[k].strength=local[k].strength-powerreq;
          
          }\\end of else when power req is not sufficient
                
       }\\to end the if case when the final coordinates of player are not in boundary or goal or out of field array
           
      else \\when the final coordinates of player are  illegal
      {
         while((global[k].x>100)&&(global[k].x<0)&&(global[k].y>50)&&(global[k].y<0)&&(falocal[global[k].x][global[k].y]=='g')&&(falocal[global[k].x][global[k].y]=='G')&&(falocal[global[k].x][global[k].y]=='B'))   }\\to end else when finla cooordinates r illegal
         {  
           if(local[k].x!=global[k].x)(xdiff>0)?(global[k].x)--:(global[k].x)++;
            if(local[k].y!=global[k].y)(ydiff>0)?(global[k].y)--:(global[k].y)++;
         }\\end of while
        
        powerreq=preq(global[k].x,global[k].y,local[k].x,local[k].y);
        goto fromelseofboundary;\\to check whether player has the power to reach the valid pos                                                                                                                                                                                                            }
      
      
      }\\to end the else loop of whether player has moved  
         }\\to end checking all players of the team
        }\\to end playerpos fn
        
 
 void ballpos(int phitter)
 {int patspot,patspotstr,xdiffb,ydiffb,validposx,validposy,found,powerreqb,i,j;
 char status,dee,goal;
  phitter=(chance==1)?phitter:(phitter+11);
  
  if((local[phitter].strength==0)||(phitter<1)||(phitter>22))
  return;
  
  if((local[phitter].x!=local[0].x)||(local[phitter].!==local[0].y))return; 
  \\to return in case phitter coordinates and initial coordinates of ball don't meet
  
  patspot=-1;patspotstr=0;
  
  for(a=(chance?l2:l1);a<=(chance?u2:u1);a++)
  {if((local[a].x==local[phitter].x)&&(local[a].y==local[phitter].y))
   {if(local[a].strength>patspostr)
     {patspot=a;
       patspotstr=local[a].strength;
     }
   }
  }\*for loop to check whether ny of opponent's player is present at the ball's pos and to calculate max strength in case the no *\
    \*is more than 1*\
    
  
  if((patspot==-1)&&(patspotstr<=local[phitter].strength))\\to check whether phitter's strength is more than opponent's strength 
                                                           \\or he the only one with the ball
  {
     local[phitter]-=patspotstr;   
      
      status='f';
      
      xdiffb=global[0].x-global[0].y;
      ydiffb=global[0].x-global[0].y;
      
      validposx=global[0].x;
      validposy=global[0].y;
      
      while((status=='f')&&)(status=='D')&&)(status=='d'))
      {
        if(validposx!=global[0].x)(xdiff>0)?(validposx)++:(validposx)--;
        if(validposy!=global[0].y)(ydiff>0)?(validposy)++:(validposy)--;
        
        for(i=1;i<=22;i++)
        {
         if((validposx==local[i].x)&&(validposy==local[i].y))
          {status='i';
            break;
          }
        }\\loop to check whether ny of the player intersect the ball
        
       if(falocal[validposx][validposy]!=0)
       {status=falocal[validposx][validposy];}\\to give status=d or D or g or G
       
       if((status=='B')&&(status=='G')&&(status=='g'))break;
       
       if((validposx==global[0].x)&&(validposy==global[0].y))\\when ball reaches its desired position
       {status='r'; break;}
       
      }\\end of while loop which operates until ball is interrupted or reaches its desired pos or enters goal or boundary
          
          
     chance==1?(dee='D'):(dee='d');
     chance==1?(goal='G'):(goal='g');
     
     \*switch case is applied to check whether ball is interupted or reached its destination or got into goal or crossed the boundary*\
     
     switch(status)
     {
       
       case 'r':
            powerreqb=preqb(global[0].x,global[0].y,local[0].x,local[0].y);
            validposx=global[0].x;     validposy=global[0].y;            
            while(powerreq>local[phitter].strength)\\while loop to find the valid pos when hitter has enough power to make the ball reach
                                                    \\there
            {
              if(validposx!=local[0].x)(xdiff>0)?(validposx)--:(validposx)++;
              if(validposy!=local[0].y)(ydiff>0)?(validposy)--:(validposy)++;
              powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            }\\end of while loop 
            
           if((falocal[validposx][validposy]==dee)&&(falocal[local[0].x][local[0].y]!=dee)
            chance==1?pts1++:pts2++;\\inc pts if ball lands in the dee and was not in the earlier)
            
           local[0].x=validposx;
           local[0].y=validposy;
           (local[phitter].strength)-=powerreqb; \\update the array accordingly
           
           break;                                                  
           
       case 'i':
            powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            
            while(powerreq>local[phitter].strength)\\while loop to find the valid pos when hitter has enough power to make the ball reach
                                                    \\there
            {
              if(validposx!=local[0].x)(xdiff>0)?(validposx)--:(validposx)++;
              if(validposy!=local[0].y)(ydiff>0)?(validposy)--:(validposy)++;
              powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            }\\end of while loop 
            
           if((falocal[validposx][validposy]==dee)&&(falocal[local[0].x][local[0].y]!=dee)
            chance==1?pts1++:pts2++;\\inc pts if ball lands in the dee and was not in the earlier)
            
           local[0].x=validposx;
           local[0].y=validposy;
           
           powerreqb=preqb(global[0].x,global[0].y,local[0].x,local[0].y);\\strength is dec on the basis of coordinates given by user 
           if(powerreqb>=local[phitter].strength)local[phitter].strength=0;\\irrespective of where the ball stops 
                                                                        \\on idea given by chirag    
           else (local[phitter].strength)-=powerreqb;
           
           break;
           
       case 'G':
            powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            
            while(powerreq>local[phitter].strength)\\while loop to find the valid pos when hitter has enough power to make the ball reach
                                                    \\there
            {
              if(validposx!=local[0].x)(xdiff>0)?(validposx)--:(validposx)++;
              if(validposy!=local[0].y)(ydiff>0)?(validposy)--:(validposy)++;
              powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            }\\end of while loop
            
            if(falocal[validposx][validposy]!='G')
            {if(falocal[validposx][validposy]=='D')
              {if(chance==1&&falocal[local[0].x][local[0].y]!='D')
                pts1++;
              }
              local[0].x=validposx;
              local[0].y=validposy;  
              }\\end of if loop 7 lines up 
            
             else \\if the ball is still in the goal 
             {
               goal1++;
               pts1+=10;
               
               found=0;\*found is to break the loop when a correct place is found to place the ball once goal happens*\
                
                for(i=25;found==0;i++)
                {
                  for(j=1;j<=11;j++)
                  {if((local[j].x==50)&&(local[j].y==i))break;}\\end of for
                  
                  if(j==12)
                  {local[0].x=50;
                    local[0].y=i;
                    found++;
                  }\\end of if
                }\\end of for
                
              }\\end of else
              
              powerreqb=preqb(global[0].x,global[0].y,local[0].x,local[0].y);\\strength is dec on the basis of coordinates given by user 
           if(powerreqb>=local[phitter].strength)local[phitter].strength=0;\\irrespective of where the ball stops 
                                                                        \\on idea given by chirag    
           else (local[phitter].strength)-=powerreqb;
           
           break;
           
          
          case 'g':
                  powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            
            while(powerreq>local[phitter].strength)\\while loop to find the valid pos when hitter has enough power to make the ball reach
                                                    \\there
            {
              if(validposx!=local[0].x)(xdiff>0)?(validposx)--:(validposx)++;
              if(validposy!=local[0].y)(ydiff>0)?(validposy)--:(validposy)++;
              powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            }\\end of while loop
            
            if(falocal[validposx][validposy]!='g')
            {if(falocal[validposx][validposy]=='d')
              {if(chance==0&&falocal[local[0].x][local[0].y]!='d')
                pts2++;
              }
              local[0].x=validposx;
              local[0].y=validposy;  
              }\\end of if loop 7 lines up 
            
             else \\if the ball is still in the goal 
             {
               goal2++;
               pts2+=10;
               
               found=0;\*found is to break the loop when a correct place is found to place the ball once goal happens*\
                
                for(i=25;found==0;i++)
                {
                  for(j=12;j<=22;j++)
                  {if((local[j].x==50)&&(local[j].y==i))break;}\\end of for
                  
                  if(j==23)
                  {local[0].x=50;
                    local[0].y=i;
                    found++;
                  }\\end of if
                }\\end of for
                
              }\\end of else
              
              powerreqb=preqb(global[0].x,global[0].y,local[0].x,local[0].y);\\strength is dec on the basis of coordinates given by user 
           if(powerreqb>=local[phitter].strength)local[phitter].strength=0;\\irrespective of where the ball stops 
                                                                        \\on idea given by chirag    
           else (local[phitter].strength)-=powerreqb;
           
           break; 
           
         case 'B':
              powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
              if(powerreqb<=local[phitter].strength)
               {chance==1?pts1--:pts2--;}\\to decrement pts in case a team hits the ball in boundary 
               
               
           do {
              if(validposx!=local[0].x)(xdiff>0)?(validposx)--:(validposx)++;
              if(validposy!=local[0].y)(ydiff>0)?(validposy)--:(validposy)++;
              powerreqb=preqb(validposx,validposy,local[0].x,local[0].y);
            }while(powerreq>local[phitter].strength);\\do while loop to find the valid pos when hitter has enough power to make the ball reach
                                                    \\there
                                                    
            powerreqb=preqb(global[0].x,global[0].y,local[0].x,local[0].y);\\strength is dec on the basis of coordinates given by user 
           if(powerreqb>=local[phitter].strength)local[phitter].strength=0;\\irrespective of where the ball stops 
                                                                        \\on idea given by chirag    
           else (local[phitter].strength)-=powerreqb;
           
           
           local[0].x=validposx;
           local[0].y=validposy;
           
           break;                                       
             };\\end of switch case
             
         }\\to end the if in line 108 and to check whether phitter's strength is more than opponent's strength
   
   
    }\\end of ballpos fn
        
        
        
   int preq(int finalx,int finaly, int initialx ,int initialy )
   {float req;
    req=floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
    return (int)req;}     
        
    int preqb(int finalx,int finaly, int initialx ,int initialy )
   {float req;
    req=2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
    return (int)req;}     
             
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
              
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
                   
