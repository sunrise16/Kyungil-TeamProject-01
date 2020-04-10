#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{

	_inventory = new Inventory;//인벤토리 클래스 가져옴
	_inventory->init();

	_playercenter.x = WINSIZEX / 2;//플레이어 중심 좌표 선언
	_playercenter.y = WINSIZEY / 2;

	//여기부터 플레이어의 아이들, 이동 상태
	_playerImage = IMAGEMANAGER->addImage("플레이어앞모습", "플레이어/링크앞모습.bmp", 64, 64, true, RGB(255, 0, 255));
	_playerLeft = IMAGEMANAGER->addFrameImage("플레이어왼쪽이동", "플레이어/링크옆으로걷기_230+23_10장.bmp", 640, 64, 10, 1);
	_playerRight = IMAGEMANAGER->addFrameImage("플레이어오른쪽이동", "플레이어/링크오른쪽옆으로걷기_230+23_10장.bmp", 640, 64, 10, 1);
	_playerUp = IMAGEMANAGER->addFrameImage("플레이어위쪽이동", "플레이어/링크위로걷기_180+26_10장.bmp", 640, 64, 10, 1);
	_playerDown = IMAGEMANAGER->addFrameImage("플레이어아래쪽이동", "플레이어/링크앞으로걷기_180+24_10장.bmp", 640, 64, 10, 1);


	//여기부터 플레이어의 공격 상태 --> 가로, 세로가 80인 이유는 64가 너무 작기 때문입니다
	_playerLeftatk = IMAGEMANAGER->addFrameImage("플레이어왼쪽공격", "플레이어/링크옆으로공격_609+25_29장.bmp", 2320, 80, 29, 1);
	_playerRightatk = IMAGEMANAGER->addFrameImage("플레이어오른쪽공격", "플레이어/링크오른쪽옆으로공격_609+25_29장.bmp", 2320, 80, 29, 1);
	_playerUpatk = IMAGEMANAGER->addFrameImage("플레이어위쪽공격", "플레이어/링크뒤로공격_638+28_11장.bmp", 880, 80, 11, 1);
	_playerFrontatk = IMAGEMANAGER->addFrameImage("플레이어앞쪽공격", "플레이어/링크앞으로공격_209+24_11장.bmp", 880, 80, 11, 1);

	_playerGetatk = IMAGEMANAGER->addFrameImage("플레이어피격", "플레이어/링크피격_125+24_5장.bmp", 320, 64, 5, 1);

	
	
	_playerHp = IMAGEMANAGER->addFrameImage("플레이어체력", "플레이어/하트 400+80_X5Y1.bmp", 200, 50, 5, 1);
	

	_playerRc = RectMakeCenter(_playercenter.x, _playercenter.y, 64, 64);//플레이어 렉트
	
	_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 32, 10, 10);//피격판정 렉트입니다
	_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 32, 10, 10);
	_getAtktopRc = RectMakeCenter(_playerRc.left + 32, _playerRc.top, 10, 10);
	_getAtkbottomRc = RectMakeCenter(_playerRc.left + 32, _playerRc.bottom, 10, 10);
	
	_left = false;//이동 하지 않음
	_right = false;
	_up = false;
	_down = false;

	_leftatk = false;//공격 하지 않음
	_rightatk = false;
	_upatk = false;
	_frontatk = false;


	_getatkleft = false;//공격 받지 않음
	_getatkright = false;
	_getatktop = false;
	_getatkbottom = false;

	_count = _index = 0;//프레임렌더에 쓸 변수 초기화

	_hpCount = 4;

	_getatk = false;

	return S_OK;
}

void player::release()
{
	_inventory->release();//인벤토리 클래스 해제
	SAFE_DELETE(_inventory);
}

