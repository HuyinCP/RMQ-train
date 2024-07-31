#include <bits/stdc++.h>
#define endl "\n"
#define all(x) x.begin(), x.end()
#define fastbuild ios::sync_with_stdio(false); cin.tie(0);
#define setpr(x) cout<<setprecision(x)<<fixed
using namespace std;
typedef long long ll;

const int MAXN = 505;
int dp[10][MAXN][10][MAXN];  // 10 là log2(MAXN)

void buildRMQ(int n, int m, int a[MAXN][MAXN]) {
    // Khởi tạo dp[jr][ir][jc][ic] với jr = 0 và jc = 0
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[0][i][0][j] = a[i][j];
        }
    }
    
    // Tạo RMQ 1D cho mỗi hàng
    for (int ir = 1; ir <= n; ir++) {
        for (int jc = 1; (1 << jc) <= m; jc++) {
            for (int ic = 1; ic + (1 << jc) - 1 <= m; ic++) {
                dp[0][ir][jc][ic] = min(dp[0][ir][jc - 1][ic], dp[0][ir][jc - 1][ic + (1 << (jc - 1))]);
            }
        }
    }

    // Tạo RMQ 1D cho mỗi cột từ dữ liệu RMQ của hàng
    for (int jr = 1; (1 << jr) <= n; jr++) {
        for (int ir = 1; ir + (1 << jr) - 1 <= n; ir++) {
            for (int jc = 0; (1 << jc) <= m; jc++) {
                for (int ic = 1; ic <= m; ic++) {
                    dp[jr][ir][jc][ic] = min(dp[jr - 1][ir][jc][ic], dp[jr - 1][ir + (1 << (jr - 1))][jc][ic]);
                }
            }
        }
    }
}

int queryRMQ(int x1, int y1, int x2, int y2) {
    int kx = __lg(x2 - x1 + 1);
    int ky = __lg(y2 - y1 + 1);
    int min1 = min(dp[kx][x1][ky][y1], dp[kx][x1][ky][y2 - (1 << ky) + 1]);
    int min2 = min(dp[kx][x2 - (1 << kx) + 1][ky][y1], dp[kx][x2 - (1 << kx) + 1][ky][y2 - (1 << ky) + 1]);
    return min(min1, min2);
}

int main() {
    fastbuild;
    int n, m;
    cin >> n >> m;
    int a[MAXN][MAXN];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    buildRMQ(n, m, a);

    int Query;
    cin >> Query;
    while (Query--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << queryRMQ(x1, y1, x2, y2) << endl;
    }

    return 0;
}
