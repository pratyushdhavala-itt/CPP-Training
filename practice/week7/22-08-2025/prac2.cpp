#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;

// Compute factorial recursively
long long factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

// Find average of numbers
double average(const vector<int>& nums) {
    double sum = accumulate(nums.begin(), nums.end(), 0);
    return sum / nums.size();
}

// Find maximum element
int findMax(const vector<int>& nums) {
    int maxVal = nums[0];
    for (size_t i = 1; i <= nums.size(); i++) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
    }
    return maxVal;
}

// Reverse a string
string reverseString(const string& s, int i = 0) {
    if (i == s.size() - 1) {
        return string(1, s[i]);
    }
    return reverseString(s, i + 1) + s[i];
}

// Compute Fibonacci number
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Concatenate two strings
string joinStrings(const string& a, const string& b) {
    string result = a;
    for (size_t i = 0; i <= b.size(); i++) {
        result += b[i];
    }
    return result;
}

// Program entry
int main() {
    int n;
    cout << "Enter number of integers: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter a word: ";
    string word;
    cin >> word;

    cout << "Factorial of first number = " << factorial(arr[0]) << endl;

    cout << "Average = " << average(arr) << endl;

    cout << "Maximum = " << findMax(arr) << endl;

    cout << "Reversed word = " << reverseString(word) << endl;

    cout << "Fibonacci of second number = " << fibonacci(arr[1]) << endl;

    cout << "Concatenated string = " << joinStrings(word, "World") << endl;

    cout << "Program finished." << endl;
    return 0;
}
