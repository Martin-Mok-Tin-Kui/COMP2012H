/**
 * \file frame.cpp
 *
 * An implementation of the frame.hpp interface. Implement an calling
 * stack for the scheme interpreter, using dynamic scope.
 * An environment is a stack of frames. The top frame is the frame
 * being executed.
 * A frame has a symbol table, recording every name value pair. And is in
 * the scope of its parent frames. 
 * A frame can define and look up symbols.
 */

#include "frame.hpp"

using namespace std;

Frame::Frame(Frame* parent_frame):
  parent(parent_frame),
  bindings(map<string, Cell*>())
{}

Frame::~Frame() {
  map<string, Cell*>::iterator i;
  for (i=bindings.begin(); i!=bindings.end(); ++i) {
    if (i->second != nil) delete i->second;
  }
}

Frame* Frame::make_new_frame(Cell* formals, Cell* args) {
  /**
   * If formals is a symbol, then the
   * function accept arbitrary number
   * of arguments. Simply bind the arg
   * list to the parameter.
   */
  if (formals->is_symbol()) {
    Frame* new_frame = new Frame(this);
    new_frame->define(formals->get_symbol(), args);
    return new_frame;
  }
  /**
   *
   * First check if the number of arguments
   * given matches the number of formal
   * parameter required by formals.
   *
   */
  else if (formals->len() > args->len()) {
    throw runtime_error("too few arguments given");
  }
  else if (formals->len() < args->len()) {
    throw runtime_error("too many arguments given");
  }
  /**
   *
   * Make a new frame whose parent is 
   * this frame. Bind values in args
   * to corresponding parameters in
   * formals.
   *
   */
  Frame* new_frame = new Frame(this);
  while (formals != nil) {
    new_frame->define((formals->get_car())->get_symbol(), args->get_car());
    formals = formals->get_cdr();
    args = args->get_cdr();
  }
  return new_frame;
}

Cell* Frame::look_up(string name) {
  if (bindings.count(name)) {
    Cell* bound_value = bindings[name];
    return bound_value->copy();
  }
  else if (parent != NULL) {
    /**
     * continuously look up names
     * in the parent frame, until
     * reaching the global frame
     *
     */
    return parent->look_up(name);
  }
  else {
    throw runtime_error("undefined variable " + name);
  }
}

void Frame::define(string name, Cell* value) {
  if (bindings.count(name)) {
    throw runtime_error("cannot redefine symbol " + name);
  }
  else {
    bindings[name] = value;
  }
}

Env::Env(): 
  max_depth(500), size(1) 
{
  top = new FrameList(new Frame(), NULL);
}

Env::~Env() {
  while (top != NULL) {
    pop();    
  }
}

Cell* Env::lookup(string name) const {
  return (top->current)->look_up(name);
}

void Env::pop() {
  FrameList* tmp = top;
  top = top->prev;
  delete tmp;
  --size;
}

void Env::push(Frame* new_frame) {
  if (size >= max_depth) {
    throw runtime_error("maximum recursion depth exceeded.");
  }
  top = new FrameList(new_frame, top);
  ++size;
}

Frame* Env::top_frame() const {
  return top->current;
}
