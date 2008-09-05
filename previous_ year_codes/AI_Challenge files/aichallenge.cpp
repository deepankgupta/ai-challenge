#include<iostream>
#include<fstream>

			// SIMULATOR //
#include"api.h"
#include <unistd.h>
#include <sys/wait.h>


using namespace std;

char farena[15][15]= {

			'X','X','X','X','X','X','X','X','X','X','X','X','X','D','T',
			'X','X','X','X','X','X','X','X','X','X','X','X','X','E','D',
			'X','X','E','E','E','E','E','E','E','E','E','E','E','E','E',
			'X','X','E','E','E','E','E','P','E','E','E','E','E','E','E',
			'X','X','E','E','S','E','E','E','E','E','E','E','E','E','E',
			'E','E','E','E','E','E','E','E','B','B','B','E','E','E','E',
			'E','E','E','E','E','E','E','E','E','B','E','E','E','E','S',
			'E','E','E','E','E','E','E','E','E','E','E','E','E','E','E',
			'S','E','E','E','E','B','E','E','E','E','E','E','E','E','E',
			'E','E','E','E','B','B','B','E','E','E','E','E','E','E','E',
			'E','E','E','E','E','E','E','E','E','E','S','E','E','X','X',
			'E','E','E','E','E','E','E','O','E','E','E','E','E','X','X',
			'E','E','E','E','E','E','E','E','E','E','E','E','E','X','X',
			'D','E','X','X','X','X','X','X','X','X','X','X','X','X','X',
			'T','D','X','X','X','X','X','X','X','X','X','X','X','X','X'

			 };


int move;
int agilityreq;
int defspellpowerreq;
int offspellpowerreq;
int spellhit;
int stop = 0;
int round;

struct input p1input, p2input;
struct reply p1reply, p2reply;
struct playerstats stats;
struct error p1error,p2error;
struct flags p1flag,p2flag;
struct repflags p1repflag,p2repflag;
struct recordio p1record, p2record;

void check(input &,reply &,flags &,repflags &,error &);
void update(input &,reply &,reply &,flags &,repflags &,error &);
void updatefile(input &,reply &,reply &,error &);











	/***************** CHECK FUNCTION *********************/

