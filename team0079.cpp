#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<iostream>
#include<map>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<sstream>
#include<cctype>
#include<cmath>

#define pb push_back
#define np next_permutation
#define all(x) x.begin(),x.end()
#define bitcount __builtin_popcount

#define vi vector<int>
#define vs vector<string>
#define ss stringstream


//#include"test_player.cpp"
//#include"soccer.cpp"  //sample_player.cpp is included just as an example. when you have made your code and you want to compete it with
                             //our test_player.cpp, then instead of include"sample_player.cpp" , include your file in which you have made your
                             //class and run the simulator.cpp file
using namespace std;

class team0079  // Soccer Maniacs
{
  private:      //private fns and variables defined
  int teamnum,oppgxmin,oppgxmax,oppgymin,oppgymax;
  int olow,ohigh,low,high;
  int playerind[11];    // playerind[i] stores the index of the player[i] (with low added)
  int preposx[11];     // predefined positions x means row no,y means col no
  int preposy[11];
  int dmaxx,dminx;  
  int lastmoved;
   int scorer;
   struct player ref[23];   // just a copy of the current array of structures
    
   int preqp(int finalx,int finaly, int initialx ,int initialy )  //function which tells the strength req by player to move from 
	{float req;                                                    //place to another
    req=(float)floor(sqrt(pow(double(finalx-initialx),2.0)+pow(double(finaly-initialy),2.0)));
    return (int)req;}     

  int preqpb(int finalx,int finaly, int initialx ,int initialy )   //function which tells the strength req by hitter of ball to hit
	{float req; int i;                                            //the ball from one place to another
    req=(float)2*(floor(sqrt(pow(double(finalx-initialx),2.0)+pow(double(finaly-initialy),2.0))));
	 i=(int)req;
	 return i;} 
  
/*  int reflect(int pos,char c)
{
    
    if(tnum==2)
    {  if(c=='y')
       return 50-pos;
       
       return 100-pos;  }
       
       return pos;  }  */

// intercept takes the index of the hitting player,so tht we can use intercept for both the teams

vi maxstr(vi indexes)
{
    int i,j;
  for(i=0;i<indexes.size();i++)
   for(j=i+1;j<indexes.size();j++)
   if(ref[playerind[indexes[i]]].strength<ref[playerind[indexes[j]]].strength)
   swap(indexes[i],indexes[j]);  
   
   return indexes; }

int intercept(int ind,int fx,int fy,int ix,int iy)
{  
  int i,mi,ma;   
  int curx=ix,cury=iy;
  int xdiff=fx-curx;
  int ydiff=fy-cury;

  if(ind<12)
  {mi=12;
  ma=22;  }
  else
  {mi=1;
  ma=11;  }
  
  int destpl=-1;
  
  for(i=low;i<=high;i++)
  if(ref[i].x==fx&&ref[i].y==fy)
   {  destpl=i;
      break;  }
  
  
  
  while(curx!=fx || cury!=fy)
		{  if(curx!=fx)
            (xdiff>0)?(curx)++:(curx)--;
          if(cury!=fy)
            (ydiff>0)?(cury)++:(cury)--;
        
         for(i=mi;i<=ma;i++)
            if((curx==ref[i].x)&&(cury==ref[i].y))
            { if(curx==fx&&cury==fy)
              if(destpl!=-1)
              if(ref[destpl].strength<ref[i].strength)
              return 1;  } 
              }      //loop to check whether any of the player intersect the ball
return 0;      }  
     
       
 vi canscore(int pl)  // return the position if goal can be scored
 {
   int i,j,mi=100000;
   vi ret;
   ret.pb(-1);
   ret.pb(-1);
   int xx=ref[playerind[pl]].x;
   int yy=ref[playerind[pl]].y;
   int str=ref[playerind[pl]].strength;
      
   for(i=oppgxmin;i<=oppgxmax;i++)
   for(j=oppgymin;j<=oppgymax;j++)
   if(preqpb(i,j,xx,yy)<=str&&!intercept(playerind[pl],i,j,xx,yy))
   if(preqpb(i,j,xx,yy)<mi)
   {   mi=preqpb(i,j,xx,yy);
       ret[0]=i;
       ret[1]=j;  }
   
   return ret;  }            
                
int canpass(int pl,int fx,int fy,int ix,int iy)
 {
   int str=ref[playerind[pl]].strength;
    
   if((str-preqpb(fx,fy,ix,iy)>=0)&&(!intercept(playerind[pl],fx,fy,ix,iy)))
         return 1;  
   
   return 0;  }              
   
