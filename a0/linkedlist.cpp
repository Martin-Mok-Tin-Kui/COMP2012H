#include "linkedlist.hpp"

int list_size(const Node* n) {
  if (n == NULL) {
    return 0;
  }
  else if (get_elem(n)) {
    return list_size(get_next(n)) + 1;
  }
  else {
    return list_size(get_next(n));
  }
}

Cell* list_ith(Node* n, unsigned int i) {
  if (n == NULL && i >= 0) {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
  else if (get_elem(n) == NULL) {
    return list_ith(get_next(n), i);
  }
  else if (i == 0) {
    return get_elem(n);
  }
  else {
    return list_ith(get_next(n), i - 1);
  }
}

Node* list_erase(Node* n, Node* pos) {
  if (get_next(n) == NULL) {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
  else if (n == pos) {
    Node* next_node = get_next(n);
    if (get_elem(n) && symbolp(get_elem(n))) {
      free((n->elem_m)->symbol_m);
    }
    free(n->elem_m);
    n->elem_m = get_elem(next_node);
    n->next_m = get_next(next_node);
    free(next_node);
    return n;
  }
  else if (get_next(n) == pos) {
    n->next_m = get_next(pos);
    if (get_elem(pos) && symbolp(get_elem(pos))) {
      free((pos->elem_m)->symbol_m);
    }
    free(pos->elem_m);
    free(pos);
    return n->next_m;
  }
  else {
    return list_erase(get_next(n), pos);
  }
}

Node* list_insert(Node* n, Node* pos, Cell* c) {
  if (n == NULL) {
    std::cerr << "ERROR" << std::endl;
    exit(1);
  }
  else if (n == pos) {
    n->next_m = make_node(get_elem(n), get_next(n));
    n->elem_m = c;
    return n;
  }
  else if (get_next(n) == pos) {
    n->next_m = make_node(c, pos);
    return n->next_m;
  }
  else {
    return list_insert(get_next(n), pos, c);
  }
}

Node* list_insert_int(Node* n, Node* pos, const int value) {
  return list_insert(n, pos, make_int(value));
}

Node* list_insert_double(Node* n, Node* pos, const double value) {
  return list_insert(n, pos, make_double(value));
}

Node* list_insert_symbol(Node* n, Node* pos, const char* value) {
  return list_insert(n, pos, make_symbol(value));
}

