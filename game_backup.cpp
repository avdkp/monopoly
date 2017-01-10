#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
class boxes
{
public:
	char name[10],owner[10],upgraded;
	int price,no;
}box[36];

class player
{
  public:
	int no,balance,loan,color,cards,no_of_upgraded_sites,last_throw,jail_pt;
	char name[6],cursur,bankrupted;
}plyr[3],bank;

char Save[5][10];
int const UNO_COLOR=2;
int const CHANCE_COLOR=6;


void box_display();
void initialise_boxes();
void start();
void start_menu();
int throw_dice();
void initialise_players();
void execute(player *plr);
void sec_card(player *plr);
void loan(player *plr);
void country(player *plr);
void bankrupt(player *plr);

void save();
void load();

void uno(player *plr);
void chance(player *plr);
void jail(player *plr);
void upgrade(player *);

void main()
{

clrscr();
getch();;
//delay(5000);
//throw_dice();
start();
while(1)
	{
		int x=0;
		clrscr();
		start_menu();
			while(1)
			{	
				flag1:
				clrscr();
				box_display();
				for(int i=0;i<160;++i)
				cprintf("\b");
				int choice;
				if(plyr[x].balance<0)
				bankrupt(&plyr[x]);
				if(plyr[x].jail_pt==0&&plyr[x].bankrupted=='n')
				{
					textcolor(plyr[x].color);
					cprintf("%c%s",'\n',plyr[x].name);
					cout<<"'s turn...\n";
					
					flag:
					if(x==0)
					{
						cout<<"\n1.throw dice\t\t2.pay loan\t\t3.save\t\t4.exit\t\t\tchoice...";			
							cin>>choice;
						if(choice<1||choice>4)												//any invalid choice will be considered 1;
							choice=1;
					}
					else
					{
						cout<<"\n1.throw dice\t\t2.pay loan\t\t\tchoice...";
							cin>>choice;
						if(choice>2||choice<1)
							choice=1;
					}
					int p_no;
					switch(choice)
					{
						case 1: p_no=plyr[x].no;
								plyr[x].last_throw=throw_dice();
								cout<<"\nyou got..."<<plyr[x].last_throw;
								getch();
								plyr[x].no +=plyr[x].last_throw;
								if(plyr[x].no<36&&plyr[x].no>24&&p_no<12&&p_no>=0)
								{
									cout<<"\nyou got Rs.1500 for crossing";
									plyr[x].balance +=1500;
									bank.balance -=1500;
									getch();
								}
								if(plyr[x].no>35)
									plyr[x].no -=36;
								clrscr();
								box_display();
								execute(&plyr[x]);
								break;
						case 2:if(plyr[x].balance>3000&&plyr[x].loan==3000)
								{
									plyr[x].balance -=3000;
									bank.balance +=3000;
									cout<<"\nloan paid";	
								}
								else if(plyr[x].loan==0)
									cout<<"\nYou don't have any loan";
								else if(plyr[x].loan==0)
									cout<<"\nYou don't have any loan";
								goto flag;
						case 3:save();
								goto flag1;
						case 4:	clrscr();
								exit(1);
								
					}

				}
				else if(plyr[x].jail_pt==1)
				{
					plyr[x].jail_pt--;
					plyr[x].balance -=500;
				}
				else
					plyr[x].jail_pt--;
				
				x++;
				if(x>2)
				x=x-3;
			}
			
				
	}
}


void save()
{
int choice;
prev_menu:
clrscr();

	for(int j=0;j<55;++j)
	{
		gotoxy(25,j);
		textcolor(15);
		cprintf(".");
	}
	for(int j=54;j>0;--j)
	{
		gotoxy(135,j);
		textcolor(15);
		cprintf(".");
	}
	for(int j=0;j<160;++j)
	{
		gotoxy(j,14);
		textcolor(15);
		cprintf(".  ");
	}
	for(int j=0;j<160;++j)
	{
		gotoxy(j,40);
		textcolor(15);
		cprintf(".  ");
	}

	gotoxy(75,16);
	textcolor(15);
	cprintf("SELECT PROFILE");
	for(int i=0;i<5;++i)
		if(strlen(Save[i])>0)
		Save[i][strlen(Save[i])-4]='\0';

	gotoxy(75,21);
	textcolor(15);
	cprintf("1.%s",Save[0]);
	gotoxy(75,23);
	textcolor(15);
	cprintf("2.%s",Save[1]);
	gotoxy(75,25);
	textcolor(15);
	cprintf("3.%s",Save[2]);
	gotoxy(75,27);
	textcolor(15);
	cprintf("4.%s",Save[3]);
	gotoxy(75,29);
	textcolor(15);
	cprintf("5.%s",Save[4]);
	
	gotoxy(68,33);
	textcolor(15);
	cprintf("Enter your choice..");
	cin>>choice;
	if(choice>5||choice<1)
	choice=1;
	int i=0;
		gotoxy(68,35);
		textcolor(15);
		cprintf("Give a name to profile...");
			
			gets(Save[choice-1]);
			
		strcat(Save[choice-1],".txt");
		
		ofstream fout;
		fout.open(Save[choice-1],ios::out);
				
		
		for(int i=0;i<36;++i)
			fout<<box[i].owner<<'\n'<<box[i].upgraded<<'\n'<<box[i].price<<'\n'<<box[i].no<<'\n';
		
		for(int i=0;i<3;++i)
			{
			fout<<plyr[i].no<<'\n'<<plyr[i].name<<'\n'<<plyr[i].color<<'\n'<<plyr[i].cursur<<'\n'<<plyr[i].balance<<'\n'<<plyr[i].cards<<'\n'<<plyr[i].last_throw<<'\n';
			fout<<plyr[i].loan<<'\n'<<plyr[i].cards<<'\n'<<plyr[i].jail_pt<<'\n'<<plyr[i].bankrupted<<'\n'<<plyr[i].no_of_upgraded_sites<<'\n';
			}
			fout<<bank.balance<<'\n'<<bank.loan<<'\n';

				gotoxy(68,38);
				textcolor(15);
				cprintf("Saved successfully...");
getch();
}

