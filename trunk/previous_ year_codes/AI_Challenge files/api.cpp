#include<fstream>
#include <iostream>
#include"api.h"

using namespace std;
/*
farena[15][15]={

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

*/

struct input objinput;
struct reply objreply;

spells::spells( int spellcode)
	{
	spell=spellcode;
		switch(spell)
		{
		    case 0 :
			health = 0;
			spellpow = 0;
			break;
		    case 1 :
			health = 150;
			spellpow = 30;
			break;
		    case 2 :
			health = 200;
			spellpow = 40;
			break;
		    case 3 :
			health = 225;
			spellpow = 45;
			break;
		    case 4 :
			health = 250;
			spellpow = 50;
			break;
		    case 5 :
			health = 275;
			spellpow = 55;
			break;
		    case 6 :
			 health = 0;
			 spellpow = 60;
			 break;
		    case 7 :
			 health = 0;
			 spellpow = 500;
			 break;
		    case 8 :
			 health = 0;
			 spellpow = 125;
			 break;
		    case 9 :
			 health = 0;
			 spellpow = 150;
			 break;
		    case 10 :
			 health = 0;
			 spellpow = 250;
			 break;
		    case 11 :		//levicorpus    round 2
			 health = 750;
			 spellpow = 150;
			 break;
		    case 12 :
			 health = 0;	//stupefy or stunner    round 2
			 spellpow =200;
			 break;
		    case 13 :
			 health = 5000;	//avada kedavara
			 spellpow = 750;
			 break;
		    case 14 :
			 health = 2000;	//sectumsempra
			 spellpow = 400;
			 break;
		    case 15 :
			 health = 100;	//petrificus totalus
			 spellpow = 350;
			 break;
		    case 16 :
			 health = 0;	//finite incantatum
			 spellpow = 250;
			 break;
		    case 17 :
			 health = 1000;	//anapneo
			 spellpow = 225;
			 break;
		    default:
			 health = 0;
			 spellpow =0;
			 break;
		}
	}
int spells::spellhealth(void)
	{
	return health;
	}
int spells::spellpower(void)
	{
	return spellpow;
	}
flags spells::initializeflags(void)
	{
	flag.agilityflag=0;
	flag.spellpowerflag=0;
	flag.fastreductionflag=0;
	switch(spell)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		      break;
		case 6:
		      flag.fastreductionflag=1;
		      break;
		case 7:
		      flag.spellpowerflag=1;
		      break;
		case 8:
		      flag.spellpowerflag=1;
		      break;
		case 9:
		      flag.agilityflag=1;
		      break;
		case 10:
		case 11:
		      break;
		case 12:
		      flag.agilityflag=1;
		      flag.spellpowerflag=1;
		      break;
		case 13:
		case 14:
		      break;
		case 15:
		      flag.agilityflag=1;
		      flag.spellpowerflag=1;
		      break;
		case 16:
		case 17:
		default:
		      break;
		}
	return flag;
	}
repflags spells::initializerepflags(void)
	{
	repflag.agilityrep=0;
	repflag.spellpowerrep=0;
	repflag.fastreductionrep=0;
	switch(spell)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		      break;
		case 6:
		      repflag.fastreductionrep=2;
		      break;
		case 7:
		      repflag.spellpowerrep=10000;
		      break;
		case 8:
		      repflag.spellpowerrep=4;
		      break;
		case 9:
		      repflag.agilityrep=2;
		      break;
		case 10:
		case 11:
		      break;
		case 12:
		      repflag.agilityrep=2;
		      repflag.spellpowerrep=2;
		      break;
		case 13:
		case 14:
		      break;
		case 15:
		      repflag.agilityrep=2;
		      repflag.spellpowerrep=2;
		      break;
		case 16:
		case 17:
		default:
		      break;
		}
	return repflag;
	}

/******************************************END OF CONSTANTS.H ***********************************************/


void setparameters( input objinput1)
{
	ofstream f("input.txt");
	if(f!=NULL)
	f.write((char*)&objinput1,sizeof(objinput1));
	f.close();
}

input getparameters(void)
{
	ifstream f("input.txt");
	if(f!=NULL)
	f.read((char*)&objinput,sizeof(objinput));
	f.close();
	return (objinput);
}

void saveparameters(reply objreply1)
{
	cout<<"vijay";
	ofstream f("reply.txt");
	if(f!=NULL)
	{
	cout<<"kumar";
	f.write((char*)&objreply1,sizeof(objreply1));
	
	}
	f.close();
}

reply readparameters(void)
{
	ifstream f("reply.txt");
	if(f!=NULL)
	f.read((char*)&objreply,sizeof(objreply));
	f.close();
	return (objreply);
}

void saverecord(recordio record)
{
	ofstream fout("records.txt",ios::binary|ios::app);
	if(fout!=NULL)
	{
		fout.seekp(0,ios::end);
		fout.write((char*)&record,sizeof(record));
	}
	fout.close();
}

