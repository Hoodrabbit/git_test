#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
using namespace std;
//���

// �����¿� ����� ����
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
			//cout << "�� �ȵ���" << endl;
			Item_Respawn(arr);
			Start = false;
		}
		//char item = 0xDA; //��������� ���� ����
		/*if (Crash_Check == NULL)
		{
			Item_Respawn(arr);
			Crash_Check = false;
		}*/
		//itemX = NULL, itemY = NULL;
	   //�������� ���� ��ġ static���� ������ ���� �ʴ´ٸ� �Լ��� ����� ������ ���� �޶��������� �̷��� ����

	   //������ ���� ��ġ�� �ٸ��� �̸� Ȯ���ϰ� ������ ��ġ �̵�
		//Item_Respawn(arr);

		if (Crash_Check == true)
		{
			//cout << "�⵿ ����" << endl;
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
	//�̸��� �̷��� ���Ḯ��Ʈ�� �� ������ 
	//�׷��ϲ� Snake_Tail->Next == NULL�� ��带 �� ���� �����������


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
	}//�� ��ȯ��Ű�� �Լ�

	void SavePosValue(int* xpos, int* ypos, Snake_Body* New_Body)
	{
		*xpos = New_Body->myXpos;
		*ypos = New_Body->myYpos;
	}

public:

	void Linked_Snake()
	{

		int xpos = 0;//���� �̷���
		int ypos = 0;//���� ���� ����غ���


		for (int i = 0; i < Snake_Length; i++)
		{
			New_Snake = new Snake_Body();
			New_Snake->Next = NULL;
			if (Snake_Head == NULL)
			{
				//New_Snake = new Snake_Body();

				New_Snake->myXpos = rand() % 18 + 1; // 0�� 19�� ���̶� ������ �� �κп����� ������ �Ǹ� �ȵǴϱ�  
				New_Snake->myYpos = rand() % 18 + 1; // 1~18���� ������ �� �ֵ��� �������

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
	}//�⺻ �� ���� �� �̵��� �� ��ġ ���浵 ������
	//�⺻ �� ���� �� �̵��� �� ��ġ ���浵 ������
	//���� ���̰� �þ�� ���� �޶����� �� ������ ����


	void Snake_Moving(int x, int y)// �Ű������� x�� ���� ������ų��, y�� ���� ������ų�� �����ֱ�
	{
		bool move = true;
		bool Get_Item = false;
		bool already_use = false;
		//���⿡ ������ ��� �ٷ� �� ��带 ����Ű�� ������ ���� �������� ���߿� ���� �� ����
		
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
			for (int i = 0; i < Snake_Length; i++) //�ʱ�ȭ �����ֱ�
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
						Increase_Node(Last_Node); //���� Get_Item�� ��𿡼� true�� ������ ���� �����غ�����
						//cout << "ITEM : " << Last_Ndoe->myXpos << " , " << Last_Ndoe->myYpos << endl;
						already_use = true;
					}


					if (NEW_SNAKE->Next == NULL)
					{
						//cout << "������ �ǰ� �ֳ��� " << endl;
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
								cout << "üũ" << endl;
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

	void Crash_Check(int* x, int* y, bool* move, bool * Get_Item)//�̺κ� �����������
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
			if (Cur->Next != NULL)//�̺κ� �����ؾ��Ԥ�������������2022-01-18
			{
				if (LastNode->myXpos + *x == Cur->myXpos && LastNode->myYpos + *y == Cur->myYpos && Cur != HEAD)
				{//��尡 ����϶��� �ϴ� �� ��ġ�� �ݵ�� �������ϱ� �� ��Ȳ�� �����ؾ���
					cout << "�۵�" << endl;
					*x = 0; *y = 0;
					*move = false;
				}
				Cur = Cur->Next;
			}
			
		}


		if (map_State[LastNode->myYpos + *y][LastNode->myXpos + *x] == 1)//? d�̷��� �ϴ°� �ƴѰ�
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

		//NODE_REVERSE = HEAD; �̰Ŵ� �������� ����
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

	void Increase_Node(Snake_Body * Last_Node)//�� ������ ����� ���� Ȯ���ؾ���
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

	char move; //Ű �Է��� ���� ����
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
				//cout << "���� " << endl;
				Snake.Snake_Moving(-1, 0);
				break;
			}
			case RIGHT:
			{
				//cout << "������ " << endl;
				Snake.Snake_Moving(1, 0);
				break;
			}
			case UP:
			{
				//cout << "���� " << endl;
				Snake.Snake_Moving(0, -1);
				break;
			}
			case DOWN:
			{
				//cout << "�Ʒ��� " << endl;
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
		cout << "���ӿ���" << endl;
		cout << "ȹ���� ���� : " << score << endl;
}