void load()
{
	int choice;
	prev_menu:
	clrscr();

	for(int j=0;j<55;++j)
	{
		gotoxy(25,j);
		textcolor(15);
		cprintf(".");
	}
	for(int j=54;j>0;--j)
	{
		gotoxy(135,j);
		textcolor(15);
		cprintf(".");
	}
	for(int j=0;j<160;++j)
	{
		gotoxy(j,14);
		textcolor(15);
		cprintf(".  ");
	}
	for(int j=0;j<160;++j)
	{
		gotoxy(j,40);
		textcolor(15);
		cprintf(".  ");
	}

	gotoxy(75,16);
	textcolor(15);
	cprintf("SELECT PROFILE");

	gotoxy(75,21);
	textcolor(15);
	cprintf("1.%s",Save[0]);
	gotoxy(75,23);
	textcolor(15);
	cprintf("2.%s",Save[1]);
	gotoxy(75,25);
	textcolor(15);
	cprintf("3.%s",Save[2]);
	gotoxy(75,27);
	textcolor(15);
	cprintf("4.%s",Save[3]);
	gotoxy(75,29);
	textcolor(15);
	cprintf("5.%s",Save[4]);
	
	gotoxy(68,33);
	textcolor(15);
	cprintf("Enter your choice..");
	cin>>choice;
	if(choice>5||choice<1)
	choice=1;
			
		
		ifstream f_in;
		f_in.open("avd.txt",ios::in);
				
		if(f_in==0)
			{
				gotoxy(68,37);
				textcolor(15);
				cprintf("load failed !!! try again...");
				getch();
				goto prev_menu;
			}
			f_in.seekg(0);
			char ch;
		for(int i=0;i<36;++i)
		{
			f_in>>box[i].owner;
			 
			f_in>>box[i].upgraded;
			   
			f_in>>box[i].price;
			   
			f_in>>box[i].no;
			   
		}
		for(int i=0;i<3;++i)
			{
				f_in>>plyr[i].no;
				   
				f_in>>plyr[i].name;
				   
				f_in>>plyr[i].color;
				   
				f_in>>plyr[i].cursur;
				   
				f_in>>plyr[i].balance;
				   
				f_in>>plyr[i].cards;
				   
				f_in>>plyr[i].last_throw;
				   
				f_in>>plyr[i].loan;
				   
				f_in>>plyr[i].cards;
				   
				f_in>>plyr[i].jail_pt;
				   
				f_in>>plyr[i].bankrupted;
				   
				f_in>>plyr[i].no_of_upgraded_sites;
				   
			}
			f_in>>bank.balance;
			   
			f_in>>bank.loan;

						
		for(int i=0;i<36;++i)
		{
			cout<<box[i].owner;
			//cout<<ch;
			cout<<box[i].upgraded;
			//cout<<ch;
			cout<<box[i].price;
			//cout<<ch;
			cout<<box[i].no;
			//cout<<ch;
		}
				
		for(int i=0;i<3;++i)
		{
			cout<<plyr[i].no;
			//cout<<ch;
			cout<<plyr[i].name;
			//cout<<ch;
			cout<<plyr[i].color;
			//cout<<ch;
			cout<<plyr[i].cursur;
			//cout<<ch;
			cout<<plyr[i].balance;
			//cout<<ch;
			cout<<plyr[i].cards;
			//cout<<ch;
			cout<<plyr[i].last_throw;
			//cout<<ch;
			cout<<plyr[i].loan;
			//cout<<ch;
			cout<<plyr[i].cards;
			//cout<<ch;
			cout<<plyr[i].jail_pt;
			//cout<<ch;
			cout<<plyr[i].bankrupted;
			//cout<<ch;
			cout<<plyr[i].no_of_upgraded_sites;
			//cout<<ch; 
		}
				gotoxy(68,38);
				textcolor(15);
				cprintf("loaded successfully...");
getch();
}




void upgrade(player *plr)
{
	char ch='n';
	if(plr->balance<5*box[plr->no].price&&plr->loan==3000)
	{
		cout<<"\nyou don't have enough balance";
		return;
	}
	else if(plr->balance>=5*box[plr->no].price-3000&&plr->loan==0)
	{
		cout<<"\n you will have to take loan. continue...(y/n)...";
		ch=getch();
		if(ch=='y'||ch=='Y')
		loan(plr);
		else
		return;
		plr->balance -=5*box[plr->no].price;
		bank.balance +=5*box[plr->no].price;
		box[plr->no].price=10*box[plr->no].price;
		box[plr->no].upgraded='y';
	}
	else
	{
		plr->balance -=5*box[plr->no].price;
		bank.balance +=5*box[plr->no].price;
		box[plr->no].price=10*box[plr->no].price;
		box[plr->no].upgraded='y';
	}

}



void jail(player *plr)
{
	for(int i=0;i<3;++i)
	{
		if(plyr[i].jail_pt>0)
		{
			plyr[i].jail_pt=0;
			cout<<"\n";
			textcolor(plyr[i].color);
			cprintf("%s",plyr[i].name);
			cout<<",you will have to come out of jail";
		}
	}
	plr->jail_pt=3;
}




void execute(player *plr)
{
	switch(plr->no)
	{
		case 0:
				break;

		case 1:country(plr);
				break;
		case 2:country(plr);
				break;
		case 3:sec_card(plr);
				break;
		case 4:uno(plr);
				break;
		case 5:country(plr);
				break;
		case 6:country(plr);
				break;
		case 7:sec_card(plr);
				break;
		case 8:country(plr);
				break;

		case 9: if(plr->balance<1000&&plr->loan==0)
				{
					loan(plr);
				}
				if(plr->balance<200)
				{
					cout<<"BANKRUPTED !!!";
					bankrupt(plr);
					break;
				}
				else
				plr->balance -=400;
				for(int i=0;i<3;++i)
				{
					if(strcmp(plyr[i].name,(plr->name))!=0)
					{
						cout<<"\nPaid Rs.200 to \"";
						textcolor(plyr[i].color);
						cprintf("%s",plyr[i].name);
						cout<<"\"";
						plyr[i].balance +=200;
					}
				}
				getch();
				break;

		case 10:country(plr);
				break;
		case 11:country(plr);
				break;
		case 12:chance(plr);
				break;

		case 13:sec_card(plr);
				break;

		case 14:if(plr->balance<1000&&plr->loan==0)
				{
					loan(plr);
				}
				if(plr->balance<1000)
				{
					cout<<"BANKRUPTED !!!";
					bankrupt(plr);
					getch();
					break;
				}
				plr->balance -=1000;
				cout<<"\nRs.1000 paid to bank";
				getch();
				break;

		case 15:
		case 16:
		case 17:country(plr);
				break;

		case 18:for(int i=0;i<3;++i)
				{
					if(plyr[i].balance<1000&&plyr[i].loan==0)
					{
						loan(plr);
					}
					if(plyr[i].balance<200)
					{
						bankrupt(&plyr[i]);
						break;
					}
					if(strcmp(plyr[i].name,plr->name)!=0)
					{
						cout<<"\nTaken Rs.200 from \"";
						textcolor(plyr[i].color);
						cprintf("%s",plyr[i].name);
						cout<<"\"";
						plyr[i].balance -=200;
					}
				}
				plr->balance +=400;
				getch();
				break;

		case 19:
		case 20:country(plr);
				break;
		case 21:if(plr->balance<500&&plr->loan==0)
				{
				loan(plr);
				}
				if(plr->balance<500)
				{
					bankrupt(plr);
					break;
				}
				else
				plr->balance -=1000;
				break;
		case 22:uno(plr);
				break;
		case 23:sec_card(plr);
				break;
		case 24:
		case 25:
		case 26:country(plr);
				break;
		case 27:plr->jail_pt=3;
				break;
		case 28:country(plr);
				break;
		case 29:sec_card(plr);
				break;
		case 30:chance(plr);
				break;
		case 31:
		case 32:country(plr);
				break;
		case 33:sec_card(plr);
				break;
				
		case 34:
		case 35:country(plr);
				break;
	}
}


