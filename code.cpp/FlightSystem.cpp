#include "FlightSystem.h"



FlightSystem::FlightSystem()
{
}


FlightSystem::~FlightSystem()
{
}

////////////////////////////////////////////////
// 1. 加载航班数据
bool FlightSystem::LoadFromFile()
{
	// 打开文件准备读取
	ifstream in(FLIGHT_FILE, ios::binary | ios::in);
	if (!in.is_open())
	{
		cout << ("\t\t错误：读取航班数据文件失败！\n");
		in.close();
		return false;
	}

	m_Flights.clear();

	// 首先读取总的数量
	int nCount = 0;
	in >> nCount;

	// 然后循环读取所有航班信息
	for (int i = 0; i < nCount; i++)
	{
		FLIGHT newFlight;

		in >> newFlight.strFlightID;
		in >> newFlight.strCompany;
		in >> newFlight.strStartCity;
		in >> newFlight.strEndCity;
		in >> newFlight.strTransitCity;
		in >> newFlight.TakeoffTime.tm_hour;
		in >> newFlight.TakeoffTime.tm_min;
		in >> newFlight.LandingTime.tm_hour;
		in >> newFlight.LandingTime.tm_min;
		in >> newFlight.nPrice; 
		in >> newFlight.nTicket;		

		// 购票乘客
		int nGuest = 0;
		in >> nGuest;
		for (int j = 0; j < nGuest; j++)
		{
			GUEST newGuest;
			in >> newGuest.strID >> newGuest.strName >> newGuest.nCount;

			newFlight.Guests.push_back(newGuest);
		}
		
		// 等候乘客
		int nWGuest = 0;
		in >> nWGuest;
		for (int k = 0; k < nWGuest; k++)
		{
			GUEST newWGuest;
			in >> newWGuest.strID >> newWGuest.strName >> newWGuest.nCount;

			newFlight.WaitingGuests.push_back(newWGuest);
		}

		m_Flights.push_back(newFlight);
	}

	in.close();
	cout << "\t\t读取 " << nCount << " 个航班信息完毕." << endl;

	return true;
}

////////////////////////////////////////////////
// 2. 保存航班数据
bool FlightSystem::SaveToFile()
{
	// 如果没有记录则不进行处理
	if (!CheckFlightData()) return false;

	// 打开文件准备写入
	ofstream out(FLIGHT_FILE, ios::binary | ios::out | ios::trunc);
	if (!out.is_open())
	{
		cout << ("\t\t航班数据文件写入失败！\n");
		out.close();
		return false;
	}

	// 首先写入总的数量
	out << m_Flights.size() << endl;

	// 然后循环写入所有航班信息
	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		// 航班信息
		out << m_Flights[i].strFlightID << " " << m_Flights[i].strCompany << " " 
			<< m_Flights[i].strStartCity << " "	<< m_Flights[i].strEndCity << " "
			<< m_Flights[i].strTransitCity << " " 
			<< m_Flights[i].TakeoffTime.tm_hour << " " << m_Flights[i].TakeoffTime.tm_min << " "						
			<< m_Flights[i].LandingTime.tm_hour << " " << m_Flights[i].LandingTime.tm_min << " "
			<< m_Flights[i].nPrice << " " << m_Flights[i].nTicket
			<< endl;
		
		// 购票乘客
		GUESTS& guests = m_Flights[i].Guests;
		out << guests.size() << endl;
		for (unsigned int j = 0; j < guests.size(); j++)
		{
			out << guests[j].strID << " " << guests[j].strName << " " << guests[j].nCount << endl;
		}

		// 等候乘客
		WGUESTS& wguests = m_Flights[i].WaitingGuests;
		out << wguests.size() << endl;
		for (unsigned int k = 0; k < wguests.size(); k++)
		{
			out << wguests[k].strID << " " << wguests[k].strName << " " << wguests[k].nCount << endl;
		}
	}

	out.close();

	cout << "\t\t航班信息同步到 " << FLIGHT_FILE << " 中完毕." << endl;

	return true;
}

