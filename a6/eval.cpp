/**
 * \file eval.cpp
 *
 * Evaluate the s-expression tree parsed by parse.cpp and do error detection.
 */

#include "eval.hpp"


/**
 * \brief Evaluate each element in expression.
 * \param expr Expression to be evaluated.
 * \return A new list with each element being the result of 
 * evaluating the corresponding element in expr.
 */
Cell* eval_each(Cell* expr);

/**
 * \brief Evaluate if form. Error if there is less 
 * than two operands or there are more than three operands.
 * \param c The root of the subtree following the if symbol.
 * \return the result of evaluating the second operand 
 * if the first one evaluates to non-zero value, 
 * otherwise return the result of evaluating the third operand. 
 * (if there is no third operand, return nil)
 */
Cell* eval_if(Cell* c);

/**
 * \brief Evaluate quote form. 
 * Error if more than one operands are passed in.
 * \param c The root of the subtree following the quote symbol.
 * \return The operand without evaluating it.
 */
Cell* eval_quote(Cell* c);

/**
 * \brief Evaluate define form. 
 * Error if the number of operands is not two, 
 * or if the first operand is not a SymbolCell.
 * \param c The root of the subtree following the define symbol.
 * \return Bind the value of evaluating the second operand 
 * to the first symbol operand in current env, return nil.
 */
Cell* eval_define(Cell* c);

/**
 * \brief Evaluate lambda form. Error if the number of operands
 * is less than two. (one for the formal parameters and one
 * for the function body). 
 * \param c The root of the subtree following the lambda symbol.
 * \return A lambda procedure with formals as the car of c and
 * body as the cdr of c.
 */
Cell* eval_lambda(Cell* c);

/**
 * \brief Check if formals is a well-formed formal parameter 
 * list. Throw an error if formals is not a well-formed list or
 * formals contains same name.
 * \param formals The formal parameter list to be checked.
 */
void check_formals(Cell* formals);

/**
 * \brief Evaluate begin form. evaluate each expression in the
 * begin form except for the last one. 
 * Error if there's an error in evaluating any expression.
 * \param expressions Expressions following begin, to be eval.
 * \return The last expression after evaluating all the 
 * previous one.
 */
Cell* eval_begin(Cell* expressions);

/**
 * \brief Evaluate let form. Make new local frame. The first
 * expression in let form should be a name-expression pair
 * list. Bind values of the expression to names in the new
 * frame. Evaluate expressions following the name-expr pair list.
 * Error if the let form isn't well formed.
 * \param expr Expressions following let.
 * \return The result of evaluating the last expression in the
 * let form.
 */
Cell* eval_let(Cell* expr);

/**
 * \brief Simplified version of eval, just looks better.
 */
Cell* optimized_eval(Cell* expr);

/**
 * \brief Apply proce with args as its formals arguments list.
 * \return The value of applying the function to args.
 */
Cell* apply(Cell* proce, Cell* args);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * Implementation of scheme primitive procedures declared in primitive.hpp
 *
 */

Cell* eval_addition(Cell* c) {
  if (!check_form(c, 0)) {
    throw runtime_error("malformed list for operator +");
  }
  // identity value for addition.
  Cell* result = make_int(0);
  while (!nullp(c)) {
    Cell* operand = car(c);
    result = operand->eval_addition(result);
    c = cdr(c);
  }
  return result;
}


Cell* eval_multi(Cell* c) {
  if (!check_form(c, 0)) {
    throw runtime_error("malformed list for operaotr *");
  }
  // identity value for multiplication.
  Cell* result = make_int(1);
  while (!nullp(c)) {
    Cell* operand = car(c);
    result = operand->eval_multi(result);
    c = cdr(c);
  }
  return result;
}


