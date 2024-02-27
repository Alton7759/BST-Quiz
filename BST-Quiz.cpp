/*******************************************************************************
** CPSC 131: Part 4 - Associative Containers
**           Binary Search Tree Quiz
**
** Implement the Binary Search Tree code asked for in each question (TO-DO) below.
**
** While the solutions to the questions below are highly inspired by the implementation
** examples presented in class, they will not be identical.  Read the questions carefully.
*******************************************************************************/


#include <utility>
#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>




template<typename Key, typename Value>
struct BST
{
  using KeyValue_Pair = std::pair<Key const, Value>;

  struct Node
  {
    Node() = default;
    Node( KeyValue_Pair const & pair ) : _pair{ pair } {}

    KeyValue_Pair _pair = { Key{}, Value{} };

    Node * _left   = nullptr;
    Node * _right  = nullptr;
    Node * _parent = nullptr;
  };

  Node *      _root = nullptr;
  std::size_t _size = 0;



  /*****************************************************************************
  ** Implement the BST's find function
  **   1)  find takes a key as its only argument and returns a pointer to the node containing that key
  **   2)  Write a recursive solution (not an iterative solution  Hint:  no while or for loops)
  **       o)  Write both the "public" and "private helper" functions
  **       o)  Clearly identify the Base Case, Visit, and Recurse steps  Hint:  write comments for each
  **           step before writing code
  *****************************************************************************/
  Node * find( Key const & key )
  {
    ///////////////////////// TO-DO (1) //////////////////////////////
    return find(key,_root);
    /////////////////////// END-TO-DO (1) ////////////////////////////
  }


  Node * find( Key const & key, Node * current )
  {
    ///////////////////////// TO-DO (2) //////////////////////////////
    auto checker = (key <=> current->_pair.first);
    if(current == nullptr) return nullptr;
    if(checker == 0) return current;
    else if (checker < 0) return find(key,current->_left);
    else return find(key,current->_right);
    /////////////////////// END-TO-DO (2) ////////////////////////////
  }



  /*****************************************************************************
  ** Implement the BST's insert function
  **   1)  Insert takes a key-value pair as its only argument and returns a pointer to the
  **       node containing that key
  **   2)  Write an iterative solution (not a recursive solution)
  *****************************************************************************/
  Node * insert( KeyValue_Pair const & pair )
  {
    ///////////////////////// TO-DO (3) //////////////////////////////
  Node * current = _root;
  Node * parent = nullptr;
  Node ** child = &_root;
  while (current != nullptr)
  {
    auto checker = (pair.first <=> current->_pair.first);
    if(checker == 0) return current;
    parent = current;
    if(checker < 0) child = &current->_left, current = current->_left;
    else child = &current->_right, current = current->_right;
  }
  Node * newNode = new Node(pair);
  newNode->_parent = parent;
  *child = newNode;
  ++_size;
  return newNode;
    /////////////////////// END-TO-DO (3) ////////////////////////////
  }



  /*****************************************************************************
  ** Implement the BST's erase function
  **   1)  Erase takes a key as its only argument and returns nothing
  **   2)  Write an iterative solution (not a recursive solution)
  **   3)  Assume the node you are erasing does NOT have two children.  Do not write code
  **       to erase a node with two children.
  *****************************************************************************/
  void erase( Key const & key )
  {
    ///////////////////////// TO-DO (4) //////////////////////////////
    Node * position_ptr = find(key);
    Node ** parent = position_ptr->_parent == nullptr ? &_root : position_ptr->_parent->_left == position_ptr ? &position_ptr->_parent->_left : &position_ptr->_parent->_right; 
    Node * child = position_ptr->_left == nullptr ? position_ptr->_right : position_ptr->_left;
    *parent = child;
    if(child) child->_parent = position_ptr->_parent;
    delete position_ptr;
    --_size;
    /////////////////////// END-TO-DO (4) ////////////////////////////
  }



  /*****************************************************************************
  ** Implement the BST's index operator function
  **   1)  operator[] takes a key as its only argument and returns a reference to the
  **       value associated with that key
  **   2)  If the key does not already exist, insert it
  *****************************************************************************/
  Value & operator[]( Key const & key )
  {
    ///////////////////////// TO-DO (5) //////////////////////////////
    return insert({key, Value{}})->_pair.second;
    /////////////////////// END-TO-DO (5) ////////////////////////////
  }


  void print()
  {
    unsigned count = 0;
    print( _root, count );
  }

  void print( Node * current, unsigned & count )
  {
    if( current == nullptr ) return;
    print( current->_left, count );

    auto && [key, value] = current->_pair;
    std::cout << std::setw(3) << ++count << ":  {" << key << ", " << value << "}\n";

    print( current->_right, count );
  }
};






int main()
{
  BST<unsigned int, std::string> myTree;

  std::cout << "Test Case 1:\n";                     //          50         //
  myTree[50] = "indeed";                             //        /   \        //
  myTree.insert( { 40, "Structures" } );             //       40    60      //
  myTree.insert( { 60, "very" } );                   //      / \   / \      //
  myTree.insert( { 30, "Lego" } );                   //     30 45 55  70    //
  myTree.insert( { 45, "are" } );
  myTree[55] = "truly";
  myTree[70] = "entertaining";
  myTree.print();
  std::cout << "------------------------------\n";

  std::cout << "\n\nTest Case 2:\n";                 //          50         //
  myTree.erase( 70 );                                //        /   \        //
  myTree[30] = "Data";                               //       40    55      //
  myTree.erase( 60 );                                //      / \     \      //
  myTree.insert( { 75, "awesome" } );                //     30 45     75    //
  myTree.insert( { 50, "never" } );
  myTree.print();
  std::cout << "------------------------------\n";
}
