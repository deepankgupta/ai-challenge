#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

using namespace std;

class team0078  
{                
    private:
  
    int myteam,op_team;  
    int pl_min;
    int pl_max;
             
  
  
    int preqp(int finalx,int finaly, int initialx ,int initialy )
    {
        float req;
        req=(float)floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2)));
        return (int)req;
    }     

    int distance(int x1,int y1,int x2,int y2)
    {
        int distance = (int)sqrt(pow((x2-x1),2)+pow((y2-y1),2));
        return distance;
    }
    
    int preqpb(int finalx,int finaly, int initialx ,int initialy )
    {
        float req; int i;
        req=(float)2*(floor(sqrt(pow((finalx-initialx),2)+pow((finaly-initialy),2))));
	    i=(int)req;
	    return i;
     }
         
	 
	 
    public:
         
    int init(int team_number, struct player *p,char farray[][51])   
	{                                                             
        myteam=team_number;   
        if(myteam ==1)
        {
            op_team = 2;
        }
        else
        {
            op_team = 1;
        }
                                           
	}                                                  
                                                 
                                                 
    int player(struct player *p)  
    {
        int mypl = -1;
        int oppl = -1;
        for(int i=1;i<23;i++)
        {
            if((p[i].x == p[0].x)&&(p[i].y == p[0].y))
            {
                if(p[i].team == myteam)
                {
                    if(mypl == -1)
                    {
                        mypl = i;
                    }
                    else
                    {
                        if(p[i].strength > p[mypl].strength)
                        {
                            mypl = i;
                        }
                    }
                }
                if(p[i].team == op_team)
                {
                    if(oppl == -1)
                    {
                        oppl = i;
                    }
                    else
                    {
                        if(p[i].strength > p[oppl].strength)
                        {
                            oppl = i;
                        }
                    }
                }    
            }
        }
        int phitter = -1;
        if(oppl == -1)
        {
            phitter = offence(p);
            if(p[phitter].strength == 0)
            {
                return -1;
            }
            return phitter;
        }
        if(mypl == -1)
        {
            phitter = -1;
            offence(p);
            return phitter;
        }
        if(p[oppl].strength > p[mypl].strength)
        {
            phitter = -1;
            offence(p);
            return phitter;
        }
        if(p[oppl].strength < p[mypl].strength)
        {
            phitter = offence(p);
        }
        if(p[phitter].strength == 0)
        {
            return -1;
        }
        return phitter;
               
                    
                    
                    
    } 
    
    // Finds the players to whom i should pass the ball
    void findPlayers(struct player *p,struct player Player,int nearpl[2])
    {
        // Find the first nearest player to my player having the ball
        int min_x=0,max_x = 100,i;
        for(i=1;i<23;i++)
        {
            if(p[i].team == myteam)
            {
                if(myteam == 1)
                {   
                    if((p[i].x>Player.x)&&(p[i].x<max_x))
                    {
                        max_x = p[i].x;
                        nearpl[1] = i;
                    }
                }
                if(myteam == 2)
                {   
                    if((p[i].x<Player.x)&&(p[i].x>min_x))
                    {
                        min_x = p[i].x;
                        nearpl[1] = i;
                    }
                }
            }
        }
        if((min_x == 0)&&(max_x == 100))
        {
            nearpl[1] = -1;
            nearpl[0] = -1;
            return;
        }
        
        // Find the second nearest player to my player having the ball
        min_x=0,max_x = 100;
        for(i=1;i<23;i++)
        {
            if(p[i].team == myteam)
            {
                if(myteam == 1)
                {   
                    if((p[i].x>p[nearpl[1]].x)&&(p[i].x<max_x))
                    {
                        max_x = p[i].x;
                        nearpl[0] = i;
                    }
                }
                if(myteam == 2)
                {   
                    if((p[i].x<p[nearpl[1]].x)&&(p[i].x>min_x))
                    {
                        min_x = p[i].x;
                        nearpl[0] = i;
                    }
                }
            }
        }
        if((min_x == 0)&&(max_x == 100))
        {
            //nearpl[1] = -1;
            nearpl[0] = -1;
            return;
        }
    }
                            
         
    
    // Function to check whether the ball is being intercepted in its path or not
    int findIntercept(struct player *p,int x1,int y1,int x2,int y2)
    {
        int flag = 0;
        while((x2 != x1)&&(y2 != y1))
        {
            
            if(x2>x1)
            {
                x1++;
            }
            else
            {
                x1--;
            }
            if(y2>y1)
            {
                y1++;
            }
            else
            {
                y1--;
            }
            
            
            for(int i=1;i<23;i++)
            {
                if(p[i].team == op_team)
                {
                    if((p[i].x == x1)&&(p[i].y == y1))
                    {
                        if((x1 != x2)&&(y1 != y2))
                        {
                            flag = 1;
                            return flag;
                        }
                    }
                }
            }
        }
        return flag;
    }
    
    // Function which is called when doing offence
    int offence(struct player *p)                                                       
    {
        int arr_pos[11][2] = {{20,14},{26,20},{32,14},{38,20},{44,14},{50,20},{56,14},{62,20},{68,14},{74,20},{80,14}};
        int i,player_number;
        int min_dist = 1000,max_energy = 0; 
        // Moving the players at the positions referred by arr_pos
        for(i=0;i<11;i++)
        {
            min_dist = 1000;
            for(int j=1;j<23;j++)
            {
                if(p[j].team == myteam)
                {
                    if(distance(p[j].x,p[j].y,arr_pos[i][0],arr_pos[i][1]) < min_dist)
                    {
                        int flag = 0;
                        for(int k=0;k<i;k++)
                        {
                            if((p[j].x == arr_pos[k][0])&&(p[j].y == arr_pos[k][1]))
                            {
                                flag = 1;
                            }
                        }
                        if(flag == 0)
                        {
                            min_dist = distance(p[j].x,p[j].y,arr_pos[i][0],arr_pos[i][1]);
                            player_number = j;
                        }
                    }
                }
            }
            p[player_number].x = arr_pos[i][0];
            p[player_number].y = arr_pos[i][1];
            
        }
        min_dist = 1000;
        // Now move the player nearest to the ball at the ball's position  
        for(i=1;i<23;i++)
        {
             
            if(p[i].team == myteam)
            {
                 min_dist = distance(p[i].x,p[i].y,p[0].x,p[0].y);
                 if((p[i].strength-min_dist)>max_energy)
                 {
                     max_energy = p[i].strength-min_dist;
                     player_number = i;
                 }
            }
        }
        p[player_number].x = p[0].x;
        p[player_number].y = p[0].y;
        
        // Now this player is going to pass the ball to the nearest player or make a goal!!
        // Keep watching!!
        int nearpl[2];
        findPlayers(p,p[player_number],nearpl);
        if(nearpl[0] == -1)
        {
            if(nearpl[1] == -1)
            {
                // This is the goal hitting code, yippeee if it reaches here...
                if(myteam == 1)
                {
                    if(findIntercept(p,p[player_number].x,p[player_number].y,14,86) == 0)
                    {
                        p[0].x = 86;
                        p[0].y = 14;
                    }
                    else
                    {
                        if(findIntercept(p,p[player_number].x,p[player_number].y,15,86) == 0)
                        {
                            p[0].x = 86;
                            p[0].y = 15;
                        }
                        else
                        {
                            if(findIntercept(p,p[player_number].x,p[player_number].y,16,86) == 0)
                            {
                                p[0].x = 86;
                                p[0].y = 16;
                            }
                            else
                            {
                                p[0].x = 86;
                                p[0].y = 17;
                            }
                        }
                    }
                }
                
                
                if(myteam == 2)
                {
                    if(findIntercept(p,p[player_number].x,p[player_number].y,14,14) == 0)
                    {
                        p[0].x = 14;
                        p[0].y = 14;
                    }
                    else
                    {
                        if(findIntercept(p,p[player_number].x,p[player_number].y,15,14) == 0)
                        {
                            p[0].x = 14;
                            p[0].y = 15;
                        }
                        else
                        {
                            if(findIntercept(p,p[player_number].x,p[player_number].y,16,14) == 0)
                            {
                                p[0].x = 14;
                                p[0].y = 16;
                            }
                            else
                            {
                                p[0].x = 14;
                                p[0].y = 17;
                            }
                        }
                    }
                }
            }
            else
            {
                if((findIntercept(p,p[player_number].x,p[player_number].y,p[nearpl[1]].x,p[nearpl[1]].y) == 0)&&(p[player_number].strength >= preqpb(p[nearpl[1]].x,p[nearpl[1]].y,p[player_number].x,p[player_number].y)))
                {
                    p[0].x = p[nearpl[1]].x;
                    p[0].y = p[nearpl[1]].y;
                }
                else
                {
                    int move_posn = p[player_number].strength/2;
                    if(myteam == 1)
                    {
                        p[0].x += move_posn;
                    }
                    else
                    {
                        p[0].x -= move_posn;
                    }
                    p[nearpl[1]].x = p[0].x;
                    p[nearpl[1]].y = p[0].y;
                }
            } 
        }
        else
        {
            if((findIntercept(p,p[player_number].x,p[player_number].y,p[nearpl[0]].x,p[nearpl[0]].y) == 0)&&(p[player_number].strength >= preqpb(p[nearpl[0]].x,p[nearpl[0]].y,p[player_number].x,p[player_number].y)))
            {
                p[0].x = p[nearpl[0]].x;
                p[0].y = p[nearpl[0]].y;
            }
            else
            {
                if((findIntercept(p,p[player_number].x,p[player_number].y,p[nearpl[1]].x,p[nearpl[1]].y) == 0)&&(p[player_number].strength >= preqpb(p[nearpl[1]].x,p[nearpl[1]].y,p[player_number].x,p[player_number].y)))
                {
                    p[0].x = p[nearpl[1]].x;
                    p[0].y = p[nearpl[1]].y;
                }
                else
                {
                    int move_posn = p[player_number].strength/2;
                    if(myteam == 1)
                    {
                        p[0].x += move_posn;
                    }
                    else
                    {
                        p[0].x -= move_posn;
                    }
                    p[nearpl[1]].x = p[0].x;
                    p[nearpl[1]].y = p[0].y;
                }
            }
        }
    return player_number;                
    } 
          
          
          
          
    // Function which is called when doing defence
    // Using player to player defence
    void defense(struct player *p)
    {
         int min_dist_pl,i;
         
         // Code to find the player nearest to the ball and send it to that position
         int min_dist = 1000,max_energy = 0,player_number;
         for(i=1;i<23;i++)
         {
             
             if(p[i].team == myteam)
             {
                  min_dist = distance(p[i].x,p[i].y,p[0].x,p[0].y);
                  if((p[i].strength-min_dist)>max_energy)
                  {
                      player_number = i;
                  }
             }
         }
         
         p[player_number].x = p[0].x;
         p[player_number].y = p[0].y;
         
         
         // Code to find the player nearest to each opponent player 
         // and put a player of mine at opponent's position
         for(i=0;i<23;i++)
         {
             if(p[i].team == op_team)
             {
                 min_dist = 1000;
                 for(int j=1;j<23;j++)
                 {
             
                    if(p[j].team == myteam)
                    {
                        if(distance(p[i].x,p[i].y,p[j].x,p[j].y) == 0)
                        {
                            goto out_label1;
                        }
                        if(distance(p[i].x,p[i].y,p[j].x,p[j].y) < min_dist)
                        {
                            int flag =1;
                            for(int k=1;k<23;k++)
                            {
                                if((p[k].team == op_team)&&(p[k].x == p[j].x)&&(p[k].y == p[j].y))
                                {
                                      flag = 0;
                                }
                            }
                            if(flag)
                            {   
                                min_dist = distance(p[i].x,p[i].y,p[j].x,p[j].y);
                                player_number = j;
                            }
                        }
                    }
                 }
                 p[player_number].x = p[i].x;
                 p[player_number].y = p[i].y;
                  
                 out_label1:
                 player_number = player_number;
             }
         }
    }
};
