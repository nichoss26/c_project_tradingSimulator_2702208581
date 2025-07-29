#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <math.h>

#define username_length 20

#define HASH_TABLE_SIZE 26
#define MAX_LENGTH 100

#define RESET		"\x1b[0m"
#define RED			"\x1b[31m"
#define GREEN		"\x1b[32m"
#define YELLOW		"\x1b[33m"
#define BLUE		"\x1b[34m"
#define PURPLE		"\x1b[35m"
#define ORANGE		"\e[38;5;208m"


int logout = 0;
int pilihan;
int val, pos, tp, sl;
int reward = 0;
bool active  = false;
long long int userCurrency = 0;



int candleBody = 219;
int shadow = 179;
int open_price = 100;

int startIndex = 0;

char email_login[255] = "";
char username_login[255] ;


 struct user{
	char username[40];
	char email[45];
	char password[45];
	long long int currency;
	struct user *next;
};struct user* hashTable[27];

void clr(){
	system("cls");
}

typedef struct Candle{
	int open, close, highest, lowest;
	struct Candle *prev, *next;
} Candle;

Candle* head = NULL;
Candle* tail = NULL;

Candle* createCandle(int open, int close, int highest, int lowest){
	Candle* newCandle = (Candle*)malloc(sizeof(Candle)); 
	if(newCandle != NULL) { 
		*newCandle = (Candle){open, close, highest, lowest, NULL, NULL}; 
	}
	return newCandle;
}

void pushTail(int open, int close, int highest, int lowest){
	Candle* newCandle = createCandle(open, close, highest, lowest);
	if(newCandle != NULL) { 
		if(!head){
			head = newCandle;
			tail = newCandle; 
			return;
		}
	
		tail->next = newCandle;
		newCandle->prev = tail;
		tail = newCandle; 
	}
}
//void setFullscreen() {
//    keybd_event (VK_MENU, 0x38, 0, 0);
//	keybd_event (VK_RETURN, 0x1c, 0, 0);
//	Sleep (100);
//	keybd_event (VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); 
//	keybd_event (VK_MENU, 0x38, KEYEVENTF_KEYUP,0);
//}

BOOL isFullscreen = FALSE; // sengaja di globalin

void setFullscreen() {
    isFullscreen = !isFullscreen;

    if (isFullscreen) {

        keybd_event(VK_MENU, 0x38, 0, 0); 
        keybd_event(VK_RETURN, 0x1c, 0, 0); 
        Sleep(100);
        keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); 
        keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
    } else {
        keybd_event(VK_ESCAPE, 0x1b, 0, 0); 
        keybd_event(VK_ESCAPE, 0x1b, KEYEVENTF_KEYUP, 0); 
    }
}



struct history{
	int value;
	int position;
	int takeProfit;
	int stopLoss;
	int reward;
	struct history *next;
}*head1, *tail1;

void pushMid(int value, int position, int takeProfit, int stopLoss, int reward) {
    struct history *node = (struct history *)malloc(sizeof(struct history));
    node->position = position;
    node->reward = reward;
    node->stopLoss = stopLoss;
    node->takeProfit = takeProfit;
    node->value = value;
    node->next = NULL;

    if (head1 == NULL) {
        head1 = tail1 = node;
    } else if (head1->reward <= node->reward) {
        node->next = head1;
        head1 = node;
    } else {
        struct history *prev = head1;
        struct history *curr = head1->next;

        while (curr != NULL && curr->reward > node->reward) {
            prev = curr;
            curr = curr->next;
        }

        prev->next = node;
        node->next = curr;

        if (curr == NULL) {
            tail1 = node;
        }
    }
}


void displayHistory() {
	system("cls");
    if (head1 == NULL) {
        printf("Currently no history\n");
    } else {
        struct history *now = head1;
        int count = 1;
		printf("Username : %s\n",username_login);
		puts("------------------------------------------------------------------------------------------------------\n");
        while (now != NULL) {
            printf("No: %d\n", count);
            printf("Value              : %d\n", now->value);
            printf("Position           : %d\n", now->position);
            printf("Take Profit        : %d\n", now->takeProfit);
            printf("Stop Loss          : %d\n", now->stopLoss);
            if((now->reward) >= 0){
            	printf("Reward             : ");
            	printf(GREEN);
            	printf("%d\n\n",now->reward);
            	printf(RESET);
            	
			}else{
				printf("Reward             : ");
            	printf(RED);
            	printf("%d\n\n",now->reward);
            	printf(RESET);
			}
            

            now = now->next;
            count++;
        }
    }
}








