int player(int team)
{ 
    int l1,u1,l2,u2,mystr=0,myno=-1,oppstr=0,phitterp=-1,i;
    char Dee,dee;
    int withme(int,int);
    int withopp(int);
    int atemptyspot();
    void check(int);
   struct region{int lx,ly,ux,uy}g,G,D,d;//to determine the limits of goal and dee 
   
   if(team==0)
    {l1=1;u1=11;l2=12;u2=22;      //to mark the limits of goals depending on the team
      g.lx=0;g.ly=20;g.ux=4;g.uy=30;
      d.lx=0;d.ly=10;d.ux=20;d.uy=40;
      G.lx=100;G.ly=20;G.ux=96;G.uy=30;
      D.lx=100;D.ly=20;D.ux=81;D.uy=40;
      Dee='D';
      dee='d';}
      
    else
    {l1=12;u1=22;l2=1;u2=11;
      g.lx=100;g.ly=20;g.ux=96;g.uy=30;
      d.lx=100;d.ly=10;d.ux=81;d.uy=40;
      G.lx=0;G.ly=20;G.ux=4;G.uy=30;
      D.lx=0;D.ly=10;D.ux=40;D.uy=20;
      Dee='d';
      dee='D';}
      
    for(i=l1;i<=u1;i++)
     {
       if ((global[i].x==global[0].x)&&(localp[i].y==local[0].y))
        {  if(localp[i].strength>mystr)
             {mystr=localp[i].strength;
               myno=i;}\\end of if
        }//to see whether the coordinates of player matches with the ball                 
        }//end of loop to find whether any of my player coincides with the coordinates of the ball 
          //and to find the player with max strength
        
    for(i=l2;i<=u2;i++)
     {
       if ((localp[i].x==localp[0].x)&&(localp[i].y==local[0].y))
        {  if(localp[i].strength>oppstr)
             {oppstr=localp[i].strength;
             }//end of if
        }//to see whether the coordinates of player matches with the ball                 
        }//end of loop to find whether any of oppositions player coincides with the coordinates of the ball
        
        
    
    /*checking different situations and calling appropriate fns*/
    
    if(((myno!=-1)&&(oppstr==0))||((myno!=-1)&&(oppstr<=mystr))) 
     phitterp=withme(1,-1);      //if ball is with me only or if both teams players are present and my strength is more than opponent
                                   //passing 1 to tell that control is not coming from withopp or atemptyslot fns and -1 is phitter no
                                   
     else if (((myno==-1)&&(oppstr!=0))||((myno!=-1)&&(oppstr>mystr)))
         phitterp=withopp(oppstr);  //if opposition has the possession of the ball and passing the strength of his max strength player
         
     else if((myno==-1)&&(oppstr==0))
         phitterp=atemptyspot();    //if nobody is present or the opposition player has 0 strength
         
     check();//to move my player to ball in case it is at empty slot or near goal in case ball is in my dee
     
     return phitterp;
         
  
  }//end of player fn
  
  
  
  int withme(int execute,int phitterf1)
  {
      int hit=0,phitterf1=0,phitterf1str=-1,powerreqball,ulimit=0,llimit;
      if (execute)
       {
         for(i=l1;i<=u1;i++)
          {
            if(global[i].strength-(preqp(global[i].x,global[i].y,global[0].x,global[0].y))>phitterf1str)
             {phitterf1=i;
               phitterf1str=global[i].strength-(preqp(global[i].x,global[i].y,global[0].x,global[0].y));
             }
          }
         global[phitterf1].strength=phitterf1str;
       }   //end of if to move my player with the highest strength after reaching the ball and this is done only in case
            //my player has the possession of the ball
      
      
      if(fieldarray[global[0].x][global[0].y]!=Dee)//if condns to check that the ball is in the limit (x) of dee but not in opponents dee
      {
        if ((global[0].x<=D.uy)&&(global[0].x>=D.ly))
         {
           if(preqpb(global[0].x,G.ux,0,0)<=global[phitterf1].strength)
            goto insidedee;    // if player has enough strength to hit the ball inside the goal so send the control 
                                //in the case when ball is in the goal
            
            powerreqball=preqpb(global[0].x,D.ux,0,0);
             
            for(j=global[0].y,ulimit=0;(j<=D.uy)||(powerreqball<global[phitterf1].strength);)
             {
               ulimit=j;
               j++;
               powerreqball=(global[0].x,D.ux,global[0].y,j);
             }\\end of for to find the max right side which the player can hit
             
            
            powerball=preqpb(global[0].x,D.ux,0,0);
             
            for(j=global[0].y,llimit=0;(j>=D.ly)||(powerreqball<global[phitterf1].strength);)
             {
               llimit=j;
               j--;
               powerreqball=(global[0].x,D.ux,global[0].y,j);
             }//end of for to find the max left side which the player can hit
             
            
         xdiff=D.ux-global[0].x;
         
         for(i=llimit;(i<=ulimit)&&(hit==0);i++) 
          {
           status='f';
            for(validposxp=global[0].x,validposyp=global[0].y;status=='f';)
             {if(validposxp!=D.ux)
               {xdiff>0?validposxp++:validposxp--;}
              
              if(validposyp!=i)validpospy++;
              
              mystrength=-1;oppstrength=-1;
              interrup=0;myno=0;
              pstatus='f';
              
              for(k=l1;k<=u1;k++)
               {interrup++;
                 if(global[k].strength>mystrength)
                  {mystrength=global[k].strength;
                   myno=k;
                  }
               }//to find whether ny of my player interrupts the ball 
               
              
              for(k=l2;k<=u2;k++)
               {interrup++;
                 if(global[k].strength>oppstrength)
                  {oppstrength=global[k].strength;
                   
                  }
               }//to find whether ny of opponents player interrupts the ball
               
             if((validposxp==D.ux)&&(validposyp==i))
               status='R';//if reached inside the dee
               
             else if (interrup>0)
             {status=mystrength>oppstrength?'M':'O';}
             
            }//end of for loop
            
            if(status=='M')
             {pstatus='M';
               ptogetball=myno;}
             )
             
             if(status=='R')
              hit==1;
              
           }//end of for loop to find appropriate position to hit the ball  

    if(hit==1)
     {global[phitterf1].strength-=preqpb(global[0].x,global[0].y,validposx,validposy);
     
       global[0].x=validposxp;
        global[0].y=validposyp;
       return phitterf1;
     }
     
    else if(pstatus=='M')
    {global[phitterf1].strength-=preqpb(global[0].x,global[0].y,global[ptogetball].x,global[ptogetball].y);
     global[0].x=global[ptogetball].x;
     global[0].y=global[ptogetball].y;
     return phitterf1;
    }
    
    else
    {
      for(i=l1;i<=u1;i++)
       {if(global[i].x>global[0].x)
        {if(preqp(global[0].x,global[i].x,0,0)<ptogetballstr)
          {ptogetball=i;
            ptogetballstr=preqp(global[0].x,global[i].x,0,0);
          }
        }
       }
       
      if(ptogetball!=-1)
       {global[0].x=global[ptogetball].x;
        global[0].y=global[ptogetball].y;
        return phitterf1;
        }
        
        global[0].x=global[phitterf1].x;
         return phitterf1;
         
       }
    }//end of if on line 115
    
    }//end of if on line 113       
   
   
   //ball is in the range of goal and is inside opponent's goal
   if((global[0].x<=G.uy)&&(global[0].x>=G.ly)&&(fieldarray[global[0].x][global[0].y]==Dee))
    
    {insidedee:\\label for goto used in previous if 
      global[0].x=G.ux;
       return phitterf1;
    }//end of if case
    
    if(((global[0].x>G.ux)&&(team==0))||((global[0].x<=G.ux)&&(team==1)))
     {
       if(global[0].y>G.uy)
        global[0].y=G.uy;
        
       else 
        global[0].y=G.ul;
        return phitterf1;
     }//end of if 
     
     
     if(((global[0].x<G.ux)&&(team==0)||(global[0].x>G.ux)&&(team==1))&&((global[0].y>G.uy)||(global[0].y<G.uy)))
        {
         ptogetball=-1;ptogetballstr=0;hit=0;
         
         for(i=l1;i<=u1;i++)
          {
           if(((global[i].x>global[0].x)&&(team==0))||((global[i].x<global[0].x)&&(team==1)))
            {
             if(ptogetballstr>preqp(global[0].x,global[0].y,global[i].x,global[i].y))
              {
                ptogetball=i;
                 ptogetballstr=preqp(global[0].x,global[0].y,global[i].x,global[i].y);
              }
             }
            }\\end of for loop 
            if(ptogetball!=-1)
            {
             status='f';
             validposxp=global[0].x;
             validposyp=global[0].y;
             
             while(status=='f')
              {
                if(validposxp!=global[ptogetball].x)
                 {global[ptogetball].x>global[0].x?validposxp++:validposxp--;}
                 
                if(validposyp!=global[ptogetball].y)
                 {global[ptogetball].y>global[0].y?validposyp++:validposyp--;}
                 
                for(i=l2;i<=u2;i++)
                 {
                   if((global[i].x==validposxp)&&(global[i].y==validposy))
                    status='O';
                 }
              }
              
              if(status=='f')
               {hit==1;
               global[0].x=validposxp;
               global[0].y=validposyp;
               return phitterf1;
               }
              }
              
              if(hit==0)
               {if(global[0].y>G.uy)
                 {global[0].x=G.ux;
                  global[0].y=G.uy;
                 }
                 
               else 
                {global[0].x=G.ux;
                 global[0].y=G.uy;
                }
                
                return phitterf1;
               
               
               }//end of if when ball is in the sideways and between the 2 goals 
       
       // if case when ball is inside dee and not in the region of goal and above G.ux for team 0 and below G.ux for team 1
       if((fieldarray[global[0].x][global[0].y]==Dee)&&((global[0].y>G.uy)||(global[0].y<G.ly)))
         {
           if(global[0].y>G.uy)
            {global[0].y=G.uy;
             global[0].x=G.ux;
             return phitterf1;
            }
            
           else
            {global[0].y=G.ly;
             global[0].x=G.lx;
              return phitterf1;
             }
             
         }//end of if case when ball is inside dee and not in the region of goal and above G.ux for team 0 and below G.ux for team 1
         
     }//end of withme loop
     
   
   int withopp(int oppstrength)
    {
     int phitterf2=-1,phitterf2str=0,strreq=0;
     
     for(i=l1;i<=u1;i++)
      {
       strreq=preqp(global[0].x,global[0].y,global[i].x,global[0].y)+oppstrength;
       
       if(global[i].strength-strreq>0)
        {
         if(phitterf2str<global[i].strength-strreq)
          {
           phitterf2=i;
           phitterf2str=global[i].strength-strreq;
          }//end of if
        }//end of if
       }//end of for loop to find my player who has enough strength to move to ball pos & can take ball from opp player
       
      if(phitterf2!=-1) //if such player is found having more str than opp player after reaching his spot is found
       {
         global[phitterf2].x=global[0].x;
          global[phitterf2].y=global[0].y;
          global[phitterf2].strength=phitterf2str;
          
          phitterf2=withme(0,phitterf2);
          return phitterf2;
       }
       
      else    //if no such player is found to skip the move
       { return -1;}
       
     }//end of withopp fn
     
     
   int atemptyslot()// if ball is at emptyslot
    {
     int phitterf2=-1,phitterf2str=0,strreq=0;
     
      for(i=l1;i<=u1;i++)
      {
       strreq=preqp(global[0].x,global[0].y,global[i].x,global[0].y);
       
      
         if(phitterf3str<global[i].strength-strreq)
          {
           phitterf3=i;
           phitterf3str=global[i].strength-strreq;
          }//end of if
     
       }//end of for loop to find my player who has enough strength to move to ball pos & can take ball from opp player
       
      if(phitterf3!=-1) //if such player is found having more str than opp player after reaching his spot is found
       {
         global[phitterf3].x=global[0].x;
          global[phitterf3].y=global[0].y;
          global[phitterf3].strength=phitterf2str;
          
          phitterf3=withme(0,phitterf3);
          return phitterf3;
       }
       
      else    //if no such player is found to skip the move
       { return -1;}
       
     }//end of atemptyslot fn
     
     
   void check(int phitterf4)
    {
     int batemptyslot=0,ptobemoved=-1,ptobemovedstr=0,strreq=0,goalsaverposx,goalsaverposy;
     
     for(i=l1;i<=u1;i++)//to find whether ny of my player is present at the pos of the ball
      {
       if((global[i].x==global[0].x)&&(global[i].y==global[0].y))
        batemptyslot=1;
       } //end of forloop
     
     
     if(batemptyslot==0)//to move the player with max str after reaching there at the pos of ball if possible
      {
        for(i=l1;i<=u1;i++)
         {
           streq=preqp(global[i].x,global[i].y,global[0].x,global[0].y);
           
           if((global[i].x-strreq>ptobemovedstr)&&(i!=phitterf4))
            {
              ptobemoved =i;
              ptobemovedstr=global[i].x-strreq;
            }//end of if
          } //end of for
          
        if(ptobemoved!=-1)
         {global[ptobemoved].x=global[0].x;
          global[ptobemoved].y=global[0].y;
          global[ptobemoved].strength=ptobemovedstr;
         }
        }//end of if  
      
      //if ball is inside my dee than to move all my players inside dee in the front of goal\
      //except that the player should not bbe the hitter of the ball and also not the one which has just moved to the ball above  
      if(team==0) goalsaverposx=5;
      
      else goalsaverposy=95;
      
     
     if(fieldarray[global[0].x][global[0].y]==dee)
      {
        for(goalsaverposy=20,i=j;goalsaverposy<=30;goalsaverposy+=2)
         {
           for(j=i;j<=u1;j++)
            {if((fieldarray[global[j].x][global[j].y]==dee)&&(j!=phitterf4)&&(j!=ptobemoved))
              {
               global[j].x=goalsaveposx;
               global[j].y=goalsaverposy;
              }//end of if
            }//end of for
         }//end of for
         
        return;
        
      }//end of check fn
     
     
     
     
     
    
     
     
     
     
     
     
     
     
     
     
     
     
     
