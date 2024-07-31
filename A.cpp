#include <bits/stdc++.h>
#define endl "\n"
#define all(x) x.begin(), x.end()
#define Try_HCD signed
#define setpr(x) cout<<setprecision(x)<<fixed
#define fastbuild ios::sync_with_stdio(false);  cin.tie(0);
#define whatIs(x) cerr << "Line " << __LINE__ << ": " << #x << " = " << (x) << endl

typedef long long ll;
using namespace std;

/*
	dp[i][j]: số nhỏ nhất trong đoạn bắt đàu từ i, và có độ dài là 2^j
	với 1 đoạn bắt đầu từ i và có độ dài là 2^j
	thì:	
		ta chia làm 2 đoạn:
		đoạn 1: f[i][j-1] 
		đoạn 2: f[i + 1LL << (j-1)][j-1]
		ta thực hiện lấy min trong đoạn i có độ dài là 2^j:
		Công thức là: Lấy min(đoạn 1, đoạn 2)
			dp[i][j] = min( dp[i][j-1], dp[i + 1LL << (j-1)][j-1] )

	Trường hợp cơ sở: dp[1][0]: chính là a[i]: đoạn bắt đầu từ 1 có độ dài là 1
*/
const int MaxN = 2e6+7;
int dp[MaxN][22];


Try_HCD main()
{
    fastbuild

    int n, q; cin >> n >> q;
    int a[n+1];
    for(int i=1; i<=n; i++) cin >> a[i];

    for(int i=1; i<=n; i++) dp[i][0] = a[i];

    for(int j=1; (1<<j) <= n; j++) /* độ dài 2^j <= n */
    {				
    	for(int i=1; i + (1<<j) - 1 <= n; i++)
    	{
    		dp[i][j] = min(dp[i][j-1], dp[i + (1 << (j-1))][j-1]);
    	}
    }		

    while(q--)
    {
    	int l,r;
    	cin >> l >> r;
    	int x = __lg(r - l + 1);
    	cout << min(dp[l][x], dp[r - (1<<x) + 1][x]) << endl;
    }   
    return 0;
}