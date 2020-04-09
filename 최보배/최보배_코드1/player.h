#pragma once
#include "gameNode.h"
#include "Inventory.h"

enum STATE
{
	IDLE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LEFTATK,
	RIGHTATK,
	UPATK,
	FRONTATK,
	GETATK,
	DEAD
};

class player : public gameNode
{
private:

	Inventory* _inventory;//인벤토리 클래스 불러오기
	
	POINT _playercenter;//혹시 몰라서 좌표 줬습니다
	RECT _playerRc;//플레이어 렉트

	

	image* _playerImage;//플레이어 아이들 상태
	image* _playerLeft;//플레이어 왼쪽으로 이동
	image* _playerRight;//플레이어 오른쪽으로 이동
	image* _playerUp;//플레이어 위쪽으로 이동
	image* _playerDown;//플레이어 아래쪽으로 이동
	image* _playerLeftatk;//플레이어 왼쪽으로 공격
	image* _playerRightatk;//플레이어 오른쪽으로 공격
	image* _playerUpatk;//플레이어 위쪽으로 공격
	image* _playerFrontatk;//플레이어 아래쪽으로 공격
	image* _playerGetatk;//공격 받음, 죽음


	image* _playerHp;

	int _hpCount;//4부터 시작하여 0이되면 사망


	RECT _getAtkleftRc;//피격판정 렉트
	RECT _getAtkrightRc;
	RECT _getAtktopRc;
	RECT _getAtkbottomRc;
	
	RECT empty;//인터섹트렉트용

	STATE _state;//상태


	bool _left;//이동 상태 변환
	bool _right;
	bool _up;
	bool _down;


	bool _leftatk;//공격 상태 변환
	bool _rightatk;
	bool _upatk;
	bool _frontatk;


	bool _getatkleft;//피격판정 불변수
	bool _getatkright;
	bool _getatktop;
	bool _getatkbottom;

	bool _getatk;

	int _count;//프레임렌더에 쓸 인트형
	int _index;
	
public:

	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	void animation();



	player() {}
	~player() {}
};

