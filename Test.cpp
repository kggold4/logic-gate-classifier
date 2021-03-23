// includes
#include <string>
#include <experimental/random>
#include "doctest.h"
#include "Board.hpp"
#include "Direction.hpp"

// namespaces
using namespace std;
using namespace ariel;

// constants
const int RANDOM_BOUNDERY = 100;

// represent a length 5 of a word
const int WORD_LEN_5 = 5;

// represent a length 12 of a word
const int WORD_LEN_12 = 12;

// function that return a random string in given length
std::string gen_random(size_t length) {
    auto randchar = []() -> char {
        const string charset =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (charset.size() - 1);
        return charset.at((unsigned int)rand() % max_index);
    };
    std::string str(length,0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

TEST_CASE("posting string horizontaly and reading it") {
    Board board;
    string str = gen_random(WORD_LEN_5);
    board.post(0, 0, Direction::Horizontal, str);
    CHECK(board.read(0, 0, Direction::Horizontal, WORD_LEN_5) == str);
}

TEST_CASE("posting string horizontal and reading verticlly") {
    Board board;
    string str = gen_random(WORD_LEN_5);
    board.post(2, 0, Direction::Horizontal, str);
    string new_str = "__" + str.substr(0,1) + "__";
    CHECK(board.read(0, 0, Direction::Vertical, WORD_LEN_5) == new_str);
}

TEST_CASE("posting string vertical and reading horizontally"){
    Board board;
    string str = gen_random(WORD_LEN_5);
    board.post(0, 2, Direction::Vertical, str);
    string new_str = "__" + str.substr(0,1) + "__";
    CHECK(board.read(0, 0, Direction::Horizontal, WORD_LEN_5) == new_str);
}

TEST_CASE("reading from empty board"){
    Board board;
    unsigned int row = (unsigned int)std::experimental::randint(0, RANDOM_BOUNDERY);
    unsigned int col = (unsigned int)std::experimental::randint(0, RANDOM_BOUNDERY);
    CHECK(board.read(row, col,Direction::Horizontal, WORD_LEN_5) == string("_____"));
    CHECK(board.read(row, col,Direction::Vertical, WORD_LEN_5) == string("_____"));
}

TEST_CASE("posting string to empty board vertical"){
    Board board;
    string str = gen_random(WORD_LEN_5);
    board.post(0, 0, Direction::Vertical, str);
    CHECK(board.read(0, 0, Direction::Vertical, WORD_LEN_5) == str);
}

TEST_CASE("overwriting existing message horizontal and read it") {
    Board board;
    string str = gen_random(WORD_LEN_5);
    board.post(0, 0, Direction::Horizontal, str);
    str = gen_random(WORD_LEN_5);
    board.post(0, 0, Direction::Horizontal, str);
    CHECK(board.read(0, 0, Direction::Horizontal, WORD_LEN_5) == str);
}

TEST_CASE("overwriting existing message vertical"){
    Board board;
    string str = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Vertical,str);
    str = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Vertical,str);
    CHECK(board.read(0,0,Direction::Vertical,WORD_LEN_5)==str);
}

TEST_CASE("overwriting existing message with longer message vertical"){
    Board board;
    string str = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Vertical,str);
    str = gen_random(WORD_LEN_12);
    board.post(0,0,Direction::Vertical,str);
    CHECK(board.read(0,0,Direction::Vertical,WORD_LEN_12)==str);
}

TEST_CASE("overwriting existing message with longer message horizontal"){
    Board board;
    string str = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Horizontal,str);
    str = gen_random(WORD_LEN_12);
    board.post(0,0,Direction::Horizontal,str);
    CHECK(board.read(0,0,Direction::Horizontal,WORD_LEN_12)==str);
}

TEST_CASE("overwriting existing message with shorter message horizontal"){
    Board board;
    string str = gen_random(WORD_LEN_12);
    board.post(0,0,Direction::Horizontal,str);
    string str2 = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Horizontal,str2);
    str.replace(0,str2.length(),str2);
    CHECK(board.read(0,0,Direction::Horizontal,WORD_LEN_12)==str);
}