////////////////////////////////////////////////
// 3. 添加航班
void FlightSystem::AddFlight()
{
	FLIGHT newFlight;

	cout << "\t\t请输入航班号：";
	cin >> newFlight.strFlightID;

	cout << "\t\t请输入航班公司名称：";
	cin >> newFlight.strCompany;

	cout << "\t\t请输入航班起飞城市：";
	cin >> newFlight.strStartCity;

	cout << "\t\t请输入航班到达城市：";
	cin >> newFlight.strEndCity;

	cout << "\t\t请输入航班经停地点(没有就写“无”)：";
	cin >> newFlight.strTransitCity;

	cout << "\t\t请输入起飞时间(格式 15:05 分，24小时制，注意一定要用英文的冒号)：";
	scanf("%d:%d", &newFlight.TakeoffTime.tm_hour, &newFlight.TakeoffTime.tm_min);

	cout << "\t\t请输入到达时间(格式 16:10 分，24小时制，注意一定要用英文的冒号)：";
	scanf("%d:%d", &newFlight.LandingTime.tm_hour, &newFlight.LandingTime.tm_min);

	cout << "\t\t请输入航班票价：";
	cin >> newFlight.nPrice;

	cout << "\t\t请输入航班可售票数：";
	cin >> newFlight.nTicket;

	// 添加新的航班信息到顺序表中
	m_Flights.push_back(newFlight);

	cout << "\t\t添加航班信息成功！" << endl;

	SaveToFile();
}

///////////////////////////////////////////////
// 4. 删除航班
void FlightSystem::DelFlight()
{
	// 如果没有记录则不进行处理
	if (!CheckFlightData()) return;

	SearchAllFlights();

	char strID[STR_LEN] = { 0 };

	cout << "\t\t请输入你要删除的航班编号：";
	cin >> strID;

	// 查找对应的课程，进行删除
	vector<FLIGHT>::iterator itr = m_Flights.begin();
	while (itr != m_Flights.end())
	{
		if (strcmp(strID, itr->strFlightID) == 0)
		{
			m_Flights.erase(itr);

			cout << "\t\t删除航班信息成功！" << endl;

			SaveToFile();

			return;
		}
		else
		{
			++itr;
		}
	}

	cout << "\t\t没有找到此记录！" << endl;
	return;
}

///////////////////////////////////////////////
// 5. 修改航班
void FlightSystem::ModFlight()
{
	// 如果没有记录则不进行处理
	if (!CheckFlightData()) return;

	SearchAllFlights();

	char strID[STR_LEN] = { 0 };
	cout << "\t\t请输入你要修改的航班编号：";
	cin >> strID;

	// 查找对应的航班，进行修改
	int nIndex = GetFlightIndexByID(strID);

	if (nIndex < 0)
	{
		cout << "\t\t错误：没有找到此记录！" << endl;
		return;
	}

	// 进行记录修改
	FLIGHT& flight = m_Flights[nIndex];

	cout << "\t\t请输入航班号：";
	cin >> flight.strFlightID;

	cout << "\t\t请输入航班公司名称：";
	cin >> flight.strCompany;

	cout << "\t\t请输入航班起飞城市：";
	cin >> flight.strStartCity;

	cout << "\t\t请输入航班到达城市：";
	cin >> flight.strEndCity;

	cout << "\t\t请输入航班经停地点(没有就写“无”)：";
	cin >> flight.strTransitCity;

	cout << "\t\t请输入起飞时间(格式 15:05 分，24小时制，注意一定要用英文的冒号)：";
	scanf("%d:%d", &flight.TakeoffTime.tm_hour, &flight.TakeoffTime.tm_min);

	cout << "\t\t请输入到达时间(格式 16:10 分，24小时制，注意一定要用英文的冒号)：";
	scanf("%d:%d", &flight.LandingTime.tm_hour, &flight.LandingTime.tm_min);

	cout << "\t\t请输入航班票价：";
	cin >> flight.nPrice;

	cout << "\t\t请输入航班可售票数";
	cin >> flight.nTicket;

	cout << "\t\t修改航班信息成功！" << endl;

	SaveToFile();
}

