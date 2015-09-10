/**
 * \file eval.cpp
 *
 * Evaluate the s-expression tree parsed by parse.cpp and do error detection.
 */

#include "eval.hpp"

/**
 * \brief Evaluation for operator if. 
 * Error if there is less than two operands or there are more than three operands.
 * \param c The root of the subtree following the if symbol.
 * \return the result of evaluating the second operand if the first one evaluates to non-zero value, 
 * otherwise return the result of evaluating the third operand. 
 * (if there is no third operand, return nil)
 */
Cell* eval_if(Cell* const c);

/**
 * \brief Evaluation for operator +. Error if an operand doesn't evaluate to IntCell or DoubleCell.
 * \param operand_list The root of the subtree following the + symbol.
 * \return The summation of result of evaluating each element in the operand_list.
 * if no operands are given, return 0.
 */
Cell* eval_addition(Cell* operand_list);

/**
 * \brief Evaluation for operator ceiling. Error if the operand doesn't evaluate to DoubleCell,
 * or more than one operands are passed in.
 * \param c The root of the subtree following the ceiling symbol.
 * \return The smallest integer that is greater than or equal to the result of evaluating the operand.
 */
Cell* eval_ceiling(Cell* const c);

/**
 * \brief Evaluation for operator floor. Error if the operand doesn't evaluate to DoubleCell,
 * or more than one operands are passed in.
 * \param c The root of the subtree following the floor symbol.
 * \return The greatest integer that is less than or equal to the result of evaluating the operand.
 */
Cell* eval_floor(Cell* const c);

/**
 * \brief Evaluation for operator quote. Error if more than one operands are passed in.
 * \param c The root of the subtree following the quote symbol.
 * \return The operand without evaluating it.
 */
Cell* eval_quote(Cell* const c);

/**
 * \brief Evaluation for operator *. Error if an operand doesn't evaluate to IntCell or DoubleCell.
 * \param operand_list The root of the subtree following the * symbol.
 * \return The product of result of evaluating each element in the operand_list.
 * if no operands are given, return 1.
 */
Cell* eval_multi(Cell* operand_list);

/**
 * \brief Evaluation for operator /. Error if an operand doesn't evaluate to IntCell or DoubleCell,
 * or no operands are given.
 * \param operand_list The root of the subtree following the / symbol.
 * \return If there's only one operand, return the inverse of the result of evaluating the operand.
 * Otherwise, Divide the first operand by the other operands.
 */
Cell* eval_divi(Cell* operand_list);

/**
 * \brief Evaluation for operator -. Error if an operand doesn't evaluate to IntCell or DoubleCell,
 * or no operands are given.
 * \param operand_list The root of the subtree following the - symbol.
 * \return If there's only one operand, return the negative of the result of evaluating the operand.
 * Otherwise, subtract other operands from the first operand.
 */
Cell* eval_subtra(Cell* operand_list);

/**
 * \brief Evaluation for operator cons. Error if the number of operands is not two.
 * \param c The root of the subtree following the cons symbol.
 * \return A new ConsCell, with first element being the result of evaluating the first operand
 *  and second element being the result of evaluating the second operand.
 */
Cell* eval_cons(Cell* const c);

/**
 * \brief Evaluation for operator car. Error if more than one operands are passed in,
 * or the operand doesn't evaluate to a valid list.
 * \param c The root of the subtree following the car symbol.
 * \return The first element of the result of evaluating the operand.
 */
Cell* eval_car(Cell* const c);

/**
 * \brief Evaluation for operator cdr. Error if more than one operands are passed in,
 * or the operand doesn't evaluate to a valid list.
 * \param c The root of the subtree following the cdr symbol.
 * \return The second element of the result of evaluating the operand.
 */
Cell* eval_cdr(Cell* const c);

/**
 * \brief Evaluation for operator nullp. Error if more than one operands are passed in.
 * \param c The root of the subtree following the nullp symbol.
 * \return IntCell with value 1, if the operand evaluates to nil, otherwise
 * return IntCell with value 0.
 */
