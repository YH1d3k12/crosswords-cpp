#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);

int const ROWS = 11, COLS = 17;

string const COMPLETED_CROSSWORD[ROWS][COLS] = {
    {"#", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"},
    {"1", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "L", "#", "#", "#", "#"},
    {"2", "#", "M", "A", "G", "O", "#", "#", "M", "A", "G", "I", "A", "#", "#", "#", "#"},
    {"3", "#", "#", "N", "#", "#", "#", "#", "#", "#", "#", "#", "D", "R", "O", "W", "#"},
    {"4", "#", "#", "A", "#", "D", "A", "D", "O", "S", "#", "#", "I", "#", "#", "#", "#"},
    {"5", "#", "#", "O", "U", "R", "O", "#", "#", "#", "L", "#", "N", "#", "#", "#", "#"},
    {"6", "#", "#", "#", "#", "A", "R", "Q", "U", "E", "I", "R", "O", "#", "#", "#", "#"},
    {"7", "#", "#", "#", "O", "G", "R", "O", "#", "#", "C", "#", "#", "#", "#", "#", "#"},
    {"8", "#", "#", "#", "#", "A", "#", "#", "#", "#", "H", "U", "M", "A", "N", "O", "#"},
    {"9", "#", "E", "L", "F", "O", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
    {"10", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"}
};

string crossword[ROWS][COLS] = {
    {"#", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"},
    {"1", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "?", "#", "#", "#", "#"},
    {"2", "#", "?", "?", "?", "?", "#", "#", "?", "?", "?", "?", "?", "#", "#", "#", "#"},
    {"3", "#", "#", "?", "#", "#", "#", "#", "#", "#", "#", "#", "?", "?", "?", "?", "#"},
    {"4", "#", "#", "?", "#", "?", "?", "?", "?", "?", "#", "#", "?", "#", "#", "#", "#"},
    {"5", "#", "#", "?", "?", "?", "?", "#", "#", "#", "?", "#", "?", "#", "#", "#", "#"},
    {"6", "#", "#", "#", "#", "?", "?", "?", "?", "?", "?", "?", "?", "#", "#", "#", "#"},
    {"7", "#", "#", "#", "?", "?", "?", "?", "#", "#", "?", "#", "#", "#", "#", "#", "#"},
    {"8", "#", "#", "#", "#", "?", "#", "#", "#", "#", "?", "?", "?", "?", "?", "?", "#"},
    {"9", "#", "?", "?", "?", "?", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
    {"10", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"}
};


void gotoxy(int x, int y) {
    COORD coord; coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int randomColor() {
    int color = rand() % 7 + 9;
    // Assegurando que o valor da cor seja entre 9 e 15.
    if (color > 15 || color < 9) {return randomColor();}
    return color;
}


void printGrid(int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (crossword[i][j] != "#") {
                SetConsoleTextAttribute(hc, randomColor());
                gotoxy(j * 4, i * 2 + 5);
                cout << crossword[i][j];
            }
            else {
                SetConsoleTextAttribute(hc, 3);
                gotoxy(j * 4, i * 2 + 5);
                cout << " ";
            }
        }
    }
}


void printHints(vector<string> hints) {
    for (int i = 0; i < hints.size(); i++) {
        cout << i + 1 << ". " << hints[i] << "\n";
    }
}


int checkLetter(string letter, int row, int col, int score) {
    if (letter == COMPLETED_CROSSWORD[row][col]) {
        crossword[row][col] = letter;
        score++;
    }
    else {
        cout << "Letra incorreta!\n";
        score--;
    }
    return score;
}

void printMenu() {
    int action;

    switch (action) {
        
    }
}


main() {
	system("chcp 65001");
	

    int score = 0, turnCount = 0, totalTurns = 10;

    vector<string> hints = {
        "Classe conjuradora, geralmente representada pela sua barba, cajado e chapéu pontudo.",
        "Criatura baixa e robusta, reconhecida pelo seu artesanato e alcoolismo.",
        "Metal cobiçado por muitos pelo seu valor e estética, usado como moeda.", 
        "Criatura escamosa que sopra fogo.",
        "Ferramentas essenciais em muitos jogos rpg de mesa.",
        "Atirador a longa distância, caminho escolhido por muitos patrulheiros.",
        "Um brutamontes cheio de banha.",
        "Raça associada com elegância e natureza, muitas vezes esnobes.",
        "Força sobrenatural que distorce a realidade.",
        "Classe especialista em furtividade, armadilhas e truques sujos.",
        "Muitas vezes associado como um elfo corrupto.",
        "Ascensão cobiçada por muitos magos e feiticeiros malignos, um ser que transcende a mortalidade.",
        "Raça predominante na maioria dos mundos."
    };

    // do {
        system("cls");
        cout << "Turno: " << turnCount + 1 << "\n";
        cout << "Pontuação: " << score << "\n\n";

        printGrid(ROWS, COLS);
        cout << "\n\n";
        printHints(hints);
        cout << "\n\n";
        printMenu();
    // } while (turnCount <= totalTurns);
}	