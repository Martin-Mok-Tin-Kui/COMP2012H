/**
 * \file frame.hpp
 * 
 * Interface of the frames for micro-scheme interpreter. The runtime stack
 * for the interpreter.
 */

#ifndef FRAME_HPP
#define FRAME_HPP

#include <map>
#include <string>
#include "Cell.hpp"

/**
 * \class Frame
 * \brief frame of runtime stack.
 */
class Frame {
private:
  Frame* parent;
  std::map<std::string, Cell*> bindings;
public:
  /**
   * \brief Constructor.
   */
  Frame (Frame* parent_frame=NULL);

  /**
   * \brief Destructor.
   */
  ~Frame ();
  
  /**
   * \brief Make a new frame for calling user defined function,
   * bind all arguments to the formal parameters in the new frame.
   * (error if the number of args doesn't equal to number of formals).
   * \return Pointer to the new frame.
   */
  Frame* make_new_frame(Cell* formals, Cell* args);

  /**
   * \brief Look up the value bound to the name from current
   * frame and its parent frame along to the global frame.
   * (error if no value bound to the name).
   * \return the Cell bound to the name.
   */ 
  Cell* look_up(std::string name);

  /**
   * \brief Bind value to the name in the current frame's
   * binding table. (error if the name is already bound to sth).
   */
  void define(std::string name, Cell* value);
};

/**
 * \class FrameList.
 * \brief A linked list to implement the stack of frames.
 */
struct FrameList {
  Frame* current;
  FrameList* prev;
  FrameList(Frame* new_current, FrameList* new_prev): current(new_current), prev(new_prev) {}
  ~FrameList() {delete current;}
};

/**
 * \class Env
 * \brief The runtime stack.
 */
class Env {
private:
  /**
   * the top of the stack, 
   * use a linked list to
   * record other elements 
   * in the stack.
   */
  FrameList* top;
  int max_depth;
  int size;

public:
  /**
   * \brief Constructor.
   */
  Env();

  /**
   * \brief Destructor.
   */
  ~Env();
  
  /**
   * \brief Pop the current frame from the stack.
   */
  void pop();
  
  /**
   * \brief Push a new frame into the stack.
   */
  void push(Frame* new_frame);

  /**
   * \brief Look for the name from the current frame and its 
   * parent frames. (error if the name binds to no value).
   * \return The value bound to the name.
   */
  Cell* lookup(std::string name) const;

  /**
   * \brief The top frame in the stack.
   * \return Current frame of top.
   */
  Frame* top_frame() const;

};

#endif // FRAME_HPP