void check(input &a,reply &current,flags &curflag,repflags &currepflag,error &error)
	{
	spells defspell(current.defspellused);
	spells offspell(current.offspellused);

			// Checking for spell codes for particular rounds

					// defensive
	if(round==1)
		{
		if(current.defspellused>=0 && current.defspellused<=5);
		else error.errordefspellpower = 1;
		}

	if(round==2)
		{
		if( (current.defspellused>=0 && current.defspellused<=5) || current.defspellused==11 );
		else error.errordefspellpower = 1;
		}

	if(round==3)
		{
		if( (current.defspellused>=0 && current.defspellused<=5) || current.defspellused==11 || current.defspellused==13 || current.defspellused==14 || current.defspellused==16);
		else error.errordefspellpower = 1;
		}
					// offensive
	if(round==1)
		{
		if(current.offspellused>=0 && current.offspellused<=10);
		else error.erroroffspellpower = 1;
		}

	if(round==2)
		{
		if(current.offspellused>=0 && current.offspellused<=12);
		else error.erroroffspellpower = 1;
		}

	if(round==3)
		{
		if(current.offspellused>=0 && current.offspellused<=17);
		else error.erroroffspellpower = 1;
		}


			// CHECKING AND UPDATING FLAGS REPITITION
	if(currepflag.agilityrep > 0)
		{
		currepflag.agilityrep--;
		if(currepflag.agilityrep==0)		curflag.agilityflag = 0;
		}
	if(currepflag.spellpowerrep > 0)
		{
		currepflag.spellpowerrep--;
		if(currepflag.spellpowerrep==0)		curflag.spellpowerflag = 0;
		}
	if(currepflag.fastreductionrep > 0)
		{
		currepflag.fastreductionrep--;
		if(currepflag.fastreductionrep==0)	curflag.fastreductionflag = 0;
		}

	int i,j;
	int dx,dy;


		// CHECKING MOVEMENT STEP BY STEP
	for( int row=0; row<=14; row++)
		{
		for( int col=0; col<=14; col++)
			{
			if(a.arena[row][col] == 'P' || a.arena[row][col] == '*' || a.arena[row][col] == '#')
				{
				i=row;
				j=col;
				goto out1;
				}
			}
		}
out1:
	dx = current.xmovefinal-i;
	dy = current.ymovefinal-j;

	if(dx==0 && dy==0);

	else if(dx>0 && dy==0)
		{
		for( int k=0; k<dx; k++)
			{
			if(a.arena[i+k][j]!='E' && a.arena[i+k][j]!='S' && a.arena[i+k][j]!='D' && a.arena[i+k][j]!='T')
				error.errormovement = 1;

			if(a.arena[i+k][j]=='D')	// CHECKING FOR PITS
				{
				current.xmovefinal = i+k;
				current.ymovefinal = j;
				break;
				}
			}
		}


	else if(dx>0 && dy>0 && dx==dy)
		{
		for( int k=0; k<dx; k++)
			{
			if(a.arena[i+k][j+k]!='E' && a.arena[i+k][j+k]!='S' && a.arena[i+k][j+k]!='D' && a.arena[i+k][j+k]!='T')
				error.errormovement = 1;

			if(a.arena[i+k][j+k]=='D')	// CHECKING FOR PITS
				{
				current.xmovefinal = i+k;
				current.ymovefinal = j+k;
				break;
				}
			}
		}

	else if(dx==0 && dy>0)
		{
		for( int k=0; k<dy; k++)
			{
			if(a.arena[i][j+k]!='E' && a.arena[i][j+k]!='S' && a.arena[i][j+k]!='D' && a.arena[i][j+k]!='T')
				error.errormovement = 1;

			if(a.arena[i][j+k]=='D')	// CHECKING FOR PITS
				{
				current.xmovefinal = i;
				current.ymovefinal = j+k;
				break;
				}
			}
		}

	else if(dx<0 && dy>0 && dx==dy)
		{
		for( int k=0; k<dy; k++)
			{
			if(a.arena[i-k][j+k]!='E' && a.arena[i-k][j+k]!='S' && a.arena[i-k][j+k]!='D' && a.arena[i-k][j+k]!='T')
				error.errormovement = 1;

			if(a.arena[i-k][j+k]=='D')	// CHECKING FOR PITS
				{
				current.xmovefinal = i-k;
				current.ymovefinal = j+k;
				break;
				}
			}
		}

	else if(dx<0 && dy==0)
		{
		for( int k=0; k<abs(dy); k++)
			{
			if(a.arena[i-k][j]!='E' && a.arena[i-k][j]!='S' && a.arena[i-k][j]!='D' && a.arena[i-k][j]!='T')
				error.errormovement = 1;

			if(a.arena[i-k][j]=='D')	// CHECKING FOR PITS
				{
				current.xmovefinal = i-k;
				current.ymovefinal = j;
				break;
				}
			}
		}

	else if(dx<0 && dy<0 && dx==dy)
		{
		for( int k=0; k<abs(dy); k++)
			{
			if(a.arena[i-k][j-k]!='E' && a.arena[i-k][j-k]!='S' && a.arena[i-k][j-k]!='D' && a.arena[i-k][j-k]!='T')
				error.errormovement = 1;

			if(a.arena[i-k][j-k]=='D')	// CHECKING FOR PITS
				{
				current.xmovefinal = i-k;
				current.ymovefinal = j-k;
				break;
				}
			}
		}

	else if(dx==0 && dy<0)
		{
		for( int k=0; k<abs(dy); k++)
			{
			if(a.arena[i][j-k]!='E' && a.arena[i][j-k]!='S' && a.arena[i][j-k]!='D' && a.arena[i][j-k]!='T')
				error.errormovement = 1;

			if(a.arena[i][j-k]=='D')	// CHECKING FOR PITS
				{
				current.xmovefinal = i;
				current.ymovefinal = j-k;
				break;
				}
			}
		}

	else if(dx>0 && dy<0 && dx==dy)
		{
		for( int k=0; k<dx; k++)
			{
			if(a.arena[i+k][j-k]!='E' && a.arena[i+k][j-k]!='S' && a.arena[i+k][j-k]!='D' && a.arena[i+k][j-k]!='T')
				error.errormovement = 1;

			if(a.arena[i+k][j-k]=='D')	// CHECKING FOR PITS
				{
				current.xmovefinal = i+k;
				current.ymovefinal = j-k;
				break;
				}
			}
		}

	else 		error.errormovement = 1;

	if(curflag.agilityflag == 1)		error.errormovement = 1;

		//check if player is moving as well as using a def spell
	if( current.defspellused!=0 && (dx!=0||dy!=0) )
	error.errormovement=1;



				// CALCULATING NO. OF STEPS
	int noofsteps;
	if(dx==0)	noofsteps = abs(dy);
	else if(dy==0)	noofsteps = abs(dx);
	else		noofsteps = abs(dx);


				// cHECKING FOR AGILITY
	int agilityreq;
	agilityreq = noofsteps * 25;
	if(a.arena[current.xmovefinal][current.ymovefinal]=='S')	agilityreq += 25;	// SAFETY POINT LANDING
	if(a.arena[current.xmovefinal][current.ymovefinal]=='D')	agilityreq += 1000;	// PIT LANDING

	if(curflag.fastreductionflag==1)		agilityreq *= 2;
	if(agilityreq>a.myagility)		error.erroragility = 1;



				// CHECKING FOR SPELL POWER
	defspellpowerreq = defspell.spellpower();
	offspellpowerreq = offspell.spellpower();

	if(defspellpowerreq>a.myspellpower)				error.errordefspellpower = 1;
	if(  (a.myspellpower) < (offspellpowerreq+defspellpowerreq) )
	error.erroroffspellpower = 1;

	if(curflag.spellpowerflag == 1)
			{
			 error.errordefspellpower = 1;
			 error.erroroffspellpower = 1;
			}


				// CHECKING FOR STRAIGHT SPELL
	int changeiny = current.yspellfinal - j;
	int changeinx = current.xspellfinal - i;
	int big, small;
	if(changeinx>0)		{ small = i; big = current.xspellfinal; }
	else			{ big = i; small = current.xspellfinal; }
	if(changeinx!=0 && changeiny!=0)
		{
		float slope = changeiny/changeinx;
		for(float x=big; x>=small; x-=0.1)
			{
			float y = slope*(x-current.xspellfinal) + current.yspellfinal;
//			if(a.arena[(int)x][(int)y]=='X')	error.errorspelldirection = 1;
			}
		}

	}   // END OF CHECK















	/******************* UPDATE FUNCTION ************************/

				// UPDATE FUNCTION
