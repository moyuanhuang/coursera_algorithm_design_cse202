#include <iostream>
#include <string>
#include <vector>

using namespace std;

int edit_distance(const string &str1, const string &str2) {
	//write your code here
	if(str1.empty() or str2.empty())	return 0;
	vector<vector<int> > dp(str1.length()+1, vector<int>(str2.length()+1, 0));
	for(int i = 1; i <= str1.length(); ++i)
		dp[i][0] = dp[i-1][0] + 1;
	for(int i = 1; i <= str2.length(); ++i)
		dp[0][i] = dp[0][i-1] + 1;
	for(int i = 1; i <= str1.length(); ++i){
		for(int j = 1; j <= str2.length(); ++j){
			if(str1[i-1] == str2[j-1])
				dp[i][j] = min(min(dp[i-1][j-1], dp[i-1][j] +1), dp[i][j-1]+1);
			else
				dp[i][j] = min(min(dp[i-1][j-1] + 1, dp[i-1][j] +1), dp[i][j-1]+1);
		}
	}
	return dp[str1.length()][str2.length()];
}

int main() {
	string str1;
	string str2;
	std::cin >> str1 >> str2;
	std::cout << edit_distance(str1, str2) << std::endl;
	return 0;
}