Cell* eval_nullp(Cell* const c);

/**
 * \brief Evaluation for operator define. Error if the number of operands is not two, 
 * or if the first operand is not a SymbolCell.
 * \param c The root of the subtree following the define symbol.
 * \return Bind the value of evaluating the second operand to the first symbol operand, return nil.
 */
Cell* eval_define(Cell* const c);

/**
 * \brief Evaluation for operator eval. Error if more than one operands are passed in.
 * \param c The root of the subtree following the eval symbol.
 * \return result of evaluating the value of operand.
 */
Cell* eval_eval(Cell* const c);

/**
 * \brief Evaluation for operator print. Error if more than one operands are passed in.
 * \param c The root of the subtree following the print symbol.
 * \return Print the value of the operand to standard output stream, return nil.
 */
Cell* eval_print(Cell* const c);

/**
 * \brief Evaluation for operator not. Error if more than one operands are passed in.
 * \param c The root of the subtree following the not symbol.
 * \return One, if the operand evaluates to zero (either int or double), and zero otherwise.
 */
Cell* eval_not(Cell* const c);

/**
 * \brief Evaluation for operator <. Error if an operand doesn't evaluate to IntCell or DoubleCell.
 * \param operand_list The root of the subtree following the < symbol.
 * \return Zero if any two consecutive operands are not monotonically increasing, and one otherwise.
 */
Cell* eval_less_than(Cell* operand_list);

Cell* eval(Cell* const c)
{
  if (nullp(c)) {
    throw runtime_error("malformd list, cannot evaluate nil.");
  }
  else if (symbolp(c)) {
    return c->bound_value();
  }
  else if (listp(c)) {
    Cell* car_cell = (!symbolp(car(c))) ? eval(car(c)) : (car(c))->eval();
    if (!car_cell->is_operator()) {
      if (!nullp(car_cell)) delete car_cell;
      throw runtime_error("malformed list, expected an operator.");
    }
    string operator_type = get_symbol(car_cell);
    if (operator_type == "+") {
      // release dynamically allocated memory, same for other cases.
      if (!nullp(car_cell)) delete car_cell;
      return eval_addition(cdr(c));
    }
    else if (operator_type == "*") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_multi(cdr(c));
    }
    else if (operator_type == "/") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_divi(cdr(c));
    }
    else if (operator_type == "-") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_subtra(cdr(c));
    }
    else if (operator_type == "if") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_if(cdr(c));
    }
    else if (operator_type == "ceiling") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_ceiling(cdr(c));
    }
    else if (operator_type == "floor") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_floor(cdr(c));
    }
    else if (operator_type == "quote") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_quote(cdr(c));
    }
    else if (operator_type == "cons") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_cons(cdr(c));
    }
    else if (operator_type == "car") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_car(cdr(c));
    }
    else if (operator_type == "cdr") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_cdr(cdr(c));
    }
    else if (operator_type == "nullp") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_nullp(cdr(c));
    }
    else if (operator_type == "define") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_define(cdr(c));
    }
    else if (operator_type == "eval") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_eval(cdr(c));
    }
    else if (operator_type == "print") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_print(cdr(c));
    }
    else if (operator_type == "not") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_not(cdr(c));
    }
    else if (operator_type == "<") {
      if (!nullp(car_cell)) delete car_cell;
      return eval_less_than(cdr(c));
    }
  }
  else {
    return c->eval();
  }
}

Cell* eval_quote(Cell* const c) {
  if (check_form(c, 1, 1)) {
    return (car(c))->eval();
  }
  else {
    throw runtime_error("operator quote expects one operand.");
  }
}

Cell* eval_addition(Cell* operand_list) {
  if (check_form(operand_list, 0)) {
    // identity value for addition.
    Cell* result = make_int(0);
    while (!nullp(operand_list)) {
      Cell* operand = eval(car(operand_list));
      result = operand->eval_addition(result);
      if (!nullp(operand)) delete operand;
      operand_list = cdr(operand_list);
    }
    return result;
  }
  else {
    throw runtime_error("malformed list for operator +");
  }
}

