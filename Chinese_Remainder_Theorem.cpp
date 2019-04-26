#include <iostream>
using namespace std;

int gcdExtended(int a, int b, int &x, int &y)
{
	if(a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcdExtended(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return gcd;
}

int mmi(int a, int m)
{
	int x, y;
	int gcd = gcdExtended(a, m, x, y);
	if(gcd == 1)
		return (x % m + m) % m;
	else
		return -1;
}

int getMinX(int num[], int rem[], int n)
{
    int product = 1, result = 0;
    for(int i = 0; i < n; i++)
        product *= num[i];
    for(int i = 0; i < n; i++)
    {
        int p = product / num[i];
        result += rem[i] * mmi(p, num[i]) * p;
    }
    return result % product;
}

int main()
{
    int n;
    cin >> n;
    int arr[n], rem_arr[n];
    cout << "Enter First Array: ";
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    cout << "Enter Second Array: ";
    for(int i = 0; i < n; i++)
        cin >> rem_arr[i];
    cout << "X = " << getMinX(arr, rem_arr, n) << endl;
    return 0;
}
