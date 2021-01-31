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

void count_neighbors(cell_t& cell, unsigned int x, unsigned int y);

void update_neighbor_count();

void update_field();

void init_vector();

void spawn_blinker(unsigned int x, unsigned int y);

void spawn_block(unsigned int x, unsigned int y);

void spawn_beacon(unsigned int x, unsigned int y);

void run(char user_input, bool& running);

int main()
{
    init_vector();
    print_field(num_rows, num_cols);
    bool running = true;
    char user_input;
    while (running) {
        std::cin >> user_input;
        run(user_input, running);
        
    }

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

void count_neighbors(cell_t& cell, unsigned int x, unsigned int y) {
    unsigned int count = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
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
    spawn_beacon((num_rows / 2), (num_cols / 2));
    update_neighbor_count();
}

//SPAWN SHAPES

void spawn_blinker(unsigned int x, unsigned int y) {
    field[x - 1][y].alive = true;
    field[x][y].alive = true;
    field[x + 1][y].alive = true;
}

void spawn_block(unsigned int x, unsigned int y) {
    field[x][y].alive = true;
    field[x][y + 1].alive = true;
    field[x + 1][y].alive = true;
    field[x + 1][y + 1].alive = true;
}

void spawn_beacon(unsigned int x, unsigned int y) {
    spawn_block(x, y);
    spawn_block(x + 2, y + 2);
}


//USER INTERACTION
void run(char user_input, bool& running) {
    switch (user_input)
    {
    case 'n':
        update_field();
        break;
    default:
        running = false;
        break;
    }
    system("CLS");
    print_field(num_rows, num_cols);
}
