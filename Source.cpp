/*

The is the source code of Monopoly Game written in C++
Programming Fundamental LAB Final Project (FAST - CFD)
04/01/2022

Group Member :-
F219478 - MUHAMMAD JAWAD (Leader)
F219511 - AIMA
F219445 - TALHA

*/

#include <iostream>
#include <string>
#include <array>
#include <iomanip>     // FOR SETW()
#include <stdlib.h>    // FOR SRAND OR RAND
#include <time.h> 
#include <Windows.h>  // FOR SLEEP()
#include <fstream>    // FOR FILE HANDLING

using namespace std;

void horizentalBoxs(string name[], string price[], int row, int position);
void verticleBoxes(string name[], string price[], int row, int  verticlePosition);
void start();
void board();
void flipTurn();

void takeInput();
void propertyPurchasingMenu();
void checkingProperty();
void buildingHouseMenu();
void buildingHotelMenu();

void communityChestCard();
void chanceCard();
void result();
void highScore();
void updateHightScore();

void initializingPropertyArray();
int mainMenu();
void header();
void instructions();
void getName();


string communityChest [6] = {"I'M SORRY: GO DIRECTLY INTO JAIL AND DO NOT PASS GO ","YOU HAVE JUST BOUGHT A NEW BIKE : TAKE RIDE TO FLEET STREET","TIME FOR HORSE RIDING : RIDE TO REGENT STREET","YOU SELL YOUR OLD BOOKS ON THE INTERNET AND EARN 50$","YOU HAVE WON A BEAUTY CONTEST : COLLECT 150$","YOU ARE SO HAPPY TODAY : GIVE 20$ TO YOUR OPPONENT"};

string chance[6] = { "ADVANCE TO GO" , "BANK PAYS YOU DIVIDEND OF 50$" ,"GO DIRECTLY INTO JAIL","PAY POOR TAX OF 15$","YOU RECEIVE A DEATH TREAT: GO BACK 3 SPACES","INCOME TAX REFUND : COLLECT 20$" };

string propertyNameTop[] = {"FREE PARK   ","STRAND ST.  ","CHANCE    " ,"FLEET ST.   " ,"TRAFALGAR   " ,"FRENCH ST.  "
                         ,"LEICESTER   " ,"COVENTRY   " ,"WATER WORK  " ,"PICCADILY   " ,"GOTO JAIL   " }; 

string propertyPriceTop[] = { "","$220     ","?      ","$230     ","$240     " ,"$200     " ,"$260     " ,"$260     " ,"$150     " ,"$280     " ,"" };


string propertyNameBottom[] = { "JUST VISIT  ","CONNECT   ","VERMONT   " ,"CHANCE   " ,"COFFEE AV. " ,"READING RD "
                         ,"INCOME TAX " ,"BALTIC AV. " ,"COMM.CHEST " ,"MEDITER AV " ,"    GO     " };

string propertyPriceBottom[] = { "(IN JAIL)   ","$120    ","$110    ","?     ","$100    " ,"$80    " ,"$200    " ,"$60     " ,"" ,"$60     " ,"<---    " };



string propertyNameVerticle[] = { "VINE ST.   ","REGENT ST.  ","MARBOR ST.  ","OXFORD ST.  " ,"COMM.CHEST  " ,"COMM.CHEST  "
                         ,"BOW ST.    " ,"BOLT ST.   " ,"MARY STA.   " ,"POL STA.   " ,"NORTH AV.   ","CHANCE    ", "OLD KENT   ","CADET ST.  ","ELECT. COMP  ","SUPER TAX  ","PALL MALL   ","MAIFAIR   " };

string propertyPriceVerticle[] = { "$200     ","$300     ","$180     ","$300     "," "," ","$180     ","$320     ","$200     ","$200     ","$160     ","?      ","$140     ","$350     ","$150     ","$100    ","$130     ","$400    " };


int propertyPrice[40] = { 0,60,0,60,200,80,100,0,110,120,0,130,150,140,160,200,180,0,180,200,0,220,0,230,240,200,260,260,150,280,0,300,300,0,320,200,0,350,100,400 };