void update(input &a,reply &current,reply &previous,flags &curflag,repflags &currepflag,error &error)
	{
	int i,j,health=0;

	spells previousdefspell(previous.defspellused);
	spells previousoffspell(previous.offspellused);
	spells currentdefspell(current.defspellused);
	spells currentoffspell(current.offspellused);

		// FINDING PLAYER'S POSITION
	for( int row=0; row<=14; row++)
		{
		for( int col=0; col<=14; col++)
			{
			if(a.arena[row][col] == 'P' || a.arena[row][col] == '*' || a.arena[row][col] == '#')
			    { i=row ; j=col; }
			}
		}


					// MOVEMENT UPDATION

	if( (!error.errormovement) && (!error.erroragility) )
		{
					// IF FINAL POSITION IS TEMPTATION
		if(a.arena[current.xmovefinal][current.ymovefinal] == 'T')
			{
			a.arena[current.xmovefinal][current.ymovefinal] = 'P';
			a.myhealth += 500;
			a.myspellpower += 200;
			}

					// EMPTY TO EMPTY
		if( (a.arena[current.xmovefinal][current.ymovefinal] == 'E') && (a.arena[i][j]=='P') )
			{
			a.arena[current.xmovefinal][current.ymovefinal] = 'P';
			a.arena[i][j]='E';
			}

					// EMPTY TO SAFETY POINT
		else if( (a.arena[current.xmovefinal][current.ymovefinal] =='S') && (a.arena[i][j]=='P') )
			{
			a.arena[current.xmovefinal][current.ymovefinal] = '*';
			a.arena[i][j]='E';
			}

					// EMPTY TO PIT
		else if( (a.arena[current.xmovefinal][current.ymovefinal] =='D') && (a.arena[i][j]=='P') )
			{
			a.arena[current.xmovefinal][current.ymovefinal] = '#';
			a.arena[i][j]='E';
			}

					// SAFETY POINT TO EMPTY
		else if( (a.arena[current.xmovefinal][current.ymovefinal] =='E') && (a.arena[i][j]=='*') )
			{
			a.arena[current.xmovefinal][current.ymovefinal] = 'P';
			a.arena[i][j]='S';
			}

					// SAFETY POINT TO SAFETY POINT
		else if( (a.arena[current.xmovefinal][current.ymovefinal] =='S') && (a.arena[i][j]=='*') )
			{
			a.arena[current.xmovefinal][current.ymovefinal] = '*';
			a.arena[i][j]='S';
			}

					// SAFETY POINT TO PIT
		else if( (a.arena[current.xmovefinal][current.ymovefinal] =='D') && (a.arena[i][j]=='*') )
			{
			a.arena[current.xmovefinal][current.ymovefinal] = '#';
			a.arena[i][j]='S';
			}

					// PIT TO EMPTY
		else if( (a.arena[current.xmovefinal][current.ymovefinal] =='E') && (a.arena[i][j]=='#') )
			{
			a.arena[current.xmovefinal][current.ymovefinal] = 'P';
			a.arena[i][j]='D';
			}

					// PIT TO SAFETY POINT
		else if( (a.arena[current.xmovefinal][current.ymovefinal] =='S') && (a.arena[i][j]=='#') )
			{
			a.arena[current.xmovefinal][current.ymovefinal] = '*';
			a.arena[i][j]='D';
			}

					// PIT TO PIT
		else if( (a.arena[current.xmovefinal][current.ymovefinal] =='D') && (a.arena[i][j]=='#') )
			{
			a.arena[current.xmovefinal][current.ymovefinal] = '#';
			a.arena[i][j]='D';
			}

		}
	else
		{
			current.xmovefinal=i; current.ymovefinal=j;
			error.errormovement = 0;
		}


					//UPDATION OF HEALTH
	spells object(previous.offspellused);
	if( (14-previous.xspellfinal==current.xmovefinal) && (14-previous.yspellfinal==current.ymovefinal) && (error.errormovement==0) ) 	// i.e. if player is hit
		{
		spellhit = 0;
			if(a.arena[current.xmovefinal][current.ymovefinal]!='*')	// i.e. player is not standing on the safety point
			{
				spellhit = 1;
				health = object.spellhealth();
				curflag = object.initializeflags();
				currepflag = object.initializerepflags();
				
			if( current.defspellused!=0 && current.xmovefinal==i && current.ymovefinal==j )	// i.e. player casts a defensive spell and he does not move
				{
				if(error.errordefspellpower==0)
					health -= currentdefspell.spellhealth();
				}

			if(health>=0)
				{
				a.myhealth -= health;
				}

			if(a.myhealth<=0 || a.opphealth<=0)	stop = 1;
			}
			else
				{
				a.arena[current.xmovefinal][current.ymovefinal] = 'P';
				}
		}

			// AGILITY UPDATION
		if( (error.errormovement==0) && (error.erroragility==0) )
			{
				a.myagility -= agilityreq;
			}

			// SPELL POWER UPDATION
		if( (error.erroroffspellpower==0) && (error.errordefspellpower==0) && (error.errorspelldirection==0) )
			{
			a.myspellpower -= (defspellpowerreq + offspellpowerreq);
			}

		if( error.errordefspellpower==1 )	current.defspellused = 0;
		if( error.erroroffspellpower==1 )	current.offspellused = 0;
		if( error.errorspelldirection==1)	current.offspellused = 0;

	}	// End of update










	/********************** UPDATEFILE FUNCTION ***************/

