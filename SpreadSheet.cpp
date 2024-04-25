#include "SpreadSheet.h"

// SpreadSheet Class Implementation

// Default constructor
SpreadSheet::SpreadSheet() : rowcnt(0), colcnt(0), board(nullptr) {}

// Copy constructor
SpreadSheet::SpreadSheet(const SpreadSheet& rhv) : rowcnt(rhv.rowcnt), colcnt(rhv.colcnt) {
    // Allocate memory for the board
    board = new Cell*[rowcnt];
    for (size_t i = 0; i < rowcnt; ++i) {
        board[i] = new Cell[colcnt];
        // Copy cell values from rhv to *this
        for (size_t j = 0; j < colcnt; ++j) {
            board[i][j] = rhv.board[i][j];
        }
    }
}

// Move constructor
SpreadSheet::SpreadSheet(SpreadSheet&& rhv) noexcept : rowcnt(rhv.rowcnt), colcnt(rhv.colcnt), board(rhv.board) {
    rhv.rowcnt = 0;
    rhv.colcnt = 0;
    rhv.board = nullptr;
}

// Constructor to create a square spreadsheet with a specified size
SpreadSheet::SpreadSheet(size_t size) : SpreadSheet(size, size) {}

// Constructor to create a spreadsheet with specified rows and columns
SpreadSheet::SpreadSheet(size_t row, size_t col) : rowcnt(row), colcnt(col) {
    // Allocate memory for the board
    board = new Cell*[rowcnt];
    for (size_t i = 0; i < rowcnt; ++i) {
        board[i] = new Cell[colcnt];
    }
}

// Destructor
SpreadSheet::~SpreadSheet() {
    // Deallocate memory for the board
    if (board != nullptr) {
        for (size_t i = 0; i < rowcnt; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }
}

// Copy assignment operator
const SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv) {
    if (this != &rhv) {
        // Deallocate memory for current board
        if (board != nullptr) {
            for (size_t i = 0; i < rowcnt; ++i) {
                delete[] board[i];
            }
            delete[] board;
        }
        
        // Copy data from rhv
        rowcnt = rhv.rowcnt;
        colcnt = rhv.colcnt;
        // Allocate memory for the board
        board = new Cell*[rowcnt];
        for (size_t i = 0; i < rowcnt; ++i) {
            board[i] = new Cell[colcnt];
            // Copy cell values from rhv to *this
            for (size_t j = 0; j < colcnt; ++j) {
                board[i][j] = rhv.board[i][j];
            }
        }
    }
    return *this;
}

// Move assignment operator
const SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv) {
    if (this != &rhv) {
        // Deallocate memory for current board
        if (board != nullptr) {
            for (size_t i = 0; i < rowcnt; ++i) {
                delete[] board[i];
            }
            delete[] board;
        }
        
        // Move data from rhv
        rowcnt = rhv.rowcnt;
        colcnt = rhv.colcnt;
        board = rhv.board;
        
        // Reset rhv
        rhv.rowcnt = 0;
        rhv.colcnt = 0;
        rhv.board = nullptr;
    }
    return *this;
}

// Subscript operator for non-const access to columns
SpreadSheet::Column SpreadSheet::operator[](size_t pos) {
    if (pos >= colcnt) {
        throw std::out_of_range("Column index out of range");
    }
    return Column(board[pos]);
}

// Subscript operator for const access to columns
const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const {
    if (pos >= colcnt) {
        throw std::out_of_range("Column index out of range");
    }
    return Column(board[pos]);
}

// Clear the spreadsheet
void SpreadSheet::clear() noexcept {
    // Clear all cells in the spreadsheet
    for (size_t i = 0; i < rowcnt; ++i) {
        for (size_t j = 0; j < colcnt; ++j) {
            board[i][j] = Cell(); // Assuming Cell() creates an empty cell
        }
    }
}


// Get the number of rows in the spreadsheet
size_t SpreadSheet::row() const {
    return rowcnt;
}

// Get the number of columns in the spreadsheet
size_t SpreadSheet::col() const {
    return colcnt;
}

// Mirror the spreadsheet horizontally
void SpreadSheet::mirrorH() {
    // Swap elements across the vertical axis
    for (size_t i = 0; i < rowcnt; ++i) {
        for (size_t j = 0; j < colcnt / 2; ++j) {
            std::swap(board[i][j], board[i][colcnt - j - 1]);
        }
    }
}

// Mirror the spreadsheet vertically
void SpreadSheet::mirrorV() {
    // Swap elements across the horizontal axis
    for (size_t i = 0; i < rowcnt / 2; ++i) {
        for (size_t j = 0; j < colcnt; ++j) {
            std::swap(board[i][j], board[rowcnt - i - 1][j]);
        }
    }
}

// Mirror the spreadsheet along the main diagonal
void SpreadSheet::mirrorD() {
    // Transpose the matrix
    for (size_t i = 0; i < rowcnt; ++i) {
        for (size_t j = i + 1; j < colcnt; ++j) {
            std::swap(board[i][j], board[j][i]);
        }
    }
}

// Mirror the spreadsheet along the secondary diagonal
void SpreadSheet::mirrorSD() {
    // Rotate the matrix 180 degrees
    rotate(2);
}