///////////////////////////////////////////////
// 6. 发布延误取消通知
void FlightSystem::Delay()
{
	// 如果没有记录则不进行处理
	if (!CheckFlightData()) return;

	SearchAllFlights();

	char strID[STR_LEN] = { 0 };
	cout << "\t\t请输入您想要发布延误通知的航班号：";
	cin >> strID;

	int nFlightIndex = GetFlightIndexByID(strID);
	if (nFlightIndex < 0)
	{
		cout << "\t\t错误：没有找到此记录！" << endl;
		return;
	}

	FLIGHT& flight = m_Flights[nFlightIndex];

	// 计算推荐航班
	
	// 相差的分钟时间
	int nDiff = 9999;
	int nSelID = -1;
	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		if (i == nFlightIndex 
			|| strcmp(flight.strStartCity,m_Flights[i].strStartCity)!=0
			|| strcmp(flight.strEndCity, m_Flights[i].strEndCity) != 0)
		{
			continue;
		}

		int nTemp = (m_Flights[i].TakeoffTime.tm_hour - flight.TakeoffTime.tm_hour) * 60 + (m_Flights[i].TakeoffTime.tm_min - flight.TakeoffTime.tm_min);
		if (nTemp > 0 && nTemp < nDiff)
		{
			nDiff = nTemp;
			nSelID = i;
		}
	}

	// 通知本航班已经购票的乘客
	GUESTS::iterator it = flight.Guests.begin();
	for (; it != flight.Guests.end();it++)
	{
		if (nSelID >= 0)
		{
			cout << "\n\t\t尊敬的 " << it->strName << " 乘客，很抱歉的通知您：\n"
				<< " \t\t    您乘坐的 [" << flight.strFlightID << "] 航班，已经取消飞行，此处推荐您乘坐下一班 [" << m_Flights[nSelID].strFlightID << "]次 航班\n";
		}
		else
		{
			cout << "\n\t\t尊敬的 " << it->strName << " 乘客，很抱歉的通知您：\n" 
				 << "\t\t    您乘坐的 [" << flight.strFlightID << "] 航班，已经取消飞行，并且今日再无其他航班推荐，非常抱歉！\n";
		}
	}
}

//////////////////////////////////////////////
// 7. 购票申请
void FlightSystem::BuyTicket()
{
	// 如果没有记录则不进行处理
	if (!CheckFlightData()) return;

	SearchAllFlights();

	char strID[STR_LEN] = { 0 };
	cout << "\t\t请输入想要购票的航班号：";
	cin >> strID;

	int nFlightIndex = GetFlightIndexByID(strID);
	if (nFlightIndex < 0)
	{
		cout << "\t\t错误：没有找到此记录！" << endl;
		return;
	}

	FLIGHT& flight = m_Flights[nFlightIndex];

	int nBuyCount = 0;
	cout << "\t\t请输入想要购票的数量：";
	cin >> nBuyCount;

	// 余票充足则直接购买
	if (flight.nTicket > nBuyCount)
	{
		flight.nTicket -= nBuyCount;
		
		// 将当前用户信息保存
		GUEST newGuest;
		newGuest.nCount = nBuyCount;
		cout << "\t\t航空公司放票成功！" << endl;
		
		cout << "\t\t请输入您的姓名：";
		cin >> newGuest.strName;

		cout << "\t\t请输入您的身份证号：";
		cin >> newGuest.strID;

		flight.Guests.push_back(newGuest);

		// cout << "\t\t您已经成功预订 [" << flight.strFlightID << "] 航班的 " << nBuyCount << " 张票！\n" << endl;

		cout << "\t\t预订成功！订票信息如下：" << endl;
		cout << "\t\t    航班号：" << flight.strFlightID << endl;
		cout << "\t\t    姓  名：" << newGuest.strName << endl;
		cout << "\t\t    身份证：" << newGuest.strID << endl << endl;

		SaveToFile();

	}
	// 余票不足则进行预约排队
	else
	{
		int nWait = 0;

		cout << "\t\t该航班只剩余 " << flight.nTicket << " 张票，您是否要预约等待？(0.否  1.是)：";
		cin >> nWait;

		if (nWait == 0)
		{
			cout << "\t\t谢谢您的惠顾！" << endl;
			return;
		}

		// 加入等待队列

		GUEST newGuest;
		newGuest.nCount = nBuyCount;

		cout << "\t\t请输入您的姓名：";
		cin >> newGuest.strName;

		cout << "\t\t请输入您的身份证号：";
		cin >> newGuest.strID;

		flight.WaitingGuests.push_back(newGuest);

		cout << "\t\t您已经成功预约 [" << flight.strFlightID << "] 航班，一旦有余票会自动帮您下单.\n" << endl;

		SaveToFile();
	}

}

