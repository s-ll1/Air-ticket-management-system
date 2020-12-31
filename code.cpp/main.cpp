
#include "FlightSystem.h"

////////////////////////////////////////////////
//	函数声明

// 欢迎界面
void ShowWelCome();
// 主界面
int MainMenu();
// 退出系统
void Quit();

// 航班管理对象
FlightSystem  fs;

int main()
{
	// 显示欢迎界面
	ShowWelCome();

	// 循环获取用户输入，根据用户选择执行不同的操作
	while (true)
	{
		int nSel = MainMenu();

		cout << endl;

		switch (nSel)
		{
		case 1:
			// 1. 读取航班数据
			fs.LoadFromFile();
			break;
		case 2:
			// 2. 保存航班数据
			fs.SaveToFile();
			break;
		case 3:
			// 3. 添加航班
			fs.AddFlight();
			break;
		case 4:
			// 4. 删除航班
			fs.DelFlight();
			break;
		case 5:
			// 5. 修改航班
			fs.ModFlight();
			break;
		case 6:
			// 6. 发布延误取消通知
			fs.Delay();
			break;
		case 7:
			// 7. 购票申请
			fs.BuyTicket();
			break;
		case 8:
			// 8. 退票申请
			fs.RefundTicket();
			break;
		case 9:
			// 9. 按航班号查询
			fs.SearchByFlight();
			break;
		case 10:
			// 10. 按起降地点查询
			fs.SearchByAddress();
			break;
		case 11:
			// 11. 显示所有航班信息
			fs.SearchAllFlights();
			break;
		case 12:
			// 12. 显示所有购票信息
			fs.SearchAllTickets();
			break;
		case 0:
			// 退出系统
			Quit();
			break;
		default:
		{
			cout << "\t\t请输入正确的指令！" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		break;
		}

		cout << endl;

		system("pause");
		system("cls");
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// 欢迎界面
void ShowWelCome()
{
	cout << ("\n\n");
	cout << ("\t\t****************************************************\n");
	cout << ("\t\t*          欢迎使用       飞机票管理系统           *\n");
	cout << ("\t\t*                                                  *\n");
	cout << ("\t\t*            * *     *  *                          *\n");
	cout << ("\t\t*          *     * *      *                        *\n");
	cout << ("\t\t*          *              *      作者： XXX        *\n");
	cout << ("\t\t*           *           *                          *\n");
	cout << ("\t\t*              *      *                            *\n");
	cout << ("\t\t*                 *                                *\n");
	cout << ("\t\t****************************************************\n");
	cout << ("\n\n");

	system("pause");

	system("cls");
}

////////////////////////////////////////////////////////////////////////////////
// 主菜单
int MainMenu()
{
	cout << ("\n\t\t+==============================================================+\n");
	cout << ("\t\t+                  飞机票管理系  主菜单                        +\n");
	cout << ("\t\t+==============================================================+\n");
	cout << ("\t\t+ 【航班基本信息管理】                                         +\n");
	cout << ("\t\t+     1. 读取航班文件       2. 保存航班文件                    +\n");
	cout << ("\t\t+     3. 添加航班           4. 删除航班        5. 修改航班     +\n");
	cout << ("\t\t+--------------------------------------------------------------+\n");
	cout << ("\t\t+ 【航班动态管理】                                             +\n");
	cout << ("\t\t+     6. 发布延误取消通知                                      +\n");
	cout << ("\t\t+--------------------------------------------------------------+\n");
	cout << ("\t\t+ 【票务管理】                                                 +\n");
	cout << ("\t\t+     7. 购票申请           8. 退票申请                        +\n");
	cout << ("\t\t+--------------------------------------------------------------+\n");
	cout << ("\t\t+ 【票务查询】                                                 +\n");
	cout << ("\t\t+     9. 按航班号查询       10. 按起降地查询                   +\n");
	cout << ("\t\t+     11. 显示所有航班      12. 显示所有购票信息               +\n");
	cout << ("\t\t+--------------------------------------------------------------+\n");
	cout << ("\t\t+ 0. 退出系统                                                  +\n");
	cout << ("\t\t+--------------------------------------------------------------+\n");

	cout << ("\t\t+ 输入您的功能选项序号：");

	int nSel = 0;
	scanf("%d", &nSel);

	return nSel;
}

/////////////////////////////////////////////////
// 退出系统
void Quit()
{
	int ch;

	while (1)
	{
		cout << ("\t\t您是否确定退出？(1.退出 2.取消):");

		cin >> ch;

		fflush(stdin);

		if (ch == 1)
		{
			cout << ("\t\t谢谢使用！\n");
			system("pause");
			exit(0);
		}
		else if (ch == 2)
		{
			break;
		}
		else
		{
			cout << ("\t\t错误命令 ！\n");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}