bool percent(int x){
	if(rand()%100 > x) return true;
	return false;
}

void generateCandleSticks(){
	
//	int open = tail->close;
//	int highest, lowest;
//	
//	int close = (rand()%3)*10;
//	if(percent(50)){
//		close *=-1;
//	}
//	close = open*close;
//	if (close <0) close = 0;
//	
//	if(open> close){
//		highest = open + (rand() % 3)*10;
//		lowest = close - (rand() % 3)*10;
//	}else{
//		lowest = open - (rand() % 3)*10;
//		highest = close + (rand() % 3)*10;
//	}
//	
//	if(highest > 330 ) highest = 330;
//	if(lowest < 0) lowest = 0;
//	open_price = tail->close;
	for (int i = 0; i < 1; ++i) {
		int close_price,highest_price,lowest_price;
		  
		if ((double)rand() / RAND_MAX < 0.1) {
		        close_price = open_price;
		} 
		// 90% 
		else {

		    int diff = open_price * 0.5; // 50% 

		    int direction = (rand() % 2 == 0) ? -1 : 1; // -1  lower, 1 higher

		    close_price = open_price + (direction * (rand() % (diff / 10) + 1) * 10);    
		}
		

		if (close_price > open_price) {
        // 30% 
        if ((double)rand() / RAND_MAX < 0.3) {
            highest_price = close_price;
        }
        // 70% 
        else {
            int random_value = (rand() % 5 + 1) * 10; 
            highest_price = close_price + random_value;
        }
    } 

    else {
        // 30%
        if ((double)rand() / RAND_MAX < 0.3) {
            highest_price = open_price;
        }
        // 70% 
        else {
            int random_value = (rand() % 5 + 1) * 10; 
            highest_price = open_price + random_value;
        }
    }
    

     if (close_price > open_price) {
        // 30% 
        if ((double)rand() / RAND_MAX < 0.3) {
            lowest_price = open_price;
        }
        // 70% 
        else {
            int random_value = (rand() % 5 + 1) * 10; 
            lowest_price = open_price - random_value;
        }
    } 

    else {
        // 30% 
        if ((double)rand() / RAND_MAX < 0.3) {
            lowest_price = close_price;
        }
        // 70% 
        else {
            int random_value = (rand() % 5 + 1) * 10; 
            lowest_price = close_price - random_value;
        }
    }
    
    if(open_price >330) open_price = 330;
    if(close_price < 0) close_price = 0;
    if(highest_price > 330 ) highest_price = 330;
    if(lowest_price < 0 ) lowest_price = 0;
		
		pushTail(open_price, close_price, highest_price, lowest_price);
	    open_price = close_price;
	    
	}
}

void printList(){
	for(Candle* temp = head; temp; temp= temp->next)
		printf("Open: %d, Close: %d, Highest: %d, Lowest: %d\n", temp->open, temp->close, temp->highest,temp->lowest);
}

