/**
 * \mainpage COMP2012H Programming Assignment 3, Fall 2014
 *
 * \author YU Xinyuan
 * \author 20176934
 * \author xyuaj@ust.hk
 * \author LA1
 *
 * \date   17/10/2014
 *
 * Instructor: <a href="http://www.cs.ust.hk/~dekai/">Dekai Wu</a>
 * Due: 2014.10.24 at 23:00 by CASS
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
#include <stdexcept>
#include <map>

/**
 * \class Cell
 * \brief Abstract base class Cell
 */
class Cell {
public:
  
  /**
   * \brief Default constructor.
   */
  Cell() {}

  /**
   * \brief Virtual destructor.
   */
  virtual ~Cell() {}

  /**
   * \brief Check if this is an IntCell.
   * \return True iff this is an IntCell.
   */
  virtual bool is_int() const;

  /**
   * \brief Check if this is a DoubleCell.
   * \return True iff this is a DoubleCell.
   */
  virtual bool is_double() const;

  /**
   * \brief Check if this is a SymbolCell.
   * \return True iff this is a SymbolCell.
   */
  virtual bool is_symbol() const;

  /**
   * \brief Check if this is a ConsCell.
   * \return True iff this is a ConsCell.
   */
  virtual bool is_cons() const;

  /**
   * \brief Check if this is a NilCell.
   * \return True iff this is a NilCell.
   */
  virtual bool is_nil() const;

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const = 0;

  /**
   * \brief Count elements in a subtree, rooted at this cell. (error if this is not a well-formed list).
   * \return Number of elements in the tree, zero if it is not a tree.
   */
  virtual int len() const;

  /**
   * \brief Accessor (error if this is not a IntCell).
   * \return The int value stored in the cell.
   */
  virtual int get_int() const;

  /**
   * \brief Accessor (error if this is not a DoubleCell).
   * \return The double value stored in the cell.
   */
  virtual double get_double() const;

  /**
   * \brief Accessor (error if this is not a SymbolCell).
   * \return The symbol name stored in the cell.
   */
  virtual std::string get_symbol() const;

  /**
   * \brief Accessor (error if this is not a ConsCell).
   * \return First element in the cell.
   */
  virtual Cell* get_car() const;

  /**
   * \brief Accessor (error if this is not a ConsCell).
   * \return Second element in the cell.
   */
  virtual Cell* get_cdr() const;

  /**
   * \brief Self evaluation.
   * \return The copy of this cell. 
   * (return the cell itself if it is nil).
   */
  virtual Cell* eval() const = 0;

  /**
   * \brief Check if the the symbol in this cell is an operator.
   * \return True iff this is a SymbolCell and it stores an operator symbol.
   */
  virtual bool is_operator() const;

  /**
   * \brief The truth value of the cell in an if statement.
   * \return True iff the cell evaluates to  non-zero value.
   */
  virtual bool truth() const = 0;

  /**
   * \brief Compute the ceiling value of the cell. (error if this is not a DoubleCell).
   * \return The smallest integer that is greater than or equal to the cell value.
   */
  virtual Cell* eval_ceiling() const;

  /**
   * \brief Compute the floor value of the cell. (error if this is not a DoubleCell).
   * \return The biggest integer that is less than or equal to the cell value.
   */
  virtual Cell* eval_floor() const;
  
  /**
   * \brief Add the current cell value to the addend cell value. (error if this is not a DoubleCell or IntCell).
   * \return The sum of value in the two cell. Return a IntCell if both operand is IntCell, a DoubleCell otherwise.
   */
  virtual Cell* eval_addition(const Cell* addend) const = 0;
  
  /**
   * \brief Multiply the current cell value by the multiplier cell value. (error if this is not a DoubleCell or IntCell).
   * \return The product of value in the two cell. Return a IntCell if both operand is IntCell, a DoubleCell otherwise.
   */
  virtual Cell* eval_multi(const Cell* multiplier) const = 0;
  
  /**
   * \brief Divide the dividend cell value by the current cell value. (error if this is not a DoubleCell or IntCell).
   * \return The fraction of value in the two cell. Return a IntCell if both operand is IntCell, a DoubleCell otherwise.
   */
  virtual Cell* eval_divi(const Cell* dividend) const = 0;
  
  /**
   * \brief Subtract the minuend cell value with the current cell value. (error if this is not a DoubleCell or IntCell).
   * \return The difference of value in the two cell. Return a IntCell if both operand is IntCell, a DoubleCell otherwise.
   */
  virtual Cell* eval_subtra(const Cell* minuend) const = 0;

  /**
   * \brief The value this cell is bound to. (error if this is not a SymbolCell).
   * \return The Cell this cell is bound to in global_variables.
   */
  virtual Cell* bound_value() const;

  /**
   * \brief Bind the value of evaluating c to this symbol. (error if this is not a SymbolCell).
   * \param c The Cell* to be evaluated and bind to this symbol.
   */
  virtual void bind_to(Cell* const c) const;

