#include "stdafx.h"
#include "iniData.h"

// �ʱ�ȭ (init)
HRESULT iniData::init()
{
	// �ʱ�ȭ ����
	return S_OK;
}

// ���� (release)
void iniData::release()
{
}

// ������ �߰�
void iniData::addData(const char * section, const char * key, const char * value)
{
	// iniData ����ü �ʱ�ȭ
	tagIniData data;
	data.section = (char*)section;
	data.key = (char*)key;
	data.value = (char*)value;

	// data ���� ���� ���� ����
	_vIniData.push_back(data);
}

// ���� �̸����� ���̺�
void iniData::saveINI(const char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat_s(dir, str);				 // strcat(value1, value2) = 2���� ���ڿ��� �� ������� ���� (value1 += value2)

	// �����͸� ���� �� ini ����
	for (int i = 0; i < _vIniData.size(); i++)
	{
		WritePrivateProfileString(_vIniData[i].section, _vIniData[i].key, _vIniData[i].value, dir);
	}
}

// ���ڷ� ���� �ε� (���� �̸�, ����, Ű)
char * iniData::loadDataString(const char * fileName, const char * section, const char * key)
{
	char str[256];
	char dir[256];
	char data[256] = { 0 };
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat_s(dir, str);

	GetPrivateProfileString(section, key, "", data, 256, dir);

	return data;
}

// ������ ���� �ε� (���� �̸�, ����, Ű)
int iniData::loadDataInteger(const char * fileName, const char * section, const char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat_s(dir, str);

	return GetPrivateProfileInt(section, key, 0, dir);
}

// �Ǽ��� ���� �ε� (���� �̸�, ����, Ű)
float iniData::loadDataFloat(const char* fileName, const char* section, const char* key)
{
	return atof(loadDataString(fileName, section, key));
}