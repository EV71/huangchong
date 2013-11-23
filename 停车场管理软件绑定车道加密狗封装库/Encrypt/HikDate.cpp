#include "HikDate.h"
#include<stdio.h>
// countDay.cpp : Defines the entry point for the console application.
//����2������֮�������
#include<stdio.h>
#include<conio.h>

/****************************************************************************************************
* @��������:	IsLeapYear
* @��  �ܣ�		�ж��Ƿ�������
* @��  ����		
* @ ayear		���
* @����ֵ��		true �������� false���������
* @˵  ����		
****************************************************************************************************/
bool IsLeapYear( int ayear)
{
	bool Is_LeapYear;
	Is_LeapYear=((ayear%4==0&&ayear%100!=0)||(ayear%400==0));
	return Is_LeapYear;
}
/****************************************************************************************************
* @��������:	Monthfate
* @��  �ܣ�		�ж�ĳһ�µ�����
* @��  ����		
* @ date3		����
* @����ֵ��		���µ�����
* @˵  ����		
****************************************************************************************************/
int Monthfate(struct date nDate)
{
	switch(nDate.month)
	{
		case 1: 
		case 3: 
		case 5:
		case 7: 
		case 8: 
		case 10: 
		case 12: return 31;
			break;
		case 4: 
		case 6: 
		case 9: 
		case 11: return 30;
			break;
		case 2: 
			{
				if(IsLeapYear(nDate.year))
				{
					return 29;
				}
				else
				{	
					return 28;
				}
			}
				break;
		default: printf(" month error!\n");
	}
	return 0;
}
/****************************************************************************************************
* @��������:	Monthfate
* @��  �ܣ�		�ж�ĳһ�µ�����
* @��  ����		
* @ date3		����
* @����ֵ��		���µ�����
* @˵  ����		
****************************************************************************************************/
int DaysBetweenYear(struct date date1,struct date date2)
{
	int i=0;
	int yearDay=0;
	int sum_year=0;
	if(date2.month>date1.month||date2.month==date1.month&&date2.day>=date1.day)
	{
		for(i=date1.year+1;i<=date2.year;i++)
		{
			if(IsLeapYear(i))
			{
				yearDay=366;
			}
			else
				yearDay=365;
			sum_year+=yearDay;
		}
		return sum_year;
	}
	else
	{
		for(i=date1.year+1;i<date2.year;i++)
		{
			if(IsLeapYear(i))
			{
				yearDay=366;
			}
			else
				yearDay=365;
			sum_year+=yearDay;
		}
	}
	return sum_year;
}
/****************************************************************************************************
* @��������:	DaysBetweenMonth
* @��  �ܣ�		�ж�ĳһ�µ�����
* @��  ����		

* @����ֵ��		
* @˵  ����		����������ʼ�·ݵ�������ʣ������
****************************************************************************************************/

int DaysBetweenMonth(struct date date1,struct date date2)
{
	int i=0;
	int monthday=0;
	int fate=0;
	int fateday=0;
	if(date2.year>date1.year&&date2.month<date1.month||date2.month==date1.month&&date2.day<date1.day)
	{
		for(i=date1.month+1;i<=12;i++)
		{
			fate=Monthfate(date1);
			monthday+=fate;
		}
		fateday=monthday+Monthfate(date1)-date1.day;
		return fateday;
	}
	else if(date2.year>=date1.year&&date2.month>date1.month||date2.month==date1.month&&date2.day>=date1.day)
	{
		for(i=date1.month+1;i<=date2.month;i++)
		{
			fate=Monthfate(date1);
			monthday+=fate;
		}
		fateday=monthday+date2.day-date1.day;
		return fateday;
	} 
	return 0;
}
/****************************************************************************************************
* @��������:	DaysBetweenMonth
* @��  �ܣ�		�ж�ĳһ�µ�����
* @��  ����		

* @����ֵ��		
* @˵  ����		����������ֹ���ڳ�������1��1�յ�����
****************************************************************************************************/

int DaysoverFate(struct date date1,struct date date2)
{
	if(date2.year>date1.year&&date2.month<date1.month||date2.month==date1.month&&date2.day<date1.day)
	{
		int i=0;
		int monthday=0;
		int fate=0;
		int overday=0;
		for(i=1;i<date2.month;i++)
		{
			fate=Monthfate(date2);
			monthday+=fate;
		}
		overday=monthday+date2.day;
		return overday;
	}
	else 
	{
		return 0;
	}
	return 0;
}
/****************************************************************************************************
 * @��������:	DaysBetweenDate
 * @��  �ܣ�	
 * @��  ����		

 * @����ֵ��		
 * @˵  ����	������������֮�������
 ****************************************************************************************************/
int DaysBetweenDate(struct date date1,struct date date2)
{
	return DaysBetweenYear(date1,date2)+DaysBetweenMonth(date1,date2)+DaysoverFate(date1,date2);
}
