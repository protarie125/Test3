#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vl = vector<ll>;

const auto& dx = vi{ -1,1,0,0 };
const auto& dy = vi{ 0,0,-1,1 };

int area;
void dfs(int m, int n, const vvb& f, vvb& isVisited, int x, int y) {
	++area;
	isVisited[y][x] = true;

	for (auto d = 0; d < 4; ++d) {
		const auto& nx = x + dx[d];
		const auto& ny = y + dy[d];

		if (nx < 0 || n <= nx ||
			ny < 0 || m <= ny) {
			continue;
		}

		if (f[ny][nx]) {
			continue;
		}

		if (isVisited[ny][nx]) {
			continue;
		}

		dfs(m, n, f, isVisited, nx, ny);
	}
}

vi solve(int m, int n, const vvb& f) {
	auto ret = vi{};
	auto isVisited = vvb(m, vb(n, false));
	for (auto y = 0; y < m; ++y) {
		for (auto x = 0; x < n; ++x) {
			if (f[y][x]) {
				continue;
			}

			if (isVisited[y][x]) {
				continue;
			}

			area = 0;
			dfs(m, n, f, isVisited, x, y);
			ret.push_back(area);
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int m, n, k;
	cin >> m >> n >> k;

	auto f = vvb(m, vb(n, false));
	while (0 < (k--)) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		for (auto r = y1; r < y2; ++r) {
			for (auto c = x1; c < x2; ++c) {
				f[r][c] = true;
			}
		}
	}

	auto ans = solve(m, n, f);

	sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (const auto& a : ans) {
		cout << a << ' ';
	}

	return 0;
}