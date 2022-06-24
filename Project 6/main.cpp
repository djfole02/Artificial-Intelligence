#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <algorithm>

using namespace std;


struct rubiks {

    string top[9] = { "W0", "W1", "W2", "W3", "W4", "W5", "W6", "W7", "W8" };
    string bot[9] = { "Y0", "Y1", "Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8" };
    string left[9] = { "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8" };
    string right[9] = { "O0", "O1", "O2", "O3", "O4", "O5", "O6", "O7", "O8" };
    string front[9] = { "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8" };
    string back[9] = { "G0", "G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8" };

    string old_top[9] = { "" };
    string old_bot[9] = { "" };
    string old_left[9] = { "" };
    string old_right[9] = { "" };
    string old_front[9] = { "" };
    string old_back[9] = { "" };

    vector<string> move_types = { "F", "F'", "F2", "B", "B'", "B2", "U", "U'", "U2", "D", "D'", "D2", "L", "L'", "L2", "R", "R'", "R2"};
    vector<string> moves;

    void rotation(string r) { //turns the face based on the move read in the string

        for (int i = 0; i < 9; i++) {
            old_top[i] = top[i];
            old_right[i] = right[i];
            old_left[i] = left[i];
            old_back[i] = back[i];
            old_front[i] = front[i];
            old_bot[i] = bot[i];
        }

        if (r == "U") {
            top_cw();
        }
        else if (r == "U'") {
            top_ccw();
        }
        else if (r == "U2") {
            top_cw();
            for (int i = 0; i < 9; i++) {
                old_top[i] = top[i];
                old_right[i] = right[i];
                old_left[i] = left[i];
                old_back[i] = back[i];
                old_front[i] = front[i];
                old_bot[i] = bot[i];
            }
            top_cw();
        }
        else if (r == "D") {
            bot_cw();
        }
        else if (r == "D'") {
            bot_ccw();
        }
        else if (r == "D2") {
            bot_cw();
            for (int i = 0; i < 9; i++) {
                old_top[i] = top[i];
                old_right[i] = right[i];
                old_left[i] = left[i];
                old_back[i] = back[i];
                old_front[i] = front[i];
                old_bot[i] = bot[i];
            }
            bot_cw();
        }
        else if (r == "R") {
            right_cw();
        }
        else if (r == "R'") {
            right_ccw();
        }
        else if (r == "R2") {
            right_cw();
            for (int i = 0; i < 9; i++) {
                old_top[i] = top[i];
                old_right[i] = right[i];
                old_left[i] = left[i];
                old_back[i] = back[i];
                old_front[i] = front[i];
                old_bot[i] = bot[i];
            }
            right_cw();
        }
        else if (r == "L") {
            left_cw();
        }
        else if (r == "L'") {
            left_ccw();
        }
        else if (r == "L2") {
            left_cw();
            for (int i = 0; i < 9; i++) {
                old_top[i] = top[i];
                old_right[i] = right[i];
                old_left[i] = left[i];
                old_back[i] = back[i];
                old_front[i] = front[i];
                old_bot[i] = bot[i];
            }
            left_cw();
        }
        else if (r == "F") {
            front_cw();
        }
        else if (r == "F'") {
            front_ccw();
        }
        else if (r == "F2") {
            front_cw();
            for (int i = 0; i < 9; i++) {
                old_top[i] = top[i];
                old_right[i] = right[i];
                old_left[i] = left[i];
                old_back[i] = back[i];
                old_front[i] = front[i];
                old_bot[i] = bot[i];
            }
            front_cw();
        }
        else if (r == "B") {
            back_cw();
        }
        else if (r == "B'") {
            back_ccw();
        }
        else if (r == "B2") {
            back_cw();
            for (int i = 0; i < 9; i++) {
                old_top[i] = top[i];
                old_right[i] = right[i];
                old_left[i] = left[i];
                old_back[i] = back[i];
                old_front[i] = front[i];
                old_bot[i] = bot[i];
            }
            back_cw();
        }
    }