void updatefile1 (struct input &a, struct reply &current, struct reply &previous, struct error &error)
{
	ofstream of("player1", ios::app);

			// FOR DISPLAYING WHAT YOUR OPPONENT DID LAST TIME
	of<<"\n The defensive spell by your opponent = " << previous.defspellused;
	of<<"\n The defensive movement taken by your opponent = from his initial position to ( " << (14-previous.xmovefinal) << "," << (14-previous.ymovefinal) << " )";
	of<<"\n The spell casted by the opponent = " << previous.offspellused << "\t At the position : ( " << (14-previous.xspellfinal) << "," << (14-previous.yspellfinal) << " )";

			// FOR DISPLAYING OPPONENT's STATS
	of<<"\n\n Opponent's Health left = " << a.opphealth;
	of<<"\n Opponent's Agility left = " << a.oppagility;
	of<<"\n Opponent's Spell power left = " << a.oppspellpower;

			// FOR DISPLAYING ARENA AFTER OPPONENTS ATTACK
	of<<"\n\n\n\t Arena after opponent's attack is as shown below : \n\n";
	for( int i = 0; i <= 14; i++)
		{
		for( int j = 0; j <=14; j++)
			of<<"  "<<a.arena[i][j];
		of<<endl;
		}

			// FOR DISPLAYING WHAT HAS PLAYER DONE ON HIS TURN KEEPING A CHECK ON ERRORS
	if(!error.errordefspellpower)
		of<<"\n The defensive spell casted by you = " << current.defspellused;
	else
		of<<"\n ILLEGAL DEFENSIVE SPELL";

	if(!error.errormovement && !error.erroragility)
		of<<"\n The defensive movement taken by you = from initial position to ( " << current.xmovefinal << "," << current.ymovefinal << " )";
	else
		of<<"\n ILLEGAL MOVEMENT !!";

	if(!error.erroroffspellpower)
		of<<"\n The offensive spell casted by you = " << current.offspellused << "\t At the position : ( " << current.xspellfinal << "," << current.yspellfinal << " )";
	else
		of<<"\n ILLEGAL OFFENSIVE SPELL";

	if(error.errorspelldirection)
		of<<"\n Your offensive spell could not be cast because of illegal direction of your spell";

			// FOR DISPLAYING PLAYER's STATS
	of<<"\n\n Your Health left = " << a.myhealth;
	of<<"\n Your Agility left = " << a.myagility;
	of<<"\n Your Spell power left = " << a.myspellpower;
	of.close();
}