Cell* eval_divi(Cell* c) {
  if (!check_form(c, 1)) {
    throw runtime_error("operator / expects at least one operand.");
  }
  if (len(c) == 1) {
    Cell* result = make_int(1);
    Cell* operand = car(c);
    result = operand->eval_divi(result);
    return result;
  }
  else {
    Cell* result = car(c);
    /**
     * raise the error, if the first operand is of wrong type.
     */
    if (!intp(result) && !doublep(result)) result->eval_divi(nil);
    c = cdr(c);
    while (!nullp(c)) {
      Cell* operand = car(c);
      result = operand->eval_divi(result);
      c = cdr(c);
    }
    return result;
  }
}


Cell* eval_subtra(Cell* c) {
  if (!check_form(c, 1)) {
    throw runtime_error("operator - expects at least one operand.");
  }
  if (len(c) == 1) {
    Cell* result = make_int(0);
    Cell* operand = car(c);
    result = operand->eval_subtra(result);
    return result;
  }
  else {
    Cell* result = car(c);
    /**
     * raise the error, if the first operand is of wrong type.
     */
    if (!intp(result) && !doublep(result)) result->eval_subtra(nil);
    c = cdr(c);
    while (!nullp(c)) {
      Cell* operand = car(c);
      result = operand->eval_subtra(result);
      c = cdr(c);
    }
    return result;
  }
}


Cell* eval_ceiling(Cell* c) {
  if (!check_form(c, 1, 1)) {
    throw runtime_error("operator ceiling expects one double operand.");
  }
  return (car(c))->eval_ceiling();  
}


Cell* eval_floor(Cell* c) {
  if (!check_form(c, 1, 1)) {
    throw runtime_error("operator floor expects one double operand.");
  }
  return (car(c))->eval_floor();
}


Cell* eval_cons(Cell* c) {
  if (!check_form(c, 2, 2)) {
    throw runtime_error("operator cons expects two operands.");
  }
  return cons(car(c), car(cdr(c)));
}


Cell* eval_car(Cell* c) {
  if (!check_form(c, 1, 1)) {
    throw runtime_error("operator car expects one list operand.");
  }
  return car(car(c));
}


Cell* eval_cdr(Cell* c) {
  if (!check_form(c, 1, 1)) {
    throw runtime_error("operator cdr expects one list operand.");
  }
  return cdr(car(c));
}


Cell* eval_nullp(Cell* c) {
  if (!check_form(c, 1, 1)) {
    throw runtime_error("operator nullp expects one operand.");
  }
  if (nullp(car(c))) {
    return make_int(1);
  }
  else {
    return make_int(0);
  }
}


Cell* eval_eval(Cell* c) {
  if (!check_form(c, 1, 1)) {
    throw runtime_error("operator eval expects one operand.");
  }  
  Cell* result = eval(car(c));
  return result;
}


Cell* eval_print(Cell* c) {
  if (!check_form(c, 1, 1)) {
    throw runtime_error("operator print expects one operand.");
  }
  cout << *(car(c)) << endl;
  return nil;
}


Cell* eval_not(Cell* const c) {
  if (!check_form(c, 1, 1)) {
    throw runtime_error("operator not expects one operand.");
  }
  int ans = (car(c))->truth() ? 0 : 1;
  return make_int(ans);
}


Cell* eval_less_than(Cell* c) {
  if (!check_form(c, 0)) {
    throw runtime_error("malformed list for operaotr <.");
  }
  Cell* smaller_cell = nil;
  if (!nullp(c)) {
    smaller_cell = car(c);
    /**
     * to make sure that the first cell is of the right type,
     * in case there is only one operand.
     *
     */
    Cell* tmp_compare_cell = make_int(1);
    smaller_cell->less_than(tmp_compare_cell);
    delete tmp_compare_cell;
    c = cdr(c);
  }
  int ans = 1;
  while (!nullp(c)) {
    Cell* bigger_cell = car(c);
    if (!smaller_cell->less_than(bigger_cell)) {
      ans = 0;
    }
    smaller_cell = bigger_cell;
    c = cdr(c);
  }
  return make_int(ans);
}


