/*************************************************
** 功能 : 先来先服务FCFS和短作业优先SJF进程调度算法
** 作者 : 2019Jibinquan
** 创建 : 2020-11-18 / 14:41
** 版权 : 431263064@qq.com
/**************************************************/

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#define ios ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define debug(a) cout << #a << " " << a << endl
using namespace std;
typedef long long ll;
const double pi = acos(-1);
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;
const int maxn = 100007;//1e5+7 
const ll mod = 1000000007;//1e9+7

struct proc {
	int id;
	int arr_tim;
	int sta_tim;
	int sev_tim;
	int end_tim;
	int turn_tim;
	double wit_tim;
	bool operator<(const proc& a) const
	{
		return sev_tim > a.sev_tim;
	}
}lis[maxn];

int n;
int Time;

/*----------------------------------*
		 Function Definition
*-----------------------------------*/

void inital()
{
	Time = 0;
	memset(lis, 0, sizeof(lis));
}

bool cmp(proc a, proc b)
{
	if (a.arr_tim != b.arr_tim) {
		return a.arr_tim < b.arr_tim;
	}
	else {
		return a.sev_tim < b.sev_tim;
	}
}

void input()
{
	cout << "请输入进程数：" << endl;
	cin >> n;
	cout << "请输入到达时间" << endl;
	for (int i = 1; i <= n; i++) {
		cin >> lis[i].arr_tim;
	}
	cout << "请输入服务时间:" << endl;
	for (int i = 1; i <= n; i++) {
		cin >> lis[i].sev_tim;
	}
	for (int i = 1; i <= n; i++) {
		lis[i].id = i;
	}
}

string sc[5];

string trans(int nu)
{
	stringstream ss;
	ss << nu;
	return ss.str();
}

void FCFS()
{
	sort(lis + 1, lis + 1 + n, cmp);
	queue<proc>que;
	queue<proc>ans;
	int zz = 1;
	int sk = 1;
	int run_tim = 0;
	proc runing;
	bool flag = 0;
	runing.arr_tim = -1;
	while (run_tim <= maxn - 7) {
		int tp = 0;
		while (lis[zz].arr_tim == run_tim) {
			sc[++tp] = "  进程" + trans(lis[zz].id) + "到达队列";
			que.push(lis[zz]);
			zz++;
		}
		if (runing.arr_tim != -1) {
			if (runing.end_tim == run_tim) {
				sc[++tp] = "  进程" + trans(runing.id) + "执行完毕";
				ans.push(runing);
				runing.arr_tim = -1;
				if (ans.size() == n) {
					flag = 1;
				}
			}
		}
		if (runing.arr_tim == -1) {
			if (que.size()) {
				runing = que.front();
				que.pop();
				runing.sta_tim = run_tim;
				runing.end_tim = runing.sta_tim + runing.sev_tim;
				runing.turn_tim = runing.end_tim - runing.arr_tim;
				runing.wit_tim = runing.turn_tim * 1.0 / runing.sev_tim;
				sc[++tp] = "  进程" + trans(runing.id) + "开始执行";
			}
		}
		if (tp) {
			cout << "时刻" << sk++ << ": " << run_tim << ": " << endl;
			for (int i = 1; i <= tp; i++) {
				cout << sc[i] << endl;
			}
			cout << endl;
		}
		if (flag) {
			cout << endl << "作业全部结束,执行顺序：" << endl << endl;
			double t_sum = 0, w_sum = 0;
			while (!ans.empty()) {
				proc nw = ans.front();
				ans.pop();
				cout << " 作业" << nw.id << ": " << " 到达时间：" << nw.arr_tim << " 开始时间：" << nw.sta_tim << " 运行时间：" << nw.sev_tim << " 结束时间：" << nw.end_tim << " 周转时间：" << nw.turn_tim << " 带权周转时间：" << nw.wit_tim << endl;
				t_sum += nw.turn_tim;
				w_sum += nw.wit_tim;
			}
			cout << endl << " 平均周转时间：" << t_sum / n << " 平均带权周转时间：" << w_sum / n << endl;
			break;
		}
		run_tim++;
	}
}

void SJF()
{
	sort(lis + 1, lis + 1 + n, cmp);
	priority_queue<proc>que;
	queue<proc>ans;
	int zz = 1;
	int sk = 1;
	int run_tim = 0;
	proc runing;
	runing.arr_tim = -1;
	bool flag = 0;
	while (run_tim <= maxn - 7) {
		int tp = 0;
		while (lis[zz].arr_tim == run_tim) {
			sc[++tp] = "  进程" + trans(lis[zz].id) + "到达队列";
			que.push(lis[zz]);
			zz++;
		}
		if (runing.arr_tim != -1) {
			if (runing.end_tim == run_tim) {
				sc[++tp] = "  进程" + trans(runing.id) + "执行完毕";
				ans.push(runing);
				runing.arr_tim = -1;
				if (ans.size() == n) {
					flag = 1;
				}
			}
		}
		if (runing.arr_tim == -1) {
			if (que.size()) {
				runing = que.top();
				que.pop();
				runing.sta_tim = run_tim;
				runing.end_tim = runing.sta_tim + runing.sev_tim;
				runing.turn_tim = runing.end_tim - runing.arr_tim;
				runing.wit_tim = runing.turn_tim * 1.0 / runing.sev_tim;
				sc[++tp] = "  进程" + trans(runing.id) + "开始执行";
			}
		}
		if (tp) {
			cout << "时刻" << sk++ << ": " << run_tim << ": " << endl;
			for (int i = 1; i <= tp; i++) {
				cout << sc[i] << endl;
			}
			cout << endl;
		}
		if (flag) {
			cout << endl << "作业全部结束,执行顺序：" << endl << endl;
			double t_sum = 0, w_sum = 0;
			while (!ans.empty()) {
				proc nw = ans.front();
				ans.pop();
				cout << " 作业" << nw.id << ": " << " 到达时间：" << nw.arr_tim << " 开始时间：" << nw.sta_tim << " 运行时间：" << nw.sev_tim << " 结束时间：" << nw.end_tim << " 周转时间：" << nw.turn_tim << " 带权周转时间：" << nw.wit_tim << endl;
				t_sum += nw.turn_tim;
				w_sum += nw.wit_tim;
			}
			cout << endl << " 平均周转时间：" << t_sum / n << " 平均带权周转时间：" << w_sum / n << endl;
			break;
		}
		run_tim++;
	}
}

void choose_Algorithm() 
{
	int op;
	cout << "请选择算法类别：0为FCFS，1为SJF,-1结束：" << endl;
	while (cin >> op) {
		if (op == 1) {
			cout << endl << "SJF算法：" << endl << endl;
			SJF();
			cout << endl << endl;
		}
		else if (op == 0) {
			cout << endl << "FCFS算法：" << endl << endl;
			FCFS();
			cout << endl << endl;
		}
		else if(op == -1) {
			break;
		}
		else {	
			cout << "指令错误！" << endl;
		}
		cout << "请选择算法类别：0为FCFS，1为SJF,-1结束：" << endl;
	}
}

/*----------------------------------*
		  Main Function
*-----------------------------------*/

int main()
{
	inital();
	input();
	choose_Algorithm();
	system("pause");
	return 0;
}
