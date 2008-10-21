#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>



using namespace std;

 //The name of your class should be teamxxxx where xxxx is the no. u will get at the time of registration and will
class team0041
{               //be unique for every participant
  private:


  struct goldee//contains the cordinates of the opnnt n my dee n gol's coord
    { int x,y;
    };
  int pl,ph,plo,pho,p;//lower and upper limits of my and oppntn's players
  struct goldee opgol[14][31],mygol[14][31],opdee[40][41],mydee[40][41];
  struct goldee myfield[100][50]; 
  int player_num,player_no;
  int blplyr,ball_player,a;//player having the ball
  int mark[11];//contain the info of marking
  int marko[11];
  char plrmd[23];//contains the roles of my player
  int team;  //team is a variable used in player function which tells all of the functions defined by the participant what their team no. is 
             //it is not mandatory for the player to use this variable .player can use any other means to satisfy the need
  //private fns 
  //this fn returns the strength req to move your player from one place to another 
  int preqp(int finalx,int finaly, int initialx ,int initialy )
	{float req;
    req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
    return (int)req;}     

//this fn returns the strength req by your hitter to move the ball from one place to another 
  int preqb(int finalx,int finaly, int initialx ,int initialy )
	{float req; int i;
    req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	 i=(int)req;
	 return i;} 
  public:
   
          
   int init(int team_number, struct player p[23],char farray[][51])   // this fn must be there in your program ,it will be called only 
	{                                                             //once at the beginning of the program .It will tell u whether u are 
      team=team_number; 
                                              //player 1 or 2 and this will also give u the basic fieldarray ie where there is  
	}                                                  //a goal or a dee or a boundary and struct player *p gives u the initial player 
                                                 //distribution in the field
                                                 
    int player(struct player p[23])   
     { // Declaration
       a = -1;
       static int k = 1;
       int i,temp,j,ind = 0;
        //assigning limits according to player no.
	 if(team == 1)
	  {

		pl = 1;            //pl shows the lower limit and ph shows the upper limit of players in the array of structures ,i.e. if player
		ph = 11;           //is 1st then his players will be 1 to 11 and if he is 2nd then his players will be 12 to 22
		plo = 12;
		pho = 22;
        player_num = 1;
	  }

	 else
	  {
		  pl = 12;
		  ph = 22;
		  plo = 1;
		  pho = 11;
          player_num = 2;
	  }
     //Findin which plr has the ball
     for(i=1;i<23;i++)
      { if( p[0].x==p[i].x && p[0].y==p[i].y )
         { blplyr = i;
           temp = 1;
           break;    
         }
      }
     if( temp == 0 )
      blplyr = 0;//no player has the ball    
         
     assngd();//assgns my and opp dee n goal coord
     
	 assnrl();
	 assnfld();//assign the field configuration accd to me
     	 // checking where is ball
    
			//player having the ball
   
  if( k == 1)//first move     
   { intlz();
     ind = 1; 
     for( i = pho; i>= plo; i--)
      { if( p[i].x == p[0].x && p[i].y == p[0].y )
         { ind = 0;
            break;
         }
      } 
      if( ind == 1 && p[0].x == 50 && p[0].y == 25)// my team gets the first chance
       {
               p[0].x = myfield[40][13].x;
         p[0].y = myfield[40][13].y;
         p[pl+7].x = myfield[40][13].x;
         p[pl+7].y = myfield[40][13].y;
         markf(p,k);
         k++;
         return ph;
       }
     for(i=1;i<23;i++)
    if( p[0].x==p[i].x && p[0].y==p[i].y )
     {
        blplyr=i;
        break;    
     }  
    
    if(i==23)
     {
       //so no player is having the ball
       
		  a=case3(p);
		 markf(p,k);
		 k++;
         return a;   //returns the hitter of the ball to the controller 
     }
    
    
	 else if((i<=11&&player_no==1)||(i>11&&player_no==2))
      {
        //then ball is with my team player
        
			a=case1(p);
		  markf(p,k);
		  k++;
        return a;
      }
     else 
      { for(i=pl; i <= ph; i++)
         { if( p[0].x==p[i].x && p[0].y==p[i].y )
            {
              blplyr=i;
              a = case1(p); 
              markf(p,k);
              k++;
              return a;  
            }
         
          else
           { a = case2(p);//ball is with no player
             markf(p,k);
             k++;
             return a;
           }
	     }
	 
      }
      
  
  }
  
  else//not the first chance
   { return ph; 
     for(i=1;i<23;i++)
      if( p[0].x==p[i].x && p[0].y==p[i].y )
       {
         blplyr=i;
         break;    
       }  
    
     if(i==23)
      {
        //so no player is having the ball
       
		  a=case3(p);
		 markf(p,k);
             k++;
		 return a;   //returns the hitter of the ball to the controller 
      }
    
    
	 else if((i<=11&&player_no==1)||(i>11&&player_no==2))
      {
        //then ball is with my team player
        
			a=case1(p);
		 
        return a;
      }
     else 
      { for( j = pl; j <= ph; j++ )
         { if( p[0].x==p[j].x && p[0].y==p[j].y )
            {
              blplyr=j;
              a = case1(p); 
              markf(p,k);
             k++; 
             return a;
            }
         
        else
         { a = case2(p);
           return a;
         }
	    }
      }
	 
  } 
  markf(p.k);
  k++;
  return a;
  }//end of player fnctn        
    
  //fnctn to initialize mark and marko
  void intlz()
   { int i = 0,j;
	 for( i = pl,j = plo; i <= ph; i++,j++)
      { mark[i] = 0;
        marko[j] = 0;
      }
   } 
  //functn to assgn the opp n my dee n gol cord
  void assngd()   
   { //Declaration
     int lgol_y = 10,lgol_x1 = 1,lgol_x2 = 99,ldee_y = 5,ldee_x1 = 1,ldee_x2 = 99;
     int i,j;
	 switch(team)
      { case 1:
          for( i = 0;i < 14;i++,lgol_x1++,lgol_x2-- )
           for( j = 0,lgol_y = 10;j < 31;j++,lgol_y++ )
              { opgol[i][j].x = lgol_x2;
                mygol[i][j].x = lgol_x1;
                opgol[i][j].y = lgol_y;
                mygol[i][j].y = lgol_y;
              }
          for( i = 0;i < 40; i++,ldee_x1++,ldee_x2-- )
           for( j = 0,ldee_y = 5; j < 41; j++,ldee_y++ )
              { opdee[i][j].x = ldee_x2;
                mydee[i][j].x = ldee_x1;
                opdee[i][j].y = ldee_y;
                mydee[i][j].y = ldee_y;
              }
           break;
        case 2:
           for( i = 0;i < 14; i++,lgol_x1++,lgol_x2-- )
            for( j = 0,lgol_y = 10;j < 31; j++,lgol_y++ )
              { opgol[i][j].x = lgol_x1;
                mygol[i][j].x = lgol_x2;
                opgol[i][j].y = lgol_y;
                mygol[i][j].y = lgol_y;
              }
           for( i = 0;i < 40; i++,ldee_x1++,lgol_x2-- )
            for( j = 0,ldee_y = 5; j < 41; j++,ldee_y++ )
              { opdee[i][j].x = ldee_x1;
                mydee[i][j].x = ldee_x2;
                opdee[i][j].y = ldee_y;
                mydee[i][j].y = ldee_y;
              }
           break;  
      } 
   }   
  //fnctn to assgn thr role as defmd, mid, att the formation is 1-3-4-3
  void assnrl( )                                                                                               
   { //Declaration
     int i = pl;
      for( i = pl; i < pl+4; i++ )
       plrmd[i] = 'd';//defender
      for(i = pl +4; i < pl + 7; i++ )
       plrmd[i] = 'l';//defensive midfielder
      for(i = pl + 10;i < pl + 10;i++)
       plrmd[i] = 'h';//attacking mid
      plrmd[i] = 'f';//forward     
   }
  //fnctn to search the nearest feasible coordinate of opp gol or dee as mentioned with srch which
  //takes the values 'g' or 'd'. the cordinate so found is reflected in cord
  int inrangegd(struct player plr[23],char srch,struct goldee *cord)
   { //Declaration
     int i,j,l,diff,flag = 0,max = 0,s;
     l = oppow(plr);//returns the max power of oppnt at the same position
     switch(srch)
      { case 'g':
         for( i = 13; i >= 0; i-- )
          { for( j = 0; j < 31; j++)
             { s = preqb(opgol[i][j].x,opgol[i][j].y,plr[blplyr].x,plr[blplyr].y);
               diff = plr[blplyr].strength - s - l;
               if(  diff > 0  && intr(plr,opgol[i][j].x,opgol[i][j].y))//to check if the ball is intrpted
                { flag = 1;
                  if( diff >= max )
                   { max = diff;
                     cord->x = plr[blplyr].x;
                     cord->y = plr[blplyr].y;
                   }
                }     
             }
          }
         return flag;
         break;
        case 'd' :
         for( j = 40; j >= 0; j-- )
          for( i = 39; i >= 0; i-- )
           {  s = preqb(opdee[i][j].x,opdee[i][j].y,plr[blplyr].x,plr[blplyr].y);
              diff = plr[blplyr].strength - s - l;
              if(  diff > 0  && intr(plr,opdee[i][j].x,opdee[i][j].y))//to check if the ball is intrpted
               { flag = 1;
                  if( diff >= max )          
                   { max = diff;
                     cord->x = plr[blplyr].x;
                     cord->y = plr[blplyr].y;
                   }
               }     
           }
          return flag; 
          break;
      }
   }
   