   int max(int a, int b)
   {
       if(a>b) return a;
       return b;
   }
//public functions
  public:         
    int init(int team_number, struct player *p,char farray[][51]) //the mandatory function which initialises the team no. of the 
	{       
        int i;    
        lastmoved=0;
    
    	if(team_number==1)
        {   teamnum=1;
            low=1;
            high=11;
            olow=12;ohigh=22;
            oppgymin=10;
            oppgymax=40;
            oppgxmin=86;
            oppgxmax=99;
            int arrx[]={49,61,45,61,50,35,50,25,25,25,15};
            int arry[]={25,11,24,39,11,24,39,10,25,40,25};
            
            // initialize the predef positions
            for(i=0;i<11;i++)
            {  preposx[i]=arrx[i];
               preposy[i]=arry[i];   }
            dmaxx=49;
            
            // set prepositions
            }
            else
            {  teamnum=2;
                low=12;// tnum=2;
            high=22;
            olow=1;ohigh=11;
            oppgymin=10;
            oppgymax=40;
            oppgxmin=1;
            oppgxmax=14;
            int arrx[]={51,39,55,39,50,65,50,75,75,75,85};
            int arry[]={25,11,24,39,11,24,39,10,25,40,25};
            
            // initialize the predef positions
            for(i=0;i<11;i++)
            {  preposx[i]=arrx[i];
               preposy[i]=arry[i];   }
            dminx=51;
            // set prepositions
            } 
        
        for(i=0;i<23;i++)
        {
         ref[i].x=p[i].x;
         ref[i].y=p[i].y;
         ref[i].strength=p[i].strength; 
         }      
            
        // map indexes of players to player nos.    
        
        /*   player nos
    
                  10
             7    8    9
             4    5    6
             1    2    3
                  0         
                  
            
                team 2
                  0
             1    2    3
             4    5    6
             7    8    9
                  10              
             
         */
         for(i=low;i<=high;i++)
         { 
            if(teamnum==1) 
          { if(ref[i].y==25&&ref[i].x==15)  // this is the goalkeeper
            playerind[10]=i;   
            
            else if(ref[i].y==10&&ref[i].x==25) 
            playerind[7]=i;  
            
            else if(ref[i].y==10&&ref[i].x==30) 
            playerind[4]=i;  
            
            else if(ref[i].y==10&&ref[i].x==40) 
            playerind[1]=i;  
            
            else if(ref[i].y==25&&ref[i].x==25) 
            playerind[8]=i;  
            
            else if(ref[i].y==25&&ref[i].x==30) 
            playerind[5]=i;  
            
            else if(ref[i].y==25&&ref[i].x==40) 
            playerind[2]=i;  
            
            else if(ref[i].y==40&&ref[i].x==25) 
            playerind[9]=i;  
            
            else if(ref[i].y==40&&ref[i].x==30) 
            playerind[6]=i;  
            
            else if(ref[i].y==40&&ref[i].x==40) 
            playerind[3]=i;  
            
            else if(ref[i].y==25&&ref[i].x==49) 
            playerind[0]=i;  }
            
            else
            { if(ref[i].y==25&&ref[i].x==85)  // this is the goalkeeper
            playerind[10]=i;   
            
            else if(ref[i].y==10&&ref[i].x==75) 
            playerind[7]=i;  
            
            else if(ref[i].y==10&&ref[i].x==70) 
            playerind[4]=i;  
            
            else if(ref[i].y==10&&ref[i].x==60) 
            playerind[1]=i;  
            
            else if(ref[i].y==25&&ref[i].x==75) 
            playerind[8]=i;  
            
            else if(ref[i].y==25&&ref[i].x==70) 
            playerind[5]=i;  
            
            else if(ref[i].y==25&&ref[i].x==60) 
            playerind[2]=i;  
            
            else if(ref[i].y==40&&ref[i].x==75) 
            playerind[9]=i;  
            
            else if(ref[i].y==40&&ref[i].x==70) 
            playerind[6]=i;  
            
            else if(ref[i].y==40&&ref[i].x==60) 
            playerind[3]=i;  
            
            else if(ref[i].y==25&&ref[i].x==51) 
            playerind[0]=i;} }
            
            
            
               
             }  // end init
             
    
int omaxstr(int pl)
{
     int i;
     for(i=olow;i<=ohigh;i++)
     if(ref[i].strength-preqp(ref[playerind[pl]].x,ref[playerind[pl]].y,ref[i].x,ref[i].y)>ref[playerind[pl]].strength)
      return 1;
      return 0;  }