int PropertyRent[40] = {0,10,0,5,200,20,25,0,30,40,0,40,50,40,50,60,50,0,50,60,0,70,0,80,80,60,90,90,100,120,0,120,120,0,120,60,0,150,100,200};

int PropertyIndex = 0;
int PriceIndex = 0;

int turn = 0;
int dice = 0;

int property[40];

string playerToken[2] = { "*","#" };

string playerName[2];

int playerPosition[2] = { 0,0 };

int boardRound[2] = { 1,1 };

int playerBalance[2] = { 1500,1500 };


int main() {

    mainMenu();

	return 0;
}

// THIS IS THE MAIN MENU OF GAME

int mainMenu() {

    system("CLS");
    int option;

    header();

    cout << "\t" << "[0] START GAME" << endl;
    cout << "\t" << "[1] HIGH SCORE" << endl;
    cout << "\t" << "[2] HOW TO PLAY?" << endl;
    cout << "\t" << "[3] QUIT" << endl << endl;

    cout << "\t" << "ENTER OPTION = ";
    cin >> option;

    switch (option) {

    case 0:
        start();
        break;
    case 1:
        highScore();
        break;
    case 2:
        instructions();
        break;
    case 3:
        return 0;
    default:
        mainMenu();

    }
}

//  THIS IS THE HEADER FOR INCREASING BEAUTY OF GAME

void header() {

    cout << " =========================================================" << endl;
    cout << "|       __   __  ___  _  _  ___  ___ _ __   __           |" << endl;
    cout << "|       |  \\/  |/ _ \\| \\| |/ _ \\| _ \\ |\\ \\ / /           |" << endl;
    cout << "|       | |\\/| | (_) | .` | (_) |  _/ |_\\ V /            |" << endl;
    cout << "|       |_|  |_|\\___/|_|\\_|\\___/|_| |____|_|             |" << endl;
    cout << "|                                                        |" << endl;
    cout << " ======================= v1.0.0 =========================" << endl;
    cout << endl;
    return;
}

//  THESE ARE THE INSTRUCTIONS ABOUT GAME

void instructions() {

    system("CLS");
    header();

    cout << "Monopoly is a multi-player economics-themed board game.In the game, players roll two dice to move around the game board,";
    cout <<"buyingand trading properties, and developing them with housesand hotels." << endl<<endl;
    cout << "Press space to roll dice and game will end when one of the player goes bankrupt." << endl << endl;

    system("pause");
    system("CLS");
    mainMenu();

    return;
}

//  THIS FUNCTION TAKE NAME FROM USER AND STORE IN NAME ARRAY

void getName() {

    system("CLS");
    header();

    for (int i = 0; i < 2; i++) {
        cout << "ENTER PLAYER " << i + 1 << " NAME = ";
        cin >> playerName[i];
    }

}

//  THIS FUNCTUON RUNS THROUGHOUT THE GAME AND CONTROL EACH FUNTIONS

void start() {

    getName();
    initializingPropertyArray();

    do {

        board();
        takeInput();
        system("pause");
        board();
        checkingProperty();    
        flipTurn();          
         
    } while (playerBalance [0] >= 0 && playerBalance[1] >= 0);

    result();


    system("pause");
    mainMenu();
}

//  THIS FUNCION ROLL DICE AND UPDATE ARRAYS

void takeInput() {

    int d1, d2;

    srand(time(NULL));

    cout << playerName[0] << " Balance = "<< playerBalance[0]<<"$" << " | " << playerName[1] << " Balance = " << playerBalance[1]<<"$" << endl;

    cout <<endl<< playerName[turn] << " = ";

    system("pause");

    cout<<endl << "Dice Rolling....."<<endl;
    Sleep(2000);

    d1 = rand() % 6 + 1; 
    d2 = rand() % 6 + 1; 


 

    cout << endl << playerName[turn] << " = ";

    cout << d1 << " | " << d2 << endl<<endl;

    dice = d1 + d2;

    playerPosition[turn] = playerPosition[turn] + dice;

    if (playerPosition[turn] > 39) {
        playerPosition[turn] = playerPosition[turn] - 40; 
        playerBalance[turn] = playerBalance[turn] + 200;

        if (boardRound[turn] < 3) {
            boardRound[turn]++;
        }
    }

}