void updatefile2 (struct input a, struct reply current, struct reply previous, struct error error)
{
	ofstream of("player2", ios::app);

			// FOR DISPLAYING WHAT YOUR OPPONENT DID LAST TIME
	of<<"\n The defensive spell by your opponent = " << previous.defspellused;
	of<<"\n The defensive movement taken by your opponent = from his initial position to ( " << (14-previous.xmovefinal) << "," << (14 - previous.ymovefinal)<< " )";
	of<<"\n The spell casted by the opponent = " << previous.offspellused << "\t At the position : ( " << (14-previous.xspellfinal) << "," << (14-previous.yspellfinal) << " )";

			// FOR DISPLAYING OPPONENT's STATS
	of<<"\n\n Opponent's Health left = " << a.opphealth;
	of<<"\n Opponent's Agility left = " << a.oppagility;
	of<<"\n Opponent's Spell power left = " << a.oppspellpower;

			// FOR DISPLAYING ARENA AFTER OPPONENTS ATTACK
	of<<"\n\n\n\t Arena after opponent's attack is as shown below : \n\n";
	for( int i = 0; i <= 14; i++)
		{
		for( int j = 0; j <=14; j++)
			of<<"  "<<a.arena[i][j];
		of<<endl;
		}

			// FOR DISPLAYING WHAT HAS PLAYER DONE ON HIS TURN KEEPING A CHECK ON ERRORS
	if(!error.errordefspellpower)
		of<<"\n The defensive spell casted by you = " << current.defspellused;
	else
		of<<"\n ILLEGAL DEFENSIVE SPELL";

	if(!error.errormovement && !error.erroragility)
		of<<"\n The defensive movement taken by you = from initial position to ( " << current.xmovefinal << "," << current.ymovefinal << " )";
	else
		of<<"\n ILLEGAL MOVEMENT !!";

	if(!error.erroroffspellpower)
		of<<"\n The offensive spell casted by you = " << current.offspellused << "\t At the position : ( " << current.xspellfinal << "," << current.yspellfinal << " )";
	else
		of<<"\n ILLEGAL OFFENSIVE SPELL";

	if(error.errorspelldirection)
		of<<"\n Your offensive spell could not be cast because of illegal direction of your spell";

			// FOR DISPLAYING PLAYER's STATS
	of<<"\n\n Your Health left = " << a.myhealth;
	of<<"\n Your Agility left = " << a.myagility;
	of<<"\n Your Spell power left = " << a.myspellpower;
	of.close();
}







	/***************** MAIN *******************/

