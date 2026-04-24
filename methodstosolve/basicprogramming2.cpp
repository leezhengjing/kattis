#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

template <typename T> vector<T> get_words() {
  string line;
  getline(std::cin, line);
  istringstream ss{line};
  ss >> boolalpha;
  vector<T> v;
  copy(istream_iterator<T>{ss}, istream_iterator<T>{}, back_inserter(v));
  return v;
}

template <typename T> void put_words(const vector<T> &v) {
  if (!v.empty()) {
    copy(v.begin(), prev(v.end()), ostream_iterator<T>{cout, " "});
    cout << v.back();
  }
  cout << '\n';
}

void solve() {
  int N, t;
  cin >> N >> t;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vi arr = get_words<int>();
  sort(arr.begin(), arr.end());
  if (t == 1) {
    int left = 0;
    int right = N - 1;
    while (left < right) {
      if (arr[left] + arr[right] == 7777) {
        cout << "Yes" << endl;
        return;
      } else if (arr[left] + arr[right] < 7777) {
        ++left;
      } else if (arr[left] + arr[right] > 7777) {
        --right;
      }
    }
    cout << "No" << endl;
    return;

  } else if (t == 2) {
    bool unique = true;
    for (int i = 0; i < N - 1; ++i) {
      if (arr[i] == arr[i + 1]) {
        unique = false;
        break;
      }
    }
    if (unique)
      cout << "Unique" << endl;
    else
      cout << "Contains duplicate" << endl;
  } else if (t == 3) {
    int possible = arr[N / 2];
    int count = 0;
    for (auto x : arr) {
      if (x == possible)
        count++;
    }
    if (count > N / 2)
      cout << possible << endl;
    else
      cout << -1 << endl;

  } else if (t == 4) {
    int first_median = arr[(N - 1) / 2];
    int second_median = arr[N / 2];
    if (N % 2 == 0) {
      cout << first_median << " " << second_median << endl;
    } else {
      cout << first_median << endl;
    }

  } else {
    bool first = true;
    for (int i = 0; i < N; ++i) {
      if (arr[i] >= 100 && arr[i] <= 999) {
        if (first) {
          cout << arr[i];
        } else {
          cout << " " << arr[i];
        }
        first = false;
      }
    }
    cout << endl;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (t--) {
    // code here
    solve();
  }

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
