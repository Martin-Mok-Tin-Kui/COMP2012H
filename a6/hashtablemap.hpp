#include <cstring>
using namespace std;

template <class Key, class T>
class hashtablemap
{
  typedef hashtablemap<Key, T>     Self;

public:
  typedef Key                key_type;
  typedef T                  data_type;
  typedef T                  mapped_type;
  typedef pair<const Key, T> value_type;
  typedef unsigned int       size_type;
  typedef int                difference_type;

public:
  /**
   * \class Node.
   * \brief A node for linked list.
   */
  struct Node {
    Node(value_type data, Node* next=NULL):
      value_m(data), next_m(next) {}
    Node(const Node& x):
      value_m(x.value_m), next_m(x.next_m) {}
    ~Node() {}
    Node& operator=(const Node& x) {
      value_m = x.value_m;
      next_m = x.next_m;
      return *this;
    }
    value_type value_m;
    Node* next_m;
  };
  /**
   * \class LinkedList.
   * \brief A listed list for separate chaining
   * in the hash table.
   */
  class LinkedList {
  public:
    LinkedList(): head_m(NULL) {}
    LinkedList(const LinkedList& x):
      head_m(NULL)
    {
      Node* node_it = x.head_m;
      Node* new_node = head_m;
      while (node_it != NULL) {	
	new_node = insert(new_node, node_it->value_m);
	node_it = node_it->next_m;	
      }
    }

    ~LinkedList() {
      _delete_all_nodes(head_m);
    }

    // delete all nodes from x to the end.
    void _delete_all_nodes(Node* x) {
      if (x == NULL) {
	return;
      }
      else {
	_delete_all_nodes(x->next_m);
	delete x;
	return;
      }
    }

    LinkedList& operator=(const LinkedList& x) {
      if (this != &x) {
	_delete_all_nodes(head_m);
	head_m = NULL;
	Node* new_node = head_m;
	Node* node_it = x.head_m;
	while (node_it != NULL) {
	  new_node = insert(new_node, node_it->value_m);
	  node_it = node_it->next_m;
	}
      }
      return *this;
    }

    void erase(Node* pos) {
      Node* node_it = head_m;
      // if the head's gonna be erased.
      if (pos == head_m) {
	head_m = head_m->next_m;
	delete node_it;
	return;
      }
      // find the previous node of pos.
      while (node_it && node_it->next_m != pos) {
	node_it = node_it->next_m;
      }
      // if node_it is not NULL.
      if (node_it) {
	node_it->next_m = pos->next_m;
	delete pos;
	return;
      }
      return;
    }

    bool empty() {
      return head_m == NULL;
    }
    
    // try to find key k, if found return that node,
    // else return the pos where it should be.
    pair<Node*, bool> find_key(const key_type& k) {
      // if k is less then head's key,
      // then return pos as NULL.

      if (head_m == NULL || k < head_m->value_m.first) {
	return pair<Node*, bool>(NULL, false);
      }
      // found in the head.
      else if (k == head_m->value_m.first) {
	return pair<Node*, bool>(head_m, true);
      }
      Node* curr = head_m;
      Node* next = head_m->next_m;
      while (next != NULL && next->value_m.first < k) {
	curr = next;
	next = next->next_m;
      }
      if (next && next->value_m.first == k) {
	return pair<Node*, bool>(next, true);
      }
      else {
	return pair<Node*, bool>(curr, false);
      }
    }
    
    // insert data after pos in the list. 
    // return the new node.
    Node* insert(Node* pos, value_type data) {
      // insert before head.
      if (pos == NULL) {
	head_m = new Node(data, head_m);
	return head_m;
      }
      else {
	Node* new_node = new Node(data, pos->next_m);
	pos->next_m = new_node;
	return new_node;
      }
    }
    
    Node* head_m;
  };

public:
  
  class iterator {
    public:
    typedef std::input_iterator_tag iterator_category;
    typedef pair<const Key, T>      value_type;
    typedef int                     difference_type;
    typedef value_type*             pointer;
    typedef value_type&             reference;

