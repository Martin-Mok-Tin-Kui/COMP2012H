/**
 * \file Cell.cpp
 *
 * An implementation of the Cell.hpp interface for a cons list data structure.
 * It supports the cons list ADT interface specified in cons.hpp.
 */

#include "Cell.hpp"

using namespace std;

//////////////////////////////////////////////////
/////////////////Class Cell///////////////////////
//////////////////////////////////////////////////
bool Cell::is_int() const {
  return false;
}

bool Cell::is_double() const {
  return false;
}

bool Cell::is_symbol() const {
  return false;
}

bool Cell::is_cons() const {
  return false;
}

bool Cell::is_nil() const {
  return false;
}

int Cell::get_int() const {
  cerr << "ERROR. Not IntCell." << endl;
  exit(1);
}

double Cell::get_double() const {
  cerr << "ERROR. Not DoubleCell." << endl;
  exit(1);
}

string Cell::get_symbol() const {
  cerr << "ERROR. Not SymbolCell." << endl;
  exit(1);
}

Cell* Cell::get_car() const {
  cerr << "ERROR. Not ConsCell." << endl;
  exit(1);
}

Cell* Cell::get_cdr() const {
  cerr << "ERROR. Not ConsCell." << endl;
  exit(1);
}

int Cell::len() const {
  return 0;
}

bool Cell::is_operator() const {
  return false;
}

Cell* Cell::eval_ceiling() const {
  cerr << "ERROR. TypeError: operator ceiling expects operands of type double." << endl;
  exit(1);
}

Cell* Cell::eval_floor() const {
  cerr << "ERROR. TypeError: operator floor expects operands of type double." << endl;
  exit(1);
}
//////////////////////////////////////////////////
///////////////Class NilCell//////////////////////
//////////////////////////////////////////////////
void NilCell::print(ostream& os) const {
  os << "()";
}

bool NilCell::is_nil() const {
  return true;
}

Cell* NilCell::eval() const {
  // there can be only one instance of nil, 
  // self-evaluation should return a copy.
  return nil;
}

bool NilCell::truth() const {
  return true;
}

Cell* NilCell::eval_addition(const Cell* addend) const {
  cerr << "ERROR. TypeError: operator of + cannot be nil." << endl;
  exit(1);
}

Cell* NilCell::eval_multi(const Cell* multiplier) const {
  cerr << "ERROR. TypeError: operator of * cannot be nil." << endl;
  exit(1);
}

Cell* NilCell::eval_divi(const Cell* dividend) const {
  cerr << "ERROR. TypeError: operator of / cannot be nil." << endl;
  exit(1);
}

Cell* NilCell::eval_subtra(const Cell* minuend) const {
  cerr << "ERROR. TypeError: operator of - cannot be nil." << endl;
  exit(1);
}

// only instance of NilCell, a dummy cell to represent nil in scheme.
Cell* const nil = new NilCell();
//////////////////////////////////////////////////
////////////////Class IntCell/////////////////////
//////////////////////////////////////////////////
IntCell::IntCell(int i): int_m(i) {}

void IntCell::print(ostream& os) const {
  os << int_m;
}

bool IntCell::is_int() const {
  return true;
}

int IntCell::get_int() const {
  return int_m;
}

Cell* IntCell::eval() const {
  return new IntCell(int_m);
}

bool IntCell::truth() const {
  if (int_m == 0) {
    return false;
  }
  else {
    return true;
  }
}

Cell* IntCell::eval_addition(const Cell* addend) const {
  if (addend->is_int()) {
    int sum = int_m + addend->get_int();
    delete addend;
    return new IntCell(sum);
  }
  else if (addend->is_double()) {
    double sum = int_m + addend->get_double();
    delete addend;
    return new DoubleCell(sum);
  }
}

Cell* IntCell::eval_multi(const Cell* multiplier) const {
  if (multiplier->is_int()) {
    int product = int_m * multiplier->get_int();
    delete multiplier;
    return new IntCell(product);
  }
  else if (multiplier->is_double()) {
    double product = int_m * multiplier->get_double();
    delete multiplier;
    return new DoubleCell(product);
  }
}

