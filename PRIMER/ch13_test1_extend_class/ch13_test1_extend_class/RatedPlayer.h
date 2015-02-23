#include "stdafx.h"
#ifndef RATED_PLAYER_H_
#define RATED_PLAYER_H_
#include "TableTennisPlayer.h"

/*
��һ:private,public,protected�ķ��ʷ�Χ:

private: ֻ���ɸ����еĺ���������Ԫ��������,���ܱ��κ��������ʣ�����Ķ���Ҳ���ܷ���.
protected: ���Ա������еĺ���������ĺ������Լ�����Ԫ��������,�����ܱ�����Ķ������
public: ���Ա������еĺ���������ĺ���������Ԫ��������,Ҳ�����ɸ���Ķ������
ע����Ԫ�����������֣���Ϊ��Ԫ��ȫ�ֺ�������Ϊ��Ԫ���еĳ�Ա����

�ڶ�:��ļ̳к󷽷����Ա仯:

ʹ��private�̳�,��������з����������б�Ϊprivate;
ʹ��protected�̳�,�����protected��public�����������б�Ϊprotected,private��������;
ʹ��public�̳�,�����еķ������Բ������ı�;
*/
class RatedPlayer :public TableTennisPlayer  //extend!!!!!!! in C++, USING : to represent extend.
{
private:
	unsigned int rating;
public:
	RatedPlayer( unsigned int r = 0, const string& fn = "none", const string& ln = "none", bool ht = false );
	RatedPlayer( unsigned int r, const TableTennisPlayer& tp );
	unsigned int Rating() const
	{
		return rating;
	}

	void ResetRating(unsigned int r)
	{
		rating = r;
	}


	void printTest() const
	{
		cout << "This is print test of extended class." << endl;
	}

	virtual void v_printTest() const  //virtual function.
	{
		cout << "This is VIRTUAL print test of extended class." << endl;
	}
};

#endif