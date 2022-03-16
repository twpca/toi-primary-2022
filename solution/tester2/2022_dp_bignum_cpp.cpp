// O(n0 * n2) DP
// DP using Big int
// Expect: [AC, AC, ?]
#include<algorithm>
#include<vector>
#include<cstdio>
#include<cstring>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define FORD(x,y,z) for(int x=y;x>=z;x--)
#define MSET(x,y) std::memset(x,y,sizeof(x))
#define M 1005
using namespace std;
using i64 = long long;
struct BigNum
{
	int len,x[20];//digit/4
	bool minus;
	void print()
	{
		if(len==1 && x[0]==0)minus=false;
		if(minus)putchar('-');
		printf("%d", x[len-1]);
		FORD(i,len-2,0) printf("%04d", x[i]);
	}
	void reset()
	{
		len = 1;
		minus=false;
		MSET(x,0);
	}
	void clear_trash()
	{
		while (len>1 && !x[len-1])
			len--;
	}
	void str_change(char s[])
	{
		reset();
		len = strlen(s) / 4;
		int remain = strlen(s)%4, j=0;
		if (remain) len++;
		else remain = 4;
		REP(i,0,remain-1)
			x[len-1] = x[len-1]*10 + s[i]-'0';
		FORD(i,len-2,0)
		{
			sscanf(s+remain+j, "%04d", &x[i]);
			j+=4;
		}
		clear_trash();
	}
	void int_change(long long num)
	{
		reset();
		if (num==0) return;
		if(num<0)
		{
			minus=true;
			num=-num;
		}

		len = 0;
		while (num)
		{
			x[len++] = num%10000;
			num /= 10000;
		}
	}
	bool operator < (const BigNum &ag) const
	{
		if(minus ^ ag.minus)
		{
			if(minus) return true;
			return false;
		}
		if(minus)
		{
			if(len != ag.len) return len > ag.len;
			FORD(i,len-1,0)
				if (x[i] != ag.x[i])
					return x[i] > ag.x[i];
			return false;
		}
		else
		{
			if (len != ag.len) return len < ag.len;
			FORD(i,len-1,0)
				if (x[i] != ag.x[i])
					return x[i] < ag.x[i];
			return false;
		}
	}
	bool operator == (const BigNum &ag)
	{
		if (minus != ag.minus) return false;
		if (len != ag.len) return false;
		REP(i,0,len-1)
			if (x[i] != ag.x[i])
				return false;
		return true;
	}
	bool operator > (BigNum ag)
	{
		return ag < *this;
	}
	bool operator != (const BigNum &ag)
	{
		return !(*this==ag);
	}
	bool operator >= (const BigNum &ag)
	{
		return !(*this<ag);
	}
	bool operator <= (const BigNum &ag)
	{
		return !(*this>ag);
	}
	BigNum (){ reset(); }
	BigNum (int num){ int_change(num); }
	BigNum (long long num){ int_change(num); }
	BigNum (char s[]){ str_change(s); }
	BigNum operator + (BigNum ag)
	{
		BigNum ans;
		ans.reset();

		if(minus ^ ag.minus)
		{
			BigNum a = *this;

			if(a.minus)
			{
				a.minus = false;
				return ag-a;
			}
			else
			{
				ag.minus = false;
				return a-ag;
			}
		}

		int l = std::max(ag.len,len);
		REP(i,0,l-1)
		{
			ans.x[i] += x[i] + ag.x[i];
			if (ans.x[i] >= 10000)
			{
				ans.x[i+1]++;
				ans.x[i] -= 10000;
			}
		}
		if (ans.x[l]) l++;
		ans.len = l;
		ans.clear_trash();
		ans.minus=minus;

		return ans;
	}
	BigNum operator - (BigNum ag2)
	{
		BigNum ans;
		ans.reset();
		BigNum ag1=*this;

		if(minus ^ ag2.minus)
		{
			ag2.minus=!ag2.minus;
			return *this+ag2;
		}

		bool mm=ag1.minus;
		ag1.minus = ag2.minus = false;
		if(ag1<ag2)
		{
			swap(ag1,ag2);
			mm ^= 1;
		}

		int l = max(ag2.len, ag1.len);
		REP(i,0,l-1)
		{
			ans.x[i] += ag1.x[i] - ag2.x[i];
			if (ans.x[i] < 0)
			{
				ans.x[i] += 10000;
				ans.x[i+1]--;
			}
		}
		ans.len = l;
		ans.clear_trash();
		ans.minus = mm;
		return ans;
	}
};
int n, n0, n2, pw[2*M];
BigNum dp[M][M][11];
inline int m11(int x) { return (x % 11 + 11) % 11; }
void print(vector<char> &v) {
    for (char c: v) {
        printf("%c", c);
    }
    puts("");
}
int main()
{
    pw[0] = 1;
    REP(i,1,2*M-1) pw[i] = m11(pw[i-1] * 10);

    scanf("%d %d", &n0, &n2);
    n = n0 + n2;

    MSET(dp, -1);
    dp[0][0][0] = 1;
    for (int p=n; p>=1; p--) {
        int used = n - p + 1;
        REP(i, 0, min(n0, used)) {
            int j = used - i;
            if (j < 0 || j > n2) {
                continue;
            }

            REP(k,0,10) {
                dp[i][j][k] = 0;
                // 0
                if (i > 0 && dp[i-1][j][k] != -1) {
                    dp[i][j][k] = dp[i][j][k] + dp[i-1][j][k];
                }
                // 2
                int mod = m11(2 * pw[n-p]);
                int pre = m11(k - mod);
                if (j > 0 && dp[i][j-1][pre] != -1) {
                    dp[i][j][k] = dp[i][j][k] + dp[i][j-1][pre];
                }
            }
        }
    }

    if (dp[n0][n2][0] < 2) {
        puts("-1");
        return 0;
    }

    // 2nd biggest
    vector<char> ans;
    int i = n0;
    int j = n2;
    int k = 0;
    BigNum cnt = 2;
    while (i > 0 || j > 0) {
        int mod = m11(2 * pw[i+j-1]);
        int pre = m11(k - mod);
        if (j > 0 && dp[i][j-1][pre] >= cnt) {
            ans.push_back('2');
            j--;
            k = pre;
        } else {
            ans.push_back('0');
            if (j > 0) cnt = cnt - dp[i][j-1][pre];
            i--;
        }
    }
    print(ans);

    // 2nd smallest
    ans.clear();
    i = n0;
    j = n2;
    k = 0;
    cnt = 2;
    while (i > 0 || j > 0) {
        int mod = m11(2 * pw[i+j-1]);
        int pre = m11(k - mod);
        if (i > 0 && dp[i-1][j][k] >= cnt) {
            ans.push_back('0');
            i--;
        } else {
            ans.push_back('2');
            if (i > 0) cnt = cnt - dp[i-1][j][k];
            j--;
            k = pre;
        }
    }
    print(ans);
    return 0;
}
