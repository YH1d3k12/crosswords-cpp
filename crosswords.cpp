#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <algorithm>

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


// Função para determinar as coordenadas que será imprimido no terminal.
void gotoxy(int x, int y) {
    COORD coord; coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Função para randomizar a cor dentro de um padrão específico.
int randomColor() {
    int color = rand() % 7 + 9;
    // Assegurando que o valor da cor seja entre 9 e 15.
    if (color > 15 || color < 9) {return randomColor();}
    return color;
}

// Função para transforma string em UPPERCASE.
string toUpperCase(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Função para imprimir o grid de caça palavras.
void printGrid(int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (crossword[i][j] != "#") { 
                // Se não for uma celula vazia, imprima o caractere.
                SetConsoleTextAttribute(hc, randomColor());
                gotoxy(j * 4, i * 2 + 5);
                cout << crossword[i][j];
            }
            else {
                // Se for uma celula vazia, imprima nada.
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


int checkLetter(string letter, int row, int col) {
    int result;
    /*
        Resultados:
        1 - Sucesso.
        2 - Falha.
        3 - Neutro.
    */

    // Se a letra for correta e já está no caça palavras, ignore.
    if (toUpperCase(letter) == COMPLETED_CROSSWORD[row][col] && crossword[row][col] == COMPLETED_CROSSWORD[row][col]) {
        return result = 3;
    }
    else if (toUpperCase(letter) == COMPLETED_CROSSWORD[row][col]) {
        crossword[row][col] = toUpperCase(letter);
        return result = 1;
    }
    else {
        cout << "Letra incorreta!\n";
        return result = 2;
    }
    return result = 3;
}


int checkHorizontalWord(string word, int row, int initialCol, int finalCol, int score) {
    int wordIndex = 0;
    for (int col = initialCol; col <= finalCol; col++) {
        score = checkLetter(string(1, word[wordIndex]), row, col);
        wordIndex++;
    }
    return score;
}


int checkVerticalWord(string word, int col, int initialRow, int finalRow, int score) {
    int wordIndex = 0;
    for (int row = initialRow; row <= finalRow; row++) {
        score = checkLetter(string(1, word[wordIndex]), row, col);
        wordIndex++;
    }
    return score;
}


int printMenu(int score) {
    int action, initialRow, finalRow, initialCol, finalCol;
    string letter;

    cout << "[1] - Inserir letra" << "\n";
    cout << "[2] - Inserir Palavra - Horizontal" << "\n";
    cout << "[3] - Inserir Palavra - Vertical" << "\n";
    cin >> action;

    switch (action) {
        case 1:
            cout << "\n" << "Digite a linha: "; cin >> initialRow;
            cout << "\n" << "Digite a coluna: "; cin >> initialCol;
            cout << "\n" << "Digite a letra: "; cin >> letter;
            score = checkLetter(letter, initialRow, initialCol);
            break;
        case 2:
            cout << "\n" << "Digite a linha: "; cin >> initialRow;
            cout << "\n" << "Digite o começo da coluna: "; cin >> initialCol;
            cout << "\n" << "Digite o final da coluna: "; cin >> finalCol;
            cout << "\n" << "Digite a palavra: "; cin >> letter;
            score = checkHorizontalWord(letter, initialRow, initialCol, finalCol, score);
            break;
        case 3:
            cout << "\n" << "Digite a coluna: "; cin >> initialCol;
            cout << "\n" << "Digite o começo da linha: "; cin >> initialRow;
            cout << "\n" << "Digite o final da linha: "; cin >> finalRow;
            cout << "\n" << "Digite a palavra: "; cin >> letter;
            score = checkVerticalWord(letter, initialCol, initialRow, finalRow, score);
            break;
        default:
            cout << "Opção inválida!\n";
            break;
    }
    return score;
}


main() {
	system("chcp 65001");
	
    int score = 0, turnCount = 0, totalTurns = 100;

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

    do {
        system("cls"); // Limpa a tela.
        cout << "Turno: " << turnCount + 1 << "\n";
        cout << "Pontuação: " << score << "\n\n";

        printGrid(ROWS, COLS);
        cout << "\n\n";
        printHints(hints);
        cout << "\n\n";
        score = printMenu(score);
        system("pause");

        turnCount++;
    } while (turnCount <= totalTurns);
}	