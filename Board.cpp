// includes
#include <iostream>
#include <string>
#include "Board.hpp"
#include "Direction.hpp"

// namespaces
using namespace std;

namespace ariel {

    // post method
    void Board::post(unsigned int i, unsigned int j, Direction dir, string str) {
        unsigned int str_len = str.size();
        bool flag = (dir == Direction::Horizontal);

        // if horizontal direction
        if(flag) { resizeBoard(std::max(this->n, i + 1), std::max(this->m, j + str_len + 1)); }
        
        // if vertical direction
        else { resizeBoard(std::max(this->n, i + str_len + 1), std::max(this->m, j + 1)); }

        // post loop
        for(unsigned int p = 0; p < str_len; p++) {
            this->matrix[i][j] = str[p];
            if(flag) { j++; } else { i++; }
        } 
    }

    // read method
    string Board::read(unsigned int i, unsigned int j, Direction dir, unsigned int len) {
        string ans;
        bool flag = (dir == Direction::Horizontal);
        try {
            for(int p = 0; p < len; p++){
                ans += this->matrix.at(i).at(j);
                if(flag) { j++; } else { i++; }
            }
        }
        catch(const std::exception& e) {
            cout << "out of the the board!" << endl;
        }
        return ans;
    }

    // print / show method
    void Board::show() {
        cout << "The board: \nrows: " << this->n << " cols: " << this->m << "\n\n"; 
        for(unsigned int i = 0; i < this->n; i++) {
            cout << i << ": ";
            for(unsigned int j = 0; j < this->m; j++) {
                cout << this->matrix[i][j] << " ";
            }
            cout << "\n\n";
        }
        cout << "\n";
    }

}
