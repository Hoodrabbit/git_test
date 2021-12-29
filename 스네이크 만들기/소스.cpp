#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
using namespace std;
//□■

// 상하좌우 상수값 설정
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int map_State[20][20];
//int Snake_Length = 2;

struct ITEM
{
private:
	bool Crash_Check;
	int itemX;
	int itemY;
public:
	void Item_Spawn(char arr[][20])
	{
		static bool Start = true;
		if (Start == true)
		{
			//cout << "왜 안되지" << endl;
			Item_Respawn(arr);
			Start = false;
		}
		//char item = 0xDA; //별모양으로 만들 예정
		/*if (Crash_Check == NULL)
		{
			Item_Respawn(arr);
			Crash_Check = false;
		}*/
		//itemX = NULL, itemY = NULL;
	   //아이템의 현재 위치 static으로 선언을 하지 않는다면 함수가 실행될 때마다 값이 달라져버리니 이렇게 설정

	   //아이템 이전 위치와 다른지 미리 확인하고 같으면 위치 이동
		//Item_Respawn(arr);

		if (Crash_Check == true)
		{
			//cout << "출동 실행" << endl;
			Item_Respawn(arr);
			Crash_Check = false;

		}
		else
		{
			arr[itemX][itemY] = 0xDA;
		}


	}

	void Item_Respawn(char arr[][20])
	{
		itemX = rand() % 18 + 1;
		itemY = rand() % 18 + 1;

		while (arr[itemX][itemY] == 0xE0)
		{
			itemX = rand() % 18 + 1;
			itemY = rand() % 18 + 1;
		}
		map_State[itemX][itemY] = 2;
		arr[itemX][itemY] = 0xDA;
	}

	void Item_Crash_Check(bool check)
	{
		if (check == true)
		{
			Crash_Check = true;
		}
	}
};

ITEM item_;

class Snake_Game
{
	int Snake_Length = 4;
	struct Snake_Body
{
	int myXpos; // [][x]
	int myYpos; // [y][]
	Snake_Body* Next;
};

	Snake_Body* Snake_Head = NULL;
	Snake_Body* Snake_Tail = NULL;
	Snake_Body* Cur = NULL;
	Snake_Body* New_Snake = NULL;


	Snake_Body * Selecting_Value(Snake_Body* GetPos)
{
	Snake_Body* Change_Snake_Tail_Pos = NULL;

	if (Change_Snake_Tail_Pos == NULL)
	{
	//	cout << "GetPos : " << GetPos->myXpos << " , " << GetPos->myYpos << endl;
		Change_Snake_Tail_Pos = GetPos;
	}
	
	if (Change_Snake_Tail_Pos->myXpos == 0)
	{
		if (Change_Snake_Tail_Pos->myYpos - 1 != 0)
		{
			Change_Snake_Tail_Pos->myXpos = Change_Snake_Tail_Pos->myXpos + 1;
			Change_Snake_Tail_Pos->myYpos = Change_Snake_Tail_Pos->myYpos - 1;
			return Change_Snake_Tail_Pos;
		}
		else
		{
			Change_Snake_Tail_Pos->myXpos = Change_Snake_Tail_Pos->myXpos + 1;
			Change_Snake_Tail_Pos->myYpos = Change_Snake_Tail_Pos->myYpos + 1;
			return Change_Snake_Tail_Pos;
		}
		
	}
	return Change_Snake_Tail_Pos;
}//값 전환시키는 함수

	void SavePosValue(int* xpos, int* ypos, Snake_Body * New_Body)
{
	*xpos = New_Body->myXpos;
	*ypos = New_Body->myYpos;
}

public:

	void Linked_Snake()
	{
		
		int xpos = 0;//값만 이렇게
		int ypos = 0;//따로 빼서 사용해보기
		

		for (int i = 0; i < Snake_Length; i++)
		{
			New_Snake = new Snake_Body();
			New_Snake->Next = NULL;
			if (Snake_Head == NULL)
			{
				//New_Snake = new Snake_Body();

				New_Snake->myXpos = rand() % 18 + 1; // 0과 19는 벽이라서 어차피 그 부분에서는 생성이 되면 안되니까  
				New_Snake->myYpos = rand() % 18 + 1; // 1~18부터 시작할 수 있도록 만들어줌

				Snake_Head = New_Snake;

				SavePosValue(&xpos, &ypos, New_Snake);
			}
			else
			{
				New_Snake->myXpos = xpos;
				New_Snake->myYpos = ypos;

				New_Snake->myXpos = New_Snake->myXpos - 1;
				New_Snake->myYpos = New_Snake->myYpos;

				New_Snake = Selecting_Value(New_Snake);

				SavePosValue(&xpos, &ypos, New_Snake);

				Snake_Tail->Next = New_Snake;

			

			}
			Snake_Tail = New_Snake;

		}


		Cur = Snake_Head;
		for (int i = 0; i < Snake_Length; i++)
		{
			if (Cur != NULL)
			{
				map_State[Cur->myYpos][Cur->myXpos] = 1;

				cout << Cur->myXpos << " , " << Cur->myYpos << endl;
				Cur = Cur->Next;
			}
			
		}
	}//기본 뱀 상태 및 이동할 때 위치 변경도 시켜줌
	//기본 뱀 상태 및 이동할 때 위치 변경도 시켜줌
	//아직 길이가 늘어남에 따라 달라지는 걸 구현을 안함