//////////////////////////////////////////////
// 8. 退票申请
void FlightSystem::RefundTicket()
{
	// 如果没有记录则不进行处理
	if (!CheckFlightData()) return;

	SearchAllFlights();

	char strID[STR_LEN] = { 0 };
	cout << "\t\t请输入想要退票的航班号：";
	cin >> strID;

	int nFlightIndex = GetFlightIndexByID(strID);
	if (nFlightIndex < 0)
	{
		cout << "\t\t错误：没有找到此记录！" << endl;
		return;
	}

	FLIGHT& flight = m_Flights[nFlightIndex];

	int nRefCount = 0;
	char strGuestID[STR_LEN] = { 0 };
	cout << "\t\t请输入您的身份证信息：";
	cin >> strGuestID;

	// 从当前航班的订票客人中移除此客人
	bool bFind = false;
	GUESTS::iterator it = flight.Guests.begin();
	for (; it!= flight.Guests.end();)
	{
		if (strcmp(it->strID, strGuestID) == 0)
		{
			cout << "\t\t尊敬的 " << it->strName << "客人，您的退票已经给您办理成功！\n" << endl;

			// 修改航班剩余票数
			flight.nTicket += it->nCount;
			it = flight.Guests.erase(it);

			bFind = true;

			break;
		}
		else
		{
			++it;
		}
	}

	if (!bFind)
	{
		cout << "\t\t错误：没有找到此客人的订票信息.\n" << endl;
		return;
	}

	// 为等待的客人自动订票
	while (flight.WaitingGuests.size()>0)
	{
		GUEST& wguest = flight.WaitingGuests.front();

		cout << "\t\t尝试为下一位预约客人 " << wguest.strName << " 自动订票............\n\n";

		// 查询余票是否足够
		cout << "\t\t目前航班剩余 " << flight.nTicket << " 张票，客人需要购买 " << wguest.nCount << "张." << endl;
		if (flight.nTicket >= wguest.nCount)
		{
			flight.nTicket -= wguest.nCount;

			cout << "\t\t订票成功！订票信息如下：" << endl;
			cout << "\t\t    航班号：" << flight.strFlightID << endl;
			cout << "\t\t    姓  名：" << wguest.strName << endl;
			cout << "\t\t    身份证：" << wguest.strID << endl << endl;

			// 将客人加入购票列表中
			GUEST newGuest;
			newGuest.nCount = wguest.nCount;
			strcpy(newGuest.strID, wguest.strID);
			strcpy(newGuest.strName, wguest.strName);

			flight.Guests.push_back(newGuest);

			// 从等待队列中移除此客人
			flight.WaitingGuests.pop_front();
		}
		else
		{
			cout << "\t\t该航班只剩余 " << flight.nTicket << " 张票，无法继续自动订票.\n\n";
			break;
		}
	}

	SaveToFile();

}

/////////////////////////////////////////////
// 9. 按航班号查询
void FlightSystem::SearchByFlight()
{
	// 如果没有记录则不进行处理
	if (!CheckFlightData()) return;

	// 查询条件
	char strID[STR_LEN] = { 0 };
	cout << "\t\t请输入想要查询的航班号：";
	cin >> strID;

	// 显示排序结果
	cout << ("\t\t查询结果如下：") << endl << endl;

	// 先显示标题
	cout << "\t\t";
	cout << setw(15) << "航班号";
	cout << setw(15) << "起点城市";
	cout << setw(15) << "终点城市";
	cout << setw(15) << "起飞时间";
	cout << setw(15) << "到达时间";
	cout << setw(10) << "票价";
	cout << setw(10) << "余票";
	cout << endl;

	// 根据查询条件进行查找
	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		bool bFind = false;

		FLIGHT flight = m_Flights[i];

		if (strcmp(strID, flight.strFlightID) == 0)
		{
			cout << "\t\t";
			cout << setw(15) << flight.strFlightID;
			cout << setw(15) << flight.strStartCity;
			cout << setw(15) << flight.strEndCity;
			cout << setw(12) << flight.TakeoffTime.tm_hour << ":" << flight.TakeoffTime.tm_min;
			cout << setw(12) << flight.LandingTime.tm_hour << ":" << flight.LandingTime.tm_min;
			cout << setw(10) << flight.nPrice;
			cout << setw(10) << flight.nTicket;
			cout << endl;
		}
	}

}