Cell* IntCell::eval_divi(const Cell* dividend) const {
  // raise a ZeroDivisionError, if the divisor is 0.
  if (int_m == 0) {
    cerr << "ERROR. ZeroDivisionError: divided by zero." << endl;
    exit(1);
  }
  if (dividend->is_int()) {
    int fraction = dividend->get_int() / int_m;
    delete dividend;
    return new IntCell(fraction);
  }
  else if (dividend->is_double()) {
    double fraction = dividend->get_double() / int_m;
    delete dividend;
    return new DoubleCell(fraction);
  }
}

Cell* IntCell::eval_subtra(const Cell* minuend) const {
  if (minuend->is_int()) {
    int diff = minuend->get_int() - int_m;
    delete minuend;
    return new IntCell(diff);
  }
  else if (minuend->is_double()) {
    double diff = minuend->get_double() - int_m;
    delete minuend;
    return new DoubleCell(diff);
  }
}
//////////////////////////////////////////////////
//////////////Class DoubleCell////////////////////
//////////////////////////////////////////////////
DoubleCell::DoubleCell(double d): double_m(d) {}

double DoubleCell::get_double() const {
  return double_m;
}

bool DoubleCell::is_double() const {
  return true;
}

void DoubleCell::print(ostream& os) const {
  os << setprecision(6) << showpoint << double_m;
}

Cell* DoubleCell::eval() const {
  return new DoubleCell(double_m);
}

bool DoubleCell::truth() const {
  if (double_m == 0) {
    return false;
  }
  else {
    return true;
  }
}

Cell* DoubleCell::eval_ceiling() const {
  int result = static_cast<int>(double_m);
  if (result < double_m) ++result;
  return new IntCell(result);
}

Cell* DoubleCell::eval_floor() const {
  int result = static_cast<int>(double_m);
  if (result > double_m) --result;
  return new IntCell(result);
}

Cell* DoubleCell::eval_addition(const Cell* addend) const {
  double sum = 0.0;
  if (addend->is_int()) {
    sum = double_m + addend->get_int();
  }
  else if (addend->is_double()) {
    sum = double_m + addend->get_double();
  }
  delete addend;
  return new DoubleCell(sum);
}

Cell* DoubleCell::eval_multi(const Cell* multiplier) const {
  double product = 1.0;
  if (multiplier->is_int()) {
    product = double_m * multiplier->get_int();
  }
  else if (multiplier->is_double()) {
    product = double_m * multiplier->get_double();
  }
  delete multiplier;
  return new DoubleCell(product);
}

Cell* DoubleCell::eval_divi(const Cell* dividend) const {
  // raise a ZeroDivisionError, if the divisor is 0.
  if (double_m == 0.0) {
    cerr << "ERROR. ZeroDivisionError: divided by zero." << endl;
    exit(1);    
  }
  double fraction = 1.0;
  if (dividend->is_int()) {
    fraction = dividend->get_int() / double_m;
  }
  else if (dividend->is_double()) {
    fraction = dividend->get_double() / double_m;
  }
  delete dividend;
  return new DoubleCell(fraction);
}

Cell* DoubleCell::eval_subtra(const Cell* minuend) const {
  double diff = 0.0;
  if (minuend->is_int()) {
    diff = minuend->get_int() - double_m;
  }
  else if (minuend->is_double()) {
    diff = minuend->get_double() - double_m;
  }
  delete minuend;
  return new DoubleCell(diff);
}

//////////////////////////////////////////////////
//////////////Class SymbolCell////////////////////
//////////////////////////////////////////////////
SymbolCell::SymbolCell(const char* const symbol) {
  char* cpy_str = new char[strlen(symbol) + 1];
  strcpy(cpy_str, symbol);
  symbol_m = cpy_str;
}

SymbolCell::~SymbolCell() {
  delete[] symbol_m;
}

