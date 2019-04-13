#include<iostream>
#include<stdlib.h>
#include<time.h>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
using namespace std;
char board[3][3],winner='0';
int r1,r2,c1,c2;
void inigame()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			board[i][j]='_';
		}
	}
}

void update()
{
	for(int i=0;i<3;i++)
	{
		printf("\t\t\t\t\t\t\t\t");
		for(int j=0;j<3;j++)
		{
			printf("%c\t",board[i][j]);
		}
		printf("\n");	
	}
}

int toss()
{
	int i;
	srand(time(NULL));
	i=rand()%2+1;
	//printf("%d",i);
	return i;
}

void p1()
{
	a:
	printf("  r: ");
	scanf("%d",&r1);
	printf("     \t\tc: ");
	scanf("%d",&c1);
	if(board[r1-1][c1-1]=='_')
	{
		board[r1-1][c1-1]='X';
	}
	else 
	{
		printf("\n\tTHIS POSITION IS NOT EMPTY, PLEASE ENTER AGAIN : ");
		goto a;
	}
}

void p2()
{
	b:
	printf("  r: ");
	scanf("%d",&r2);
	printf("     \t\tc: ");
	scanf("%d",&c2);
	if(board[r2-1][c2-1]=='_')
	{
		board[r2-1][c2-1]='O';
	}
	else 
	{
		printf("\n\tTHIS POSITION IS NOT EMPTY, PLEASE ENTER AGAIN : ");
		goto b;
	}
}

void checkWinner()
{
	for (int i=0; i<=2; i++)
	{
		if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='_')

		{

			winner=board[i][0];

		}

	}
	for(int i=0; i<=2; i++)
	{
		if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='_')
		{
			winner=board[0][i];

		}

	}

	if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='_')
	{

		winner=board[0][0];

	}

	if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!='_')
	{

		winner=board[0][2];

	}



	if(board[0][0]==board[0][1] && board[0][1]==board[0][2]&& board[0][2]==board[0][1]&& board[1][0]==board [1][1]&& board[1][1]==board[1][2]&&board[1][2]==board[2][0]&&board[2][0]==board [2][1]&& board[2][1]==board [2][2] && board [0][0]!='_')
	{

		winner='0';

	}
}

int check(char board[3][3])
{
	for (int i=0; i<=2; i++)
	{
		if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='_')

		{

			return 1;

		}

	}

	for(int i=0; i<=2; i++)
	{

		if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='_')
		{
			return 1;
		}

	}

	if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='_')
	{

		return 1;

	}

	if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!='_')
	{

		return 1;
	}

	if(board[0][0]==board[0][1] && board[0][1]==board[0][2]&& board[0][2]==board[0][1]&& board[1][0]==board [1][1]&& board[1][1]==board[1][2]&&board[1][2]==board[2][0]&&board[2][0]==board [2][1]&& board[2][1]==board [2][2] && board [0][0]!='_')
	{

		return 0;
	}
	else
	{
		return 0;
	}
}
void bestmov()
{
	char ex[3][3];
	int win=0,r,c;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			ex[i][j]=board[i][j];
		}
	}


	for(r=0;r<3;r++)
	{
		for(c=0;c<3;c++)
		{		
			if(ex[r][c]=='_')
			{
				// Check if AI wins with next move
				ex[r][c]='O';
				win=check(ex);
				if (win) {
					goto SETBOARD;
				}
				else
				{
					ex[r][c]='_'; //reset to original value
				}
			}
		}
	}
	

	for(r=0;r<3;r++)
	{
		for(c=0;c<3;c++)
		{		
			if(ex[r][c]=='_')
			{
				// Check if opponent wins with next move
				ex[r][c]='X';
				win=check(ex);
				if (win) {
					goto SETBOARD;
				}
				else
				{
					ex[r][c]='_'; //reset to original value
				}
			}
		}
	}

	
	if(win==0)
	{	int once=1;
		srand(time(NULL));
		int big=rand()%5+1;
		switch(big)
		{
			again:
			case 1:
			{
				if(ex[0][0]=='_')
		 		{
					board[0][0]='O';
					break;
				}
			}
			case 2:
			{
				if (ex[0][2]=='_')
				{
					board[0][2]='O';
					break;
				}
				
			}
			case 3:
			{
				if (ex[2][0]=='_')
				{
					board[2][0]='O';
					break;
				}
				
				
			}
			case 4:
			{
				if (ex[2][2]=='-')
				{
					board[2][2]='O';
					break;
				}
				
			}
			case 5:
			{
				if (ex[1][1]=='_')
				{
					board[1][1]='O';
					break;
				}
				else
				{	
					if(once)
					{	once=0;
						goto again;
					}
					int once1=1;
					srand(time(NULL));
					int big1=rand()%4+1;
					switch(big1)
					{
						again1:
						case 1:
						{
							if(ex[0][1]=='_')
					 		{
								board[0][1]='O';
								break;
							}
						}
						case 2:
						{
							if (ex[1][2]=='_')
							{
								board[1][2]='O';
								break;
							}
							
						}
						case 3:
						{
							if (ex[2][1]=='_')
							{
								board[2][1]='O';
								break;
							}
							
							
						}
						case 4:
						{
							if (ex[1][0]=='_')
							{
								board[1][0]='O';
								break;
							}
							else
							{	
								if(once1)
								{	once1=0;
									goto again1;
								}
								break;
							}
						}
					}
				}
			}
		}
	}
	SETBOARD:
	if (win=1)
	{
		board[r][c]='O';
	}
}