//  THIS FUNTION CHANGE TURN FROM  ONE USER TO ANOTHER

void flipTurn() {

    if (turn == 0) {
        turn = 1;
    }
    else {
        turn = 0;
    }
}

//  THIS FUNCTION PRINT MONOPLY BOARD

void board() {

    system("CLS");

    int horizentalPosition = 0;
    int verticlePosition = 19;

    int verticleBoxNum = 1;      // FOR VERTICLE (TWO BOXES)
    PropertyIndex = 0;         // INITIALIZE TO 0 FOR EVERY TIME BEFORE PRINTING BOARD
    PriceIndex = 0;           // INITIALIZE TO 0 FOR EVERY TIME BEFORE PRINTING BOARD


    for (int i = 1; i <= 11; i++){

        if (i == 1) {
            horizentalPosition = 20;
            horizentalBoxs(propertyNameTop, propertyPriceTop,1, horizentalPosition);
        }
        else if (i == 11) {
            horizentalPosition = 10;
            horizentalBoxs(propertyNameBottom, propertyPriceBottom,11, horizentalPosition);
        }
        else {
            verticleBoxes(propertyNameVerticle, propertyPriceVerticle , verticleBoxNum++, verticlePosition --);
        }

    }

    header();

}

//  PRINT HORIZENTAL BOXES

void horizentalBoxs(string name[], string price[],int row , int position) {

    int height = 5;
    int width = 165;
    int propertyIndex = 0;
    int priceIndex = 0;

    for (int i = 0; i <= height; i++) {

        for (int j = 0; j <= width; j++) {

            if (i == 0 || i == height) {

                cout << "-";
                
            }
            else {

                if (j % 15 == 0) {
                    cout << "|";
                }
                else if(i==2) {
                    cout <<setw(14) << name[propertyIndex++];
                    j = j + 13;
                }
                else if (i == 3) {
                    cout << setw(14) << price[priceIndex++];
                    j = j + 13;
                }
                else if (i == 4) {

                    if ( position == playerPosition[0] || position == playerPosition[1] ) {

                        if (position == playerPosition[1]) {
                            cout << setw(14) << playerToken[1];
                        }
                        else {
                            cout << setw(14) << playerToken[0];
                        }

                        
                    }
                    else {
                        cout << setw(14) <<" ";
                    } 

                    if (row == 1) {
                        position ++;
                    }
                    else if (row == 11) {
                        position --;
                    }

                    j = j + 13;
                    
                }
                else {
                    cout << " ";
                }
            }

        }

        cout << endl;

    }

}

//  PRINT VERTICLE BOXES

void verticleBoxes(string name [],string price [],int row , int  verticlePosition) {

    int height = 5;
    int width = 165;


    for (int i = 0; i <= height; i++) {

        for (int j = 0; j <= width; j++) {

            if ( (i == 0 || i == height) && ( (j >= 0 && j <= 15) || (j >= width-15 && j <= width) ) ){
                cout << "-";
            }
            else if ( (j % 15 == 0) && (j <= 15 || j >= width - 15) ){
                cout << "|";
            }
            else if (i == 2 && (j <= 15 || j >= width - 15) ) {
                cout << setw(14) << name[PropertyIndex++];
                j = j + 13;
            }
            else if (i == 3 && (j <= 15 || j >= width - 15) ) {
                cout << setw(14) << price[PriceIndex++];
                j = j + 13;
            }
            else if (i == 4 && (j <= 15 || j >= width - 15) ) {

                if (verticlePosition == playerPosition[0] || verticlePosition == playerPosition[1]) {

                    if (verticlePosition == playerPosition[1]) {
                        cout << setw(14) << playerToken[1];
                    }
                    else {
                        cout << setw(14) << playerToken[0];
                    }


                }
                else {
                    cout << setw(14) << " ";
                }

                verticlePosition = verticlePosition + 10 + 2 * row;
                
                j = j + 13;

            }
            else {
                cout << " ";
            }

        }

        cout << endl;

    }

}