    void top_cw() { //turns the top face clockwise
        top[0] = old_top[6];
        top[1] = old_top[3];
        top[2] = old_top[0];
        top[3] = old_top[7];
        top[4] = old_top[4];
        top[5] = old_top[1];
        top[6] = old_top[8];
        top[7] = old_top[5];
        top[8] = old_top[2];

        front[0] = old_right[0];
        front[1] = old_right[1];
        front[2] = old_right[2];

        left[0] = old_front[0];
        left[1] = old_front[1];
        left[2] = old_front[2];

        back[0] = old_left[0];
        back[1] = old_left[1];
        back[2] = old_left[2];

        right[0] = old_back[0];
        right[1] = old_back[1];
        right[2] = old_back[2];
    }

    void top_ccw() { //turns the top face counter clockwise
        top[0] = old_top[2];
        top[1] = old_top[5];
        top[2] = old_top[8];
        top[3] = old_top[1];
        top[4] = old_top[4];
        top[5] = old_top[7];
        top[6] = old_top[0];
        top[7] = old_top[3];
        top[8] = old_top[6];

        front[0] = old_left[0];
        front[1] = old_left[1];
        front[2] = old_left[2];

        left[0] = old_back[0];
        left[1] = old_back[1];
        left[2] = old_back[2];

        back[0] = old_right[0];
        back[1] = old_right[1];
        back[2] = old_right[2];

        right[0] = old_front[0];
        right[1] = old_front[1];
        right[2] = old_front[2];
    }

    void bot_cw() {  //turns the bottom face clockwise
        bot[0] = old_bot[6];
        bot[1] = old_bot[3];
        bot[2] = old_bot[0];
        bot[3] = old_bot[7];
        bot[4] = old_bot[4];
        bot[5] = old_bot[1];
        bot[6] = old_bot[8];
        bot[7] = old_bot[5];
        bot[8] = old_bot[2];

        front[6] = old_left[6];
        front[7] = old_left[7];
        front[8] = old_left[8];

        left[6] = old_back[6];
        left[7] = old_back[7];
        left[8] = old_back[8];

        back[6] = old_right[6];
        back[7] = old_right[7];
        back[8] = old_right[8];

        right[6] = old_front[6];
        right[7] = old_front[7];
        right[8] = old_front[8];
    }

    void bot_ccw() { //turns the bottom face counter clockwise
        bot[0] = old_bot[2];
        bot[1] = old_bot[5];
        bot[2] = old_bot[8];
        bot[3] = old_bot[1];
        bot[4] = old_bot[4];
        bot[5] = old_bot[7];
        bot[6] = old_bot[0];
        bot[7] = old_bot[3];
        bot[8] = old_bot[6];

        front[6] = old_right[6];
        front[7] = old_right[7];
        front[8] = old_right[8];

        left[6] = old_front[6];
        left[7] = old_front[7];
        left[8] = old_front[8];

        back[6] = old_left[6];
        back[7] = old_left[7];
        back[8] = old_left[8];

        right[6] = old_back[6];
        right[7] = old_back[7];
        right[8] = old_back[8];
    }

    void left_cw() { //turns the left face clockwise
        left[0] = old_left[6];
        left[1] = old_left[3];
        left[2] = old_left[0];
        left[3] = old_left[7];
        left[4] = old_left[4];
        left[5] = old_left[1];
        left[6] = old_left[8];
        left[7] = old_left[5];
        left[8] = old_left[2];

        top[0] = old_back[8];
        top[3] = old_back[5];
        top[6] = old_back[2];

        front[0] = old_top[0];
        front[3] = old_top[3];
        front[6] = old_top[6];

        bot[0] = old_front[0];
        bot[3] = old_front[3];
        bot[6] = old_front[6];

        back[2] = old_bot[6];
        back[5] = old_bot[3];
        back[8] = old_bot[0];
    }

    void left_ccw() { //turns the left face counter clockwise
        left[0] = old_left[2];
        left[1] = old_left[5];
        left[2] = old_left[8];
        left[3] = old_left[1];
        left[4] = old_left[4];
        left[5] = old_left[7];
        left[6] = old_left[0];
        left[7] = old_left[3];
        left[8] = old_left[6];

        top[0] = old_front[0];
        top[3] = old_front[3];
        top[6] = old_front[6];

        front[0] = old_bot[0];
        front[3] = old_bot[3];
        front[6] = old_bot[6];

        bot[0] = old_back[8];
        bot[3] = old_back[5];
        bot[6] = old_back[2];

        back[2] = old_top[6];
        back[5] = old_top[3];
        back[8] = old_top[0];
    }