#define TRUE 1
#define FALSE 0

int main()
{	
	int trn,r1,r2,c1,c2,max=0,choice[3];
	//bool first_mov=TRUE;
	inigame();
	printf("**************************************************************************************************************************************************************\n\n");
	printf("\t\t\t\t\t\t\tWELCOME TO THE TIC TAC TOE GAME !!!\n\n");	
	printf("\t Select game mode:\n\t   1.P Vs P\n\t   2.P Vs AI\n\t   3.Multiplayer[LAN]\n");
	c:
	scanf("%d",&choice[0]);
	printf("\n\n");
	switch(choice[0])
	{ 
		case 1:
		{ 
			update();
			trn=toss();
			while(winner=='0' && max!=9)
			{
				if(trn%2==1)
				{
					printf("\nPlayer 1[X] turn : ");
					p1();
					update();
					trn++;
					max++;
					checkWinner();
					

				}
				else if(trn%2==0)
				{
					printf("\nPlayer 2[O] turn : ");
					p2();
					update();
					trn++;
					max++;
					checkWinner();
					

				}
				
			}
			if(winner=='X')
			{
				printf("\n\n\t\t\t\t\t\t\t PLAYER 1[X] WINS !!!\n\n");
			}
			else if (winner=='O')
			{
				printf("\n\n\t\t\t\t\t\t\t PLAYER 2[O] WINS !!!\n\n");
			}
			else
			{
				printf("\n\n\t\t\t\t\t\t\t ITS A TIE !!!\n\n");
			}
			break;
		}
		case 2:
		{	

			update();
			cout<<"\n\n";
			trn=toss();
			int first_mov;
			if (trn==2) // AI 1st move
			{
				first_mov=0;
			}
			else
			{
				first_mov=1; // Opp 1st move
			
			}
			while(winner=='0' && max!=9)
			{
				if(trn%2==1) // Player turn
				{
					printf("\nPlayer 1[X] turn : ");
					p1();
					update();
					trn++;
					max++;
					first_mov++;
					checkWinner();
					
				} 
				else if(trn%2==0)  // AI turn
				{
					
					if (first_mov<=3)
					{
						srand(time(NULL));
						int big=rand()%5+1;
						
						switch(big)
						{
							again:
							case 1:
							{
								if(board[0][0]=='_')
						 		{
									board[0][0]='O';
									break;
								}
							}
							case 2:
							{
								if (board[0][2]=='_')
								{
									board[0][2]='O';
									break;
								}
								else
								{
									continue;
								}
							}
							case 3:
							{
								if (board[2][0]=='_')
								{
									board[2][0]='O';
									break;
								}
								else
								{
									continue;
								}
								
							}
							case 4:
							{
								if (board[2][2]=='-')
								{
									board[2][2]='O';
									break;
								}
								else
								{
									continue;
								}
							}
							case 5:
							{
								if (board[1][1]=='_')
								{
									board[1][1]='O';
									break;
								}
								else
								{
									goto again;
								}
							}
						}
						first_mov++;

						printf("\nAI[O] turn : \n");
						update();
						trn++;
						max++;

					}
					else
					{
						bestmov();
						printf("\nAI[O] turn : \n");
						update();
						trn++;
						max++;
						checkWinner();
					}

				}
				
			}
			if(winner=='X')
			{
				printf("\n\n\t\t\t\t\t\t\t PLAYER 1[X] WINS !!!\n\n");
			}
			else if (winner=='O')
			{
				printf("\n\n\t\t\t\t\t\t\t AI[O] WINS !!!\n\n");
			}
			else
			{
				printf("\n\n\t\t\t\t\t\t\t ITS A TIE !!!\n\n");
			}
			break;
		}
		case 3:
		{
			int pin,r3,c3,r4,c4;
			char ipad[20];
			printf("Select following options:\n");
			printf("\t 1.Create a Server\n\t 2.Join a server\n\n");
			cin>>choice[1];
			if(choice[1]==1)
			{
				cout<<"Enter a 5 digit pin : ";
				cin>>pin;
				 
			    int port = pin;
			    //buffer to send and receive messages with
			    
			     
			    //setup a socket and connection tools
			    sockaddr_in servAddr;
			    bzero((char*)&servAddr, sizeof(servAddr));
			    servAddr.sin_family = AF_INET;
			    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
			    servAddr.sin_port = htons(port);
			 
			    //open stream oriented socket with internet address
			    //also keep track of the socket descriptor
			    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
			    if(serverSd < 0)
			    {
			        cerr << "Error establishing the server socket" << endl;
			        exit(0);
			    }
			    //bind the socket to its local address
			    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr,sizeof(servAddr));
			    if(bindStatus < 0)
			    {
			        cerr << "Error binding socket to local address" << endl;
			        exit(0);
			    }
			    cout << "Waiting for a client to connect..." << endl;
			    //listen for up to 5 requests at a time
			    listen(serverSd, 5);
			    //receive a request from client using accept
			    //we need a new address to connect with the client
			    sockaddr_in newSockAddr;
			    socklen_t newSockAddrSize = sizeof(newSockAddr);
			    //accept, create a new socket descriptor to 
			    //handle the new connection with client
			    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
			    if(newSd < 0)
			    {
			        cerr << "Error accepting request from client!" << endl;
			        exit(1);
			    }
			    cout << "Connected with client!" << endl;
			    int bytesRead, bytesWritten = 0;
			    while(winner=='0' && max!=9)
			    {
			        //receive a message from the client (listen)
			        cout << "Awaiting client response..." << endl;
			        memset(&r4, 0, sizeof(r4));
			        memset(&c4, 0, sizeof(c4));
			        //clear the buffer
			        bytesRead += recv(newSd,(char*)&board,sizeof(board),0);
			        bytesRead += recv(newSd,(char*)&board,sizeof(board),0);
			        cout<<"\n";
			        update();
			        max++;
					checkWinner();
			        while(1)
					{	
						printf("Player X:\n");
						printf("  r: ");
						scanf("%d",&r3);
						printf("    \t\tc: ");
						scanf("%d",&c3);
						if(board[r3-1][c3-1]=='_')
						{
							board[r3-1][c3-1]='X';
							memset(&r3, 0, sizeof(r3));
			        			memset(&c3, 0, sizeof(c3));
			        		 	bytesRead += send(newSd,(char*)&board,sizeof(board),0);
			        			bytesRead += send(newSd,(char*)&board,sizeof(board),0);
			        		break;
						}
						else 
						{
							printf("\n\tTHIS POSITION IS NOT EMPTY, PLEASE ENTER AGAIN : ");
						}
					}
					update();
					checkWinner();
			    }
			    if(winner=='X')
				{
					printf("\n\n\t\t\t\t\t\t\t PLAYER 1[X] WINS !!!\n\n");
				}
				else if (winner=='O')
				{
					printf("\n\n\t\t\t\t\t\t\t PLAYER 2[O] WINS !!!\n\n");
				}
				else
				{
					printf("\n\n\t\t\t\t\t\t\t ITS A TIE !!!\n\n");
				}
			    //we need to close the socket descriptors after we're all done
			    //gettimeofday(&end1, NULL);
			    close(newSd);
			    close(serverSd);
			    /*cout << "********Session********" << endl;
			    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
			   // cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) 
			    //    << " secs" << endl;
			    cout << "Connection closed..." << endl;
			    return 0;*/   
			}
			else if (choice[1]==2)
			{
				 //we need 2 things: ip address and port number, in that order
			     //grab the IP address and port number
			    cout<<"\nEnter the ipaddress of host:  ";
			    cin>>ipad;
			    cout<<"\nEnter the password :  ";
			    cin>>pin; 
			    char *serverIp = ipad;  
			    //create a message buffer 
			    //char msg[1500]; 
			    //setup a socket and connection tools 
			    struct hostent* host = gethostbyname(serverIp); 
			    sockaddr_in sendSockAddr;   
			    bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
			    sendSockAddr.sin_family = AF_INET; 
			    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
			    sendSockAddr.sin_port = htons(pin);
			    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
			    //try to connect...
			    int status = connect(clientSd,(sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
			    if(status < 0)
			    {
			        cout<<"Error connecting to socket!"<<endl; 
			        exit(0);
			    }
			    cout << "Connected to the server!" << endl;
			    int bytesRead, bytesWritten = 0;
			    //struct timeval start1, end1;
			    //gettimeofday(&start1, NULL);
			    while(winner=='0' && max!=9)
			    {
			        //cout << ">";
			        //string data;
			        //getline(cin, data);
			        memset(&r3, 0, sizeof(r3));
			        memset(&c3, 0, sizeof(c3));//clear the buffer
			         while(1)
					{	
						update();
						printf("Player O:\n");
						printf("  r: ");
						scanf("%d",&r3);
						printf("    \t\tc: ");
						scanf("%d",&c3);
						if(board[r3-1][c3-1]=='_')
						{
							board[r3-1][c3-1]='O';
							memset(&r3, 0, sizeof(r3));
			        		memset(&c3, 0, sizeof(c3));
			        		bytesRead += send(clientSd, (int*)&r3, sizeof(r3), 0);
			        		bytesRead += send(clientSd, (int*)&c3, sizeof(c3), 0);
			        		break;
						}
						else 
						{
							printf("\n\tTHIS POSITION IS NOT EMPTY, PLEASE ENTER AGAIN : ");
						}
					}
					update();
					checkWinner();
					memset(&r4, 0, sizeof(r4));
			        memset(&c4, 0, sizeof(c4));
			        bytesRead += recv(clientSd, (int*)&r4, sizeof(r4), 0);
			        bytesRead += recv(clientSd, (int*)&c4, sizeof(c4), 0);
			        board[r4-1][c4-1]='X';
			        update();
					checkWinner();
			    }
			    if(winner=='X')
				{
					printf("\n\n\t\t\t\t\t\t\t PLAYER 1[X] WINS !!!\n\n");
				}
				else if (winner=='O')
				{
					printf("\n\n\t\t\t\t\t\t\t PLAYER 2[O] WINS !!!\n\n");
				}
				else
				{
					printf("\n\n\t\t\t\t\t\t\t ITS A TIE !!!\n\n");
				}
			    //gettimeofday(&end1, NULL);
			    close(clientSd);
			    /*cout << "********Session********" << endl;
			    cout << "Bytes written: " << bytesWritten << 
			    " Bytes read: " << bytesRead << endl;
			    cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec) 
			      << " secs" << endl;
			    cout << "Connection closed" << endl;
			    return 0;*/    
			}				
						
			break;
		}
		default:
		{
			printf("Wrong choice please try again\n");
			goto c;
		}
	
	}
}
