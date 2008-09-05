#include"api.h"
#include<stdlib.h>
//using namespace std;

int find_x(char arena[15][15])
{
     int i,j,x=-1;
     for(i=0;i<15;i++)
       for(j=0;j<15;j++)
	 if(arena[i][j]=='P')
	 {
	  x=i;
	  break;
	 }

     return x;
}

int find_y(char arena[15][15])
{
     int i,j,y=-1;
     for(i=0;i<15;i++)
       for(j=0;j<15;j++)
	 if(arena[i][j]=='P')
	 {
	  y=j;
	  break;
	 }
     return y;
}

int main()
{
 int n=-1,pos[255][2],i,j,l=0,t[2],f=0,sp=0,currx,curry,starting=0,temptation=0,tp=0,current_x,current_y;
 struct arenahistory prev;
 struct input in;
 struct reply out;

 in=getparameters();

 current_x=find_x(in.arena);
 current_y=find_y(in.arena);
 
 
 
 for(i=0;i<15;i++)                                          //searching for present position of O
		  for(j=0;j<15;j++)
				   if(in.arena[i][j]=='O'||in.arena[i][j]=='@'||in.arena[i][j]=='$')
				   {
				    pos[0][0]=i;
				    pos[0][1]=j;
				    l++;
				    currx=i;                //present posn of O
				    curry=j;
				    break;
				   }

 for(n=1;starting==0;n++)                                             //collecting last n moves of O
 {
     prev.arenasituation(n);
			    
                if(prev.arena[3][7]=='P'&&prev.arena[11][7]=='O')
                {
                 starting=1;
                }

			     for(i=0;i<15;i++)
					     for(j=0;j<15;j++)
					     {
							      if(prev.arena[i][j]=='O')
							      {
							       pos[l][0]=i;
							       pos[l][1]=j;
							       l++;
							      }
					     }
 }


 for(i=0;i<l/2;i++)                           //reversing the array
 {
		    t[0]=pos[l-i-1][0];t[1]=pos[l-i-1][1];
		    pos[l-i-1][0]=pos[i][0];pos[l-i-1][1]=pos[i][1];
		    pos[i][0]=t[0];pos[i][1]=t[1];
 }


 for(i=0;i<15;i++)                                //if opponent is at safety point
 {
		  for(j=0;j<15;j++)
		  {
				   if(in.arena[i][j]=='@')
				   {
				    out.offspellused=1;
				    out.xspellfinal=i;
				    out.yspellfinal=j;
				    sp=1;
				    break;
				   }
		  }
		  if(sp==1)
		  break;
 }


 if(sp==0)                                       //if opponent is not at safety point
 {
	  if(in.myspellpower>=1200)
	  {
					if(in.oppagility!=0&&in.oppspellpower!=0)//agility!=0,spell power!=0,stupefy at temptation,pattern,current position
					{
     						  {             //checking for player at temptation diagonal
							if(currx==4&&curry==10)
							temptation=1;
							else if(currx==3&&curry==11)
							temptation=1;
							else if(currx==2&&curry==12)
							temptation=1;
							else if(currx==1&&curry==13)
							temptation=1;
							else if(currx==0&&curry==14)
							temptation=1;

							else if(currx==10&&curry==4)
							temptation=2;
							else if(currx==11&&curry==3)
							temptation=2;
							else if(currx==12&&curry==2)
							temptation=2;
							else if(currx==13&&curry==1)
							temptation=2;
							else if(currx==14&&curry==0)
							temptation=2;
						       }

						       if(temptation==1&&in.arena[0][14]=='T')//player at upper temptation diagonal
						       {
							out.xspellfinal=0;
							out.yspellfinal=14;
							out.offspellused=12;
						       }
						       else if(temptation==2&&in.arena[14][0]=='T')//player at lower temptation diagonal
						       {
							out.xspellfinal=14;
							out.yspellfinal=0;
							out.offspellused=12;
						       }

						       else//player not at temptation diagonal
						       {
								    for(i=l-2;i>=0;i--)                    //pattern testing
								    {
										if(pos[l-1][0]==pos[i][0]&&pos[l-1][1]==pos[i][1])
										{
										f=0;
										    if(i==l-2)   //aa
										    {
										     f=1;
										    }
										    else
											      for(j=l-2;j>i;j--)
											      {
												      if( pos[j][0]!= pos[i-((l-1)-j)][0]||pos[j][1]!= pos[i-((l-1)-j)][1] )
												      {
												       f=1;
												       break;
												      }
											      }

										    if(f==0)
										    {
										     n=i+1;
										    }
										}
								    }

								    if(n!=-1)                 //pattern found
								    {
										//cout<<pos[n][0]<<pos[n][1];
										out.xspellfinal=pos[n][0];
										out.yspellfinal=pos[n][1];
										out.offspellused=12;
								    }

								    else                //pattern not found, hit at current position
								    {
								    out.xspellfinal=currx;
								    out.yspellfinal=curry;
								    out.offspellused=12;
								    }
						       }
					}

					else if(in.oppagility==0&&in.oppspellpower==0)//agility=0,spellpower=0,avada kedavra at currx,y
					{
					 //AVADA KEDAVRA!!!!!!!!!!!!!!!!!!!!!
					 out.xspellfinal=currx;
					 out.yspellfinal=curry;
					 out.offspellused=13;
					}

					else if(in.oppagility==0&&in.oppspellpower!=0)//rictumsempra, reducing spell power to 0*********************
					{
					 out.xspellfinal=currx;
					 out.yspellfinal=curry;
					 out.offspellused=9;
					}

					else if(in.oppagility!=0&&in.oppspellpower==0)//agility!=0,spellpower=0, jelly legs, xy same as 1st case
					{
					     {             //checking for player at temptation diagonal
							if(currx==4&&curry==10)
							temptation=1;
							else if(currx==3&&curry==11)
							temptation=1;
							else if(currx==2&&curry==12)
							temptation=1;
							else if(currx==1&&curry==13)
							temptation=1;
							else if(currx==0&&curry==14)
							temptation=1;

							else if(currx==10&&curry==4)
							temptation=2;
							else if(currx==11&&curry==3)
							temptation=2;
							else if(currx==12&&curry==2)
							temptation=2;
							else if(currx==13&&curry==1)
							temptation=2;
							else if(currx==14&&curry==0)
							temptation=2;
						       }

						       if(temptation==1&&in.arena[0][14]=='T')//player at upper temptation diagonal
						       {
							out.xspellfinal=0;
							out.yspellfinal=14;
							out.offspellused=8;
						       }
						       else if(temptation==2&&in.arena[14][0]=='T')//player at lower temptation diagonal
						       {
							out.xspellfinal=14;
							out.yspellfinal=0;
							out.offspellused=8;
						       }

						       else//player not at temptation diagonal
						       {
                                    n=-1;
								    for(i=l-2;i>=0;i--)                    //pattern testing
								    {
										if(pos[l-1][0]==pos[i][0]&&pos[l-1][1]==pos[i][1])
										{
										f=0;
										    if(i==l-2)   //aa
										    {
										     f=1;
										    }
										    else
											      for(j=l-2;j>i;j--)
											      {
												      if( pos[j][0]!= pos[i-((l-1)-j)][0]||pos[j][1]!= pos[i-((l-1)-j)][1] )
												      {
												       f=1;
												       break;
												      }
											      }

										    if(f==0)
										    {
										     n=i+1;
										    }
										}
								    }

								    if(n!=-1)                 //pattern found
								    {
										//cout<<pos[n][0]<<pos[n][1];
										out.xspellfinal=pos[n][0];
										out.yspellfinal=pos[n][1];
										out.offspellused=8;
								    }

								    else                //pattern not found, hit at current position
								    {
								    out.xspellfinal=currx;
								    out.yspellfinal=curry;
								    out.offspellused=8;
								    }
						       }
					}
	  }
	  
      else if(in.myspellpower<200) //go to temptation****************
	  {
	   tp=1;
	   out.offspellused=0;
	  }
	  
      else if(in.myspellpower<1200)
	  {
			if(in.oppagility!=0&&in.oppspellpower!=0)// no attack, wait for O's spellpower n agility to be 0
			{
				out.offspellused=0;
			}
			else if(in.oppagility==0&&in.oppspellpower==0)
			{
				   if(in.myspellpower>=750)//Avada Kedavra!!!!!!!!!!!
				   {
				    out.xspellfinal=currx;
				    out.yspellfinal=curry;
				    out.offspellused=13;
				   }
				   else
				   {
				    tp=1;//go to temptation*****************************
				    out.offspellused=0;
				   }

			}
			else if(in.oppagility==0&&in.oppspellpower!=0)//rictumsempra
			{
			  out.xspellfinal=currx;
			  out.yspellfinal=curry;
			  out.offspellused=9;
			}
			else if(in.oppagility!=0&&in.oppspellpower==0)//if O has stopped moving to save his agility
			{
				struct arenahistory arena1,arena2,arena3;
				int oppx1,oppy1,oppx2,oppy2,oppx3,oppy3;
				arena1.arenasituation(1);
				arena2.arenasituation(2);
				arena3.arenasituation(3);

				for(i=0;i<15;i++)
					for(j=0;j<15;j++)
						if(arena1.arena[i][j]=='O')
						{
						 oppx1=i;
						 oppy1=j;
						}
				for(i=0;i<15;i++)
					for(j=0;j<15;j++)
						if(arena2.arena[i][j]=='O')
						{
						 oppx2=i;
						 oppy2=j;
						}
				for(i=0;i<15;i++)
					for(j=0;j<15;j++)
						if(arena3.arena[i][j]=='O')
						{
						 oppx3=i;
						 oppy3=j;
						}

				if(oppx1==oppx2&&oppx2==oppx3&&oppy1==oppy2&&oppy2==oppy3)//if O has stopped moving to  his agility
				{
				 out.xspellfinal=oppx1;
				 out.yspellfinal=oppy1;
				 out.offspellused=12;
				}
				else
				out.offspellused=0;
            }      
      }
 }


  int p=0;
  if(in.myagility!=0)
  {
	   if(in.oppspellpower==0)
	   {
	     //Don't move if opponent's spell power is zero (save your agility)
	     out.xmovefinal=current_x;
	     out.ymovefinal=current_y;
	   }

	   if(!(in.spellcasted>=1&&in.spellcasted<=17))
	   {
	     //If no spell casted by opponent, donot move
	     out.xmovefinal=current_x;
	     out.ymovefinal=current_y;
	   }

      

	   if(in.arena[current_x][current_y]=='*')
	   {
		out.xmovefinal=current_x;
		out.ymovefinal=current_y;
	   }

       if(tp==1)//we moving towards 'T'
	   {

	     if(in.arena[0][14]=='T' && in.arena[14][0]=='T')
	     {

	       int flag1=0;

	       if(current_x>=5 && current_x<=9 && current_y>=4 && current_y<=10)//if inside the middle box containing boulders
	       {
		 for(i=current_y; i<=11; i++)
		 {
		   if(in.arena[current_x][i]=='B')
		     {
		       flag1=1;
		       break;
		     }
		 }

		 if(flag1==0)
		 {
		   out.xmovefinal=current_x;
		   out.ymovefinal=11;
		 }

		 flag1=0;

		 for(i=current_y; i<=3; i--)
		 {
		   if(in.arena[current_x][i]=='B')
		     {
		       flag1=1;
		       break;
		     }
		 }

                 if(flag1==0)
                 {
                   out.xmovefinal=current_x;
                   out.ymovefinal=3;
                 }            
                 
                 
               }
               
               else if(current_x<=4 && current_x>0 && current_x+current_y==14)//upper temptation diagonal
               {
                 out.xmovefinal=0;
                 out.ymovefinal=14;
               }
               
               else if(current_x>=10 && current_x<14 && current_x+current_y==14)//lower temptation diagonal
               {
                 out.xmovefinal=14;
                 out.ymovefinal=0;
               } 
                   
               else //if out of the middle box containing boulders
               {
                 if(current_x<=4)
                 {
                   if(current_x==2)
                   {
                     out.xmovefinal=2;
                     out.ymovefinal=12;                
                   }
                   if(current_x==3)
                   {
                     out.xmovefinal=3;
                     out.ymovefinal=11;                
                   }
                   if(current_x==4)
                   {
                     out.xmovefinal=4;
                     out.ymovefinal=10;                
                   }                
                 }
                 
                 if(current_x>=10)
                 {
                   if(current_x==10)
                   {
                     out.xmovefinal=10;
                     out.ymovefinal=4;                
                   }
                   if(current_x==11)
                   {
                     out.xmovefinal=11;
                     out.ymovefinal=3;                
                   }
                   if(current_x==12)
                   {
                     out.xmovefinal=12;
                     out.ymovefinal=2;                
                   }                
                 }
                 
                 else
                 {
                   if(current_y<=3)
                   {
                     if(current_y==3)
                     {
                       out.xmovefinal=11;
                       out.ymovefinal=3;                
                     }
                     if(current_y==2)
                     {
                       out.xmovefinal=12;
                       out.ymovefinal=2;                
                     }
                     if(current_y==1)
                     {
                       out.xmovefinal=13;
                       out.ymovefinal=1;                
                     }
                     if(current_y==0)
                     {
                       out.xmovefinal=current_x;
                       out.ymovefinal=1;                
                     }                                                
                   }
                   if(current_y>=11)
                   {
                     if(current_y==11)
                     {
                       out.xmovefinal=3;
                       out.ymovefinal=11;                
                     }
                     if(current_y==12)
                     {
                       out.xmovefinal=2;
                       out.ymovefinal=12;                
                     }
                     if(current_y==13)
                     {
                       out.xmovefinal=1;
                       out.ymovefinal=13;                
                     }
                     if(current_y==14)
                     {
                       out.xmovefinal=current_x;
                       out.ymovefinal=13;                
                     }                 
                   }                                 
                 } 
                                
               }         
             }
             
             else if(in.arena[0][14]!='T' && in.arena[14][0]=='T')//go to lower 'T'
             {
               if(current_x==0 && current_y==14)
               {
                 out.xmovefinal=4;
                 out.ymovefinal=10;
               }
               if(current_x==4 && current_y==10)
               {
                 out.xmovefinal=4;
                 out.ymovefinal=3;
               }                
               if(current_x==4 && current_y==3)
               {
                 out.xmovefinal=11;
                 out.ymovefinal=3;
               }                
               if(current_x==11 && current_y==3)
               {
                 out.xmovefinal=14;
                 out.ymovefinal=0;
               }                                
             }
             
             else if(in.arena[0][14]=='T' && in.arena[14][0]!='T')//go to upper 'T'
             {
               if(current_x==14 && current_y==0)
               {
                 out.xmovefinal=11;
                 out.ymovefinal=3;
               }
               if(current_x==11 && current_y==3)
               {
                 out.xmovefinal=4;
                 out.ymovefinal=3;
               }                
               if(current_x==4 && current_y==3)
               {
                 out.xmovefinal=4;
                 out.ymovefinal=10;
               }                
               if(current_x==4 && current_y==10)
               {
                 out.xmovefinal=0;
                 out.ymovefinal=14;
               }  
             }                                                                                    
           }


	   if((in.arena[4][10]=='O') || (in.arena[3][11]=='O') || (in.arena[2][12]=='O') || (in.arena[1][13]=='O') || (in.arena[10][4]=='O') || (in.arena[11][3]=='O') || (in.arena[12][2]=='O') || (in.arena[13][1]=='O'))//if opponent is on 'T' diagonal, move in the respective upper/lower triangle to get a straight unblocked line
	   {
	     if(((in.arena[4][10]=='O') || (in.arena[3][11]=='O') || (in.arena[2][12]=='O') || (in.arena[1][13]=='O')) && (current_y<14-current_x))
	     {
		 if(current_x==1)
		 {
		   out.xmovefinal=1;
		   out.ymovefinal=13;
		 }
		 if(current_x==2)
		 {
		   out.xmovefinal=2;
		   out.ymovefinal=13;
		 }
		 if(current_x==3)
		 {
		   out.xmovefinal=3;
		   out.ymovefinal=12;
		 }
		 if(current_x==4)
		 {
		   out.xmovefinal=4;
		   out.ymovefinal=11;
		 }
		 if(current_x==10)
		 {
		   out.xmovefinal=10;
		   out.ymovefinal=4;
		 }
		 if(current_x==11)
		 {
		   out.xmovefinal=11;
		   out.ymovefinal=3;
		 }
		 if(current_x==12)
		 {
		   out.xmovefinal=12;
		   out.ymovefinal=2;
		 }
		 if(current_x==13)
		 {
		   out.xmovefinal=13;
		   out.ymovefinal=1;
		 }
		 if(current_x==7)
		 {
		   out.xmovefinal=7;
		   out.ymovefinal=7;
		 }
		 if(current_x==6)
		 {
		   out.xmovefinal=6;
		   out.ymovefinal=8;
		 }
		 if(current_x==5)
		 {
		   if(current_y==1)
		   {
		     out.xmovefinal=13;
		     out.ymovefinal=1;
		   }
		   if(current_y==2)
		   {
		     out.xmovefinal=12;
		     out.ymovefinal=2;
		   }
		   if(current_y==3)
		   {
		     out.xmovefinal=11;
		     out.ymovefinal=3;
		   }
		   if(current_y==4)
		   {
		     out.xmovefinal=8;
		     out.ymovefinal=7;
		   }
		   if(current_y==5)
		   {
		     out.xmovefinal=7;
		     out.ymovefinal=7;
		   }
		   if(current_y==6)
		   {
		     out.xmovefinal=8;
		     out.ymovefinal=6;
		   }
		   if(current_y==7)
		   {
		     out.xmovefinal=7;
		     out.ymovefinal=7;
		   }
		 }
		 if(current_x==8)
		 {
		   if(current_y==0)
		   {
		     out.xmovefinal=11;
		     out.ymovefinal=3;
		   }
		   if(current_y==1)
		   {
		     out.xmovefinal=13;
		     out.ymovefinal=1;
		   }
		   if(current_y==2)
		   {
		     out.xmovefinal=12;
		     out.ymovefinal=2;
		   }
		   if(current_y==3)
		   {
		     out.xmovefinal=11;
		     out.ymovefinal=3;
		   }
		 }
		 if(current_x==9)
		 {
		   if(current_y==0)
		   {
		     out.xmovefinal=12;
		     out.ymovefinal=3;
		   }
		   if(current_y==1)
		   {
		     out.xmovefinal=13;
		     out.ymovefinal=1;
		   }
		   if(current_y==2)
		   {
		     out.xmovefinal=12;
		     out.ymovefinal=2;
		   }
		   if(current_y==3)
		   {
		     out.xmovefinal=11;
		     out.ymovefinal=3;
		   }
          }
	      }

	     if(((in.arena[10][4]=='O') || (in.arena[11][3]=='O') || (in.arena[12][2]=='O') || (in.arena[13][1]=='O')) && (current_y>14-current_x))
	     {
		 if(current_x==1)
		 {
		   out.xmovefinal=1;
		   out.ymovefinal=13;
		 }
		 if(current_x==2)
		 {
		   out.xmovefinal=2;
		   out.ymovefinal=12;
		 }
		 if(current_x==3)
		 {
		   out.xmovefinal=3;
		   out.ymovefinal=11;
		 }
		 if(current_x==4)
		 {
		   out.xmovefinal=4;
		   out.ymovefinal=10;
		 }
		 if(current_x==10)
		 {
		   out.xmovefinal=10;
		   out.ymovefinal=4;
		 }
		 if(current_x==11)
		 {
		   out.xmovefinal=11;
		   out.ymovefinal=3;
		 }
		 if(current_x==12)
		 {
		   out.xmovefinal=12;
		   out.ymovefinal=2;
		 }
		 if(current_x==13)
		 {
		   out.xmovefinal=13;
		   out.ymovefinal=1;
		 }
		 if(current_x==7)
		 {
		   out.xmovefinal=7;
		   out.ymovefinal=7;
		 }
		 if(current_x==8)
		 {
		   out.xmovefinal=8;
		   out.ymovefinal=6;
		 }
		 if(current_x==9)
		 {
		   if(current_y==7)
		   {
		     out.xmovefinal=8;
		     out.ymovefinal=6;
		   }
		   if(current_y==8)
		   {
		     out.xmovefinal=6;
		     out.ymovefinal=8;
		   }
		   if(current_y==9)
		   {
		     out.xmovefinal=7;
		     out.ymovefinal=7;
		   }
		   if(current_y==10)
		   {
		     out.xmovefinal=6;
		     out.ymovefinal=7;
		   }
		   if(current_y==11)
		   {
		     out.xmovefinal=6;
		     out.ymovefinal=8;
		   }
		   if(current_y==12)
		   {
		     out.xmovefinal=2;
		     out.ymovefinal=12;
		   }
		   if(current_y==13)
		   {
		     out.xmovefinal=1;
		     out.ymovefinal=13;
		   }
		 }
		 if(current_x==6)
		 {
		   if(current_y==11)
		   {
		     out.xmovefinal=3;
		     out.ymovefinal=11;
		   }
		   if(current_y==12)
		   {
		     out.xmovefinal=2;
		     out.ymovefinal=12;
		   }
		   if(current_y==13)
		   {
		     out.xmovefinal=1;
		     out.ymovefinal=13;
		   }
		   if(current_y==14)
		   {
		     out.xmovefinal=3;
		     out.ymovefinal=11;
		   }
		 }
		 if(current_x==5)
		 {
		   if(current_y==11)
		   {
		     out.xmovefinal=3;
		     out.ymovefinal=11;
		   }
		   if(current_y==12)
		   {
		     out.xmovefinal=2;
		     out.ymovefinal=12;
		   }
		   if(current_y==13)
		   {
		     out.xmovefinal=1;
		     out.ymovefinal=13;
		   }
		   if(current_y==14)
		   {
		     out.xmovefinal=2;
		     out.ymovefinal=11;
		   }
		 }
	     }
	   }

	      
           
           else//random motion
           {
               do
               {
                 randomize();
                 int flag,temp;
                 struct arenahistory obj1;
                 do
                 {
                   flag=random(8);
                                   
                   int x1,y1,x2,y2;
                   obj1.arenasituation(1);
     
                   x1=current_x;
                   y1=current_y;
                   x2=find_x(obj1.arena);
                   y2=find_y(obj1.arena);
     
      
                   if(x1-x2==-1 && y1-y2==0)temp=0;
                   if(x1-x2==-1 && y1-y2==1)temp=1;
                   if(x1-x2==0 && y1-y2==1)temp=2;
                   if(x1-x2==1 && y1-y2==1)temp=3;
                   if(x1-x2==1 && y1-y2==0)temp=4;
                   if(x1-x2==1 && y1-y2==-1)temp=5;
                   if(x1-x2==0 && y1-y2==-1)temp=6;
                   if(x1-x2==-1 && y1-y2==-1)temp=7;
                   //temp is the previous direction
                    
                 }while(flag==temp);
                 
                 
                 if(flag==0){
                              out.xmovefinal=current_x-1;
                              out.ymovefinal=current_y; 
                            }
                 if(flag==1){
                              out.xmovefinal=current_x-1;
                              out.ymovefinal=current_y+1; 
                            }
                 if(flag==2){
                              out.xmovefinal=current_x;
                              out.ymovefinal=current_y+1; 
                            }
                 if(flag==3){
                              out.xmovefinal=current_x+1;
                              out.ymovefinal=current_y+1; 
                            }
                 if(flag==4){
                              out.xmovefinal=current_x+1;
                              out.ymovefinal=current_y; 
                            }
                 if(flag==5){
                              out.xmovefinal=current_x+1;
                              out.ymovefinal=current_y-1; 
                            }  
                 if(flag==6){
                              out.xmovefinal=current_x;
                              out.ymovefinal=current_y-1; 
                            }
                 if(flag==7){
                              out.xmovefinal=current_x-1;
                              out.ymovefinal=current_y-1; 
                            }
               
                 if(in.arena[out.xmovefinal][out.ymovefinal]=='X')p=1;
                 if(in.arena[out.xmovefinal][out.ymovefinal]=='B')p=1;
                 if(in.arena[out.xmovefinal][out.ymovefinal]=='O')p=1;
                 if(in.arena[out.xmovefinal][out.ymovefinal]=='D')p=1;
                 else p=0;
                 
               }while(p==1);
           }
           out.defspellused=0;
  }
  else
  {
    if((in.spellcasted>=1 && in.spellcasted<=5) || (in.spellcasted==11))
    {
      out.defspellused=in.spellcasted;
    }
    if((in.spellcasted==7) || (in.spellcasted==9) || (in.spellcasted==12) || (in.spellcasted==13) || (in.spellcasted==14) || (in.spellcasted==15) || (in.spellcasted==17))
    {
      out.defspellused=16;                       
    }                                
  }

 saveparameters(out);
 return 0;
}
