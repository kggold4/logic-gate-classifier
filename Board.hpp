#pragma once

// includes
#include <vector>
#include <string>
#include "Direction.hpp"

using namespace std;

// declare board class in ariel namespace
namespace ariel {

    // borad class
    class Board {

        // private methods and variables
        private:

            // helpful variables
            unsigned int h_start = INT32_MAX, v_start = INT32_MAX;
            int h_end = -1, v_end = -1;

            // the board represent by vector
            vector<string> board;

            // private update method
            void update(unsigned int horizontal, unsigned int vertical,Direction d, unsigned int len);

        // public methods and variables
        public:

            // constructor
            Board() noexcept: board(0, "_") {};

            // post method
            void post(unsigned int horizontal, unsigned int vertical, Direction dir, const string &message);

            // read method
            string read(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int length);

            // show method
            void show();
    };
}