Cell* eval_multi(Cell* operand_list) {
  if (check_form(operand_list, 0)) {
    // identity value for multiplication.
    Cell* result = make_int(1);
    while (!nullp(operand_list)) {
      Cell* operand = eval(car(operand_list));
      result = operand->eval_multi(result);
      if (!nullp(operand)) delete operand;
      operand_list = cdr(operand_list);
    }
    return result;
  }
  else {
    throw runtime_error("malformed list for operaotr *");
  }
}

Cell* eval_divi(Cell* operand_list) {
  if (check_form(operand_list, 1)) {
    if (len(operand_list) == 1) {
      Cell* result = make_int(1);
      Cell* operand = eval(car(operand_list));
      result = operand->eval_divi(result);
      if (!nullp(operand)) delete operand;
      return result;
    }
    else {
      Cell* result = eval(car(operand_list));
      // raise the error, if the first operand is of wrong type.
      if (!intp(result) && !doublep(result)) result->eval_divi(make_int(1));
      operand_list = cdr(operand_list);
      while (!nullp(operand_list)) {
	Cell* operand = eval(car(operand_list));
	result = operand->eval_divi(result);
	if (!nullp(operand)) delete operand;
	operand_list = cdr(operand_list);
      }
      return result;
    }
  }
  else {
    throw runtime_error("operator / expects at least one operand.");
  }
}

Cell* eval_subtra(Cell* operand_list) {
  if (check_form(operand_list, 1)) {
    if (len(operand_list) == 1) {
      Cell* result = make_int(0);
      Cell* operand = eval(car(operand_list));
      result = operand->eval_subtra(result);
      if (!nullp(operand)) delete operand;
      return result;
    }
    else {
      Cell* result = eval(car(operand_list));
      // raise the error, if the first operand is of wrong type.
      if (!intp(result) && !doublep(result)) result->eval_subtra(make_int(0));
      operand_list = cdr(operand_list);
      while (!nullp(operand_list)) {
	Cell* operand = eval(car(operand_list));
	result = operand->eval_subtra(result);
	if (!nullp(operand)) delete operand;
	operand_list = cdr(operand_list);
      }
      return result;
    }
  }
  else {
    throw runtime_error("operator - expects at least one operand.");
  }
}

Cell* eval_if(Cell* const c) {
  if (check_form(c, 2, 3)) {
    int list_length = len(c);
    Cell* condition = eval(car(c));
    Cell* clause = cdr(c);
    if (!condition->truth()) {
      if (list_length == 2) {
	if (!nullp(condition)) delete condition;
	return nil;
      }
      else {
	if (!nullp(condition)) delete condition;
	return eval(car(cdr(clause)));
      }
    }
    else {
      if (!nullp(condition)) delete condition;
      return eval(car(clause));
    }
  }
  else {
    throw runtime_error("operator if expects either two or three operands.");
  }
}

Cell* eval_ceiling(Cell* const c) {
  if (check_form(c, 1, 1)) {
    Cell* operand = eval(car(c));
    Cell* ans = operand->eval_ceiling();
    if (!nullp(operand)) delete operand;
    return ans;
  }
  else {
    throw runtime_error("operator ceiling expects one double operand.");
  }
}

Cell* eval_floor(Cell* const c) {
  if (check_form(c, 1, 1)) {
    Cell* operand = eval(car(c));
    Cell* ans = operand->eval_floor();
    if (!nullp(operand)) delete operand;
    return ans;
  }
  else {
    throw runtime_error("operator floor expects one double operand.");
  }
}


Cell* eval_cons(Cell* const c) {
  if (check_form(c, 2, 2)) {
    return cons(eval(car(c)), eval(car(cdr(c))));
  }
  else {
    throw runtime_error("operator cons expects two operands.");
  }
}

