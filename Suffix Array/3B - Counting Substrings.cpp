/*
* @Author: Zakaria
* @Date:   2023-03-14 14:13:23
* @Last Modified time: 2023-03-21 01:56:38
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
const int N = mod;

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

string s;

vector<int>Build_Suffixarray(string s)
{
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

    // Transition

    int k = 0;
    while ((1 << k) < n)
    {
        vector<pair<pair<int, int>, int> > a(n);

        for (int i = 0 ; i < n ; i++)
        {
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        }

        //  sort(a.begin(), a.end());
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

vector<int>suffixarray;

int findleft(char c, int len, int l, int r, int n)
{
    int low = l, high = r;
    int ans = N;
   
    while(low<=high)
    {
        int mid = (low+high)/2;
        int pos = suffixarray[mid];

        if(pos+len>=n)
        {
            low = mid + 1;
        }
        else if(s[pos+len]>c)
            high = mid - 1;
        else if(s[pos+len]<c)
            low = mid + 1;
        else if(s[pos+len]==c)
        {
            ans = mid;
            high = mid - 1;
        }
    }

    return ans;
}

int findright(char c, int len, int l, int r, int n)
{
    int low = l, high = r;
    int ans = -1;
   
    while(low<=high)
    {
        int mid = (low+high)/2;
        int pos = suffixarray[mid];
        if(pos+len>=n)
        {
            low = mid + 1;
        }
        else if(s[pos+len]>c)
            high = mid - 1;
        else if(s[pos+len]<c)
            low = mid + 1;
        else if(s[pos+len]==c)
        {
            ans = mid;
            low = mid + 1;
        }
    }

    return ans;
}

void Solve()
{

    
    cin >> s;


    suffixarray = Build_Suffixarray(s);


    

    int q;
    cin>>q;

    while(q--)
    {
        string pattern ;
        cin>>pattern;

        int l = 0, r = suffixarray.size()-1;
        int len = 0;
        for(auto i:pattern)
        {
            int left = findleft(i, len, l, r, s.size());
            int right = findright(i, len, l, r, s.size());
            l = left;
            r = right;
            len++;
        }

        if(l==N || r==-1)
        {
            cout<<0<<endl;
        }
        else
            cout<<r-l+1<<endl;
    }

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