     int player(struct player *p)        //main player func 
{
        int i,hitter=-1,j,ind=-1,bestp,ma,passed;
		vi ret,indexes,n;
        for(i=0;i<23;i++)
        {
         ref[i].x=p[i].x;
         ref[i].y=p[i].y;
         ref[i].strength=p[i].strength; 
         }       
         
	if(ref[0].x==50)
	{  
             for(j=1;j<11;j++)
            {  
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }
	// Goal scored against condition??
/*	if(1) //(ref[playerind[7]].y!=preposy[7]||ref[playerind[9]].y!=preposy[9]||ref[playerind[7]].x!=preposx[7]||ref[playerind[9]].x!=preposx[9])
	{  
		
	for(i=25;i<=50;i++)
	{   bool ppresent=false;
	for(int j=low;j<=high;j++)
	{ if(ref[j].y==i&&ref[j].x==50)
        {  ppresent=true;
		 break; }
	  if(!ppresent)
	{   ref[playerind[0]].y=i;
          ref[playerind[0]].x=50;}
		}}
	}  */
    }  

	possession:

        bool possess=false;
        int pl=-1,str,rec=-1,k;
            
        // loop determines whether a team player has the ball    
       for(i=low;i<=high;i++)
       if(ref[i].x==ref[0].x&&ref[i].y==ref[0].y&&ref[i].strength!=0)
       { possess=true;
		ind=i;

       for(j=olow;j<=ohigh;j++)
       if(ref[j].x==ref[0].x&&ref[j].y==ref[0].y&&ref[j].strength>ref[i].strength)
       {  possess=false;
          ref[i].y++;  }
         }     
       
       if(possess)
      { for(i=0;i<11;i++)
       if(playerind[i]==ind)
       break;   
       cout<<"posession="<<ind;}
       
       int next=-1;
  check_states:      
      if(possess) 
      {      
      switch(i)     // switch the player no
      {
        // the goalkeeper has the ball
       case 10:	  //next=7;
                  indexes.clear();
                  indexes.pb(7);
                  indexes.pb(8);
                  indexes.pb(9);
                  passed=0;
                 n=maxstr(indexes);
            
            
            for(j=0;j<n.size();j++)
            {     next=n[j];
            	if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y))	
			  {   ref[0].x=ref[playerind[next]].x;
                  ref[0].y=ref[playerind[next]].y; 
                  hitter=playerind[10]; passed=1;
                  ref[playerind[10]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y); 
                  break; }
                  }
                  
                 for(j=1;j<11;j++)
            {  if(j==i||j==next)
                 continue;
                  ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);
                 ref[playerind[j]].x=preposx[j];
                ref[playerind[j]].y= preposy[j];
                 }
                 
                 if(!passed)
                 if(omaxstr(10))
                 {  ref[playerind[10]].strength--;
                 ref[playerind[10]].x++;  }                   
                
		
		   break;   
       
