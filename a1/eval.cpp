/**
 * \file eval.cpp
 *
 * Evaluate the s-expression tree parsed by parse.cpp.Handle three 
 * operator + if and ceiling and do error detection.
 */

#include "eval.hpp"

/**
 * \brief Evaluate operator if.Error if there is too few operands or there are too many operands.
 * \param c The root of the subtree following the if symbol.
 * \return the value of the second expression if the first one evaluates to non-zero value, 
 * otherwise return the value of the third expression if there is a third expression,
 * or undefined if there isn't any.
 */
Cell* eval_if(Cell* const c);

/**
 * \brief Evaluate operator +.Error if an operand is not of type int or double.
 * \param operand_list The root of the subtree following the + symbol.
 * \return the summation of the operand_list.
 */
Cell* eval_addition(Cell* operand_list);

/**
 * \brief Evaluate operator ceiling.Error if the operand is not of type double or more than one operands are passed in.
 * \param c The root of the subtree following the ceiling symbol.
 * \return The smallest integer that is greater or equal to the operand.
 */
Cell* eval_ceiling(Cell* const c);

Cell* eval(Cell* const c)
{
  if (nullp(c)) {
    raise_err("ERROR. Malform list, expect operator name.");
  }
  else if (intp(c)) {
    return make_int(get_int(c));
  }
  else if (doublep(c)) {
    return make_double(get_double(c));
  }
  else if (symbolp(c)) {
    return make_symbol(get_symbol(c).c_str());
  }
  else if (listp(c)) {
    Cell* car_cell = eval(car(c));
    if (symbolp(car_cell)) {
      string operator_type = get_symbol(car_cell);
      if (operator_type == "+") {
	// release dynamically allocated memory.
	delete car_cell;
	return eval_addition(cdr(c));
      }
      else if (operator_type == "if") {
	// release dynamically allocated memory.
	delete car_cell;
	return eval_if(cdr(c));
      }
      else if (operator_type == "ceiling") {
	// release dynamically allocated memory.
	delete car_cell;
	return eval_ceiling(cdr(c));
      }
      else {
	raise_err("ERROR. Undefined operator " + operator_type + ".");
      }
    }
    else {
      raise_err("ERROR. Undefined operator.");
    }
  }
}

Cell* eval_addition(Cell* operand_list) {
  double sum = 0.0;
  bool int_result = true;
  while (!nullp(operand_list) && listp(operand_list)) {
    Cell* operand = eval(car(operand_list));
    if (intp(operand)) {
      sum += get_int(operand);
    }
    else if (doublep(operand)) {
      sum += get_double(operand);
      int_result = false;
    }
    else {
      raise_err("ERROR. TypeError: operator + expects int or double operands.");
    }
    operand_list = cdr(operand_list);
    // release dynamically allocated memory.
    delete operand;
  }
  if (int_result) {
    return make_int(static_cast<int>(sum));
  }
  else {
    return make_double(sum);
  }
}

Cell* eval_if(Cell* const c) {
  if (nullp(c) || !listp(c)) {
    raise_err("ERROR. SyntaxError: operator if expects at least two operands.");
  }
  int list_length = len(c);
  if (list_length == 1) {
    raise_err("ERROR. SyntaxError: operator if expects at least one return expression.");
  }
  else if (list_length > 3) {
    raise_err("ERROR. SyntaxError: too many operands for operator if.");
  }
  Cell* condition_cell = eval(car(c));
  Cell* clause = cdr(c);
  double condition = 1.0;
  if (nullp(condition_cell)) {condition = 0;}
  else if (intp(condition_cell)) {
    condition = get_int(condition_cell);
  }
  else if (doublep(condition_cell)) {
    condition = get_double(condition_cell);
  }
  // release dynamically allocated memory.
  delete condition_cell;
  if (!condition) {
    if (list_length == 2) {
      return make_symbol("undefined");
    }
    else {
      return eval(car(cdr(clause)));
    }
  }
  else {
    return eval(car(clause));
  }
}

Cell* eval_ceiling(Cell* const c) {
  if (nullp(c)) {
    raise_err("ERROR. SyntaxError: operator ceiling expects one double operand.");
  }
  if (listp(c)) {
    if (!nullp(cdr(c))) {
      raise_err("ERROR. SyntaxError: operator ceiling expects exactly one double operand.");
    }
    else {
      Cell* operand_cell = eval(car(c));
      if (!doublep(operand_cell)) {
	raise_err("ERROR. TypeError: operator ceiling expects operand of type double.");
      }
      else {
	double operand = get_double(operand_cell);
	int result = 0;
	if (operand > 0) {
	  while ((result < operand) && (++result));
	}
	else if (operand < 0) {
	  while ((result > operand) && (--result));
	  ++result;
	}
	// release dynamically allocated memory.
	delete operand_cell;
	return make_int(result);
      }
    }
  }
}
