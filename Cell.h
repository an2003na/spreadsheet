#ifndef __CELL__H__
#define __CELL__H__

#include <iostream>
#include <vector>
#include <string>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob);


class Cell
{
private:
    std::string val;
public:
    Cell();
    Cell(const Cell& rhv);
    Cell(Cell&& rhv) noexcept;
    explicit Cell(int val);
    explicit Cell(double val);
    explicit Cell(char val);
    explicit Cell(bool val);
    explicit Cell(std::string val);
    explicit Cell(const std::vector<int>& val);

    const Cell& operator=(const Cell& rhv);  
    const Cell& operator=(Cell&& rhv);  
    const Cell& operator=(int rhv);  
    const Cell& operator=(double rhv);  
    const Cell& operator=(char rhv);  
    const Cell& operator=(bool rhv);  
    const Cell& operator=(std::string rhv);  
    const Cell& operator=(const std::vector<int>& rhv);

    operator int();  
    operator double();  
    operator char();  
    operator bool();  
    operator std::string();  
    operator std::vector<int>();  

    void set_val(std::string v) {val = v;}
    std::string get_val() const {return val;}
};

bool operator==(const Cell& lhv, const Cell& rhv);
bool operator!=(const Cell& lhv, const Cell& rhv);

bool operator==(const Cell& lhv, const std::string& rhv);
bool operator!=(const Cell& lhv, const std::string& rhv);


std::ostream& operator<<(std::ostream& out, const Cell& ob);
std::istream& operator>>(std::istream& in, Cell& ob);


#endif //__CELL__H__