int main(int argc, char *argv[])
{
//clrscr();
ofstream a("player1",ios::app);
a.close();
ofstream b("player2",ios::app);
b.close();
ofstream of1("player1",ios::trunc);
of1.close();
ofstream of2("player2",ios::trunc);
of2.close();
ofstream of("records",ios::trunc);
of.close();
	int row, col;
	round = 3;

		// INITIALIZATION OF FLAGS
	p1flag.agilityflag = p2flag.agilityflag = 0;
	p1flag.spellpowerflag = p2flag.spellpowerflag = 0;
	p1flag.fastreductionflag = p2flag.fastreductionflag = 0;

		// INITIALIZATION OF REPFLAGS
	p1repflag.agilityrep = p2repflag.agilityrep = 0;
	p1repflag.spellpowerrep = p2repflag.spellpowerrep = 0;
	p1repflag.fastreductionrep = p2repflag.fastreductionrep = 0;

		// Initialization of stats
	stats.p1health = stats.p2health = 6000;
	stats.p1agility = stats.p2agility = 5000;
	stats.p1spellpower = stats.p2spellpower = 5000;

		// Initialization of reply
	p1reply.xmovefinal = 7;		p1reply.ymovefinal = 3;
	p2reply.xmovefinal = 7;		p2reply.ymovefinal = 11;
	p1reply.defspellused = p2reply.defspellused = 0;
	p1reply.offspellused = p2reply.offspellused = 0;
	p1reply.xspellfinal = p1reply.yspellfinal = 0;
	p2reply.xspellfinal = p2reply.yspellfinal = 0;

			// Initializing Errors to zero
	p1error.errormovement = 0;
	p1error.erroragility = 0;
	p1error.errordefspellpower = 0;
	p1error.erroroffspellpower = 0;
	p1error.errorspelldirection = 0;

			// Initializing Errors to zero
	p2error.errormovement = 0;
	p2error.erroragility = 0;
	p2error.errordefspellpower = 0;
	p2error.erroroffspellpower = 0;
	p2error.errorspelldirection = 0;
	
			// Initializing Records of player 1
	for(row = 0 ; row <=14; row++)
		{
		for (col = 0 ; col <= 14 ; col++)
		      {
			p1record.arena[row][col] = farena[row][col];
		      }
		}

	p1record.defspellused = 0;
	p1record.offspellused = 0;
	p1record.spellhitted = 0;
	p1record.flag.agilityflag = 0;
	p1record.flag.spellpowerflag = 0;
	p1record.flag.fastreductionflag = 0;
	p1record.repflag.agilityrep = 0;
	p1record.repflag.spellpowerrep = 0;
	p1record.repflag.fastreductionrep = 0;

			// Initializing Records of player 2
	for(row = 0 ; row <=14; row++)
		{
		for (col = 0 ; col <= 14 ; col++)
		      {
			p2record.arena[row][col] = farena[row][col];
		      }
		}

	p2record.defspellused = 0;
	p2record.offspellused = 0;
	p2record.spellhitted = 0;
	p2record.flag.agilityflag = 0;
	p2record.flag.spellpowerflag = 0;
	p2record.flag.fastreductionflag = 0;
	p2record.repflag.agilityrep = 0;
	p2record.repflag.spellpowerrep = 0;
	p2record.repflag.fastreductionrep = 0;

	saverecord(p1record);
	saverecord(p2record);

		//FOR MOVES OF PLAYER
	for ( move = 1 ; move <= 500 ; move++)
		{
			//FOR UPDATION OF ARRAY FOR PLAYER 1
		for(row = 0 ; row <=14; row++)
			{
			for (col = 0 ; col <= 14 ; col++)
			      {
				p1input.arena[row][col] = farena[row][col];
				p1record.arena[row][col] = farena[row][col];
			      }
			}

			// FOR UPDATION OF INPUT FOR PLAYER1
		p1input.spellcasted = p2reply.offspellused;
		p1input.myhealth = stats.p1health;
		p1input.myagility = stats.p1agility;
		p1input.myspellpower = stats.p1spellpower;
		p1input.opphealth = stats.p2health;
		p1input.oppagility = stats.p2agility;
		p1input.oppspellpower = stats.p2spellpower;

		setparameters(p1input);

			// CALLING PLAYER 1
		//lp(P_WAIT,"C:\\TC\\BIN\\STRATEGY.exe",NULL);
		pid_t id;
		id=fork();
		if(id==0){
			execlp("./strategy",'\0');
		} 
		int *status;
		waitpid(id,status,WUNTRACED);

		p1reply = readparameters();
		ofstream p1("reply.txt",ios::trunc);
		p1.close();
		check(p1input,p1reply,p1flag,p1repflag,p1error);
		update(p1input,p1reply,p2reply,p1flag,p1repflag,p1error);
		updatefile1(p1input, p1reply, p2reply, p1error);
//		exit(0);
			// UPDATION OF STATS OF PLAYER 1
		stats.p1health = p1input.myhealth;
		stats.p1agility = p1input.myagility;
		stats.p1spellpower = p1input.myspellpower;
		stats.p2health = p1input.opphealth;



			// Updation of record file
		p1record.defspellused = p1reply.defspellused;
		p1record.offspellused = p1reply.offspellused;
		p1record.spellhitted = spellhit;
		p1record.flag.agilityflag = p1flag.agilityflag;
		p1record.flag.spellpowerflag = p1flag.spellpowerflag;
		p1record.flag.fastreductionflag = p1flag.fastreductionflag;
		p1record.repflag.agilityrep = p1repflag.agilityrep;
		p1record.repflag.spellpowerrep = p1repflag.spellpowerrep;
		p1record.repflag.fastreductionrep = p1repflag.fastreductionrep;

		saverecord(p1record);
//		exit(0);
			// UPDATING FARENA AFTER PLAYER 1 TURN
		for(row=0; row<=14; row++)
			{
			for(col=0; col<=14; col++)
				{
				farena[row][col] = p1input.arena[row][col];
				}
			}

			// FOR UPDATION OF INPUT FOR PLAYER2
		p2input.spellcasted = p1reply.offspellused;
		p2input.myhealth = stats.p2health;
		p2input.myagility = stats.p2agility;
		p2input.myspellpower = stats.p2spellpower;
		p2input.opphealth = stats.p1health;
		p2input.oppagility = stats.p1agility;
		p2input.oppspellpower = stats.p1spellpower;

			// FOR UPDATION OF ARRAY FOR PLAYER 2
		for(row=0 ; row<=14; row++)
			{
			for(col=0; col<=14; col++)
				{
				if(farena[14-row][14-col] == 'P')	p2input.arena[row][col] = 'O';
				else if(farena[14-row][14-col] == 'O')	p2input.arena[row][col] = 'P';
				else if(farena[14-row][14-col] == '*')	p2input.arena[row][col] = '@';
				else if(farena[14-row][14-col] == '@')	p2input.arena[row][col] = '*';
				else if(farena[14-row][14-col] == '$')	p2input.arena[row][col] = '#';
				else if(farena[14-row][14-col] == '#')	p2input.arena[row][col] = '$';
				else	p2input.arena[row][col] = farena[14-row][14-col];
				}
			}

			// Updation of array to be sent to record
		for(row=0; row<=14; row++)
			{
			for(col=0; col<=14; col++)
				{
				p2record.arena[row][col] = p2input.arena[row][col];
				}
			}


		setparameters(p2input);


			// CALLING PLAYER 2
		//spawnlp(P_WAIT,"strategy.exe",NULL);
		pid_t id2;
		id2=fork();
		if(id2==0){
			cout<<"here";
			execlp("./strategy",'\0');
		}
		int *status2;
		waitpid(id2,status2,WUNTRACED);

		p2reply = readparameters();
		ofstream p2("reply.txt",ios::trunc);
		p2.close();
		p2reply.xmovefinal = 14 - p2reply.xmovefinal;      // To change coordinates with respect to player 1
		p2reply.ymovefinal = 14 - p2reply.ymovefinal;
		check(p2input,p2reply,p2flag,p2repflag,p2error);
		update(p2input,p2reply,p1reply,p2flag,p2repflag,p2error);

			// UPDATION OF STATS OF PLAYER 2
		stats.p2health = p2input.myhealth;
		stats.p2agility = p2input.myagility;
		stats.p2spellpower = p2input.myspellpower;
		stats.p1health = p2input.opphealth;


		updatefile2(p2input, p2reply, p1reply, p2error);

			// Updation of record file
		p2record.defspellused = p2reply.defspellused;
		p2record.offspellused = p2reply.offspellused;
		p2record.spellhitted = spellhit;
		p2record.flag.agilityflag = p2flag.agilityflag;
		p2record.flag.spellpowerflag = p2flag.spellpowerflag;
		p2record.flag.fastreductionflag = p2flag.fastreductionflag;
		p2record.repflag.agilityrep = p2repflag.agilityrep;
		p2record.repflag.spellpowerrep = p2repflag.spellpowerrep;
		p2record.repflag.fastreductionrep = p2repflag.fastreductionrep;

		saverecord(p2record);
//		exit(0);
			// UPDATING FARENA AFTER PLAYER 2 TURN
		for(int row=0; row<=14; row++)
			{
			for( int col=0; col<=14; col++)
				{
				if(p2input.arena[row][col] == '*')		farena[14-row][14-col] = '@';
				else if(p2input.arena[row][col] == '@')		farena[14-row][14-col] = '*';
				else if(p2input.arena[row][col] == 'P')		farena[14-row][14-col] = 'O';
				else if(p2input.arena[row][col] == 'O')		farena[14-row][14-col] = 'P';
				else if(p2input.arena[row][col] == '$')		farena[14-row][14-col] = '#';
				else if(p2input.arena[row][col] == '#')		farena[14-row][14-col] = '$';
				else farena[14-row][14-col] = p2input.arena[row][col];
				}
			}
		if(stop)	exit(0);
		} // end of for loop
return 0;	
}  // End of main








