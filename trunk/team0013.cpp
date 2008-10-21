#include<stdio.h>
#include<time.h>
//#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

using namespace std;

class team0013  //The name of your class should be teamxxxx where xxxx is the no. u will get at the time of registration and will
{                //be unique for every participant
  private:
  
  int team,ll,ul,status,frm;  //team is a variable used in player function which tells all of the functions defined by the participant what their team no. is
             //it is not mandatory for the player to use this variable .player can use any other means to satisfy the need
  //private fns 
  //this fn returns the strength req to move your player from one place to another 
  int preqp(int finalx,int finaly, int initialx ,int initialy )
	{ float req;
      req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
      return (int)req;
    }

//this fn returns the strength req by your hitter to move the ball from one place to another 
  int preqpb(int finalx,int finaly, int initialx ,int initialy )
	{ float req;
      int i;
      req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	  i=(int)req;
	  return i;
    }
	 
	 
  public:

   int init(int team_number, struct player *p,char farray[][51])   // this fn must be there in your program ,it will be called only 
	{ status=0;                                                        //once at the beginning of the program .It will tell u whether u are
      team=team_number;
      if(team==1) { ll=1; ul=11; }
      else if(team==2) {ll =12; ul=22; }
      formn(p);
      frm=1;                               //player 1 or 2 and this will also give u the basic fieldarray ie where there is
	}                                             //a goal or a dee or a boundary and struct player *p gives u the initial player
                                                 //distribution in the field
                                                 