    friend class hashtablemap;
    
    // it's standard idiom to contain the map in iterator class.
    // though in this case, we don't actually need it.
    iterator(Self* map=NULL, Node* node=NULL): map_m(map), node_m(node) {}
    iterator(const iterator& x): map_m(x.map_m), node_m(x.node_m) {}
    
    iterator& operator=(const iterator& x) {
      // simple memberwise assignment.
      map_m = x.map_m;
      node_m = x.node_m;
      return *this;
    }
    
    bool operator==(const iterator& x) const {
      return (x.node_m == node_m);
    }

    bool operator!=(const iterator& x) const {
      return (node_m != x.node_m);
    }

    reference operator*() {
      return node_m->value_m;
    }
    
    pointer operator->() {
      return &(node_m->value_m);
    }

    iterator& operator++() {
      node_m = map_m->_successor(node_m);
      return *this;
    }

    // post ++, use sort of hack method,
    // pass a dummy int argument.
    iterator& operator++(int) {
      iterator ret(*this);
      node_m = map_m->_successor(node_m);
      return ret;
    }

  private:
    Self* map_m;
    Node* node_m;
  };

  class const_iterator {
    public:
    typedef std::input_iterator_tag  iterator_category;
    typedef const pair<const Key, T> value_type;
    typedef int                      difference_type;
    typedef value_type*              pointer;
    typedef value_type&              reference;

    friend class hashtablemap;
    
    // it's standard idiom to contain the map in iterator class.
    // though in this case, we don't actually need it.
    const_iterator(const Self* map=NULL, Node* node=NULL): map_m(map), node_m(node) {}
    const_iterator(const const_iterator& x): map_m(x.map_m), node_m(x.node_m) {}
    
    const_iterator& operator=(const const_iterator& x) {
      // simple memberwise assignment.
      map_m = x.map_m;
      node_m = x.node_m;
      return *this;
    }
    
    bool operator==(const const_iterator& x) const {
      return (x.node_m == node_m);
    }

    bool operator!=(const const_iterator& x) const {
      return (node_m != x.node_m);
    }

    reference operator*() {
      return node_m->value_m;
    }
    
    pointer operator->() {
      return &(node_m->value_m);
    }

    const_iterator& operator++() {
      node_m = map_m->_successor(node_m);
      return *this;
    }

    // post ++, use sort of hack method,
    // pass a dummy int argument.
    const_iterator& operator++(int) {
      const_iterator ret(*this);
      node_m = map_m->_successor(node_m);
      return ret;
    }

  private:
    const Self* map_m;
    Node* node_m;    
  };
  // typedef of iterator and const_iterator.
  // typedef _iterator<value_type, Self> iterator;
  // typedef _iterator<const value_type, const Self> const_iterator;

public:
  // default constructor to create an empty map
  hashtablemap(size_type m=503): 
    table_size(m), size_m(0)
  {
    table_m = new LinkedList[table_size];
  }

  // overload copy constructor to do a deep copy
  hashtablemap(const Self& x): 
    table_size(x.table_size), size_m(x.size_m)
  {
    table_m = new LinkedList[table_size];
    // copy all elements from x.
    for (size_type i=0; i!=table_size; ++i) {
      table_m[i] = x.table_m[i];
    }
  }

  // destructor.
  ~hashtablemap() {
    delete [] table_m;
  }

  // overload assignment to do a deep copy
  Self& operator=(const Self& x) {
    // self assignment protection.
    if (this != &x) {
      delete [] table_m;
      table_size = x.table_size;
      size_m = x.size_m;
      table_m = new LinkedList[table_size];
      for (size_type i=0; i!=table_size; ++i) {
	table_m[i] = x.table_m[i];
      }
    }
    return *this;
  }