/////////////////////////////////////////////
// 10. 按起降地点查询
void FlightSystem::SearchByAddress()
{
	// 如果没有记录则不进行处理
	if (!CheckFlightData()) return;

	// 查询条件
	char strStart[STR_LEN] = { 0 };
	char strEnd[STR_LEN] = { 0 };
	
	cout << "\t\t请输入想要查询的出发城市：";
	cin >> strStart;

	cout << "\t\t请输入想要查询的终点城市：";
	cin >> strEnd;

	// 先获取查询结果数量
	int nResultCount = 0;
	unsigned int i = 0, j = 0;
	for (i = 0; i < m_Flights.size(); i++)
	{
		bool bFind = false;

		FLIGHT flight = m_Flights[i];

		if (strcmp(strStart, flight.strStartCity) == 0
			&& strcmp(strEnd, flight.strEndCity) == 0)
		{
			nResultCount++;
		}
	}

	// 选择排序方式
	SORT_TYPE SortType = SORT_NORMAL;
	if (nResultCount < 0)
	{
		cout << "\t\t没有找到对应的航班！" << endl;
		return;
	}
	else if (nResultCount == 0)
	{
		SortType = SORT_NORMAL;
	}
	else
	{
		cout << "\t\t查询到多条结果，请选择排序方式 (0.默认  1.按票价  2.按飞行时间  3.按余票数量)：";
		cin >> (int&)SortType;
	}

	// 根据不同的排序方式首先排序
	for (j = 0; j < m_Flights.size(); j++)
	{
		for (unsigned int k = 0; k < m_Flights.size(); k++)
		{
			bool bNeedExchange = false;

			if (SortType == SORT_BY_PRICE)
			{
				if (m_Flights[k].nPrice > m_Flights[j].nPrice)
				{
					bNeedExchange = true;
				}
			}
			else if(SortType==SORT_BY_TIME)
			{
				// 计算飞行时间
				int nTimeK = (m_Flights[k].LandingTime.tm_hour - m_Flights[k].TakeoffTime.tm_hour) * 60 +
					(m_Flights[k].LandingTime.tm_min - m_Flights[k].TakeoffTime.tm_min);

				int nTimeJ = (m_Flights[j].LandingTime.tm_hour - m_Flights[j].TakeoffTime.tm_hour) * 60 +
					(m_Flights[j].LandingTime.tm_min - m_Flights[j].TakeoffTime.tm_min);

				if (nTimeK > nTimeJ)
				{
					bNeedExchange = true;
				}

			}
			else if( SortType==SORT_BY_TICKET)
			{
				if (m_Flights[k].nTicket > m_Flights[j].nTicket)
				{
					bNeedExchange = true;
				}
			}

			if (bNeedExchange)
			{
				FLIGHT temp;

				temp = m_Flights[j];
				m_Flights[j] = m_Flights[k];
				m_Flights[k] = temp;
			}
		}
	}

	// 显示排序结果
	cout << ("\t\t查询结果如下：") << endl << endl;

	// 先显示标题
	cout << "\t\t";
	cout << setw(15) << "航班号";
	cout << setw(15) << "起点城市";
	cout << setw(15) << "终点城市";
	cout << setw(15) << "起飞时间";
	cout << setw(15) << "到达时间";
	cout << setw(10) << "票价";
	cout << setw(10) << "余票";
	cout << endl;	

	// 根据查询条件进行查找
	for (i = 0; i < m_Flights.size(); i++)
	{
		bool bFind = false;

		FLIGHT flight = m_Flights[i];

		if (strcmp(strStart, flight.strStartCity) == 0
			&& strcmp(strEnd, flight.strEndCity) == 0)
		{
			cout << "\t\t";
			cout << setw(15) << flight.strFlightID;
			cout << setw(15) << flight.strStartCity;
			cout << setw(15) << flight.strEndCity;
			cout << setw(12) << flight.TakeoffTime.tm_hour << ":" << flight.TakeoffTime.tm_min;
			cout << setw(12) << flight.LandingTime.tm_hour << ":" << flight.LandingTime.tm_min;
			cout << setw(10) << flight.nPrice;
			cout << setw(10) << flight.nTicket;
			cout << endl;
		}
	}
}