bool SymbolCell::is_symbol() const {
  return true;
}

string SymbolCell::get_symbol() const {
  return symbol_m;
}

void SymbolCell::print(ostream& os) const {
  os << symbol_m;
}

bool SymbolCell::is_operator() const {
  string s = get_symbol();
  return (s == "+" || s == "if" || s == "ceiling" || s == "floor"
	  || s == "*" || s == "/" || s == "quote" || s == "-"
	  || s == "cons" || s == "car" || s == "cdr" || s == "nullp");
}

Cell* SymbolCell::eval() const {
  return new SymbolCell(symbol_m);
}

bool SymbolCell::truth() const {
  return true;
}

Cell* SymbolCell::eval_addition(const Cell* addend) const {
  cerr << "ERROR. TypeError: operator of + cannot be a symbol." << endl;
  exit(1);
}

Cell* SymbolCell::eval_multi(const Cell* multiplier) const {
  cerr << "ERROR. TypeError: operator of * cannot be a symbol." << endl;
  exit(1);
}

Cell* SymbolCell::eval_divi(const Cell* dividend) const {
  cerr << "ERROR. TypeError: operator of / cannot be a symbol." << endl;
  exit(1);
}

Cell* SymbolCell::eval_subtra(const Cell* minuend) const {
  cerr << "ERROR. TypeError: operator of - cannot be a symbol." << endl;
  exit(1);
}
//////////////////////////////////////////////////
////////////////Class ConsCell////////////////////
//////////////////////////////////////////////////
ConsCell::ConsCell(Cell* const my_car, Cell* const my_cdr): car(my_car), cdr(my_cdr) {}

ConsCell::~ConsCell() {
  if (car != nil) delete car;
  if (cdr != nil) delete cdr;
}

bool ConsCell::is_cons() const {
  return true;
}

Cell* ConsCell::get_car() const {
  return car;
}

Cell* ConsCell::get_cdr() const {
  return cdr;
}

void ConsCell::print(ostream& os) const {
  os << "(";
  const Cell* car_cell = get_car();
  const Cell* cdr_cell = get_cdr();
  car_cell->print(os);
  while (cdr_cell->is_cons()) {
    car_cell = cdr_cell->get_car();
    os << " ";
    car_cell->print(os);
    cdr_cell = cdr_cell->get_cdr();
  }
  if (cdr_cell != nil) {
    os << " . ";
    cdr_cell->print(os);
  }
  os << ")";
}

int ConsCell::len() const {
  int l = 0;
  const Cell* car_cell = get_car();
  const Cell* cdr_cell = get_cdr();
  ++l;
  while (cdr_cell->is_cons()) {
    car_cell = cdr_cell->get_car();
    ++l;
    cdr_cell = cdr_cell->get_cdr();
  }
  if (cdr_cell != nil) {
    cerr << "ERROR. Malformed list." << endl;
    exit(1);
  }
  return l;  
}

Cell* ConsCell::eval() const {
  Cell* copy_car = car;
  Cell* copy_cdr = cdr;
  if (car != nil) copy_car = car->eval();
  if (cdr != nil) copy_cdr = cdr->eval();
  return new ConsCell(copy_car, copy_cdr);
}

bool ConsCell::truth() const {
  return true;
}

Cell* ConsCell::eval_addition(const Cell* addend) const {
  cerr << "ERROR. TypeError: operator of + cannot be a list." << endl;
  exit(1);
}

Cell* ConsCell::eval_multi(const Cell* multiplier) const {
  cerr << "ERROR. TypeError: operator of * cannot be a list." << endl;
  exit(1);
}

Cell* ConsCell::eval_divi(const Cell* dividend) const {
  cerr << "ERROR. TypeError: operator of / cannot be a list." << endl;
  exit(1);
}

Cell* ConsCell::eval_subtra(const Cell* minuend) const {
  cerr << "ERROR. TypeError: operator of - cannot be a list." << endl;
  exit(1);
}
