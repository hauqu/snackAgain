#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define random(x) (rand()%x)
#define MAX_N 100
#define SIZE 8
#define STAT_POS_Y 128
#define STAT_POS_X 128
#define WIN_LENGTH 640
#define WIN_HEIGHT 640

#pragma comment(lib,"winmm.lib")//���ؿ����ڲ�������
//�Զ�����������
enum DIR
{
	UP = 72, RIGHT = 77, LEFT = 75, DOWN = 80, STOP = 32
};
enum FOODTYPE
{
	ORANGE = 0, WATERMELON, COOKIR, STONE, BASKETBALL,MAN
};
struct  Point
{
	int pos_x;
	int pos_y;
};
struct  Snack
{
	int n;//��ǰ����
	DIR dir;//�ߵķ���
	struct Point point[MAX_N];//�ߵ�����
};
//ȫ�ֱ�������
struct Snack snack;//��
int food_x;//ʳ������
int food_y;//ʳ������
FOODTYPE food;
int FAIL;//�Ƿ�ʧ�ܱ���
IMAGE background;
IMAGE basketball; IMAGE orange; IMAGE watermelon; 
IMAGE cookie; IMAGE stone; IMAGE man;
//��������
int Start_Page(void);
void Initialize_snack(void);
void Draw_snack(void);
int Game(void);
void keypro(void);
void Draw_food(void);



int main()
{

	srand((int)time(0));
	initgraph(WIN_LENGTH, WIN_HEIGHT);
	int player_choose=Start_Page();
	if (player_choose==0)
	{
		//��ʼ��Ϸ
		Initialize_snack();
		Game();
	}
	if (player_choose==1)
	{
		return 0;//�˳���Ϸ
	}
	if (player_choose==2)
	{
		//����
		cleardevice();
		IMAGE START;
		loadimage(&START, L"start.jpg", WIN_LENGTH, WIN_HEIGHT);
		putimage(0, 0, &START);
		settextcolor(RED);
		settextstyle(32, 0, L"����");
		setbkmode(TRANSPARENT);
		outtextxy(200, 200, L"�����ˣ�����");
		outtextxy(200, 250, L"����ʱ�䣺2019");
		outtextxy(200, 300, L"��ԴЭ�飺BSD  ");
		outtextxy(200, 350, L"�汾��1.0  ");

	}



	_getch();
	return 0;
}