  //fnctn to find whthr ball is intrptd or not; 1 for no and 0 for yes by opp
  int intr( struct player q[23],int x, int y )
   { //declaration
     int xi,yi,flag = 1,i,j,d1,d2,k;
     xi = q[blplyr].x;
     yi = q[blplyr].y;
     d1 = x - xi;
     d2 = y - yi;
     if( d1 >= 0 && d2 >= 0 )//passing southeast 
      { for( i = xi+1,j = yi+1; i <= x && j <= y; i++,j++ )
         {  for( k = plo; k <= pho ; k++ )
             { if( q[k].x == i && q[k].y == j )
                { flag = 0;
                  break;
                }
             }
            if(flag == 0 )
            break;
         }
        if( flag != 0 )//one of the variable has ended while orher still remains
         { if (i < x || j < y )
            { if( i < x )
               { while( i <= x )
                  { for( k = plo; k <= pho ; k++ )
                     { if( q[k].x == i && q[k].y == j )
                        { flag = 0;
                          break;
                        }
                     }
                    i++;
                  }
               }
              else
               {  while( j <= y )
                  { for( k = plo; k <= pho ; k++ )
                     { if( q[k].x == i && q[k].y == j )
                        { flag = 0;
                          break;
                        }
                     }
                    j++;
                  }
               }
		    }
         } 
	 }
       
     else if( d1 < 0 && d2 > 0)//passing northeast 
      { for( i = xi-1,j = yi+1; i >= x && j <= y; i--,j++ )
         {  for( k = plo; k <= pho ; k++ )
             { if( q[k].x == i && q[k].y == j )
                { flag = 0;
                  break;
                }
             }
            if(flag == 0 )
            break;
         }
        if( flag != 0 )//one of the variable has ended while other still remains
         { if (i > x || j < y )
            { if( i >= x )
               { while( i >= x )
                  { for( k = plo; k <= pho ; k++ )
                     { if( q[k].x == i && q[k].y == j )
                        { flag = 0;
                          break;
                        }
                     }
                    i--;
                  }
               }
              else
               {  while( j <= y )
                  { for( k = plo; k <= pho ; k++ )
                     { if( q[k].x == i && q[k].y == j )
                        { flag = 0;
                          break;
                        }
                     }
                    j++;
                  }
               }
		     }
         }    
      }
     else if( d1 > 0 && d2 < 0)//passingsouthwest 
      { for( i = xi+1,j = yi-1; i <= x && j >= y; i++,j-- )
         {  for( k = plo; k < pho ; k++ )
             { if( q[k].x == i && q[k].y == j )
                { flag = 0;
                  break;
                }
             }
            if(flag == 0 )
            break;
         }
        if( flag != 0 )//one of the variable has ended while other still remains
         { if (i < x || j > y )
            { if( i <= x )
               { while( i < x )
                  { for( k = plo; k <= pho ; k++ )
                     { if( q[k].x == i && q[k].y == j )
                        { flag = 0;
                          break;
                        }
                     }
                    i++;
                  }
               }
              else
               {  while( j >= y )
                  { for( k = plo; k <= pho ; k++ )
                     { if( q[k].x == i && q[k].y == j )
                        { flag = 0;
                          break;
                        }
                     }
                    j--;
                  }
               }
		    }
		}            
      }
       
     else if( d1 < 0 && d2 < 0)//passing northwest 
      { for( i = xi-1,j = yi-1; i >= x && j >= y; i--,j-- )
         {  for( k = plo; k <= pho ; k++ )
             { if( q[k].x == i && q[k].y == j )
                { flag = 0;
                  break;
                }
             }
            if(flag == 0 )
            break;
         }
        if( flag != 0 )//one of the variable has ended while oter still remains
         { if (i > x || j > y )
            { if( i > x )
               { while( i >= x )
                  { for( k = plo; k <= pho ; k++ )
                     { if( q[k].x == i && q[k].y == j )
                        { flag = 0;
                          break;
                        }
                     }
                    i--;
                  }
               }
              else
               {  while( j > y )
                  { for( k = plo; k < pho ; k++ )
                     { if( q[k].x == i && q[k].y == j )
                        { flag = 0;
                          break;
                        }
                     }
                    j--;
                  }
               }
		    }
         }   
      }
    return flag;
   } 
  //fnctn to check if a given player is ahead than another given player
  int ahead(struct player t[23],int i)
   { //Declaration
     int j = 0;
     switch(team)
      { case 1:
         if( t[blplyr].x <= t[i].x )
          j = 1;
         else 
          j = 0;
         break;
        case 2:
         if( t[blplyr].x >= t[i].x )
          j = 1;
         else 
          j = 0;
         break; 
      }
     return j;
   }           
  //fnctn to find  the cord of the player to which ball can be passed cord of the two possible candidates
  //returns the no. of players found
  int inrangp(struct goldee *cord1,struct goldee *cord2,struct player t[23] )
   { //declaration
     char ch;
     int plr1 = 0,max = 0,plr2 = 0,l,temp,flag = 0,s,diff,i,j;//player 1- max,2- second highest
     l = oppow(t);
     ch = plrmd[blplyr]; 
     for( i = ph,j = ph-10;i >= j; i-- )
      { s = preqb(t[i].x,t[i].y,t[blplyr].x,t[blplyr].y);
        diff = t[blplyr].strength - s - l;
        if( diff >= 0 && ahead(t,i) && diff != 50 )//ahead checks if the player to which the ball is to be passed is ahead or not
         { flag = 1;
           if( diff >= max )
            { if( diff == max && i != ph )//if the diff is same for two players then select the one
               { max = diff;             //with max power
                 if(t[blplyr].strength < t[i].strength )
                   { temp = plr1;
                     plr1 = i;
                     plr2 = temp;
                   }
               }
              else if(diff > max)    
               { 
                 temp = plr1;
                 plr1 = i;
                 plr2 = temp;
               }  
            }
          }
      }
     if ( flag == 1 )
      { cord1->x = t[plr1].x;
        cord1->y = t[plr1].y;
        if( plr2 != 0 )
	     { cord2->x = t[plr2].x;
           cord2->y = t[plr2].y;
		 }
      }  
     flag = 0;
	 if( plr1 != 0 && plr2 != 0 )
       flag = 2;
     else if( plr2 == 0)
      { if( plr1 != 0 )
         flag = 1;
      }     
        return flag;
   }
  //fnctn to assgn the field accd to me
  void assnfld( )
   { //Declaration
     int i,j,k; 
     switch(team)
      { case 1: 
         for( i = 99; i >= 1; i-- )
          for( j = 1; j < 50; j++ )
           { k = 100 - i;
             myfield[k][j].x = i;
             myfield[k][j].y = j;
           }
         break;
        case 2:
         for( i = 1; i < 100; i++ )         
          for( j = 1; j < 50; j++ )
           { myfield[i][j].x = i;
             myfield[i][j].y = j;
           }
         break;  
      }
   }                      
 //fnctn to break opnt markin to pass the ball to my player and changes the cord of receiver
 int brkmrk( struct player pla[23],struct goldee *cord1,struct goldee *cord2, int h )
  { //declaration
    struct goldee p,q;
    int tmp1 = 0,tmp2 = 0,tmpe1 = 0,tmpe2 = 0,s1,s2,t1,t2,str1,str2,i,j;
    int flag = 0,m,n,l,plr;
	char ch;
	int d1,d2,d3,d4;
	blplyr = plr;
    int strlft1 = 0,strlft2 = 0;
    l = oppow(pla);
    ch = plrmd[plr];
    p = *cord1;
    q = *cord2;
    d1 = p.x - pla[plr].x;
    d2 = p.y - pla[plr].y;
    d3 = q.x - pla[plr].x;
    d4 = q.y - pla[plr].y;
    m = srch(pla,cord1);//fnctn to assgn player no to players with the given coordinates
    n = srch(pla,cord2);
    //for cord1 i.e. max power 
    if( d1 > 0 && d2 > 0 )
      { for( i = p.x; ; i-- )
         { t1 = pla[m].strength - preqp(i,p.y,p.x,p.y);
           if( intr(pla,i,p.y) && inzon(pla,m,i,p.y) && ( t1 >= 0 ) && ahd(pla,i,p.y) )//inzon checks that the given player is in its defmdined zone and ahd checks the player is ahead
            { tmp1 = 1;
              break;
            }
		   if(ahd(pla,i,p.y) == 0 )
            break;
         }
        for( j = p.y; ;j-- )
         { t2 = pla[m].strength - preqp(p.x,j,p.x,p.y);
           if( intr(pla,p.x,j) && inzon(pla,m,p.x,j) && ( t2 >= 0 ) )
            { tmp2 = 1;
              break;
            }  
		   if( inzon(pla,plr,p.x,j) == 0)
            break;
         }
        if( tmp1 == 1 || tmp2 ==1 )   
         { s1 = preqb(i,p.y,pla[plr].x,pla[plr].y) ; 
           s2 = preqb(p.x,j,pla[plr].x,pla[plr].y) ;    
           if( t2 > t1 )
            { if( s2 <= 50 && tmp2 == 1)
               { str1= t2;
                 flag = 1;
                 p.y = j;
               }
            }  
           else if(t1 == t2)
            { if( s2 <= 50 && tmp2 == 1)
               { str1= t2;
                 flag = 1;
                 p.y = j;
               }
              else if( s1 <= 50 && tmp1 == 1)
               { str1= t1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if( s1 <= 50 && tmp1 == 1 )
               { str1= t1;
                 flag = 1;
                 p.x = i;
               }
            }
         }  
      }
    else if( d1 > 0 && d2 < 0 )
      { for( i = p.x; ; i-- )
         { t1 = pla[m].strength - preqp(i,p.y,p.x,p.y);
           if( intr(pla,i,p.y) && inzon(pla,m,i,p.y) && ( t1 >= 0) && ahd(pla,i,p.y) )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1;
              break;
            } 
		   if(ahd(pla,i,p.y) == 0)
		    break;
         }
        for( j = p.y; ;j++ )
         { t2 = pla[m].strength - preqp(p.x,j,p.x,p.y);
           if( intr(pla,p.x,j) && inzon(pla,m,p.x,j) && ( t2 >= 0))
            { tmp2 = 1;
              break;
            }
		   if(inzon(pla,i,p.x,j) == 0)
		    break;
         }
        if( tmp1 == 1 || tmp2 == 1)   
         { s1 = preqb(i,p.y,pla[plr].x,pla[plr].y); 
           s2 = preqb(p.x,j,pla[plr].x,pla[plr].y);    
           if( t2 > t1 )
            { if( s2 <= 50 && tmp2 == 1 )
               { str1= t2;
                 flag = 2;
                 p.y = j;
               }
            }  
           else if(t1 == t2)
            { if( s2 <= 50 && tmp2 == 1)
               { str1= t2;
                 flag = 1;
                 p.y = j;
               }
              else if( s1 <= 50 && tmp1 == 1)
               { str1= t1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if( s1 <= 50 && tmp1 == 1 )
               { str1= t1;
                 flag = 1;
                 p.x = i;
               }
            }
         }   
      }
    else if( d1 < 0 && d2 > 0 )
      { for( i = p.x; ; i++ )
         { t1 = pla[m].strength - preqp(i,p.y,p.x,p.y);
           if( intr(pla,i,p.y) && inzon(pla,m,i,p.y) && ( t1 >= 0) && ahd(pla,i,p.y) )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1; 
              break;
            }
           if( ahd(pla,i,p.y) == 0)
            break; 
         }
        for( j = p.y; ;j-- )
         { t2 = pla[m].strength - preqp(p.x,j,p.x,p.y);
           if( intr(pla,p.x,j) && inzon(pla,m,p.x,j) && ( t2 > 0 ))
            { tmp2 = 1;
              break;
            }
		   if(inzon(pla,m,p.x,j) == 0) 
            break;
         }
        if( tmp1 == 1 || tmp2 == 1)   
         { s1 = preqb(i,p.y,pla[plr].x,pla[plr].y); 
           s2 = preqb(p.x,j,pla[plr].x,pla[plr].y);    
           if( t2 > t1 )
            { if( s2 <= 50 && tmp2 == 1 )
               { str1= t2;
                 flag = 1;
                 p.y = j;
               }
            }  
           else if(t1 == t2)
            { if( s2 <= 50 && tmp2 == 1)
               { str1= t2;
                 flag = 1;
                 p.y = j;
               }
              else if( s1 <= 50 && tmp1 == 1)
               { str1= t1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if( s1 <= 50 && tmp1 == 1 )
               { str1= t1;
                 flag = 1;
                 p.x = i;
               }
            }
         }   
      }
    else if( d1 < 0 && d2 < 0 )
      { for( i = p.x; ; i++ )
         { t1 = pla[m].strength - preqp(i,p.y,p.x,p.y);
           if( intr(pla,i,p.y) && inzon(pla,m,i,p.y) && ( t1 >= 0 ) && ahd(pla,i,p.y)  )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1;
              break;
            }
		   if( ahd(pla,i,p.y) == 0)
		    break;

         }
        for( j = p.y; ;j++ )
         { t2 = pla[m].strength - preqp(p.x,j,p.x,p.y);
           if( intr(pla,p.x,j) && inzon(pla,m,p.x,j) && ( t2 >= 0 ))
           { tmp2 = 1;
             break;
           }
           if ( inzon(pla,plr,p.x,j) == 0)
			   break;
         }
        if( tmp1 == 1 || tmp2 == 1 )   
         { s1 = preqb(i,p.y,pla[plr].x,pla[plr].y); 
           s2 = preqb(p.x,j,pla[plr].x,pla[plr].y);    
           if( t2 > t1 )
            { if( s2 <= 50 && tmp2 == 1 )
               { str1= t2;
                 flag = 1;
                 p.y = j;
               }
            }  
           else if(t1 == t2)
            { if( s2 <= 50 && tmp2 == 1)
               { str1= t2;
                 flag = 1;
                 p.y = j;
               }
              else if( s1 <= 50 && tmp1 == 1)
               { str1= t1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if( s1 <= 50 && tmp1 == 1)
               { str1= t1;
                 flag = 1;
                 p.x = i;
               }
            }
         }   
      }
                                   
     //for cord2 i.e. 2ndmax power 
  if( h == 2 )
   { if( d3 > 0 && d4 > 0 )
      { for( i = q.x; ; i-- )
         { t1 = pla[m].strength - preqp(i,p.y,p.x,p.y);
        if( intr(pla,i,q.y) && inzon(pla,n,i,q.y) && ( t1 >= 0) && ahd(pla,i,p.y))  //inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            }
        if( ahd(pla,i,p.y) == 0 )
		 break;
         }
        for( j = q.y; ;j-- )
         { t2 = pla[m].strength - preqp(p.x,j,p.x,p.y);
           if( intr(pla,p.x,j) && inzon(pla,n,p.x,j) && ( t2 >= 0) )
            { tmpe2 = 1;
              break;
            }
		   if( inzon(pla,n,p.x,j) == 0 )
            break;
         }
        if( tmpe1 == 1 || tmpe2 == 1 )   
         { s1 = preqb(i,q.y,pla[plr].x,pla[plr].y); 
           s2 = preqb(q.x,j,pla[plr].x,pla[plr].y);    
           if( t1 > t2 )
            { if( s2 <= 50 &&  tmpe2 == 1)
               { str2 = t2;
                 flag = 2;
                 q.y = j;
               }
            }  
          else if(t1 == t2)
            { if( s2 <= 50 && tmpe2 == 1)
               { str2= t2;
                 flag = 1;
                 q.y = j;
               }
              else if( s1 <= 50 && tmpe1 == 1)
               { str2= t1;
                 flag = 1;
                 q.x = i;
               } 
            }    
           else 
            { if( s1 <= 50 && tmpe1 == 1 )
               { str2 = t1;
                 flag = 2;
                 q.x = i;
               }
            }
         }  
      }
    else if( d1 > 0 && d2 < 0 )
      { for( i = q.x; ; i-- )
         { t1 = pla[m].strength - preqp(i,p.y,p.x,p.y);
           if( intr(pla,i,q.y) && inzon(pla,n,i,q.y) && ( t1 >= 0 ) && ahd(pla,i,p.y) )//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            }
		   if( ahd(pla,i,p.y) == 0)
            break;
         }
        for( j = q.y; ;j++ )
         { t2 = pla[m].strength - preqp(p.x,j,p.x,p.y);
           if( intr(pla,q.x,j) && inzon(pla,n,p.x,j) && ( t2 >= 0 ))
            { tmpe2 = 1;
              break;
            }
		   if( inzon(pla,n,p.x,j) == 0 )
		    break;
         }
        if( tmpe1 == 1 || tmpe2 == 1 )   
         { s1 = preqb(i,q.y,pla[plr].x,pla[plr].y); 
           s2 = preqb(q.x,j,pla[plr].x,pla[plr].y);    
           if( t2 > t1 )
            { if( s2 <= 50 && tmpe2 == 1)
               { str2 = t2;
                 flag = 2;
                 q.y = j;
               }
            }  
           else if(t1 == t2)
            { if( s2 <= 50 && tmpe2 == 1)
               { str2= t2;
                 flag = 1;
                 q.y = j;
               }
              else 
               { str2= t1;
                 flag = 1;
                 q.x = i;
               } 
            }    
           else 
            { if( s1 <= 50 && tmpe1 == 1 )
               { str2 = t1;
                 flag = 2;
                 q.x = i;
               }
            }
         }   
      }
    else if( d1 < 0 && d2 > 0 )
      { for( i = q.x; ; i++ )
         { t1 = pla[m].strength - preqp(i,p.y,p.x,p.y);
           if( intr(pla,i,q.y) && inzon(pla,n,i,p.y) && ( t1 >= 0) && ahd(pla,i,p.y) )//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            }
		   if( ahd(pla,i,p.y) == 0 )
		    break;
         }
        for( j = q.y; ;j-- )
         { t2 = pla[m].strength - preqp(p.x,j,p.x,p.y);
           if( intr(pla,q.x,j) && inzon(pla,n,p.x,j) && ( t2 >= 0) )
            { tmpe2 = 1;
              break;
            }
		   if( inzon(pla,n,p.x,j) == 0 )
		    break;
         }
        if( tmpe1 == 1 || tmpe2 == 1)
         { s1 = preqb(i,q.y,pla[plr].x,pla[plr].y); 
           s2 = preqb(q.x,j,pla[plr].x,pla[plr].y);    
           if( t2 > t1 )
            { if( s2 <= 50 && tmpe2 == 1 )
               { str2 = t2;
                 flag = 2;
                 q.y = j;
               }
            }  
           else if(t1 == t2)
            { if( s2 <= 50 && tmpe2 == 1)
               { str2= t2;
                 flag = 1;
                 q.y = j;
               }
              else if( s1 <= 50 && tmpe1 == 1)
               { str2= t1;
                 flag = 1;
                 q.x  = i;
               } 
            }    
           else if( i >= pla[plr].y )
            { if( s1 <= 50 && tmpe1 == 1 )
               { str2 = t1;
                 flag = 2;
                 q.x = i;
               }
            }
         }   
      }
    else if( d1 < 0 && d2 < 0 )
      { for( i = q.x; ; i++ )
         { t1 = pla[m].strength - preqp(i,p.y,p.x,p.y);
           if( intr(pla,i,q.y) && inzon(pla,n,i,p.y) && ( t1 >= 0) && ahd(pla,i,p.y)  )//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            }
		   if( ahd(pla,i,p.y) == 0)
			   break;
         }
        for( j = p.y; ;j++ )
         { t2 = pla[m].strength - preqp(p.x,j,p.x,p.y);
           if( intr(pla,q.x,j) && inzon(pla,n,p.x,j) && ( t2 >= 0 ) )
            { tmpe2 = 1;
              break;
            }
		   if( inzon(pla,n,p.x,j) == 0 )
            break;
         }
        if( tmpe1 == 1 && tmpe2 == 1)   
         { s1 = preqb(i,q.y,pla[plr].x,pla[plr].y); 
           s2 = preqb(q.x,j,pla[plr].x,pla[plr].y);    
           if( t2 > t1 )
            { if( s2 <= 50 && tmpe2 == 1)
               { str2 = t2;
                 flag = 2;
                 q.y = j;
               }
            }  
           else if(t1 == t2)
            { if( s2 <= 50 && tmpe2 == 1)
               { str2= s2;
                 flag = 1;
                 q.y = j;
               }
              else if( s1 <= 50 && tmpe1 == 1)
               { str2= t1;
                 flag = 1;
                 q.x = i;
               } 
            }    
           else 
            { if( s1 <= 50 && tmpe1 == 1 )
               { str2 = t1;
                 flag = 2;
                 q.x = i;
               }
            }
         }   
      }
   }    
     if( tmp1 == 1 || tmp2 == 1 )  
      strlft1 = pla[m].strength - s1 - l;
     if( tmpe1 == 1 || tmpe2 == 1 )  
      strlft2 = pla[n].strength - s2 - l;
     flag = 0;
     if( strlft1 > 0 || strlft2 < 0 )
      { if( strlft1 > strlft2 )
         { flag = 1;
           pla[m].x = p.x;
           pla[m].x = p.y;
         }
        else if( strlft2 > strlft1 )
         { flag = 2;
           pla[n].x  = q.x;
           pla[n].y  = q.y;
         }
       else
         { if( s1 <= s2 )
            { flag = 1;
              pla[m].x = p.x;
              pla[m].x = p.y;
            }
           else 
            { flag = 2;
              pla[n].x  = q.x;
              pla[n].y  = q.y;
            } 
         }
      }   
     return flag;
  }        
 //functn when the ball is with me                    
 int case1( struct player p[23] )
  {  //declaration
     char ch = plrmd[blplyr],temp,w;
	 char ch1,ch2;
     int t,h,pow;
     t = oppow(p); 
     char mod1 = 'g';char mod2 = 'd';
     struct goldee *cord,*cord2;
     switch(ch)
      { case 'l' ://the ball is with the defmdmid 
             if( searchdee(p,cord) )//checks if any of my player is standing in the oppnt dee is possible to receive the ball from me
              { ascrd(p[0],cord);//assigns the cord of cord to p
                return blplyr;
              }
             else if( inrangegd(p,mod2,cord) )
              { pow = p[blplyr].strength - preqb(cord->x,cord->y,p[blplyr].x,p[blplyr].y) - t;
                if(pow > 15)
                 { ascrd(p[0],cord);
                   return blplyr;
                 }
              }                                                           
             else if( inrangp(cord,cord2,p) )
              { h =  inrangp(cord,cord2,p);//1 or 2
                temp = brkmrk(p,cord,cord2,h);
                if(  temp != 0 )
                 { if( temp == 1)
                    ascrd(p[0],cord);
                   else if( temp == 2)
                    ascrd(p[0],cord2);   
                   return blplyr;
                 }
              }   
             else if(1)
              { clsst(p,cord,cord2);//finds the closest of 2 players ahead
                temp = altr(p,cord,cord2);
                if(  temp != 0 )
                 { if( temp == 1)
                    ascrd(p[0],cord);
                    else if( temp == 2)
                    ascrd(p[0],cord2);   
                    return blplyr;
                 }
              }   
   
             else 
              return (-1);
             break;
        case 'f' ://the ball is with the forward
             if( inrangegd(p,mod1,cord ))
              { ascrd(p[0],cord);
                return blplyr;
              }
			 else if(9)
			 { w =  inrangp(cord,cord2,p); 
               temp = brkmrk(p,cord,cord2,w);
                if(  temp != 0 )
                 { if( temp == 1)
                    ascrd(p[0],cord);
                   else if( temp == 2)
                    ascrd(p[0],cord2);   
                   return blplyr;
                 }
              }
             else if(1)
              {  clr(p,2);         
                 return blplyr;
              }
             else if(2)
              return(-1);
             break;      
        case 'h' : //the ball is with the attackin mid
             if(inrangegd(p,mod1,cord))
              { ascrd(p[0],cord);
                return blplyr;
              }
             else if( searchdee(p,cord) )//checks if any of my player is standing in the oppnt dee is possible to receive the ball fron me
              { ascrd(p[0],cord);//assigns the cordnts of cord to p
                return blplyr;
              }
             else if( 1 )
              {  t = rn(p,&ch1,cord,&ch2,cord2);//fnctn to make run into the dee
                 if ( t != 0)
                  { temp = atbrk(p,ch1,cord,ch2,cord2,t);//fnctn to break the marking spclly such that player remains in dee
                    if( temp != 0 )
                     { if( temp == 1 )
                       ascrd(p[0],cord);
                       else if( temp == 2)
                       ascrd(p[0],cord2);
                       return blplyr;
                     }
                   }
              }    
             else if(2)
              { clsst(p,cord,cord2);//finds the closest of 2 players ahead
                temp = altr(p,cord,cord2);//altr changes the cord and checks if the pass is feasible
                if(  temp != 0 )
                 { if( temp == 1)
                    ascrd(p[0],cord);
                   else if( temp == 2)
                    ascrd(p[0],cord2);   
                   return blplyr;
                 }
              }     
             else 
              return (-1);
             break; 
         case 'd':
              if(inrangp(cord,cord2,p) )
               { h = inrangp(cord,cord2,p);
				 temp = brkmrk(p,cord,cord2,h);
                 if(  temp != 0 )
                  { if( temp == 1)
                     ascrd(p[0],cord);
                    else if( temp == 2)
                     ascrd(p[0],cord2);   
                    return blplyr;
                  }
               }
              else if(1)
               { clsst(p,cord,cord2);//finds the closest of 2 players ahead
                 temp = altr(p,cord,cord2);
                 if(  temp != 0 )
                  { if( temp == 1)
                     ascrd(p[0],cord);
                    else if( temp == 2)
                     ascrd(p[0],cord2);   
                    return blplyr;
                 }
              } 
              else 
               return (-1);
              break;
         default:
              return (-1);     
         
  }}
 //fnctn to clear the ball as per the different modes spcfd
 void clr( struct player p[23],int mode )               
  { //Declaration
    
    switch(mode)
     { case 2://ball is with forward
          if(p[blplyr].strength >= 10 )
           { switch(team)
              { case 1:
                   if(intr(p,p[blplyr].x+3,p[blplyr].y-1))
                    { p[0].x = p[blplyr].x+3;
                      p[0].y = p[blplyr].y-1;
                    }
                   else
                    {  p[0].x = p[blplyr].x+3;
                       p[0].y = p[blplyr].y+1;
                    }
                   break;
                case 2:
                    if(intr(p,p[blplyr].x-3,p[blplyr].y-1))
                    { p[0].x = p[blplyr].x-3;
                      p[0].y = p[blplyr].y-1;
                    }
                   else
                    {  p[0].x = p[blplyr].x-3;
                       p[0].y = p[blplyr].y+1;
                    }
                   break;
              }
           }
          break;
     } 
  }                                  
 //fnct to see if a player is ahead
 int ahd(struct player p[23],int x, int y)
  { //dclaration
    int flag = 0;
    switch( team )
	{ case 1:
	   if( x <= p[blplyr].x )
	    flag = 1;
       break;
	 case 2:
      if( x >= p[blplyr].x )
       flag = 1;
	  break;
   }
   return flag;
 }
  //fnctn when the ball is with the opponent
 int case2(struct player p[23])
   { //declaration
     int max = 0,i,num = 0,a = -1,s,g,x,y,j,t,m;
	 struct goldee *cord;
     if(spcl(p))//calculates the spcl case scenario when at one position there are more than one players of teams
      { for( i = pl; i <= ph; i++ )
         { s = p[i].strength - preqp(p[0].x,p[0].y,p[pl].x,p[pl].y);
           if ( s > 0 && mark[i] == 0 )
            { if( s >= max )
               { max = s;
                 num = i;
               }
             if( num > 0 )
              { p[num].x = p[i].x;
                p[num].y = p[i].y;
                blplyr = num;
				p[num].strength = p[num].strength - max;
                a = case1(p);
              }
            }
         }
      }          
	 else if(defmd(p))
      { num = srch(p,cord);
	    t = indeop(p,num);
		for( i = pl; i <= ph; i++ )
         { s = p[i].strength - preqp(p[blplyr].x,p[blplyr].y,p[i].x,p[j].y);
           if( s >= 0 && mark[i] == 0  )//mark array contains the oppnt player no. of player marked
            { if( s > max)
               { max = s;
                 num = i;
               }
            }
         }
        if( num != 0 )
         { p[num].x = p[blplyr].x;
           p[num].y = p[blplyr].y;
           blplyr = num;
		   p[num].strength = p[num].strength - max;
           a = case1(p);         
         }
		if( num == 0)
		 { g = marko[blplyr];
		   x = p[g].x;
		   y = p[g].y;
		   if( g != 0)
		    { p[g]. x = p[blplyr].x;
		      p[g].y = p[blplyr].y;
			  p[g].strength = p[g].strength - preqp(p[g].x,p[g].y,x,y);
			  a = case1(p);
		    }
		 }
	 }
     else
      { for( i = ph; i >= ph; i++ )
         { s = p[i].strength - preqp(p[blplyr].x,p[blplyr].y,p[i].x,p[j].y);
           if( s >= 0 && mark[i] == 0 && inzon(p,i,p[i].x,p[i].y) )//mark array contains the oppnt player no. of player marked
            { if( s >= max)
               { max = s;
                 num = i;
               }
            }
         }
        if( num != 0 )
         { p[num].x = p[blplyr].x;
           p[num].y = p[blplyr].y;
           blplyr = num;
           p[num].strength = p[num].strength - max;
           a = case1(p);         
         } 
      }
     return a;     
         
   }
  //fnctn when the ball is with no one
  int case3(struct player p[23])
   { //declaration
     int i,max = 0,a = -1,num = 0,s;
     if( defmd(p) )
      { for( i = pl; i <= ph; i++ )
         { s = p[i].strength - preqp(p[0].x,p[0].y,p[i].x,p[i].y);
           if( s >= 0 && mark[i] == 0 )
            { if( s >= max )
               { max = s;
                 num = i;
               }
            }
         } 
         if( num != 0 )
          { p[num].x = p[0].x;
            p[num].y = p[0].y;
            blplyr = num;
            p[num].strength = p[num].strength - max;
			a = case1(p);
		  }
		
      }
     else
      {  for( i = pl; i <= ph; i++ )
          { s = p[i].strength - preqp(p[0].x,p[0].y,p[i].x,p[i].y);
            if( s >= 0 && mark[i] == 0 )
             { if( s >= max )
                { max = s;
                  num = i;
                }
             }
          } 
         if( num != 0 )
          { p[num].x = p[0].x;
            p[num].y = p[0].y;
            blplyr = num;
			p[num].strength = p[num].strength - max;
            a = case1(p);         
          }
      }
     return a;    
   }       
 //fnctn to assign the cordnts of temp to player l
  int spcl(struct player p[23])
  {   
	  int i,flag=0;
	  for(i=pl;i<=ph && flag == 0;i++)
	  {
		  if( p[i].x == p[blplyr].x && p[i].y == p[blplyr].y)
		  {
			  if( p[i].strength == p[blplyr].strength)
				  flag=1;
		  }
	  }
	  return flag;
  }
 void ascrd( struct player l,struct goldee *temp )
  { //declaration
    
    l.x = temp->x;
    l.y = temp->y;
  } 
 //fnctn to find if a given player is in my dee
 int indeop( struct player p[23],int m)
  { //dclration
    int i,j,flag = 0;
    for( i = 0; i <= 40 && flag != 0;i++)
	 { for( j = 0; j <= 13;j++)
	    { if( p[m].x == mydee[i][j].x && p[m].y == mydee[i][j].y )
	       { flag = 0;
	         break;
	       }
	    }
	}
 }
 //fnctn to return 1 if in defensive mode
 int defmd(struct player p[23])
  { //declaration
    int flag = 0;
    switch(team)
     { case 1:
          if( p[0].x >= 60 )
           flag = 1;
          break;
       case 2:
          if( p[0].x <= 40 )
           flag = 1;
          break;
       default:
          flag = 1;
     }
    return flag;
  }                          
  //fnctn to make the run into oppnts dee and return the no. of players making dee with ch and ch2 takin
  //value 'y' or 'n' if their corresponding cord have changed
  int rn(struct player p[23],char *ch,struct goldee *cord,char *ch2,struct goldee *cord2)
   { //declaration
     int chang_a = 0,chang_b =0,i,m,n,s1,s2,temp = 0; 
     int a = 3, b = 3,flag = 0;
     *ch = 'n';
     *ch2 = 'n';
     for( i = pl; i <= ph; i++ )
      { if( plrmd[i] == 'h' && blplyr != pl )
         { if(flag == 0)
            { flag = 1;
              cord->x = p[pl].x;
              cord->y = p[pl].y;
            }
           else if(flag == 1)
            { flag = 2;
              cord2->x = p[pl].x;
              cord2->y = p[pl].y;
            }
         }
      }
     if(flag == 2)
      { temp = 1;
        m = srch(p,cord);
        n = srch(p,cord2);
        a = srchd(m,p);//searches if the player is already present in the oppnt dee
        b = srchd(n,p);
        if(a == 0)
         chang_a = 1;
        if(b == 0)
         chang_b = 1;
      }  
     else if(flag == 1)
       { temp = 1;
         m = srch(p,cord);
         a = srchd(m,p);
         if(a == 0)
         chang_a = 1;
       }     
     if(temp == 1)
      { if(flag == 2)
         { s1 = p[m].strength - preqp(opdee[39][0].x,cord->y,cord->x,cord->y);
           if( s1 >= 0 && chang_a == 1)
            {cord->x = opdee[39][0].x; 
             i++;
             *ch = 'y';
            }                             
           s2 = p[n].strength - preqp(opdee[39][0].x,cord2->y,cord2->x,cord2->y);
           if( s2 >= 0 && chang_b == 1)
            { cord2->x = opdee[39][0].x;
              *ch2 = 'y';
              i++;
            }
         }      
        else if(flag == 1)
         { s1 = p[m].strength - preqp(opdee[39][0].x,cord->y,cord->x,cord->y);
           if( s1 >= 0 && chang_a == 1 )
            { cord->x = opdee[39][0].x;
              *ch = 'y';
              i++;
            }
         }   
      }
     if( a == 1 &&  b == 1)
      { i = 2;
        flag = 2;
        *ch = 'y';
        *ch2 = 'y';
      }
     else if( a == 1 && b != 1)
      { i = 1;
        flag = 1;
        *ch = 'y';
      }
     else if( a != 1 && b == 1)
      { i = 1;
        flag = 1;
        *ch2 = 'y';
      }
    return flag;
 }          
 //fnctn to find the max oppnt strength present at my position 
 int oppow( struct player p[23] )
  { //declaration
    int powr = 0,max = 0,i;
    for( i = plo; i <= pho; i++ )
     { if(p[blplyr].x == p[i].x && p[blplyr].y == p[i].y )
        { powr = p[i].strength;
          if( powr >= max )
           max = powr;
        }
     }
    return max;
  }
 //fnctn to find two players closest to ballholder of my team
 void clsst( struct player p[23],struct goldee *cord1,struct goldee *cord2 )
  { //declaration
    char ch;
    int plr1 = 0,max,max1,plr2 = 0,l,i,flag = 0 ,j,s,diff,temp = 0,plr;//player 1- max,2- second highest
    l = oppow(p);
    ch = plrmd[blplyr];
	plr = blplyr;
    for( i = ph,j = ph-10;i >= j; i-- )
     { s = preqp(p[i].x,p[i].y,p[blplyr].x,p[blplyr].y);
       diff = p[blplyr].strength - s - l;
        if( ahead(p,i) && diff != 50 )//ahead checks if the player to which the ball is to be passed is ahead or not
         { flag = 1;
           if( diff >= max )
            { if( diff == max && i != ph )//if the diff is same for two players then select the one
               { max1 = diff;//with max power
                  if(p[plr].strength < p[i].strength )
                   { temp = plr1;
                     plr1 = i;
                     plr2 = temp;
                   }
               }
              else if(diff > max)    
               { max1 = max;
		         max = diff;
				 temp = plr1;
                 plr1 = i;
                 plr2 = temp;
               }  
            }
         }
     }
     if ( flag == 1 )
      { cord1->x = p[plr1].x;
        cord1->y = p[plr1].y;
        cord2->x = p[plr2].x;
        cord2->y = p[plr2].y; 
      }  
  }        
 //fnctn to alter the coord of closest players player to bring them close and to break the marking
 int altr( struct player pl[23], struct goldee *cord1, struct goldee *cord2 )
  { //declaration
    struct goldee p,q;
    int tmp1 = 0,tmp2 = 0,tmpe1 = 0,tmpe2 = 0,b1,b2,t1,t2,str1,str2,d1,d2,d3,d4;
    int flag = 0,m,n,l,plr,i,j;
	char ch;
	blplyr = plr;
    int strlft1 = 0,strlft2 = 0;
    l = oppow(pl);
    ch = plrmd[blplyr];
    p = *cord1;
    q = *cord2;
    plr = blplyr;  
    d1 = p.x - pl[plr].x;
    d2 = p.y - pl[plr].y;
    d3 = q.x - pl[plr].x;
    d4 = q.y - pl[plr].y;
    m = srch(pl,cord1);//fnctn to assgn player no to players with the given coordinates
    n = srch(pl,cord2);
    //for cord1 i.e. max power 
    if( d1 > 0 && d2 > 0 )
      { for( i = p.x; ahd(pl,i,p.y) != 0 ; i-- )
         { t1 = pl[m].strength - preqp(i,p.y,p.x,p.y);
           b1 = pl[plr].strength - preqb(i,p.y,p.x,p.y)- l;
           if( intr(pl,i,p.y) && inzon(pl,m,i,p.y) && ( t1 >= 0 ) && ( b1 >= 0 ) && ahd(pl,i,p.y)  )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1;
              break;
            }  
         }
        for( j = p.y;inzon(pl,m,p.x,p.y) != 0 ;j-- )
         { t2 = pl[m].strength - preqp(p.x,j,p.x,p.y);
           b2 = pl[plr].strength - preqb(p.x,j,p.x,p.y) - l;
           if( intr(pl,p.x,j) && inzon(pl,m,p.x,j) && ( t2 >= 0 ) && ( b2 >= 0)  )
            { tmp2 = 1;
              break;
            }  
         }
        if( tmp1 == 1 || tmp2 ==1 )   
         { if( b2 > t1 )
            { if( tmp2 == 1)
               { str1= b2;
                 flag = 1;
                 p.y = j;
               }
            }  
           else if(b1 == b2)
            { if( t2 > t1 && tmp2 == 1)
               { str1= b2;
                 flag = 1;
                 p.y = j;
               }
              else if( tmp1 == 1)
               { str1= b1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if( tmp1 == 1 )
               { str1= b1;
                 flag = 1;
                 p.x = i;
               }
            }
         }  
      }
    else if( d1 > 0 && d2 < 0 )
      { for( i = p.x;ahd(pl,i,p.y) != 0  ; i-- )
         { t1 = pl[m].strength - preqp(i,p.y,p.x,p.y);
           b1 = pl[plr].strength - preqb(i,p.y,p.x,p.y)- l;
           if( intr(pl,i,p.y) && inzon(pl,m,i,p.y) && ( t1 >= 0) && ( b1 >= 0) && ahd(pl,i,p.y) )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1;
              break;
            }  
         }
        for( j = p.y;inzon(pl,m,p.x,j)== 0 ;j++ )
         { t2 = pl[m].strength - preqp(p.x,j,p.x,p.y);
           b2 = pl[plr].strength - preqb(p.x,j,p.x,p.y)- l;
           if( intr(pl,p.x,j) && inzon(pl,m,p.x,j) && ( t2 >= 0) && ( b2 >= 0)  )
            { tmp2 = 1;
              break;
            }  
         }
        if( tmp1 == 1 || tmp2 == 1)   
         { if( b2 > b1 && j >= pl[plr].y )//i do not want to back pass
            { if( tmp2 == 1 )
               { str1= b2;
                 flag = 2;
                 p.y = j;
               }
            }  
           else if(b1 == b2)
            { if( t2 > t1 && tmp2 == 1)
               { str1= b2;
                 flag = 1;
                 p.y = j;
               }
              else if( tmp1 == 1)
               { str1= b1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else if( i >= pl[plr].y )
            { if(  tmp1 == 1 )
               { str1= b1;
                 flag = 1;
                 p.x = i;
               }
            }
         }   
      }
    else if( d1 < 0 && d2 > 0 )
      { for( i = p.x; ahd(pl,i,p.y) != 0 ; i++ )
         { t1 = pl[m].strength - preqp(i,p.y,p.x,p.y);
           b1 = pl[plr].strength - preqb(i,p.y,p.x,p.y)- l;
           if( intr(pl,i,p.y) && inzon(pl,m,i,p.y) && ( t1 >= 0) && ( b1 >= 0 ) && ahd(pl,i,p.y) )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1; 
              break;
            }  
         }
        for( j = p.y;inzon(pl,m,p.x,j) != 0 ;j-- )
         { t2 = pl[m].strength - preqp(p.x,j,p.x,p.y);
           b2 = pl[plr].strength - preqb(p.x,j,p.x,p.y)- l;
           if( intr(pl,p.x,j) && inzon(pl,m,p.x,j) && ( t2 > 0 ) && ( b2 >= 0 )  )
            { tmp2 = 1;
              break;
            }  
         }
        if( tmp1 == 1 || tmp2 == 1)   
         { if( b2 > b1 )
            { if( tmp2 == 1 )
               { str1= b2;
                 flag = 1;
                 p.y = j;
               }
            }  
           else if(b1 == b2)
            { if( t2 > t1 && tmp2 == 1)
               { str1= b2;
                 flag = 1;
                 p.y = j;
               }
              else if( tmp1 == 1)
               { str1= b1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if( tmp1 == 1 )
               { str1= b1;
                 flag = 1;
                 p.x = i;
               }
            }
         }   
      }
    else if( d1 < 0 && d2 < 0 )
      { for( i = p.x;ahd(pl,i,p.y) != 0  ; i++ )
         { t1 = pl[m].strength - preqp(i,p.y,p.x,p.y);
           b1 = pl[plr].strength - preqb(i,p.y,p.x,p.y)- l;
           if( intr(pl,i,p.y) && inzon(pl,m,i,p.y) && ( t1 >= 0 ) && ( b1 >= 0 ) && ahd(pl,i,p.y) )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1;
              break;
            }  
         }
        for( j = p.y;inzon(pl,m,p.x,j) != 0 ;j++ )
         { t2 = pl[m].strength - preqp(p.x,j,p.x,p.y);
           b2 = pl[plr].strength - preqb(p.x,j,p.x,p.y)- l;
           if( intr(pl,p.x,j) && inzon(pl,m,p.x,j) && ( t2 >= 0 ) && ( b2 >= 0) && ahd(pl,p.x,j) )
           { tmp2 = 1;
             break;
           }  
         }
        if( tmp1 == 1 || tmp2 == 1 )   
         { if( b2 > b1 )
            { if( tmp2 == 1 )
               { str1= b2;
                 flag = 1;
                 p.y = j;
               }
            }  
           else if(b1 == b2)
            { if( t2 > t1 && tmp2 == 1)
               { str1= b2;
                 flag = 1;
                 p.y = j;
               }
              else if(tmp1 == 1)
               { str1= b1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if(  tmp1 == 1)
               { str1= b1;
                 flag = 1;
                 p.x = i;
               }
            }
         }   
      }
                                   
     //for cord2 i.e. 2ndmax power 
   if( d3 > 0 && d4 > 0 )
      { for( i = q.x;ahd(pl,i,p.y) != 0  ; i-- )
         { t1 = pl[m].strength - preqp(i,q.y,q.x,q.y);
           b1 = pl[plr].strength - preqb(i,q.y,q.x,q.y)- l; 
           if( intr(pl,i,q.y) && inzon(pl,n,i,q.y) && ( t1 >= 0) && ( b1 >= 0) && ahd(pl,i,q.y) )//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            }  
         }
        for( j = q.y;inzon(pl,n,q.x,j) != 0 ;j-- )
         { t2 = pl[m].strength - preqp(q.x,j,q.x,q.y);
           b2 = pl[plr].strength - preqb(q.x,j,q.x,q.y)- l; 
           if( intr(pl,q.x,j) && inzon(pl,n,q.x,j) && ( t2 >= 0) && ( b2 >= 0) )
            { tmpe2 = 1;
              break;
            }  
         }
        if( tmpe1 == 1 || tmpe2 == 1 )   
         { if( b1 > b2 )
            { if( tmpe2 == 1)
               { str2 = b2;
                 flag = 2;
                 q.y = j;
               }
            }  
          else if(b1 == b2)
            { if( t2 > t1 && tmpe2 == 1)
               { str2= b2;
                 flag = 1;
                 q.y = j;
               }
              else if( tmpe1 == 1)
               { str2= b1;
                 flag = 1;
                 q.x = i;
               } 
            }    
           else 
            { if( tmpe1 == 1 )
               { str2 = b1;
                 flag = 2;
                 q.x = i;
               }
            }
         }  
      }
    else if( d3 > 0 && d4 < 0 )
      { for( i = q.x;ahd(pl,i,p.y) != 0  ; i-- )
         { t1 = pl[m].strength - preqp(i,p.y,p.x,p.y);
           b1 = pl[plr].strength - preqb(i,q.y,q.x,q.y)- l; 
           if( intr(pl,i,q.y) && inzon(pl,n,i,q.y) && ( t1 >= 0 ) && ( b1 >= 0) && ahd(pl,i,q.y) )//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            } 
         }
        for( j = q.y;inzon(pl,n,q.x,j) != 0 ;j++ )
         { t2 = pl[m].strength - preqp(p.x,j,p.x,p.y);
           b2 = pl[plr].strength - preqb(q.x,j,q.x,q.y)- l; 
           if( intr(pl,q.x,j) && inzon(pl,n,q.x,j) && ( t2 >= 0) && ( b2 >= 0) && ahd(pl,q.x,j) )
            { tmpe2 = 1;
              break;
            }  
         }
        if( tmpe1 == 1 || tmpe2 == 1 )   
         { if( b2 > b1 )
            { if( tmpe2 == 1)
               { str2 = b2;
                 flag = 2;
                 q.y = j;
               }
            }  
           else if(b1 == b2)
            { if( t2 > t1 && tmpe2 == 1)
               { str2= b2;
                 flag = 1;
                 q.y = j;
               }
              else if( tmpe1 == 1)
               { str2= b1;
                 flag = 1;
                 q.x = i;
               } 
            }    
           else 
            { if( tmpe1 == 1 )
               { str2 = b1;
                 flag = 2;
                 q.x = i;
               }
            }
         }   
      }
    else if( d3 < 0 && d4 > 0 )
      { for( i = q.x;ahd(pl,i,q.y) != 0  ; i++ )
         { t1 = pl[m].strength - preqp(i,p.y,p.x,p.y);
           b1 = pl[plr].strength - preqb(i,q.y,q.x,q.y)- l; 
           if( intr(pl,i,q.y) && inzon(pl,n,i,q.y) && ( t1 >= 0) && ( b2 >= 0) && ahd(pl,i,q.y) )//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            }  
         }
        for( j = q.y;inzon(pl,n,q.x,j) != 0 ;j-- )
         { t2 = pl[m].strength - preqp(p.x,j,p.x,p.y);
           b2 = pl[plr].strength - preqb(q.x,j,q.x,q.y)- l; 
           if( intr(pl,q.x,j) && inzon(pl,n,q.x,j) && ( t2 >= 0) && ( b2 >= 0)  )
            { tmpe2 = 1;
              break;
            }
         }
        if( tmpe1 == 1 || tmpe2 == 1)
         { if( b2 > b1 )
            { if( tmpe2 == 1 )
               { str2 = b2;
                 flag = 2;
                 q.y = j;
               }
            }  
           else if(b1 == b2)
            { if( t2 > t1 && tmpe2 == 1)
               { str2= b2;
                 flag = 1;
                 q.y = j;
               }
              else if( tmpe1 == 1)
               { str2=b1;
                 flag = 1;
                 q.x  = i;
               } 
            }    
           else 
            { if( tmpe1 == 1 )
               { str2 = b1;
                 flag = 2;
                 q.x = i;
               }
            }
         }   
      }
    else if( d3 < 0 && d4 < 0 )
      { for( i = q.x;ahd(pl,i,q.y) != 0  ; i++ )
         { t1 = pl[m].strength - preqp(i,p.y,p.x,p.y);
           b1 = pl[plr].strength - preqb(i,q.y,q.x,q.y)- l; 
           if( intr(pl,i,q.y) && inzon(pl,n,i,q.y) && ( t1 >= 0) && ( b1 >= 0) && ahd(pl,i,q.y) )//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            }
         }
        for( j = p.y;inzon(pl,n,q.x,j) != 0 ;j++ )
         { t2 = pl[m].strength - preqp(p.x,j,p.x,p.y);
           b2 = pl[plr].strength - preqb(q.x,j,q.x,q.y)- l; 
           if( intr(pl,q.x,j) && inzon(pl,n,q.x,j) && ( t2 >= 0 ) && ( b2 >= 0 ) && ahd(pl,q.x,j) )
            { tmpe2 = 1;
              break;
            }
         }
        if( tmpe1 == 1 && tmpe2 == 1)   
         { if( b2 > b1 )
            { if( tmpe2 == 1)
               { str2 = b2;
                 flag = 2;
                 q.y = j;
               }
            }  
           else if(b1 == b2)
            { if( t2 > t1 && tmpe2 == 1)
               { str2= b2;
                 flag = 1;
                 q.y = j;
               }
              else if( tmpe1 == 1)
               { str2= b1;
                 flag = 1;
                 q.x = i;
               } 
            }    
           else if( i >= pl[plr].y )
            { if( tmpe1 == 1 )
               { str2 = b1;
                 flag = 2;
                 q.x = i;
               }
            }
         }   
   }    
     if( tmp1 == 1 || tmp2 == 1 )  
      strlft1 = t1;
     if( tmpe1 == 1 || tmpe2 == 1 )  
      strlft2 = t2;
     flag = 0;
     if( strlft1 > 0 || strlft2 < 0 )
      { if( strlft1 > strlft2 )
         { flag = 1;
           pl[m].x = p.x;
           pl[m].x = p.y;
         }
        else if( strlft2 > strlft1 )
         { flag = 2;
           pl[n].x  = q.x;
           pl[n].y  = q.y;
         }
       else
         { if( strlft1 <= strlft2 )
            { flag = 1;
              pl[m].x = p.x;
              pl[m].x = p.y;
            }
           else 
            { flag = 2;
              pl[n].x  = q.x;
              pl[n].y  = q.y;
            } 
         }
      }   
     return flag;
  } 
 //fnctn to brk marking such that my player remains in dee
 int atbrk( struct player pl[23],char ch1,struct goldee *cord1,char ch2,struct goldee *cord2, int h )
  { //declaration
    struct goldee p,q;
    int tmp1 = 0,tmp2 = 0,tmpe1 = 0,tmpe2 = 0,s1,str1,str2,d1,d2,d3,d4,i,j,s2;
    int flag = 0,m,n,l,plr;
    int strlft1 = 0,strlft2 = 0;
	char ch;
    l = oppow(pl);
	plr = blplyr;
    ch = plrmd[plr];
    p = *cord1;
    q = *cord2;
    d1 = p.x - pl[plr].x;
    d2 = p.y - pl[plr].y;
    d3 = q.x - pl[plr].x;
    d4 = q.y - pl[plr].y;
    m = srch(pl,cord1);//fnctn to assgn player no to players with the given coordinates
    n =srch(pl,cord2);
  if( ch1 == 'y' )//check only if it has succesfully made the run  
   {//for cord1 i.e. max power 
    if( d1 > 0 && d2 > 0 )
      { for( i = p.x;isde(i,p.y,pl) != 0; i-- )
         { if( intr(pl,i,p.y) && inzon(pl,m,i,p.y) && isde(i,p.y,pl) && ahd(pl,i,p.y) != 0 )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1;
              break;
            }  
         }
        for( j = p.y;isde(p.x,j,pl) != 0 ;j-- )
         { if( intr(pl,p.x,j) && inzon(pl,m,p.x,j) && isde(p.x,j,pl) )
            { tmp2 = 1;
              break;
            }  
         }
        if( tmp1 == 1 || tmp2 ==1 )   
         { s1 = preqb(i,p.y,pl[plr].x,pl[plr].y) ; 
           s2 = preqb(p.x,j,pl[plr].x,pl[plr].y) ;    
           if( s1 > s2 )
            { if( s2 <= 50 && tmp2 == 1)
               { str1= s2;
                 flag = 1;
                 p.y = j;
               }
            }  
           else if(s1 == s2)
            { if( s2 <= 50 && tmp2 == 1)
               { str1= s2;
                 flag = 1;
                 p.y = j;
               }
              else if( s1 <= 50 && tmp1 == 1)
               { str1= s1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if( s1 <= 50 && tmp1 == 1 )
               { str1= s1;
                 flag = 1;
                 p.x = i;
               }
            }
         }  
      }
    else if( d1 > 0 && d2 < 0 )
      { for( i = p.x;isde(i,p.y,pl) != 0  ; i-- )
         { if( intr(pl,i,p.y) && inzon(pl,m,i,q.y) && isde(i,p.y,pl)  )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1;
              break;
            }  
         }
        for( j = p.y;isde(p.x,j,pl) != 0  ;j++ )
         { if( intr(pl,p.x,j) && inzon(pl,plr,p.x,j) && isde(p.x,j,pl) )
            { tmp2 = 1;
              break;
            }  
         }
        if( tmp1 == 1 || tmp2 == 1)   
         { s1 = preqb(i,p.y,pl[plr].x,pl[plr].y); 
           s2 = preqb(p.x,j,pl[plr].x,pl[plr].y);    
           if( s1 > s2 )
            { if( s2 <= 50 && tmp2 == 1 )
               { str1= s2;
                 flag = 2;
                 p.y = j;
               }
            }  
           else if(s1 == s2)
            { if( s2 <= 50 && tmp2 == 1)
               { str1= s2;
                 flag = 1;
                 p.y = j;
               }
              else if( s1 <= 50 && tmp1 == 1)
               { str1= s1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if( s1 <= 50 && tmp1 == 1 )
               { str1= s1;
                 flag = 1;
                 p.x = i;
               }
            }
         }   
      }
    else if( d1 < 0 && d2 > 0 )
      { for( i = p.x;isde(i,p.y,pl) != 0  ; i++ )
         { if( intr(pl,i,p.y) && inzon(pl,m,i,p.y) && isde(i,p.y,pl) )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1; 
              break;
            }  
         }
        for( j = p.y;isde(p.x,j,pl) != 0  ;j-- )
         { if( intr(pl,p.x,j) && inzon(pl,m,p.x,j) && isde(p.x,j,pl) )
            { tmp2 = 1;
              break;
            }  
         }
        if( tmp1 == 1 || tmp2 == 1)   
         { s1 = preqb(i,p.y,pl[plr].x,pl[plr].y); 
           s2 = preqb(p.x,j,pl[plr].x,pl[plr].y);    
           if( s1 > s2 )
            { if( s2 <= 50 && tmp2 == 1 )
               { str1= s2;
                 flag = 1;
                 p.y = j;
               }
            }  
           else if(s1 == s2)
            { if( s2 <= 50 && tmp2 == 1)
               { str1= s2;
                 flag = 1;
                 p.y = j;
               }
              else if( s1 <= 50 && tmp1 == 1)
               { str1= s1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if( s1 <= 50 && tmp1 == 1 )
               { str1= s1;
                 flag = 1;
                 p.x = i;
               }
            }
         }   
      }
    else if( d1 < 0 && d2 < 0 )
      { for( i = p.x;!isde(i,p.y,pl); i++ )
         { if( intr(pl,i,p.y) && inzon(pl,m,i,p.y) && isde(i,p.y,pl) )//inzon checks that the given player is in its defmdined zone
            { tmp1 = 1;
              break;
            }  
         }
        for( j = p.y;isde(p.x,j,pl) != 0 ;j++ )
         { if( intr(pl,p.x,j) && inzon(pl,m,p.x,j) && isde(p.x,j,pl))
           { tmp2 = 1;
             break;
           }  
         }
        if( tmp1 == 1 || tmp2 == 1 )   
         { s1 = preqb(i,p.y,pl[plr].x,pl[plr].y); 
           s2 = preqb(p.x,j,pl[plr].x,pl[plr].y);    
           if( s1 > s2 )
            { if( s2 <= 50 && tmp2 == 1 )
               { str1= s2;
                 flag = 1;
                 p.y = j;
               }
            }  
           else if(s1 == s2)
            { if( s2 <= 50 && tmp2 == 1)
               { str1= s2;
                 flag = 1;
                 p.y = j;
               }
              else if( s1 <= 50 && tmp1 == 1)
               { str1= s1;
                 flag = 1;
                 p.x = i;
               } 
            }  
           else 
            { if( s1 <= 50 && tmp1 == 1)
               { str1= s1;
                 flag = 1;
                 p.x = i;
               }
            }
         }   
      }
  }                                
     //for cord2 i.e. 2ndmax power 
  if( ch2 == 'y' )
   { if( d3 > 0 && d4 > 0 )
      { for( i = q.x;isde(i,q.y,pl) != 0  ; i-- )
         { if( intr(pl,i,q.y) && inzon(pl,n,i,q.y) && isde(i,q.y,pl) )//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            }  
         }
        for( j = q.y;isde(q.x,j,pl) != 0  ;j-- )
         { if( intr(pl,q.x,j) && inzon(pl,n,q.x,j) && isde(q.x,j,pl) )
            { tmpe2 = 1;
              break;
            }  
         }
        if( tmpe1 == 1 || tmpe2 == 1 )   
         { s1 = preqb(i,q.y,pl[plr].x,pl[plr].y); 
           s2 = preqb(q.x,j,pl[plr].x,pl[plr].y);    
           if( s1 > s2 )
            { if( s2 <= 50 &&  tmpe2 == 1)
               { str2 = s2;
                 flag = 2;
                 q.y = j;
               }
            }  
          else if(s1 == s2)
            { if( s2 <= 50 && tmpe2 == 1)
               { str2= s2;
                 flag = 1;
                 q.y = j;
               }
              else if( s1 <= 50 && tmpe1 == 1)
               { str2= s1;
                 flag = 1;
                 q.x = i;
               } 
            }    
           else 
            { if( s1 <= 50 && tmpe1 == 1 )
               { str2 = s1;
                 flag = 2;
                 q.x = i;
               }
            }
         }  
      }
    else if( d3 > 0 && d4 < 0 )
      { 
		for( i = q.x;isde(i,q.y,pl) != 0; i-- )
         { if( intr(pl,i,q.y) && inzon(pl,n,i,q.y) && isde(i,q.y,pl) )//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            } 
         }
        for( j = q.y;isde(i,q.y,pl) != 0; j++ )
         { if( intr(pl,q.x,j) && inzon(pl,n,q.x,j) && isde(q.x,j,pl))
            { tmpe2 = 1;
              break;
            }  
         }
        if( tmpe1 == 1 || tmpe2 == 1 )   
         { s1 = preqb(i,q.y,pl[plr].x,pl[plr].y); 
           s2 = preqb(q.x,j,pl[plr].x,pl[plr].y);    
           if( s1 > s2 )
            { if( s2 <= 50 && tmpe2 == 1)
               { str2 = s2;
                 flag = 2;
                 q.y = j;
               }
            }  
           else if(s1 == s2)
            { if( s2 <= 50 && tmpe2 == 1)
               { str2= s2;
                 flag = 1;
                 q.y = j;
               }
              else if( s1 <= 50 && tmpe1 == 1)
               { str2= s1;
                 flag = 1;
                 q.x = i;
               } 
            }    
           else
            { if( s1 <= 50 && tmpe1 == 1 )
               { str2 = s1;
                 flag = 2;
                 q.x = i;
               }
            }
         }   
      }
    else if( d3 < 0 && d4 > 0 )
      { for( i = q.x;isde(i,q.y,pl) != 0; i++ )
         { if( intr(pl,i,q.y) && inzon(pl,n,i,q.y) && isde(i,q.y,pl))//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            }  
         }
        for( j = q.y;isde(q.x,j,pl) != 0   ;j-- )
         { if( intr(pl,q.x,j) && inzon(pl,n,q.x,j) && isde(q.x,j,pl))
            { tmpe2 = 1;
              break;
            }
         }
        if( tmpe1 == 1 || tmpe2 == 1)
         { s1 = preqb(i,q.y,pl[plr].x,pl[plr].y); 
           s2 = preqb(q.x,j,pl[plr].x,pl[plr].y);    
           if( s1 > s2 )
            { if( s2 <= 50 && tmpe2 == 1 )
               { str2 = s2;
                 flag = 2;
                 q.y = j;
               }
            }  
           else if(s1 == s2)
            { if( s2 <= 50 && tmpe2 == 1)
               { str2= s2;
                 flag = 1;
                 q.y = j; 
               }
              else if( s1 <= 50 && tmpe1 == 1)
               { str2= s1;
                 flag = 1;
                 q.x = i;
               } 
            }    
           else 
            { if( s1 <= 50 && tmpe1 == 1 )
               { str2 = s1;
                 flag = 2;
                 q.x = i;
               }
            }
         }   
      }
    else if( d3 < 0 && d4 < 0 )
      { i = q.x,j = q.y;
		for( i = q.x;isde(i,q.y,pl) != 0   ; i++ )
         { if( intr(pl,i,q.y) && inzon(pl,n,i,q.y) && isde(i,q.y,pl))//inzon checks that the given player is in its defmdined zone
            { tmpe1 = 1;
              break;
            }
         }
        for( j = q.y;isde(q.x,j,pl) != 0   ;j++ )
         { if( intr(pl,q.x,j) && inzon(pl,n,q.x,j) && isde(q.x,j,pl))
            { tmpe2 = 1;
              break;
            }
         }
        if( tmpe1 == 1 && tmpe2 == 1)   
         { s1 = preqb(i,q.y,pl[plr].x,pl[plr].y); 
           s2 = preqb(q.x,j,pl[plr].x,pl[plr].y);    
           if( s1 > s2 )
            { if( s2 <= 50 && tmpe2 == 1)
               { str2 = s2;
                 flag = 2;
                 q.x = i;
                 q.y = j;
               }
            }  
           else if(s1 == s2)
            { if( s2 <= 50 && tmpe2 == 1)
               { str2= s2;
                 flag = 1;
                 q.x = i;
                 q.y = j;
               }
              else if( s1 <= 50 && tmpe1 == 1)
               { str2= s1;
                 flag = 1;
                 q.x = i;
                 q.y = j;
               } 
            }    
           else 
            { if( s1 <= 50 && tmpe1 == 1 )
               { str2 = s1;
                 flag = 2;
                 q.x = i;
                 q.y = j;
               }
            }
         }   
      }
   }    
     if( tmp1 == 1 || tmp2 == 1 )  
      strlft1 = pl[m].strength - s1 - l;
     if( tmpe1 == 1 || tmpe2 == 1 )  
      strlft2 = pl[n].strength - s2 - l;
     flag = 0;
     if( strlft1 > 0 || strlft2 < 0 )
      { if( strlft1 > strlft2 )
         { flag = 1;
           pl[m].x = p.x;
           pl[m].x = p.y;
         }
        else if( strlft2 > strlft1 )
         { flag = 2;
           pl[n].x  = q.x;
           pl[n].y  = q.y;
         }
       else
         { if( s1 <= s2 )
            { flag = 1;
              pl[m].x = p.x;
              pl[m].x = p.y;
            }
           else 
            { flag = 2;
              pl[n].x  = q.x;
              pl[n].y  = q.y;
            } 
         }
      }   
     return flag;
  }
  //fnctn to find the player with the given no.
  int srch(struct player p[23],struct goldee *cord)
   { //declaration
     int i,num = 0;
     for( i = pl; i <= ph; i++ )
	  { if( p[i].x == cord->x && p[i].y == cord->y )
	     { num = i;
	       break;
	     }
	  }

   return num;
  }

  //fnctn to find if any player is in the opnt dee
  int searchdee( struct player p[23], struct goldee *cord )
   { //declaration
     int i,j,t,flag = 0;
     for( t = ph; t >= pl ; t--)
      { for( i = 39;i >= 0 ; i-- )
         { for( j = 0; j < 41; j++ )
            { if( p[t].x == opdee[i][j].x && p[t].y == opdee[i][j].y )
               { flag = 1;
                 break;
               }             
            }
            if( flag == 1)
             break;
         }
        if ( flag == 1 )
         break; 
      } 
      if( flag == 1 )
       { cord->x = opdee[i][j].x;
         cord->y = opdee[i][j].y;
       } 
      return flag;
   }
  //fnctn to search if a given player is present inside the dee
  int srchd( int m,struct player p[23] )                       
   { //declaration
     int i,j,flag = 0;
     for( i = 39; i >= 0; i++ )
      { for( j = 0; j < 41; j++ )
         { if( p[m].x == opdee[i][j].x && p[m].y == opdee[i][j].y )
            { flag = 1;
              break;
            }
         }
         if( flag == 1)
          break;
      }
     return flag;
   }
  //fnctn to find if a given player is present inside the oppnt dee with diff argument than previous fnctn      
  int isde( int x, int y, struct player p[23] )
   { //declaration
     int i,j,flag = 0;
     for( i = 39; i >= 0; i++ )
      { for( j = 0; j < 41; j++ )
         { if( x == opdee[i][j].x && y == opdee[i][j].y )
            { flag = 1;
              break;
            }
         }
        if( flag == 1)
          break;
      }
     return flag;
   }
 //fnctn to check if the player is in his defmdined zone
 int inzon(struct player p[23],int m,int x, int y)
  { //dclaration
    int flag = 0,i,j;
    switch(m)  
     { case 1:
          for( i = 65; i <= 99; i++ )
           { for( j = 25; j <=36; j++ )
              { if( x == myfield[i][j].x  )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		      }
           }
          break;
       case 2:
          for( i = 65; i <= 99; i++ )
           { for( j = 1; j <=24; j++ )
              { if( x == myfield[i][j].x )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		      }
           }
          break;
        case 3:
          for( i = 65; i <= 99; i++ )
           { for( j = 13; j <=24; j++ )
              { if( x == myfield[i][j].x )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		     }
           }
          break;  
        case 4:
          for( i = 65; i <= 99; i++ )
           { for( j = 37; j <= 49; j++ )
              { if( x == myfield[i][j].x )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		     }
           }
          break;  
        case 5:
          for( i = 50; i <= 64; i++  )
           { for( j = 1; j <= 16; j++ )
              { if( x == myfield[i][j].x && y == myfield[i][j].y )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		     }
           }
          break;  
        case 6:
          for( i = 55; i <= 64; i++  )
           { for( j = 17; j <= 32; j++ )
              { if( x == myfield[i][j].x && y == myfield[i][j].y )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		      }
           }
          break;  
        case 7:
          for( i = 50; i <= 64; i++  )
           { for( j = 18; j <= 49; j++ )
              { if( x == myfield[i][j].x && y == myfield[i][j].y )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		      }
           }
          break;
        case 8:
          for( i = 33; i <= 50; i++  )
           { for( j = 1; j <= 16; j++ )
              { if( x == myfield[i][j].x && y == myfield[i][j].y )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		     }
           }
          break;       
        case 9:
          for( i = 40; i <= 55; i++  )
           { for( j = 17; j <= 32; j++ )
              { if( x == myfield[i][j].x && y == myfield[i][j].y )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		      }
           }
          break;
         case 10:
          for( i = 33; i <= 50; i++  )
           { for( j = 33; j <= 48; j++ )
              { if( x == myfield[i][j].x && y == myfield[i][j].y )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		      }
           }
          break;
         case 11:
          for( i = 33; i <= 50; i++  )
           { for( j= 5; j <= 45; j++ )
              { if( x == myfield[i][j].x && y == myfield[i][j].y )
                 { flag = 1;
                   break;
                 }
                if(flag == 1)
                 break;
		     }
           }
          break;         
    }
   return flag;
  }   
 //fnctn to check if an oppnt player has entered my dee
 int indee(struct player p[23], int op[11])//op contains the no of players in my dee
  { //declaration
    int t,i,j,n = 0,l = 0;
    for( t = pho; i >= plo; t-- )
     { for( i = 39; i>= 0; i++ )
        { for( j = 0; j>= 0; j ++ )
           { if( p[t].x == opdee[i][j].x && p[t].y == opdee[i][j].y && marko[t] == 0  )
		      { n++;
                op[l] = i;
                l++;
                break;
              }
             if( n != 0 )
              break;
           }
        }
     }
     return n;
  } 
  //fnctn to check if an oppnt player is in my dee
  int indop(struct player p[23],int m)
   { //declaration
     int i,j,flag = 0;
     for( i = 0; i <= 39 && flag == 0; i++ )
      { for( j = 0; j <= 40; j++ )
         { if(p[m].x == mydee[i][j].x )
            { flag = 1;
              break;
            }
         }
      }
     return flag;
   } 
                      
 //fnctn to mark and to be at proper positions
 void markf(struct player p[23],int k)//k is the no. of moves by me
  { //declaration
    int i,max = 0,a = -1,num = 0,t,v = 0,s,z,j,x,y,min=50;
    int op[11];
    t = indee(p,op);
    if( k == 1 )
     { if( pl != blplyr )
        { p[pl].x = myfield[70][30].x;
          p[pl].y = myfield[70][30].y;
        }
       if( (pl+1) != blplyr )  
        { p[pl+1].x = myfield[70][12].x;
          p[pl+1].y = myfield[70][12].y;
        }
       if( (pl+2) != blplyr )  
        { p[pl+2].x = myfield[70][20].x;
          p[pl+2].y = myfield[70][20].y;
        }
       if( (pl+3) != blplyr )   
        { p[pl+3].x = myfield[70][42].x;
          p[pl+3].y = myfield[70][42].y;
        }
       if( (pl+4) != blplyr )  
        { p[pl+4].x = myfield[55][10].x;
          p[pl+4].y = myfield[55][10].y;
        } 
       if( (pl+5) != blplyr )  
        { p[pl+5].x = myfield[60][25].x;
          p[pl+5].y = myfield[60][25].y;
        }
       if( (pl+6) != blplyr )  
        { p[pl+6].x = myfield[55][30].x;
          p[pl+6].y = myfield[55][30].y;
        }  
       if( (pl+7) != blplyr )  
        { p[pl+7].x = myfield[45][13].x;
          p[pl+7].y = myfield[45][13].y;
        } 
       if( (pl+8) != blplyr )  
        { p[pl+8].x = myfield[48][25].x;
          p[pl+8].y = myfield[48][25].y;
        } 
       if( (pl+9) != blplyr )  
        { p[pl+9].x = myfield[45][37].x;
          p[pl+9].y = myfield[45][37].y;
        }  
       if( (pl+10) != blplyr )  
        { p[pl+10].x = myfield[36][70].x;
          p[pl+10].y = myfield[36][70].y;
        }
     } 
    if( t != 0 )
     { while( v < t )
       { for( i = pl; i <= pl + 3; i++ )
          { s = p[pl].strength - preqp(p[0].x,p[0].y,p[i].x,p[i].y);
            if( s >= 0 && mark[i] == 0 && i != blplyr )
             { if( s >= max )
                { max = s;
                  num = i;  
                }
             }
          } 
         if( num != 0 )
          { p[num].x = p[0].x;
            p[num].y = p[0].y;
            mark[num] = op[v];
            v++;
          }
         else if( num == 0 )
          { for( i = pl+4; i <= pl + 6; i++ )
             { s = p[pl].strength - preqp(p[0].x,p[0].y,p[i].x,p[i].y);
                if( s >= 0 && mark[i] == 0 && i != blplyr )
                 { if( s >= max )
                    { max = s;
                      num = i;  
                    }
                 }
		 } }
            if( num != 0 )
             { p[num].x = p[0].x;
               p[num].y = p[0].y;
               mark[num] = op[v];
               v++;
             }
          }
        
     if( defmd(p) )
      { for( i = pl +4; i <= pl+6; i++ )
         { if(p[pl].strength >= 20 && i != blplyr )
            { if( team == 1)
               { if( inzon(p,pl,p[pl].x-5,p[pl].y ))
                  p[pl].x = p[pl].x - 5;
               }
              else
               { if( inzon(p,pl,p[pl].x+5,p[pl].y ))  
                  p[pl].x = p[pl].x - 5;
               } 
            }
         }
      }
     //marking their forwards
     for( i = pl; i <= ph; i++ )
      { if( mark[i] != 0 )
         { num = mark[i];
           if( inzon(p,i,p[num].x,p[num].y) || indop(p,num) )
            { p[i].x = p[num].x;
              p[i].y = p[num].y;
            }
         }
      }
     
     //to return players back to their zones;
     for( z = pl; i <= ph; z++ )
      { if( inzon(p,z,p[z].x,p[z].y) == 0 && mark[z] == 0 )
         { for( i = 1; i <= 99; i++ )
            { for( j = 1; j <= 49; j++ )
               { if( inzon(p,z,myfield[i][j].x,myfield[i][j].y) )
                  { s = preqp(myfield[i][j].x,myfield[i][j].y,p[z].x,p[z].y);
                    if(s <= min)
                     { x = myfield[i][j].x;
                       y = myfield[i][j].y;
                       min = s;
                     }
                  }
               }
            }
            p[z].x = x;
            p[z].y = y;
         }
      }  
             
	} } 
};//end of class

