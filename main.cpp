
//------------------------INCLUDE------------------------//
#include <iostream>
#include <fstream>
#include <cmath>
//-----------------------NAMESPACE-----------------------//
using namespace std;

//------------------------DEFINE-------------------------//
#define ERROR 1
#define FILE_ERROR 2
#define NO_REAL_ROOTS 0
#define INFINITE_NUMBER_OF_ROOTS 1
#define REAL_ROOTS 2
#define input R"(C:\Users\Kurai\Desktop\0\C++\axb\input.txt)"
#define output R"(C:\Users\Kurai\Desktop\0\C++\axb\output.txt)"

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

double discriminant(coefficients c){
    return c.b * c.b - 4 * c.a * c.c;
}

coefficients read(){
    coefficients c = {-1, -1, -1};
    ifstream in(input);

    if (in.is_open()){
        in >> c.a >> c.b >> c.c;
    } else fileError();
    in.close();

    if (!in) fileError();
    return c;
}

void write(int state, roots r = {-1, -1}){
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
    if (!out) fileError();
}

roots realRoots(double discriminant, coefficients c){
    roots roots = {-1, -1};
    roots.x1 = ((-1) * c.b - sqrt(discriminant)) / (2 * c.a);
    roots.x2 = ((-1) * c.b + sqrt(discriminant)) / (2 * c.a);
    return roots;
}

void slove(coefficients c){
    if (c.a == 0 && c.b == 0 && c.c == 0){
        write(INFINITE_NUMBER_OF_ROOTS);
        return;
    }
    double d = discriminant(c);
    if (d < 0) {
        write(NO_REAL_ROOTS);
        return;
    }
   write(REAL_ROOTS, realRoots(d, c)); //Äâà äåéñòâèòåëüíûõ ðàçëè÷íûõ èëè êðàòíûõ êîðíÿ
}

int main() {
    slove(read());
    return 0;
}
