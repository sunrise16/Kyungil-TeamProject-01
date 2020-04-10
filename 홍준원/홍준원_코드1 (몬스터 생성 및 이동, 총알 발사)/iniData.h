#pragma once
#include "singletonBase.h"

// iniData ����ü
struct tagIniData
{
	char* section;		// ���� ( [***] �κ� )
	char* key;			// Ű �� ( *** = $$$ ���� *** �κ�)
	char* value;		// ��� �� ( *** = $$$ ���� $$$ �κ�)
};

// iniData Ŭ����
class iniData : public singletonBase <iniData>
{
private:
	// ��ü ����
	vector<tagIniData> _vIniData;			// ini�� ���� ������ ����

public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ������ �߰�
	void addData(const char* section, const char* key, const char* value);

	// ���� �̸����� ���̺�
	void saveINI(const char* fileName);

	// ���ڷ� ���� �ε� (���� �̸�, ����, Ű)
	char* loadDataString(const char* fileName, const char* section, const char* key);

	// ������ ���� �ε� (���� �̸�, ����, Ű)
	int loadDataInteger(const char* fileName, const char* section, const char* key);

	// �Ǽ��� ���� �ε� (���� �̸�, ����, Ű)
	float loadDataFloat(const char* fileName, const char* section, const char* key);

	// ������, �Ҹ���
	iniData() {}
	~iniData() {}
};