void uno(player *plr)
{
	switch(plr->last_throw)
		{
			case 2:for(int i=0;i<3;++i)
					plyr[i].balance -=500;
					
					plr->balance +=1500;
					cout<<"Rs. 500 taken from each player...";
					getch();
					break;
			case 3:plr->no=27;
					jail(plr);
					cout<<"\nYou won't have your turn  times and you will have to pay Rs.500";
					getch();
					break;
					
			case 4:plr->balance +=2500;
					bank.balance -=2500;
					cout<<"\ncongrates you won 2500";
					getch();
					break;
					
			case 5:plr->balance -=1000;
					bank.balance +=1000;
					cout<<"\naccident due to wrong driving loss of Rs. 1000.";
					getch();
					break;
			case 6:plr->balance +=2000;
					bank.balance -=2000;
					cout<<"\nIncome tax refund 2000";
					getch();
					break;
			case 7:plr->balance -=1000;;
					bank.balance +=1000;
					cout<<"\npaid Rs. 1000 for health insurance.";
					getch();
					break;
			case 8:plr->balance +=1500;;
					bank.balance -=1500;
					cout<<"\nprofit on shares Rs. 1500.";
					getch();
					break;
			case 9:plr->balance -=2000;;
					bank.balance +=2000;
					cout<<"\nloss on shares Rs. 2000.";
					getch();
					break;
			case 10:for(int i=0;i<3;++i)
					plyr[i].balance -=200;
					plr->balance +=600;
					cout<<"Rs. 200 taken from each player...";
					plr->no=18;
					getch();
					break;
		
			case 11:plr->balance -=4000;;
					bank.balance +=4000;
					cout<<"\nbusiness loss Rs. 4000.";
					getch();
					break;
		
			case 12:plr->balance +=5000;;
					bank.balance -=5000;
					cout<<"\nbusiness profit Rs. 5000.";
					getch();
					break;
		}
}


void chance(player *plr)
{

	switch(plr->last_throw)
		{
			case 2:plr->balance -=100*(plr->cards);
					cout<<"\nrepairing sites @100 for each site";
					getch();
					break;
			case 3:for(int i=0;i<3;++i)
					plyr[i].balance -=200;
					plr->no=18;
					plr->balance +=600;
					cout<<"Rs. 200 taken from each player...";
					getch();
					break;
					
			case 4:plr->balance -=1000;
					bank.balance +=1000;
					cout<<"\nPaid 1000 income tax";
					getch();
					break;
					
			case 5:plr->balance +=1200;
					bank.balance -=1200;
					cout<<"\ncongrates you won lottery Rs.1200";
					getch();
					break;
			case 6:plr->balance -=1000;
					bank.balance +=1000;
					cout<<"\nWrong driving fine Rs. 1000.";
					getch();
					break;
			case 7:plr->balance +=1500;
					bank.balance -=1000;
					cout<<"\naid from world bank Rs. 1500.";
					getch();
					break;
			case 8:plr->no=27;
					jail(plr);
					cout<<"\nYou won't have your turn 3 times and you will have to pay Rs.500";
					getch();
					break;
			case 9:plr->balance +=1500;
					bank.balance -=1500;
					plr->no =0;
					getch();
					break;
			case 10:plr->balance -=2500;
					bank.balance +=2500;
					cout<<"Loss due to fire in godown Rs. 2500.";
					getch();
					break;
		
			case 11:plr->balance +=3000;;
					bank.balance -=3000;
					cout<<"\nBusiness profit Rs. 3000.";
					getch();
					break;
		
			case 12:plr->balance -=5000;;
					bank.balance +=5000;
					cout<<"\nMarket crash Rs. 5000.";
					getch();
					break;
		}
}


void initialise_boxes()
{
	for(int i=0;i<36;++i)
	box[i].no=i;
	

	for(int i=0;i<36;++i)
	box[i].upgraded='n';
	
	for(int i=0;i<36;++i)
	strcpy(box[i].owner,"BANK");
	
	//box.name
	{
	strcpy(box[0].name,"START");
	strcpy(box[1].name,"England");
	strcpy(box[2].name,"Iraq");
	strcpy(box[3].name,"Waterways");
	strcpy(box[4].name,"UNO");
	strcpy(box[5].name,"France");
	strcpy(box[6].name,"Nepal");
	strcpy(box[7].name,"Satellite");
	strcpy(box[8].name,"Russia");
	strcpy(box[9].name,"RESORT");
	strcpy(box[10].name,"Canada");
	strcpy(box[11].name,"Germany");
	strcpy(box[12].name,"Chance");
	strcpy(box[13].name,"Airways");
	strcpy(box[14].name,"Cstm Duty");
	strcpy(box[15].name,"Singapore");
	strcpy(box[16].name,"Iran");
	strcpy(box[17].name,"Pakistan");
	strcpy(box[18].name,"PARTY");
	strcpy(box[19].name,"Japan");
	strcpy(box[20].name,"USA");
	strcpy(box[21].name,"Trvl Duty");
	strcpy(box[22].name,"UNO");
	strcpy(box[23].name,"Roadways");
	strcpy(box[24].name,"Mexico");
	strcpy(box[25].name,"Brazil");
	strcpy(box[26].name,"Australia");
	strcpy(box[27].name,"JAIL");
	strcpy(box[28].name,"India");
	strcpy(box[29].name,"Patrolium");
	strcpy(box[30].name,"Chance");
	strcpy(box[31].name,"UAE");
	strcpy(box[32].name,"China");
	strcpy(box[33].name,"Railways");
	strcpy(box[34].name,"Italy");
	strcpy(box[35].name,"Spain");
	}
	//box.price
	{
	box[1].price=3500;
	box[2].price=2000;
	box[3].price=7000;
	box[4].price=0;
	box[5].price=3000;
	box[6].price=1000;
	box[7].price=2000;
	box[8].price=5000;
	box[9].price=200;
	box[10].price=4000;
	box[11].price=4500;
	box[12].price=0;
	box[13].price=10000;
	box[14].price=1000;
	box[15].price=2500;
	box[16].price=3000;
	box[17].price=2000;
	box[18].price=200;
	box[19].price=4000;
	box[20].price=8000;
	box[21].price=500;
	box[22].price=0;
	box[23].price=2000;
	box[24].price=3500;
	box[25].price=3000;
	box[26].price=3500;
	box[27].price=500;
	box[28].price=6000;
	box[29].price=5000;
	box[30].price=0;
	box[31].price=5000;
	box[32].price=6000;
	box[33].price=9000;
	box[34].price=3000;
	box[35].price=3000;
}


}

