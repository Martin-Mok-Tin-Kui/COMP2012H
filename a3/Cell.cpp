/**
 * \file Cell.cpp
 *
 * An implementation of the Cell.hpp interface for a cons list data structure.
 * It supports the cons list ADT interface specified in cons.hpp.
 */

#include "Cell.hpp"

using namespace std;

// Use map in STL, to store global variables.
map<string, Cell*> global_variables;

//////////////////////////////////////////////////
////////////Arithmetic Templates//////////////////
//////////////////////////////////////////////////
/// type_indicate is used to indicate the
/// type of T, in order to determine the 
/// return type of Cell.
template <typename T, char type_indicate>
Cell* add(T augend, const Cell* addend_cell) {
  if (addend_cell->is_int()) {
    int addend = addend_cell->get_int();
    delete addend_cell;
    if (type_indicate == 'd') {
      return new DoubleCell(augend + addend);
    }
    else {
      return new IntCell(augend + addend);
    }
  }
  else {
    double addend = addend_cell->get_double();
    delete addend_cell;
    return new DoubleCell(augend + addend);
  }
}

/// type_indicate is used to indicate the
/// type of T, in order to determine the 
/// return type of Cell.
template <typename T, char type_indicate>
Cell* mul(T multiplicand, const Cell* multiplier_cell) {
  if (multiplier_cell->is_int()) {
    int multiplier = multiplier_cell->get_int();
    delete multiplier_cell;
    if (type_indicate == 'd') {
      return new DoubleCell(multiplicand * multiplier);
    }
    else {
      return new IntCell(multiplicand * multiplier);
    }
  }
  else {
    double multiplier = multiplier_cell->get_double();
    delete multiplier_cell;
    return new DoubleCell(multiplicand * multiplier);
  }
}

/// type_indicate is used to indicate the
/// type of T, in order to determine the 
/// return type of Cell.
template <typename T, char type_indicate>
Cell* div(T divisor, const Cell* dividend_cell) {
  // raise a ZeroDivisionError, if the divisor is 0.
  if (!divisor) throw runtime_error("ZeroDivisionError, divided by zero.");
  if (dividend_cell->is_int()) {
    int dividend = dividend_cell->get_int();
    delete dividend_cell;
    if (type_indicate == 'd') {
      return new DoubleCell(dividend / divisor);
    }
    else {
      return new IntCell(dividend / divisor);
    }
  }
  else {
    double dividend = dividend_cell->get_double();
    delete dividend_cell;
    return new DoubleCell(dividend / divisor);
  }
}

/// type_indicate is used to indicate the
/// type of T, in order to determine the 
/// return type of Cell.
template <typename T, char type_indicate>
Cell* sub(T subtractor, const Cell* minuend_cell) {
  if (minuend_cell->is_int()) {
    int minuend = minuend_cell->get_int();
    delete minuend_cell;
    if (type_indicate == 'd') {
      return new DoubleCell(minuend - subtractor);
    }
    else {
      return new IntCell(minuend - subtractor);
    }
  }
  else {
    double minuend = minuend_cell->get_double();
    delete minuend_cell;
    return new DoubleCell(minuend - subtractor);
  }
}
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
  throw logic_error("calling get_int() on a non IntCell.");
}

double Cell::get_double() const {
  throw logic_error("calling get_double() on a non DoubleCell.");
}

string Cell::get_symbol() const {
  throw logic_error("calling get_symbol() on a non SymbolCell.");
}

Cell* Cell::get_car() const {
  throw logic_error("calling get_car() on a non ConsCell.");
}

Cell* Cell::get_cdr() const {
  throw logic_error("calling get_cdr() on a non ConsCell.");
}

int Cell::len() const {
  return 0;
}

bool Cell::is_operator() const {
  return false;
}

Cell* Cell::eval_ceiling() const {
  throw runtime_error("operator ceiling expects operands of type double.");
}

Cell* Cell::eval_floor() const {
  throw runtime_error("operator floor expects operands of type double.");
}

Cell* Cell::bound_value() const {
  throw logic_error("attempt the bound value on a non SymbolCell.");
}

void Cell::bind_to(Cell* const c) const {
  throw runtime_error("attempt to bind value to a non SymbolCell.");
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
  // self-evaluation should not return a copy.
  return nil;
}