//  THIS CHECKS THE PROPERTY TYPE AND OWNERSHIP

void checkingProperty() {

    if (playerPosition[turn] == 4 || playerPosition[turn] == 38) {

        playerBalance[turn] = playerBalance[turn] - PropertyRent[playerPosition[turn]];

        cout <<"Tax Deducted Successfully...";
        Sleep(2000);

    }
    else if (playerPosition[turn] == 30) {

        playerBalance[turn] = playerBalance[turn] - 50;

        playerPosition[turn] = 10;

        cout << "Going To Jail...";

        Sleep(2000);

    }
    else if (playerPosition[turn] == 10 || playerPosition[turn] == 20 || playerPosition[turn] == 0) {
        // Just Visiting
    }
    else if (playerPosition[turn] == 2 || playerPosition[turn] == 17 || playerPosition[turn] == 33) {
        communityChestCard();
    }
    else if (playerPosition[turn] == 7 || playerPosition[turn] == 22 || playerPosition[turn] == 36) {
        chanceCard();
    }
    else {

        if (property[playerPosition[turn]] == -1) {
            propertyPurchasingMenu();
        }
        else if ( property[playerPosition[turn]] == turn && boardRound[turn] == 2) {
            buildingHouseMenu();
        }
        else if (property[playerPosition[turn]] == turn && boardRound[turn] == 3) {
            buildingHotelMenu();
        }
        else if (property[playerPosition[turn]] != -1 && property[playerPosition[turn]] != turn) {

            playerBalance[turn] = playerBalance[turn] - PropertyRent[playerPosition[turn]];

            cout <<"Rent Deducted Successfully...";
            Sleep(2000);

        }

    }

}

//  MENU FOR PURCHASING PROPERTY

void propertyPurchasingMenu() {

    cout << playerName[turn] << " Balance = " << playerBalance[turn]<<"$" << endl << endl;

    int option;

    cout << "[0] Ignore Purchasing "<<endl;
    cout << "[1] Purchase Property " << endl;
    cout <<endl<< "Enter Option = ";
    cin >> option;

    if (option) {

        if (playerBalance[turn] >= propertyPrice[playerPosition[turn]]) {

            property[playerPosition[turn]] = turn;

            playerBalance[turn] = playerBalance[turn] - propertyPrice[playerPosition[turn]];

            cout << endl << "Purchase Successfully...";
        }
        else {
            cout << endl << "Not Enough Money...";
        }

        
        Sleep(2000);
    }

}

//  MENU FOR BUILDING HOUSE

void buildingHouseMenu() {

    cout << playerName[0] << " Balance = " << playerBalance[0]<<"$" << endl << endl;

    int option;

    cout << "[0] Ignore Building House " << endl;
    cout << "[1] Build House " << endl;
    cout << endl << "Enter Option = ";
    cin >> option;

    if (option) {

        if (playerBalance[turn] >= propertyPrice[playerPosition[turn]]) {

            property[playerPosition[turn]] = turn;

            playerBalance[turn] = playerBalance[turn] - propertyPrice[playerPosition[turn]];

            PropertyRent[playerPosition[turn]] = PropertyRent[playerPosition[turn]] * 2 + 50;

            cout << endl << "House Build Successfully...";
        }
        else {
            cout << endl << "Not Enough Money...";
        }
        
        Sleep(2000);
    }

}

//  MENU FOR HOTEL HOUSE

void buildingHotelMenu() {

    cout << playerName[0] << " Balance = " << playerBalance[0] << "$" << endl << endl;

    int option;

    cout << "[0] Ignore Building Hotel " << endl;
    cout << "[1] Build Hotel " << endl;
    cout << endl << "Enter Option = ";
    cin >> option;

    if (option) {

        if (playerBalance[turn] >= propertyPrice[playerPosition[turn]]) {

            property[playerPosition[turn]] = turn;

            playerBalance[turn] = playerBalance[turn] - propertyPrice[playerPosition[turn]];

            PropertyRent[playerPosition[turn]] = PropertyRent[playerPosition[turn]] * 2 + 100;

            cout << endl << "Hotel Build Successfully...";
        }
        else {
            cout << endl << "Not Enough Money...";
        }

        Sleep(2000);
    }

}

