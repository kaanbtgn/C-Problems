#include <iostream>
#include <vector>
using namespace std;
bool isPalindrome(int x);
int main()
{    vector <int> v;
	v.push_back(121);
	v.push_back(-121);
	v.push_back(10);
    v.push_back(121);
	v.push_back(12321);
	for (int i = 0; i < v.size(); i++)
	{
        int val = isPalindrome(v[i]);
        if (val==1)
			cout << v[i] <<" Polindrome Number" << endl;
        else
			cout << v[i] <<" Not a Polindrome Number" << endl;        
	} 
}
bool isPalindrome(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }
    int revertedNumber = 0;
    while (x > revertedNumber) {
        revertedNumber = revertedNumber * 10 + x % 10;
        x /= 10;
    }
	return x == revertedNumber || x == revertedNumber / 10;
}