// ConwayConsole.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>

//DEFINE VARIABLES AND STRUCTS
typedef struct Cell {
    bool alive;
    unsigned int alive_neighbors;
} cell_t;

unsigned int num_rows = 10;
unsigned int num_cols = 10;

std::vector<std::vector<cell_t>> field(num_rows, std::vector<cell_t>(num_cols));

//DEFINE FUNCTIONS
void print_field(unsigned int rows, unsigned int cols);

void count_neighbors(cell_t &cell, unsigned int x, unsigned int y) {
    unsigned int count = 0;
    for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j <= y+1; j++) {
            if (i == x && j == y)
                continue;

            if (i > -1 && j > -1 && i < num_rows && j < num_cols) {
                if (field[i][j].alive) {
                    count++;
                }
            }          
        }
    }
    cell.alive_neighbors = count;
}

void update_neighbor_count() {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            count_neighbors(field[i][j], i, j);
        }
    }
}
 
void update_field() {
    

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if ((field[i][j].alive_neighbors == 2 || field[i][j].alive_neighbors == 3) && field[i][j].alive == true) {//Any live cell with two or three live neighbours survives.
                field[i][j].alive = true;
            }
            else if (field[i][j].alive == false && field[i][j].alive_neighbors == 3) {//Any dead cell with three live neighbours becomes a live cell.
                field[i][j].alive = true;
            }
            else {
                field[i][j].alive = false;
            }
        }
    }
    update_neighbor_count();
}

void init_vector() {

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            cell_t new_cell = { false };
            field[i][j] = new_cell;
        }
    }
    field[num_rows / 2][num_cols / 2].alive = true;
    update_neighbor_count();
}

int main()
{
    init_vector();


    print_field(num_rows, num_cols);

    return 0;

}


//FUNTION IMPLENTATION
void print_field(unsigned int rows, unsigned int cols) {
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            if (field[i][j].alive)
                std::cout << (char)254;
            else
                std::cout << field[i][j].alive_neighbors;
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