    void right_cw() { //turns the right face clockwise 
        right[0] = old_right[6];
        right[1] = old_right[3];
        right[2] = old_right[0];
        right[3] = old_right[7];
        right[4] = old_right[4];
        right[5] = old_right[1];
        right[6] = old_right[8];
        right[7] = old_right[5];
        right[8] = old_right[2];

        top[2] = old_front[2];
        top[5] = old_front[5];
        top[8] = old_front[8];

        front[2] = old_bot[2];
        front[5] = old_bot[5];
        front[8] = old_bot[8];

        bot[2] = old_back[6];
        bot[5] = old_back[3];
        bot[8] = old_back[0];

        back[0] = old_top[8];
        back[3] = old_top[5];
        back[6] = old_top[2];
    }

    void right_ccw() { //turns the right face counter clockwise
        right[0] = old_right[2];
        right[1] = old_right[5];
        right[2] = old_right[8];
        right[3] = old_right[1];
        right[4] = old_right[4];
        right[5] = old_right[7];
        right[6] = old_right[0];
        right[7] = old_right[3];
        right[8] = old_right[6];

        top[2] = old_back[6];
        top[5] = old_back[3];
        top[8] = old_back[0];

        front[2] = old_top[2];
        front[5] = old_top[5];
        front[8] = old_top[8];

        bot[2] = old_front[2];
        bot[5] = old_front[5];
        bot[8] = old_front[8];

        back[0] = old_bot[8];
        back[3] = old_bot[5];
        back[6] = old_bot[2];
    }

    void front_cw() { //turns the front face clockwise
        front[0] = old_front[6];
        front[1] = old_front[3];
        front[2] = old_front[0];
        front[3] = old_front[7];
        front[4] = old_front[4];
        front[5] = old_front[1];
        front[6] = old_front[8];
        front[7] = old_front[5];
        front[8] = old_front[2];

        top[6] = old_left[8];
        top[7] = old_left[5];
        top[8] = old_left[2];

        left[2] = old_bot[0];
        left[5] = old_bot[1];
        left[8] = old_bot[2];

        bot[0] = old_right[6];
        bot[1] = old_right[3];
        bot[2] = old_right[0];

        right[0] = old_top[6];
        right[3] = old_top[7];
        right[6] = old_top[8];
    }

    void front_ccw() { //turns the front face counter clockwise
        front[0] = old_front[2];
        front[1] = old_front[5];
        front[2] = old_front[8];
        front[3] = old_front[1];
        front[4] = old_front[4];
        front[5] = old_front[7];
        front[6] = old_front[0];
        front[7] = old_front[3];
        front[8] = old_front[6];

        top[6] = old_right[0];
        top[7] = old_right[3];
        top[8] = old_right[6];

        left[2] = old_top[8];
        left[5] = old_top[7];
        left[8] = old_top[6];

        bot[0] = old_left[2];
        bot[1] = old_left[5];
        bot[2] = old_left[8];

        right[0] = old_bot[2];
        right[3] = old_bot[1];
        right[6] = old_bot[0];
    }

    void back_cw() { //turns the back face clockwise
        back[0] = old_back[6];
        back[1] = old_back[3];
        back[2] = old_back[0];
        back[3] = old_back[7];
        back[4] = old_back[4];
        back[5] = old_back[1];
        back[6] = old_back[8];
        back[7] = old_back[5];
        back[8] = old_back[2];

        top[0] = old_right[2];
        top[1] = old_right[5];
        top[2] = old_right[8];

        right[2] = old_bot[8];
        right[5] = old_bot[7];
        right[8] = old_bot[6];

        left[0] = old_top[2];
        left[3] = old_top[1];
        left[6] = old_top[0];

        bot[6] = old_left[0];
        bot[7] = old_left[3];
        bot[8] = old_left[6];
    }

    void back_ccw() { //turns the back face counter clockwise
        back[0] = old_back[2];
        back[1] = old_back[5];
        back[2] = old_back[8];
        back[3] = old_back[1];
        back[4] = old_back[4];
        back[5] = old_back[7];
        back[6] = old_back[0];
        back[7] = old_back[3];
        back[8] = old_back[6];

        top[0] = old_left[6];
        top[1] = old_left[3];
        top[2] = old_left[0];

        right[2] = old_top[0];
        right[5] = old_top[1];
        right[8] = old_top[2];

        left[0] = old_bot[6];
        left[3] = old_bot[7];
        left[6] = old_bot[8];

        bot[6] = old_right[8];
        bot[7] = old_right[5];
        bot[8] = old_right[2];
    }

