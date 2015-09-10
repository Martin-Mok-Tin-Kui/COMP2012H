/**
 * \file Cell.cpp
 *
 * An implementation of the Cell.hpp interface for a cons list data structure.
 * It supports the cons list ADT interface specified in cons.hpp.
 */

#include "Cell.hpp"

using namespace std;

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

bool Cell::is_procedure() const {
  return false;
}

bool Cell::is_primitive() const {
  return false;
}

int Cell::get_int() const {
  throw runtime_error("calling get_int() on a non IntCell.");
}

double Cell::get_double() const {
  throw runtime_error("calling get_double() on a non DoubleCell.");
}

string Cell::get_symbol() const {
  throw runtime_error("calling get_symbol() on a non SymbolCell.");
}

Cell* Cell::get_car() const {
  throw runtime_error("calling car on a non-list type: " + to_str());
}

Cell* Cell::get_cdr() const {
  throw runtime_error("calling cdr on a non-list type: " + to_str());
}

Cell* Cell::get_formals() const {
  throw runtime_error("calling get_formals() on a non ProcedureCell.");
}

Cell* Cell::get_body() const {
  throw runtime_error("calling get_body() on a non ProcedureCell.");
}

int Cell::len() const {
  throw runtime_error("attempt length on a non-list type.");
}

void Cell::print(ostream& os) const {
  os << this->to_str();
}

Cell* Cell::eval_ceiling() const {
  throw runtime_error("bad argument type for ceiling: " + to_str() + ". expect double.");
}

Cell* Cell::eval_floor() const {
  throw runtime_error("bad argument type for floor: " + to_str() + ". expect double.");
}

Cell* Cell::eval_addition(const Cell* addend) const {
  throw runtime_error("operand of + cannot be: " + to_str());
}


Cell* Cell::eval_multi(const Cell* multiplier) const {
  throw runtime_error("operand of * cannot be: " + to_str());
}

Cell* Cell::eval_divi(const Cell* dividend) const {
  throw runtime_error("operand of / cannot be: " + to_str());
}

Cell* Cell::eval_subtra(const Cell* minuend) const {
  throw runtime_error("operand of - cannot be: " + to_str());
}

bool Cell::less_than(const Cell* c) const {
  throw runtime_error("operand of < cannot be: " + to_str());
}

Cell* Cell::call(Cell* c) const {
  throw runtime_error("cannot apply non primitive func as primitive.");
}
//////////////////////////////////////////////////
///////////////Class NilCell//////////////////////
//////////////////////////////////////////////////
string NilCell::to_str() const {
  return string("()");
}

bool NilCell::is_nil() const {
  return true;
}

int NilCell::len() const {
  return 0;
}

Cell* NilCell::copy() const {
  // there can be only one instance of nil, 
  // self-evaluation should not return a copy.
  return nil;
}

bool NilCell::truth() const {
  return true;
}

// only instance of NilCell, a dummy cell to represent nil in scheme.
Cell* const nil = new NilCell();
//////////////////////////////////////////////////
////////////////Class IntCell/////////////////////
//////////////////////////////////////////////////
IntCell::IntCell(int i): int_m(i) {}

string IntCell::to_str() const {
  stringstream ss;
  ss << int_m;
  return ss.str();
}

bool IntCell::is_int() const {
  return true;
}

int IntCell::get_int() const {
  return int_m;
}

Cell* IntCell::copy() const {
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

string DoubleCell::to_str() const {
  stringstream ss;
  ss << setprecision(6) << showpoint << double_m;
  return ss.str();
}

Cell* DoubleCell::copy() const {
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

string SymbolCell::to_str() const {
  stringstream ss;
  ss << symbol_m;
  return ss.str();
}

Cell* SymbolCell::copy() const {
  return new SymbolCell(symbol_m);
}

bool SymbolCell::truth() const {
  return true;
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

string ConsCell::to_str() const {
  stringstream ss;
  ss << "(";
  const Cell* car_cell = get_car();
  const Cell* cdr_cell = get_cdr();
  ss << car_cell->to_str();
  while (cdr_cell->is_cons()) {
    car_cell = cdr_cell->get_car();
    ss << " ";
    ss << car_cell->to_str();
    cdr_cell = cdr_cell->get_cdr();
  }
  if (cdr_cell != nil) {
    ss << " . ";
    ss << cdr_cell->to_str();
  }
  ss << ")";
  return ss.str();
}

int ConsCell::len() const {
  int l = 0;
  const Cell* cdr_cell = get_cdr();
  ++l;
  while (cdr_cell->is_cons()) {
    ++l;
    cdr_cell = cdr_cell->get_cdr();
  }
  if (cdr_cell != nil) {
    throw runtime_error("malformed expression " + to_str());
  }
  return l;  
}

Cell* ConsCell::copy() const {
  Cell* copy_car = car;
  Cell* copy_cdr = cdr;
  if (car != nil) copy_car = car->copy();
  if (cdr != nil) copy_cdr = cdr->copy();
  return new ConsCell(copy_car, copy_cdr);
}

bool ConsCell::truth() const {
  return true;
}
//////////////////////////////////////////////////
/////////////Class ProcedureCell//////////////////
//////////////////////////////////////////////////
ProcedureCell::ProcedureCell(Cell* my_formals, Cell* my_body):
  formals(my_formals), body(my_body) {}

ProcedureCell::~ProcedureCell() {
  if (formals != nil) delete formals;
  if (body != nil) delete body;
}

bool ProcedureCell::is_procedure() const {
  return true;
}

Cell* ProcedureCell::get_formals() const {
  return formals;
}

Cell* ProcedureCell::get_body() const {
  return body;
}

string ProcedureCell::to_str() const {
  return string("#<function>");
}

Cell* ProcedureCell::copy() const {
  Cell* copy_formals = formals;
  Cell* copy_body = body;
  if (formals != nil) copy_formals = formals->copy();
  if (body != nil) copy_body = body->copy();
  return new ProcedureCell(copy_formals, copy_body);  
}

bool ProcedureCell::truth() const {
  return true;
}
//////////////////////////////////////////////////
/////////////Class PrimitiveCell//////////////////
//////////////////////////////////////////////////
PrimitiveCell::PrimitiveCell(Cell *(*f)(Cell*)):
  primitive_func(f) {}

bool PrimitiveCell::is_primitive() const {
  return true;
}

string PrimitiveCell::to_str() const {
  return string("#<primitive function>");
}

Cell* PrimitiveCell::copy() const {
  return new PrimitiveCell(primitive_func);
}

bool PrimitiveCell::truth() const {
  return true;
}

Cell* PrimitiveCell::call(Cell* c) const {
  return primitive_func(c);
}