Cell* eval_apply(Cell* c) {
  if (!check_form(c, 2, 2)) {
    throw runtime_error("operator apply expects exactly two operands.");
  }
  Cell* proce = car(c);
  Cell* args = car(cdr(c));
  return apply(proce, args);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


/**
 * \brief bind symbols to primitive procedures in the global env.
 */
Env* init_env() {
  Env *env = new Env();
  Frame* global_f = env->top_frame();
  global_f->define("+", make_primitive(eval_addition));
  global_f->define("*", make_primitive(eval_multi));
  global_f->define("/", make_primitive(eval_divi));
  global_f->define("-", make_primitive(eval_subtra));
  global_f->define("ceiling", make_primitive(eval_ceiling));
  global_f->define("floor", make_primitive(eval_floor));
  global_f->define("cons", make_primitive(eval_cons));
  global_f->define("car", make_primitive(eval_car));
  global_f->define("cdr", make_primitive(eval_cdr));
  global_f->define("nullp", make_primitive(eval_nullp));
  global_f->define("eval", make_primitive(eval_eval));
  global_f->define("print", make_primitive(eval_print));
  global_f->define("not", make_primitive(eval_not));
  global_f->define("<", make_primitive(eval_less_than));
  global_f->define("apply", make_primitive(eval_apply));
  return env;
}

Env* env = init_env();
/**
 * functioin definitions
 */

Cell* eval(Cell* const c) {
  return optimized_eval(c);
}

Cell* optimized_eval(Cell* expr)
{
  /**
   *
   * to be done: tail recursive call optimization.
   * method used now: recursively calling eval,
   * return the value of evaluation.
   *
   */
  // while (true) {

  if (nullp(expr)) {
    throw runtime_error("cannot evaluate ().");
  }
  
  if (symbolp(expr)) {
    return env->lookup(get_symbol(expr));
  }
  
  if (!listp(expr)) {
    return expr->copy();
  }
  
  /**
   * other cases c must be a listp.
   */
  Cell* oper = car(expr);
  Cell* body = cdr(expr);
  
  /**
   * evaluate special form.
   */
  if (symbolp(oper)) {
    string form = get_symbol(oper);
    if (form == "if") {
      return optimized_eval(eval_if(body));
    }
    else if (form == "begin") {
      return optimized_eval(eval_begin(body));
    }
    else if (form == "define") {
      return eval_define(body);
    }
    else if (form == "quote") {
      return eval_quote(body);
    }
    else if (form == "lambda") {
      return eval_lambda(body);
    }
    else if (form == "let") {
      env->push((env->top_frame())->make_new_frame(nil, nil));
      try {
	expr = eval_let(body);
      }
      catch (runtime_error e) {
	env->pop();
	throw e;
      }
      env->pop();
      return expr;
    }
  }
  
  /**
   * evaluate combinations.
   */
  Cell* args = eval_each(body);
  Cell* proce = optimized_eval(oper);

  expr = apply(proce, args);
  //  if (!nullp(args)) delete args;
  //  if (!nullp(proce)) delete proce;
  return expr;
    // }
}

Cell* apply(Cell* proce, Cell* args) {
  Cell* expr = nil;
  if (is_primitive(proce)) {
    expr = proce->call(args);
    return expr;
  }
  else if (procedurep(proce)) {
    /**
     * Push a new frame whose parents
     * is the top frame currently in 
     * the env. Bind args to proce's 
     * formal parameter list.
     *
     */
    env->push((env->top_frame())->make_new_frame(get_formals(proce), args));

    try {
      expr = optimized_eval(get_body(proce));
    }
    catch (runtime_error e) {
      /**
       * pop previous calling stacks when
       * exceptions ocurr in user defined
       * functions. to make the calling
       * stack properly pop.
       *
       */
      env->pop();

      throw e;
    }
    env->pop();
    return expr;
  }
  else {
    throw runtime_error("cannot call a value that is not a function: " + proce->to_str());
  }
}

Cell* eval_each(Cell* expr) {
  if (nullp(expr)) {
    return nil;
  }
  else if (listp(expr)) {
    Cell* car_cell = optimized_eval(car(expr));    
    expr = cdr(expr);
    return cons(car_cell, eval_each(expr));
  }
  else {
    throw runtime_error("malformed expression.");
  }
}

Cell* eval_lambda(Cell* const c) {
  if (!check_form(c, 2)) {
    throw runtime_error("operator lambda expects at least two operands");
  }
  Cell* my_formals = (car(c))->copy();
  check_formals(my_formals);
  Cell* my_body = cons(make_symbol("begin"), (cdr(c))->copy());
  return lambda(my_formals, my_body);
}

void check_formals(Cell* formals) {
  if (!symbolp(formals)) {
    if (!listp(formals)) {
      throw runtime_error("malformed parameter list " + formals->to_str());
    }
    string* symbols = new string[len(formals)];
    int index = 0;
    string name;
    while (!nullp(formals)) {
      Cell* symbol = car(formals);
      if (!symbolp(symbol)) {
	delete [] symbols;
	throw runtime_error(symbol->to_str() + " cannot be a formal parameter.");
      }
      /**
       * Check if string name conflict
       * with names already in the formal
       * parameter list.
       * If so, throw an error.
       *
       */
      name = get_symbol(symbol);
      for(int i=0; i<index; ++i) {
	if (name == symbols[i]) {
	  delete [] symbols;
	  throw runtime_error("name conflict in formal parameter list: " + name);
	}
      }
      symbols[index] = name;
      ++index;
      formals = cdr(formals);
    }
    delete [] symbols;
  }
}

Cell* eval_begin(Cell* expressions) {
  Cell* result = car(expressions);
  while (!nullp(cdr(expressions))) {
    /**
     * if there are multiple expressions
     * in the function body, the return
     * values of them are trivial.
     * (except for the last one, which is
     * not gonna be evaluated).
     *
     */
    Cell* tmp = optimized_eval(car(expressions));
    if (!nullp(tmp)) delete tmp;
    expressions = cdr(expressions);
    result = car(expressions);
  }
  return result;
}

Cell* eval_if(Cell* c) {
  if (!check_form(c, 2, 3)) {
    throw runtime_error("operator if expects either two or three operands.");
  }
  int list_length = len(c);
  Cell* condition = optimized_eval(car(c));
  Cell* clause = cdr(c);
  if (!condition->truth()) {
    if (list_length == 2) {
      if (!nullp(condition)) delete condition;
      return nil;
    }
    else {
      if (!nullp(condition)) delete condition;
      return (car(cdr(clause)))->copy();
    }
  }
  else {
    if (!nullp(condition)) delete condition;
    return (car(clause))->copy();
  }
}

Cell* eval_quote(Cell* c) {
  if (!check_form(c, 1, 1)) {
    throw runtime_error("operator quote expects only one operand.");
  }
  return (car(c))->copy();
}

Cell* eval_define(Cell* c) {
  if (!check_form(c, 2, 2)) {
    throw runtime_error("operator define expects two operands.");
  }
  string name;
  if (symbolp(car(c))) {
    name = get_symbol(car(c));
  }
  else {
    throw runtime_error("cannot define non-symbol: " + (car(c))->to_str());
  }
  Cell* value = optimized_eval(car(cdr(c)));
  (env->top_frame())->define(name, value);
  return nil; 
}

Cell* eval_let(Cell* expr) {
  Cell* variables = car(expr);
  if (!listp(variables)) {
    throw runtime_error("unexpected expression in let form: " + variables->to_str());
  }
  while (!nullp(variables)) {
    Cell* var_pair = car(variables);
    if (nullp(var_pair) || !listp(var_pair)) {
      throw runtime_error("unexpected expression in let form: " + variables->to_str());
    }
    if (len(var_pair) != 2) {
      throw runtime_error("unexpected expression in let form: " + var_pair->to_str());
    }
    eval_define(var_pair);
    variables = cdr(variables);
  }
  Cell* expressions = cdr(expr);
  return optimized_eval(eval_begin(expressions));
}
