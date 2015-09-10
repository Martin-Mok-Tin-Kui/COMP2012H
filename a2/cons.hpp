/**
 * \file cons.hpp
 *
 * Encapsulates an abstract interface layer for a cons list ADT,
 * without using member functions. Makes no assumptions about what
 * kind of concrete type Cell will be defined to be.
 */

#ifndef CONS_HPP
#define CONS_HPP

#include "Cell.hpp"
#include <string>
#include <iostream>

/**
 * \brief The null pointer value.
 */
extern Cell* const nil;

/**
 * \brief Print error message to standard error and exit program.
 * \param err_msg The error message to be printed, by default should be ERROR.
 */
inline void raise_err(std::string err_msg="ERROR")
{
  std::cerr << err_msg << std::endl;
  exit(1);
}

/**
 * \brief Return the length of c. (error if c is not a well-formed list).
 * \param c The root of the subtree.
 * \return the number of elements in c, if it is a tree,
 *  otherwise return zero.  
 */
inline int len(Cell* const c)
{
  return c->len();
}

/**
 * \brief Make an int cell.
 * \param i The initial int value to be stored in the new cell.
 */
inline Cell* make_int(const int i)
{
  return new IntCell(i);
}

/**
 * \brief Make a double cell.
 * \param d The initial double value to be stored in the new cell.
 */
inline Cell* make_double(const double d)
{
  return new DoubleCell(d);
}

/**
 * \brief Make a symbol cell.
 * \param s The initial symbol name to be stored in the new cell.
 */
inline Cell* make_symbol(const char* const s)
{
  return new SymbolCell(s);
}

/**
 * \brief Make a conspair cell.
 * \param my_car The initial car pointer to be stored in the new cell.
 * \param my_cdr The initial cdr pointer to be stored in the new cell.
 */
inline Cell* cons(Cell* const my_car, Cell* const my_cdr)
{
  return new ConsCell(my_car, my_cdr);
}

/**
 * \brief Check if c points to an empty list, i.e., is a null pointer.
 * \return True iff c points to an empty list, i.e., is a null pointer.
 */
inline bool nullp(Cell* const c)
{
  return (c == nil);
}

/**
 * \brief Check if c points to a list (i.e., nil or a cons cell).
 * \return True iff c points to a list (i.e., nil or a cons cell).
 */
inline bool listp(Cell* const c)
{
  return nullp(c) || c->is_cons();
}

/**
 * \brief Check if c points to an int cell.
 * \return True iff c points to an int cell.
 */
inline bool intp(Cell* const c)
{
  return !nullp(c) && c->is_int();
}

/**
 * \brief Check if c points to a double cell.
 * \return True iff c points to a double cell.
 */
inline bool doublep(Cell* const c)
{
  return !nullp(c) && c->is_double();
}

/**
 * \brief Check if c points to a symbol cell.
 * \return True iff c points to a symbol cell.
 */
inline bool symbolp(Cell* const c)
{
  return !nullp(c) && c->is_symbol();
}

/**
 * \brief Accessor (error if c is not an int cell).
 * \return The value in the int cell pointed to by c.
 */
inline int get_int(Cell* const c)
{
  return c->get_int();
}

/**
 * \brief Accessor (error if c is not a double cell).
 * \return The value in the double cell pointed to by c.
 */
inline double get_double(Cell* const c)
{
  return c->get_double();
}

/**
 * \brief Retrieve the symbol name as a string (error if c is not a
 * symbol cell).
 * \return The symbol name in the symbol cell pointed to by c.
 */
inline std::string get_symbol(Cell* const c)
{
  return c->get_symbol();
}

/**
 * \brief Accessor (error if c is not a cons cell).
 * \return The car pointer in the cons cell pointed to by c.
 */
inline Cell* car(Cell* const c)
{
  return c->get_car();
}

/**
 * \brief Accessor (error if c is not a string cell).
 * \return The cdr pointer in the cons cell pointed to by c.
 */
inline Cell* cdr(Cell* const c)
{
  return c->get_cdr();
}

/**
 * \brief Print the subtree rooted at c, in s-expression notation.
 * \param os The output stream to print to.
 * \param c The root cell of the subtree to be printed.
 */
inline std::ostream& operator<<(std::ostream& os, const Cell& c)
{
  c.print(os);
  return os;
}

/**
 * \brief Check the number of elements in the list is legal or not.
 * \param c The root of the subtree to be checked.
 * \param min The minimum allowed length of the list.
 * \param max The maximum allowed length of the list, by default there's no limit in maximum.
 * \return True iff c is a valid list and the length of c is greater than or 
 *  equals to min, and less than or equals to max.
 */
inline bool check_form(Cell* const c, int min, int max = 0)
{
  int list_len = len(c);
  if (listp(c) && (list_len >= min) && ((!max) || (list_len <= max))) return true;
  return false;
}

#endif // CONS_HPP