/////////////////////////////////////////////
// 11. 查询所有航班
void FlightSystem::SearchAllFlights()
{
	// 如果没有记录则不进行处理
	if (!CheckFlightData()) return;

	cout << "\t\t" << "所有航班信息如下：\n" << endl;

	// 先显示标题
	cout << "\t\t-------------------------------------------------------------------------------------\n";
	cout << "\t";
	cout << setw(15) << "航班号";
	cout << setw(15) << "起点城市";
	cout << setw(15) << "终点城市";
	cout << setw(15) << "起飞时间";
	cout << setw(15) << "到达时间";
	cout << setw(10) << "票价";
	cout << setw(10) << "余票";
	cout << endl;

	// 显示所有航班记录
	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		bool bFind = false;

		FLIGHT flight = m_Flights[i];

		cout << "\t";
		cout << setw(15) << flight.strFlightID;
		cout << setw(15) << flight.strStartCity;
		cout << setw(15) << flight.strEndCity;
		cout << setw(12) << flight.TakeoffTime.tm_hour << ":" << flight.TakeoffTime.tm_min;
		cout << setw(12) << flight.LandingTime.tm_hour << ":" << flight.LandingTime.tm_min;
		cout << setw(10) << flight.nPrice;
		cout << setw(10) << flight.nTicket;
		cout << endl;
	}
	cout << "\t\t-------------------------------------------------------------------------------------\n\n";
}

///////////////////////////////////////////////
// 12. 查询所有购票信息
void FlightSystem::SearchAllTickets()
{
	// 如果没有记录则不进行处理
	if (!CheckFlightData()) return;

	cout << "\t\t" << "所有购票信息如下：\n" << endl;

	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		cout << "\t\t航班 [" << m_Flights[i].strFlightID << "] 购票信息" << endl;		

		// 购票乘客
		GUESTS& guests = m_Flights[i].Guests;
		cout << "\t\t  已购票乘客，共 " << guests.size() << " 人" << endl;		
		for (unsigned int j = 0; j < guests.size(); j++)
		{
			cout << "\t\t\t身份证号：" << guests[j].strID << "\t姓名：" << guests[j].strName << "\t购票数：" << guests[j].nCount << "张"<< endl;
		}
		
		// 等候乘客
		WGUESTS& wguests = m_Flights[i].WaitingGuests;
		cout << "\t\t  预约乘客，共 " << wguests.size() << " 人" << endl;
		for (j = 0; j < wguests.size(); j++)
		{
			cout << "\t\t\t身份证号：" << wguests[j].strID << "\t姓名：" << wguests[j].strName << "\t购票数：" << wguests[j].nCount << "张" << endl;
		}

		cout << endl;
	}
}

///////////////////////////////////////////////
// 检查航班数据是否有效
bool FlightSystem::CheckFlightData()
{
	if (m_Flights.size() <= 0)
	{
		cout << "\t\t错误：尚无航班数据！" << endl;
		return false;
	}

	return true;
}

//////////////////////////////////////////////
// 根据指定的航班号获取航班的索引
int FlightSystem::GetFlightIndexByID(const char* pID)
{
	int nIndex = -1;

	// 根据查询条件进行查找
	for (unsigned int i = 0; i < m_Flights.size(); i++)
	{
		bool bFind = false;

		FLIGHT flight = m_Flights[i];

		if (strcmp(pID, flight.strFlightID) == 0)
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}
