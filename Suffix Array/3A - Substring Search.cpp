
/*
* @Author: Zakaria
* @Date:   2023-03-14 14:13:23
* @Last Modified time: 2023-03-21 01:56:46
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

string s;
int n;

void Radix_sort(vector<pair<pair<int , int> , int> > &a)
{

	int n = a.size();

	{
		vector<int> cnt(n);
		for (auto x : a)
		{
			cnt[x.first.second]++;
		}

		vector<pair<pair<int , int> , int> > a_new(n);

		vector<int> pos(n);

		pos[0] = 0;

		for (int i = 1; i < n; i++)
		{
			pos[i] = pos[i - 1] + cnt[i - 1];
		}

		for (auto x : a)
		{
			int i = x.first.second;
			a_new[pos[i]] = x;
			pos[i]++;
		}

		a = a_new;
	}

	{
		vector<int> cnt(n);
		for (auto x : a)
		{
			cnt[x.first.first]++;
		}

		vector<pair<pair<int , int> , int> > a_new(n);
		vector<int> pos(n);

		pos[0] = 0;

		for (int i = 1; i < n; i++)
		{
			pos[i] = pos[i - 1] + cnt[i - 1];
		}

		for (auto x : a)
		{
			int i = x.first.first;
			a_new[pos[i]] = x;
			pos[i]++;
		}
		a = a_new;
	}
}

vector<int>Build_Suffixarray(string &s)
{
	s = s + "$";

	n = s.size();

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

	// Transition

	int k = 0;
	while ((1 << k) < n)
	{
		vector<pair<pair<int, int>, int> > a(n);

		for (int i = 0 ; i < n ; i++)
		{
			a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
		}

		//	sort(a.begin(), a.end());
		Radix_sort(a);

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
	return p;

}

void Solve()
{


	cin >> s;


	vector<int>suffixarray = Build_Suffixarray(s);


	int q;
	cin >> q;

	while (q--)
	{
		string pattern;
		cin >> pattern;

		int low = 0, high = n - 1;
		int ans = -1;

		while (low <= high)
		{
			int mid = (low + high) / 2;
			
			string temp = s.substr(suffixarray[mid], pattern.size());
			//	cout<<temp<<endl;
			if (pattern == temp)
			{
				ans = 0;
				cout<<"Yes"<<endl;
				break;
			}
			if(temp<pattern)
				low = mid + 1;
			else
				high = mid - 1;
		}

		if(ans)
		{
			cout<<"No"<<endl;
		}

		

	}


}

int main()
{

	ios::sync_with_stdio(false);
	cin.tie(0);

	int tt = 1;

//	cin >> tt;

	while (tt--)
	{

		Solve();
	}

	return 0;

}