void start()
{
clrscr();

	for(int j=0;j<55;++j)
	{
		gotoxy(25,j);
		textcolor(15);
		cprintf(".");
	}
	for(int j=54;j>0;--j)
	{
		gotoxy(135,j);
		textcolor(15);
		cprintf(".");
	}
	for(int j=0;j<160;++j)
	{
		gotoxy(j,14);
		textcolor(15);
		cprintf(".  ");
	}
	for(int j=0;j<160;++j)
	{
		gotoxy(j,40);
		textcolor(15);
		cprintf(".  ");
	}

	gotoxy(75,27);
	textcolor(15);
	cprintf("MONOPOLY");

	gotoxy(106,39);
	textcolor(15);
	cprintf("-by Avdhesh Kumar Prajapati");
	getch();

}

void start_menu()
{
int choice;

clrscr();

	for(int j=0;j<55;++j)
	{
		gotoxy(25,j);
		textcolor(15);
		cprintf(".");
	}
	for(int j=54;j>0;--j)
	{
		gotoxy(135,j);
		textcolor(15);
		cprintf(".");
	}
	for(int j=0;j<160;++j)
	{
		gotoxy(j,14);
		textcolor(15);
		cprintf(".  ");
	}
	for(int j=0;j<160;++j)
	{
		gotoxy(j,40);
		textcolor(15);
		cprintf(".  ");
	}

	gotoxy(75,16);
	textcolor(15);
	cprintf("MONOPOLY");

	gotoxy(75,21);
	textcolor(15);
	cprintf("1.Start New Game");
	gotoxy(75,23);
	textcolor(15);
	cprintf("2.Load");
	gotoxy(75,25);
	textcolor(15);
	cprintf("3.Save");
	gotoxy(75,27);
	textcolor(15);
	cprintf("4.Exit");

	gotoxy(68,29);
	textcolor(15);
	cprintf("Enter your choice..");
	cin>>choice;

	switch(choice)
	{
		case 1:clrscr();
				initialise_boxes();
				initialise_players();
				break;

		case 2:	initialise_boxes();
				initialise_players();
				load();
				break;

		case 3:save();
				break;

		case 4:	clrscr();
				exit(1);
				break;

	}

	getch();
}

int throw_dice()
{
	int i,randnum;
	unsigned int seedval;
	time_t t;
	seedval=(unsigned)time(&t);
	srand(seedval);

	return (rand()%6)+(rand()%6)+2;									//call of rand() twice, to make generation of numbers more random
}

void initialise_players()
{

	for(int i=0;i<3;++i)
	{
		plyr[i].bankrupted='n';
		plyr[i].jail_pt=0;
		plyr[i].balance=10000;
	}
		strcpy(plyr[0].name,"aaaaa");
		plyr[0].cursur='\1';
		plyr[0].color=1;
		
		strcpy(plyr[1].name,"bbbbb");
		plyr[1].cursur='\2';
		plyr[1].color=2;
		
		strcpy(plyr[2].name,"ccccc");
		plyr[2].cursur='\3';
		plyr[2].color=3;
		
		
	for(int i=0;i<3;++i)			//general initialisation for players
	{
		plyr[i].no=0;
		plyr[i].loan=0;
		plyr[i].cards=0;
		plyr[i].no_of_upgraded_sites=0;
		plyr[i].balance=10000;
	}



	
	

	bank.balance=1000000;
	bank.loan=0;
	bank.color=15;



/*
	for(int i=0;i<3;++i)
	{
		plyr[i].bankrupted='n';
		plyr[i].jail_pt=0;
		cout<<"Details of player "<<i+1;
		cout<<"\nEnter your name";
		gets(plyr[i].name);
		cout<<"\nselect color";
		for(int j=9;j<15;++j)
		{
			cout<<"\n";
			textcolor(j);
			cprintf("%d.color",j-8);
		}
		cout<<"\nchoice...";
		cin>>plyr[i].color;
		plyr[0].color +=8;

		cout<<"\nEnter your marker or any symbol from keyboard\n";
		textcolor(plyr[i].color);
		cprintf("1.%c   2.%c   3.%c   4.%c   5.%c",'\1','\2','\4','\5','\6');
		int ch;
		cout<<"\nchoice...";
		cin>>ch;
		switch(ch)
		{
			case 1:plyr[i].cursur='\1';
					break;

			case 2:plyr[i].cursur='\2';
					break;

			case 3:plyr[i].cursur='\4';
					break;

			case 4:plyr[i].cursur='\5';
					break;

			case 5:plyr[i].cursur='\6';
					break;

			default :plyr[i].cursur='\6';
					break;
		}
	}
*/
}

