#include<iostream>
//#include"C:\\Documents and Settings\\Sumit\\My Documents\\code\\common.h"
using namespace std;
class team0023
{
    int counter,prev,moveh;
    struct player initial[23],beforeMove[23];
    int preqp(int finalx,int finaly, int initialx ,int initialy )  //function which tells the strength req by player to move from 
	{
         float req;                                                    //place to another
         req=(float)floor(sqrt(pow((double)(finalx-initialx),2)+pow((double)(finaly-initialy),2)));
         return (int)req;
    }     

    int preqpb(int finalx,int finaly, int initialx ,int initialy )   //function which tells the strength req by hitter of ball to hit
	{
         float req; int i;                                            //the ball from one place to another
         req=(float)2*(floor(sqrt(pow((double)(finalx-initialx),2)+pow((double)(finaly-initialy),2))));
         i=(int)req;
         return i;
    }
    int team_no,add;
    
     
      
    public:
        
         void init(int no,struct player* p,char farray[101][51])
         {
                team_no=no;
                moveh=0;
                if(no==1)
                 add=1;
                else
                 add=12;
                counter=0;
                prev=-1;   
                for(int i=0;i<23;i++)
                {
                    initial[i]=p[i];
                }
         }
         int player(struct player* p)
         {
                 for(int i=0;i<23;i++)
                 {
                    beforeMove[i]=p[i];
                 } 
                 counter=0;
                 int x,y;
                 x=p[0].x;
                 y=p[0].y;
                 int my_poss=search1(x,y);
                 int opp_poss=search2(x,y);
                 int cas;
                 //cout<<"\n"<<my_poss<<endl<<opp_poss;
                 //cout<<endl<<p[0].x<<"\t"<<p[0].y;
                 if(my_poss!=-1&&opp_poss==-1)
                 {
                     cout<<"\nCase is 1"<<endl<<my_poss;
                     return caseis1(my_poss);
                 }    
                 if(my_poss==-1&&opp_poss!=-1)
                   return caseis2(opp_poss);
                 if(my_poss!=-1&&opp_poss!=-1)
                   return caseis3(my_poss,opp_poss);
                 else
                   return caseis4();
                 return 0;
         }
         int search1(int x,int y)
         {
             int max=-1;
             for(int i=add;i<add+11;i++)
             {
                 if(global[i].x==x&&global[i].y==y)
                 {
                     if(max==-1)
                       max=i;
                     else
                         if(global[i].strength>global[max].strength)
                           max=i;
                   //        return p[i];
                 }    
             }
             if(max==-1)
             {
                 return -1;
             }
             return max;    
         }
         int search2(int x,int y)
         {
             int max=-1;
             int j;
             if(add==1)
              j=12;
             else
              j=1;
             for(int i=j;i<j+11;i++)
             {
                 if(global[i].x==x&&global[i].y==y)
                 {
                     if(max==-1)
                       max=i;
                     else
                         if(global[i].strength>global[max].strength)
                           max=i;
                   //        return p[i];
                 }    
             }
             if(max==-1)
             {
                 return -1;
             }
             return max;    
         }
         void check_present(int po,int a=1,int t=23)                   //check Strength change//done
         {
             for(int i=a;i<t;i++)
             {
                 if(i!=po)
                 {
                     if(global[i].x==global[po].x&&global[i].y==global[po].y)
                     {
                         if(team_no==1)
                         {
                             if(global[po].strength>0)
                               global[po].x--;                     //think for team=2//done
                             else
                              return;
                             calcStrength();
                             if(global[po].x<1)
                             {
                                 int s=preqp(15,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=15;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                                 calcStrength();                                 //Check,strength change//done
                                 //check_present(po);
                             }
                             check_present(po,a,t);
                         }
                         else
                         {
                             if(global[po].strength>0)
                               global[po].x++;
                             else
                               return;
                             calcStrength();
                             if(global[po].x>99)
                             {
                                 int s=preqp(85,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=85;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                                 calcStrength();
                             }    
                             check_present(po,a,t);
                         }
                     }
                 }
             }
         }
         /*void check_present2(player* p,player& po)
         {
             for(int i=1;i<23;i++)
             {
                 if(p[i]!=po)
                 {
                     if(p[i].x==po.x&&p[i].y==po.y)
                     {
                         po.x++;
                         if(po.x>99)
                         {
                             po.x=90;
                             check_present2(p,po);
                         }    
                     }
                 }
             }
         }*/
         void back(int po)
         {
             if(team_no==1)
             {
                 if(global[po].strength>20)
                 {
                     global[po].x-=20;
                     calcStrength();
                     //global[po].strength-=20;
                     if(global[po].x<initial[po].x)
                     {
                         global[po].x+=20;
                         calcStrength();
                         //global[po].strength+=20;
                     }    
                     check_present(po);
                 }
                 else
                 {
                     global[po].x-=global[po].strength;
                     //cout<<"\nBefore calc strength";
                     //system("pause");
                     calcStrength();
                     //cout<<"\nAfter calc strength";
                     //system("pause");
                     if(global[po].x<initial[po].x)
                     {
                         global[po].x+=global[po].strength;
                         calcStrength();
                     }
                     //else
                       //global[po].strength=0;
                     //cout<<"\nBefore check_present";
                     check_present(po);
                     //system("pause");
                 }
             }
             else
             {
                 if(global[po].strength>20)
                 {
                     global[po].x+=20;
                     calcStrength();
                     //global[po].strength-=20;
                     if(global[po].x>initial[po].x)
                     {
                         //global[po].strength+=20+(10+global[po].x);
                         global[po].x-=20;
                         calcStrength();
                         //global[po].strength+=20;
                     }    
                     check_present(po);
                 }
                 else
                 {
                     global[po].x+=global[po].strength;
                     calcStrength();
                     if(global[po].x>initial[po].x)
                     {
                         global[po].x-=global[po].strength;
                         calcStrength();
                     }
                     //else
                       //global[po].strength=0;
                     //global[po].strength=0;    
                     check_present(po);
                 }
             }
         }                                         
         void ahead(int po)
         {
             if(team_no==1)
             {
                 if(global[po].strength>20)
                 {
                     global[po].x+=20;
                     calcStrength();
                     //global[po].strength-=20;
                     if(global[po].x>99)
                     {
                         //global[po].strength+=20-(global[po].x-110);
                         global[po].x-=20;
                         calcStrength();
                     }    
                     check_present(po);
                 }
                 else
                 {
                     global[po].x+=global[po].strength;
                     calcStrength();
                     //global[po].strength=0;
                     if(global[po].x>99)
                     {
                         global[po].x-=global[po].strength;
                         calcStrength();
                     }
                     //global[po].strength=0;    
                     check_present(po);
                  }
              }
              else
              {
                 if(global[po].strength>20)
                 {
                     global[po].x-=20;
                     calcStrength();
                     //global[po].strength-=20;
                     if(global[po].x<1)
                     {
                         //global[po].strength+=20+(10+global[po].x);
                         global[po].x+=20;
                         calcStrength();
                     }    
                     check_present(po);
                 }
                 else
                 {
                     global[po].x-=global[po].strength;
                     calcStrength();
                     if(global[po].x<1)
                     {
                         global[po].x+=global[po].strength;
                         calcStrength();
                     }
                     //global[po].strength=0;    
                     check_present(po);
                  }
              }          
         }    
         void moveAhead(int poss)
         {
             for(int i=add,j=1;i<add+11;i++,j++)
             {
                 if(i!=poss)
                 {
                     ahead(i);
                 }
             }
             getinRange(poss);
             for(int i=add;i<add+11;i++)
             {
                 if(i!=poss)
                   check_present(i);
             }
             for(int po=add+10;po>=add;po--)
             {
                 if(po!=poss)
                 {
                     switch(po)
                     {
                         case 8:
                         case 9:
                         case 10:
                             /*if(global[po].x>global[11].x-5)
                             {
                                 int s=preqp(global[11].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[11].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }    
                             calcStrength();*/
                             check_present(po);  
                             break;
                         case 5:
                         case 6:
                         case 7:
                             if(global[po].x>global[8].x-5)
                             {
                                 int s=preqp(global[8].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[8].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[9].x-5)
                             {
                                 int s=preqp(global[9].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[9].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[10].x-5)
                             {
                                 int s=preqp(global[10].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[10].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             check_present(po);  
                             break;
                         case 2:
                         case 3:
                         case 4:
                             if(global[po].x>50)
                             {
                                 int s=preqp(50,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=50;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[4].x-5)
                             {
                                 int s=preqp(global[4].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[4].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[5].x-5)
                             {
                                 int s=preqp(global[5].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[5].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[6].x-5)
                             {
                                 int s=preqp(global[6].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[6].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             check_present(po);  
                             break;        
                         case 1:
                             if(global[po].x>30)
                             {
                                 int s=preqp(30,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=30;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[2].x-5)                           //Check,Should be for all 4 5 6//done
                             {
                                 int s=preqp(global[2].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[2].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[3].x-5)
                             {
                                 int s=preqp(global[3].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[3].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[4].x-5)
                             {
                                 int s=preqp(global[4].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[4].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             check_present(po);  
                             break;
                     }
                     switch(po)
                     {
                         case 19:
                         case 20:
                         case 21:
                             /*if(global[po].x<global[22].x+5)
                             {
                                 int s=preqp(global[22].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[22].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();*/
                             check_present(po);  
                             break;
                         case 16:
                         case 17:
                         case 18:
                             if(global[po].x<global[19].x+5)
                             {
                                 int s=preqp(global[19].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[19].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[20].x+5)
                             {
                                 int s=preqp(global[20].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[20].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[21].x+5)
                             {
                                 int s=preqp(global[21].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[21].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             check_present(po);  
                             break;
                         case 13:
                         case 14:
                         case 15:
                             if(global[po].x<50)
                             {
                                 int s=preqp(50,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=50;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[16].x+5)
                             {
                                 int s=preqp(global[16].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[16].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[17].x+5)
                             {
                                 int s=preqp(global[17].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[17].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[18].x+5)
                             {
                                 int s=preqp(global[18].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[18].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             check_present(po);  
                             break;        
                         case 12:
                             if(global[po].x<70)
                             {
                                 int s=preqp(70,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=70;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[14].x+5)                           //Check,Should be for all 13 14 15//done
                             {
                                 int s=preqp(global[14].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[14].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[15].x+5)
                             {
                                 int s=preqp(global[15].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[15].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[13].x+5)
                             {
                                 int s=preqp(global[13].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[13].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             check_present(po);  
                             break;
                     }
                 }    
             }    
         }
         void moveBack(int poss)
         {
             for(int i=add;i<add+11;i++)
             {
                 //system("pause");
                 if(i!=poss)
                 {
                     back(i);
                 }
             }
             //system("pause");
             getinRange(poss);
             for(int i=add;i<add+11;i++)
             {
                 if(i!=poss)
                   check_present(i);
             }
             for(int po=add;po<add+11;po++)
             {
                 if(po!=poss)
                 {
                     switch(po)
                     {
                         case 2:
                         case 3:
                         case 4:
                             if(global[po].x<global[1].x+5)
                             {
                                 int s=preqp(global[1].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[1].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             break;
                         case 5:
                         case 6:
                         case 7:
                             if(global[po].x<global[2].x+5)
                             {
                                 int s=preqp(global[2].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[2].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[3].x+5)
                             {
                                 int s=preqp(global[3].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[3].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[4].x+5)
                             {
                                 int s=preqp(global[4].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[4].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             check_present(po);  
                             break;
                         case 8:
                         case 9:
                         case 10:
                             if(global[po].x<50)
                             {
                                 int s=preqp(50,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=50;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }                                 
                             calcStrength();
                             if(global[po].x<global[5].x+5)
                             {
                                 int s=preqp(global[5].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[5].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[6].x+5)
                             {
                                 int s=preqp(global[6].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[6].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[7].x+5)
                             {
                                 int s=preqp(global[7].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[7].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             check_present(po);  
                             break;
                         case 11:
                             if(global[po].x<40)
                             {
                                 int s=preqp(40,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=40;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             /*if(global[po].x<global[po-3].x+5)
                             {
                                 int s=preqp(global[po-3].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[po-3].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[9].x+5)
                             {
                                 int s=preqp(global[9].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[9].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x<global[10].x+5)
                             {
                                 int s=preqp(global[10].x+5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[10].x+5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();*/
                             check_present(po);  
                             break;
                     }
                     switch(po)
                     {
                         case 13:
                         case 14:
                         case 15:
                             if(global[po].x>global[12].x-5)
                             {
                                 int s=preqp(global[12].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[12].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             break;
                         case 16:
                         case 17:
                         case 18:
                             if(global[po].x>global[po-3].x-5)
                             {
                                 int s=preqp(global[po-3].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[po-3].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             check_present(po);  
                             break;
                         case 19:
                         case 20:
                         case 21:
                             if(global[po].x>60)
                             {
                                 int s=preqp(60,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=60;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[po-3].x-5)
                             {
                                 int s=preqp(global[po-3].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[po-3].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             check_present(po);  
                             break;
                         case 22:
                             if(global[po].x>50)
                             {
                                 int s=preqp(50,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=50;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             /*if(global[po].x>global[po-3].x-5)
                             {
                                 int s=preqp(global[po-3].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[po-3].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[20].x-5)
                             {
                                 int s=preqp(global[20].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[20].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();
                             if(global[po].x>global[21].x-5)
                             {
                                 int s=preqp(global[21].x-5,global[po].y,beforeMove[po].x,beforeMove[po].y);
                                 if(s<beforeMove[po].strength)
                                   global[po].x=global[21].x-5;
                                 else
                                 {
                                     global[po].x=beforeMove[po].x;                                 //Check,can be impreoved
                                     global[po].y=beforeMove[po].y;
                                 }
                             }
                             calcStrength();*/
                             check_present(po);  
                             break;
                     }
                 }    
             }             
         }    
         int findMin(int poss,int t=0,int cas=0)
         {
             int min=-1;
             int s;
             int i,temp;
             //const int e=add;
             if(cas==0)
             {
                 if(team_no==1)
                 {
                     switch(poss)
                     {
                         case 1:
                             i=poss;
                             break;
                         case 2:
                         case 3:
                         case 4:
                             i=5;
                             break;
                         case 5:
                         case 6:
                         case 7:
                             i=8;
                             break;
                         case 8:
                         case 9:
                         case 10:
                         case 11:
                             i=add+7;
                             break;
                     }
                 }
                 else
                 {
                     switch(poss)
                     {
                         case 12:
                             i=poss;
                             break;
                         case 13:
                         case 14:
                         case 15:
                             i=16;
                             break;
                         case 16:
                         case 17:
                         case 18:
                             i=19;
                             break;
                         case 19:
                         case 20:
                         case 21:
                         case 22:
                             i=19;
                             break;
                     }
                 }        
             }        
             else
               i=add;
             for(;i<add+11;i++)
             {
                 if(i!=poss&&i!=prev)
                 {
                     if(cas==0)
                     {
                         shift(poss,i);
                      if(noPresent(global[poss].x,global[poss].y,global[i].x,global[i].y))
                      {
                         int temp=search2(global[i].x,global[i].y);
                         if(i==6)
                           cout<<"\ntemp="<<temp;
                         if(temp!=-1)
                         {
                             if(global[temp].strength>=global[i].strength+20)
                               continue;
                         }
                         int s1=preqpb(global[i].x,global[i].y,global[poss].x,global[poss].y);
                         if(s1>global[poss].strength)
                           continue;
                         if(min==-1)
                         {
                             min=i;
                             s=preqpb(global[min].x,global[min].y,global[poss].x,global[poss].y);
                         }    
                         else
                         {
                             
                             //int s2=preqpb(p[min].x,p[min].y,poss.x,poss.y);
                             if(s1<s)
                             {
                                 min=i;
                                 s=preqpb(global[min].x,global[min].y,global[poss].x,global[poss].y);
                             }    
                         }
                      }
                     }
                     else
                     {
                         int s1=preqp(global[poss].x,global[poss].y,global[i].x,global[i].y);
                         if(s1<global[i].strength)
                           temp=i;
                         else
                           continue;
                         if(min==-1)
                         {
                             s=s1;
                             min=i;
                         }
                         else
                         {
                             if(s1<s)
                             {
                                 min=i;
                                 s=s1;
                             }
                         }
                     }            
                                           
                 }
             }
             //int s=preqpb(p[min].x,p[min].y,poss.x,poss.y);
             /*if(t==0)
               if(s>global[poss].strength)
                 min=-1;
             if(t==1)
               if((s/2)>global[min].strength)
                 min=-1;*/
             return min;
         }
         bool noPresent(int x,int y,int fx,int fy)
         {
             int xdiffb=fx-x;   //calculates the difference between changed coordinates and initial coordinates of the 
             int ydiffb=fy-y;
             int vx=x;
             int vy=y;
             while(vx!=fx||vy!=fy)
             {
                 if(vx!=fx)
                   (xdiffb>0)?(vx)++:(vx)--;
                 if(vy!=fy)
                   (ydiffb>0)?(vy)++:(vy)--;
                 if(vx==fx&&vy==fy)
                   break;  
                 for(int i=1;i<=22;i++)
                 {
                     if((vx==global[i].x)&&(vy==global[i].y))
                       return false;
                 }
             }
             return true;
         }        
             /*float slope;
             if(fx-x) 
               slope=(fy-y)/(fx-x);
             else
               return 1;                               // Check
             int i=x,j=y;
             for(int i=1;i<=fx-x;i++)                  // Only for fx>x
             {
                 float k=i*slope;
                 if(k<1)
                 {
                     if(present(::i+i,j))
                       return false;
                     continue;
                 }
                     
                 while(k)
                 {
                     if(present(::i,j+k))
                       return false;
                     k--;
                 }
             }
             return true;*//*
         }*/        
                   
         void attack(int poss,int k=100)
         {
             for(int j=10;j<=40;j++)
             {
                 if(noPresent(global[poss].x,global[poss].y,k,j))
                 {
                     int s=preqpb(k,j,global[poss].x,global[poss].y);
                     if(s<=global[poss].strength)
                     {
                         global[0].x=k;                     // Check for strength
                         global[0].y=j;
                         return;
                     }    
                 }       
             }
         }
         bool inrange(int poss,int k=100)
         {
             for(int j=10;j<=40;j++)
             {
                 if(noPresent(global[poss].x,global[poss].y,k,j))
                 {
                     int s=preqpb(k,j,global[poss].x,global[poss].y);
                     if(s<=global[poss].strength)
                     {
                         return true;
                     }    
                 }       
             }
             return false;
         }
         void display()
         {
             for(int i=add;i<add+11;i++)
             {
                 cout<<endl<<global[i].x<<"\t"<<global[i].y;
             }
         }        
         int caseis1(int poss)
         {
              for(int i=add;i<add+11;i++)
              {
                  if(i!=poss)
                    check_present(i);
              }
              //check_present(poss);
              cout<<"Coords:"<<global[poss].x<<"\t"<<global[poss].y;
              if(moveh>0)
                getinRange(poss,15);
              cout<<"\nCounter is "<<counter;
              if(counter==0)
              {
                  moveAhead(poss);
                  //cout<<"\nMoving Ahead";
              }
              //if(counter==2)
              //  getclose(poss);
              display();
              int i=findMin(poss);
              cout<<"\nNearest neighbour"<<i; 
              //int str=preqpb(p[i].x,p[i].y,poss.x,poss.y);
              int s;
              if(team_no==1)
              {
                  if(inrange(poss))
                  {
                      attack(poss);
                      moveBack(poss);
                      moveh=0;
                      return poss;
                  }    
                  if(global[poss].x>85)
                  {
                      attack(poss);
                      if(global[0].x==100)
                      {
                          moveBack(poss);
                          moveh=0;
                          return poss;
                      }    
                      if(i!=-1)
                      {
                          if(noPresent(global[poss].x,global[poss].y,global[i].x,global[i].y))
                          {
                              global[0].x=global[i].x;
                              global[0].y=global[i].y;
                              prev=poss;
                              /*if(global[i].x==90)
                              {
                                  attack(i);                              // Strength decr acc. in moveAhead
                                  if(global[0].x==100)
                                    return 2;
                                  return 1; 
                              }*/
                              moveh=0;
                              return poss;
                          }
                          //if(counter==0)
                            moveBack(poss);
                          if(counter==1)
                          {
                              moveh++;
                              return 0;
                          }    
                          counter++;
                          return caseis1(poss);                          //Checked,Recursively call caseis1                          
                      }
                      //if(counter==0)
                        moveBack(poss);
                      if(counter==1)
                      {
                          moveh++;
                          return 0;
                      }    
                      counter++;
                      return caseis1(poss);                           //Check,Recursively call caseis1           
                  }
                  if(i!=-1)
                  {
                      if(noPresent(global[poss].x,global[poss].y,global[i].x,global[i].y))
                      {
                          cout<<"\nNo one present.  Passing to i";
                          global[0].x=global[i].x;
                          global[0].y=global[i].y;
                          prev=poss;
                          /*if(global[i].x==90)
                          {
                              attack(i);                              // Strength decr acc. in moveAhead
                              if(global[0].x==100)
                                return 2;
                              return 1; 
                          }*/
                          moveh=0;
                          return poss;
                      }
                      //if(counter==0)
                        moveBack(poss);
                      if(counter==1)
                      {
                          moveh++;
                          return 0;
                      }    
                      counter++;
                      return caseis1(poss);
                  }
                  //if(counter==0)
                    moveBack(poss);
                  if(counter==1)
                  {
                      moveh++;
                      return 0;
                  }    
                  counter++;
                  return caseis1(poss);        
              }
              else
              {
                  if(inrange(poss,0))
                  {
                      attack(poss,0);
                      moveBack(poss);
                      moveh=0;
                      return poss;
                  }
                  if(global[poss].x<15)
                  {
                      attack(poss,0);
                      if(global[0].x==0)
                      {
                          moveBack(poss);
                          moveh=0;
                          return poss;
                      }    
                      if(i!=-1)
                      {
                          if(noPresent(global[poss].x,global[poss].y,global[i].x,global[i].y))
                          {
                              global[0].x=global[i].x;
                              global[0].y=global[i].y;
                              prev=poss;
                              /*if(global[i].x==10)
                              {
                                  attack(i,0);                              // Strength decr acc. in moveAhead
                                  if(global[0].x==0)
                                    return 2;
                                  return 1; 
                              }*/
                              moveh=0;
                              return poss;
                          }
                          //if(counter==0)
                            moveBack(poss);
                          if(counter==1)
                          {
                              moveh++;
                              return 0;
                          }    
                          counter++;
                          return caseis1(poss);
                      }
                      //if(counter==0)
                        moveBack(poss);
                      if(counter==1)
                      {
                          moveh++;
                          return 0;
                      }    
                      counter++;
                      return caseis1(poss);                
                  }
                  if(i!=-1)
                  {
                      if(noPresent(global[poss].x,global[poss].y,global[i].x,global[i].y))
                      {
                          global[0].x=global[i].x;
                          global[0].y=global[i].y;
                          prev=poss;
                          /*if(global[i].x==10)
                          {
                              attack(i,0);                              // Strength decr acc. in moveAhead
                              if(global[0].x==0)
                                return 2;
                              return 1; 
                          }*/
                          moveh=0;
                          return poss;
                      }
                      //if(counter==0)
                        moveBack(poss);
                      if(counter==1)
                      {
                          moveh++;
                          return 0;
                      }    
                      counter++;
                      return caseis1(poss);
                  }
                  //if(counter==0)
                    moveBack(poss);
                  if(counter==1)
                  {
                      moveh++;
                      return 0;
                  }    
                  counter++;
                  return caseis1(poss);        
              }
         }
         int caseis2(int poss)
         {
             cout<<"\nCase is 2";
             //system("pause");
             if(moveh>0)
               getinRange(poss,15);
             int i=findMin(poss,1,1);                          //Check if str is there to reach player//done
             cout<<"\nMin :"<<i;
             if(i==-1)
             {
                 moveh++;
                 return 0;
             }
             //system("pause");
             int s=preqp(global[poss].x,global[poss].y,global[i].x,global[i].y);
             global[i].x=global[poss].x;
             global[i].y=global[poss].y;
             global[i].strength-=s;
             //system("pause");
             if(global[i].strength<0)
             {
                 global[i].strength=0;
                 return 0;
             }    
             cout<<"Final coords:"<<global[i].x<<"\t"<<global[i].y;
             //system("pause");
             moveBack(i);
             //system("pause");
             global[i].strength-=global[poss].strength;
             moveh=0;
             //system("pause");
             cout<<"Final coords:"<<global[i].x<<"\t"<<global[i].y;
             return caseis1(i);
         }
         int caseis3(int mposs,int oposs)
         {
             if(moveh>0)
               getinRange(mposs,15);
             global[mposs].strength-=global[oposs].strength;
             return caseis1(mposs);
         }
         int caseis4()
         {
             if(moveh>0)
               getinRange(0,15);
             int i=findMin(0,1,1);
             if(i==-1)
             {
                 moveh++;
                 return 0;
             }    
             int s=preqp(global[0].x,global[0].y,global[i].x,global[i].y);
             global[i].x=global[0].x;
             global[i].y=global[0].y;
             global[i].strength-=s;
             if(global[i].strength<0)
             {
                 global[i].strength=0;
                 return 0;
             }
             moveh=0;
             //moveBack(i);
             return caseis1(i);
         }
         void getinRange(int t=0,int l=30)
         {
             int x=global[t].x,y=global[t].y;
             for(int i=add;i<add+11;i++)
             {
                 if(i!=t)
                 {
                 if(global[i].x-x>l||global[i].x-x<-l)
                 {
                     if(global[i].x-x>l)
                       global[i].x=x+l;
                     else
                       global[i].x=x-l;
                     calcStrength();
                 }
                 check_present(i);
                 }    
             }
         }
         void calcStrength()
         {
             for(int i=add;i<add+11;i++)
             {
                 int t=preqp(global[i].x,global[i].y,beforeMove[i].x,beforeMove[i].y);
                 global[i].strength=beforeMove[i].strength-t;
                 if(global[i].strength<0)
                   global[i].strength=0;
             }
         }
         void getclose(int po,int t=10)
         {
             if(po==add)
             {
                 for(int i=add+1;i<add+4;i++)
                 {
                     if(global[i].y>global[po].y+t)
                     {
                         global[i].y=global[po].y+t;
                     }
                     if(global[i].y<global[po].y-t)
                     {
                         global[i].y=global[po].y-t;
                     }
                     calcStrength();
                     check_present(i);
                 }
                 return;
             }    
             if(po<add+4)
             {
                 for(int i=add+4;i<add+7;i++)
                 {
                     if(global[i].y>global[po].y+t)
                     {
                         global[i].y=global[po].y+t;
                     }
                     if(global[i].y<global[po].y-t)
                     {
                         global[i].y=global[po].y-t;
                     }
                     calcStrength();
                     check_present(i);
                 }
                 return;
             }
             if(po<add+7)
             {
                 for(int i=add+8;i<add+10;i++)
                 {
                     if(global[i].y>global[po].y+t)
                     {
                         global[i].y=global[po].y+t;
                     }
                     if(global[i].y<global[po].y-t)
                     {
                         global[i].y=global[po].y-t;
                     }
                     calcStrength();
                     check_present(i);
                 }
                 return;
             }
             for(int i=add+8;i<add+11;i++)
             {
                  if(global[i].y>global[po].y+t)
                  {
                      global[i].y=global[po].y+t;
                  }
                  if(global[i].y<global[po].y-t)
                  {
                      global[i].y=global[po].y-t;
                  }
                  calcStrength();
                  check_present(i);
              }
          }
          void shift(int i,int j)
          {
                     if(noPresent(global[i].x,global[i].y,global[j].x,global[j].y))
                       return;
                     global[j].y++;
                     if(global[j].y<49)
                     {
                         calcStrength();
                         check_present(j);
                         if(noPresent(global[i].x,global[i].y,global[j].x,global[j].y))
                           return;
                     }
                     if(global[j].y>0)
                     {
                         global[j].y-=2;
                         calcStrength();
                         check_present(j);
                         if(noPresent(global[i].x,global[i].y,global[j].x,global[j].y))
                          return;
                     }    
                     global[j].y++;
                     calcStrength();
          }              
              /*if(i==-1)
              {
                  int str=poss.strength;
                  while(str>0)
                  {
                      if(team_no==1)
                      {
                          p[0].x++;*/
           //   }
         //}
};         
//remove strength in back//done
// Defence not come ahead,etc.//done
//inrange funcn,//done
//ball should always move ahead//done
//Remove same passes like a 2 b and then b 2 a//done
//If nothing is happening, get in range//done
//defenders in same line as ball
