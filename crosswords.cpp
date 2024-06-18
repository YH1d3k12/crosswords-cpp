#include <iostream>
#include <vector>
#include "stringTransform.h"
#include "terminus.h"

using namespace std;

// Defina o tamanho do caça palavras AQUI.
int const ROWS = 12, COLS = 17;
// Defina os pontos por letra aqui.
int const SUCCESS_POINTS = 10;
// Defina a penalidade por erros aqui.
int const PENALTY = -5;

// Prototipagem das funções.
void printGrid(int rows, int cols, string crossword[ROWS][COLS]);
void printHints(vector<string> hints);
int printMenu(int score, string crossword[ROWS][COLS], string COMPLETED_CROSSWORD[ROWS][COLS]);
int checkLetter(string letter, int row, int col, string crossword[ROWS][COLS], string COMPLETED_CROSSWORD[ROWS][COLS]);
int checkHorizontalWord(string word, int row, int initialCol, int finalCol, string crossword[ROWS][COLS], string COMPLETED_CROSSWORD[ROWS][COLS]);
int checkVerticalWord(string word, int col, int initialRow, int finalRow, string crossword[ROWS][COLS], string COMPLETED_CROSSWORD[ROWS][COLS]);
bool isCrosswordCompleted(string crossword[ROWS][COLS], string COMPLETED_CROSSWORD[ROWS][COLS]);


int main() {
    system("chcp 65001");
    int score = 0, turnCount = 0, totalTurns = 40;
    bool finished = false;

    // Crie o caça palavras por completo aqui.
    string COMPLETED_CROSSWORD[ROWS][COLS] = {
        {"#", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"},
        {"1", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "¹⁰↓", "#", "#", "#", "#"},
        {"2", "#", "#", "²↓", "#", "#", "#", "#", "#", "#", "#", "#", "L", "#", "#", "#", "#"},
        {"3", "¹→", "M", "A", "G", "O", "#", "⁹→", "M", "A", "G", "I", "A", "#", "#", "#", "#"},
        {"4", "#", "#", "N", "#", "⁴↓", "#", "#", "#", "#", "#", "¹¹→", "D", "R", "O", "W", "#"},
        {"5", "#", "#", "A", "⁵→", "D", "A", "D", "O", "S", "¹²↓", "#", "I", "#", "#", "#", "#"},
        {"6", "#", "³→", "O", "U", "R", "O", "#", "#", "#", "L", "#", "N", "#", "#", "#", "#"},
        {"7", "#", "#", "#", "⁶→", "A", "R", "Q", "U", "E", "I", "R", "O", "#", "#", "#", "#"},
        {"8", "#", "#", "⁷→", "O", "G", "R", "O", "#", "#", "C", "#", "#", "#", "#", "#", "#"},
        {"9", "#", "#", "#", "#", "A", "#", "#", "#", "¹³→", "H", "U", "M", "A", "N", "O", "#"},
        {"10", "⁸→", "E", "L", "F", "O", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
        {"11", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"}
    };

    // Substitua as letras por ? aqui.
    string crossword[ROWS][COLS] = {
        {"#", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"},
        {"1", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "¹⁰↓", "#", "#", "#", "#"},
        {"2", "#", "#", "²↓", "#", "#", "#", "#", "#", "#", "#", "#", "?", "#", "#", "#", "#"},
        {"3", "¹→", "?", "?", "?", "?", "#", "⁹→", "?", "?", "?", "?", "?", "#", "#", "#", "#"},
        {"4", "#", "#", "?", "#", "⁴↓", "#", "#", "#", "#", "#", "¹¹→", "?", "?", "?", "?", "#"},
        {"5", "#", "#", "?", "⁵→", "?", "?", "?", "?", "?", "¹²↓", "#", "?", "#", "#", "#", "#"},
        {"6", "#", "³→", "?", "?", "?", "?", "#", "#", "#", "?", "#", "?", "#", "#", "#", "#"},
        {"7", "#", "#", "#", "⁶→", "?", "?", "?", "?", "?", "?", "?", "?", "#", "#", "#", "#"},
        {"8", "#", "#", "⁷→", "?", "?", "?", "?", "#", "#", "?", "#", "#", "#", "#", "#", "#"},
        {"9", "#", "#", "#", "#", "?", "#", "#", "#", "¹³→", "?", "?", "?", "?", "?", "?", "#"},
        {"10", "⁸→", "?", "?", "?", "?", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
        {"11", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"}
    };

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

        printGrid(ROWS, COLS, crossword);
        cout << "\n\n";

        printHints(hints);
        cout << "\n\n";

        score += printMenu(score, crossword, COMPLETED_CROSSWORD);
        system("pause");

        finished = isCrosswordCompleted(crossword, COMPLETED_CROSSWORD);
        turnCount++;
    } while (turnCount <= totalTurns && !finished);

    system("cls");
    if (finished) {
        cout << "\t\t" << "Parabéns! Você completou o caça palavras!" << "\n";
        cout << "\t\t" << "Pontuação final: " << score * (totalTurns - turnCount) << "\n";
    }
    else {
        cout << "\t\t" << "Você excedeu o número de turnos!" << "\n";
        cout << "\t\t" << "Pontuação final: " << score << "\n";
    }
    printGrid(ROWS, COLS, crossword);
    system("pause");
}


// Função para imprimir o grid de caça palavras.
void printGrid(int rows, int cols, string crossword[ROWS][COLS]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (crossword[i][j] != "#") {
                // Se não for uma celula vazia, imprima o caractere.
                SetConsoleTextAttribute(hc, randomColor());
                gotoxy(j * 5, i * 2 + 5);
                cout << crossword[i][j];
            }
            else {
                // Se for uma celula vazia, imprima nada.
                SetConsoleTextAttribute(hc, 3);
                gotoxy(j * 5, i * 2 + 5);
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


int printMenu(int score, string crossword[ROWS][COLS], string COMPLETED_CROSSWORD[ROWS][COLS]) {
    int action, initialRow, finalRow, initialCol, finalCol;
    string input;

    cout << "[1] - Inserir letra" << "\n";
    cout << "[2] - Inserir Palavra - Horizontal" << "\n";
    cout << "[3] - Inserir Palavra - Vertical" << "\n";
    cin >> action;

    switch (action) {
        case 1:
            cout << "\n" << "Digite a linha: "; cin >> initialRow;
            cout << "\n" << "Digite a coluna: "; cin >> initialCol;
            cout << "\n" << "Digite a letra: "; cin >> input;
            score = checkLetter(input, initialRow, initialCol, crossword, COMPLETED_CROSSWORD);
            break;
        case 2:
            cout << "\n" << "Digite a linha: "; cin >> initialRow;
            cout << "\n" << "Digite o começo da coluna: "; cin >> initialCol;
            cout << "\n" << "Digite o final da coluna: "; cin >> finalCol;
            cout << "\n" << "Digite a palavra: "; cin >> input;
            score = checkHorizontalWord(input, initialRow, initialCol, finalCol, crossword, COMPLETED_CROSSWORD);
            break;
        case 3:
            cout << "\n" << "Digite a coluna: "; cin >> initialCol;
            cout << "\n" << "Digite o começo da linha: "; cin >> initialRow;
            cout << "\n" << "Digite o final da linha: "; cin >> finalRow;
            cout << "\n" << "Digite a palavra: "; cin >> input;
            score = checkVerticalWord(input, initialCol, initialRow, finalRow, crossword, COMPLETED_CROSSWORD);
            break;
        default:
            cout << "Opção inválida!\n";
            break;
    }
    return score;
}


int checkLetter(
    string letter,
    int row,
    int col,
    string crossword[ROWS][COLS],
    string COMPLETED_CROSSWORD[ROWS][COLS]
) {
    // Se a letra for correta e já está no caça palavras, ignore.
    if (toUpperCase(letter) == COMPLETED_CROSSWORD[row][col] && crossword[row][col] == COMPLETED_CROSSWORD[row][col]) {
        return 0;
    }
    else if (toUpperCase(letter) == COMPLETED_CROSSWORD[row][col]) {
        crossword[row][col] = toUpperCase(letter);
        return SUCCESS_POINTS;
    }
    else {
        cout << "Letra incorreta!" << "\n";
        return PENALTY;
    }
}


int checkHorizontalWord(
    string word,
    int row,
    int initialCol,
    int finalCol,
    string crossword[ROWS][COLS],
    string COMPLETED_CROSSWORD[ROWS][COLS]
) {
    int wordIndex = 0, result = 0;
    for (int col = initialCol; col <= finalCol; col++) {
        result += checkLetter(string(1, word[wordIndex]), row, col, crossword, COMPLETED_CROSSWORD);
        wordIndex++;
    }
    return result;
}


int checkVerticalWord(
    string word,
    int col,
    int initialRow,
    int finalRow,
    string crossword[ROWS][COLS],
    string COMPLETED_CROSSWORD[ROWS][COLS]
) {
    int wordIndex = 0, result = 0;
    for (int row = initialRow; row <= finalRow; row++) {
        result += checkLetter(string(1, word[wordIndex]), row, col, crossword, COMPLETED_CROSSWORD);
        wordIndex++;
    }
    return result;
}


bool isCrosswordCompleted(string crossword[ROWS][COLS], string COMPLETED_CROSSWORD[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (crossword[i][j] != "#" && crossword[i][j] != COMPLETED_CROSSWORD[i][j]) {
                return false;
            }
        }
    }
    return true;
}