void graph(){
	clr();
	int xLen = 140;
	int yLen = 40;
	
	int yGraph = yLen - 6;
	int num = 330;
	
	//grafik
	for(int y =0 ; y<=yGraph; y++){
		
		int highest,lowest, close, open, highCandle, lowCandle;
		Candle* curr = head;
		int i = 0;
		while(i<startIndex){
			curr = curr->next;
			i++;
		}
		
		for(int x = 0; x <=xLen; x++){
			
			if(curr){
				highest = curr->highest;	
				lowest = curr->lowest;
				close = curr->close;
				open = curr->open;
			}else{
				highest = lowest = close = open = -1;
			}
			
			if(close > open){
				highCandle = close;
				lowCandle = open;
			}else{
				highCandle = open;
				lowCandle = close;
			}
			
			int tailHighCandle, tailLowCandle;
			
			if(tail && tail->close > tail->open){
				tailHighCandle = tail->close;
				tailLowCandle = tail->open;
			}else if(tail){
				tailHighCandle = tail->open;
				tailLowCandle = tail->close;
			}
			if(!active && pos <= tailHighCandle && pos>=tailLowCandle){
				active=true; 
			}
			
			if(active){
				int mut = fabs(close - pos);
				if(tp <= tailHighCandle && tp>=tailLowCandle){
					reward = val*mut/100;
					active = false;
					userCurrency += reward;
					userCurrency += val;
					pushMid(val,pos,tp,sl,(reward));
					sl=tp=pos=val = -10;
				}else if(sl <= tailHighCandle && sl>=tailLowCandle){
					reward = (val*mut/100)*-1;
					active = false;
					userCurrency += reward;
					userCurrency += val;
					pushMid(val,pos,tp,sl,(reward));
					sl=tp=pos=val = -10;
				}else if(tp <= tailHighCandle && tp>=tailLowCandle){
					reward = val*mut/100;
					active = false;
					userCurrency += reward;
					userCurrency += val;
					pushMid(val,pos,tp,sl,(reward));
					sl=tp=pos=val = -10;
				}else if (sl >= tailHighCandle && sl<=tailLowCandle){
					reward = (val*mut/100)*-1;
					active = false;
					userCurrency += reward;
					userCurrency += val;
					pushMid(val,pos,tp,sl,(reward));
					sl=tp=pos=val = -10;
				}
				
				    FILE *file = fopen("user.txt", "r");
				    FILE *tempFile = fopen("temp.txt", "w");
				    char username[101];
				    char email[101];
				    long long currency;
				    char password[101];  
				    int updated = 0;
				
				
				    while (fscanf(file, "%[^#]#%[^#]#%[^#]#%lld\n", username, email, password, &currency) == 4) {
				        if (strcmp(username, username_login) == 0) {
				            currency = userCurrency;
				            updated = 1;
				        }
				        fprintf(tempFile, "%s#%s#%s#%lld\n", username, email, password, currency);
				    }
				
				    fclose(file);
				    fclose(tempFile);
				
				    if (!updated) {
				        printf("Username not found.\n");
				        remove("temp.txt"); 
				    }
				
				    if (remove("user.txt") != 0) {
				        printf("Error removing original file.\n");
				    }
				    if (rename("temp.txt", "user.txt") != 0) {
				        printf("Error renaming temporary file.\n");
				    }
    
			}
			
			
			if((y == 0 && x==0)|| (y == 0 && x == xLen)|| (y == yGraph && x == 0 )|| (y == yGraph && x == xLen)){
				printf("+");
			}else if( y == 0 || y == yGraph){
				printf("~");
			}else if(x == 0 || x == xLen){
				printf("|");
			}else if(x >= xLen - 6){ //data kanan
				if(x == xLen -6 ){
					printf("|");
				}else if (x == xLen - 4){
					printf("%-3d", num);
					num-=10;
				}else if ( x == xLen -5 || x == xLen-3){
					printf(" ");
				}
			}
			else{//letak candle
			
				//HIGHEST & LOWEST
				if(num <= highest  && num >= lowest && x > 0 && tail->prev != NULL){ // Check tail->prev
					if(curr->prev && highest > curr->prev->highest){
						printf(GREEN);
					}else{
						printf(RED);
					}
					if(num <= highCandle && num >= lowCandle){
						printf("%c",candleBody);
					}else{
						printf("%c",shadow);
					}
					
					printf(RESET);
				}else{
					if(num == pos){
						printf(YELLOW);
					}else if(num == tp){
						printf(GREEN);
					}else if(num == sl ){
						printf(RED);
					}
					printf("-");	
					printf(RESET);
				}
			}
			if(curr && x>0)curr = curr->next;
		}
		printf("\n");
		
	}
	
		//data bawah
		printf("|");
	printf("\e[0;35m");
	printf(" Halo 24-2 angkatan paling gacor, ");
	printf("\e[0;33m");
	printf("%-10s                    ", username_login);
	 printf("\033[0m");
	 
	printf("|                                                        |                 |\n");
	 
	printf("| 1. New Day    3. Next    5. Short                              |                                                        |   $ %-10d  |\n",userCurrency);
	printf("| 2. Previous   4. Long    6. Log Out                            |                                                        |                 |\n");
//	printf("| Halo 24-2 angkatan paling gacor, %-10s                    |                                                        |                 |\n", username_login);
	printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
	printf("\n\n Reward %d - Value %d - Position %d - TP %d - SL %d\n",reward, val, pos,tp,sl);
	
	if(active){
		printf("\n Trade is Active!\n");
	}else{
		printf(" Trade is  not Active!\n");
	}
	
}


