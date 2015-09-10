/**
 * \mainpage COMP2012H Programming Assignment 1, Fall 2014
 *
 * \author YU Xinyuan
 * \author 20176934
 * \author xyuaj@ust.hk
 * \author LA1
 *
 * \date 24/9/2014
 *
 * Instructor: <a href="http://www.cs.ust.hk/~dekai/">Dekai Wu</a>
 * Due: 2014.09.26 at 23:00 by CASS
 */

/**
 * \file Cell.hpp
 *
 * Encapsulates the abstract interface for a concrete class-based
 * implementation of cells for a cons list data structure.
 */

#ifndef CELL_HPP
#define CELL_HPP

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>

#include <iomanip>

/**
 * \class Cell
 * \brief Class Cell
 */
class Cell {
public:

  /**
   * \brief Constructor to make int cell.
   */
  Cell(const int i);

  /**
   * \brief Constructor to make double cell.
   */
  Cell(const double d);

  /**
   * \brief Constructor to make symbol cell.
   */
  Cell(const char* const s);

  /**
   * \brief Constructor to make cons cell.
   */
  Cell(Cell* const my_car, Cell* const my_cdr);

  /**
   * \brief Special constructor to make the nil cell.
   */
  Cell();

  /**
   * \brief Destructor for a cell
   */
  ~Cell();

  /**
   * \brief Check if this is an int cell.
   * \return True iff this is an int cell.
   */
  bool is_int() const;

  /**
   * \brief Check if this is a double cell.
   * \return True iff this is a double cell.
   */
  bool is_double() const;

  /**
   * \brief Check if this is a symbol cell.
   * \return True iff this is a symbol cell.
   */
  bool is_symbol() const;

  /**
   * \brief Check if this is a cons cell.
   * \return True iff this is a cons cell.
   */
  bool is_cons() const;

  /**
   * \brief Check if this is a nil cell.
   * \return True iff this is a nil cell.
   */
  bool is_nil() const;

  /**
   * \brief Accessor (error if this is not an int cell).
   * \return The value in this int cell.
   */
  int get_int() const;

  /**
   * \brief Accessor (error if this is not a double cell).
   * \return The value in this double cell.
   */
  double get_double() const;

  /**
   * \brief Accessor (error if this is not a symbol cell).
   * \return The symbol name in this symbol cell.
   */
  std::string get_symbol() const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return First child cell.
   */
  Cell* get_car() const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return Rest child cell.
   */
  Cell* get_cdr() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  void print(std::ostream& os = std::cout) const;

  /**
   * \brief Print the error message to standard error and exit the program.
   * \param err_msg The error message to be printed, by default should be ERROR.
   */
  void raise_err(std::string err_msg="ERROR") const;

  /**
   * \brief Count elements in this tree
   * \return Numbers of elements in the tree. Return zero, if it's not a conspair. 
   */
  int len() const;

private:
  enum TypeTag {type_int, type_double, type_symbol, type_conspair, type_nil};
  struct ConsPair {
    Cell* car;
    Cell* cdr;
  };  
  TypeTag tag_m;
  union {
    int int_m;
    double double_m;
    char* symbol_m;
    ConsPair conspair_m;
  };
};

// Reminder: cons.hpp expects nil to be defined somewhere (for this
// implementation, Cell.cpp is the logical place to define it).
// Here we promise this again, just to be safe.
extern Cell* const nil;

#endif // CELL_HPP
