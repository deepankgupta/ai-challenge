int player(int num1)
{
    
    
    int case1(int num)
    {
        
        
        //checking wether the my team player having the ball is in the range of opp team goal or not
    
    float small=1000;
    int player_no1=-1,player_no2=-1;
    
    
    if(p[num].y>=20 && p[num].y<=30 )                    
    {    //now the my team player having the ball is in the range of opp team goal check which players are intercepting
                    for(int j=1;j<=22;j++)
                    if(p[j].y==p[num].y && p[j].x>p[num].x && (p[j].x-p[num].x)<small )
           //any player is intercepting and the player is
    player_no1=j;
    if(player_no1!=-1)
    {  //some player is intercepting now check wehter it is of which team
    
    if( (player_no1<=11&&num1==1) || (player_no1>=12&&num1==2))
    {
                     //my team player is intercepting
                     p[0].x=p[j].x;
                     p[0].y=p[j].y;
                     }
                     
                     else
                     
                     {
                         //opp team player is intercepting
                         
                         //finding my team's nearest player
                         small=1000;
                         if(num1==2)
                         {
                         for(int i=12;i<=22;i++)
                         {
                                 distance=sqrt( pow( (p[i].x-p[num].x),2) + pow( (p[i].y-p[num].y),2) );
                         if(p[i].x>p[num].x && distance<small && p[num].strength>(2*floor(distance)) )
                         player_no2=i;
                         }
                         
                         
                         p[0].x=p[player_no2].x;
                         p[0].y=p[player_no2].y;
                         }//end of if(num1==2)
                         else
                         {
                             for(int i=1;i<=11;i++)
                         {
                                 distance=sqrt( pow( (p[i].x-p[num].x),2) + pow( (p[i].y-p[num].y),2) );
                         if(p[i].x>p[num].x && distance<small && p[num].strength>(2*floor(distance)) )
                         player_no2=i;
                         }
                         
                         
                         p[0].x=p[player_no2].x;
                         p[0].y=p[player_no2].y;
                         }//end of else of if(num1==2)
 
                             
                         } //end of else
                         }// end of if(player_no1!=-1)
                         
                         else
                             //no player is intercepting
                             if(num1==1)
                             p[0].x+=p[num].strength;   //kicking the ball with all the available strength
                             else
                             p[0].x-=p[num].strength;
                              
                              } //end of checking wether the player is in the range of goal or not
                              
                              
                              else
                              {
                                  //my player having the ball is not in the range of goal
                                  
                                  //find out if i can directly hit in the goal or not
                                  if(num1==1)
                                  {
                                             
                                      float distance1=sqrt( pow( (95-p[num].x),2 ) + pow( (p[num].y-20),2 ) );
                                      float distance2=sqrt( pow( (95-p[num].x),2 ) + pow( (p[num].y-30),2 ) );
                                  }
                                  else
                                  {
                                      float distance1=sqrt( pow( (5-p[num].x),2 ) + pow( (p[num].y-20),2 ) );
                                      float distance2=sqrt( pow( (5-p[num].x),2 ) + pow( (p[num].y-30),2 ) );

                                 if(p[num].strength> (2*floor(distance1) ) && p[num].strength < (2*floor(distance2) ) )  )
                                 {
                                                     if(num1==1)
                                                     {
                                                     p[0].x=95;
                                                     p[0].y=20;
                                                     }
                                                     else
                                                     {
                                                         p[0].x=5;
                                                         p[0].y=20;
                                                         }
                                                     }
                                                     
                                                     else
                                                     if(p[num].strength> (2*(floor(distance2)) ) )
                                                     {
                                                                  if(num1==1)
                                                                  {
                                                                  p[0].x=95;
                                                                  p[0].y=30;
                                                                  }
                                                                  else
                                                                  {
                                                                      p[0].x=5;
                                                                      p[0].y=30;
                                                                      }
                                                                  }
                                                                  
                                                     else
                                                     {   small=1000;
                                                         player_n02=-1;
                                                         if(num1==1)
                                                         {
                                                         for(i=1;i<=11;i++)
                                                         if(p[i].x>p[num].x)
                                                         {
                                                                distance1=sqrt( pow( (p[i].x-p[num].x),2) + pow( (p[i].y-p[num].y),2 ) );
                                                                if(distance1<small && p[num].strength>(2*(floor(distance))) )
                                                                {
                                                                                   small=distance;
                                                                                   player_no2=i;
                                                                                   }
                                                                 if(player_no2!=-1)
                                                                 {
                                                                                   p[0].x=p[player_no2];
                                                                                   p[0].y=p[player_no2];
                                                                                   }
                                                                                   }//end of if(num==1)
                                                                                   
                                                                                   else
                                                                                   {
                                                                                       // iam player no.2
                                                                                         for(i=12;i<=22;i++)
                                                         if(p[i].x<p[num].x)
                                                         {
                                                                distance1=sqrt( pow( (p[i].x-p[num].x),2) + pow( (p[i].y-p[num].y),2 ) );
                                                                if(distance1<small && p[num].strength>(2*(floor(distance))) )
                                                                {
                                                                                   small=distance;
                                                                                   player_no2=i;
                                                                                   }
                                                                 if(player_no2!=-1)
                                                                 {
                                                                                   p[0].x=p[player_no2];
                                                                                   p[0].y=p[player_no2];
                                                                                   }
                                                                                   }//end of else of if(num==1) 
                                                                                       
                                                                                   }
                                                                                   }//end of else for which player is not in the range of the goal  
                                                                                            
                                                                                            return 0;                     
                                                                                              
                                                                                              }//end of case1 func
                                                                                              
                                                                                              
                                                                                              
                                                                                              
                                                                                              
                                                                                              
                                                                           
                                                                           
                                                     
                                   
    
    
    
    
    int player_no=-1;
    if(num==1) //i am player no 1
    {
               //check my d operation
               
               if(p[0].y>=10 && p[0].y<=40 && p[0].x<10)
               {
                             //then ball is in my D
                             for(int i=20;i<=30;i+=2)
                             {
                                     for(int j=1;j<=11;j++)
                                     {
                                             distance=sqrt(pow( (p[j].y-i),2)+pow( (p[j].x-5),2 ) );
                                             if(p[j].strength>=floor(distance) )
                                             player_no=j;
                                             } //end of j loop 
                                             p[player_no].x=5;
                                             p[player_no].y=i;
                                             }//end of i loop
                                             
                                             }// end of if(ball is in D)
                                             
                                             } //end of checking the D
                                             
                                             
                                             
                                             
                                             
                             
          
          //checking wether the ball is with any of my player or not
          
          for(i=1;i<=11;i++)
          if( p[i].x=p[0].x && p[i].y==p[0].y )
          break;
          
          if(i<=11)  //ball is with one of my player
          {        int x=p[0].x;
                   int y=p[0].y;
                   case1(i);
                   if(p[0].x==x&&p[0].y==y)
                   return -1;
                   return i;
                   }
                   
                   //if control comes here than ball is not with my player
                  
                  if(i>=12&&i<=22)
                  {
                                  //ball with opposite team's player
                                  player_no=-1;
                                  large=-1;
                                  for(j=1;j<=11;j++)
                                  {
                                          distance=sqrt( pow( (p[j].x-p[0].x),2 ) + pow( (p[j].y-p[0].y),2 ) );
                                          
                                          if(p[j].strength>floor(distance)&&  (p[j].strength-floor(distance) )>p[i].strength  &&   (p[j].strength-floor(distance)>large)
                                          {
                                                                              large=p[j].strength-floor(distance);
                                                                              player_no=j;

                                                                              }  //end of j for                                            
                                           if(player_no==-1)
                                                            return -1;
                                                            else
                                                            {
                                                                p[player_no].x=p[0].x;
                                                                p[player_no].y=p[0].y;
                                                                case1(player_no);
                                                                return player_no;
                                                             }
                                                             
                                                             
                                                             
                                                             else //case 3 ball with no player
                                                             {    
                                                                  large=-1;
                                                                  player_no=-1;
                                                                  for(j=1;j<=11;j++)
                                                                  {
                                                                                    distance=sqrt(pow( (p[j].x-p[0].x),2) + pow( (p[j].y-p[0].y),2) );
                                                                                    if(p[j].strength>floor(strength && (p[j].strength-floor(distance) )>large)
                                                                                    {
                                                                                                                    large=(p[j].strength-floor(distance) );
                                                                                                                    player_no=j; 
                                                                                                                    }
                                                                                                                    }// end of j for
                                                                                                                    
                                                                                                                    
                                                                                                                    if(player_n0==-1)
                                                                                                                    return -1;
                                                                                                                    else
                                                                                                                    {
                                                                                                                        p[player_no].x=p[0].x;
                                                                                                                        p[player_no].y=p[0].y;
                                                                                                                        casei(player_no);
                                                                                                                        return player_no;
                                                                                                                        }              
                                                                                                                        }//end of case 3
                                                                                                                        
                                                                                                                        }// end of if(num==-1)
                                                                                                                        
                                                                                                                        
                                                                                                                        
                                                                                                                        
       else //of if(num==1)
       {
           //i am player 2  
           
           if(p[0].y>=10 && p[0].y<=40 && p[0].x<90)
               {
                             //then ball is in my D
                             for(int i=20;i<=30;i+=2)
                             {
                                     for(int j=12;j<=22;j++)
                                     {
                                             distance=sqrt(pow( (p[j].y-i),2)+pow( (p[j].x-95),2 ) );
                                             if(p[j].strength>=floor(distance) )
                                             player_no=j;
                                             } //end of j loop 
                                             p[player_no].x=95;
                                             p[player_no].y=i;
                                             }//end of i loop
                                             
                                             }// end of if(ball is in D)
                                             
                                             } //end of checking the D
                                             
                                             
                                             
                                             
                                             
                             
          
          //checking wether the ball is with any of my player or not
          
          for(i=12;i<=22;i++)
          if( p[i].x=p[0].x && p[i].y==p[0].y )
          break;
          
          if(i>=12)  //ball is with one of my player
          {        int x=p[0].x;
                   int y=p[0].y;
                   case1(i);
                   if(p[0].x==x&&p[0].y==y)
                   return -1;
                   return i;
                   }
                   
                   //if control comes here than ball is not with my player
                  
                  if(i>=1&&i<=11)
                  {
                                  //ball with opposite team's player
                                  player_no=-1;
                                  large=-1;
                                  for(j=12;j<=22;j++)
                                  {
                                          distance=sqrt( pow( (p[j].x-p[0].x),2 ) + pow( (p[j].y-p[0].y),2 ) );
                                          
                                          if(p[j].strength>floor(distance)&&  (p[j].strength-floor(distance) )>p[i].strength  &&   (p[j].strength-floor(distance)>large)
                                          {
                                                                              large=p[j].strength-floor(distance);
                                                                              player_no=j;

                                                                              }  //end of j for                                            
                                           if(player_no==-1)
                                                            return -1;
                                                            else
                                                            {
                                                                p[player_no].x=p[0].x;
                                                                p[player_no].y=p[0].y;
                                                                case1(player_no);
                                                                return player_no;
                                                             }
                                                             
                                                             
                                                             
                                                             else //case 3 ball with no player
                                                             {    
                                                                  large=-1;
                                                                  player_no=-1;
                                                                  for(j=12;j<=22;j++)
                                                                  {
                                                                                    distance=sqrt(pow( (p[j].x-p[0].x),2) + pow( (p[j].y-p[0].y),2) );
                                                                                    if(p[j].strength>floor(strength && (p[j].strength-floor(distance) )>large)
                                                                                    {
                                                                                                                    large=(p[j].strength-floor(distance) );
                                                                                                                    player_no=j; 
                                                                                                                    }
                                                                                                                    }// end of j for
                                                                                                                    
                                                                                                                    
                                                                                                                    if(player_n0==-1)
                                                                                                                    return -1;
                                                                                                                    else
                                                                                                                    {
                                                                                                                        p[player_no].x=p[0].x;
                                                                                                                        p[player_no].y=p[0].y;
                                                                                                                        casei(player_no);
                                                                                                                        return player_no;
                                                                                                                        }              
                                                                                                                        }//end of case 3
                                                                                                                        
                                                                                                                        }// end of if(num==-1)
                                                                                                                        
                                                                                                                        
                                                                                                                        
                                                                                                                        
                                                                                                                        
                                                                                                                        
                                                                                                                        }//end of player1 func 