void player::update()
{
	_state = IDLE;//플레이어 상태 : 아이들

	if (INPUT->getKey(VK_LEFT) && _playerRc.left >= 0)//왼쪽으로 이동합니다
	{
		_left = true;
		_state = LEFT;//상태 바꿔주고

		_playerRc.left -= 3;
		_playerRc.right -= 3;



		if (INPUT->getKey(VK_SPACE))//왼쪽으로 공격합니다
		{
			_leftatk = true;
			_state = LEFTATK;//왼쪽으로 공격 상태로 바꿔줍니다

			_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 40, 10, 10);//아이들 상태의 렉트의 크기와 공격 상태의 렉트의 크기가 다르므로 다시 피격판정렉트를 그려줍니다
			_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 40, 10, 10);
			_getAtktopRc = RectMakeCenter(_playerRc.left + 40, _playerRc.top, 10, 10);
			_getAtkbottomRc = RectMakeCenter(_playerRc.left + 40, _playerRc.bottom, 10, 10);

		}
	}


	//===========================================여기까지 왼쪽================================================================//



	//대각선 이동이 불가능하게끔 엘스이프 처리
	else if (INPUT->getKey(VK_RIGHT) && _playerRc.right <= WINSIZEX)//오른쪽으로 이동합니다
	{
		_right = true;
		_state = RIGHT;//상태 바꿔주고

		_playerRc.left += 3;
		_playerRc.right += 3;

		if (INPUT->getKey(VK_SPACE))//오른쪽으로 공격합니다
		{
			_rightatk = true;
			_state = RIGHTATK;//오른쪽으로 공격 상태로 바꿔줍니다

			_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 40, 10, 10);
			_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 40, 10, 10);
			_getAtktopRc = RectMakeCenter(_playerRc.left + 40, _playerRc.top, 10, 10);
			_getAtkbottomRc = RectMakeCenter(_playerRc.left + 40, _playerRc.bottom, 10, 10);

		}
	}


	//===========================================여기까지 오른쪽================================================================//
	


	else if (INPUT->getKey(VK_UP) && _playerRc.top >= 0)//위쪽으로 이동합니다
	{
		_up = true;
		_state = UP;//상태 바꿔주고

		_playerRc.top -= 3;
		_playerRc.bottom -= 3;

		if (INPUT->getKey(VK_SPACE))//위쪽으로 공격합니다
		{
			_upatk = true;
			_state = UPATK;//위쪽으로 공격 상태로 바꿔줍니다

			_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 40, 10, 10);
			_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 40, 10, 10);
			_getAtktopRc = RectMakeCenter(_playerRc.left + 40, _playerRc.top, 10, 10);
			_getAtkbottomRc = RectMakeCenter(_playerRc.left + 40, _playerRc.bottom, 10, 10);

		}
	}


	//===========================================여기까지 위쪽================================================================//


	else if (INPUT->getKey(VK_DOWN) && _playerRc.bottom <= WINSIZEY)//아래쪽으로 이동합니다
	{
		_down = true;
		_state = DOWN;//상태 바꿔주고

		_playerRc.top += 3;
		_playerRc.bottom += 3;

		if (INPUT->getKey(VK_SPACE))//아래쪽으로 공격합니다
		{
			_frontatk = true;
			_state = FRONTATK;//아래쪽으로 공격 상태로 바꿔줍니다

			_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 40, 10, 10);
			_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 40, 10, 10);
			_getAtktopRc = RectMakeCenter(_playerRc.left + 40, _playerRc.top, 10, 10);
			_getAtkbottomRc = RectMakeCenter(_playerRc.left + 40, _playerRc.bottom, 10, 10);

		}
	}


	//===========================================여기까지 아래쪽================================================================//



	this->animation();//애니메이션 보여줍시다


	_getAtkleftRc = RectMakeCenter(_playerRc.left, _playerRc.top + 32, 10, 10);//아이들, 이동 상태의 피격판정 렉트입니다
	_getAtkrightRc = RectMakeCenter(_playerRc.right, _playerRc.top + 32, 10, 10);
	_getAtktopRc = RectMakeCenter(_playerRc.left + 32, _playerRc.top, 10, 10);
	_getAtkbottomRc = RectMakeCenter(_playerRc.left + 32, _playerRc.bottom, 10, 10);


	//if(IntersectRect(&empty, &_getAtkleftRc, &/*오빠 렉트 적어주세요*/)
	//	{
	//		_hpCount--;
	//	}
	//else if (IntersectRect(&empty, &_getAtkrightRc, &/*오빠 렉트 적어주세요*/)
	//{
	//	_hpCount--;
	//}
	//else if (IntersectRect(&empty, &_getAtktopRc, &/*오빠 렉트 적어주세요*/)
	//{
	//	_hpCount--;
	//}
	//else if (IntersectRect(&empty, &_getAtkbottomRc, &/*오빠 렉트 적어주세요*/)
	//{
	//	_hpCount--;
	//}





	_inventory->update();//인벤토리 업데이트
}