bool NilCell::truth() const {
  return true;
}

Cell* NilCell::eval_addition(const Cell* addend) const {
  throw runtime_error("operand of + cannot be nil.");
}

Cell* NilCell::eval_multi(const Cell* multiplier) const {
  throw runtime_error("operand of * cannot be nil.");
}

Cell* NilCell::eval_divi(const Cell* dividend) const {
  throw runtime_error("operand of / cannot be nil.");
}

Cell* NilCell::eval_subtra(const Cell* minuend) const {
  throw runtime_error("operand of - cannot be nil.");
}

bool NilCell::less_than(const Cell* c) const {
  throw runtime_error("operand of < cannot be nil.");
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
  return add<int, 'i'>(int_m, addend);
}

Cell* IntCell::eval_multi(const Cell* multiplier) const {
  return mul<int, 'i'>(int_m, multiplier);
}

Cell* IntCell::eval_divi(const Cell* dividend) const {
  return div<int, 'i'>(int_m, dividend);
}

Cell* IntCell::eval_subtra(const Cell* minuend) const {
  return sub<int, 'i'>(int_m, minuend);
}

bool IntCell::less_than(const Cell* c) const {
  if (c->is_int()) {
    return int_m < c->get_int();
  }
  else if (c->is_double()) {
    return int_m < c->get_double();
  }
  else {
    c->less_than(nil);
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
  return add<double, 'd'>(double_m, addend);
}

Cell* DoubleCell::eval_multi(const Cell* multiplier) const {
  return mul<double, 'd'>(double_m, multiplier);
}

Cell* DoubleCell::eval_divi(const Cell* dividend) const {
  return div<double, 'd'>(double_m, dividend);
}

Cell* DoubleCell::eval_subtra(const Cell* minuend) const {
  return sub<double, 'd'>(double_m, minuend);
}

bool DoubleCell::less_than(const Cell* c) const {
  if (c->is_int()) {
    return double_m < c->get_int();
  }
  else if (c->is_double()) {
    return double_m < c->get_double();
  }
  else {
    c->less_than(nil);
  }
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
	  || s == "cons" || s == "car" || s == "cdr" || s == "nullp"
	  || s == "define" || s == "eval" || s == "print" || s == "<"
	  || s == "not");
}

Cell* SymbolCell::eval() const {
  return new SymbolCell(symbol_m);
}

bool SymbolCell::truth() const {
  return true;
}

Cell* SymbolCell::eval_addition(const Cell* addend) const {
  throw runtime_error("operand of + cannot be a symbol.");
}

Cell* SymbolCell::eval_multi(const Cell* multiplier) const {
  throw runtime_error("operand of * cannot be a symbol.");
}

Cell* SymbolCell::eval_divi(const Cell* dividend) const {
  throw runtime_error("operand of / cannot be a symbol.");
}

Cell* SymbolCell::eval_subtra(const Cell* minuend) const {
  throw runtime_error("operand of - cannot be a symbol.");
}

Cell* SymbolCell::bound_value() const {
  if (global_variables.count(get_symbol())) {
    return global_variables[get_symbol()]->eval();
  }
  else {
    throw runtime_error("undefined variable " + get_symbol());
  }
}

void SymbolCell::bind_to(Cell* const c) const {
  if (global_variables.count(get_symbol())) {
    throw runtime_error("cannot redefine symbol " + get_symbol());
  }
  else {
    global_variables[get_symbol()] = c;
  }
}

bool SymbolCell::less_than(const Cell* c) const {
  throw runtime_error("operand of < cannot be a symbol.");
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
    throw runtime_error("attempt length on a malformed list.");
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
  throw runtime_error("operand of + cannot be a list.");
}

Cell* ConsCell::eval_multi(const Cell* multiplier) const {
  throw runtime_error("operand of * cannot be a list.");
}

Cell* ConsCell::eval_divi(const Cell* dividend) const {
  throw runtime_error("operand of / cannot be a list.");
}

Cell* ConsCell::eval_subtra(const Cell* minuend) const {
  throw runtime_error("operand of - cannot be a list.");
}

bool ConsCell::less_than(const Cell* c) const {
  throw runtime_error("operand of < cannot be a list.");
}
