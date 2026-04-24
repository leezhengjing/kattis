#include <iostream>
#include <map>
#include <string>

int main() {
  // 1. Create and populate a map (IDs mapped to Names)
  std::map<int, std::string> inventory;

  inventory[10] = "Apple";
  inventory[20] = "Banana";
  inventory[30] = "Cherry";
  inventory[40] = "Date";
  inventory[50] = "Elderberry";
  inventory[60] = "Fig";

  // --- A. Basic Iteration (C++17 Structured Binding) ---
  std::cout << "--- All Items ---\n";
  for (const auto &[id, name] : inventory) {
    std::cout << "ID: " << id << ", Name: " << name << "\n";
  }

  // --- B. Range Query: Items from 20 to 50 (Inclusive) ---
  // We want 20, 30, 40, 50.
  // lower_bound(20) points to 20.
  // upper_bound(50) points to 60 (the first item > 50).
  // The loop will run while it != 60.

  std::cout << "\n--- Range [20, 50] ---\n";

  auto it_low = inventory.lower_bound(20);
  auto it_up = inventory.upper_bound(50);

  for (auto it = it_low; it != it_up; ++it) {
    std::cout << "Found: " << it->first << " (" << it->second << ")\n";
  }

  // --- C. Using equal_range() ---
  // Useful if you need both bounds at once.
  // Let's check for ID 30.
  std::cout << "\n--- Equal Range for 30 ---\n";

  auto range = inventory.equal_range(30);

  // range.first is lower_bound, range.second is upper_bound
  if (range.first != inventory.end() && range.first->first == 30) {
    std::cout << "Element exists: " << range.first->second << "\n";
  }

  // Since this is a unique map, the distance between first and second is either
  // 0 or 1. In a std::multimap, this would print all duplicates of key 30.
  for (auto it = range.first; it != range.second; ++it) {
    std::cout << "Iterating equal_range: " << it->second << "\n";
  }

  return 0;
}
