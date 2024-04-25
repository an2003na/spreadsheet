#include "Cell.h"

#include <sstream>

//default constructor
Cell::Cell() : val("") {}

//copy constructor
Cell::Cell(const Cell& rhv) :val(rhv.val) {}

//move constructor
Cell::Cell(Cell&& rhv) noexcept : val(std::move(rhv.val)) {}

//constructor for int value
Cell::Cell(int val) {
    std::ostringstream oss;
    oss << val;
    this->val = oss.str();
}

//constructor for double value
Cell::Cell(double val) {
    std::ostringstream oss;
    oss << val;
    this->val = oss.str();
}

//constructor for char value
Cell::Cell(char val) {
    this->val = val;
}

//constructor for bool value
Cell::Cell(bool val) {
    this->val = val ? "true" : "false";
}

//constructor for std::string value
Cell::Cell(std::string val) :val(val) {}

//constructor for std::vector<int> value
Cell::Cell(const std::vector<int>& val) {
    std::ostringstream oss;
    for(auto i : val) {
        oss << i <<" ";
    }
    this->val = oss.str();
}



//copy assignment operator
const Cell& Cell::operator=(const Cell& rhv) {
    if(this != &rhv) {
        val = rhv.val;
    }
    return *this;
}

//move assignment operator
const Cell& Cell::operator=(Cell&& rhv) {
    if(this != &rhv) {
        val = std::move(rhv.val);
    }
    return *this;
}

//assignment operators for different types
const Cell& Cell::operator=(int rhv) {
    std::ostringstream oss;
    oss << rhv;
    val = oss.str();
    return *this;
}

const Cell& Cell::operator=(double rhv) {
    std::ostringstream oss;
    oss << rhv;
    val = oss.str();
    return *this;
}

const Cell& Cell::operator=(char rhv) {
    val = rhv;
    return *this;
}

const Cell& Cell::operator=(bool rhv) {
    val = rhv ? "true" : "false";
    return *this;
}

const Cell& Cell::operator=(std::string rhv) {
    val = rhv;
    return *this;
}

const Cell& Cell::operator=(const std::vector<int>& rhv) {
    std::ostringstream oss;
    for(auto a : rhv) {
        oss << a << " ";
    }
    val = oss.str();
    return *this;
}

//conversion operators
Cell::operator int() {
    return std::stoi(val);
}

Cell::operator double() {
    return std::stod(val);
}

Cell::operator char() {
    return val[0];
}

Cell::operator bool() {
    return val == "true";
}

Cell::operator std::string() {
    return val;
}

Cell::operator std::vector<int>() {
    std::vector<int> vec;
    std::istringstream iss(val);
    int num{};
    while(iss >> num) {
        vec.push_back(num);
    }
    return vec;
}

//comparison operators

bool operator==(const Cell& lhv, const Cell& rhv) {
    return lhv.get_val() == rhv.get_val();
}

bool operator!=(const Cell& lhv, const Cell& rhv) {
    return lhv.get_val() != rhv.get_val();
}

//output operator
std::ostream& operator<<(std::ostream& out, const Cell& ob) {
    out << ob.get_val();
    return out;
}

std::istream& operator>>(std::istream& in, Cell& ob) {
    std::string v;
    in >> v;
    ob.set_val(v);
    return in;
}

// Add these functions to your Cell class definition in Cell.h or Cell.cpp

// Comparison operator for comparing a Cell object with an empty string
bool operator==(const Cell& lhv, const std::string& rhv) {
    return lhv.get_val() == rhv;
}

bool operator!=(const Cell& lhv, const std::string& rhv) {
    return !(lhv == rhv);
}



