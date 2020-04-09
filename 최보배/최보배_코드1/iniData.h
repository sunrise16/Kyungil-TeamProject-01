#pragma once
#include "singletonBase.h"

// iniData 구조체
struct tagIniData
{
	char* section;		// 섹션 ( [***] 부분 )
	char* key;			// 키 값 ( *** = $$$ 에서 *** 부분)
	char* value;		// 밸류 값 ( *** = $$$ 에서 $$$ 부분)
};

// iniData 클래스
class iniData : public singletonBase <iniData>
{
private:
	// 객체 관련
	vector<tagIniData> _vIniData;			// ini에 담을 데이터 벡터

public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 데이터 추가
	void addData(const char* section, const char* key, const char* value);

	// 파일 이름으로 세이브
	void saveINI(const char* fileName);

	// 문자로 값을 로드 (파일 이름, 섹션, 키)
	char* loadDataString(const char* fileName, const char* section, const char* key);

	// 정수로 값을 로드 (파일 이름, 섹션, 키)
	int loadDataInteger(const char* fileName, const char* section, const char* key);

	// 실수로 값을 로드 (파일 이름, 섹션, 키)
	float loadDataFloat(const char* fileName, const char* section, const char* key);

	// 생성자, 소멸자
	iniData() {}
	~iniData() {}
};

