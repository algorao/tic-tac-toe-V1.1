/*
  Krishna Rao
  Mini Project
  Tic-Tac-Toe - two player game(w/files)
  Version 1.1
  Procedural Style (non OOP style)
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <string>
#include <vector>
const int RC = 3;
const char X = 'X';
const char O = 'O';
void intro();
void modarr(char[][RC], int);
void rando(int*, const int);
std::string* names(const int);
void assgn(int*, std::string*, std::string*, char*);
void conc(std::string*, char*, const int);
void askset(char[][RC], int, std::string*, char*, int);
void display(char[][RC], int);
void determine(char[][RC], int, bool&);
std::string mssg();
void won(std::string*, char*, int, std::vector<std::string>&);
void tie(std::vector<std::string>&);
char askUser();
void writeTo(std::string*, const int, int*, std::string*, char*, std::vector<std::string>);
int main()
{
    const int SIZE = 2;
    int random[SIZE];
    std::string pn[SIZE];
    std::vector <std::string> vec;
    char tictactoe[RC][RC], pc[SIZE],choice;
    intro();
    modarr(tictactoe, RC);
    rando(random, SIZE);
    std::string *nameptr = names(SIZE);
    assgn(random, nameptr, pn, pc);
    conc(pn, pc, SIZE);
    do{
        display(tictactoe, RC);
        bool status = false;
        int done = 0;
        while (status == false && (done < 9))
        {
            askset(tictactoe, RC, pn, pc, done);
            display(tictactoe, RC);
            determine(tictactoe, RC, status);
            if(status == true)
            {
                won(pn, pc, done, vec);
                modarr(tictactoe, RC);
            }
            else if(done == 8)
            {
                tie(vec);
                modarr(tictactoe, RC);
            }
            if((status == true)||(done == 8))
            {
                choice = askUser();

            }
            done++;
        }
    }while(choice == 'Y');
    writeTo(nameptr, SIZE, random, pn, pc, vec);
    delete []nameptr;
    nameptr = nullptr;
    return 0;
}
void intro()
{
    std::cout << "----------------" << std::endl;
    std::cout << "WELCOME!" << std::endl;
    std::cout << "----------------" << std::endl;
    /*
    Standard introduction.
    Again, welcome to the game and feel free to check out my program!
    */
}
void modarr(char x[][RC], int y)
{
    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < y; j++)
        {
            x[i][j] =  '_';
        }
    }
}
void rando(int *x, const int y)
{
    srand(time(0));
    for(int i = 0; i < y; i++)
    {
        *(x+i) = (rand()%2);
    }
}
std::string* names(const int x)
{
    std::string *dyname = new std::string[x];
    for(int i = 0; i < x; i++)
    {
        std::cout << "Name #"<< (i+1) << " :";
        std::cin >> *(dyname+i);
    }
    return dyname;
}
void assgn(int *w, std::string *x, std::string *y, char *z)
{
    if(*(w) == 0 && *(w+1) == 0)
    {
        *(y) = *(x+1);
        *(y+1) = *(x);
        *(z) = O;
        *(z+1) = X;
    }
    else if(*(w) == 0 && *(w+1) == 1)
    {
        *(y) = *(x+1);
        *(y+1) = *(x);
        *(z) = X;
        *(z+1) = O;
    }
    else if(*(w) == 1 && *(w+1) == 0)
    {
        *(y) = *(x);
        *(y+1) = *(x+1);
        *(z) = O;
        *(z+1) = X;
    }
    else if(*(w) == 1 && *(w+1) == 1)
    {
        *(y) = *(x);
        *(y+1) = *(x+1);
        *(z) = X;
        *(z+1) = O;
    }
}
void conc(std::string *x, char *y, const int z)
{
    std::cout << "\nPlaying order with associated character:" << std::endl;
    for(int i = 0; i < z; i++)
    {
        std::cout << (i+1) << ". " << *(x+i) << "  " << *(y+i) << std::endl;
    }
}
void askset(char a[][RC], int y, std::string *b, char *c, int z)
{
    bool place_stat = true;
    std::cout << '\n' << *(b+(z%2)) << "'s turn" << std::endl;
    int r,col;
    std::cout << "Row (#): ";
    std::cin >> r;
    std::cout << "Column (#): ";
    std::cin >> col;
    std::cin.ignore();
    if(a[r-1][col-1] != '_')
    {
        place_stat = false;
    }
    while(((r>3) || (r<0)) || ((col>3)||(col<0)) || (place_stat == false))
    {
        std::cout << "\nENTER A VALID ROW/COLUMN OR ONES THAT HAVEN'T BEEN CHOOSEN" << std::endl;
        std::cout << "Row: ";
        std::cin >> r;
        std::cout << "Column: ";
        std::cin >> col;
        if(a[r-1][col-1] != '_')
        {
            place_stat = false;
        }
        else if(a[r-1][col-1] == '_')
        {
            place_stat = true;
        }
    }
    if((z%2) == 0)
    {
       a[r-1][col-1] = *(c);
    }
    else
    {
        a[r-1][col-1] = *(c+1);
    }
}
void display(char x[][RC], int y)
{
    std::cout << '\n' << "    " << "~Tic-Tac-Toe Board~" << '\n' << std::endl;
    std::cout << "      C1    C2    C3" << std::endl;
    std::cout << "  R1  " << x[0][0] << "   |  " << x[0][1] << "  |  " << x[0][2] << std::endl;
    std::cout << "       ---|-----|---" << std::endl;
    std::cout << "  R2  " << x[1][0] << "   |  " << x[1][1] << "  |  " << x[1][2] << std::endl;
    std::cout << "       ---|-----|---" << std::endl;
    std::cout << "  R3  " << x[2][0] << "   |  " << x[2][1] << "  |  " << x[2][2] << std::endl;
    std::cout << '\n';
}
void determine(char x[][RC], int y, bool&z)
{
    if((x[0][0] == X && x[0][1] == X && x[0][2] == X)||
       (x[1][0] == X && x[1][1] == X && x[1][2] == X)||
       (x[2][0] == X && x[2][1] == X && x[2][2] == X))
    {
        z = true;
    }
    else if((x[0][0] == O && x[0][1] == O && x[0][2] == O)||
           (x[1][0] == O && x[1][1] == O && x[1][2] == O)||
           (x[2][0] == O && x[2][1] == O && x[2][2] == O))
    {
        z = true;
    }
    else if((x[0][0] == X && x[1][0] == X && x[2][0] == X)||
       (x[0][1] == X && x[1][1] == X && x[2][1] == X)||
       (x[0][2] == X && x[1][2] == X && x[2][2] == X))
    {
        z = true;
    }
    else if((x[0][0] == O && x[1][0] == O && x[2][0] == O)||
       (x[0][1] == O && x[1][1] == O && x[2][1] == O)||
       (x[0][2] == O && x[1][2] == O && x[2][2] == O))
    {
        z = true;
    }
    else if((x[0][0] == X && x[1][1] == X && x[2][2] == X)||
            (x[2][0] == X && x[1][1] == X && x[0][2] == X))
    {
        z = true;
    }
    else if((x[0][0] == O && x[1][1] == O && x[2][2] == O)||
            (x[2][0] == O && x[1][1] == O && x[0][2] == O))
    {
        z = true;
    }
}
std::string mssg()
{
    int i = (rand()%4);
    std::string x[4] = {"Maybe there's something special about the ", "Ah, that good'ol character ", "Dang, you won using an ", "Well played with an "};
    return x[i];
}
void won(std::string *x, char *y, int a, std::vector<std::string>&z)
{
    std::string endmssg = mssg();
    if((a%2) == 0)
    {
        std::cout << *(x) << " has won the game!" << endmssg << *(y) <<std::endl;
        std::cout << *(x+1) << ", don't back off! Play again to try and beat " << *(x) << "!" << std::endl;
        z.push_back(*(x));
    }
    else if(((a%2) == 1) && (a!=8))
    {
        std::cout << *(x+1) << " has won the game!" << endmssg << *(y+1) <<  std::endl;
        std::cout << *(x) << ", don't back off! Play again to try and beat " << *(x+1) << "!" << std::endl;
        z.push_back(*(x+1));
    }
}
void tie(std::vector<std::string>&x)
{
    std::cout << "TIE GAME! Play again to see who would win!" << std::endl;
    x.push_back("Tie");
}
char askUser()
{
    char x;
    std::cout << "Would you like to play again? If so enter 'Y' and if not, enter 'N': ";
    std::cin>> x;
    return x;
}
void writeTo(std::string*a, const int b, int*x, std::string*y, char*z, std::vector<std::string> vec)
{
    std::vector <int> tot_vec(3,0);
    std::ofstream ticfile;
    ticfile.open("Gamestats.txt");
    ticfile << "---------------------------\n";
    ticfile << "~~GAMESTATS~~\n";
    for(int i = 0; i < (3*b); i++)
    {
        if(i<b)
        {
            if((i%2) == 0)
            {
                ticfile << "---------------------------\n";
                ticfile << "NAMES:\n";
            }
            ticfile << (i+1) << ". " << *(a+i) << "\n";
        }
        else if(i<(2*b) && i>=b)
        {
            if((i%2) == 0)
            {
                ticfile << "---------------------------\n";
                ticfile << "PLAYER ORDER(#):\n";
            }
            ticfile << (i-1) << ". " << *(y+(i-2)) << "\n";
        }
        else if(i<(3*b) && i>=(2*b))
        {
            if((i%2) == 0)
            {
                ticfile << "---------------------------\n";
                ticfile << "PLAYER CHARACTER:\n";
            }
            ticfile << (i-3) << ". " << *(z+(i-4)) << "\n";
        }
    }
    ticfile << "---------------------------\n";
    ticfile << "OUTCOMES:\n";
    for(int i = 0; i < vec.size();i++)
    {
        if(vec[i] != "Tie")
        {
            if(vec[i] == *(y))
            {
                tot_vec[1] += 1;
            }
            else
            {
                tot_vec[2] += 1;
            }
            ticfile << vec[i] << " won\n";
        }
        else
        {
            tot_vec[0] += 1;
            ticfile << vec[i] << "\n";
        }
    }
    ticfile << "---------------------------\n";
    ticfile << "TOTALS:\n";
    ticfile << "Ties: " << tot_vec[0] << "\n";
    ticfile << "Player 1 Dubs: " << tot_vec[1] << "\n";
    ticfile << "Player 2 Dubs: " << tot_vec[2] << "\n";
    ticfile << "---------------------------\n";
    ticfile.close();
}