void sec_card(player *plr)
{
	char ch;

			if(strcmp(box[plr->no].owner,"BANK")==0)
				{
					if(plr->balance>=box[plr->no].price)
					{
						cout<<"Do you want to buy \""<<box[plr->no].name<<"\" for Rs."<<box[plr->no].price<<" (y/n)...";
						cin>>ch;
						if(ch=='y'||ch=='Y')
						{
							plr->balance -=box[plr->no].price;
							bank.balance +=box[plr->no].price;
							strcpy(box[plr->no].owner,plr->name);
							box[plr->no].price /=10;
							cout<<"\nyou bought \""<<box[plr->no].name<<"\"";
							plr->cards++;
						}
					}
					else if(plr->balance>=box[plr->no].price-3000&&plr->loan==0)
					{
						char ch;
						cout<<"\nDo you really want to buy \""<<box[plr->no].name<<"\"...you will have to take loan..(y/n)...";
						cin>>ch;
						if(ch=='y'||ch=='Y')
						{
							plr->balance +=3000;
							plr->loan +=3000;
							bank.loan +=3000;
							bank.balance -=3000;
							cout<<"\nloan taken...";

							plr->balance -=box[plr->no].price;
							bank.balance +=box[plr->no].price;
							strcpy(box[plr->no].owner,plr->name);
							box[plr->no].price /=10;
							cout<<"\nyou bought \""<<box[plr->no].name<<"\"";
							plr->cards++;
						}
					}

					else
						{
						cout<<"\nnot enough balance...";
						}
				}

			else
			{
				cout<<"paying Rs."<<box[plr->no].price<<"to owner of \""<<box[plr->no].name;
				if(plr->balance>=box[plr->no].price||(plr->balance>=box[plr->no].price-3000&&plr->loan==0))
				{
					if(plr->balance<box[plr->no].price)
					loan(plr);
					for(int i=0;i<3;++i)
						if(strcmp(plyr[i].name,box[plr->no].owner)==0)
							plyr[i].balance+=box[plr->no].price;
					plr->balance -=box[plr->no].price;
					getch();
					cout<<"\npaid...";
				}
				else
				bankrupt(plr);
			}


getch();
}


void loan(player *plr)
{
	char ch='n';
	cout<<"\nare you sure want to take loan...";
	ch=getch();
	if(ch=='y'||ch=='Y')
	{
		plr->balance +=3000;
		plr->loan=3000;
		bank.loan +=3000;
		bank.balance-=3000;
		cout<<"loan granted...";
	}
getch();
}
void country(player *plr)
{
	char ch;

			if(strcmp(box[plr->no].owner,"BANK")==0)
				{
					if(plr->balance>=box[plr->no].price)
					{
						cout<<"\nDo you want to buy \""<<box[plr->no].name<<"\" for Rs."<<box[plr->no].price<<" (y/n)...";
						cin>>ch;
						if(ch=='y'||ch=='Y')
						{
							plr->balance -=box[plr->no].price;
							bank.balance +=box[plr->no].price;
							strcpy(box[plr->no].owner,plr->name);
							box[plr->no].price /=10;
							plr->cards++;
							cout<<"\nyou bought \""<<box[plr->no].name<<"\"";
							
						}
					}
					else if(plr->balance>=box[plr->no].price-3000&&plr->loan==0)
					{
						char ch;
						cout<<"\nDo you really want to buy \""<<box[plr->no].name<<"\"...you will have to take loan..(y/n)...";
						cin>>ch;
						if(ch=='y'||ch=='Y')
						{
							plr->balance +=3000;
							plr->loan +=3000;
							bank.loan +=3000;
							bank.balance -=3000;
							cout<<"\nloan taken...";

							plr->balance -=box[plr->no].price;
							bank.balance +=box[plr->no].price;
							strcpy(box[plr->no].owner,plr->name);
							box[plr->no].price /=10;
							plr->cards++;
							cout<<"\nyou bought \""<<box[plr->no].name<<"\"";
							
						}
					}

					else
						{
						cout<<"\nnot enough balance...";
						}
				}

			else if(strcmp(plr->name,box[plr->no].owner)==0)
			{	char ch;
				if(box[plr->no].upgraded!='n')
				{
					cout<<"\nDo you want to upgrade this site..(y/n)...";
					cin>>ch;
					if(ch=='y'||ch=='Y')
					upgrade(plr);
				}
			}
			else if(strcmp(plr->name,box[plr->no].owner)!=0)
			{
				cout<<"\npaying Rs."<<box[plr->no].price<<"to owner of \""<<box[plr->no].name;
				if(plr->balance>=box[plr->no].price||(plr->balance>=box[plr->no].price-3000&&plr->loan==0))
				{
					if(plr->balance<box[plr->no].price)
					loan(plr);
					for(int i=0;i<3;++i)
						if(strcmp(plyr[i].name,box[plr->no].owner)==0)
							plyr[i].balance+=box[plr->no].price;
					plr->balance -=box[plr->no].price;
					getch();
					cout<<"\npaid...";
				}
				else
				bankrupt(plr);
			}

getch();
}


void bankrupt(player *plr)
{
textcolor(plr->color);
cprintf("%c%s",'\n',plr->name);
cout<<"bankrupted...";
plr->balance=0;
plr->loan=0;
plr->cursur='\0';
plr->bankrupted='y';

	for(int i=1;i<36;++i)
	{
		if(strcmp(plr->name,box[i].owner)==0)
		strcpy(box[i].owner,"BANK");
	}

getch();
}



void box_display()
{
	int x=-1,y=-1;														//-1->no color
	for(int j=0;j<10;++j)									//print first |------------| line
	{
		cout<<"|";
		for(int i=0;i<15;++i)
		cout<<"-";
	}
	cout<<"|\n";

	for(int j=0;j<10;++j)									//print names and cursur of player 0
	{
		cout<<"| ";
		if(j==0)
		{

			if(plyr[0].no==j)
			{
				textcolor(plyr[0].color);
				cprintf("%c",plyr[0].cursur);
			}
			else
			cout<<" ";
			cout<<"   "<<box[0].name<<"\t";

		}
		else
		{

			if(plyr[0].no==36-j)
			{
				textcolor(plyr[0].color);
				cprintf("%c",plyr[0].cursur);
			}
			else
			cout<<" ";
			cout<<"   ";

			int color_name=-1;
			for(int i=0;i<3;++i)
			{
				if(strcmp(box[36-j].owner,plyr[i].name)==0)
				{
					textcolor(plyr[i].color);
					x=i;
					y=j;
					color_name=i;					//color has been buffered
				}
			}
			if(color_name!=-1)
			cprintf("%s",box[36-j].name);
			else
			cout<<box[36-j].name;
			cout<<"\t";

		}

	}
	cout<<"|\n";


	for(int j=0;j<10;++j)									//prints price and cursur of player 1
	{
		cout<<"| ";
		if(j==0)
		{

			if(plyr[1].no==j)
			{
				textcolor(plyr[1].color);
				cprintf("%c",plyr[1].cursur);
			}
			else
			cout<<" ";
			cout<<"   Rs."<<box[0].price<<"\t";

		}
		else
		{

			if(plyr[1].no==36-j)
			{
				textcolor(plyr[1].color);
				cprintf("%c",plyr[1].cursur);
			}
			else
			cout<<" ";
			cout<<"   ";
			int p_col=7;
			for(int i=0;i<3;++i)
			{
				if(strcmp(plyr[i].name,box[36-j].owner)==0)
				p_col=plyr[i].color;
			}
			textcolor(p_col);
			cprintf("Rs. %d",box[36-j].price);
			cout<<"\t";
		}

	}
	cout<<"|\n";




	for(int j=0;j<10;++j)									//prints owner and cursur of player 2
	{
		cout<<"| ";
		if(j==0)
		{

			if(plyr[2].no==j)
			{
				textcolor(plyr[2].color);
				cprintf("%c",plyr[2].cursur);
			}
			else
			cout<<" ";
			cout<<"   "<<box[0].owner<<"\t";

		}

		else
		{

			if(plyr[2].no==36-j)
			{
				textcolor(plyr[2].color);
				cprintf("%c",plyr[2].cursur);
			}
			else
			cout<<" ";
			cout<<"   ";
			int p_col=7;
			for(int i=0;i<3;++i)
			{
				if(strcmp(plyr[i].name,box[36-j].owner)==0)
				p_col=plyr[i].color;
			}
			textcolor(p_col);
			cprintf("%s",box[36-j].owner);
			cout<<"\t";
		}

	}
	cout<<"|\n";


	for(int j=0;j<10;++j)									//print first |------------| line
	{
		cout<<"|";
		for(int i=0;i<15;++i)
		cout<<"-";
	}
	cout<<"|\n|";


//*********************************************************************************************


	if(plyr[0].no==1)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		int color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[1].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[1].name);
		else
		cout<<box[1].name;
		cout<<"\t|";

		cout<<"\t\t\t       ";
		textcolor(UNO_COLOR);
		cprintf("UNO");
		cout<<"\t\t\t\t|\t\t\t      ";
		textcolor(CHANCE_COLOR);
		cprintf("CHANCE");
		cout<<"\t\t\t\t|";



	if(plyr[0].no==26)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[26].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[26].name);
		else
		cout<<box[26].name;
		cout<<"\t|\n|";

