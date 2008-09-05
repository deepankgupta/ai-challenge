#include<fstream.h>
#include <iostream.h>
struct input
	{
	char arena[15][15];
	int spellcasted;
	int myhealth, myagility, myspellpower;
	int opphealth, oppagility, oppspellpower;
	};


struct reply
	{
	int xmovefinal,ymovefinal;	// final position coordinates where player intends to move
	int defspellused;
	int offspellused;
	int xspellfinal,yspellfinal;		// target of offensive spell
	};

struct playerstats
	{
	int p1health, p2health;
	int p1spellpower, p2spellpower;
	int p1agility, p2agility;
	};

struct repflags
	{
	int agilityrep;
	int spellpowerrep;
	int fastreductionrep;
	};

struct flags
	{
	int agilityflag;
	int spellpowerflag;
	int fastreductionflag;
	};

struct error
	{
	int errormovement ;
	int erroragility;
	int erroroffspellpower;
	int errordefspellpower;
	};

struct recordio
	{
	char arena[15][15];	// before turn reply
	int defspellused;	// after reply
	int offspellused;
	int spellhitted;
	flags flag;
	repflags repflag;
	};

class spells
	{
	private:

	int spell;
	int health;
	int spellpow;
	struct flags flag;
	struct repflags repflag;

	public:

	spells( int spellcode);
	int spellhealth(void);
	int spellpower(void);
	flags initializeflags(void);
	repflags initializerepflags(void);
	};

struct input objinput;
struct reply objreply;

input getparameters(void);
void setparameters(input);
reply readparameters(void);
void saveparameters(reply);


void saverecord(recordio record);


class spellhistory
{
	public:
	int lastspellhitopp();
	int lastspellhitplayer();
	int defspellplayer(int n);
	int defspellopp(int n);
	int offspellplayer(int n);
	int offspellopp(int n);
};
class arenahistory
{
	public:
	char arena[15][15];
	void arenasituation(int n);
};
class status
{
	public:
	int agilitystatusplayer();
	int agilitystatusopp();
	int spellpowerstatusplayer();
	int spellpowerstatusopp();
	int agilityreductionstatusplayer();
	int agilityreductionstatusopp();
};