void displayGuide (){
	system("cls");
	printf(BLUE);
	printf("What Is Forex?\n");
	printf(RESET);
	printf("short for foreign exchange, is a global decentralized marketplace for trading currencies.\n"); 
	printf("In forex trading, participants buy one currency by selling another currency simultaneously, with the aim of profiting form fluctuat\n");
	printf("ions in exchange rates.\n");
 	printf("another currency simultaneously, with the aim of profiting from fluctuat It is one of the largest and most liquid financial markets in the world, operating 24 hours a day, five days a week.\n\n");
 	
 	printf(YELLOW);
 	printf("What Is Candle Stick?\n");
 	printf(RESET);
 	printf("\"Canlde Stick\" in charts are a type of financial chart used to represent price movements in trading markets, including forex.\n");
 	printf("hey visually display the open, high, low, and close prices for a specific period.\n");
 	printf("if the close price is higher than the open price, the candle color will be green\n");
 	printf("then if the close price is less than the open price, the candle color will be red.\n");
 	printf("shadow or tick is the highest and the lowest price of a candle.\n\n");
 	
 	printf(PURPLE);
 	printf("What Is Position?\n");
 	printf(RESET);
 	printf("\"Position\" in forex trading refers to where we want to enter the market at certain price point\n\n");
 	
 	printf(GREEN);
 	printf("What Is Long?\n");
 	printf(RESET);
 	printf("\"Long\" in forex trading refers to a trading position where a trader buys a currency pair\n");
	printf("with the expectation that its value will increase over time.\n\n");
	 
	printf(ORANGE);
 	printf("What Is Short?\n");
 	printf(RESET);
 	printf("\"Short\" in forex trading refers to a trading position where a trader sells a currency pair\n");
	printf("with the expectation that its value will decrease over time.\n\n");
	 
	printf(GREEN);
 	printf("What Is Take Profit?\n");
 	printf(RESET);
 	printf("\"Take Profit\" in forex trading refers to where we will leave the market at the specified price point our position\n");
	printf("will automatically closed after the market price hit our take profit price\n\n");
 	
 	printf(ORANGE);
 	printf("What Is Stop Lost?\n");
 	printf(RESET);
 	printf("\"Stop Lost\" in forex trading refers to where we will leave the market at the specified price point\n");
 	printf("it's used to make sure that we don't loss all of our money and many more\n");
	printf("same like take profit, our position will automatically closed after the market price hit our take profit price\n\n");
	
	system("pause");
	return;
 	
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int scanValue(const char *message) {
    int num;
    while (1) {
        printf("%s", message);
        if (scanf("%d", &val) != 1 || val < 10 || val > userCurrency) {
        	printf(RED);
            printf("Value must be between 10 and %lld\n",userCurrency);
            printf(RESET);
            clearBuffer();
        } else {
            clearBuffer();
            userCurrency-= val;
            return num;
        }
    }
}

int scanPos(const char *message) {
    int num;
    while (1) {
        printf("%s", message);
        if (scanf("%d", &pos) != 1 || pos < 20 || pos > 330 || pos % 10 != 0) {
        	printf(RED);
            printf("Position must be between 20 and 330 and multiple of 10.\n");
            printf(RESET);
            clearBuffer();
        } else {
            clearBuffer();
            return num;
        }
    }
}

int scanTp(const char *message) {
    int num;
    while (1) {
        printf("%s", message);
        if (scanf("%d", &tp) != 1 ||tp <= pos || tp < 10 || tp > 330 || tp % 10 != 0 ) {
        	printf(RED);
            printf("Take profit must be higher than position and between 10 and 330, multiple of 10.\n");
            printf(RESET);
            clearBuffer();
        } else {
            clearBuffer();
            return num;
        }
    }
}

int scanSl(const char *message) {
    int num;
    while (1) {
        printf("%s", message);
        if (scanf("%d", &sl) != 1 ||sl >= pos || sl < 10 || sl > 330 || sl % 10 != 0  ) {
        	printf(RED);
            printf("Stop loss must be lower than position and between 10 and 330, multiple of 10.\n");
            printf(RESET);
            clearBuffer();
        } else {
            clearBuffer();
            return num;
        }
    }
}

int scanTpShort(const char *message) {
    int num;
    while (1) {
        printf("%s", message);
        if (scanf("%d", &tp) != 1 ||tp >= pos || tp < 10 || tp > 330 || tp % 10 != 0 ) {
        	printf(RED);
            printf("Take profit must be lower than position and between 10 and 330, multiple of 10.\n");
            printf(RESET);
            clearBuffer();
        } else {
            clearBuffer();
            return num;
        }
    }
}

int scanSlShort(const char *message) {
    int num;
    while (1) {
        printf("%s", message);
        if (scanf("%d", &sl) != 1 ||sl <= pos || sl < 10 || sl > 330 || sl % 10 != 0  ) {
        	printf(RED);
            printf("Stop loss must be higher than position and between 10 and 330, multiple of 10.\n");
            printf(RESET);
            clearBuffer();
        } else {
            clearBuffer();
            return num;
        }
    }
}


void menu(){
	int choice = 0;
	int message = 0;
	printf(" Input >> ");
	scanf("%d",&choice); getchar();
	
	switch(choice){
		case 1: 
			generateCandleSticks();
			break;
		case 2:
			startIndex--;
			break;
		case 3: 
			startIndex++;
			break;
		case 4: 
			scanValue("Value must be between 10 and your currency : ");
			scanPos("Position must be between 20 and 330 and multiple of 10 : ");
			scanTp("Take profit must be higher than position and between 10 and 330, multiple of 10 : ");
			scanSl("Stop loss must be lower than position and between 10 and 330, multiple of 10 : ");
			break;
			
		case 5:
			scanValue("Value must be between 10 and your currency : ");
			scanPos("Position must be between 20 and 330 and multiple of 10 : ");
			scanTpShort("Take profit must be lower than position and between 10 and 330, multiple of 10 : ");
			scanSlShort("Stop loss must be higher than position and between 10 and 330, multiple of 10 : ");
			break;
		case 6: 
			pilihan=4;
			return;
//			menuPertama();
			break;
	}
	graph();
	menu();
}



int getHashKey(char username[255]){
	int sum = 0;
    for (int i = 0; username[i] != '\0'; i++) {
        sum += (int)username[i]; // Sum of ASCII values of characters in the username
    }
    return sum % 27; 
}

struct user* newNode(char username[], char email[], char password[]){
	struct user* newNode=(struct user*)malloc(sizeof(struct user));
	
	strcpy(newNode->username,username);	
	strcpy(newNode->email, email);	
	strcpy(newNode->password, password);
	newNode->next=NULL;
	
	return newNode;	
}

void insertData(char username[255], char email[255], char password[255]){
	int index=getHashKey(username);
	
	if(hashTable[index]==NULL){
		hashTable[index]=newNode(username, email, password);
		return;
	}
	struct user* tempData=hashTable[index];
	
	while(tempData->next != NULL){
		tempData = tempData->next;
	}
	tempData->next=newNode(username, email, password);
	return;
}

void printHashTable(){
	
//	sizeof(hashTable)/sizeof(hashTable[0]);
	for(int i=0;i<26;i++){
		if(hashTable[i]!=NULL){
			struct user* tempUser=hashTable[i]->next;
		printf("%d %s %s %s", i+1,hashTable[i]->username, hashTable[i]->email, hashTable[i]->password);
		while(tempUser !=NULL){
			printf(" -> %s %s %s", tempUser->username, tempUser->email, tempUser->password);
			tempUser=tempUser->next;
		}	
		} else{
			printf("%d. NULL", i+1);
		}
		printf("\n");
	}
}

bool searchData(char email[], char password[]){
	
	for(int i=0;i<26;i++){
		if(hashTable[i] != NULL){
			struct user* tempData = hashTable[i];
			while(tempData != NULL){
				if(strcmp(email, tempData->email)==0 && strcmp(email, tempData->email)==0){
				return true;
			}
			tempData=tempData->next;	
			}
			
		}
		
	}
	return false;
}

void loginUser(int *berhasil, char temp[101]) {
    char email[255];
    char password[255];
    int valid = 0;
    while (!valid) {
    	system("cls");
        printf("Enter your email (0 to go back to Main Menu): ");
        scanf("%s", email);
        
        if (strcmp(email, "0") == 0) {
            printf("Returning to Main Menu...\n");
            //system("pause");
            return;
        }
        
        if (strlen(email) == 0) {
            printf("Error: Email cannot be empty.\n");
            system("pause");
            continue;
        }
        
        system("cls");
        
        printf("Enter your password (0 to return to email input): ");
        scanf("%s", password);
        strcpy(temp, password);
        
        system("cls");
        
        if (strcmp(password, "0") == 0) {
            printf("Returning to email input...\n");
            //system("pause");
            return;
        }
        
        if (!searchData(email, password)) {
            FILE *file = fopen("user.txt", "r");
            if (file == NULL) {
                printf("Error opening file.\n");
                return; 
            }

            char email1[101][101];
            char username1[101][101];
            char password1[101][101];
            long long currency1[101];
            int z = 0;

            while (fscanf(file, "%[^#]#%[^#]#%[^#]#%lld\n", username1[z], email1[z], password1[z], &currency1[z]) != EOF) {
                if(strcmp(email1[z], email )==0 && strcmp(password1[z], password)==0){
                    insertData(username1[z],email1[z],password1[z]);
                    valid = 1;
                    *berhasil=10;
                    break;
                }
                z++;
            }
            
            fclose(file);

            if (!valid) {
                printf("Error: Invalid email or password. Please try again.\n");
                system("pause");
                continue;
            }
        }else{
        	valid = 1;
		}
        //printHashTable();
        
        printf("Login successful!\n");
        strcpy(email_login,email);
        system("pause");
    }
}




void registerUsername(int *c, char username[101]) {
    int valid = 0;
    user User;

    do {
        system("cls");
        printf("Input Username (Input 0 To Exit) : ");
        scanf("%s", User.username); 
        getchar(); 
        
        int len = strlen(User.username);

        if (strcmp(User.username, "0") == 0) {
            *c = 10;
            return;
        }

        if (len > 20 || len < 1) {
            printf("\033[1;31m");
            printf("Input username between 1-20 Characters\n\n");
            printf("\033[0m");
            system("pause");
            system("cls");
            registerUsername(c, username);
            return; 
        }

        for (int i = 0; i < len; i++) {
            if (!isalnum(User.username[i]) || (!isalpha(User.username[i]) && !isalnum(User.username[i]))) {
                printf("\033[1;31m");
                printf("Username can only contain letters and numbers\n\n");
                printf("\033[0m");
                system("pause");
                system("cls");
                registerUsername(c, username);
                return; 
            }
        }

		strcpy(username, User.username);
        valid = 1;
        printf("%s is now your username!\n\n", User.username);
        
        system("pause");

    } while (valid != 1);


}

void registerGmail(int *c, char gmail[101]) {
    //user User;
    int valid = 0;
    user User;
    
    do {
        system("cls");
        printf("Input Your Email (Input 0 To Exit) : ");
        scanf("%s", User.email); 
        getchar(); 
        
        if (strcmp(User.email, "0") == 0) {
            *c = 10;
            return;
        }
        
        int len = strlen(User.email);
        
        if (len > 36 || len < 6) {
            printf("\033[1;31m");
            printf("Input Email Between 6-36 Characters\n\n");
            printf("\033[0m");
            system("pause");
            system("cls");
            registerGmail(c, gmail);
            return; 
        }
        
        if (!isalpha(User.email[0])) {
            printf("\033[1;31m");
            printf("Email must start with a letter\n\n");
            printf("\033[0m");
            system("pause");
            system("cls");
            registerGmail(c, gmail);
			return; 
        }
        
        if (strchr(User.email, '#') != NULL) {
            printf("\033[1;31m");
            printf("Email cannot contain the character '#'\n\n");
            printf("\033[0m");
            system("pause");
            system("cls");
            registerGmail(c, gmail);
			return; 
        }
        
        int count = 0;
        
       for (int i = 0; i < len; i++) {
    		if ((!isalnum(User.email[i]) || (!isalpha(User.email[i]) && !isdigit(User.email[i]))) && (User.email[i] != '@' && User.email[i] != '.')) {
        	printf("\033[1;31m");
       		printf("Email can only contain letters, numbers, '@', and '.'\n\n");
        	printf("\033[0m");
        	system("pause");
        	system("cls");
        	registerGmail(c, gmail);
        	return;
    }
}

		for (int i = 0; i < len; i++) {
    		if (User.email[i] == '@') {
                count++;
            }
    }  
            
            if (count > 1) {
                printf("\033[1;31m");
                printf("Email should contain only one '@'\n\n");
                printf("\033[0m");
                system("pause");
                system("cls");
                registerGmail(c, gmail);
			return; 
            }
        
        
        if (User.email[len - 4] != '.' && User.email[len - 3] != 'c' && User.email[len - 2] != 'o' && User.email[len - 1] != 'm') {
            printf("\033[1;31m");
            printf("Email should end with '.com'\n\n");
            printf("\033[0m");
            system("pause");
            system("cls");
            registerGmail(c, gmail);
			return; 
        }
        
        if (User.email[len - 1] == ' ') {
            printf("\033[1;31m");
            printf("Email shouldn't end with a whitespace character\n\n");
            printf("\033[0m");
            system("pause");
            system("cls");
            registerGmail(c, gmail);
			return; 
        }
        
        // Validation for domain presence
        char *domain = strchr(User.email, '@');
        if (domain == NULL || strlen(domain) <= 1) {
            printf("\033[1;31m");
            printf("Email must have a domain after '@'\n\n");
            printf("\033[0m");
            system("pause");
            system("cls");
            registerGmail(c, gmail);
			return; 
        }

        valid = 1;
        strcpy(gmail,User.email);
        printf("%s is now your email!\n\n", User.email);
        system("pause");
    } while (valid != 1);
}

void registerPassword(int *c, char password[101]) {
    int has_alphabet = 0;
    int has_number = 0;
    user User;
    char ch;
    int z=0;
    int valid=0;
    *c=0;

    do {
        system("cls");
		printf("Input Your Password (Input 0 To Exit) : ");
//		scanf("%s", User.password);
//		getchar(); // Consuming newline character
		while((ch = _getch()) != 13) {
    		User.password[z] = ch;
    		z++;
   			printf("*");
		}
	
			printf("\n");
		
		User.password[z] = '\0';
//		printf("%s\n", User.password);


        if (strcmp(User.password, "0") == 0) {
            *c = 10;
            return;
        }

        int len = strlen(User.password);

        if (len < 8 || len > 36) {
            printf("\033[1;31m");
            printf("Password must be between 8 and 36 characters\n\n");
            printf("\033[0m");
            system("pause");
            system("cls");
            registerPassword(c, password);
            return;
        }

        for (int i = 0; i < len; i++) {
            if (!isalnum(User.password[i])) {
                printf("\033[1;31m");
                printf("Password can only contain letters and numbers\n\n");
                printf("\033[0m");
                system("pause");
                system("cls");
                registerPassword(c, password);
            return;
            }

            if (isdigit(User.password[i])) {
                has_number = 1;
            } else if (isalpha(User.password[i])) {
                has_alphabet = 1;
            }
        }

        if (!has_alphabet || !has_number) {
            printf("\033[1;31m");
            printf("Password must contain at least one alphabet and one number\n\n");
            printf("\033[0m");
            system("pause");
            system("cls");
            registerPassword(c, password);
            return;
        }

        printf("Password is valid!\n\n");
        strcpy(password, User.password);
        system("pause");
        system("cls");
        valid=1;
        

    } while (!valid);
}

void menu2() {
	char username[101];
	char gmail[101];
	char password[101];
	long long int currency=10000;
	
	FILE *file = fopen("user.txt", "a+");
    int c = 0, d=0;
    registerUsername(&c, username);
    if (c == 10) {
        return;
    }
    
    registerGmail(&c, gmail);
    if (c == 10) {
        return;
    }
    
    registerPassword(&c, password);
    if (c == 10) {
        return;
    }
    
    //User.currency=10000;
    fprintf(file,"%s#%s#%s#%lld\n", username, gmail ,password, currency);
    printf("your file succesfully saved");
    fclose(file);
}

void getUsername(){
	char line [MAX_LENGTH];
	char *getuser;
	char *getCurrency;
	FILE *file;
	
	file = fopen("user.txt","r");
	if(file == NULL){
		printf("File is cannot be open or not found! \n");
	
	}
	
	while (fgets(line,sizeof(line),file)){
		getuser = strtok(line,"#\n");
		char *found_email = strtok(NULL,"#");
		getCurrency = strtok(NULL, "#"); // password
        getCurrency = strtok(NULL, "#"); // current
		
		if(strcmp(found_email,email_login)==0){
			userCurrency = atoll(getCurrency);
			strcpy(username_login,getuser);

			fclose(file);
		}
	}
}

void userMenu(){
//	int pilihan;
	
	getUsername();
	
	
	do{
		system("cls");
//		if(logout == -1 ){
//			logout = 0;
//		return;
//	}
	
	printf("Meta FI - User MENU - %s\n",username_login);
	puts("1. Start Trade");
	puts("2. Trade History");
	puts("3. Guide");
	puts("4. Log Out");
	printf(">> ");
	scanf("%d", &pilihan);
	
	switch(pilihan){
		case 1 :{
			graph();
			printf("\n");
			menu();
			break;
		}
		case 2 : {
			displayHistory();
			system("pause");
			break;
		}
		case 3 : {
			displayGuide();
			break;
		}
	}	
	} while(pilihan !=  4);
	
	
	
}

void menuPertama(){
	logout = 0;
	puts("______________  _______  _________  ________  ________ ___          ___    ___       _______  ___   ___                   _______");
    puts("|\\   _ \\  _   \\|\\  ___ \\|\\___   ___\\\\   __  \\|\\  _____\\\\  \\        |\\  \\  /  /|     /  ___  \\|\\  \\ |\\  \\                 /  ___  \\");  
    puts("\\ \\  \\\\\\__\\ \\  \\ \\   __/\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \__/\\ \\  \\        \\ \\  \\/  / /    /__/|_/  /\\ \\  \\\\_\\  \\  ____________ /__/|_/  /|");  
    puts(" \\ \\  \\\\|__| \\  \\ \\  \\_|/__  \\ \\  \\ \\ \\   __  \\ \\   __\\\\ \\  \\       \\ \\    / /     |__|//  / /\\ \\______  \\|\\____________\\__|//  / /");
    puts("  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\  \\ \\  \\ \\ \\  \\ \\  \\ \\  \\_| \\ \\  \\       /     \\/          /  /_/__\\|_____|\\  \\|____________|   /  /_/__");
    puts("   \\ \\__\\    \\ \\__\\ \\_______\\  \\ \\__\\ \\ \\__\\ \\__\\ \\__\\   \\ \\__\\     /  /\\   \\         |\\________\\     \\ \\__\\               |\\________\\");
    puts("    \\|__|     \\|__|\\|_______|   \\|__|  \\|__|\\|__|\\|__|    \\|__|    /__/ /\\ __\\         \\|_______|      \\|__|                \\|_______|");
   // puts("                                                                  |__|/  \\|__|                                                                  ");
	puts("Welcome To META FI");
	puts("1. Log In To Trade");
	puts("2. Register Account");
	puts("3. Exit Application");
	printf(">> ");
	
	
		
		
}


int main(){
	
	
	int choice;
	char username[191];
	
	
	do{
		system("cls");
		setFullscreen();
		menuPertama();
		scanf("%d", &choice); getchar();
		
		switch(choice){
			case 1 : {
				char temp[101];
				int berhasil;
				system("cls");
    			loginUser(&berhasil, temp);
    			
    			 FILE *file = fopen("user.txt", "r");
           

            char email1[101][101];
            char username1[101][101];
            char password1[101][101];
            long long currency1[101];
            
            char username[101];
            int z = 0;

            while (fscanf(file, "%[^#]#%[^#]#%[^#]#%lld\n", username1[z], email1[z], password1[z], &currency1[z]) != EOF) {
                if(strcmp(password1[z], temp )==0 ){
                    strcpy(username, username1[z]);
                }
                z++;
            }
            
            fclose(file);
    			
    if(berhasil==10){
    	userMenu();
	}
    
	
    
			
			
				

				break;
			}
			case 2 : {
				menu2();
				break;
			}
			case 3 : {


				break;
			}
			default : {
				printf("MASUKAN ANGKA ANTARA 1, 2, ATAU 3\n");
				break;
			}
			
		}
			
		
		
		if (choice != 3) {
            system("pause");
        }
	} while(choice !=3);
	
	
	
	
	
	return 0;
}