//************************************************************************************************

	if(plyr[1].no==1)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[1].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[1].price);
		else
		cout<<box[1].price;
		cout<<"\t|";

		cout<<"\t";
		textcolor(UNO_COLOR);
		cprintf("2. collect Rs. 500 from each player its your birthday.");
		cout<<"\t|\t";
		textcolor(CHANCE_COLOR);
		cprintf("2. repairing sites Rs. 100 per site.");
		cout<<"\t\t";
		cout<<"\t|";



	if(plyr[1].no==26)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[26].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[26].price);
		else
		cout<<"Rs. "<<box[26].price;
		cout<<"\t|\n|";

//************************************************************************************************

	if(plyr[2].no==1)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[1].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[1].owner);
		else
		cout<<box[1].owner;
		cout<<"\t|";

		cout<<"\t";
		textcolor(UNO_COLOR);
		cprintf("3. go to jail.");
		cout<<"\t\t\t\t\t\t|\t";
		textcolor(CHANCE_COLOR);
		cprintf("3. go to party house,collect Rs.200 from each player.");
		cout<<"\t|";



	if(plyr[2].no==26)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[26].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[26].owner);
		else
		cout<<box[26].owner;
		cout<<"\t|\n";
//*******************************************************************************************************************************

cout<<"|---------------|\t";
textcolor(UNO_COLOR);
cprintf("4. lottery Rs. 2500.");
cout<<"\t\t\t\t\t|\t";
textcolor(CHANCE_COLOR);
cprintf("4. income tax Rs. 1500.");
cout<<"\t\t\t\t\t|---------------|\n|";
/*******************************************************************************************************************************
*******************************************************************************************************************************/



	if(plyr[0].no==2)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[2].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[2].name);
		else
		cout<<box[2].name;
		cout<<"\t|";

		cout<<"\t";
		textcolor(UNO_COLOR);
		cprintf("5. accident due to wrong driving Rs. 1000.");
		cout<<"\t\t|\t";
		textcolor(CHANCE_COLOR);
		cprintf("5. lottery Rs.1200.");
		cout<<"\t\t\t\t\t|";



	if(plyr[0].no==25)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[25].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[25].name);
		else
		cout<<box[25].name;
		cout<<"\t|\n|";

//************************************************************************************************

	if(plyr[1].no==2)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[2].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[2].price);
		else
		cout<<"Rs. "<<box[2].price;
		cout<<"\t|";

		cout<<"\t";
		textcolor(UNO_COLOR);
		cprintf("6. Income tax refund Rs. 2000.");
		cout<<"\t\t\t\t|\t";
		textcolor(CHANCE_COLOR);
		cprintf("6. Wrong driving fine Rs. 1000.");
		cout<<"\t\t\t\t|";



	if(plyr[1].no==25)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[25].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[25].price);
		else
		cout<<"Rs. "<<box[25].price;
		cout<<"\t|\n|";

//************************************************************************************************

	if(plyr[2].no==2)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[2].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[2].owner);
		else
		cout<<box[2].owner;
		cout<<"\t|";

		cout<<"\t";
		textcolor(UNO_COLOR);
		cprintf("7. pay Rs. 1000 for health insurance.");
		cout<<"\t\t\t|\t";
		textcolor(CHANCE_COLOR);
		cprintf("7. aid from world bank Rs. 1500.");
		cout<<"\t\t\t|";



	if(plyr[2].no==25)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[25].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[25].owner);
		else
		cout<<box[25].owner;
		cout<<"\t|\n";
/*******************************************************************************************************************************
*******************************************************************************************************************************/



cout<<"|---------------|\t";
textcolor(UNO_COLOR);
cprintf("8. profit on shares Rs. 1500.");
cout<<"\t\t\t\t|\t";
textcolor(CHANCE_COLOR);
cprintf("8. go to jail.");
cout<<"\t\t\t\t\t\t|---------------|\n|";
/*******************************************************************************************************************************
*******************************************************************************************************************************/



	if(plyr[0].no==3)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[3].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[3].name);
		else
		cout<<box[3].name;
		cout<<"\t|";

		cout<<"\t";
		textcolor(UNO_COLOR);
		cprintf("9. loss on shares Rs. 2000.");
		cout<<"\t\t\t\t|\t";
		textcolor(CHANCE_COLOR);
		cprintf("9. jump to start and collect Rs. 1500.");
		cout<<"\t\t\t|";



	if(plyr[0].no==24)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[24].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[24].name);
		else
		cout<<box[24].name;
		cout<<"\t|\n|";