int spellhistory::lastspellhitopp()
	{
		int flag=0;
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			long l1=fin.tellg();
			fin.seekg(-sizeof(record),ios::end);
			while(flag==0)
			{
				if(fin.tellg()<=l1)
				{
					flag=1;
					fin.read((char*)&record,sizeof(record));
				}
				else
				{
					fin.read((char*)&record,sizeof(record));
				}
				if(record.spellhitted!=0)
				{
					flag=1;
				}
				else
				{
					fin.seekg(-(3*sizeof(record)),ios::cur);
				}
			}
		}
		fin.close();
		return record.spellhitted;
	}
int spellhistory::lastspellhitplayer()
	{
		int flag=0;
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			long l1=fin.tellg();
			fin.seekg(-(2*sizeof(record)),ios::end);
			while(flag==0)
				{
				if(fin.tellg()<=l1)
				{
					flag=1;
				}
				fin.read((char*)&record,sizeof(record));
				if(record.spellhitted!=0)
					{
					flag=1;
					}
				else
					{
					fin.seekg(-(3*sizeof(record)),ios::cur);
					}
				}
		}
		fin.close();
		return record.spellhitted;
	}
int spellhistory::defspellplayer(int n)
	{
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			fin.seekg(-(2*n*sizeof(record)),ios::end);
			fin.read((char*)&record,sizeof(record));
		}
		fin.close();
		return record.defspellused;
	}
int spellhistory::defspellopp(int n)
	{
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			fin.seekg(-((2*n-1)*sizeof(record)),ios::end);
			fin.read((char*)&record,sizeof(record));
		}
		fin.close();
		return record.defspellused;
	}
int spellhistory::offspellplayer(int n)
	{
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			fin.seekg(-(2*n*sizeof(record)),ios::end);
			fin.read((char*)&record,sizeof(record));
		}
		fin.close();
		return record.offspellused;
	}
int spellhistory::offspellopp(int n)
	{
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			fin.seekg(-((2*n+1)*sizeof(record)),ios::end);
			fin.read((char*)&record,sizeof(record));
		}
		fin.close();
		return record.offspellused;
	}


void arenahistory::arenasituation(int n)
	{
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			fin.seekg(-(2*n*sizeof(record)),ios::end);
			fin.read((char*)&record,sizeof(record));
		}
		fin.close();
		for(int i=0;i<15;i++)
		{
			for(int j=0;j<15;j++)
			{
				arena[i][j]=record.arena[i][j];
			}
		}
	}

int status::agilitystatusplayer()
	{
		int status;
		recordio record;
		ifstream fin("records.txt",ios::binary);
		fin.seekg(-(2*sizeof(record)),ios::end);
		fin.read((char*)&record,sizeof(record));
		fin.close();
		if(record.flag.agilityflag==1)
		{
			status=record.repflag.agilityrep;
		}
		else
		{
			status=0;
		}
		return status;
	}
int status::agilitystatusopp()
	{
		int status;
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			fin.seekg(-sizeof(record),ios::end);
			fin.read((char*)&record,sizeof(record));
		}
		fin.close();
		if(record.flag.agilityflag==1)
		{
			status=record.repflag.agilityrep;
		}
		else
		{
			status=0;
		}
		return status;
	}
int status::spellpowerstatusplayer()
	{
		int status;
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			fin.seekg(-(2*sizeof(record)),ios::end);
			fin.read((char*)&record,sizeof(record));
		}
		fin.close();
		if(record.flag.spellpowerflag==1)
		{
			status=record.repflag.spellpowerrep;
		}
		else
		{
			status=0;
		}
		return status;
	}
int status::spellpowerstatusopp()
	{
		int status;
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			fin.seekg(-sizeof(record),ios::end);
			fin.read((char*)&record,sizeof(record));
		}
		fin.close();
		if(record.flag.spellpowerflag==1)
		{
			status=record.repflag.spellpowerrep;
		}
		else
		{
			status=0;
		}
		return status;
	}
int status::agilityreductionstatusplayer()
	{
		int status;
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			fin.seekg(-(2*sizeof(record)),ios::end);
			fin.read((char*)&record,sizeof(record));
		}
		fin.close();
		if(record.flag.fastreductionflag==1)
		{
			status=record.repflag.fastreductionrep;
		}
		else
		{
			status=0;
		}
		return status;
	}
int status::agilityreductionstatusopp()
	{
		int status;
		recordio record;
		ifstream fin("records.txt",ios::binary);
		if(fin!=NULL)
		{
			fin.seekg(-sizeof(record),ios::end);
			fin.read((char*)&record,sizeof(record));
		}
		fin.close();
		if(record.flag.fastreductionflag==1)
		{
			status=record.repflag.fastreductionrep;
		}
		else
		{
			status=0;
		}
		return status;
	}

