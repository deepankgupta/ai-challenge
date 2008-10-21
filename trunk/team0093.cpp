    #include<stdio.h>
    
    #include<stdlib.h>
    #include<string.h>
    #include<math.h>
    #include<iostream>
    using namespace std;
    static int f=0;
    static int f2=0;
    class team0093 
    {
    private:
        int pl, ph, team, player_no,og,od,pg,pd,ol,oh;
    
        int preqp(int finalx, int finaly, int initialx, int initialy) 
        {
            float req;
            req = floor(sqrt(pow((finalx - initialx), 2) + pow((finaly - initialy), 2)));
            return (int) req;
        }
    
        int preqpb(int finalx, int finaly, int initialx, int initialy) //function which tells the strength req by hitter of ball to hit
        {
            float req;
            int i; //the ball from one place to another
            req = 2 * (floor(sqrt(pow((finalx - initialx), 2) + pow((finaly - initialy), 2))));
            i = req;
            return i;
        }
    
        //public functions
    public:
    int case1(int,struct player *);
    int case2(int,struct player *);
    int case3(struct player *);
    int intt(int fposx, int fposy, int iposx, int iposy,struct player *p) ;
    int playerD(int bp, struct player *p);
    int playerG(int bp, struct player*p);
    void angle(int bp, struct player *p,int def1,int def2);
    int range(int bp,struct player *p) ;
    int moveDefend(int def,int def2,int start,int end,int bp, struct player *p);
    


    int init(int team_number, struct player *p, char farray[][51]) //the mandatory function which initialises the team no. of the 
        {
        
            player_no = team_number;
        }
    void playpos(struct player *p)
    {
        if(player_no==1)
       {
         p[2].x=30;p[2].y=12;
         p[3].x=40;p[3].y=25;
         p[4].x=30;p[4].y=38;
         p[5].x=50;p[5].y=10;
         p[6].x=50;p[6].y=25;
         p[7].x=50;p[7].y=40;
         p[8].x=65;p[8].y=15;
         p[9].x=60;p[9].y=25;
         p[10].x=65;p[10].y=35;
         p[11].x=75;p[11].y=25;
         	p[2].strength-=preqp(30,12,25,10);
         		p[3].strength-=preqp(40,25,25,25);
         			p[4].strength-=preqp(30,38,25,40);
         				p[5].strength-=preqp(50,10,30,10);
         					p[6].strength-=preqp(50,25,30,25);
         						p[7].strength-=preqp(50,40,30,40);
         							p[8].strength-=preqp(65,15,40,10);
         								p[9].strength-=preqp(60,25,40,25);
         									p[10].strength-=preqp(65,35,40,40);
         										p[11].strength-=preqp(75,25,49,25);
}
if(player_no==2)
{
    p[13].x=70;p[2].y=12;
         p[14].x=60;p[14].y=25;
         p[15].x=70;p[15].y=38;
         p[16].x=50;p[16].y=10;
         p[17].x=50;p[17].y=25;
         p[18].x=50;p[18].y=40;
         p[19].x=35;p[19].y=15;
         p[20].x=40;p[20].y=25;
         p[21].x=35;p[21].y=35;
         p[22].x=25;p[22].y=25;
         	p[13].strength-=preqp(70,12,75,10);
         		p[14].strength-=preqp(60,25,75,25);
         			p[15].strength-=preqp(70,38,75,40);
         				p[16].strength-=preqp(50,10,70,10);
         					p[17].strength-=preqp(50,25,70,25);
         						p[18].strength-=preqp(50,40,70,40);
         							p[19].strength-=preqp(35,15,60,10);
         								p[20].strength-=preqp(40,25,60,25);
         									p[21].strength-=preqp(35,35,60,40);
         										p[22].strength-=preqp(25,25,51,25);


         										
}

         }
        int player(struct player *p) //main player func 
        {
            
            f++;
            
            if(f==1)
        
            {
            playpos(p);
            
            }
            int i, j, bp, a;
             
            if (player_no == 1) 
            {
                pl = 1; //pl shows the lower limit and ph shows the upper limit of players in the array of structures ,i.e. if player
                ph = 11; //is 1st then his players will be 1 to 11 and if he is 2nd then his players will be 12 to 22
                team = 1;
                pd=40,pg=14;
                od=60,og=86;
                ol=12,oh=22;
            }
           else 
           {
                pl = 12;
                ph = 22;
                team = 2;
                pd=60,pg=86;
                od=40,og=14;
                ol=1,oh=11;
            }
    
            for (i = 1; i < 23; i++)
                {
                     if (p[0].x == p[i].x && p[0].y == p[i].y) 
               {    
                                        bp= i;

                   
                    break;
                }
}
            if (i == 23) 
            {
                //so no player is having the ball
                a = case3(p);
                return a; //returns the hitter of the ball to the controller 
            }
    
            if ((bp <= 11 && player_no == 1) || (bp > 11 && player_no == 2 )) 
            {
                //then ball is with my team player
    
                a = case1(bp, p);
                return a;
            }
    
    
            // ball with opp team player
    
            a = case2(bp, p);
            return a;
    
        }//end of player func.
    };

        
    
    int team0093::intt(int fposx, int fposy, int iposx, int iposy,struct player *p)    // Intruption function 
                {
                   int i;
                   int xi,yi;
                    xi=iposx;
                    yi=iposy;
                   while(((xi<fposx)&&(iposx<fposx))||((xi>fposx)&&(iposx>fposx))||((yi<fposy)&&(iposy<fposy))||((yi>fposy)&&(iposy>fposy)))
                     {
                     if(xi<fposx && iposx<fposx)
                	  {++xi;}
                    if(xi>fposx && iposx>fposx)
             	    {--xi;}
              	    if(yi<fposy && iposy<fposy)
             	    {++yi;}
                    if((yi>fposy) && (iposy>fposy))
             	    {--yi;}
                                                                                                               
                    for (i = ol; i <= oh; i++)  //change to ol to oh
    	            { 
                        if(p[i].x==xi&&p[i].y==yi)  //this func returns any player interupt in the path of ball
                        {
                    
                         return i;}
                        
                    }
                                 
                    }


                    return 0;
                }
                
        
    int team0093::playerD(int bp, struct player *p) //This function calculates capability of player to hit in D
    {
        int stroppD;
        stroppD= preqpb(pd ,p[bp].y ,p[bp].x ,p[bp].y); //40 to pd
        if(p[bp].strength >=stroppD)
        	{return 1;}
        else
        	{return 0;}
    }
    
    int team0093:: playerG(int bp, struct player*p) //This function calculates capability of player to hit in goal
    {
        int stroppG;
        stroppG= preqpb(pg ,p[bp].y ,p[bp].x ,p[bp].y); //14 to gpos
        if(p[bp].strength >=stroppG)
        	{return 1;}
        else
        	{return 0;}
    }
              
                
    void team0093::angle(int bp, struct player *p,int def1=0,int def2=0)
    {
        
         int choice=0,defender=0,xi,yi,finStrength1,finStrength2,save_x,save_y,i,reqStrength;
         finStrength1=preqpb(p[ol].x,p[ol].y,p[bp].x,p[bp].y);
         for(i=(ol+1);i<=oh;i++)
         {
              finStrength2=preqpb(p[i].x,p[i].y,p[bp].x,p[bp].y);
              if(finStrength2<finStrength1)
              {
                                           choice=i;
                                           finStrength1=finStrength2;
                            }
                            } 
                            if(choice!=0)
                            {defender=choice;}
                                              
         finStrength2=0;

    	 
         xi=p[bp].x;
         yi=p[bp].y;
    	
         while(((xi>p[defender].x)&&team==1)||((xi<p[defender].x) && team==2)||(yi<p[defender].y&&p[bp].y<p[defender].y)||(yi>p[defender].y&&p[bp].y>p[defender].y))
         {
    	 if(((xi>p[defender].x)&&team==1)||((xi<p[defender].x) && team==2))
               	{xi--;}
              	 if(yi<p[defender].y&&p[bp].y<p[defender].y)
             	  {yi++;}
    	else if(yi>p[defender].y&&p[bp].y>p[defender].y)
             	  {yi--;}
               for(i=pl;i<=ph;i++)
               {	if(i!=def1 && i!=def2)
    			{
                   reqStrength= preqp(xi,yi, p[i].x, p[i].y);
                   finStrength1= p[i].strength- reqStrength;
                   if(i>pl)
                   {
    			finStrength2= p[choice].strength - preqp(save_x,save_y, p[choice].x, p[choice].y);
                }
                 	if(finStrength2<=finStrength1)
                   	{
                        choice = i;
                        save_x = xi;
                        save_y = yi;
                   	}
               	   
    		}
              
         	    }

    }
if(choice!=0) //add night
{
          p[choice].x=save_x;
    	p[choice].y=save_y;
        }
    }
                   

   int team0093::range(int bp,struct player *p) 
        {
            int i, j,c=0;
            if (preqpb(og, p[bp].y, p[bp].x, p[bp].y)<= p[bp].strength) //86 to gpos
            {
                c = intt(og, p[bp].y, p[bp].x, p[bp].y,p);  //86 to gpos
                if (c == 0) 
                {
                    return p[bp].y;
                }
               else 
               {
                    for (j = 10; j <= 40; j++) 
                    {
    
                      if ((preqpb(og, j, p[bp].x, p[bp].y) <= p[bp].strength) && (intt(og, j, p[bp].x, p[bp].y,p)) == 0) 
    		          {//86 to gpos
                                		return j;
                      }
                    }
                    return 0;
                }
    
        }
        return 0;
    }                
    
    //We are using max 3 players to save our goal. For this reason def and def2 are used for protecting the clashing between the players 
    //so that we do not mess up replacing the same player with different positions    
    int team0093:: moveDefend(int def,int def2,int start,int end,int bp, struct player *p) //This function calculates the best option to defend the ball and also the 																nearest player to opponent
    {

        int i, reqStrength[23],choice=0,finStrength[23];
    	finStrength[0]=0;
      for(i=start;i<=end;i++)      // This loop calculates required strength to move to place thus the best option
        {				
                         reqStrength[i]= preqp(p[bp].x, p[bp].y, p[i].x, p[i].y);
                         finStrength[i]= p[i].strength - reqStrength[i];
                         if((reqStrength[i]<=p[i].strength)&&(finStrength[choice]<=finStrength[i])&&(choice!=def)&&(choice!=def2))
                         {
                              choice= i;
                         }
        }
        

        return choice;				    
                         
    }
    

     //definition of case1() , when the ball is with my player
     int team0093::case1(int bp, struct player * p) 
                {   
                    int o;
                
                    int i,c=0,large=0,di;
                    int y;
                    
                     for(i=ol;i<=oh;i++)
                    {
                                        
                                       if(p[i].x==p[bp].x && p[bp].y==p[i].y)
                                       {
                                        
                                               di=p[bp].strength-p[i].strength;
                                               if(di<=0)
                                               {
                                               
                                                return -1;
                                               }
                                               else
                                               {p[bp].strength=di;
                                               break;
                                               }
                                       }
                     }
                    if(((p[bp].x>=60)&&team==1)||((p[bp].x<=40)&&(team==2)))        //60 to dpos and sign
                    {y = range(bp,p);
                    if (y != 0) 
    	            {
                        p[0].x = og;
                        p[0].y = y;
                        return bp;
                    }
                    if (y == 0) 
    	            {
                          
                        large = p[bp].strength;
                        for (i = pl; i <= ph ; i++) //pl to ph
    	                 {
                            if ((p[i].x > 40) && (p[i].x < 60) && (i!=bp))  //check
    	                     {
                                if (((intt(p[i].x, p[i].y, p[bp].x, p[bp].y,p)) == 0) && (preqpb(p[i].x, p[i].y, p[bp].x, p[bp].y)) <= large) 
                                {
                                    large = preqpb(p[i].x, p[i].y, p[bp].x, p[bp].y);
                                    p[0].x = p[i].x;
                                    p[0].y = p[i].y;
                                    c=i;
                                }
                            }
                        }
                        if(c!=0)
                        {return bp;}
                        for (i = pl; i <= ph ; i++) //pl to ph
    	                {
                            if (i!=bp && (((p[i].x > p[bp].x)&&(team==1))||((p[i].x < p[bp].x)&&(team==2)))) //sign combine
    	                    {
                                if ((intt(p[i].x, p[i].y, p[bp].x, p[bp].y,p)) == 0 && (preqpb(p[i].x, p[i].y, p[bp].x, p[bp].y)) <= p[bp].strength) 
    	                        {
                                    p[0].x = p[i].x;
                                    p[0].y = p[i].y;
                                    return bp;
                                }
                            }
                        }
                        return -1;
                    }
                    }
                    large = p[bp].strength;
                    c=0;int d;
                    if(p[bp].x>40&&p[bp].x<60)
                    {                               
                      for (i = pl; i <= ph; i++) //pl to ph
    	                {
                             if(i!=bp && (((p[i].x >=60)&&(team==1))|| ((p[i].x <=40)&&(team==2))))//sign combine
                             {
                                                   d=intt(p[i].x, p[i].y, p[bp].x, p[bp].y,p);
                           
                            
                             if (d == 0 && (preqpb(p[i].x, p[i].y, p[bp].x, p[bp].y)) <= large)
                             
    	                     { 
                                large = preqpb(p[i].x, p[i].y, p[bp].x, p[bp].y);
                                p[0].x = p[i].x;
                                p[0].y = p[i].y;
                                c=i;
                                
                             }
                             }
                            
                        }
                        if(c!=0)
                        {
                        return bp;}
                        //here c=0 as if cond false
                        
                        large =p[bp].strength;
                        for (i = 5; i <=45; i++) 
    	                {    
                             if(team==1)
                                 o=od;                            
    	                     else
    	                     o=od;
    	                     d=intt(o, i, p[bp].x, p[bp].y,p);
                             if (d == 0 && (preqpb(o, i, p[bp].x, p[bp].y)) <= large) //60 to dpos
    	                     { 
                           
                                large = preqpb(o, i, p[bp].x, p[bp].y);  //60 to dpos
                                p[0].x = o;  //60 to dpos
                                p[0].y = i;                               
                             }
                             
                            
                        }
                        for(i=pl;i<=ph;i++)
                        {
                        if(p[i].x==o)
                        {             if(preqp(o,p[0].y,p[i].x,p[i].y)<=p[i].strength)
                                      {p[i].y=p[0].y;
                                      return bp;
                                      }
                                      
                         }
                         }
                        int  reqStrength[23],choice=0,finStrength[23];
    	                finStrength[0]=0;
    	                choice=0;
                        for(i=pl;i<=ph;i++)      // This loop calculates required strength to move to place thus the best option
                        {
                        
                        if((i!=bp) && (((p[i].x >=60)&&(team==1))|| ((p[i].x <=40)&&(team==2))))
                        {
                                 
                         reqStrength[i]= preqp(o, p[0].y, p[i].x, p[i].y);
                         
                         finStrength[i]= p[i].strength - reqStrength[i];
                        if((reqStrength[i]<=p[i].strength)&&(finStrength[choice]<=finStrength[i]))
                         {
                              choice= i;
                         }
                         
                         }
                         }
                         if(choice!=0)
                         {p[choice].x=p[0].x;
                         p[choice].y=p[0].y;
                         return bp;
                         }
                         
                        return -1;
                     }
                     large=p[bp].strength;
                     if((p[bp].x<=40 && team==1)|| (p[bp].x>=60 && team==2)) //sign combine
                     {
                         c=0;
                      for (i = pl; i <= ph; i++) //pl to ph
    	                {
                             if(i!=bp && (((p[i].x >40)&&(team==1))|| ((p[i].x <60)&&(team==2))))  //sign combine
                             {
                             if ((intt(p[i].x, p[i].y, p[bp].x, p[bp].y,p)) == 0 && ((preqpb(p[i].x, p[i].y, p[bp].x, p[bp].y)) <= large)) 
    	                     { 
                                large = preqpb(p[i].x, p[i].y, p[bp].x, p[bp].y);
                                
                                c=i;
                                }
                            }
                            
                        }
                        
                        
                        if(c!=0)
                        {p[0].x = p[c].x;
                                p[0].y = p[c].y;
                                return bp;}
                        
                        else
                        {   
                            
                            large =preqpb(p[ph].x, p[ph].y, p[bp].x, p[bp].y);
                             
                             for (i = pl; i <= ph; i++) //pl to ph
    	                {
                             if(i!=bp && (((p[i].x >40)&&(team==1))||((p[i].x <60)&&(team==2))))  //sign combine
                             {
                             if ((intt(p[i].x, p[i].y, p[bp].x, p[bp].y,p)) == 0 && (preqpb(p[i].x, p[i].y, p[bp].x, p[bp].y)) <= large) 
    	                     { 
                                large = preqpb(p[i].x, p[i].y, p[bp].x, p[bp].y);
                                
                                c=i;
                            }
                            }
                            
                        }
                        if(c!=0 )
                        {       p[0].x = p[c].x;
                                p[0].y = p[c].y;
                                p[pl].y=p[0].y;
                                return bp;
                                
                                }
                        
                        return -1;
                        }
                        
                        
                        
                }
            }
            
    int team0093:: case2(int bp, struct player *p)
    {
        int flag=0,defender,bpx,x,strdiff, dDefender,i,smalli,smallf;
        if((p[bp].x>40 && team==1) || (p[bp].x<60 && team==2))     //To check if opponent in outside our D  
        {                                                            // sign combine
                         flag= playerD(bp,p);
                         if(flag==1)   //Best player placed right on the ball if D is achievable  
                         {
                                 defender= moveDefend(30,30,pl,ph,bp,p);//1 to pl 11 to ph
                                 p[defender].x= p[bp].x;
                                 p[defender].y= p[bp].y;
                                 strdiff = p[bp].strength - p[defender].strength;   
                                 if(((strdiff>=(2*(p[bp].x-40))) && team==1) || ((strdiff>=(2*(60-p[bp].x))) && team==2))
                                 {                     
                                 if(team==1)         
                                      smalli=p[pl].strength-preqp(41,p[bp].y,p[pl].x,p[pl].y);
                                      else
                                      smalli=p[pl].strength-preqp(59,p[bp].y,p[pl].x,p[pl].y);
                                      for(i=pl+1;i<=ph;i++)
                                      {                                                    
                                      if(i!=defender){
                                                      if(team==1)
                                            smallf=p[i].strength-preqp(41,p[bp].y,p[i].x,p[i].y);
                                            else
                                            smallf=p[i].strength-preqp(59,p[bp].y,p[i].x,p[i].y);              
                                                        if(smallf>smalli)
                                                        {
                                                                         dDefender=i;
                                                                         smalli=smallf;
                                                        }
                                                        }
                                      }
                                      if(team==1)
                                      p[dDefender].x = 41;
                                      else
                                      p[dDefender].x=59;
                                      
                                      p[dDefender].y = p[bp].y;
                                      return -1;
                                 }
                                 else if((p[defender].strength)>(p[bp].strength))
                                 {
                                     p[defender].strength-=p[bp].strength;
                                      return (case1(defender,p));
                                 }
                                 else
                                 {return -1;}
                                 
                         }
                         if(flag==0)  //Best player placed in line of ball if D not achievable
                         {
                                 defender= moveDefend(30,30,pl,ph,bp,p);//1 to pl 11 to ph
                                  if((p[defender].strength)-(preqp(p[bp].x,p[bp].y,p[defender].x,p[defender].y))>(p[bp].strength))
                                 {
                                 p[defender].x=p[bp].x;
                                 p[defender].y=p[bp].y;
                                p[defender].strength-=p[bp].strength;
                                      return (case1(defender,p));
                                 }
                                 else if((p[defender].x<p[bp].x && team==1) || (p[defender].x>p[bp].x && team==2))//sign combine
                                      {p[defender].y= p[bp].y;
                                      return -1;}
    				else
                            return -1;
                         }
                         
        }
        else        //When opponent is in our D
        {
            flag= playerG(bp,p);
            if(flag == 1)     //Opponent will be able to hit in the goal
            {                            
/*1 to pl 15 to gpos+1*/                 p[pl].x=(team==1)?15:85;            //This and the next line will place the goal keeper in the line of ball holder opponent
                       p[pl].y=p[bp].y;
                       defender = moveDefend(pl,30,pl+1,ph,bp,p);   //1 to pl,2 to pl+1,11 to ph
                       p[defender].x= p[bp].x;
                       p[defender].y= p[bp].y;
                       
                       x=defender;
                       angle(bp,p,x,pl);//1 to pl
    				   return -1;
            }
            else  //Opponent will not be able to hit in the goal
            {     
                   defender= moveDefend(30,30,pl,ph,bp,p);//1 to pl 11 to ph
                                  if((p[defender].strength)-preqp(p[bp].x,p[bp].y,p[defender].x,p[defender].y)>(p[bp].strength))
                                 {
                                 p[defender].x=p[bp].x;
                                 p[defender].y=p[bp].y;
                                 p[defender].strength-=p[bp].strength;
                                      return (case1(defender,p));
                                 }
                                 else if((p[defender].x<p[bp].x && team==1) || (p[defender].x>p[bp].x && team==2))
                                      {
                                       angle(bp,p,30,defender);
                                      p[defender].y= p[bp].y;
                                      return -1;}
    						else
    						{
                                angle(bp,p,30,30);
                            return -1;
                                   }
                
    			
            }    
                       
        }
    }                              
    
    int team0093:: case3(struct player *p)
    {int a= -1;
    int ch=0;
    	 ch=moveDefend(30,30,pl,ph,0,p); //1 to pl,11 to ph
    	 if(ch!=0)
    	{p[ch].strength-=preqp(p[0].x,p[0].y,p[ch].x,p[ch].y);
    		p[ch].x=p[0].x;
    		p[ch].y=p[0].y;
       		a=case1(ch,p);
         }
    		return a;
    	
    	
    	
    	
    }
    
   