    int player(struct player *p)  //This fn should contain the strategies u want to implement.You can also define other fns in your 
    { int c=poss(p);
      if(p[0].x==50)
       { if(frm==2)
          { attfrm(p);
          }
         if(frm==1)
          { attfrm(p);
            movdef(p);
          }
         if(frm==0);
          { deffrm(p);
          }
       }
        if(c<=ul&&c>=ll)
        { if(p[0].x<=40)                                    // our D
           { if(frm==1);
              { movatt(p);
                rballfw(p,c+2);
                return c;
              }
             if(frm==0);
              { movdef(p);
                rballfw(p,c+3);
                return c;
              }
             if(frm==2);
              { deffrm(p); frm=0; movdef(p);
                rballfw(p,c+5);
                return c;
              }
           }
          else if(p[0].x>40&&p[0].x<70)                     //our midfield
           { if(frm==1)
              { attfrm(p); frm=2; movatt(p);
                if(c>5&&c<9)
                 rballfw(p,c+rand()%3+1);
                else if(c==9||c==10)
                 rballfw(p,c+1);
                else
                 rballbk(p,c-3);
                return c;
              }
             if(frm==0)
              { formn(p); frm=1; movatt(p);
                if(c>5&&c<9)
                 rballfw(p,c+rand()%3+1);
                else if(c==9||c==10)
                 rballfw(p,c+1);
                else
                 rballbk(p,c-1);
                return c;
              }
             if(frm==2)
              { movatt(p);
                 if(c>5&&c<9)
                 rballfw(p,c+rand()%3+1);
                else if(c==9||c==10)
                 rballfw(p,c+1);
                else
                 rballbk(p,c-rand()%2*2-1);
                return c;
              }
           }

          else if(p[0].x>=70)                                     //their D
           { movdef(p);
             shotatgoal(p);
             return c;
           }
        }

        else if(c==0)
        { int n=near_p(p,0);

          if(p[0].x<=40)                     // our D
           { if(frm==0)
              { for(int i=0; n+i<=ul; i++)
                 { if(p[n+i].strength>20)
                    { getball(p,n+i);
                      formn(p); frm=1;
                      rballfw(p,n+i+2);
                      return n+i;
                    }
                 }
                return 1;
              }
             if(frm==1||frm==2)
              { for(int i=0; n+i<=ul; i++)
                 { if(p[n+i].strength>20)
                    { getball(p,n+i);
                      movatt(p);
                      if(n+i+1+2<=ul) rballfw(p,n+i+rand()%3+1);
                      else rballfw(p,ul);
                      return n+i;
                    }
                 }
                return 1;
              }
           }

          else if(p[0].x>40&&p[0].x<70) //our midfield
           {
             if(frm==1)
              { for(int i=0; n+i<=ul; i++)
                 { if(p[n+i].strength>20)
                    { getball(p,n+i);
                      movatt(p);
                      rballbk(p,n+i-rand()%2*2-1);
                      return n+i;
                    }
                 }
                return 1;
              }
             if(frm==2)
              { for(int i=0; n+i<=ul; i++)
                 { if(p[n+i].strength>20)
                    { getball(p,n+i);
                      movatt(p);
                      rballbk(p,n+i+1);
                      return n+i;
                    }
                 }
                return 1;
              }
             if(frm==0)
              { for(int i=0; n+i<=ul; i++)
                 { if(p[n+i].strength>20)
                    { getball(p,n+i);
                      rballbk(p,n+i-rand()%2*2-1);
                      attfrm(p); frm=1;
                      return n+i;
                    }
                 }
                return 1;
              }
           }
          else if(p[0].x>=70)                         //their D
           { for(int i=ul; i>ll; i--)
                 { if(p[i].strength>preqp(p[0].x,p[0].y,p[i].x,p[i].y))
                    { getball(p,i);
                      frm=2;
                      shotatgoal(p);
                      return i;
                    }
                 }
              formn(p); frm=1;
              return 1;
           }
        }
 /*-------------------------------------------------------------------------*/
       else if(c>ul||c<ll)
        { if(p[0].x<=40) // our D
           { deffrm(p); movdef(p);
             shotblock(p);
             return 1;
           }
          else if(p[0].x>40&&p[0].x<70) //our midfield
           { movdef(p);
             int n=near_p(p,0);
             if(frm==1)
              { for(int i=0; n+i<=ul; i++)
                 { if(p[n+i].strength>20)
                    { getball(p,n+i);
                      rballbk(p,n+i-rand()%2*2-1);
                      movatt(p);
                      return n+i;
                    }
                 }
                return 1;
              }
             if(frm==2)
              { for(int i=0; n+i<=ul; i++)
                 { if(p[n+i].strength>20)
                    { getball(p,n+i);
                      movatt(p);
                      rballbk(p,n+i+1);
                      return n+i;
                    }
                 }
                return 1;
              }
             if(frm==0)
              { for(int i=0; n+i<=ul; i++)
                 { if(p[n+i].strength>20)
                    { getball(p,n+i);
                      rballbk(p,n+i-rand()%2*2-1);
                      attfrm(p); frm=1;
                      return n+i;
                    }
                 }
                return 1;
              }
           }
          else if(p[0].x>=70) //their D
           { manmark(p);
             for(int i=ul; i>ll; i--)
                 { if(p[i].strength>preqp(p[0].x,p[0].y,p[i].x,p[i].y))
                    { getball(p,i);
                      frm=2;
                      shotatgoal(p);
                      return i;
                    }
                 }
              formn(p); frm=1;
             return 1;
           }
        }


  }
    void formn(struct player *p)
     { int c=poss(p);
        if((c!=ll)&&p[ll].strength>15) { p[ll-1+1].x=15; p[ll-1+1].y=25; }
        if((c!=ll+1)&&p[ll+1].strength>15) { p[ll-1+2].x=25; p[ll-1+2].y=10; }
        if((c!=ll+2)&&p[ll+2].strength>15) { p[ll-1+3].x=25; p[ll-1+3].y=20; }
        if((c!=ll+3)&&p[ll+3].strength>15) { p[ll-1+4].x=25; p[ll-1+4].y=30; }
        if((c!=ll+4)&&p[ll+4].strength>15) { p[ll-1+5].x=25; p[ll-1+5].y=40; }
        if((c!=ll+5)&&p[ll+5].strength>15) { p[ll-1+6].x=33; p[ll-1+6].y=15; }
        if((c!=ll+6)&&p[ll+6].strength>15) { p[ll-1+7].x=33; p[ll-1+7].y=35; }
        if((c!=ll+7)&&p[ll+7].strength>15) { p[ll-1+8].x=42; p[ll-1+8].y=10; }
        if((c!=ll+8)&&p[ll+8].strength>15) { p[ll-1+9].x=38; p[ll-1+9].y=25; }
        if((c!=ll+9)&&p[ll+9].strength>15) { p[ll-1+10].x=42; p[ll-1+10].y=40; }
        if((c!=ll+10)&&p[ll+10].strength>15) { p[ll-1+11].x=49; p[ll-1+11].y=25; }
     }  //contain the positions of the 22 players and the ball at that time .It is also supposed to return the
                                 //the no of the player who will hit the ball to the controller fn

    void getball(struct player *p,int pl)
     { for(int i=pl; i<=ul; i++)
        if((preqp(p[0].x,p[0].y,p[pl].x,p[pl].y))<=(p[pl].strength)-10)
         { p[pl].x=p[0].x;
           p[pl].y=p[0].y;
           return;
         }
       for(int i=pl; i>=ll; i--)
        if((preqp(p[0].x,p[0].y,p[pl].x,p[pl].y))<=(p[pl].strength)-10)
         { p[pl].x=p[0].x;
           p[pl].y=p[0].y;
           return;
         }
     }

    int poss(struct player *p)
     { for(int i=1; i<23; i++)
        if(p[0].x==p[i].x&&p[0].y==p[i].y)
         return i;
       return 0;
     }

    int near_p(struct player *p, int possn)
     { int low = preqp(p[possn].x,p[possn].y,p[ll].x,p[ll].y);
       int k=ll;
       for(int i=ll; i<=ul; i++)
        { if(i==possn) continue;
          if(preqp(p[possn].x,p[possn].y,p[i].x,p[i].y)<low)
           { low=preqp(p[possn].x,p[possn].y,p[i].x,p[i].y);
             k=i;
           }
        }
       return k;
     }

    void attfrm(struct player *p)
     { int c=poss(p);

       if((c!=ll-1+1)&&p[ll].strength>20) { p[ll-1+1].x=20; p[ll-1+1].y=25; }
       if((c!=ll-1+2)&&p[ll+1].strength>20) { p[ll-1+2].x=35; p[ll-1+2].y=10; }
       if((c!=ll-1+3)&&p[ll+2].strength>20) { p[ll-1+3].x=30; p[ll-1+3].y=15; }
       if((c!=ll-1+4)&&p[ll+3].strength>20) { p[ll-1+4].x=30; p[ll-1+4].y=35; }
       if((c!=ll-1+5)&&p[ll+4].strength>20) { p[ll-1+5].x=35; p[ll-1+5].y=40; }
       if((c!=ll-1+6)&&p[ll+5].strength>20) { p[ll-1+6].x=53; p[ll-1+6].y=15; }
       if((c!=ll-1+7)&&p[ll+6].strength>20) { p[ll-1+7].x=53; p[ll-1+7].y=35; }
       if((c!=ll-1+8)&&p[ll+7].strength>20) { p[ll-1+8].x=64; p[ll-1+8].y=5;  }
       if((c!=ll-1+9)&&p[ll+8].strength>20) { p[ll-1+9].x=62; p[ll-1+9].y=28; }
       if((c!=ll-1+10)&&p[ll+9].strength>20) { p[ll-1+10].x=64; p[ll-1+10].y=45; }
       if((c!=ll-1+11)&&p[ll+10].strength>20) { p[ll-1+11].x=65; p[ll-1+11].y=rand()%25+10;}

     }

    void deffrm(struct player *p)
     { int c=poss(p);

       if((c!=ll-1+1)&&p[ll].strength>20) { p[ll-1+1].x=17; p[ll-1+1].y=25; }
       if((c!=ll-1+2)&&p[ll+1].strength>20) { p[ll-1+2].x=30; p[ll-1+2].y=10; }
       if((c!=ll-1+3)&&p[ll+2].strength>20) { p[ll-1+3].x=25; p[ll-1+3].y=15; }
       if((c!=ll-1+4)&&p[ll+3].strength>20) { p[ll-1+4].x=25; p[ll-1+4].y=35; }
       if((c!=ll-1+5)&&p[ll+4].strength>20) { p[ll-1+5].x=30; p[ll-1+5].y=40; }
       if((c!=ll-1+6)&&p[ll+5].strength>20) { p[ll-1+6].x=48; p[ll-1+6].y=15; }
       if((c!=ll-1+7)&&p[ll+6].strength>20) { p[ll-1+7].x=48; p[ll-1+7].y=35; }
       if((c!=ll-1+8)&&p[ll+7].strength>20) { p[ll-1+8].x=54; p[ll-1+8].y=15;  }
       if((c!=ll-1+9)&&p[ll+8].strength>20) { p[ll-1+9].x=52; p[ll-1+9].y=24; }
       if((c!=ll-1+10)&&p[ll+9].strength>20) { p[ll-1+10].x=54; p[ll-1+10].y=35; }
       if((c!=ll-1+11)&&p[ll+10].strength>20) { p[ll-1+11].x=60; p[ll-1+11].y=27;}
     }

    void movatt(struct player *p)
     { int c=poss(p);
       if(p[0].x<35)
        { if((c!=ll-1+1)&&p[ll].strength>20) { p[ll-1+1].x+=3; }
          if((c!=ll-1+2)&&p[ll+1].strength>20) { p[ll-1+2].x+=10; p[ll-1+2].y+=2; }
          if((c!=ll-1+3)&&p[ll+2].strength>20) { p[ll-1+3].x+=7; }
          if((c!=ll-1+4)&&p[ll+3].strength>20) { p[ll-1+4].x+=7; }
          if((c!=ll-1+5)&&p[ll+4].strength>20) { p[ll-1+5].x+=10; p[ll-1+5].y-=2; }
          if((c!=ll-1+6)&&p[ll+5].strength>20) { p[ll-1+6].x+=5; p[ll-1+6].y-=2; }
          if((c!=ll-1+7)&&p[ll+6].strength>20) { p[ll-1+7].x+=5; p[ll-1+7].y+=3; }
          if((c!=ll-1+8)&&p[ll+7].strength>20) { p[ll-1+8].x+=5; }
          if((c!=ll-1+9)&&p[ll+8].strength>20) { p[ll-1+9].x+=4; }
          if((c!=ll-1+10)&&p[ll+9].strength>20) { p[ll-1+10].x+=5; }
          if((c!=ll-1+11)&&p[ll+10].strength>20) { p[ll-1+11].x+=10; p[ll-1+11].y+=3;}
        }
       if(p[0].x>35&&p[0].x<55)
        {  if((c!=ll-1+6)&&p[ll+5].strength>20) { p[ll-1+6].x+=5; p[ll-1+6].y-=2; }
           if((c!=ll-1+7)&&p[ll+6].strength>20) { p[ll-1+7].x+=5; p[ll-1+7].y+=3; }
           if((c!=ll-1+8)&&p[ll+7].strength>20) { p[ll-1+8].x+=5; }
           if((c!=ll-1+9)&&p[ll+8].strength>20) { p[ll-1+9].x+=4; }
           if((c!=ll-1+10)&&p[ll+9].strength>20) { p[ll-1+10].x+=5; }
           if((c!=ll-1+11)&&p[ll+10].strength>20) { p[ll-1+11].x+=15; p[ll-1+11].y+=3;}
        }
       if(p[0].x>55)
        { if((c!=ll-1+8)&&p[ll+7].strength>20) { p[ll-1+8].x+=5; }
          if((c!=ll-1+9)&&p[ll+8].strength>20) { p[ll-1+9].x+=4; }
          if((c!=ll-1+10)&&p[ll+9].strength>20) { p[ll-1+10].x+=5; }
          if((c!=ll-1+11)&&p[ll+10].strength>20) { p[ll-1+11].x+=15; p[ll-1+11].y+=3;}
        }
     }

    void rballbk(struct player *p,int possn)
     { int c=poss(p);
        for(; possn>=ll; possn--)
         if(preqpb(p[c].x,p[c].y,p[possn].x,p[possn].y)<(p[c].strength-10))
          { p[0].x=p[possn].x;
            p[0].y=p[possn].y;
            return;
          }
        if(possn<ll)
         { p[0].x=p[ll].x;
           p[0].y=p[ll].y;
           return;
         }
     }
    void rballfw(struct player *p,int possn)
     { int c=poss(p);
       int i=possn;
        for(; possn<=ul; possn++)
         {  if(possn==c) continue;
            if(preqpb(p[c].x,p[c].y,p[possn].x,p[possn].y)<(p[c].strength-10))
            {
              p[0].x=p[possn].x;
              p[0].y=p[possn].y;
              return;
            }
         }
        if(possn>ul)
         { for(possn=i; possn>=ll; possn--)
            { if(possn==c) continue;
              if(preqpb(p[c].x,p[c].y,p[possn].x,p[possn].y)<(p[c].strength-10))
              {
                p[0].x=p[possn].x;
                p[0].y=p[possn].y;
                return;
              }
            }
         }
        shotatgoal(p);
     }

    void movdef(struct player *p)
    { int c=poss(p);
      if(p[0].x>55)
      { if((c!=ul)&&p[c].x>45&&p[ul].strength>20)  p[ul].x-=5;
        if((c!=ul-1)&&p[c].x>35&&p[ul-1].strength>20) {p[ul-1].x-=7; p[ul-1].y-=2;}
        if((c!=ul-2)&&p[c].x>38&&p[ul-2].strength>20) p[ul-2].x-=9;
        if((c!=ul-3)&&p[c].x>35&&p[ul-3].strength>20) {p[ul-3].x-=7; p[ul-1].y+=2;}
        if((c!=ul-4)&&p[c].x>23&&p[ul-4].strength>20) p[ul-4].x-=10;
        if((c!=ul-5)&&p[c].x>23&&p[ul-5].strength>20) p[ul-5].x-=10;
        if((c!=ul-6)&&p[c].x>23&&p[ul-6].strength>20) {p[ul-6].x-=2; p[ul-1].y-=2;}
        if((c!=ul-7)&&p[c].x>25&&p[ul-7].strength>20) p[ul-7].x-=3;
        if((c!=ul-8)&&p[c].x>25&&p[ul-8].strength>20) p[ul-8].x-=3;
        if((c!=ul-9)&&p[c].x>25&&p[ul-9].strength>20) {p[ul-9].x-=2; p[ul-1].y+=2;}
        if((c!=ul-10)&&p[c].x>15&&p[ul-10].strength>20) p[ul-10].x-=3;
      }
      if(p[0].x<55&&p[0].x>35)
      { if((c!=ul)&&p[c].x>45&&p[ul].strength>20) p[ul].x-=5;
        if((c!=ul-1)&&p[c].x>35&&p[ul-1].strength>20) {p[ul-1].x-=7; p[ul-1].y-=2;}
        if((c!=ul-2)&&p[c].x>38&&p[ul-2].strength>20) p[ul-2].x-=9;
        if((c!=ul-3)&&p[c].x>35&&p[ul-3].strength>20) {p[ul-3].x-=7; p[ul-1].y+=2; }
        if((c!=ul-4)&&p[c].x>23&&p[ul-4].strength>20) p[ul-4].x-=10;
        if((c!=ul-5)&&p[c].x>23&&p[ul-5].strength>20) p[ul-5].x-=10;
        if((c!=ul-6)&&p[c].x>23&&p[ul-6].strength>20) {p[ul-6].x-=2; p[ul-1].y-=2;}
      }
     if(p[0].x<35)
     { if((c!=ul)&&p[c].x>45&&p[ul].strength>20) p[ul].x-=5;
       if((c!=ul-1)&&p[c].x>35&&p[ul-1].strength>20) {p[ul-1].x-=7; p[ul-1].y-=2;}
       if((c!=ul-2)&&p[c].x>38&&p[ul-2].strength>20) p[ul-2].x-=9;
       if((c!=ul-3)&&p[c].x>35&&p[ul-3].strength>20) {p[ul-3].x-=7; p[ul-1].y+=2;  }
       if((c!=ul-4)&&p[c].x>23&&p[ul-4].strength>20) p[ul-4].x-=10;
       if((c!=ul-5)&&p[c].x>23&&p[ul-5].strength>20) p[ul-5].x-=10;
     }
    }

    void manmark(struct player *p)
    { if((poss(p)>ul||poss(p)<ll)&&poss(p)!=0)
       { for(int i=1; i<23; i++)
          { if(i>=ll&&i<=ul) continue;
            else if(p[i].x<40)
             { for(int j=ll; j<=ul; j++)
                if((p[j].x>p[0].x&&p[j].x<p[i].x)||(p[j].x<p[0].x&&p[j].x>p[i].x))
                 { float m=(p[i].y-p[0].y)/(1.0*p[i].x-p[0].x);
                   p[j].x=int((m*p[j].y+p[j].x-m*p[0].y+p[0].x)/2);
                   p[j].y=int((m*p[j].y+p[j].x+m*p[0].y-p[0].x)/2);
                 }
             }
          }
       }
    }

    void shotblock(struct player *p)
    { int c=poss(p);
       if(p[c].y<20)
        { int n=near_p(p,0);
           p[n].x=p[0].x-1;
           p[n].y=p[0].y;
          n=near_p(p,n);
           p[n].x=p[0].x-1;
           p[n].y=p[0].y+1;
        }
       else if(p[c].y>30)
        { int n=near_p(p,0);
           p[n].x=p[0].x-1;
           p[n].y=p[0].y;
          n=near_p(p,n);
           p[n].x=p[0].x-1;
           p[n].y=p[0].y-1;
        }
       else
        { int n=near_p(p,0);
           p[n].x=p[0].x-1;
           p[n].y=p[0].y;
          n=near_p(p,n);
           p[n].x=p[0].x-1;
           p[n].y=p[0].y+1;
          p[ll].x=p[0].x-1;
          p[ll].x=p[0].y-1;
        }
    }

    void shotatgoal(struct player *p)
    { int c=poss(p);
      if(p[c].y<25)
       { p[0].x=99;
         p[0].y=40;
       }
      else
       { p[0].x=99;
         p[0].y=10;
       }
    }

    int pmid(struct player *p)
    { for(int j=1; j<12; j++)
       if(p[j].x>30&&p[j].x<45)
        return j;
      return 0;
    }

};