  /**
   * \brief Check whether value of this cell is less than value of c.
   * (error if one of this cell or c is not of type IntCell or DoubleCell).
   * \return True iff value of this cell is less than value of c.
   */
  virtual bool less_than(const Cell* c) const = 0;

};

/**
 * \class IntCell
 * \brief Class IntCell to store int data.
 */
class IntCell: public Cell {
public:

  /**
   * \brief Constructor to make IntCell.
   */
  IntCell(int i);

  /**
   * \brief Destructor.
   */
  virtual ~IntCell() {}

  virtual void print(std::ostream& os = std::cout) const;

  virtual bool is_int() const;

  virtual int get_int() const;

  virtual Cell* eval() const;

  virtual bool truth() const;

  virtual Cell* eval_addition(const Cell* addend) const;

  virtual Cell* eval_multi(const Cell* multiplier) const;

  virtual Cell* eval_divi(const Cell* dividend) const;
  
  virtual Cell* eval_subtra(const Cell* minuend) const;

  virtual bool less_than(const Cell* c) const;

private:
  int int_m;
};

/**
 * \class DoubleCell
 * \brief Class DoubleCell to store double data.
 */
class DoubleCell: public Cell {
public:

  /**
   * \brief Constructor to make DoubleCell.
   */
  DoubleCell(double d);

  /**
   * \brief Destructor.
   */
  virtual ~DoubleCell() {}

  virtual void print(std::ostream& os = std::cout) const;

  virtual bool is_double() const;

  virtual double get_double() const;

  virtual Cell* eval() const;

  virtual bool truth() const;

  virtual Cell* eval_ceiling() const;

  virtual Cell* eval_floor() const;
  
  virtual Cell* eval_addition(const Cell* addend) const;

  virtual Cell* eval_multi(const Cell* multiplier) const;

  virtual Cell* eval_divi(const Cell* dividend) const;
  
  virtual Cell* eval_subtra(const Cell* minuend) const;

  virtual bool less_than(const Cell* c) const;

private:
  double double_m;
};

/**
 * \class SymbolCell
 * \brief Class SymbolCell to store symbol data.
 */
class SymbolCell: public Cell {
public:

  /**
   * \brief Constructor to make SymbolCell.
   */
  SymbolCell(const char* const symbol);

  /**
   * \brief Destructor.
   */
  virtual ~SymbolCell();

  virtual void print(std::ostream& os = std::cout) const;

  virtual bool is_symbol() const;

  virtual std::string get_symbol() const;

  virtual Cell* eval() const;

  virtual bool is_operator() const;  

  virtual bool truth() const;

  virtual Cell* eval_addition(const Cell* addend) const;

  virtual Cell* eval_multi(const Cell* multiplier) const;

  virtual Cell* eval_divi(const Cell* dividend) const;
  
  virtual Cell* eval_subtra(const Cell* minuend) const;

  virtual Cell* bound_value() const;

  virtual void bind_to(Cell* const c) const;

  virtual bool less_than(const Cell* c) const;

private:
  char* symbol_m;
};

/**
 * \class ConsCell
 * \brief Class ConsCell to store a cons pair.
 */
class ConsCell: public Cell {
public:

  /**
   * \brief Constructor to make ConsCell.
   */
  ConsCell(Cell* const my_car, Cell* const my_cdr);

  /**
   * \brief Destructor.
   */
  virtual ~ConsCell();

  virtual void print(std::ostream& os = std::cout) const;

  virtual bool is_cons() const;

  virtual int len() const;

  virtual Cell* get_car() const;

  virtual Cell* get_cdr() const;

  virtual Cell* eval() const;

  virtual bool truth() const;

  virtual Cell* eval_addition(const Cell* addend) const;

  virtual Cell* eval_multi(const Cell* multiplier) const;

  virtual Cell* eval_divi(const Cell* dividend) const;
  
  virtual Cell* eval_subtra(const Cell* minuend) const;

  virtual bool less_than(const Cell* c) const;

private:
  Cell* car;
  Cell* cdr;
};

/**
 * \class NilCell
 * \brief Class NilCell to represent nil.
 */
class NilCell: public Cell {
public:

  /**
   * \brief Constructor to make NilCell.
   */
  NilCell() {}
  
  /**
   * \brief Destructor.
   */
  virtual ~NilCell() {}

  virtual void print(std::ostream& os = std::cout) const;

  virtual bool is_nil() const;

  virtual Cell* eval() const;

  virtual bool truth() const;

  virtual Cell* eval_addition(const Cell* addend) const;

  virtual Cell* eval_multi(const Cell* multiplier) const;

  virtual Cell* eval_divi(const Cell* dividend) const;
  
  virtual Cell* eval_subtra(const Cell* minuend) const;

  virtual bool less_than(const Cell* c) const;

};

extern Cell* const nil;

extern std::map<std::string, Cell*> global_variables;

#endif //CELL_HPP

