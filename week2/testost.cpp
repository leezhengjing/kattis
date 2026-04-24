#include <iostream>
// Include the headers from the template above
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// --- Template Start ---
template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// --- Template End ---

int main() {
  ordered_set<int> os;

  // 1. Insert elements (acts like std::set, sorts automatically)
  // Insert: 1, 5, 10, 2, 8
  // Resulting Set: {1, 2, 5, 8, 10}
  os.insert(1);
  os.insert(5);
  os.insert(10);
  os.insert(2);
  os.insert(8);

  cout << "Set contains: {1, 2, 5, 8, 10}" << endl;

  // --- SUPERPOWER 1: find_by_order(k) ---
  // "What is the element at index k?" (0-indexed)
  // Returns an iterator, so use * to get value.

  cout << "Index 0: " << *os.find_by_order(0) << endl; // Output: 1
  cout << "Index 3: " << *os.find_by_order(3) << endl; // Output: 8

  // Safety check: if k >= size, it returns os.end()
  if (os.find_by_order(100) == os.end()) {
    cout << "Index 100 is out of bounds." << endl;
  }

  // --- SUPERPOWER 2: order_of_key(val) ---
  // "What index would 'val' be at?"
  // OR "How many elements are strictly smaller than 'val'?"

  cout << "Index of 8: " << os.order_of_key(8) << endl; // Output: 3
  cout << "Index of 2: " << os.order_of_key(2) << endl; // Output: 1

  // It works even for elements NOT in the set:
  // How many numbers are smaller than 7? {1, 2, 5} are smaller.
  cout << "How many elements < 7: " << os.order_of_key(7) << endl; // Output: 3

  // 3. Deletion
  os.erase(5); // Set is now {1, 2, 8, 10}
  cout << "After deleting 5, index 2 is now: " << *os.find_by_order(2)
       << endl; // Output: 8

  return 0;
}