TEST_CASE("overwriting existing message with shorter message vertical"){
    Board board;
    string str = gen_random(WORD_LEN_12);
    board.post(0,0,Direction::Vertical,str);
    string str2 = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Vertical,str2);
    str.replace(0,str2.length(),str2);
    CHECK(board.read(0,0,Direction::Vertical,WORD_LEN_12)==str);
}

TEST_CASE("add 2 messages same direction different length and rows"){
    Board board;
    string long_str = gen_random(WORD_LEN_12);
    string short_str = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Horizontal,short_str);
    board.post(1,0,Direction::Horizontal,long_str);
    CHECK(board.read(1,0,Direction::Horizontal,12)==long_str);
    CHECK(board.read(0,0,Direction::Horizontal,12)==short_str+"_______");
}

TEST_CASE("add 2 messages same direction different length and columns"){
    Board board;
    string long_str = gen_random(WORD_LEN_12);
    string short_str = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Vertical,short_str);
    board.post(0,1,Direction::Vertical,long_str);
    CHECK(board.read(0,0,Direction::Vertical,12)==short_str+"_______");
    CHECK(board.read(0,1,Direction::Vertical,12)==long_str);
}

TEST_CASE("add 2 messages different directions"){
    Board board;
    string long_str = gen_random(WORD_LEN_12);
    string short_str = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Horizontal,short_str);
    board.post(0,0,Direction::Vertical,long_str);
    CHECK(board.read(0,0,Direction::Vertical,12)==long_str);
    CHECK(board.read(0,0,Direction::Horizontal,5)==long_str.at(0)+short_str.substr(1,4));
}

TEST_CASE("add 2 messages different directions and distanced locations"){
    Board board;
    const int row = 90;
    const int col=9;
    string long_str = gen_random(WORD_LEN_12);
    string short_str = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Horizontal,short_str);
    board.post(row,col,Direction::Vertical,long_str);
    CHECK(board.read(row,col,Direction::Vertical,12)==long_str);
    CHECK(board.read(0,0,Direction::Horizontal,5)==short_str);
}

TEST_CASE("add messages to random location vertical"){
    Board board;
    unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    string short_str = gen_random(WORD_LEN_5);
    board.post(row,col,Direction::Vertical,short_str);
    CHECK(board.read(row,col,Direction::Vertical,WORD_LEN_5)==short_str);
}

TEST_CASE("add messages to random location horizontal"){
    Board board;
    unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    string short_str = gen_random(WORD_LEN_5);
    short_str = gen_random(WORD_LEN_5);
    board.post(row,col,Direction::Horizontal,short_str);
    CHECK(board.read(row,col,Direction::Horizontal,WORD_LEN_5)==short_str);
}

TEST_CASE("after adding mwssage check if empty cells horizontal") {
    Board board;
    unsigned int row = (unsigned int) std::experimental::randint(0, RANDOM_BOUNDERY);
    unsigned int col = (unsigned int) std::experimental::randint(0, RANDOM_BOUNDERY);
    string short_str = gen_random(WORD_LEN_5);
    short_str = gen_random(WORD_LEN_5);
    board.post(row, col, Direction::Horizontal, short_str);
            CHECK(board.read(row + WORD_LEN_5, col, Direction::Horizontal, WORD_LEN_5) == "_____");
            CHECK(board.read(row, col + WORD_LEN_5, Direction::Horizontal, WORD_LEN_5) == "_____");
}

TEST_CASE("after adding mwssage check if empty cells vertical"){
    Board board;
    unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    string short_str = gen_random(WORD_LEN_5);
    board.post(row,col,Direction::Vertical,short_str);
    CHECK(board.read(row+WORD_LEN_5,col,Direction::Vertical,WORD_LEN_5)=="_____");
    CHECK(board.read(row,col+WORD_LEN_5,Direction::Vertical,WORD_LEN_5)=="_____");
}

TEST_CASE("read with word length of zero"){
    Board board;
    string short_str = gen_random(WORD_LEN_5);
    board.post(0,0,Direction::Vertical,short_str);
    unsigned int row = (unsigned int)std::experimental::randint(WORD_LEN_5,RANDOM_BOUNDERY);
    unsigned int col = (unsigned int)std::experimental::randint(WORD_LEN_5,RANDOM_BOUNDERY);
    CHECK(board.read(row,col,Direction::Vertical,0)=="");
}
