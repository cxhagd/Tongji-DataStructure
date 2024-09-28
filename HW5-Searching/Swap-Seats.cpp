class Solution {
public:
    int solve(std::vector<vector<std::string>>& old_chart, std::vector<std::vector<std::string>>& new_chart) {
        int sum = 0;
        int n = old_chart.size();//i
        int m = old_chart[0].size();//j 
 
        map<string, pair<int, int>> mp;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mp.insert({new_chart[i][j], { i, j }   });
            }
        }
 
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {//遍历表 
              while(old_chart[i][j] != new_chart[i][j]) {//在正确的表里面找到位置 
                    int x, y;
                    x = mp[old_chart[i][j]].first;
                    y = mp[old_chart[i][j]].second;
                  // pair<int ,int> {x, y } = mp[old_chart[i][j]];
 
                    swap(old_chart[x][y], old_chart[i][j]);
                    sum++;
                }
 
            }
        }
        return sum;
    }
};