//************************************************************************************************

	if(plyr[1].no==3)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[3].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[3].price);
		else
		cout<<"Rs. "<<box[3].price;
		cout<<"\t|";

		cout<<"\t";
		textcolor(UNO_COLOR);
		cprintf("10. go to party house,collect Rs.200 from each player.");
		cout<<"\t|\t";
		textcolor(CHANCE_COLOR);
		cprintf("10. Loss due to fire in godown Rs. 2500.");
		cout<<"\t\t|";



	if(plyr[1].no==24)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[24].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[24].price);
		else
		cout<<"Rs. "<<box[24].price;
		cout<<"\t|\n|";

//************************************************************************************************

	if(plyr[2].no==3)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[3].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[3].owner);
		else
		cout<<box[3].owner;
		cout<<"\t|";

		cout<<"\t";
		textcolor(UNO_COLOR);
		cprintf("11. business loss Rs. 4000.");
		cout<<"\t\t\t\t|\t";
		textcolor(CHANCE_COLOR);
		cprintf("11. Business profit Rs. 3000.");
		cout<<"\t\t\t\t|";



	if(plyr[2].no==24)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[24].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[24].owner);
		else
		cout<<box[24].owner;
		cout<<"\t|\n";
/*******************************************************************************************************************************
*******************************************************************************************************************************/

	cout<<"|";
	for(int j=0;j<15;++j)									//print first |------------| line
	cout<<"-";
	cout<<"|\t";
		textcolor(UNO_COLOR);
		cprintf("12. business profit Rs. 5000.");
		cout<<"\t\t\t\t|\t";
		textcolor(CHANCE_COLOR);
		cprintf("12. Market crash Rs. 5000.");
		cout<<"\t\t\t\t|";

	for(int j=0;j<15;++j)									//print first |------------| line
	cout<<"-";
	cout<<"|\n";

/*******************************************************************************************************************************
*******************************************************************************************************************************/

	cout<<"|";

	if(plyr[0].no==4)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[4].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[4].name);
		else
		cout<<box[4].name;
		cout<<"\t|";

	for(int j=0;j<127;++j)									//print first |------------| line
	cout<<"-";
	cout<<"|";




	if(plyr[0].no==23)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[23].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[23].name);
		else
		cout<<box[23].name;
		cout<<"\t|\n|";
//********************************************************************************************************


	if(plyr[1].no==4)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[4].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[4].price);
		else
		cout<<"Rs. "<<box[4].price;
		cout<<"\t|\t";

		textcolor(plyr[0].color);
		cprintf("   %c   %s",plyr[0].cursur,plyr[0].name);
		cout<<"\t\t|\t";

		textcolor(plyr[1].color);
		cprintf("   %c   %s",plyr[1].cursur,plyr[1].name);
		cout<<"\t\t|\t";

		textcolor(plyr[2].color);
		cprintf("   %c   %s",plyr[2].cursur,plyr[2].name);
		cout<<"\t\t|\t";

		textcolor(15);
		cprintf("       BANK");
		cout<<"\t\t|";


		if(plyr[1].no==23)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[23].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[23].price);
		else
		cout<<"Rs. "<<box[23].price;
		cout<<"\t|\n|";
//*****************************************************************************************************



	if(plyr[2].no==4)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[4].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[4].owner);
		else
		cout<<box[4].owner;
		cout<<"\t|\t";

		textcolor(plyr[0].color);
		cprintf("Balance  :%d",plyr[0].balance);
		cout<<"\t\t|\t";

		textcolor(plyr[1].color);
		cprintf("Balance  :%d",plyr[1].balance);
		cout<<"\t\t|\t";

		textcolor(plyr[2].color);
		cprintf("Balance  :%d",plyr[2].balance);
		cout<<"\t\t|\t";

		textcolor(15);
		cprintf("Balance  :%d",bank.balance);
		cout<<"\t|";

	if(plyr[2].no==23)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[23].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[23].owner);
		else
		cout<<box[23].owner;
		cout<<"\t|\n|";

	for(int j=0;j<15;++j)									//print first |------------| line
	cout<<"-";
	cout<<"|\t";

		textcolor(plyr[0].color);
		cprintf("No.of Cards:%d",plyr[0].cards);
		cout<<"\t\t|\t";

		textcolor(plyr[1].color);
		cprintf("No.of Cards:%d",plyr[1].cards);
		cout<<"\t\t|\t";

		textcolor(plyr[2].color);
		cprintf("No.of Cards:%d",plyr[2].cards);
		cout<<"\t\t|\t";

		textcolor(15);
		cprintf("No.of Cards:%d",bank.cards);
		cout<<"\t\t|";

	for(int j=0;j<15;++j)									//print first |------------| line
	cout<<"-";
	cout<<"|\n";

/****************************************************************************************************
****************************************************************************************************/
	cout<<"|";

	if(plyr[0].no==5)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[5].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[5].name);
		else
		cout<<box[5].name;
		cout<<"\t|\t";


		textcolor(plyr[0].color);
		cprintf("Loan taken:%d",plyr[0].loan);
		cout<<"\t\t|\t";

		textcolor(plyr[1].color);
		cprintf("Loan taken:%d",plyr[1].loan);
		cout<<"\t\t|\t";

		textcolor(plyr[2].color);
		cprintf("Loan taken:%d",plyr[2].loan);
		cout<<"\t\t|\t";

		textcolor(bank.color);
		cprintf("Loan given:% d",bank.loan);
		if(bank.loan==0)
		cout<<"\t\t|";
		else
		cout<<"\t|";


	if(plyr[0].no==22)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[22].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[22].name);
		else
		cout<<box[22].name;
		cout<<"\t|\n|";
//********************************************************************************************************



	if(plyr[1].no==5)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[5].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[5].price);
		else
		cout<<"Rs. "<<box[5].price;
		cout<<"\t|\t";

		textcolor(plyr[0].color);
		cprintf("upgraded sites:%d",plyr[0].no_of_upgraded_sites);
		cout<<"\t|\t";

		textcolor(plyr[1].color);
		cprintf("upgraded sites:%d",plyr[1].no_of_upgraded_sites);
		cout<<"\t|\t";

		textcolor(plyr[2].color);
		cprintf("upgraded sites:%d",plyr[2].no_of_upgraded_sites);
		cout<<"\t|\t";

		cout<<"\t\t\t|";


		if(plyr[1].no==22)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[22].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[22].price);
		else
		cout<<"Rs. "<<box[22].price;
		cout<<"\t|\n|";

//**************************************************************************************************************************



	if(plyr[2].no==5)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[5].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[5].owner);
		else
		cout<<box[5].owner;
		cout<<"\t|\t\t\t\t|\t\t\t\t|\t\t\t\t\t|\t\t\t\t|";


		if(plyr[2].no==22)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[22].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[22].owner);
		else
		cout<<box[22].owner;
		cout<<"\t|\n";

