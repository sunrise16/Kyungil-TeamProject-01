#pragma once
#include "gameNode.h"
#include "inventory.h"

// 클래스 전방 선언 (상호 참조용)
class octopus;
class mushroom;
class boss;

// 플레이어 현재 상태 열거문
enum PLAYER_STATE
{
	PLAYER_STATE_LEFTSTANDING = 0,		// 왼쪽 스탠딩
	PLAYER_STATE_RIGHTSTANDING = 1,		// 오른쪽 스탠딩
	PLAYER_STATE_UPSTANDING = 2,		// 위쪽 스탠딩
	PLAYER_STATE_DOWNSTANDING = 3,		// 아래쪽 스탠딩
	PLAYER_STATE_LEFT = 4,				// 왼쪽 이동
	PLAYER_STATE_RIGHT = 5,				// 오른쪽 이동
	PLAYER_STATE_UP = 6,				// 위쪽 이동
	PLAYER_STATE_DOWN = 7,				// 아래쪽 이동
	PLAYER_STATE_LEFTATK = 8,			// 왼쪽 공격
	PLAYER_STATE_RIGHTATK = 9,			// 오른쪽 공격
	PLAYER_STATE_UPATK = 10,			// 위쪽 공격
	PLAYER_STATE_DOWNATK = 11,			// 아래쪽 공격
	PLAYER_STATE_GETATK = 12,			// 몬스터에게 피격
	PLAYER_STATE_DEAD = 13,				// 플레이어 사망
};

// player 클래스
class player : public gameNode
{
private:
	// 주소값 관련
	octopus* _octopusAdress;			// octopus 클래스 주소값
	mushroom* _mushroomAdress;			// mushroom 클래스 주소값
	boss* _bossAdress;					// boss 클래스 주소값

	// 이미지 관련
	image* _playerLeftStanding;			// 플레이어 기본 스탠딩 상태 (왼쪽)
	image* _playerRightStanding;		// 플레이어 기본 스탠딩 상태 (오른쪽)
	image* _playerUpStanding;			// 플레이어 기본 스탠딩 상태 (위쪽)
	image* _playerDownStanding;			// 플레이어 기본 스탠딩 상태 (아래쪽)
	image* _playerLeft;					// 플레이어 왼쪽으로 이동
	image* _playerRight;				// 플레이어 오른쪽으로 이동
	image* _playerUp;					// 플레이어 위쪽으로 이동
	image* _playerDown;					// 플레이어 아래쪽으로 이동
	image* _playerLeftAtk;				// 플레이어 왼쪽으로 공격
	image* _playerRightAtk;				// 플레이어 오른쪽으로 공격
	image* _playerUpAtk;				// 플레이어 위쪽으로 공격
	image* _playerDownAtk;				// 플레이어 아래쪽으로 공격
	image* _playerGetAtk;				// 플레이어 공격 받음
	image* _playerHP;					// 플레이어 체력

	// 객체 관련
	inventory* _inventory;				// inventory 클래스 선언
	POINT playerCenter;					// 플레이어 센터 좌표
	RECT playerRc;						// 플레이어 RECT
	RECT playerGetAtkLeftRc;			// 플레이어 피격 판정 RECT (왼쪽)
	RECT playerGetAtkRightRc;			// 플레이어 피격 판정 RECT (오른쪽)
	RECT playerGetAtkTopRc;				// 플레이어 피격 판정 RECT (위쪽)
	RECT playerGetAtkBottomRc;			// 플레이어 피격 판정 RECT (아래쪽)
	RECT empty;							// IntersectRect용 RECT
	RECT playerAttack;

	// 변수 관련
	PLAYER_STATE playerState;			// 플레이어 현재 상태
	int hpCount;						// 플레이어 HP (4부터 시작하여 0이 되면 사망)
	int count;							// 프레임 렌더 카운트
	int index;							// 프레임 렌더 인덱스
	// 상태 변환
	bool playerLeftStanding;			// 왼쪽 스탠딩
	bool playerRightStanding;			// 오른쪽 스탠딩
	bool playerUpStanding;				// 위쪽 스탠딩
	bool playerDownStanding;			// 아래쪽 스탠딩
	// 이동 상태 변환
	bool playerLeft;					// 왼쪽 이동
	bool playerRight;					// 오른쪽 이동
	bool playerUp;						// 위쪽 이동
	bool playerDown;					// 아래쪽 이동
	// 공격 상태 변환
	bool playerLeftAtk;					// 왼쪽 공격
	bool playerRightAtk;				// 오른쪽 공격
	bool playerUpAtk;					// 위쪽 공격
	bool playerDownAtk;					// 아래쪽 공격
	// 피격 판정
	bool playerGetAtkLeft;				// 왼쪽 피격
	bool playerGetAtkRight;				// 오른쪽 피격
	bool playerGetAtkTop;				// 위쪽 피격
	bool playerGetAtkBottom;			// 아래쪽 피격
	bool playerGetAtk;					// 플레이어 피격 판정
	int playerGetAtkDelay;				// 플레이어 피격 딜레이
	bool playerGetAtkDelayBool;			// 플레이어 피격 딜레이 판정

public:
	// GET, SET 함수
	RECT getAttack() { return playerAttack; }
	RECT getplayerleftatkRc() { return playerGetAtkLeftRc; }
	void setplayerleftatkRc(RECT _playerGetAtkLeftRc) { playerGetAtkLeftRc = _playerGetAtkLeftRc; }
	RECT getplayerrightatkRc() { return playerGetAtkRightRc; }
	void setplayerrightatkRc(RECT _playerGetAtkRightRc) { playerGetAtkRightRc = _playerGetAtkRightRc; }
	RECT getplayertopatkRc() { return playerGetAtkTopRc; }
	void setplayertopatkRc(RECT _playerGetAtkTopRc) { playerGetAtkTopRc = _playerGetAtkTopRc; }
	RECT getplayerbottomatkRc() { return playerGetAtkBottomRc; }
	void setplayerbottomatkRc(RECT _playerGetAtkBottomRc) { playerGetAtkBottomRc = _playerGetAtkBottomRc; }
	RECT getPlayerRc() { return playerRc; }
	void setPlayerRc(RECT _playerRc) { playerRc = _playerRc; }
	POINT getPlayercenter() { return playerCenter; }
	void setPlayercenter(POINT playercenter) { playerCenter = playercenter; }

	void setPlayerleft(bool _playerLeft) { playerLeft = _playerLeft; }
	void setPlayerright(bool _playerRight) { playerRight = _playerRight; }
	void setPlayerup(bool _playerUp) { playerUp = _playerUp; }
	void setPlayerdown(bool _playerdown) { playerDown = _playerDown; }
	// 주소값 받기
	void setOctopusAdress(octopus* octopusAdress) { _octopusAdress = octopusAdress; }
	void setMushroomAdress(mushroom* mushroomAdress) { _mushroomAdress = mushroomAdress; }
	void setBossAdress(boss* bossAdress) { _bossAdress = bossAdress; }

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