  // accessors:
  iterator begin() {
    return iterator(this, _get_first_elem());
  }
  const_iterator begin() const {
    return const_iterator(this, _get_first_elem());
  }
  iterator end() {
    return iterator(this, NULL);
  }
  const_iterator end() const {
    return const_iterator(this, NULL);
  }
  bool empty() const {
    return size_m == 0;
  }
  size_type size() const {
    return size_m;
  }

  // insert/erase
  pair<iterator,bool> insert(const value_type& x) {
    // first try to find the key.
    size_type i = _hash_func(x.first);
    pair<Node*, bool> ret = _find(x.first, i);
    if (ret.second) {
      // the key's already in the map.
      return pair<iterator, bool>(iterator(this, ret.first), false);
    }
    else {
      // else insert x in table_m[i] bucket.
      ++size_m;
      Node* new_node = table_m[i].insert(ret.first, x);
      return pair<iterator, bool>(iterator(this, new_node), true);
    }
  }

  void erase(iterator pos) {
    key_type k = pos->first;
    size_type i = _hash_func(k);
    pair<Node*, bool> ret = _find(k, i);
    if (ret.second) {
      table_m[i].erase(ret.first);
      --size_m;
    }
  }

  size_type erase(const Key& x) {
    // first find the key x.
    iterator it = find(x);
    if (it != end()) {
      // since we can only have
      // a key once, so just erase it;
      erase(it);
      return 1;
    }
    else {
      // the key's not found.
      return 0;
    }
  }
  
  void clear() {
    delete [] table_m;
    table_m = new LinkedList(table_size);
    size_m = 0;
  }

  // map operations:
  iterator find(const Key& x) {
    size_type i = _hash_func(x);
    pair<Node*, bool> ret = _find(x, i);
    if (ret.second) {
      return iterator(this, ret.first);
    }
    else {
      return iterator(this, NULL);
    }
  }
  
  const_iterator find(const Key& x) const {
    size_type i =_hash_func(x);
    pair<Node*, bool> ret = _find(x, i);
    if (ret.second) {
      return const_iterator(this, ret.first);
    }
    else {
      return const_iterator(this, NULL);
    }
  }

  size_type count(const Key& x) const {
    if (find(x) != end()) {
      return 1;
    }
    else {
      return 0;
    }
  }
  
  T& operator[](const Key& k) {
    // first try to find the key.
    iterator it = find(k);
    if (it != end()) {
      return it->second;
    }
    // if the key's not found,
    // insert it with default
    // init value;
    else {
      value_type x(k, T());
      pair<iterator, bool> ret = insert(x);
      return ret.first->second;
    }
  }

private:
  // hash function. currently only work for string.
  size_type _hash_func(const key_type& key) const {
    int seed = 1;
    int sum = 0;
    for (int i=key.length()-1; i>=0; --i) {
      int a = key[i];
      sum = (sum + (a*seed % table_size)) % table_size;
      seed *= 128;
    }
    // cout << key << " " << sum << endl;
    return sum;
  } 

  // find key x in the ith bucket.
  pair<Node*, bool> _find(const Key& x, size_type i) const {
    return table_m[i].find_key(x);
  }

  // find next elem, no need to consider
  // order of elements.
  Node* _successor(Node* elem) const {
    // if there's still data in the current bucket.
    if (elem && elem->next_m != NULL) {
      return elem->next_m;
    }
    // else find the next bucket that has elem.
    else if (elem && elem->next_m == NULL) {
      size_type i = _hash_func(elem->value_m.first) + 1;
      while (i < table_size && table_m[i].empty()) {++i;}
      if (i >= table_size) {
	return NULL;
      }
      else {
	return table_m[i].head_m;
      }
    }
    return NULL;
  }
  
  // get the first elem.
  Node* _get_first_elem() const {
    for (size_type i=0; i<table_size; ++i) {
      if (!table_m[i].empty()) {
	return table_m[i].head_m;
      }
    }
    return NULL;
  }

  LinkedList* table_m;
  size_type table_size, size_m;
};