//****************************************************************************************************************


	for(int j=0;j<10;++j)									//print first |------------| line
	{
		cout<<"|";
		for(int i=0;i<15;++i)
		cout<<"-";
	}
	cout<<"|\n";


/****************************************************************************************************************
****************************************************************************************************************/
	cout<<"|";

	if(plyr[0].no==6)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[6].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[6].name);
		else
		cout<<box[6].name;
		cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";


	if(plyr[0].no==21)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[21].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[21].name);
		else
		cout<<box[21].name;
		cout<<"\t|\n|";
//********************************************************************************************************



	if(plyr[1].no==6)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[6].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[6].price);
		else
		cout<<"Rs. "<<box[6].price;

		cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";


		if(plyr[1].no==21)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[21].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[21].price);
		else
		cout<<"Rs. "<<box[21].price;
		cout<<"\t|\n|";

//**************************************************************************************************************************


	if(plyr[2].no==6)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[6].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[6].owner);
		else
		cout<<box[6].owner;
		cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";


		if(plyr[2].no==21)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[21].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[21].owner);
		else
		cout<<box[21].owner;
		cout<<"\t|\n";

//*******************************************************************************************************


		cout<<"|";
		for(int i=0;i<15;++i)
		cout<<"-";
		cout<<"|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";
		for(int i=0;i<15;++i)
		cout<<"-";
		cout<<"|\n";

/******************************************************************************************************
*******************************************************************************************************/

	cout<<"|";

	if(plyr[0].no==7)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[7].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[7].name);
		else
		cout<<box[7].name;
		cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";


	if(plyr[0].no==20)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[20].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[20].name);
		else
		cout<<box[20].name;
		cout<<"\t|\n|";
//********************************************************************************************************



	if(plyr[1].no==7)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[7].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[7].price);
		else
		cout<<"Rs. "<<box[7].price;

		cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";


		if(plyr[1].no==20)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[20].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[20].price);
		else
		cout<<"Rs. "<<box[20].price;
		cout<<"\t|\n|";

//**************************************************************************************************************************


	if(plyr[2].no==7)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[7].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[7].owner);
		else
		cout<<box[7].owner;
		cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";


		if(plyr[2].no==20)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[20].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[20].owner);
		else
		cout<<box[20].owner;
		cout<<"\t|\n";

//*******************************************************************************************************


		cout<<"|";
		for(int i=0;i<15;++i)
		cout<<"-";
		cout<<"|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";
		for(int i=0;i<15;++i)
		cout<<"-";
		cout<<"|\n";

/******************************************************************************************************
*******************************************************************************************************/

	cout<<"|";

	if(plyr[0].no==8)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[8].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[8].name);
		else
		cout<<box[8].name;
		cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";


	if(plyr[0].no==19)
		{
			textcolor(plyr[0].color);
			cprintf("%c",plyr[0].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[19].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[19].name);
		else
		cout<<box[19].name;
		cout<<"\t|\n|";
//********************************************************************************************************



	if(plyr[1].no==8)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[8].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[8].price);
		else
		cout<<"Rs. "<<box[8].price;

		cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";


		if(plyr[1].no==19)
		{
			textcolor(plyr[1].color);
			cprintf("%c",plyr[1].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[19].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("Rs. %d",box[19].price);
		else
		cout<<"Rs. "<<box[19].price;
		cout<<"\t|\n|";

//**************************************************************************************************************************


	if(plyr[2].no==8)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[8].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[8].owner);
		else
		cout<<box[8].owner;
		cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";


		if(plyr[2].no==19)
		{
			textcolor(plyr[2].color);
			cprintf("%c",plyr[2].cursur);
		}
		else
		cout<<" ";
		cout<<"    ";

		x=-1;
		color_name=-1;
		for(int i=0;i<3;++i)
		{
			if(strcmp(box[19].owner,plyr[i].name)==0)
			{
				textcolor(plyr[i].color);
				x=i;
				color_name=i;					//color has been buffered
			}
		}
		if(color_name!=-1)
		cprintf("%s",box[19].owner);
		else
		cout<<box[19].owner;
		cout<<"\t|\n";

//*******************************************************************************************************


	for(int j=0;j<10;++j)									//print first |------------| line
	{
		cout<<"|";
		for(int i=0;i<15;++i)
		cout<<"-";
	}
	cout<<"|\n";

/******************************************************************************************************
*******************************************************************************************************/


	for(int j=9;j<=18;++j)									//print names and cursur of player 0
	{
		cout<<"| ";

			if(plyr[0].no==j)
			{
				textcolor(plyr[0].color);
				cprintf("%c",plyr[0].cursur);
			}
			else
			cout<<" ";
			cout<<"   ";

			int color_name=-1;
			for(int i=0;i<3;++i)
			{
				if(strcmp(box[j].owner,plyr[i].name)==0)
				{
					textcolor(plyr[i].color);
					x=i;
					y=j;
					color_name=i;					//color has been buffered
				}
			}
			if(color_name!=-1)
			cprintf("%s",box[j].name);
			else
			cout<<box[j].name;
			cout<<"\t";



	}
	cout<<"|\n";


	for(int j=9;j<=18;++j)									//prints price and cursur of player 1
	{
		cout<<"| ";


			if(plyr[1].no==j)
			{
				textcolor(plyr[1].color);
				cprintf("%c",plyr[1].cursur);
			}
			else
			cout<<" ";
			cout<<"   ";
			int p_col=7;							//7 is normal white
			for(int i=0;i<3;++i)
			if(strcmp(plyr[i].name,box[j].owner)==0)
			p_col=plyr[i].color;

			textcolor(p_col);
			cprintf("Rs. %d",box[j].price);
			cout<<"\t";
			
		


	}
	cout<<"|\n";




	for(int j=9;j<=18;++j)									//prints owner and cursur of player 2
	{
		cout<<"| ";

			if(plyr[2].no==j)
			{
				textcolor(plyr[2].color);
				cprintf("%c",plyr[2].cursur);
			}
			else
			cout<<" ";
			cout<<"   ";
			int p_col=7;							//7 is normal white
			for(int i=0;i<3;++i)
			if(strcmp(plyr[i].name,box[j].owner)==0)
			p_col=plyr[i].color;
			
			textcolor(p_col);
			cprintf("%s",box[j].owner);
			cout<<"\t";



	}
	cout<<"|\n";


	for(int j=0;j<10;++j)									//print first |------------| line
	{
		cout<<"|";
		for(int i=0;i<15;++i)
		cout<<"-";
	}
	cout<<"|";

}
