
//------------------------INCLUDE------------------------//
#include <iostream>
#include <fstream>
#include <cmath>
//-----------------------NAMESPACE-----------------------//
using namespace std;

//------------------------DEFINE-------------------------//
#define input "input.txt"
#define output "output.txt"

//-------------------------ENUM-------------------------//
enum ErrorCode {ERROR = 1, FILE_ERROR = 2};

enum RootsType {NO_REAL_ROOTS, INFINITE_NUMBER_OF_ROOTS, REAL_ROOTS};

//------------------------STRUCT------------------------//
struct coefficients{
    double a, b, c;
};

struct roots{
    double x1, x2;
};

//-------------------ERROR--FUNCTIONS-------------------//
void error(){
    cerr<<"error\n";
    exit(ERROR);
}

void fileError(){
    cerr<<"File error\n";
    exit(FILE_ERROR);
}

//------------------------------------------------------//

double discriminant(const coefficients &c){
    return c.b * c.b - 4 * c.a * c.c;
}

coefficients read(){
    coefficients c = {-1, -1, -1};
    ifstream in(input);
    if (in.is_open()) in >> c.a >> c.b >> c.c;
    else fileError();
    in.close();
    return c;
}

void write(const RootsType state,const roots &r){
    ofstream out(output);
    if (!out.is_open()) fileError();
    switch (state) {
        case NO_REAL_ROOTS:
            out << "No real roots";
            break;
        case INFINITE_NUMBER_OF_ROOTS:
            out << "Infinite number of roots";
            break;
        case REAL_ROOTS:
            out << r.x1 << ' ' << r.x2;
            break;
        default:
            error();
            break;
    }
    out.close();
}

roots realRoots(const double discriminant,const coefficients &c,const RootsType r){
    if (r != REAL_ROOTS) return {-1, -1};
    roots roots = {-1, -1};
    roots.x1 = ((-1) * c.b - sqrt(discriminant)) / (2 * c.a);
    roots.x2 = ((-1) * c.b + sqrt(discriminant)) / (2 * c.a);
    return roots;
}

RootsType slove(const coefficients &c){
    if (c.a == 0 && c.b == 0 && c.c == 0) return INFINITE_NUMBER_OF_ROOTS;
    if (discriminant(c) < 0) return NO_REAL_ROOTS;
    return REAL_ROOTS;
}

int main() {
    const coefficients c = read();
    const coefficients &rc = c;
    const RootsType type = slove(rc);
    const roots r = realRoots(discriminant(rc), rc, type);
    const roots &rr = r;
    write(type, rr);
    return 0;
}