void player::render()
{

	Rectangle(getMemDC(), _playerRc);


	if (_state == IDLE)
	{
		_playerImage->render(getMemDC(), _playerRc.left, _playerRc.top);
	}
	if (_state == LEFT)
	{
		_playerLeft->frameRender(getMemDC(), _playerRc.left, _playerRc.top);
	}
	if (_state == RIGHT)
	{
		_playerRight->frameRender(getMemDC(), _playerRc.left, _playerRc.top);
	}
	if (_state == UP)
	{
		_playerUp->frameRender(getMemDC(), _playerRc.left, _playerRc.top);
	}
	if (_state == DOWN)
	{
		_playerDown->frameRender(getMemDC(), _playerRc.left, _playerRc.top);
	}



	//======================여기까지 이동====================================//


	if (_state == LEFTATK)
	{
		_playerLeftatk->frameRender(getMemDC(), _playerRc.left - 20, _playerRc.top - 15);
	}
	if (_state == RIGHTATK)
	{
		_playerRightatk->frameRender(getMemDC(), _playerRc.left + 10, _playerRc.top - 10);
	}
	if (_state == UPATK)
	{
		_playerUpatk->frameRender(getMemDC(), _playerRc.left - 10, _playerRc.top - 15);
	}
	if (_state == FRONTATK)
	{
		_playerFrontatk->frameRender(getMemDC(), _playerRc.left - 10, _playerRc.top);
	}


	if (_hpCount == 4)
	{
		_playerHp->frameRender(getMemDC(), 100, 50, 5, 0);
		_getatk = true;
		_state = GETATK;

		if (_count > 5000 == 0)
		{
			_state = IDLE;
			_count = 0;
		}
	}
	if (_hpCount == 3)
	{
		_playerHp->frameRender(getMemDC(), 100, 50, 4, 0);
		_getatk = true;
		_state = GETATK;

		if (_count > 5000 == 0)
		{
			_state = IDLE;
			_count = 0;
		}
	}
	if (_hpCount == 2)
	{
		_playerHp->frameRender(getMemDC(), 100, 50, 3, 0);
		_getatk = true;
		_state = GETATK;

		if (_count > 5000 == 0)
		{
			_state = IDLE;
			_count = 0;
		}
	}
	if (_hpCount == 1)
	{
		_playerHp->frameRender(getMemDC(), 100, 50, 2, 0);
		_getatk = true;
		_state = GETATK;

		if (_count > 5000 == 0)
		{
			_state = IDLE;
			_count = 0;
		}
	}
	if (_hpCount == 0)
	{
		_playerHp->frameRender(getMemDC(), 100, 50, 1, 0);
		_state = DEAD;
	}
	//=============================여기까지 공격=========================================================================//

	Rectangle(getMemDC(), _getAtkleftRc);//피격판정 렉트입니다
	Rectangle(getMemDC(), _getAtkrightRc);
	Rectangle(getMemDC(), _getAtktopRc);
	Rectangle(getMemDC(), _getAtkbottomRc);


	_inventory->render();//인벤토리 그려줍니다
}



void player::animation()
{
	switch (_state)
	{

	case IDLE:

		_playerImage->render(getMemDC(), _playerRc.left, _playerRc.top);

		break;

	case LEFT:

		if (_left)
		{
			_count++;
			_playerLeft->setFrameY(0);

			if (_count % 10 == 0)
			{
				_index++;

				if (_index >= 10)
				{
					_index = 0;
				}
				_playerLeft->setFrameX(_index);
			}
		}
		break;
	case RIGHT:

		if (_right)
		{
			_count++;
			_playerRight->setFrameY(0);
			if (_count % 10 == 0)
			{
				_index++;

				if (_index >= 10)
				{
					_index = 0;
				}
				_playerRight->setFrameX(_index);
			}
		}
		break;
	case UP:

		if (_up)
		{
			_count++;
			_playerUp->setFrameY(0);
			if (_count % 10 == 0)
			{
				_index++;

				if (_index >= 10)
				{
					_index = 0;
				}
				_playerUp->setFrameX(_index);
			}
		}
		break;
	case DOWN:

		if (_down)
		{
			_count++;
			_playerDown->setFrameY(0);
			if (_count % 10 == 0)
			{
				_index++;

				if (_index >= 10)
				{
					_index = 0;
				}
				_playerDown->setFrameX(_index);
			}
		}
		break;


		//================================================================여기까지 이동==================================================================//



	case LEFTATK:

		if (_leftatk)
		{
			_count++;
			_playerLeftatk->setFrameY(0);
			if (_count % 3 == 0)
			{
				_index++;

				if (_index >= 29)
				{
					_index = 0;
				}
				_playerLeftatk->setFrameX(_index);
			}
		}
		break;
	case RIGHTATK:

		if (_rightatk)
		{
			_count++;
			_playerRightatk->setFrameY(0);

			if (_count % 3 == 0)
			{
				_index++;

				if (_index >= 29)
				{
					_index = 0;
				}
				_playerRightatk->setFrameX(_index);
			}
		}
		break;
	case UPATK:

		if (_upatk)
		{
			_count++;
			_playerUpatk->setFrameY(0);

			if (_count % 3 == 0)
			{
				_index++;

				if (_index >= 11)
				{
					_index = 0;
				}
				_playerUpatk->setFrameX(_index);
			}
		}
		break;

	case FRONTATK:

		if (_frontatk)
		{
			_count++;
			_playerFrontatk->setFrameY(0);

			if (_count % 5 == 0)
			{
				_index++;

				if (_index >= 11)
				{
					_index = 0;
				}
				_playerFrontatk->setFrameX(_index);
			}
		}
		break;
	case GETATK:

		if (_hpCount == 0)
		{
			_count++;
			_playerGetatk->setFrameY(0);

			if (_count % 5 == 0)
			{
				_index++;

				if (_index >= 5)
				{
					_index = 5;
				}

				_playerGetatk->setFrameX(_index);
			}
		}
		break;
	case DEAD:

		if (_hpCount == 0)
		{
			_count++;
			_playerGetatk->setFrameY(0);

			if (_count % 5 == 0)
			{
				_index++;

				if (_index >= 5)
				{
					_index = 5;
				}

				_playerGetatk->setFrameX(_index);
			}
		}
		break;
	
	}
}