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
int score = 0;

int GAME = 1;
void Game_Over()
{
	GAME = 0;
}



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

	Snake_Body* HEAD = NULL;
	//이름만 이렇고 연결리스트의 맨 마지막 
	//그러니꺄 Snake_Tail->Next == NULL인 노드를 이 노드로 지정해줘야함


	Snake_Body* Selecting_Value(Snake_Body* GetPos)
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

	void SavePosValue(int* xpos, int* ypos, Snake_Body* New_Body)
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

				//cout << Cur->myXpos << " , " << Cur->myYpos << endl;
				Cur = Cur->Next;
			}

		}
	}//기본 뱀 상태 및 이동할 때 위치 변경도 시켜줌
	//기본 뱀 상태 및 이동할 때 위치 변경도 시켜줌
	//아직 길이가 늘어남에 따라 달라지는 걸 구현을 안함


	void Snake_Moving(int x, int y)// 매개변수로 x를 몇을 증감시킬지, y를 몇을 증감시킬지 정해주기
	{
		bool move = true;
		bool Get_Item = false;
		bool already_use = false;
		//여기에 마지막 노드 바로 전 노드를 가리키는 변수를 따로 만들어줘야 나중에 편할 것 같음
		
		if (HEAD == NULL)
		{
			End_Check(Snake_Head);
		}
		
		Crash_Check(&x, &y, &move, &Get_Item);
		Snake_Body* NEW_SNAKE = HEAD;
		Snake_Body* Second_Node = NULL;
		Snake_Body* Last_Node = NULL;
		if (move == true)
		{
			for (int i = 0; i < Snake_Length; i++) //초기화 시켜주기
			{
				if (NEW_SNAKE != NULL)
				{
					map_State[NEW_SNAKE->myYpos][NEW_SNAKE->myXpos] = 0;

					if (NEW_SNAKE->Next != NULL)
					{
						Second_Node = NEW_SNAKE;
						//cout << "Second_Node : " << Second_Node->myXpos << " , " << Second_Node->myYpos << endl;
					}
					if (NEW_SNAKE->Next == NULL)
					{
						Last_Node = NEW_SNAKE;
					}

					NEW_SNAKE = NEW_SNAKE->Next;

				}

			}
			NEW_SNAKE = HEAD;
			for (int i = 0; i < Snake_Length; i++)
			{
				if (NEW_SNAKE != NULL)
				{


					if (NEW_SNAKE->Next != NULL && Get_Item == false)
					{
						NEW_SNAKE->myXpos = NEW_SNAKE->Next->myXpos;
						NEW_SNAKE->myYpos = NEW_SNAKE->Next->myYpos;
						//cout << NEW_SNAKE->myXpos << " , " << NEW_SNAKE->myYpos << endl;
					}

					if (NEW_SNAKE->Next != NULL && Get_Item == true && already_use == false )
					{
						Increase_Node(Last_Node); //지금 Get_Item을 어디에서 true를 시켜줄 건지 생각해봐야함
						//cout << "ITEM : " << Last_Ndoe->myXpos << " , " << Last_Ndoe->myYpos << endl;
						already_use = true;
					}


					if (NEW_SNAKE->Next == NULL)
					{
						//cout << "실행이 되고 있나요 " << endl;
						//cout << "X : " << x << "Y : " << y << endl;
						NEW_SNAKE->myXpos += x;
						NEW_SNAKE->myYpos += y;
						if (Get_Item == true)
						{
							Item_respawn_Check();
							Get_Item = false;
						}

					/*	Cur = HEAD;
					for (int i = 0; i < Snake_Length; i++)
					{
						if (Cur != NULL)
						{
							cout << "Cur : " << Cur->myXpos << " , " << Cur->myYpos << endl;
							if (Cur->Next == NULL)
							{
								cout << "체크" << endl;
							}
							Cur = Cur->Next;
						}
						
					}*/
						//cout << NEW_SNAKE->myXpos << " , " << NEW_SNAKE->myYpos << endl;
					}

					

					map_State[NEW_SNAKE->myYpos][NEW_SNAKE->myXpos] = 1;
					//cout << NEW_SNAKE->myXpos << " , " << NEW_SNAKE->myYpos << endl;
					NEW_SNAKE = NEW_SNAKE->Next;
				}

			}
		}
		
		


	}

	void Crash_Check(int* x, int* y, bool* move, bool * Get_Item)//이부분 수정해줘야함
	{
		Cur = HEAD;

		for (int i = 0; i < Snake_Length; i++)
		{
			if (Cur->Next != NULL)
			{
				Cur = Cur->Next;
			}
		}
		Snake_Body* LastNode = Cur;

		Cur = HEAD;
		//cout << "LastNode : " << LastNode->myXpos << " , " << LastNode->myYpos << endl;
		for (int i = 0; i < Snake_Length; i++)
		{
			if (Cur->Next != NULL)//이부분 수정해야함ㅁㄴㅇㄻㄴㅇㄹ2022-01-18
			{
				if (LastNode->myXpos + *x == Cur->myXpos && LastNode->myYpos + *y == Cur->myYpos && Cur != HEAD)
				{//노드가 헤드일때는 일단 그 위치가 반드시 없어지니까 그 상황은 제외해야함
					cout << "작동" << endl;
					*x = 0; *y = 0;
					*move = false;
				}
				Cur = Cur->Next;
			}
			
		}


		if (map_State[LastNode->myYpos + *y][LastNode->myXpos + *x] == 1)//? d이렇게 하는게 아닌가
		{
			*x = 0; *y = 0;
			*move = false;
			Game_Over();
		}

		if (map_State[LastNode->myYpos + *y][LastNode->myXpos + *x] == 2)
		{
			Snake_Length++;
			score++;
			*Get_Item = true;
		}
	}

	void Item_respawn_Check()
	{
		item_.Item_Crash_Check(true);
	}

	void End_Check(Snake_Body* START)
	{
		Snake_Body* NODE = NULL;
		Snake_Body* NODE_REVERSE = NULL;

		//NODE_REVERSE = HEAD; 이거는 마지막에 하자
		for (int i = 0; i < Snake_Length; i++)
		{
			Snake_Body* NewNew = new Snake_Body();
			NewNew->Next = NULL;
			if (START != NULL)
			{
				NODE = START->Next;
				if (NODE_REVERSE == NULL)
				{
					START->Next = NULL;
				}

				if (NODE_REVERSE != NULL)
				{
					START->Next = NODE_REVERSE;

				}
				NODE_REVERSE = START;
				START = NODE;
			}

		}

		HEAD = NODE_REVERSE;
		//cout << "HEAD->NEXT->X : " << HEAD->Next->myXpos<<"HEAD->NEXT->Y : " << HEAD->Next->myYpos << endl;
	}

	void Increase_Node(Snake_Body * Last_Node)//왜 문제가 생기는 건지 확인해야함
	{
		Snake_Body* Plus_Node = new Snake_Body();
		cout << "PLUS_Node " << Last_Node->myXpos << " , " << Last_Node->myYpos << endl;
		Plus_Node->Next = Last_Node->Next;
		Plus_Node->myXpos = Last_Node->myXpos;
		Plus_Node->myYpos = Last_Node->myYpos;
		Last_Node->Next = Plus_Node;
		
	}



};

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
				map_State[i][j] = 1;
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
	Snake_Game Snake;
	Snake.Linked_Snake();

	char move; //키 입력을 받을 변수
		while (GAME)
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
				Snake.Snake_Moving(-1, 0);
				break;
			}
			case RIGHT:
			{
				//cout << "오른쪽 " << endl;
				Snake.Snake_Moving(1, 0);
				break;
			}
			case UP:
			{
				//cout << "위쪽 " << endl;
				Snake.Snake_Moving(0, -1);
				break;
			}
			case DOWN:
			{
				//cout << "아래쪽 " << endl;
				Snake.Snake_Moving(0, 1);
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
		cout << "게임오버" << endl;
		cout << "획득한 점수 : " << score << endl;
}