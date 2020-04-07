#include "stdafx.h"
#include "iniData.h"

// 초기화 (init)
HRESULT iniData::init()
{
	return S_OK;
}

// 해제 (release)
void iniData::release()
{
}

// 데이터 추가
void iniData::addData(const char * section, const char * key, const char * value)
{
	// iniData 구조체 초기화
	tagIniData data;
	data.section = (char*)section;
	data.key = (char*)key;
	data.value = (char*)value;

	// data 값을 담은 벡터 생성
	_vIniData.push_back(data);
}

// 파일 이름으로 세이브
void iniData::saveINI(const char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf_s(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat_s(dir, str);				 // strcat(value1, value2) = 2개의 문자열을 앞 밸류값에 연결 (value1 += value2)

	// 데이터를 담은 후 ini 생성
	for (int i = 0; i < _vIniData.size(); i++)
	{
		WritePrivateProfileString(_vIniData[i].section, _vIniData[i].key, _vIniData[i].value, dir);
	}
}

// 문자로 값을 로드 (파일 이름, 섹션, 키)
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

// 정수로 값을 로드 (파일 이름, 섹션, 키)
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

// 실수로 값을 로드 (파일 이름, 섹션, 키)
float iniData::loadDataFloat(const char* fileName, const char* section, const char* key)
{
	return atof(loadDataString(fileName, section, key));
}
