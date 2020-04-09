#pragma once
#include "gameNode.h"
#include "inventory.h"

// 클래스 전방 선언 (상호 참조용)
class octopus;

// 플레이어 현재 상태 열거문
enum PLAYER_STATE
{
	PLAYER_STATE_IDLE = 0,			// 기본 스탠딩
	PLAYER_STATE_LEFT = 1,			// 왼쪽 이동
	PLAYER_STATE_RIGHT = 2,			// 오른쪽 이동
	PLAYER_STATE_UP = 3,			// 위쪽 이동
	PLAYER_STATE_DOWN = 4,			// 아래쪽 이동
	PLAYER_STATE_LEFTATK = 5,		// 왼쪽 공격
	PLAYER_STATE_RIGHTATK = 6,		// 오른쪽 공격
	PLAYER_STATE_UPATK = 7,			// 위쪽 공격
	PLAYER_STATE_DOWNATK = 8,		// 아래쪽 공격
	PLAYER_STATE_GETATK = 9,		// 몬스터에게 피격
	PLAYER_STATE_DEAD = 10			// 사망
};

// player 클래스
class player : public gameNode
{
private:
	// 주소값 관련
	octopus* _octopusAdress;		// octopus 클래스 주소값

	// 이미지 관련
	image* _playerImage;			// 플레이어 기본 스탠딩 상태
	image* _playerLeft;				// 플레이어 왼쪽으로 이동
	image* _playerRight;			// 플레이어 오른쪽으로 이동
	image* _playerUp;				// 플레이어 위쪽으로 이동
	image* _playerDown;				// 플레이어 아래쪽으로 이동
	image* _playerLeftAtk;			// 플레이어 왼쪽으로 공격
	image* _playerRightAtk;			// 플레이어 오른쪽으로 공격
	image* _playerUpAtk;			// 플레이어 위쪽으로 공격
	image* _playerDownAtk;			// 플레이어 아래쪽으로 공격
	image* _playerGetAtk;			// 플레이어 공격 받음
	image* _playerHP;				// 플레이어 체력

	// 객체 관련
	inventory* _inventory;			// inventory 클래스 선언
	POINT playerCenter;				// 플레이어 센터 좌표
	RECT playerRc;					// 플레이어 RECT
	RECT playerGetAtkLeftRc;		// 플레이어 피격 판정 RECT (왼쪽)
	RECT playerGetAtkRightRc;		// 플레이어 피격 판정 RECT (오른쪽)
	RECT playerGetAtkTopRc;			// 플레이어 피격 판정 RECT (위쪽)
	RECT playerGetAtkBottomRc;		// 플레이어 피격 판정 RECT (아래쪽)
	RECT empty;						// IntersectRect용 RECT

	// 변수 관련
	PLAYER_STATE playerState;		// 플레이어 현재 상태
	int hpCount;					// 플레이어 HP (4부터 시작하여 0이 되면 사망)
	int count;						// 프레임 렌더 카운트
	int index;						// 프레임 렌더 인덱스
	// 이동 상태 변환
	bool playerLeft;				// 왼쪽 이동
	bool playerRight;				// 오른쪽 이동
	bool playerUp;					// 위쪽 이동
	bool playerDown;				// 아래쪽 이동
	// 공격 상태 변환
	bool playerLeftAtk;				// 왼쪽 공격
	bool playerRightAtk;			// 오른쪽 공격
	bool playerUpAtk;				// 위쪽 공격
	bool playerDownAtk;				// 아래쪽 공격
	// 피격 판정
	bool playerGetAtkLeft;			// 왼쪽 피격
	bool playerGetAtkRight;			// 오른쪽 피격
	bool playerGetAtkTop;			// 위쪽 피격
	bool playerGetAtkBottom;		// 아래쪽 피격
	bool playerGetAtk;				// 플레이어 피격 판정
	
public:
	// GET, SET 함수
	// 주소값 받기
	void setOctopusAdress(octopus* octopusAdress) { _octopusAdress = octopusAdress; }

	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 애니메이션 처리
	void animation();

	// 생성자, 소멸자
	player() {}
	~player() {}
};