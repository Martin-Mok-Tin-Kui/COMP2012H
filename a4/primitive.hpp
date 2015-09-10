/**
 * \file primitive.hpp
 * 
 * Interface of all primitive scheme procedures, implementing natively in c++. 
 */

#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

/**
 * \brief Evaluation for operator +. Error if an operand doesn't evaluate to IntCell or DoubleCell.
 * \param c The root of the subtree following the + symbol.
 * \return The summation of result of evaluating each element in the c.
 * if no operands are given, return 0.
 */
Cell* eval_addition(Cell* c);

/**
 * \brief Evaluation for operator ceiling. Error if the operand doesn't evaluate to DoubleCell,
 * or more than one operands are passed in.
 * \param c The root of the subtree following the ceiling symbol.
 * \return The smallest integer that is greater than or equal to the result of evaluating the operand.
 */
Cell* eval_ceiling(Cell* c);

/**
 * \brief Evaluation for operator floor. Error if the operand doesn't evaluate to DoubleCell,
 * or more than one operands are passed in.
 * \param c The root of the subtree following the floor symbol.
 * \return The greatest integer that is less than or equal to the result of evaluating the operand.
 */
Cell* eval_floor(Cell* c);

/**
 * \brief Evaluation for operator *. Error if an operand doesn't evaluate to IntCell or DoubleCell.
 * \param c The root of the subtree following the * symbol.
 * \return The product of result of evaluating each element in the c.
 * if no operands are given, return 1.
 */
Cell* eval_multi(Cell* c);

/**
 * \brief Evaluation for operator /. Error if an operand doesn't evaluate to IntCell or DoubleCell,
 * or no operands are given.
 * \param c The root of the subtree following the / symbol.
 * \return If there's only one operand, return the inverse of the result of evaluating the operand.
 * Otherwise, Divide the first operand by the other operands.
 */
Cell* eval_divi(Cell* c);

/**
 * \brief Evaluation for operator -. Error if an operand doesn't evaluate to IntCell or DoubleCell,
 * or no operands are given.
 * \param c The root of the subtree following the - symbol.
 * \return If there's only one operand, return the negative of the result of evaluating the operand.
 * Otherwise, subtract other operands from the first operand.
 */
Cell* eval_subtra(Cell* c);

/**
 * \brief Evaluation for operator cons. Error if the number of operands is not two.
 * \param c The root of the subtree following the cons symbol.
 * \return A new ConsCell, with first element being the result of evaluating the first operand
 *  and second element being the result of evaluating the second operand.
 */
Cell* eval_cons(Cell* c);

/**
 * \brief Evaluation for operator car. Error if more than one operands are passed in,
 * or the operand doesn't evaluate to a valid list.
 * \param c The root of the subtree following the car symbol.
 * \return The first element of the result of evaluating the operand.
 */
Cell* eval_car(Cell* c);

/**
 * \brief Evaluation for operator cdr. Error if more than one operands are passed in,
 * or the operand doesn't evaluate to a valid list.
 * \param c The root of the subtree following the cdr symbol.
 * \return The second element of the result of evaluating the operand.
 */
Cell* eval_cdr(Cell* c);

/**
 * \brief Evaluation for operator nullp. Error if more than one operands are passed in.
 * \param c The root of the subtree following the nullp symbol.
 * \return IntCell with value 1, if the operand evaluates to nil, otherwise
 * return IntCell with value 0.
 */
Cell* eval_nullp(Cell* c);

/**
 * \brief Evaluation for operator eval. Error if more than one operands are passed in.
 * \param c The root of the subtree following the eval symbol.
 * \return result of evaluating the value of operand.
 */
Cell* eval_eval(Cell* c);

/**
 * \brief Evaluation for operator print. Error if more than one operands are passed in.
 * \param c The root of the subtree following the print symbol.
 * \return Print the value of the operand to standard output stream, return nil.
 */
Cell* eval_print(Cell* c);

/**
 * \brief Evaluation for operator not. Error if more than one operands are passed in.
 * \param c The root of the subtree following the not symbol.
 * \return One, if the operand evaluates to zero (either int or double), and zero otherwise.
 */
Cell* eval_not(Cell* c);

/**
 * \brief Evaluation for operator <. Error if an operand doesn't evaluate to IntCell or DoubleCell.
 * \param c The root of the subtree following the < symbol.
 * \return Zero if any two consecutive operands are not monotonically increasing, and one otherwise.
 */
Cell* eval_less_than(Cell* c);



Cell* eval_listp(Cell* c);

Cell* eval_symbolp(Cell* c);

Cell* eval_intp(Cell* c);

Cell* eval_nump(Cell* c);

#endif // PRIMITIVE_HPP
