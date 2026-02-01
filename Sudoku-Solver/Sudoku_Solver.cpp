#include<iostream>
#include<vector>
using namespace std;

class SudokuBoard{
private:
    vector<vector<char>> &board;
public:
    SudokuBoard(vector<vector<char>> &b) : board(b) {}

    char get(int row, int col){
        return board[row][col];
    }
    void set(int row, int col, char value){
        board[row][col] = value;
    }

    bool isEmpty(int row, int col) const {
        return board[row][col] == '.';
    }
};

class ISudokuValidator{
public:
    virtual bool isvalid(SudokuBoard &board, int row, int col, char digit) = 0;
    virtual ~ISudokuValidator() = default;
};

class ClassicSudokuValidator : public ISudokuValidator{
public:
    bool isvalid(SudokuBoard &board, int row, int col, char digit) override {

        for(int i=0; i<9; i++){
            if(board.get(row, i) == digit) return false;
            if(board.get(i, col) == digit) return false;
        }

        int strow = (row /3) * 3;
        int stcol = (col /3) * 3;

        for(int i=strow; i<strow + 3; i++){
            for(int j=stcol; j<stcol + 3; j++){
                if(board.get(i, j) == digit) return false;
            }
        }

        return true;
    }
};

class SudokuSolver{
private:
    ISudokuValidator* validator;
public:
    SudokuSolver(ISudokuValidator* v) : validator(v) {}

    bool solve(SudokuBoard &board, int row, int col){
        if(row == 9) return true;

        int nextrow = (col == 8) ? row+1 : row;
        int nextcol = (col + 1) % 9;

        if(!board.isEmpty(row, col)){
            return solve(board, nextrow, nextcol);
        }

        for(char digit = '1'; digit <= '9'; digit++){
            if(validator->isvalid(board, row, col, digit)){
                board.set(row, col, digit);
                if(solve(board, nextrow, nextcol)) return true;
                board.set(row, col, '.');
            }
        }
        return false;
    }
};

class Solution{
public:
    void SolveSudoku(vector<vector<char>> &board){
        SudokuBoard sudokuBoard(board);
        ClassicSudokuValidator validator;
        SudokuSolver solver(&validator);
        solver.solve(sudokuBoard, 0, 0);
    }
};

int main(){
    Solution s;
    vector<vector<char>> board = {{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
    s.SolveSudoku(board);

    for (auto &row : board) {
        for (char c : row)
            cout << c << " ";
        cout << endl;
    }
    
    return 0;
}