/**
 * \file linkedlist_internals.hpp
 *
 * Encapsulates an abstract interface layer for a cons list ADT,
 * without using member functions. Makes no assumptions about what
 * kind of concrete type Cell will be defined to be.
 */

#ifndef LINKEDLIST_INTERNALS_HPP
#define LINKEDLIST_INTERNALS_HPP

#include "Node.hpp"
#include "Cell.hpp"
#include <string>
#include <iostream>
#include <cstring>

/**
 * \brief Make an int cell.
 * \param i The initial int value to be stored in the new cell.
 */
inline Cell* make_int(int i)
{
  Cell* int_cell = (Cell*)malloc(sizeof(Cell));
  if (!int_cell) {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
  int_cell->tag_m = type_int;
  int_cell->int_m = i;
  return int_cell;
}

/**
 * \brief Make a double cell.
 * \param d The initial double value to be stored in the new cell.
 */
inline Cell* make_double(double d)
{
  Cell* double_cell = (Cell*)malloc(sizeof(Cell));
  if (!double_cell) {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
  double_cell->tag_m = type_double;
  double_cell->double_m = d;
  return double_cell;
}

/**
 * \brief Make a symbol cell.
 * \param s The initial symbol name to be stored in the new cell.
 */
inline Cell* make_symbol(const char* s)
{
  Cell* symbol_cell = (Cell*)malloc(sizeof(Cell));
  if (!symbol_cell) {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
  symbol_cell->tag_m = type_symbol;
  char* cpy_str = (char*)malloc((strlen(s) + 1) * sizeof(char));
  if (!cpy_str) {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
  strcpy(cpy_str, s);
  symbol_cell->symbol_m = cpy_str;
  return symbol_cell;
}


/**
 * \brief Make a linked list node.
 * \param my_elem Pointer to the element to be held by this node.
 * \param my_next Pointer to the next node.
 */
inline Node* make_node(Cell* my_elem, Node* my_next)
{
  Node* new_node = (Node*)malloc(sizeof(Node));
  if (!new_node) {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
  new_node->elem_m = my_elem;
  new_node->next_m = my_next;
  return new_node;
}

/**
 * \brief Check if d points to an int node.
 * \return True iff d points to an int node.
 */
inline bool intp(const Cell* c)
{
  return (c->tag_m == type_int);
}

/**
 * \brief Check if d points to a double node.
 * \return True iff d points to a double node.
 */
inline bool doublep(const Cell* c)
{
  return (c->tag_m == type_double);
}

/**
 * \brief Check if d points to a symbol node.
 * \return True iff d points to a symbol node.
 */
inline bool symbolp(const Cell* c)
{
  return (c->tag_m == type_symbol);
}

/**
 * \brief Accessor (error if d is not an int node).
 * \return The value in the int node pointed to by c.
 */
inline int get_int(const Cell* c)
{
  if (intp(c)) {
    return c->int_m;
  }
  else {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
}

/**
 * \brief Accessor (error if d is not a double node).
 * \return The value in the double node pointed to by c.
 */
inline double get_double(const Cell* c)
{
  if (doublep(c)) {
    return c->double_m;
  }
  else {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
}

/**
 * \brief Retrieve the symbol name as a string (error if d is not a
 * symbol node).
 * \return The symbol name in the symbol node pointed to by c.
 */
inline char* get_symbol(const Cell* c)
{
  if (symbolp(c)) {
    return c->symbol_m;
  }
  else {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
}

/**
 * \brief Accessor.
 * \return The elem pointer in the linked list node pointed to by c.
 */
inline Cell* get_elem(const Node* n)
{
  return n->elem_m;
}

/**
 * \brief Accessor.
 * \return The next pointer in the linked list node pointed to by c.
 */
inline Node* get_next(const Node* n)
{
  return n->next_m;
}

/**
 * \brief Print the linked list rooted at n in parentheses.
 * \param os The output stream to print to.
 * \param n The root node of the linked list to be printed.
 */
inline std::ostream& operator<<(std::ostream& os, const Node& n)
{
  const Node* current_node = &n;
  Cell* elem = NULL;
  os << "(";
  while (current_node != NULL) {
    if (get_elem(current_node)) {
      elem = get_elem(current_node);
      if (intp(elem)) {os << get_int(elem) << " ";}
      else if (doublep(elem)) {os << get_double(elem) << " ";}
      else if (symbolp(elem)) {os << get_symbol(elem) << " ";}
    }
    current_node = get_next(current_node);
  }
  if (elem) {os << '\b';}
  os << ")";
  return os;
}

#endif // LINKEDLIST_INTERNALS_HPP
