/**
 * \file Cell.cpp
 *
 * An implementation of the Cell.hpp interface for a cons list data structure.
 * It supports the cons list ADT interface specified in cons.hpp. Use a pair
 * to store the first and second element for a cons list while use a tagged
 * union to track the data type store in a cell.
 */

#include "Cell.hpp"

using namespace std;

Cell::Cell(const int i) {
  tag_m = type_int;
  int_m = i;
}

Cell::Cell(const double d) {
  tag_m = type_double;
  double_m = d;
}

Cell::Cell(const char* const s) {
  tag_m = type_symbol;
  char* cpy_str = new char[strlen(s) + 1];
  strcpy(cpy_str, s);
  symbol_m = cpy_str;
}

Cell::Cell(Cell* const my_car, Cell* const my_cdr) {
  tag_m = type_conspair;
  conspair_m.car = my_car;
  conspair_m.cdr = my_cdr;
}

Cell::Cell() {
  tag_m = type_nil;
}

Cell::~Cell() {
  if (is_cons()) {
    if (!conspair_m.car->is_nil()) {
      delete conspair_m.car;
    }
    if (!conspair_m.cdr->is_nil()) {
      delete conspair_m.cdr;
    }
  }
  if (is_symbol()) {
    delete[] symbol_m;
  }
}

bool Cell::is_int() const {
  return (tag_m == type_int);
}

bool Cell::is_double() const {
  return (tag_m == type_double);
}

bool Cell::is_symbol() const {
  return (tag_m == type_symbol);
}

bool Cell::is_cons() const {
  return (tag_m == type_conspair);
}

bool Cell::is_nil() const {
  return (tag_m == type_nil);
}

void Cell::raise_err(string err_msg) const {
  cerr << err_msg << endl;
  exit(1);
}

int Cell::get_int() const {
  if (is_int()) {
    return int_m;
  }
  else {
    raise_err();
  }
}

double Cell::get_double() const {
  if (is_double()) {
    return double_m;
  }
  else {
    raise_err();
  }
}

string Cell::get_symbol() const {
  if (is_symbol()) {
    return symbol_m;
  }
  else {
    raise_err();
  }
}

Cell* Cell::get_car() const {
  if (is_cons()) {
    return conspair_m.car;
  }
  else {
    raise_err();
  }
}

Cell* Cell::get_cdr() const {
  if (is_cons()) {
    return conspair_m.cdr;
  }
  else {
    raise_err();
  }
}

int Cell::len() const {
  int l = 0;
  if (is_cons()) {
    const Cell* car_cell = get_car();
    const Cell* cdr_cell = get_cdr();
    if (!car_cell->is_nil()) {++l;}
    while (cdr_cell->is_cons()) {
      car_cell = cdr_cell->get_car();
      if (!car_cell->is_nil()) {++l;}
      cdr_cell = cdr_cell->get_cdr();
    }
    if (!cdr_cell->is_nil()) {++l;}
  }
  return l;
}

void Cell::print(ostream& os) const {
  if (is_nil()) {os << "()";}
  else if (is_int()) {os << int_m;}
  else if (is_double()) {os << setprecision(6) << showpoint << double_m;}
  else if (is_symbol()) {os << symbol_m;}
  else if (is_cons()) {
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
    if (!cdr_cell->is_nil()) {
      os << " . ";
      cdr_cell->print(os);
    }
    os << ")";
  }
}

// Reminder: cons.hpp expects nil to be defined somewhere.  For this
// implementation, this is the logical place to define it.

Cell* const nil = new Cell();