// Rotate the spreadsheet by a certain counterclockwise angle
void SpreadSheet::rotate(int cnt) {
    cnt %= 4;
    if (cnt < 0) cnt += 4;
    for (int k = 0; k < cnt; ++k) {
        // Transpose the matrix
        for (size_t i = 0; i < rowcnt; ++i) {
            for (size_t j = i + 1; j < colcnt; ++j) {
                std::swap(board[i][j], board[j][i]);
            }
        }
        // Reverse each row
        for (size_t i = 0; i < rowcnt; ++i) {
            for (size_t j = 0; j < colcnt / 2; ++j) {
                std::swap(board[i][j], board[i][colcnt - j - 1]);
            }
        }
    }
}

// Remove a specific row from the spreadsheet
void SpreadSheet::removeRow(size_t row) {
    if (row >= rowcnt) {
        throw std::out_of_range("Row index out of range");
    }
    // Move the rows above the deleted row down by one
    for (size_t i = row; i < rowcnt - 1; ++i) {
        for (size_t j = 0; j < colcnt; ++j) {
            board[i][j] = board[i + 1][j];
        }
    }
    // Deallocate memory for the last row
    delete[] board[rowcnt - 1];
    // Update the row count
    --rowcnt;
}

// Remove multiple rows specified by an initializer list
void SpreadSheet::removeRows(std::initializer_list<size_t> rows) {
    for (auto row : rows) {
        removeRow(row);
    }
}

// Remove a specific column from the spreadsheet
void SpreadSheet::removeCol(size_t col) {
    if (col >= colcnt) {
        throw std::out_of_range("Column index out of range");
    }
    // Move the columns to the right of the deleted column left by one
    for (size_t i = 0; i < rowcnt; ++i) {
        for (size_t j = col; j < colcnt - 1; ++j) {
            board[i][j] = board[i][j + 1];
        }
    }
    // Update the column count
    --colcnt;
}

// Remove multiple columns specified by an initializer list
void SpreadSheet::removeCols(std::initializer_list<size_t> cols) {
    for (auto col : cols) {
        removeCol(col);
    }
}

// Resize the number of rows in the spreadsheet
void SpreadSheet::resizeRow(size_t r) {
    if (r == rowcnt) return; // No change in size
    if (r < rowcnt) {
        // Remove excess rows
        for (size_t i = r; i < rowcnt; ++i) {
            delete[] board[i];
        }
        rowcnt = r;
    } else {
        // Add new rows
        Cell** newBoard = new Cell*[r];
        for (size_t i = 0; i < rowcnt; ++i) {
            newBoard[i] = board[i];
        }
        for (size_t i = rowcnt; i < r; ++i) {
            newBoard[i] = new Cell[colcnt];
        }
        delete[] board;
        board = newBoard;
        rowcnt = r;
    }
}

// Resize the number of columns in the spreadsheet
void SpreadSheet::resizeCol(size_t c) {
    if (c == colcnt) return; // No change in size
    if (c < colcnt) {
        // Remove excess columns
        for (size_t i = 0; i < rowcnt; ++i) {
            Cell* newRow = new Cell[c];
            for (size_t j = 0; j < c; ++j) {
                newRow[j] = board[i][j];
            }
            delete[] board[i];
            board[i] = newRow;
        }
        colcnt = c;
    } else {
        // Add new columns
        for (size_t i = 0; i < rowcnt; ++i) {
            Cell* newRow = new Cell[c];
            for (size_t j = 0; j < colcnt; ++j) {
                newRow[j] = board[i][j];
            }
            for (size_t j = colcnt; j < c; ++j) {
                newRow[j] = Cell(); // Initialize new cells with default constructor
            }
            delete[] board[i];
            board[i] = newRow;
        }
        colcnt = c;
    }
}

// Resize the spreadsheet to the specified number of rows and columns
void SpreadSheet::resize(size_t r, size_t c) {
    resizeRow(r);
    resizeCol(c);
}

// Extract a slice of the spreadsheet based on specified rows and columns
SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols) {
    size_t r = rows.size();
    size_t c = cols.size();
    SpreadSheet slicedSheet(r, c);
    size_t i = 0;
    for (auto row : rows) {
        size_t j = 0;
        for (auto col : cols) {
            slicedSheet.board[i][j] = board[row][col];
            ++j;
        }
        ++i;
    }
    return slicedSheet;
}

// Column Class Implementation

// Constructor to initialize the column with a pointer to the first cell
SpreadSheet::Column::Column(Cell* col) : col(col) {}

// Subscript operator for non-const access to cells within the column
Cell& SpreadSheet::Column::operator[](size_t pos) {
    return col[pos];
}

// Subscript operator for const access to cells within the column
const Cell& SpreadSheet::Column::operator[](size_t pos) const {
    return col[pos];
}

// Comparison operators for SpreadSheet objects
bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv) {
    if (lhv.row() != rhv.row() || lhv.col() != rhv.col()) {
        return false;
    }
    for (size_t i = 0; i < lhv.row(); ++i) {
        for (size_t j = 0; j < lhv.col(); ++j) {
            if (lhv[i][j] != rhv[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv) {
    return !(lhv == rhv);
}

// Output operator for SpreadSheet objects
std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob) {
    for (size_t i = 0; i < ob.row(); ++i) {
        for (size_t j = 0; j < ob.col(); ++j) {
            out << std::setw(8) << ob[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

