#pragma once
#include "Common.h"

class FlightSystem
{
	
public:
	FlightSystem();
	~FlightSystem();
	
public:
	
	// 1. 加载航班数据
	bool LoadFromFile();
	// 2. 保存航班数据
	bool SaveToFile();
	
	// 3. 添加航班
	void AddFlight();
	// 4. 删除航班
	void DelFlight();
	// 5. 修改航班
	void ModFlight();
	
	// 6. 发布延误取消通知
	void Delay();
	
	// 7. 购票申请
	void BuyTicket();
	// 8. 退票申请
	void RefundTicket();
	
	// 9. 按航班号查询
	void SearchByFlight();
	// 10. 按起降地点查询
	void SearchByAddress();
	// 11. 查询所有航班
	void SearchAllFlights();
	// 12. 查询所有购票信息
	void SearchAllTickets();
	
protected:
	
	// 检查航班数据是否有效
	bool CheckFlightData();
	
	// 根据指定的航班号获取航班的索引
	int GetFlightIndexByID(const char* pID);
	
	// 航班顺序表
	vector<FLIGHT>					m_Flights;
	
};

