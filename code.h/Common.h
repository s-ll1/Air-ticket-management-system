#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <limits>
#include <iomanip>
#include <fstream>
using namespace std;

// 默认的航班数据文件名
#define FLIGHT_FILE							"flight_data.txt"

// 字符串的长度
#define STR_LEN								0x20

// 每趟航班的默认票数
#define DEFAULT_TICKET_COUNT				200

// 航班状态
typedef enum _tagFlightStatus
{
	STATUS_NORMAL,											// 航班状态正常
		STATUS_DELAY,											// 航班状态延误
		STATUS_CANCEL,											// 航班状态取消
		STATUS_COUNT
		
} FLIGHT_STATUS;

// 查询结果的排序规则
typedef enum _tagSortType
{
	SORT_NORMAL,											// 默认排序
		SORT_BY_PRICE,											// 按票价排序
		SORT_BY_TIME,											// 按飞行时间排序
		SORT_BY_TICKET,											// 按余票数排序
		SORT_COUNT
		
} SORT_TYPE;

// 乘客信息结构体
typedef struct _tagGuest
{
	char			strID[STR_LEN];							// 购票人身份证
	char			strName[STR_LEN];						// 购票人姓名
	
	int				nCount;
	
	_tagGuest()
	{
		memset(strID, 0, sizeof(strID));
		memset(strName, 0, sizeof(strName));
		
		nCount = 0;
	}
	
} GUEST, *LPGUEST;

// 航班信息结构体
typedef vector<GUEST>			GUESTS;
typedef deque<GUEST>            WGUESTS;
typedef struct _tagFlight
{
	char			strFlightID[STR_LEN];					// 航班号
	char			strCompany[STR_LEN];					// 航空公司名称
	char			strStartCity[STR_LEN];					// 起点
	char			strEndCity[STR_LEN];					// 终点
	char			strTransitCity[STR_LEN];				// 经停
	
	struct tm       TakeoffTime;							// 起飞时间
	struct tm       LandingTime;							// 落地时间
	
	int				nTicket;								// 可售票数
	
	int				nPrice;									// 票价
	
	GUESTS			Guests;									// 购票乘客
	WGUESTS			WaitingGuests;							// 预约乘客队列
	
	_tagFlight()
	{
		memset(strFlightID, 0, sizeof(strFlightID));
		memset(strFlightID, 0, sizeof(strFlightID));
		memset(strFlightID, 0, sizeof(strFlightID));
		memset(strFlightID, 0, sizeof(strFlightID));
		memset(strFlightID, 0, sizeof(strFlightID));
		
		memset(&TakeoffTime, 0, sizeof(TakeoffTime));
		memset(&LandingTime, 0, sizeof(LandingTime));
		
		nTicket = DEFAULT_TICKET_COUNT;
		
		nPrice = 0;
	}
	
} FLIGHT, *LPFLIGHT;