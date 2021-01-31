#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
//DEFINE VARIABLES AND STRUCTS
typedef struct Cell {
    bool alive;
    unsigned int alive_neighbors;
} cell_t;

unsigned int num_rows = 30;
unsigned int num_cols = 10;

std::vector<std::vector<cell_t>> field(num_cols, std::vector<cell_t>(num_rows));

//DEFINE FUNCTIONS
void print_field(unsigned int cols, unsigned int rows);

void count_neighbors(cell_t& cell, unsigned int x, unsigned int y);

void update_neighbor_count();

void update_field();

void init_vector();

void spawn_blinker(unsigned int x, unsigned int y);

void spawn_block(unsigned int x, unsigned int y);

void spawn_beacon(unsigned int x, unsigned int y);

void spawn_toad(unsigned int x, unsigned int y);

void spawn_glider(unsigned int x, unsigned int y);

void run(char user_input, bool& running);

void run_thousand_times();

int main()
{
    init_vector();
    print_field(num_cols, num_rows);
    bool running = true;
    char user_input;
    while (running) {
        std::cin >> user_input;
        run(user_input, running);     
    }

    return 0;

}


//FUNTION IMPLENTATION
void print_field(unsigned int cols, unsigned int rows) {
    for (unsigned int i = 0; i < cols; ++i) {
        for (unsigned int j = 0; j < rows; ++j) {
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

            if (i > -1 && j > -1 && i < num_cols && j < num_rows) {
                if (field[i][j].alive) {
                    count++;
                }
            }
        }
    }
    cell.alive_neighbors = count;
}

void update_neighbor_count() {
    for (int i = 0; i < num_cols; i++) {
        for (int j = 0; j < num_rows; j++) {
            count_neighbors(field[i][j], i, j);
        }
    }
}

void update_field() {


    for (int i = 0; i < num_cols; i++) {
        for (int j = 0; j < num_rows; j++) {
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

    for (int i = 0; i < num_cols; i++) {
        for (int j = 0; j < num_rows; j++) {
            cell_t new_cell = { false };
            field[i][j] = new_cell;
        }
    }
    spawn_glider(1,1);
    update_neighbor_count();
}

//SPAWN SHAPES

void spawn_blinker(unsigned int x, unsigned int y) {
    field[y][x - 1].alive = true;
    field[y][x].alive = true;
    field[y][x + 1].alive = true;
}

void spawn_block(unsigned int x, unsigned int y) {
    field[y][x].alive = true;
    field[y + 1][x].alive = true;
    field[y][x + 1].alive = true;
    field[y + 1][x + 1].alive = true;
}

void spawn_beacon(unsigned int x, unsigned int y) {
    spawn_block(x, y);
    spawn_block(x + 2, y + 2);
}

void spawn_toad(unsigned int x, unsigned int y) {
    field[y][x + 1].alive = true;
    field[y][x + 2].alive = true;
    field[y][x + 3].alive = true;

    field[y + 1][x].alive = true;
    field[y + 1][x + 1].alive = true;
    field[y + 1][x + 2].alive = true;
}

void spawn_glider(unsigned int x, unsigned int y) {
    field[y][x + 2].alive = true;
    field[y + 1][x].alive = true;
    field[y + 1][x + 2].alive = true;
    field[y + 2][x + 1].alive = true;
    field[y + 2][x + 2].alive = true;

}

void run_thounsand_times() {
    unsigned int i = 0;
    while (i < 1000) {
        update_field();
        system("CLS");
        print_field(num_cols, num_rows);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
        i++;
    }
}

//USER INTERACTION
void run(char user_input, bool& running) {
    switch (user_input)
    {
    case 'n':
        update_field();
        break;
    case 's':
        run_thounsand_times();
        break;
    default:
        running = false;
        break;
    }
    system("CLS");
    print_field(num_cols, num_rows);
}