	void Snake_Moving(int x = 0, int y = 0)// 매개변수로 x를 몇을 증감시킬지, y를 몇을 증감시킬지 정해주기
	{
		bool move = true;
		Crash_Check(&x, &y, &move);

		Cur = Snake_Head;
		struct value_temp
		{
			int xpos_temp_1, ypos_temp_1;
			bool HasValue = false;
		};
		struct value_temp_2
		{
			int xpos_temp_2, ypos_temp_2;
			bool HasValue = false;
		};
		value_temp v_t = { 0,0 };
		value_temp_2 v_t_2{ 0,0 };
		for (int i = 0; i < Snake_Length; i++) //초기화 시켜주기
		{
			if (Cur != NULL)
			{
				map_State[Cur->myYpos][Cur->myXpos] = 0;

				Cur = Cur->Next;
			}

		}

		
		if (move == true)
		{
			New_Snake = Snake_Head;
			for (int i = 0; i < Snake_Length; i++) // 이동을 했을 경우 이게 실행이 되야 함
			{
				if (New_Snake != NULL)
				{

					if (New_Snake->Next != NULL)
					{

						if (v_t.HasValue == false && v_t_2.HasValue == false)
						{
							v_t.xpos_temp_1 = New_Snake->Next->myXpos; v_t.ypos_temp_1 = New_Snake->Next->myYpos;

							v_t.HasValue = true;
							v_t_2.HasValue = false;
							//cout << "1번 실행" << endl;

							New_Snake->Next->myXpos = New_Snake->myXpos;
							New_Snake->Next->myYpos = New_Snake->myYpos;

						}
						else if (v_t.HasValue == true && v_t_2.HasValue == false)
						{
							v_t_2.xpos_temp_2 = New_Snake->Next->myXpos; v_t_2.ypos_temp_2 = New_Snake->Next->myYpos;
							v_t_2.HasValue = true;
							//cout << "2번 실행" << endl;
							New_Snake->Next->myXpos = v_t.xpos_temp_1;
							New_Snake->Next->myYpos = v_t.ypos_temp_1;
							v_t.HasValue = false;
						}
						else if (v_t.HasValue == false && v_t_2.HasValue == true)
						{
							v_t.xpos_temp_1 = New_Snake->Next->myXpos; v_t.ypos_temp_1 = New_Snake->Next->myYpos;
							v_t.HasValue = true;
							//cout << "3번 실행" << endl;
							New_Snake->Next->myXpos = v_t_2.xpos_temp_2;
							New_Snake->Next->myYpos = v_t_2.ypos_temp_2;

							v_t_2.HasValue = false;
						}
						if (Snake_Head == New_Snake)
						{
							New_Snake->myXpos += x;
							New_Snake->myYpos += y;
						}

					}

					New_Snake = New_Snake->Next;
				}

			}
		}
		

		Cur = Snake_Head;

		for (int i = 0; i < Snake_Length; i++)
		{
			if (Cur != NULL)
			{
				map_State[Cur->myYpos][Cur->myXpos] = 1;
				Cur = Cur->Next;
			}
		}
	}

	void Crash_Check(int *x, int *y, bool *move)
	{
		Cur = Snake_Head;

		if (Cur->myXpos + *x == Cur->Next->myXpos && Cur->myYpos + *y == Cur->Next->myYpos)
		{
			//움직이지 못하고 그냥 넘어가도록 만들어주기
			//x와 y 0으로 바꿔주기
			*x = 0; *y = 0;
			*move = false;
		}
		else if (map_State[Cur->myYpos + *y][Cur->myXpos + *x] == 2)
		{
			Snake_Length++;
			//cout << "아이템과 충돌" << endl;
			item_.Item_Crash_Check(true);  
		}
		else
		{
			if (map_State[Cur->myYpos + *y][Cur->myXpos + *x] == 1)
			{
				//이동하려는 위치가 빈 공간인지 확인하고 아니라면 게임종료 시키고 점수출력
				//cout << "충돌하였습니다."; // 잘 출력됨
			}
		}
	}
};



void Game_Over()
{
	//현재 점수 출력시켜주고 게임종료 시켜주기 
}




void Map()
{
	char map[20][20] = { 0 };

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (i == 0 || j == 0 || i == 19 || j == 19)
			{
				map[i][j] = 0xE1;
				printf("%c%c", 0xA1, map[i][j]);
			}
			else
			{
				
				map[i][j] = 0xE0;
				if (map_State[i][j] == 1)
				{
					map[i][j] = 0xE1;
				}
				else
				{
					map[i][j] = 0xE0;
					item_.Item_Spawn(map);
				}
				printf("%c%c", 0xA1, map[i][j]);
			}
		}
		printf("\n");
	}
	
}



int main()
{
	srand(time(NULL));
	Snake_Game sNake;
	sNake.Linked_Snake(); //제일 처음 스네이크 상태 만들어주기
	Map();
	char move; //키 입력을 받을 변수
	while (1)
	{
		
		move = _getch();
		if (move == -32)
		{
			move = _getch();
		}
		switch (move)
		{
		case LEFT:
		{
			//cout << "왼쪽 " << endl;
			sNake.Snake_Moving(-1, 0);
			break;
		}
		case RIGHT:
		{
			//cout << "오른쪽 " << endl;
			sNake.Snake_Moving(1, 0);
			break;
		}
		case UP:
		{
			//cout << "위쪽 " << endl;
			sNake.Snake_Moving(0, -1);
			break;
		}
		case DOWN:
		{
			//cout << "아래쪽 " << endl;
			sNake.Snake_Moving(0, 1);
			break;
		}
		default:
		{
			break;
		}
		}
		system("cls");
		Map();
	}
		



	//Linked_Snake();//기본 뱀 상태 및 이동할 때 위치 변경도 시켜줌
	//아직 길이가 늘어남에 따라 달라지는 걸 구현을 안함

	int player_length = 4; //플레이어의 현재 길이 
	int score = 0; // 아이템 먹었을 때 이 변수의 값을 1씩 증가 시킴

	



	return 0;
}


