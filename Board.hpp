#pragma once

// includes
#include <string>
#include <vector>
#include "Direction.hpp"

// namespaces
using ariel::Direction;
using namespace std;

// declare board class in ariel namespace
namespace ariel {
    class Board {

        // private methods and variables
        private:

            // the matrix of the meesageboard
            vector<vector<char>> matrix;

            // n is the horizontal size of the matrix
            unsigned int n;

            // m is the vertical size of the metrix
            unsigned int m;

            // private resize method
            void resizeBoard(unsigned int i, unsigned int j) {
                this->n = i;
                this->m = j;
                this->matrix.resize(i);
                for(unsigned int p = 0; p < i ; p++) {
                    this->matrix[p].resize(j, '_');
                }
            }

        // public methods and variables
        public:

            // default constructor
            Board() {
                this->matrix = vector<vector<char>>(0, vector<char> (0, '_'));
                this->n = 0;
                this->m = 0;
            }

            // posting on the board
            void post(unsigned int i, unsigned int j, Direction dir, std::string str);

            // read from the board
            std::string read(unsigned int i, unsigned int j, Direction dir, unsigned int len);

            // print board
            void show();
    };
}
