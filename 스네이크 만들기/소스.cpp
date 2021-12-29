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
}//�� ��ȯ��Ű�� �Լ�

	void SavePosValue(int* xpos, int* ypos, Snake_Body * New_Body)
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

				cout << Cur->myXpos << " , " << Cur->myYpos << endl;
				Cur = Cur->Next;
			}
			
		}
	}//�⺻ �� ���� �� �̵��� �� ��ġ ���浵 ������
	//�⺻ �� ���� �� �̵��� �� ��ġ ���浵 ������
	//���� ���̰� �þ�� ���� �޶����� �� ������ ����


	void Snake_Moving(int x = 0, int y = 0)// �Ű������� x�� ���� ������ų��, y�� ���� ������ų�� �����ֱ�
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
		for (int i = 0; i < Snake_Length; i++) //�ʱ�ȭ �����ֱ�
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
			for (int i = 0; i < Snake_Length; i++) // �̵��� ���� ��� �̰� ������ �Ǿ� ��
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
							//cout << "1�� ����" << endl;

							New_Snake->Next->myXpos = New_Snake->myXpos;
							New_Snake->Next->myYpos = New_Snake->myYpos;

						}
						else if (v_t.HasValue == true && v_t_2.HasValue == false)
						{
							v_t_2.xpos_temp_2 = New_Snake->Next->myXpos; v_t_2.ypos_temp_2 = New_Snake->Next->myYpos;
							v_t_2.HasValue = true;
							//cout << "2�� ����" << endl;
							New_Snake->Next->myXpos = v_t.xpos_temp_1;
							New_Snake->Next->myYpos = v_t.ypos_temp_1;
							v_t.HasValue = false;
						}
						else if (v_t.HasValue == false && v_t_2.HasValue == true)
						{
							v_t.xpos_temp_1 = New_Snake->Next->myXpos; v_t.ypos_temp_1 = New_Snake->Next->myYpos;
							v_t.HasValue = true;
							//cout << "3�� ����" << endl;
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
			//�������� ���ϰ� �׳� �Ѿ���� ������ֱ�
			//x�� y 0���� �ٲ��ֱ�
			*x = 0; *y = 0;
			*move = false;
		}
		else if (map_State[Cur->myYpos + *y][Cur->myXpos + *x] == 2)
		{
			Snake_Length++;
			//cout << "�����۰� �浹" << endl;
			item_.Item_Crash_Check(true);  
		}
		else
		{
			if (map_State[Cur->myYpos + *y][Cur->myXpos + *x] == 1)
			{
				//�̵��Ϸ��� ��ġ�� �� �������� Ȯ���ϰ� �ƴ϶�� �������� ��Ű�� �������
				//cout << "�浹�Ͽ����ϴ�."; // �� ��µ�
			}
		}
	}
};



void Game_Over()
{
	//���� ���� ��½����ְ� �������� �����ֱ� 
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
	sNake.Linked_Snake(); //���� ó�� ������ũ ���� ������ֱ�
	Map();
	char move; //Ű �Է��� ���� ����
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
			//cout << "���� " << endl;
			sNake.Snake_Moving(-1, 0);
			break;
		}
		case RIGHT:
		{
			//cout << "������ " << endl;
			sNake.Snake_Moving(1, 0);
			break;
		}
		case UP:
		{
			//cout << "���� " << endl;
			sNake.Snake_Moving(0, -1);
			break;
		}
		case DOWN:
		{
			//cout << "�Ʒ��� " << endl;
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
		



	//Linked_Snake();//�⺻ �� ���� �� �̵��� �� ��ġ ���浵 ������
	//���� ���̰� �þ�� ���� �޶����� �� ������ ����

	int player_length = 4; //�÷��̾��� ���� ���� 
	int score = 0; // ������ �Ծ��� �� �� ������ ���� 1�� ���� ��Ŵ

	



	return 0;
}