    int check_score() { //finds the score of the cube, 0 is best, 48 is worst possible
        int score = 0;
        for (int i = 0; i < 9; i++) {
            if (top[i] != "W" + to_string(i)) {
                score++;
            }
            if (bot[i] != "Y" + to_string(i)) {
                score++;
            }
            if (left[i] != "R" + to_string(i)) {
                score++;
            }
            if (right[i] != "O" + to_string(i)) {
                score++;
            }
            if (front[i] != "B" + to_string(i)) {
                score++;
            }
            if (back[i] != "G" + to_string(i)) {
                score++;
            }
        }
        return score;
    }

    void make_moves(vector<string> moves) {
        for (int i = 0; i < (int)moves.size(); i++) {
            rotation(moves[i]);
        }
    }

    bool check_isSolved() {
        if (check_score() == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    void print_cube() { //prints the cube in its arrays
        for (int i = 0; i < 9; i++) {
            cout << top[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 9; i++) {
            cout << bot[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 9; i++) {
            cout << left[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 9; i++) {
            cout << right[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 9; i++) {
            cout << front[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 9; i++) {
            cout << back[i] << " ";
        }
        cout << endl;
        cout << endl;
    }

    void print_moves() { //prints the moves of a cube
        for (int i = 0; i < (int)moves.size(); i++) {
            if (i != moves.size() - 1) {
                cout << moves[i] << " -> ";
            }
            else {
                cout << moves[i] << endl;
            }
        }
    }

    void shuffle_cube(int num_moves) { //shuffles a cube
        for (int i = 0; i < num_moves; i++) {
            int random = rand() % move_types.size();
            if (moves.size() > 0) {
                while (moves.back()[0] == move_types[random][0]) {
                    random = rand() % move_types.size();
                }
            }
            rotation(move_types[random]);
            moves.push_back(move_types[random]);
        }
    }

    void set_moves(vector<string> moves) {
        for (int i = 0; i < (int)moves.size(); i++) {
            rotation(moves[i]);
            this->moves.push_back(moves[i]);
        }
    }

    vector<string> get_moves() {
        return moves;
    }
};

struct moves_set {
    vector<string> moves;
    int score = INT_MAX;
    int filter_score = 1;
    int best_index = -1;
    vector<string> last_moves_group;
    vector<string> move_types = { "F", "F'", "F2", "B", "B'", "B2", "U", "U'", "U2", "D", "D'", "D2", "L", "L'", "L2", "R", "R'", "R2"};
    vector<string> group1 = { "U", "U'", "U2", "D", "D'", "D2" };
    vector<string> group2 = { "L", "L'", "L2", "R", "R'", "R2" };
    vector<string> group3 = { "F", "F'", "F2", "B", "B'", "B2" };

    void shuffle(int num_moves) { //creates a random set of moves adhering to the filtering guidelines.
        string prev = "";
        string curr = "";
        string next = "";
        int next_chosen = 0;
        for (int i = 0; i < num_moves; i++) {
            int random = rand() % move_types.size();
            
            if (moves.size() > 0) {
                curr = move_types[random];
                if (next_chosen == 1) {
                    curr = next;
                }
                int redo = 0;
                while (redo == 0) {
                    if (prev[0] == curr[0]) {
                        random = rand() % move_types.size();
                        curr = move_types[random];
                    }
                    else {
                        redo = 1;
                    }
                }
                if (prev[0] == 'U' && curr[0] == 'D' || prev[0] == 'D' && curr[0] == 'U') {
                    random = rand() % group1.size();
                    int select = rand() % 2;
                    if (select == 0) {
                        next = group2[random];
                    }
                    else {
                        next = group3[random];
                    }
                    next_chosen = 1;
                }
                else if (prev[0] == 'L' && curr[0] == 'R' || prev[0] == 'R' && curr[0] == 'L') {
                    random = rand() % group1.size();
                    int select = rand() % 2;
                    if (select == 0) {
                        next = group1[random];
                    }
                    else {
                        next = group3[random];
                    }
                    next_chosen = 1;
                }
                else if (prev[0] == 'F' && curr[0] == 'B' || prev[0] == 'B' && curr[0] == 'F') {
                    random = rand() % group1.size();
                    int select = rand() % 2;
                    if (select == 0) {
                        next = group1[random];
                    }
                    else {
                        next = group2[random];
                    }
                    next_chosen = 1;
                }
                else {
                    next_chosen = 0;
                }
                moves.push_back(curr);
                prev = curr;
                }
            else {
                moves.push_back(move_types[random]);
                prev = moves.back();
            }
        }
    }

    void set_score(rubiks cube) { //sets the score of the cube using the filter
        rubiks test_cube1 = cube;
        test_cube1.make_moves(moves);
        score = test_cube1.check_score()*filter();
        filter_score = filter();
        rubiks test_cube2 = cube;
        if (max_score_find(test_cube2) != -1) {
            score = 0;
        }
    }

    int max_score_find(rubiks cube) { //used to find if the cube gets solved somewhere in the middle of the move set
        rubiks test_cube = cube;
        int max_index = -1;
        int max_score = 0;
        for (int i = 0; i < (int)moves.size(); i++) {
            test_cube.rotation(moves[i]);
            if (test_cube.check_score() == max_score) {
                max_index = i;
                best_index = max_index;
            }
        }
        return max_index;
    }

    void slice_bloat() {
        moves.erase(moves.begin() + best_index + 1, moves.end());
    }

    void print_moves() {
        for (int i = 0; i < (int)moves.size(); i++) {
            if (i != moves.size() - 1) {
                cout << moves[i] << " -> ";
            }
            else {
                cout << moves[i] << endl;
            }
        }
    }

    int filter() { //used to give a filtering score for the moves list.
        string prev;
        string curr;
        string next;
        int filtration = 1;
        for (int i = 0; i < (int)moves.size()-2; i++) {
            prev = moves[i];
            curr = moves[i + 1];
            next = moves[i + 2];

            if (prev[0] == 'U' && curr[0] == 'D' || prev[0] == 'D' && curr[0] == 'U') {
                if (next[0] == 'U' || next[0] == 'D') {
                    filtration = 3;
                    filter_score = filtration;
                    return filtration;
                }
            }
            else if (prev[0] == 'L' && curr[0] == 'R' || prev[0] == 'R' && curr[0] == 'L') {
                if (next[0] == 'L' || next[0] == 'R') {
                    filtration = 3;
                    filter_score = filtration;
                    return filtration;
                }
            }
            else if (prev[0] == 'F' && curr[0] == 'B' || prev[0] == 'B' && curr[0] == 'F') {
                if (next[0] == 'F' || next[0] == 'B') {
                    filtration = 3;
                    filter_score = filtration;
                    return filtration;
                }
            }
            if (prev[0] == curr[0] || curr[0] == next[0]) {
                filtration = 2;
                filter_score = filtration;
                return filtration;
            }
        }
        return filtration;
    }
};

struct moves_population {
    vector<moves_set> pop;
    int generation = 0;
    rubiks cube;

    void initialize(int pop_size, rubiks cube) {
        for (int i = 0; i < pop_size; i++) {
            moves_set new_moves;
            new_moves.shuffle(20);
            new_moves.set_score(cube);
            pop.push_back(new_moves);
        }
    }

    void rank_moves() { //sort in order from highest score to lowest score
        moves_set key;
        int j;
        for (int i = 1; i < (int)pop.size(); i++) {
            key = pop[i];
            j = i - 1;
            while (j >= 0 && pop[j].score > key.score) {
                pop[j + 1] = pop[j];
                j = j - 1;
            }
            pop[j + 1] = key;
        }
    }

    moves_population(rubiks c, int pop_size) {
        cube = c;
        if (pop_size != 0) {
            initialize(pop_size, c);
            rank_moves();
        }
    };
};

moves_population crossover_method(moves_population p, string method, int kill) { //takes 4 parents, combines best parents together and worst parents together. Makes 4 children. Makes new population.
    moves_population child = moves_population(p.cube, 0);
    int size = p.pop.size();
    while ((int)child.pop.size() < size) {
        moves_set c1;
        moves_set c2;
        moves_set c3;
        moves_set c4;
        moves_population parent = moves_population(p.cube, 0);
        if (method == "one_point_crossover") {
            int rdp1 = (rand() % (p.pop.size() - kill));
            int rdp2 = (rand() % (p.pop.size() - kill));
            int rdp3 = (rand() % (p.pop.size() - kill));
            int rdp4 = (rand() % (p.pop.size() - kill));
            while (rdp1 == rdp2 || rdp1 == rdp3 || rdp1 == rdp4 || rdp2 == rdp3 || rdp2 == rdp4 || rdp3 == rdp4) {
                rdp1 = (rand() % p.pop.size());
                rdp2 = (rand() % p.pop.size());
                rdp3 = (rand() % p.pop.size());
                rdp4 = (rand() % p.pop.size());
            }
            parent.pop.push_back(p.pop[rdp1]);
            parent.pop.push_back(p.pop[rdp2]);
            parent.pop.push_back(p.pop[rdp3]);
            parent.pop.push_back(p.pop[rdp4]);
            parent.rank_moves();
            
            int a1 = (rand() % parent.pop[0].moves.size());
            for (int i = 0; i < a1; i++) {
                c1.moves.push_back(parent.pop[0].moves[i]);
                c2.moves.push_back(parent.pop[1].moves[i]);
                c3.moves.push_back(parent.pop[2].moves[i]);
                c4.moves.push_back(parent.pop[3].moves[i]);
            }
            for (int i = a1; i < (int)parent.pop[0].moves.size(); i++) {
                c1.moves.push_back(parent.pop[1].moves[i]);
                c2.moves.push_back(parent.pop[0].moves[i]);
                c3.moves.push_back(parent.pop[3].moves[i]);
                c4.moves.push_back(parent.pop[2].moves[i]);
            }
        }
        rubiks cube1 = p.cube;
        c1.set_score(cube1);
        cube1 = p.cube;
        c2.set_score(cube1);
        cube1 = p.cube;
        c3.set_score(cube1);
        cube1 = p.cube;
        c4.set_score(cube1);
        child.pop.push_back(c1);
        child.pop.push_back(c2);
        child.pop.push_back(c3);
        child.pop.push_back(c4);
    }
    //cout << "CROSSED" << endl;
    return child;
}

moves_population mutation_method(moves_population p, string method) { //takes a sequence, replaces a move with a different move. 66% mutation rate
    moves_population child = moves_population(p.cube, 0);
    int num_mutated = 0;

    if (method == "swap_mutation") {
        for (int i = 0; i < (int)p.pop.size(); i++) {
            moves_set c1 = p.pop[i];
            int rate = rand() % 3;
            if (rate > 0 && c1.filter() == 1) {
                int m1 = rand() % c1.moves.size();
                int m2 = rand() % c1.move_types.size();
                string move = c1.move_types[m2];
                c1.moves[m1] = move;
                int pass = 0;
                while (pass == 0) {
                    if (c1.filter() == 1) {
                        pass = 1;
                    }
                    else {
                        m2 = rand() % c1.move_types.size();
                        c1.moves[m1] = c1.move_types[m2];
                    }
                }
                c1.set_score(p.cube);
                num_mutated++;
                child.pop.push_back(c1);
            }
            else {
                child.pop.push_back(c1);
            }
        }
    }
    //cout << "MUTATED " << num_mutated << endl;
    return child;
}

vector<moves_population> genetic_algorithm(moves_population p, int kill) { //genetic algorithm that uses a crossover and mutation. repeats until itercation cap or until best score is 0
    vector<moves_population> results;
    int gen = 0;
    int kill_cut = kill;
    int iterations = 200;
    int index = 0;
    int best_score = INT_MAX;
    p.generation = gen;
    results.push_back(p);
    moves_population d = p;
    while (index < iterations && best_score != 0) {
        gen++;
        moves_population cross = moves_population(d.cube, 0);
        moves_population mut = moves_population(d.cube, 0);
        
        cross = crossover_method(d, "one_point_crossover", kill_cut);
        mut = mutation_method(cross, "swap_mutation");
        d.pop.clear();
        d.generation = gen;
        d.pop.insert(d.pop.begin(), mut.pop.begin(), mut.pop.end());
        d.rank_moves();
        
        if (d.pop[0].score < best_score) {
            index = 0;
            if (d.pop[0].score <= best_score) {
                best_score = d.pop[0].score;
                results.push_back(d);
            }
        }
        
        //cout << "GEN: " << gen << " | Best Score: " << d.pop[0].score << endl;
        index++;
    }
    cout << "TOTAL GENERATIONS: " << gen << endl;
    return results;
}

moves_set woc(vector<moves_population> mp, rubiks c) { //looks at the most popular two moves and adds them to the woc move list then the next two most popular until 20 moves is reached.
    moves_set wisdom;
    vector<vector<int>> crowd(wisdom.move_types.size(), vector<int>(wisdom.move_types.size(), 0));
    int start = 0;
    while (start != 20) {
        for (int i = 0; i < mp.size(); i++) {
            for (int j = 0; j < (int)(mp[i].pop.size() * .1); j++) {
                auto it1 = find(wisdom.move_types.begin(), wisdom.move_types.end(), mp[i].pop[j].moves[start]);
                auto it2 = find(wisdom.move_types.begin(), wisdom.move_types.end(), mp[i].pop[j].moves[start+1]);
                int first = distance(wisdom.move_types.begin(), it1);
                int second = distance(wisdom.move_types.begin(), it2);
                crowd[first][second]++;
            }
        }
        int best_first = -1;
        int best_second = -1;
        int best = 0;
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 18; j++) {
                if (crowd[i][j] > best) {
                    best = crowd[i][j];
                    best_first = i;
                    best_second = j;
                }
                crowd[i][j] = 0;
            }
        }
        wisdom.moves.push_back(wisdom.move_types[best_first]);
        wisdom.moves.push_back(wisdom.move_types[best_second]);
        start += 2;
    }
    wisdom.set_score(c);
    if (wisdom.best_index != -1) {
        wisdom.slice_bloat();
    }
    return wisdom;
}

int main() {
    srand(time(0));
    rubiks cube;
    cube.set_moves({ "B", "U'", "F", "U" }); //set of 4 moves
    //cube.set_moves({ "B", "U'", "F", "U", "B", "F", "D", "B2", "U2", "F2", "R2", "L2", "F'", "D'", "R", "U", "L'", "F", "R", "D", "U", "R", "U2", "L2", "B", "U2", "F'", "U2", "R'", "F"}); //set of 30 moves
    //cube.print_cube();
    //cout << "SHUFFLE MOVES: ";
    //cube.print_moves(); 
    //cout << endl;

    moves_population pop = moves_population(cube, 1000);

    auto gaStart = chrono::steady_clock::now();
    vector<moves_population> results = genetic_algorithm(pop, 700);
    auto gaEnd = chrono::steady_clock::now();
    auto wocStart = chrono::steady_clock::now();
    moves_set woc_results = woc(results, cube);
    auto wocEnd = chrono::steady_clock::now();

    if (results.back().pop[0].best_index != -1) {
        results.back().pop[0].slice_bloat();
    }
    for (int i = 0; i < results.size(); i++) {
        rubiks print = cube;
        cout << "\n\nGENERATION: " << results[i].generation << " | SCORE: " << results[i].pop[0].score << endl;
        print.make_moves(results[i].pop[0].moves);
        print.print_cube();
    }
    printf("\n\nGA ONLY Elapsed Time in seconds: %.2f\n", (double)chrono::duration_cast<chrono::seconds>(gaEnd - gaStart).count());
    cout << "BEST GENETIC ALGORITHM SCORE: ";
    cout << results.back().pop[0].score << "\n" << endl;
    cout << "BEST MOVES: " << endl;
    results.back().pop[0].print_moves();
    rubiks ga_cube = cube;
    ga_cube.make_moves(results.back().pop[0].moves);
    ga_cube.print_cube();
    printf("WOC ONLY Elapsed Time in milliseconds: %.2f\n", (double)chrono::duration_cast<chrono::milliseconds>(wocEnd - wocStart).count());

    cout << "WOC SCORE: ";
    cout << woc_results.score << endl;
    rubiks woc_cube = cube;
    cout << "BEST MOVES: " << endl;
    woc_results.print_moves();
    woc_cube.make_moves(woc_results.moves);
    woc_cube.print_cube();

    printf("GA + WOC Elapsed Time in seconds: %.2f\n", (double)chrono::duration_cast<chrono::seconds>(wocEnd - gaStart).count());

    return 0;
}
        