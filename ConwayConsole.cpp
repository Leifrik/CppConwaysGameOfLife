// ConwayConsole.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include "Cell.h"

//DEFINE VARIABLES AND STRUCTS
typedef struct Cell {
    bool alive;
    std::vector<struct Cell> neightbors[8];
} cell_t;



//DEFINE FUNCTIONS
void print_field(std::vector<std::vector<cell_t>> &field, unsigned int rows, unsigned int cols);

int main()
{
    unsigned int num_rows = 10;
    unsigned int num_cols = 10;

    std::vector<std::vector<cell_t>> field(num_rows, std::vector<cell_t>(num_cols));

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            cell_t new_cell = { false };
            field[i][j] = new_cell;
        }
    }

    print_field(field, num_rows, num_cols);
    
    return 0;

}


//FUNTION IMPLENTATION
void print_field(std::vector<std::vector<cell_t>>& vec, unsigned int rows, unsigned int cols) {
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            if (vec[i][j].alive)
                std::cout << 'X';
            else
                std::cout << '.';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
