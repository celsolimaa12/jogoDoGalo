#include <iostream>
using namespace std;

int main() {
    char tab[3][3];
    char jogador = 'X';
    int linha, coluna;

    // Inicializa tabuleiro
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tab[i][j] = ' ';

    cout << "=== Jogo do Galo ===" << endl;

    for (int jogada = 0; jogada < 9; jogada++) {
        // Mostra tabuleiro
        cout << endl << "  1 2 3" << endl;
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << " ";
            for (int j = 0; j < 3; j++)
                cout << tab[i][j] << (j < 2 ? '|' : '\0');
            cout << endl;
            if (i < 2) cout << "  -----" << endl;
        }

        cout << endl << "Vez do jogador " << jogador << endl;
        cout << "Linha (1-3): "; cin >> linha;
        cout << "Coluna (1-3): "; cin >> coluna;

        if (linha < 1 || linha > 3 || coluna < 1 || coluna > 3 || tab[linha-1][coluna-1] != ' ') {
            cout << "Posição inválida! Tenta outra." << endl;
            jogada--;
            continue;
        }

        tab[linha-1][coluna-1] = jogador;
        jogador = (jogador == 'X') ? 'O' : 'X';
    }

    cout << endl << "🎮 Fim de jogo!" << endl;
    return 0;
}