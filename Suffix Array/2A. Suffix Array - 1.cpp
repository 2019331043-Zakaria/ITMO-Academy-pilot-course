/*
* @Author: Zakaria
* @Date:   2023-03-14 14:13:23
* @Last Modified time: 2023-03-21 01:56:10
*/
#include <bits/stdc++.h>
#define  pb          push_back
#define  f           first
#define  s           second
#define  pi          acos(-1.0)
#define  LCM(a,b)    a*b/__gcd(a,b)
#define  GCD(a,b)    __gcd(a,b)
#define  sof         sizeof
#define  endl        '\n'
#define  eps         1e-6
typedef long long ll;
using namespace std;

const int mod = 1e9 + 7;
const int N = 2e5 + 6;

void Solve()
{

	string s;
	cin >> s;

	s = s + "$";

	int n = s.size();

	vector<int>p(n), c(n);

	// k = 0
	vector<pair<char, int> > a(n);

	for (int i = 0 ; i < n ; i++) a[i] = {s[i], i};

	sort(a.begin(), a.end());

	for (int i = 0 ; i < n ; i++) p[i] = a[i].second;

	c[p[0]] = 0;

	for (int i = 1 ; i < n ; i++)
	{
		if (a[i].first == a[i - 1].first)
			c[p[i]] = c[p[i - 1]];
		else
			c[p[i]] = c[p[i - 1]] + 1;
	}


	int k = 0;

	while ((1 << k) < n)
	{
		vector<pair<pair<int, int>, int> > a(n);

		for (int i = 0 ; i < n ; i++)
		{
			a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
		}

		sort(a.begin(), a.end());

		for (int i = 0 ; i < n ; i++) p[i] = a[i].second;

		c[p[0]] = 0;

		for (int i = 1 ; i < n ; i++)
		{
			if (a[i].first == a[i - 1].first)
				c[p[i]] = c[p[i - 1]];
			else
				c[p[i]] = c[p[i - 1]] + 1;
		}

		k++;

	}


	vector<int>suffixarray(n);
	suffixarray = p;

	for(auto i:suffixarray)
		cout<<i<<" ";
	cout<<endl;


}

int main()
{

	ios::sync_with_stdio(false);
	cin.tie(0);

	int tt = 1;

	//    cin>>tt;

	while (tt--)
	{

		Solve();
	}

	return 0;

}