int Start_Page()//��ʼ����
{
	setbkmode(TRANSPARENT); //���屳��Ϊ��
	IMAGE START;
	loadimage(&START, L"start.jpg",WIN_LENGTH,WIN_HEIGHT);//��ʼ���汳��ͼƬ
	putimage(0, 0, &START);
	settextcolor(GREEN);
	settextstyle(32, 0, L"����");
	outtextxy(300, 440, L"��ʼ��Ϸ");
	settextcolor(RED);
	outtextxy(300, 500, L"�˳���Ϸ");
	outtextxy(300, 560, L"  ����  ");
	int key_value; //����ֵ
	int key = 0;//ѡ�ֵ
	do
	{
		key_value = _getch();
		if (key_value == 72)
		{
			key--;
			if (key == -1){ key++; }
		}
		if (key_value == 80)
		{
			key++;
			if (key == 3){ key--; }
		}
		switch (key)
		{
		case 0:
			settextcolor(GREEN);
			settextstyle(32, 0, L"����");
			outtextxy(300, 440, L"��ʼ��Ϸ");
			settextcolor(RED);
			outtextxy(300, 500, L"�˳���Ϸ");
			outtextxy(300, 560, L"  ����  ");
			break;
		case 1:
			settextcolor(RED);
			settextstyle(32, 0, L"����");
			outtextxy(300, 440, L"��ʼ��Ϸ");
			settextcolor(GREEN);
			outtextxy(300, 500, L"�˳���Ϸ");
			settextcolor(RED);
			outtextxy(300, 560, L"  ����  ");
			break;
		case 2:
			settextcolor(RED);
			settextstyle(32, 0, L"����");
			outtextxy(300, 440, L"��ʼ��Ϸ");
			outtextxy(300, 500, L"�˳���Ϸ");
			settextcolor(GREEN);
			outtextxy(300, 560, L"  ����  ");

		default:
			break;
		}

	} while (key_value != 13);
	return key;
}
void Initialize_snack()//��ʼ������
{
	mciSendString(L"open music.mp3 alias music", 0, 0, 0);
	mciSendString(L"play music.mp3  repeat", 0, 0, 0);
	snack.n = 5;
	snack.dir = RIGHT;
	snack.point[0].pos_x = STAT_POS_X;
	snack.point[0].pos_y = STAT_POS_Y;
	snack.point[1].pos_x = STAT_POS_X - SIZE;
	snack.point[1].pos_y = STAT_POS_Y;
	snack.point[2].pos_x = STAT_POS_X - SIZE * 2;
	snack.point[2].pos_y = STAT_POS_Y;
	snack.point[3].pos_x = STAT_POS_X - SIZE * 3;
	snack.point[3].pos_y = STAT_POS_Y;
	snack.point[4].pos_x = STAT_POS_X - SIZE * 4;
	snack.point[4].pos_y = STAT_POS_Y;
	 food_x = WIN_LENGTH / 2;
	 food_y = WIN_HEIGHT / 2;

	//��ʼһ����ڵ��ߣ�ʳ������
	  food = ORANGE;
	 //��ʼʳ�����
	 loadimage(&background, L"background.jpg", WIN_LENGTH, WIN_HEIGHT);
	 //��Ϸ����ı���ͼ
	 loadimage(&orange, L"orange.jpg", 2 * SIZE + 1,2*SIZE+1);
	 loadimage(&stone, L"stone.jpg", 2 * SIZE + 1, 2 * SIZE + 1);
	 loadimage(&basketball, L"basketball.jpg", 2 * SIZE + 1, 2 * SIZE + 1);
	 loadimage(&watermelon, L"watermelon.jpg", 2 * SIZE + 1, 2 * SIZE + 1);
	 loadimage(&man, L"man.jpg", 5 * SIZE + 1, 5 * SIZE + 1);
	 loadimage(&cookie, L"cookie.jpg", 2 * SIZE + 1, 2 * SIZE + 1);
	 //ʳ����ͼ
}
void Draw_snack() //������
{
	
	
	for (int i = 0; i <snack.n; i++)
	{
		setfillcolor(RGB(random(256), random(256), random(256)));//ɫ�������
		fillcircle(snack.point[i].pos_x, snack.point[i].pos_y, SIZE / 2);
	}
	char node[3];
	_itoa_s(100-snack.n, node, 10);//��һ��������ʮ������ʽ�����ַ�����
	outtextxy(600, 60,node[0]);//��ʾʣ��ʳ����
	outtextxy(620, 60, node[1]);
	if (snack.n%10==0)
	{
		settextcolor(RGB(random(255), random(255), random(255)));
		outtextxy(20, 60, L"���ո����ͣ�����������");
	}
}
int snack_move(DIR dir)//�ߵ��ƶ�
{
	if (dir==STOP)
	{
		return 0;
	}
	struct Point temp;//��ͷ���긱��
	temp.pos_x = snack.point[0].pos_x;
	temp.pos_y = snack.point[0].pos_y;
	
		
	snack.point[1].pos_y = snack.point[0].pos_y;
	switch (dir)
	{
	case UP:
		snack.point[0].pos_y = snack.point[0].pos_y-SIZE/2;
		break;
	case RIGHT:
		snack.point[0].pos_x = snack.point[0].pos_x + SIZE/2;
		break;
	case LEFT:
		snack.point[0].pos_x = snack.point[0].pos_x - SIZE/2;
		break;
	case DOWN:
		snack.point[0].pos_y = snack.point[0].pos_y + SIZE/2;
		break;
	case STOP:Sleep(500);
	default:
		break;
	}
	for (int i = 1; i <snack.n; i++)
	{
		if (snack.point[i].pos_x == snack.point[0].pos_x&&snack.point[i].pos_y == snack.point[0].pos_y)
		{
			outtextxy(WIN_LENGTH / 2-20, WIN_HEIGHT / 2-20, L"������,ҧ�����Լ�");
			return 1;//��ʾ�Ե��Լ�
			
		}
	}
	
	for (int i = snack.n-1; i >1; i--)//�ƶ�
	{
		snack.point[i].pos_x = snack.point[i - 1].pos_x;
		snack.point[i].pos_y = snack.point[i - 1].pos_y;

	}
	snack.point[1].pos_x = temp.pos_x;
	snack.point[1].pos_y = temp.pos_y;
	return 0;//û�Ե��Լ�
}
int Game()//��Ϸ������
{
	while (1)
	{
		while (!_kbhit())
		{
			putimage(0, 0, &background);
			if (abs(food_x - snack.point[0].pos_x)<SIZE&&abs(food_y-snack.point[0].pos_y)<SIZE)//��ԳԵ�ʳ��
			{
				//(food_x == snack.point[0].pos_x&&food_y == snack.point[0].pos_y)���ԳԵ�ʳ��
				food_x = SIZE*random(WIN_LENGTH / SIZE);
				food_y = SIZE*random(WIN_HEIGHT / SIZE);
				food = (FOODTYPE)random(6);
				snack.n++;
				if (snack.n == 100)//�ߴﵽ��󳤶�
				{
					break;
				}
				//����һ����
				if (snack.point[snack.n - 2].pos_x == snack.point[snack.n - 1].pos_x)
				{
					if (snack.point[snack.n - 2].pos_y > snack.point[snack.n - 1].pos_y)
					{
						snack.point[snack.n].pos_x = snack.point[snack.n - 1].pos_x;
						snack.point[snack.n].pos_y = snack.point[snack.n - 1].pos_y - SIZE;
					}
					else
					{
						snack.point[snack.n].pos_x = snack.point[snack.n - 1].pos_x;
						snack.point[snack.n].pos_y = snack.point[snack.n - 1].pos_y + SIZE;
					}
				}
				else
				{
					if (snack.point[snack.n - 2].pos_x > snack.point[snack.n - 1].pos_x)
					{
						snack.point[snack.n].pos_x = snack.point[snack.n - 1].pos_x - SIZE;
						snack.point[snack.n].pos_y = snack.point[snack.n - 1].pos_y;
					}
					else
					{
						snack.point[snack.n].pos_x = snack.point[snack.n - 1].pos_x + SIZE;
						snack.point[snack.n].pos_y = snack.point[snack.n - 1].pos_y;
					}
				}

			}


			FAIL = snack_move(snack.dir);
			if (FAIL)
			{
				return 0;
			}
			setfillcolor(GREEN);
			//fillcircle(food_x, food_y, SIZE);//��ʳ��
			Draw_food();
			Draw_snack();
			if (snack.point[0].pos_x<0)break;
			if (snack.point[0].pos_y<0)break;
			if (snack.point[0].pos_x>WIN_LENGTH)break;
			if (snack.point[0].pos_y>WIN_HEIGHT)break;

			Sleep(50);
		}
		if (snack.n == 100)	break;
		if (snack.point[0].pos_x<0)break;
		if (snack.point[0].pos_y<0)break;
		if (snack.point[0].pos_x>WIN_LENGTH)break;
		if (snack.point[0].pos_y>WIN_HEIGHT)break;
		keypro();

	}
	if (snack.n != 100)
	{
		outtextxy(WIN_LENGTH / 2, WIN_HEIGHT / 2, L"������,ײǽ����");
	}
	else
	{
		outtextxy(WIN_LENGTH / 2, WIN_HEIGHT / 2, L"��Ӯ�˴ﵽ��󳤶�100");
	}

}
void keypro()
{
	
	DIR key = (DIR)_getch();
	switch (key)
	{
	case UP:
		if (snack.dir!=DOWN)
		snack.dir = UP;
		break;
	case RIGHT:
		if (snack.dir != LEFT)
		snack.dir = RIGHT;
		break;
	case LEFT:
		if (snack.dir != RIGHT)
		snack.dir = LEFT;
		break;
	case DOWN:
		if (snack.dir != UP)
		snack.dir = DOWN;
		break;
	case STOP:
		snack.dir = STOP;

	default:
		
		
		break;
	}
}
void Draw_food()
{
	//fillcircle(food_x, food_y, SIZE);//��ʳ��
	int pos_x = food_x-SIZE;
	int pos_y = food_y-SIZE;

	
	switch (food)
	{
	case ORANGE:
		putimage(pos_x,pos_y, &orange);
		break;
	case WATERMELON:
		putimage(pos_x, pos_y, &watermelon);
		break;
	case COOKIR:
		putimage(pos_x, pos_y, &cookie);
		break;
	case STONE:
		putimage(pos_x, pos_y, &stone);
		break;
	case BASKETBALL:
		putimage(pos_x, pos_y, &basketball);
		break;
	case MAN:
		putimage(pos_x, pos_y, &man);
		break;
	default:
		break;
	}

}

//BUG �������ƶ���ʱ����һ����ʾ���ָ������ƶ�����
//BUG:ż��/����ʳ����ʧ����Ϸ�޷�����
