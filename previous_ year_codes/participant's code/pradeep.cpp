#include"api.h"
void main()
{
struct input i;
void getparameters(struct input i);
struct reply r;

int a=2,b=8,k,l,j,p,q,u;
if(i.myagility<i.myspellpower)
{
switch(i.spellcasted)
{
 case 1:
 r.defspellused=1;
 break;
 case 2:
 r.defspellused=2;
 break;
 case 3:
 r.defspellused=3;
 break;
 case 4:
 r.defspellused=4;
 break;
 case 5:
 r.defspellused=5;
 break;
 case 6:
 r.defspellused=16;
 break;
 case 7:
 r.defspellused=16;
 break;
 case 8:
 r.defspellused=17;
 break;

 case 9:
 r.defspellused=11;
 break;
 case 10:
 r.defspellused=16;
 break;
case 11:
r.defspellused=11;
break;
case 12:
r.defspellused=16;
break;
case 13:
r.defspellused=16;
break;
case 14:
r.defspellused=16;
break;
case 15:
r.defspellused=16;
break;
case 16:
r.defspellused=16;
break;
case 17:
r.defspellused=17;
break;
}
}
r.offspellused=i.spellcasted;
if(i.oppspellpower==0)
{
if((i.opphealth<3000)&&(i.opphealth>2000))
i.spellcasted=14;
if((i.opphealth<2000)&&(i.opphealth>1000))
i.spellcasted=17;
if((i.opphealth<1000)&&(i.opphealth>500))
i.spellcasted=11;
}


for(k=0;k<15;k++)
for(l=0;l<15;l++)
if(i.arena[k][l]=='O')
{k=p;l=q;
if(k<13&&l<13)
{r.xspellfinal=k++;
r.xspellfinal=l++;}
if(k<10&&l<15)
{r.xspellfinal=k--;
r.xspellfinal=l;}

if(k<13)
{r.xspellfinal=k--;
r.xspellfinal=l++;}
}
if(i.myagility>i.myspellpower)
{
if(a==3&&b==7)
{b++;a++;}
if(a==3&&b==9)
{b++;a++;}
if(a==4&&b==10)
{b++;a++;}
if(a==5&&b==11)
{b++;a++;}
if(a==6&&b==12)
b++;
if(a==6&&b==13)
b++;
if(a==6&&b==14)
{b=b-2;a=a+2;}
if(a==8&&b==12)
a=a+2;
if(a==10&&b==12)
b=b-2;

if(a==10&&b==10)
{b=b-2;a=a+2;}
if(a==12&&b==8)
b--;
if(a==12&&b==7)
b=b-3;
if(a==12&&b==4)
{b--;a--;}
if(a==11&&b==3)
b=b-2;
if(a==11&&b==1)
a=a-2;
if(a==9&&b==1)
{b--;a--;}
if(a==8&&b==0)
a=a-2;
if(a==6&&b==0)
b=b+3;
if(a==6&&b==3)
{a++;b++;}
if(a==7&&b==4)
{a--;b=b+2;}
if(a==6&&b==6)
{a--;}

}
r.xmovefinal=a;
r.ymovefinal=b;

if(i.myhealth<500)
{
    if(i.opphealth<500)
    u++;
    else
    {
      if(i.myagility>400)
      { r.xmovefinal=0;
	r.ymovefinal=14;}
      else
      {
       if(i.myspellpower>200)
       r.offspellused= 5;  }
    }


}


if(i.oppagility==0)
{r.xspellfinal=p;
r.yspellfinal=q;}

if(p==8&&q==12)
{r.offspellused=17;
r.xmovefinal=7;
r.ymovefinal=13;

}
if(p==10&&q==2)
{r.offspellused=17;
r.xmovefinal=9;
r.ymovefinal=1;

}

if(p==3&&q==12)
{r.offspellused=7;
r.xmovefinal=2;
r.ymovefinal=9; }

if(p==5&&q==0)
{r.offspellused=7;
r.xmovefinal=7;
r.ymovefinal=0; }

if(p==7&&q==10)
{r.offspellused=17;
r.xmovefinal=6;
r.ymovefinal=10;}

if(p==5&&q==5)
{r.offspellused=17;
r.xmovefinal=6;
r.ymovefinal=6;

}


if(i.oppspellpower==0)
{
r.offspellused=17;
r.xmovefinal=p+2;
r.ymovefinal=q+2;

}
void saveparameters(struct reply r);
}






























/*movement
if((x>0)&&(y>0))
{
 do
 {
 x++;
 y--;
 } while(y> 0);
 }

 if(y==0)
 {
  while(x<=13)
  {
   x++;y++;
   }

   }

 if(x==13)
 {
  while(y<=9)
  {
   y++;
   }
   }

   if(y==9)
   {
   while(x>=2)
   {
   x--;y--;
   }

  }       */



