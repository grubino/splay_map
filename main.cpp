#include "splay_tree.h"
#include "splay_map.h"

#include <ext/functional>
#include <utility>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include <ctime>
#include <cstdlib>

#include <string>
#include <iterator>

using namespace std;
using namespace __gnu_cxx;

template<class TreeType>
struct print_node {

  print_node(const TreeType& t)
    : m_tree(t) {}

  void operator() (typename TreeType::const_iterator it) {
    cout << setw(8 * m_tree.node_depth(it)) << it->first << ": " << it->second << endl;
  }

  const TreeType& m_tree;
  
};

template <class Pair>
void print_pair(Pair input) {
  cout << input.first << ": " << input.second << endl;
}

char random_char() {

  return (unsigned char) rand() % 26 + 65 + (rand() % 2) * 32;
  
}

string random_string(unsigned int len = 10) {

  string result(len, 0);
  generate(
	   result.begin()
	   , result.end()
	   , &random_char
	   );
  return result;
  
}

int main(void) {

  typedef _splay_tree<string
    , pair<string, string>
    , select1st<pair<string, string> >
    , less<string> > tree_type;
  
  tree_type t;

  srand(time(NULL));
  for(unsigned int i = 20; i > 0; --i) {
    t._M_insert_unique(make_pair(random_string(4), random_string(10)));
  }

  for(unsigned int i = 0; i < 20; ++i) {
    t._M_insert_unique(make_pair(random_string(4), random_string(10)));
  }

  unsigned int j = 0;
  for(
      tree_type::const_iterator it = t.begin()
	; it != t.end()
	; ++it, ++j
      ) {
    if(j == 23) {
      t.erase(it); break;
    }
  }

  print_node<tree_type> node_printer(t);
  for(tree_type::const_iterator it = t.begin(); it != t.end(); ++it) { node_printer(it); }

  typedef splay_map<string, string> example_map;

  example_map s_map;
  
  for(unsigned int i = 20; i > 0; --i) {
    s_map.insert(make_pair(random_string(), random_string()));
  }

  for(unsigned int i = 0; i < 20; ++i) {
    s_map.insert(make_pair(random_string(), random_string()));
  }
  
  srand(time(NULL));
  for_each(s_map.begin(), s_map.end(), &print_pair<example_map::value_type>);

  return 0;
  
}
