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

            // the board
            vector<string> board;
            unsigned int horizontal_start = INT32_MAX;
            int horizontal_end = -1;
            unsigned int vertical_start = INT32_MAX;
            int vertical_end = -1;
            void update_bounderys(unsigned int horizontal, unsigned int vertical,Direction d, unsigned int len);
            void postHorizontal(unsigned int horizontal,unsigned int vertical,const std::string& message);
            void postVertical(unsigned int horizontal,unsigned int vertical,std::string message);
            std::string readHorizontal(unsigned int horizontal, unsigned int vertical, unsigned int len);
            std::string readVertical(unsigned int horizontal, unsigned int vertical, unsigned int len);

        // public methods and variables
        public:

            // constructor
            Board() noexcept: board(0, "_") {};

            // post method
            void post(unsigned int horizontal, unsigned int vertical, Direction d, const std::string &message);

            // read method
            std::string read(unsigned int horizontal, unsigned int vertical, Direction d, unsigned int length);

            // show method
            void show();
    };
}
