// includes
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <array>

// header files
#include "Board.hpp"
#include "Direction.hpp"

// namespaces
using namespace std;
using ariel::Direction;

// post function
void ariel::Board::post(unsigned int horizontal, unsigned int vertical, Direction dir, const string &message){
    switch(dir) {
        case Direction::Horizontal:
            update(horizontal, vertical, dir, message.length());
            board.at(horizontal-h_start).replace(vertical-v_start,message.length(),message);
            break;
        case Direction::Vertical:
            update(horizontal, vertical, dir, message.length());
            for(unsigned int i = 0; i < message.length() ; ++i) { board.at(horizontal-h_start+i).at(vertical-v_start) = message[i]; }
            break;
        default:
            throw out_of_range("invalid Direction type");
    }
}

// read function
string ariel::Board::read(unsigned int horizontal, unsigned int vertical, Direction d, unsigned int len) {
    vector<string> str_from_board(1, "_");
    switch(d) {
        case Direction::Horizontal:
            str_from_board.at(0).resize(len, '_');
            if(horizontal + 1 > h_end || horizontal < h_start) {
                return str_from_board.at(0);
                }
            for(unsigned int i = 0; i < len; ++i) {
                try {
                    str_from_board.at(0).at(i)=board.at(horizontal-h_start).at(vertical-v_start+i);
                } catch (const exception& e) {}
            }
            return str_from_board.at(0);
        case Direction::Vertical:
            str_from_board.at(0).resize(len, '_');
            if(vertical + 1 > (int)v_end || vertical < v_start) { return str_from_board.at(0); }
            for(unsigned int i = 0; i < len && horizontal + i < h_end; ++i) {
                try {
                    str_from_board.at(0).at(i) = board.at(horizontal-h_start + i).at(vertical-v_start);
                } catch (const exception& e) {

                }
            }
            return str_from_board.at(0);
        default:
            throw out_of_range("invalid Direction type");
    }
}

// update function
void ariel::Board::update(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int len) {
    int h_len = 0, v_len = 0;

    if(dir == Direction::Horizontal) {
        h_len = (int)horizontal + 1;
        v_len = (int)(len + vertical);
    } else if(dir == Direction::Vertical) {
        h_len = (int)(horizontal + len);
        v_len = 1 + (int)vertical;
    }

    if(this->h_start == INT32_MAX && this->h_end == -1 && this->v_start == INT32_MAX && this->v_end == -1) {
        this->h_start = horizontal;
        this->h_end = h_len;
        this->v_start = vertical;
        v_end = v_len;
        board.insert(board.begin(),(unsigned int)h_end-h_start, "_");
    } else {
        if(h_len > h_end) {
            board.insert(board.end(), ((unsigned int)h_len - (unsigned int)h_end), "_");
            h_end = h_len;
        }
        if(horizontal < h_start) {
            board.insert(board.begin(), h_start - horizontal, "_");
            this->h_start = horizontal;
        }
        if(vertical < v_start) {
            v_start = vertical;
        }
        if(v_len > v_end) {
            this->v_end = v_len;
        }
    }
    for(auto ptr = board.begin(); ptr < board.end(); ptr++) { (*ptr).resize((unsigned int)v_end-v_start, '_'); }
}

// show function
void ariel::Board::show() {
    for(auto & item : board) { cout << string(item) << endl; }
}