Cell* eval_car(Cell* const c) {
  if (check_form(c, 1, 1)) {
    Cell* eval_result = eval(car(c));
    // raise the error, if the operand doesn't evaluate to a ConsCell. 
    if (nullp(eval_result) || !listp(eval_result)) {
      if (!nullp(eval_result)) delete eval_result;
      throw runtime_error("operator car expects one list operand.");
    }
    // Self evaluate the first element of eval_result to make a copy, 
    // and release memory of the second elements.
    Cell* car_result = (car(eval_result))->eval();
    delete eval_result;
    return car_result;
  }
  else {
    throw runtime_error("operator car expects one list operand.");
  }
}

Cell* eval_cdr(Cell* const c) {
  if (check_form(c, 1, 1)) {
    Cell* eval_result = eval(car(c));
    // raise the error, if the operand doesn't evaluate to a ConsCell. 
    if (nullp(eval_result) || !listp(eval_result)) {
      if (!nullp(eval_result)) delete eval_result;
      throw runtime_error("operator cdr expects one list operand.");
    }
    // Self evaluate the second element of eval_result to make a copy, 
    // and release memory of the first elements.
    Cell* cdr_result = (cdr(eval_result))->eval();
    if (!nullp(eval_result)) delete eval_result;
    return cdr_result;
  }
  else {
    throw runtime_error("operator cdr expects one list operand.");
  }
}

Cell* eval_nullp(Cell* const c) {
  if (check_form(c, 1, 1)) {
    Cell* eval_result = eval(car(c));
    if (nullp(eval_result)) {
      return make_int(1);
    }
    else {
      delete eval_result;
      return make_int(0);
    }
  }
  else {
    throw runtime_error("operator nullp expects one operand.");
  }
}


Cell* eval_define(Cell* const c) {
  if (check_form(c, 2, 2)) {
    (car(c))->bind_to(eval(car(cdr(c))));
    return nil;
  }
  else {
    throw runtime_error("operator define expects two operands.");
  }
}

Cell* eval_eval(Cell* const c) {
  if (check_form(c, 1, 1)) {
    Cell* to_be_eval = eval(car(c));
    Cell* result = eval(to_be_eval);
    if (!nullp(to_be_eval)) delete to_be_eval;
    return result;
  }
  else {
    throw runtime_error("operator eval expects one operand.");
  }
}

Cell* eval_print(Cell* const c) {
  if (check_form(c, 1, 1)) {
    Cell* eval_result = eval(car(c));
    cout << *eval_result << endl;
    if (!nullp(eval_result)) delete eval_result;
    return nil;
  }
  else {
    throw runtime_error("operator print expects one operand.");
  }
}

Cell* eval_not(Cell* const c) {
  if (check_form(c, 1, 1)) {
    Cell* eval_result = eval(car(c));
    int ans = eval_result->truth() ? 0 : 1;
    if (!nullp(eval_result)) delete eval_result;
    return make_int(ans);
  }
  else {
    throw runtime_error("operator not expects one operand.");
  }
}

Cell* eval_less_than(Cell* operand_list) {
  if (check_form(operand_list, 0)) {
    Cell* smaller_cell = nil;
    if (!nullp(operand_list)) {
      smaller_cell = eval(car(operand_list));
      // to make sure that the first cell is of the right type,
      // in case there is only one operand.
      Cell* tmp_compare_cell = make_int(1);
      smaller_cell->less_than(tmp_compare_cell);
      delete tmp_compare_cell;
      operand_list = cdr(operand_list);
    }
    int ans = 1;
    while (!nullp(operand_list)) {
      Cell* bigger_cell = eval(car(operand_list));
      if (!smaller_cell->less_than(bigger_cell)) {
	ans = 0;
      }
      if (!nullp(smaller_cell)) delete smaller_cell;
      smaller_cell = bigger_cell;
      operand_list = cdr(operand_list);
    }
    if (!nullp(smaller_cell)) delete smaller_cell;
    return make_int(ans);
  }
  else {
    throw runtime_error("malformed list for operaotr <.");
  }
}
