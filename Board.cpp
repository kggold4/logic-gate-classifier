// includes
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <array>
#include "Board.hpp"
#include "Direction.hpp"

// namespaces
using namespace std;
using ariel::Direction;

// update_bounderys function
void ariel::Board::update_bounderys(unsigned int horizontal, unsigned int vertical, Direction d, unsigned int len) {
    int lenWithHorizontal = 0;
    int lenWithVertical = 0;
    if(d == Direction::Horizontal) {
        lenWithHorizontal=(int)horizontal+1;
        lenWithVertical=(int)(len+vertical);

    } else if(d == Direction::Vertical) {
        lenWithHorizontal=(int)(horizontal+len);
        lenWithVertical=1+(int)vertical;
    }
    if(this->horizontal_start == INT32_MAX && this->horizontal_end == -1 && this->vertical_start == INT32_MAX && this->vertical_end == -1) {
        this->horizontal_start = horizontal;
        this->horizontal_end = lenWithHorizontal;
        this->vertical_start = vertical;
        vertical_end = lenWithVertical;
        board.insert(board.begin(),(unsigned int)horizontal_end-horizontal_start, "_");

    } else {
        if(lenWithHorizontal > horizontal_end) {
            board.insert(board.end(), ((unsigned int)lenWithHorizontal - (unsigned int)horizontal_end), "_");
            horizontal_end = lenWithHorizontal;
        }
        if(horizontal<horizontal_start) {
            board.insert(board.begin(), horizontal_start - horizontal, "_");
            this->horizontal_start = horizontal;
        }
        if(vertical < vertical_start) {
            vertical_start = vertical;
        }
        if(lenWithVertical > vertical_end) {
            this->vertical_end = lenWithVertical;
        }
    }
    for(auto ptr = board.begin(); ptr < board.end(); ptr++) {
        (*ptr).resize((unsigned int)vertical_end-vertical_start, '_');
    }
}

// postHorizontal function
void ariel::Board::postHorizontal(unsigned int horizontal, unsigned int vertical, const std::string& message) {
    board.at(horizontal-horizontal_start).replace(vertical-vertical_start,message.length(),message);
}

// postVertical function
void ariel::Board::postVertical(unsigned int horizontal, unsigned int vertical, std::string message) {
    for (unsigned int i = 0; i <message.length() ; ++i) {
        board.at(horizontal-horizontal_start+i).at(vertical-vertical_start)=message[i];
    }
}

// post function
void ariel::Board::post(unsigned int horizontal, unsigned int vertical, Direction d, const std::string &message){
    switch (d) {
        case Direction::Horizontal:
            update_bounderys(horizontal, vertical, d, message.length());
            postHorizontal(horizontal, vertical, message);
            break;
        case Direction::Vertical:
            update_bounderys(horizontal, vertical, d, message.length());
            postVertical(horizontal,vertical, message);
            break;
        default:
            throw std::out_of_range("invalid Direction type");
    }
}

// readHorizontal function
std::string ariel::Board::readHorizontal(unsigned int horizontal, unsigned int vertical, unsigned int len) {
    vector<string> str_from_board(1, "_");
    str_from_board.at(0).resize(len, '_');
    if(horizontal+1 > horizontal_end || horizontal < horizontal_start) {
        return str_from_board.at(0);
        }
    for(unsigned int i=0; i < len; ++i) {
        try {
            str_from_board.at(0).at(i)=board.at(horizontal-horizontal_start).at(vertical-vertical_start+i);
        } catch (const std::exception& e) {}
    }
    return str_from_board.at(0);
}

// readVertical function
std::string ariel::Board::readVertical(unsigned int horizontal, unsigned int vertical, unsigned int len) {
    vector<string> str_from_board(1,"_");
    str_from_board.at(0).resize(len,'_');
    if(vertical+1 > (int)vertical_end || vertical < vertical_start) {
        return str_from_board.at(0);
    }
    for(unsigned int i = 0; i < len && horizontal+i<horizontal_end; ++i) {
        try {
            str_from_board.at(0).at(i) = board.at(horizontal-horizontal_start + i).at(vertical-vertical_start);
        } catch (const std::exception& e) {

        }
    }
    return str_from_board.at(0);
}

// read function
std::string ariel::Board::read(unsigned int horizontal, unsigned int vertical, Direction d, unsigned int length) {
    switch(d) {
        case Direction::Horizontal:
            return readHorizontal(horizontal,vertical,length);
        case Direction::Vertical:
            return readVertical(horizontal,vertical,length);
        default:
            throw std::out_of_range("invalid Direction type");
    }
}

// show function
void ariel::Board::show() {
    for (auto & item : board) {
        std::cout << string(item) << endl;
    }
}