//  CALL WHEN USER STANDS ON COMMUNITY CHEST BOX

void communityChestCard() {

    srand(time(NULL));

    cout << "Community Chest Card" << endl << endl;

    int option = rand() % 6;   

    cout << communityChest[option]<<endl;

    switch (option) {

        case 0:
            playerBalance[turn] = playerBalance[turn] - 50;
            playerPosition[turn] = 10;
            break;

        case 1:
            playerPosition[turn] = 23;
            break;

        case 2:
            playerPosition[turn] = 31;
            break;

        case 3:
            playerBalance[turn] = playerBalance[turn] + 50;
            break;

        case 4:
            playerBalance[turn] = playerBalance[turn] + 150;
            break;

        case 5:
            playerBalance[turn] = playerBalance[turn] - 20;
            if (turn == 0) {
                playerBalance[1] = playerBalance[1] + 20;
            }
            else {
                playerBalance[0] = playerBalance[0] + 20;
            }
            break;

        default:
            break;
    }

    cout << endl;
    system("pause");
    
}

//  CALL WHEN USER STANDS ON CHANCE BOX

void chanceCard() {

    srand(time(NULL));

    cout << "Chance Card" << endl << endl;

    int option = rand() % 6;

    cout << chance[option] << endl;

    switch (option) {

    case 0:
        playerBalance[turn] = playerBalance[turn] + 200;
        playerPosition[turn] = 0;

        if (boardRound[turn] < 3) {
            boardRound[turn] ++; 
        }

        break;

    case 1:
        playerBalance[turn] = playerBalance[turn] + 50;
        break;

    case 2:
        playerBalance[turn] = playerBalance[turn] - 50;
        playerPosition[turn] = 10;
        break;

    case 3:
        playerBalance[turn] = playerBalance[turn] - 15;
        break;

    case 4:
        playerPosition[turn] = playerPosition[turn] - 3;
        break;

    case 5:
        playerBalance[turn] = playerBalance[turn] + 20;
        break;

    default:
        break;
    }

    cout << endl;
    system("pause");

}

//  ANNOUNCE RESULT

void result() {

    board();

    if (playerBalance[1] > 0) {
        cout << playerName[1] << " Balance = " << playerBalance[1] << "$" << endl << endl;
        cout << "Congratulations !!! " << playerName[1] << " Won The Match...";
    }
    else if (playerBalance[0] > 0) {
        cout << playerName[0] << " Balance = " << playerBalance[1] << "$" << endl << endl;
        cout << "Congratulations !!! " << playerName[0] << " Won The Match...";
    }

    updateHightScore();

    cout << endl << endl;
}

// BELOW FUNTION IS TO DISPLAY HIGH SCORE

void highScore() {

    int score = 0;
    string name;

    system("CLS");
    header();

    ifstream input;

    input.open("HighScore.txt");

    if (input) {

        while (!input.eof()) {

            input >> name;
            input >> score;
        }
    }

    cout << "NAME" << "\t" << "SCORE" << endl << endl;

    if (score != 0) {
        cout << name << "\t" << score << endl;
    }

    input.close();
    cout << endl;
    system("pause");
    mainMenu();

}

// BELOW FUNTION UPDATE HIGH SCORE AFTER RESULT

void updateHightScore() {

    int OldScore = 0;
    string Oldname = "";
    int winnerIndex = 0;

    ifstream input;
    input.open("HighScore.txt");

    if (input) {

        while (!input.eof()) {

            input >> Oldname;
            input >> OldScore;
        }
    }

    input.close();

    if (playerBalance[0] > playerBalance[1]) {
        winnerIndex = 0;
    }
    else {
        winnerIndex = 1;
    }

    if (playerBalance[winnerIndex] > OldScore) {
        ofstream output;
        output.open("HighScore.txt");
        output << playerName[winnerIndex] << "\t" << playerBalance[winnerIndex];
        output.close();
    }
}

//  INITIALIZING ALL ELEMENTS OF ARRAY TO -1

void initializingPropertyArray() {

    for (int i = 0; i < 40; i++){
        property[i] = -1;
    }
}