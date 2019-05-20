#ifndef dslist_h_
#define dslist_h_
// A simplified implementation of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  Node() : next_(NULL), prev_(NULL) {}
  Node(const T& v) : value_(v), next_(NULL), prev_(NULL) {}

  // REPRESENTATION
  T value_;
  Node<T>* next_;
  Node<T>* prev_;
};

// A "forward declaration" of this class is needed
template <class T> class dslist;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator(Node<T>* p=NULL) : ptr_(p) {}
  // NOTE: the implicit compiler definitions of the copy constructor,
  // assignment operator, and destructor are correct for this class

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->value_;  }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
    ptr_ = ptr_->next_;
    return *this;
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
    ptr_ = ptr_->next_;
    return temp;
  }
  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
    ptr_ = ptr_->prev_;
    return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    ptr_ = ptr_->prev_;
    return temp;
  }
  // the dslist class needs access to the private ptr_ member variable
  friend class dslist<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_; }
  bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_; }

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class dslist {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  // Checkpoint2: add end_ in initialization
  dslist() : head_(NULL), tail_(NULL), end_(NULL), size_(0) {}
  dslist(const dslist<T>& old) { copy_list(old); }
  dslist& operator= (const dslist<T>& old);
  ~dslist() { destroy_list(); }

  typedef list_iterator<T> iterator;

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { destroy_list(); }

  // read/write access to contents
  const T& front() const { return head_->value_;  }
  T& front() { return head_->value_; }
  const T& back() const { return tail_->value_; }
  T& back() { return tail_->value_; }

  // modify the linked list structure
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();

  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& v);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(end_); } // Checkpoint2

private:
  // private helper functions
  void copy_list(const dslist<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  Node<T>* end_; // Checkpoint2
  unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
dslist<T>& dslist<T>::operator= (const dslist<T>& old) {
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}

template <class T>
void dslist<T>::push_front(const T& v) {
  if (size_ == 0) push_back(v);
  else insert(head_);
}

template <class T>
void dslist<T>::pop_front() {
  erase(head_);
}

template <class T>
void dslist<T>::push_back(const T& v) {
  Node<T>* newp = new Node<T>(v);
  // special case: initially empty list
  if (!tail_) {
    head_ = tail_ = newp;
    // Checkpoint2: connect tail_ with end_
    end_ = new Node<T>();
    tail_->next_ = end_;
    end_->prev_ = tail_;
  } else {
    // normal case: at least one node already
    newp->prev_ = tail_;
    tail_->next_ = newp;
    tail_ = newp;
    // Checkpoint2: connect tail_ with end_
    tail_->next_ = end_;
    end_->prev_ = tail_;
  }
  ++size_;
}

template <class T>
void dslist<T>::pop_back() {
    erase(tail_);
}

// do these lists look the same (length & contents)?
template <class T>
bool operator== (dslist<T>& left, dslist<T>& right) {
  if (left.size() != right.size()) return false;
  typename dslist<T>::iterator left_itr = left.begin();
  typename dslist<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}

template <class T>
bool operator!= (dslist<T>& left, dslist<T>& right){ return !(left==right); }

template <class T>
typename dslist<T>::iterator dslist<T>::erase(iterator itr) {
  assert (size_ > 0);
  --size_;
  iterator result(itr.ptr_->next_);
  // One node left in the list.
  if (itr.ptr_ == head_ && head_ == tail_) {
    // Checkpoint2
    delete end_;
    head_ = tail_ = end_ = NULL;
  }
  // Removing the head in a list with at least two nodes
  else if (itr.ptr_ == head_) {
    head_ = head_->next_;
    head_->prev_ = NULL;
  }
  // Removing the tail in a list with at least two nodes
  else if (itr.ptr_ == tail_) {
    tail_ = tail_->prev_;
    // Checkpoint2: connect tail_ with end_
    tail_->next_ = end_;
    end_->prev_ = tail_;
  }
  // Normal remove
  else {
    itr.ptr_->prev_->next_ = itr.ptr_->next_;
    itr.ptr_->next_->prev_ = itr.ptr_->prev_;
  }
  delete itr.ptr_;
  return result;
}


template <class T>
typename dslist<T>::iterator dslist<T>::insert(iterator itr, const T& v) {
  ++size_ ;
  Node<T>* p = new Node<T>(v);
  p->prev_ = itr.ptr_->prev_;
  p->next_ = itr.ptr_;
  itr.ptr_->prev_ = p;
  if (itr.ptr_ == head_)
    head_ = p;
  else
    p->prev_->next_ = p;
  return iterator(p);
}


template <class T>
void dslist<T>::copy_list(const dslist<T>& old) {
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == 0) {
    head_ = tail_ = end_ = NULL;
    return;
  }
  // Create a new head node.
  head_ = new Node<T>(old.head_->value_);
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    tail_->next_ = new Node<T>(old_p->value_);
    tail_->next_->prev_ = tail_;
    tail_ = tail_->next_;
    old_p = old_p->next_;
  }
}

template <class T>
void dslist<T>::destroy_list() {
    while (this->begin() != iterator(NULL)) this->erase(this->begin());
}

#endif