       // one of the 3 defenders has the ball
       case 7:   
            passed=0;
            if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[2]].x,ref[playerind[2]].y))
			{
                    passed=1;
			      ref[0].x=ref[playerind[2]].x;
                  ref[0].y=ref[playerind[2]].y; 
                  hitter=playerind[7]; 
                  rec=2;
                  ref[playerind[7]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[2]].x,ref[playerind[2]].y); 
                  
			}
            
           else if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[5]].x,ref[playerind[5]].y))
			{passed=1;
			      ref[0].x=ref[playerind[5]].x;
                  ref[0].y=ref[playerind[5]].y; 
                  hitter=playerind[7];
                  rec=5; 
                  ref[playerind[7]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[5]].x,ref[playerind[5]].y); 
                  
			}
			else
			{
			//choose players 8,9 or 10 for best strength and max returns best player
			indexes.clear();
                  indexes.pb(10);
                  indexes.pb(8);
                  indexes.pb(9);		
		n=maxstr(indexes);
            
            
            for(j=0;j<n.size();j++)
            {     next=n[j];
            	if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y))	
			  {   ref[0].x=ref[playerind[next]].x;
                  ref[0].y=ref[playerind[next]].y; 
                  hitter=playerind[7]; passed=1; rec=next;
                  ref[playerind[7]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y); 
                  break; }
                  }
			}
			
			for(j=1;j<11;j++)
            {  if(j==i||j==rec)
                 continue;
                     ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }
               
               if(!passed)
               if(omaxstr(7))
                 {  ref[playerind[7]].strength--;
                 ref[playerind[7]].x++;  }               

			break;
       
       case 8:   passed=0;
            if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[2]].x,ref[playerind[2]].y))
			{passed=1;
			      ref[0].x=ref[playerind[2]].x;
                  ref[0].y=ref[playerind[2]].y; 
                  hitter=playerind[8]; 
                  rec=2;
                  ref[playerind[8]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[2]].x,ref[playerind[2]].y); 
                  
			}
            
           else if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[5]].x,ref[playerind[5]].y))
			{passed=1;
			      ref[0].x=ref[playerind[5]].x;
                  ref[0].y=ref[playerind[5]].y; 
                  hitter=playerind[8];
                  rec=5; 
                  ref[playerind[8]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[5]].x,ref[playerind[5]].y); 
                  
			}
			else
			{
			//choose players 7,9 or 10 for best strength and max returns best player
			indexes.clear();
                  indexes.pb(7);
                  indexes.pb(10);
                  indexes.pb(9);					
		n=maxstr(indexes);
            
            
            for(j=0;j<n.size();j++)
            {     next=n[j];
            	if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y))	
			  {   ref[0].x=ref[playerind[next]].x;
                  ref[0].y=ref[playerind[next]].y; 
                  hitter=playerind[8]; passed=1; rec=next;
                  ref[playerind[8]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y); 
                  break; }
                  }
			
			}
			
			for(j=1;j<11;j++)
            {  if(j==i||j==rec)
                 continue;
                   ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }
               
               if(!passed)
                if(omaxstr(8))
                 {  ref[playerind[8]].strength--;
                 ref[playerind[8]].x++;  }
                     
			break;
       
       case 9:   passed=0;
            if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[2]].x,ref[playerind[2]].y))
			{passed=1;
			      ref[0].x=ref[playerind[2]].x;
                  ref[0].y=ref[playerind[2]].y; 
                  hitter=playerind[9]; 
                  rec=2;
                  ref[playerind[9]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[2]].x,ref[playerind[2]].y); 
                  
			}
            
           if(rec==-1 || canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[5]].x,ref[playerind[5]].y))
			{passed=1;
			      ref[0].x=ref[playerind[5]].x;
                  ref[0].y=ref[playerind[5]].y; 
                  hitter=playerind[9];
                  rec=5; 
                  ref[playerind[9]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[5]].x,ref[playerind[5]].y); 
                  
			}
			else
			{
			//choose players 8,7 or 10 for best strength and max returns best player
			//int next=7;
			indexes.clear();
                  indexes.pb(7);
                  indexes.pb(8);
                  indexes.pb(10);
            //     next=maxstr(indexes);
			
				n=maxstr(indexes);
            
            
            for(j=0;j<n.size();j++)
            {     next=n[j];
            	if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y))	
			  {   ref[0].x=ref[playerind[next]].x;
                  ref[0].y=ref[playerind[next]].y; 
                  hitter=playerind[9]; passed=1; rec=next;
                  ref[playerind[9]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y); 
                  break; }
                  }
			}
			
			for(j=1;j<11;j++)
            {  if(j==i||j==rec)
                 continue;
                      ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }
               
               if(!passed)
               if(omaxstr(9))
                 {  ref[playerind[9]].strength--;
                 ref[playerind[9]].x++;  }
			break;

       //  the static midfielder has the ball
       case 5: passed=0; 
            if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[2]].x,ref[playerind[2]].y))
			{passed=1;
			ref[0].x=ref[playerind[2]].x;
                  ref[0].y=ref[playerind[2]].y; 
                  hitter=playerind[5];
                  rec=2; 
                 ref[playerind[5]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[2]].x,ref[playerind[2]].y); 
                  
			}
		if(rec==-1)
        {	
			indexes.clear();
                  indexes.pb(7);
                  indexes.pb(8);
                  indexes.pb(9);
               //  next=maxstr(indexes);
            	n=maxstr(indexes);
            
            
            for(j=0;j<n.size();j++)
            {     next=n[j];
            	if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y))	
			  {   ref[0].x=ref[playerind[next]].x;
                  ref[0].y=ref[playerind[next]].y; 
                  hitter=playerind[5]; passed=1; rec=next;
                  ref[playerind[5]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y); 
                  break; }
                  }
            
            }      
                 for(j=1;j<11;j++)
            {  if(j==i||j==rec)
                 continue;
                  ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }
                   
                   if(!passed)
                    if(omaxstr(5))
                 {  ref[playerind[5]].strength--;
                 ref[playerind[5]].x++;  }               
			break;
       
       //  the static attacker has the ball
       case 2:              
            passed=0;
            if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[0]].x,ref[playerind[0]].y))
			{passed=1;
			ref[0].x=ref[playerind[0]].x;
                  ref[0].y=ref[playerind[0]].y; 
                  hitter=playerind[2];
                  rec=0; 
               ref[playerind[2]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[0]].x,ref[playerind[0]].y); 
           
			}
			
             if(rec==-1)
                  {		
                      indexes.clear();
                  indexes.pb(4);
                  indexes.pb(6);
                  //indexes.pb(9);
                // next=maxstr(indexes);
			
					n=maxstr(indexes);
            
            
            for(j=0;j<n.size();j++)
            {     next=n[j];
            	if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y))	
			  {   ref[0].x=ref[playerind[next]].x;
                  ref[0].y=ref[playerind[next]].y; 
                  hitter=playerind[2]; passed=1; rec=next;
                  ref[playerind[2]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y); 
                  break; }
                  }
			
        }
			for(j=1;j<11;j++)
            {  if(j==i||j==rec)
                 continue;
                   ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }               
             
               if(!passed)
                if(omaxstr(2))
                 {  ref[playerind[2]].strength--;
                 ref[playerind[2]].x++;  }
                 
                
			 break;
       
       //  one of the two moving midfielders has the ball
       case 4:         
             passed=0;
            if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[0]].x,ref[playerind[0]].y))  // pass it to player0
             {   
                    ret=canscore(0);                
                     if(ret[0]!=-1)
                       {   ref[0].x=ref[playerind[0]].x;passed=1;
                           ref[0].y=ref[playerind[0]].y; 
                           hitter=playerind[4];
                           rec=0;
                           ref[playerind[4]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[0]].x,ref[playerind[0]].y); 
                       }            
                } 
                                
            if(rec==-1 ||canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[1]].x,ref[playerind[1]].y))  // pass it to player1
               {                
                   ref[0].x=ref[playerind[1]].x;passed=1;
                    ref[0].y=ref[playerind[1]].y; 
               hitter=playerind[4];
               rec=1;
             ref[playerind[4]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[1]].x,ref[playerind[1]].y); 
          
                }
              //  cout<<canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[1]].x,ref[playerind[1]].y);       
             for(j=1;j<11;j++)
            {  if(j==i||j==rec)
                 continue;
                  ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }
                
                if(!passed)
                if(omaxstr(4))
                 {  ref[playerind[4]].strength--;
                 ref[playerind[4]].x++;  }
                
                
                 break;
      
      case 6:  passed=0;
               if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[0]].x,ref[playerind[0]].y))  // pass it to player0
               {  
                ret=canscore(0);
                if(ret[0]!=-1)
               {   ref[0].x=ref[playerind[0]].x;
               ref[0].y=ref[playerind[0]].y; 
               hitter=playerind[6]; passed=1;
               rec=0;
                ref[playerind[6]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[0]].x,ref[playerind[0]].y); 
          
               } }
               
               if(rec==-1 ||canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[3]].x,ref[playerind[3]].y))  // pass it to player3
               {   ref[0].x=ref[playerind[3]].x;
               ref[0].y=ref[playerind[3]].y; 
               hitter=playerind[6];passed=1;
               rec=1;
               ref[playerind[6]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[3]].x,ref[playerind[3]].y); 
          
                }
                
                for(j=1;j<11;j++)
                {  if(j==i||j==rec)
                 continue;
                  ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }
               
                if(!passed)
                if(omaxstr(6))
                 {  ref[playerind[6]].strength--;
                 ref[playerind[6]].x++;  }
               
               
               break;
      
      // player0 has the ball 
      case 0:  passed=0;  
           ret=canscore(i);
           if(ret[0]!=-1)  // player0 can score a goal
           {  i=11;
           ref[playerind[0]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[0].x,ref[0].y); 
          
           ref[0].x=ret[0];
           ref[0].y=ret[1];
           scorer=i;
           passed=1;
           hitter=playerind[0];
           lastmoved=1;
              goto check_states; }
              
           if(rec ==-1 || canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[1]].x,ref[playerind[1]].y))
           {
                  ref[0].x=ref[playerind[1]].x;
                  ref[0].y=ref[playerind[1]].y; 
                  hitter=playerind[0]; 
                  rec=1;passed=1;
                  lastmoved=1;
                  ref[playerind[0]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[1]].x,ref[playerind[1]].y); 
           }
           if(rec==-1 || canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[3]].x,ref[playerind[3]].y))
                    {ref[0].x=ref[playerind[3]].x;
                  ref[0].y=ref[playerind[3]].y; 
                  hitter=playerind[0]; 
                  rec=3;passed=1;
                  lastmoved=1;
                  ref[playerind[0]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[3]].x,ref[playerind[3]].y); 
          }
          		if(rec==-1)
        {	
                  indexes.clear();                  
                  indexes.pb(4);
                  indexes.pb(6);
                  
                for(j=0;j<n.size();j++)
            {     next=n[j];
            	if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y))	
			  {   ref[0].x=ref[playerind[next]].x;
                  ref[0].y=ref[playerind[next]].y; 
                  hitter=playerind[0]; passed=1; rec=next;
                  lastmoved=1;
                  ref[playerind[0]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y); 
                  break; }
                  }
			 }
                  
            	for(j=1;j<11;j++)
            {  if(j==i||j==rec)
                 continue;
                  ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }
                     
                if(!passed) 
                 if(omaxstr(0))
                 {  
                       ref[playerind[0]].strength--;
                       ref[playerind[0]].x++;
                       lastmoved=1;  }
              
            break;
       
       //  one of the two moving attackers has the ball
       case 1:   passed=0;
           ret=canscore(i);
           if(ret[0]!=-1)// player1 can score a goal
           {  i=11;
           scorer=i;
            ref[playerind[1]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[0].x,ref[0].y); 
          passed=1;
           ref[0].x=ret[0];
           ref[0].y=ret[1];
           
           hitter=playerind[1];
              goto check_states; }
            
           if(rec==-1 ||canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[0]].x,ref[playerind[0]].y))  // pass it to player1
           { ret=canscore(0);
           if(ret[0]!=-1)
           {   ref[0].x=ref[playerind[0]].x;
               ref[0].y=ref[playerind[0]].y; 
               hitter=playerind[1];passed=1;
               ref[playerind[1]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[0]].x,ref[playerind[0]].y); 
        
               rec=0; }  }
            
    		if(rec==-1)
        {	
                  indexes.clear();
                  indexes.pb(4);
                  indexes.pb(6);
                //  indexes.pb(1);
                  indexes.pb(3);
                  
                // next=maxstr(indexes);
			
				n=maxstr(indexes);
                
            for(j=0;j<n.size();j++)
            {     next=n[j];
            	if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y))	
			  {   ref[0].x=ref[playerind[next]].x;
                  ref[0].y=ref[playerind[next]].y; 
                  hitter=playerind[1]; passed=1; rec=next;
                  ref[playerind[1]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y); 
                  break; }
                  }
            
            
             }
            
            
            	for(j=1;j<11;j++)
            {  if(j==i||j==rec)
                 continue;
                  ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }
                    
                    if(!passed)
                    if(omaxstr(1))
                 {  ref[playerind[1]].strength--;
                 ref[playerind[1]].x++;  }
              
                      
            break;
            
       
       
       case 3:passed=0;
            
             ret=canscore(i);
           if(ret[0]!=-1)// player3 can score a goal
           {  i=11;
            ref[playerind[3]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[0].x,ref[0].y); 
                     scorer=i;
           ref[0].x=ret[0];
           ref[0].y=ret[1];
           passed=1;
           hitter=playerind[3];
              goto check_states; }
            
           if(rec==-1 ||canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[0]].x,ref[playerind[0]].y))  // pass it to player0
           { ret=canscore(0);
           if(ret[0]!=-1)
           {   ref[0].x=ref[playerind[0]].x;
               ref[0].y=ref[playerind[0]].y; 
               hitter=playerind[3];passed=1;
               ref[playerind[3]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[0]].x,ref[playerind[0]].y); 
        
               rec=0; }  }
            
          if(rec==-1) {
                  indexes.clear();
                  indexes.pb(4);
                  indexes.pb(6);
                  indexes.pb(1);
              //    indexes.pb(3);
                  
                // next=maxstr(indexes);
			
				n=maxstr(indexes);
            
            
            for(j=0;j<n.size();j++)
            {     next=n[j];
            	if(canpass(i,ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y))	
			  {   ref[0].x=ref[playerind[next]].x;
                  ref[0].y=ref[playerind[next]].y; 
                  hitter=playerind[3]; passed=1; rec=next;
                  ref[playerind[3]].strength-=preqpb(ref[playerind[i]].x,ref[playerind[i]].y,ref[playerind[next]].x,ref[playerind[next]].y); 
                  break; }
                  }
            
             }
            
            	for(j=1;j<11;j++)
            {  if(j==i||j==rec)
                 continue;
                  ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }
                    
                    if(!passed)
                    if(omaxstr(3))
                 {  ref[playerind[3]].strength--;
                 ref[playerind[3]].x++;  }                    
            
            
             break;    
       
       //  We have scored a goal.Move the players towards their predef positions     
       case 11:  
                 for(j=0;j<11;j++)
                {  if(j==scorer)
                   continue;
                ref[playerind[j]].x=preposx[j];
                  ref[playerind[j]].y=preposy[j];
                      
                    }
                  
             
                    
	for(k=25;k<=50;k++)
	{   bool ppresent=false;
	for(j=low;j<=high;j++)
	{ if(ref[j].y==k&&ref[j].x==50)
     {  ppresent=true;
		 break; }
	  if(!ppresent)
	{   ref[playerind[0]].y= k-1;
        ref[playerind[0]].x=50;}
		}}
	               
             break;     }  // end switch
             
             if(!lastmoved)
               { if(ref[playerind[0]].strength>=4)
                if(ref[playerind[0]].x >=34 && teamnum==2)
                {
                      ref[playerind[0]].x-=4;
                      ref[playerind[0]].strength-=4;
                     lastmoved=1;
                } 
                else if(ref[playerind[0]].x <=66 && teamnum==1)
                {
                     ref[playerind[0]].x+=4;
                      ref[playerind[0]].strength-=4;
                      lastmoved=1;
                }
                }
                else
                lastmoved=0;
             } //   end of if possess
             
      else   // our team doesnt possess the ball 
      // the ball is in our D
      //  if it is not, move all the players to their predefined positions
      {
          cout<<"ball not in our posess"; 
          
          	ind=-1;int ma=0;
		int opossess=0;
			for(j=olow;j<=ohigh;j++)
			 	if(ref[j].x==ref[0].x && ref[j].y==ref[0].y)
					if(ref[j].strength>ma)
					{ opossess = 1;
					   ind=j;
                       ma=ref[j].strength;  }     
                 
             int strreqd=ref[ind].strength;
              
		if(opossess)       
{	if((ref[0].x<=dmaxx&&teamnum==1)||(ref[0].x>=dminx&&teamnum==2))          
	{	
	     
             cout<<"oppn posess the ball in our d";
              int bx=ref[0].x;
			  int by=ref[0].y;
			  int ma=0,bestp=-1,movp=-1;
			  
			  for(j=low;j<=high;j++)
			  if(j==playerind[5]||j==playerind[7]||j==playerind[8]||j==playerind[9]||j==playerind[10])
			  if((ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y))>strreqd)
			  if(ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y)>ma)
			  {  ma=ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y);
                   bestp=j;  }
                   
                   cout<<"bestp = "<<bestp;
               
               if(bestp!=-1)
               {  ref[bestp].strength-=preqp(bx,by,ref[bestp].x,ref[bestp].y);
                   ref[bestp].x=bx;
                   ref[bestp].y=by;
                   
                   for(j=1;j<11;j++)				
                {               
                if(playerind[j]==bestp)
                        continue;
                   ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                    ref[playerind[j]].x=preposx[j];
                   ref[playerind[j]].y= preposy[j];   
                } //end for
	      
	            goto possession;
                     } // end if
                   
                  for(j=low;j<=high;j++)
                      if(ref[j].x==bx&&ref[j].y==by)
			            {  movp=j;                                                    
                             break;  } 
                             
                             
                      if(movp!=-1)
                      {   ref[movp].x++;  } 
                      
              	for(j=1;j<11;j++)
            {  if(playerind[j]==movp)
                 continue;
                 ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   }          
                        
			}  // end if of ball in our d


                //opp  posesses the ball but not in our D
		else 
		{  cout<<"\n opp does possess the ball but not in our D";
             
        int bx=ref[0].x,ind;
			  int by=ref[0].y;
             bestp=-1;
             ma=0;
             
           for(j=olow;j<=ohigh;j++)
			 	if(ref[j].x==ref[0].x && ref[j].y==ref[0].y)
					if(ref[j].strength>ma)
					{ opossess = 1;
					   ind=j;
                       ma=ref[j].strength;  }     
                 
             int strreqd=ref[ind].strength;  
           for(j=low;j<=high;j++)           
           {         
            if(j==playerind[2]||j==playerind[1]||j==playerind[3]||j==playerind[4]||j==playerind[6])
               { if(ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y)>strreqd)
                 if(ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y)>ma)
                 { ma=ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y);
                   bestp=j; 
                 }//end if
               }//end if
            }//end for

             cout<<"\nbestp"<<bestp;
             
			if(bestp!=-1)
			{  	
                
                ref[bestp].strength-=preqp(bx,by,ref[bestp].x,ref[bestp].y);
			    ref[bestp].x=ref[0].x;
				ref[bestp].y=ref[0].y;
			
			  	if(playerind[0]==bestp)
			    	lastmoved=1;
	    	    else lastmoved=0;
	    	    
                for(j=1;j<11;j++)				
                {               
                if(playerind[j]==bestp)
                        continue;
                   ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                    ref[playerind[j]].x=preposx[j];
                   ref[playerind[j]].y= preposy[j];   
                } //end for
	      
	            goto possession;
           } //end if of bestp
           
				cout<<"lastmoved"<<lastmoved;
			  for(j=1;j<11;j++)				
                {               
                if(playerind[j]==bestp)
                        continue;
                   ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                    ref[playerind[j]].x=preposx[j];
                   ref[playerind[j]].y= preposy[j];   
                } //end for
                
          }  //end else for ball not in our D  but opossess
          
          }   // end if opossess
          
          else   // opp doesnt possess the ball
          {    
          
          if((ref[0].x<=dmaxx&&teamnum==1)||(ref[0].x>=dminx&&teamnum==2))          
	{   cout<<"\nopp doesnt possess and ball in our d";
          int bx=ref[0].x;
			  int by=ref[0].y;
             bestp=-1;
             
             for(j=low;j<=high;j++)
             if(j==playerind[5]||j==playerind[7]||j==playerind[8]||j==playerind[9]||j==playerind[10])
			  if(ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y)>ma)
			  {  ma=ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y);
                   bestp=j;  }

            cout<<"bestp"<<bestp;
            
			if(bestp!=-1)
			{  	ref[bestp].strength-=preqp(bx,by,ref[bestp].x,ref[bestp].y);
				ref[bestp].x=ref[0].x;
				ref[bestp].y=ref[0].y;
				
				if(playerind[0]==bestp)
                    lastmoved=1;
				 else lastmoved=0;
				 
				for(j=1;j<11;j++)
            {  if(playerind[j]==bestp)
                 continue;
                 ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                 ref[playerind[j]].x=preposx[j];
               ref[playerind[j]].y= preposy[j];   } 
               
				goto possession;
			}}//  end if ball in our d
          else  // opp doesnt possess and ball not in our d
          {
          cout<<"\nopp doesnt possess n ball not in our D";
        cout<<"bestp"<<bestp;
        int bx=ref[0].x;
			  int by=ref[0].y;
             bestp=-1;
             ma=0;
           for(j=low;j<=high;j++)           
           {         
           if(ref[0].x==50)
           {
           if(j==playerind[2]||j==playerind[1]||j==playerind[3]||j==playerind[4]||j==playerind[6]||j==playerind[0])
              if(ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y)>ma)
              { ma=ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y);
              bestp=j; 
              }//end if
           }//end if
           else
            {  if(j==playerind[2]||j==playerind[1]||j==playerind[3]||j==playerind[4]||j==playerind[6])
               {
                 if(ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y)>ma)
                 { ma=ref[j].strength-preqp(bx,by,ref[j].x,ref[j].y);
                   bestp=j; 
                 }//end if
               }//end if
            } //end else
            }//end for

             cout<<"\nbestp"<<bestp;
             
			if(bestp!=-1)
			{  	ref[bestp].strength-=preqp(bx,by,ref[bestp].x,ref[bestp].y);
			    ref[bestp].x=ref[0].x;
				ref[bestp].y=ref[0].y;
			    
			    
			  	if(playerind[0]==bestp)
			    	lastmoved=1;
	    	    
                for(j=1;j<11;j++)				
                {               
                if(playerind[j]==bestp)
                        continue;
                   ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                    ref[playerind[j]].x=preposx[j];
                   ref[playerind[j]].y= preposy[j];   
                } //end for
	      
	            goto possession;
           } //end if of bestp
           
				cout<<"lastmoved"<<lastmoved;
			  for(j=1;j<11;j++)				
                {               
                if(playerind[j]==bestp)
                        continue;
                   ref[playerind[j]].strength-=preqp(ref[playerind[j]].x,ref[playerind[j]].y,preposx[j],preposy[j]);              
          
                    ref[playerind[j]].x=preposx[j];
                   ref[playerind[j]].y= preposy[j];   
                } //end for
                
          }  //end else for ball not in our D and opp doesnt possess
          
          
          
          
          
          
          
          
          
          
          
          
          //-----------
          }// end else 
       } //end else for ball not in our posess
	

            
      for(i=0;i<23;i++)
        {
         p[i].x=ref[i].x;
         p[i].y=ref[i].y;
         p[i].strength=ref[i].strength; 
         }          
                            
      return hitter;   }   // end player      
      
      }; //end class  
      
