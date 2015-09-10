#include <iostream>
#include "linkedlist.hpp"

int main(int argc, char** argv) {
  using namespace std;

  Node* mixed_list = make_node(make_int(1),NULL);
  Node* mixed_list_rev = make_node(make_int(1),NULL);
  Node* pos = mixed_list_rev;
  Node* pp = NULL;

  for (int i = 2; i <= 5; ++i) {
    list_insert_int(mixed_list, NULL, i);
    list_insert_int(mixed_list_rev, pos, i);
  }

  for (int i = 1; i <=5; ++i) {
    double d = i * 0.1;
    list_insert_double(mixed_list, NULL, d);
    list_insert_double(mixed_list_rev, pos, d);
  }

  for (char c = 'a'; c < 'f'; ++c) {
    char* str = new char[2];
    str[0] = c;
    str[1] = c;
    str[2] = '\0';
    if (c == 'b') 
      {pp = list_insert_symbol(mixed_list, NULL, str);}
    else 
      {list_insert_symbol(mixed_list, NULL, str);}
    list_insert_symbol(mixed_list_rev, pos, str);
  }
  
  // Get all the even positioned elements (head at 1) and delete them
  int size = list_size(mixed_list);

  cout << "Size of the list is " << size << endl;
  cout << *mixed_list << endl;
  cout << *mixed_list << endl;

  cout << "Size of the reverse list is " << size << endl;
  cout << *mixed_list_rev << endl;
  cout << *mixed_list_rev << endl << endl;

  // Write test cases for erase and ith
  
  pos = list_erase(mixed_list_rev, pos);
  cout << *mixed_list_rev << list_size(mixed_list_rev) << endl;
  pp = list_erase(mixed_list, pp);
  //test part.
  pp = mixed_list;
  pp = list_erase(mixed_list, pp);
  cout << *mixed_list << list_size(mixed_list) << endl;
  cout << *pp << endl;
  

  char s[] = "xyuaj";
  Node* new_list = make_node(make_symbol(s), NULL);
  list_insert_int(new_list, NULL, 123);
  list_insert_double(new_list, NULL, 2.54);
  s[1] = 't';
  list_insert_symbol(new_list, NULL, s);
  cout << *new_list << list_size(new_list) << endl;

  Node* pos2 = new_list;
  list_erase(new_list, pos2);
  list_insert(new_list, pos2, list_ith(mixed_list, 1));
  cout << *new_list << list_size(new_list) << endl;

  list_insert(new_list, pos2, NULL);
  cout << *new_list << list_size(new_list) << endl;
  list_insert_symbol(new_list, pos2, s);
  cout << *new_list << list_size(new_list) << endl;

  Node* empty_list = make_node(NULL, NULL);
  cout << *empty_list << list_size(empty_list) << endl;
  Node* elist = NULL;
  cout << *elist << list_size(elist) << endl;

  Node* only_node = make_node(make_symbol("yxy"), NULL);
  Node* onlyp = only_node;
  cout << *only_node << endl;
  list_insert_double(only_node, onlyp, 25.54);
  onlyp = list_insert_symbol(only_node, NULL, "abc");
  cout << *only_node << endl;
  onlyp = list_erase(only_node, onlyp);
  cout << *only_node << *onlyp << list_size(onlyp) << list_size(only_node) << endl;
  

  cout << *pos << endl;
  while (get_next(pos)) {
    pos = list_erase(mixed_list_rev, pos);
    cout << *mixed_list_rev << endl;
  }

  Node* test_list = make_node(make_symbol(")"), NULL);
  Node* test_pos = list_insert_symbol(test_list, NULL, "(");
  cout << *test_list << endl << *test_pos << endl;
  test_pos = list_insert(test_list, NULL, NULL);
  cout << *test_list << list_size(test_list) << endl;
  
  return EXIT_SUCCESS;
}

//tar -zcvf a0.tar.gz a0
