#include <graphics.h>
#include <conio.h>
#include<iostream>
#include<windows.h>
#include<ctime>
using namespace std;

//切割后的图片结构体
typedef struct  Image_part {
	IMAGE image;
	int x;		//左上横坐标
	int y;		//左上纵坐标
	int height = 213;  //高度
	int weight = 213;	//宽度
	int locate; // 该图片位置，左上0，右下8
	int nowlocate; //该图片当前位置

}Image_part;
int *BankLocate;// 空白所在位置

void Pic_welcome();
void Pic_play();
void Pic_introduction();
void Pic_win();
void waitchoose_w();
void waitchoose_i();
void waitchoose_p(Image_part* part);

void num_random(int num[9]);
void Pic_play_random(Image_part* part);
void move_down(Image_part* p);
void move_up(Image_part* p);
void move_left(Image_part* p);
void move_right(Image_part* p);

//输出欢迎界面,进入欢迎界面操作
void Pic_welcome() {
	setbkcolor(WHITE);
	cleardevice();

	//输出“拼图”标题
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 48;						// 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式

	setcolor(BLACK);
	//标题“拼图”
	wchar_t s1[] = L"拼 图";
	outtextxy(260, 30, s1);

	gettextstyle(&f);
	f.lfHeight = 24;						// 设置字体高度为24
	settextstyle(&f);

	//输出三个模式选项
	rectangle(200, 158, 440, 208);			//(200,158) -> (440,208)
	wchar_t s2[] = L"电脑模式";
	outtextxy(272, 171, s2);
	rectangle(200, 268, 440, 318);			//(200,268) -> (440,318)
	wchar_t s3[] = L"玩家模式";
	outtextxy(272, 281, s3);
	rectangle(200, 378, 440, 428);			//(200,378) -> (440,428)
	wchar_t s4[] = L"游戏介绍";
	outtextxy(272, 391, s4);

	waitchoose_w();
}
//输出玩家游戏界面，并进入游戏操作
void Pic_play() {
	setbkcolor(WHITE);
	cleardevice();

	//加载图片
	int i;
	IMAGE image;
	Image_part part[9];
	loadimage(&image, _T("test.jpg"), 640, 640);
	putimage(0, 0, &image);
	clearrectangle(426, 426, 640, 640);

	for (i = 0; i < 9; i++) {
		part[i].x = 213 * (i % 3);
		part[i].y = 213 * int(i / 3);
		part[i].locate = i;//初始化位置
		part[i].nowlocate = i;//当前位置
		getimage(&part[i].image, part[i].x, part[i].y, part[i].weight, part[i].height);
	}
	BankLocate = &part[8].nowlocate;
	Sleep(1000);
	Pic_play_random(part);
	waitchoose_p(part);
}
//输出游戏介绍界面，并进入介绍界面操作
void Pic_introduction() {
	setbkcolor(WHITE);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 48;						// 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	setcolor(BLACK);
	//标题 游戏介绍
	wchar_t s1[] = L"游戏介绍";
	wchar_t s2[] = L"1.通过鼠标点击移动对应的图片方块完成拼图。";
	//wchar_t s3[] = L"2.通过方向键移动图片完成拼图。";
	wchar_t s4[] = L"确认";
	int x;
	x = textwidth(s1);
	outtextxy(224, 30, s1);

	gettextstyle(&f);
	f.lfHeight = 24;
	settextstyle(&f);
	x = textwidth(s2);
	outtextxy(40, 150, s2);
	//x = textwidth(s3);
	//outtextxy(40, 200, s3);


	rectangle(280, 300, 360, 340);		//(280,300) -> (300,340)
	outtextxy(296, 310, s4);

	waitchoose_i();
}
//欢迎界面操作
void waitchoose_w() {
	ExMessage m;
	int flag = -1;
	flushmessage(); //清空消息
	while (1) {
		getmessage(&m, EM_MOUSE);
		//第一个框
		if (m.x > 200 && m.x < 440 && m.y>158 && m.y < 208) {
			setlinecolor(GREEN);
			rectangle(200, 158, 440, 208);
			setcolor(GREEN);
			wchar_t s2[] = L"电脑模式";
			outtextxy(272, 171, s2);
			if (m.lbutton) {

				flag = 1;
				break;
			}
		}
		else {
			setlinecolor(BLACK);
			rectangle(200, 158, 440, 208);
			setcolor(BLACK);
			wchar_t s2[] = L"电脑模式";
			outtextxy(272, 171, s2);
		}
		//第二个框
		if (m.x > 200 && m.x < 440 && m.y>268 && m.y < 318) {
			setlinecolor(GREEN);
			rectangle(200, 268, 440, 318);
			setcolor(GREEN);
			wchar_t s3[] = L"玩家模式";
			outtextxy(272, 281, s3);
			if (m.lbutton) {
				flag = 2;
				break;
			}
		}
		else {
			setlinecolor(BLACK);
			rectangle(200, 268, 440, 318);
			setcolor(BLACK);
			wchar_t s3[] = L"玩家模式";
			outtextxy(272, 281, s3);
		}
		//第三个框
		if (m.x > 200 && m.x < 440 && m.y>378 && m.y < 428) {
			setlinecolor(GREEN);
			rectangle(200, 378, 440, 428);
			setcolor(GREEN);
			wchar_t s4[] = L"游戏介绍";
			outtextxy(272, 391, s4);
			if (m.lbutton) {
				flag = 3;
				break;
			}
		}
		else {
			setlinecolor(BLACK);
			rectangle(200, 378, 440, 428);
			setcolor(BLACK);
			wchar_t s4[] = L"游戏介绍";
			outtextxy(272, 391, s4);
		}
	}

	switch (flag) {
	case 1: {
		break;
	}
	case 2: {
		Pic_play();
		break;
	}
	case 3: {
		Pic_introduction();
		break;
	}
	}

}
//介绍界面操作
void waitchoose_i() {
	ExMessage m;
	flushmessage(); //清空消息
	while (1) {
		peekmessage(&m, EM_MOUSE);
		if (m.x > 280 && m.x < 360 && m.y>300 && m.y < 340) {
			setlinecolor(GREEN);
			setcolor(GREEN);
			wchar_t s4[] = L"确认";
			rectangle(280, 300, 360, 340);
			outtextxy(296, 310, s4);
			if (m.lbutton) {
				break;
			}
		}
		else {
			setlinecolor(BLACK);
			setcolor(BLACK);
			wchar_t s4[] = L"确认";
			rectangle(280, 300, 360, 340);
			outtextxy(296, 310, s4);
		}

	}
	Pic_welcome();
}
//玩家游戏操作
void waitchoose_p(Image_part *part) {
	int i,flag=0; //flag=0表示图还没有拼好
	int m_move;		//标记当前块移动方向
	int m_locate;	//记录点击到的图片位置
	ExMessage m;

	flushmessage(); //清空缓存消息
	while (1) {
		getmessage(&m, EM_MOUSE);
		//getmessage(&k, EM_CHAR);
		if (m.lbutton) {
			
			m_locate = int(m.y / 213) * 3 + int(m.x / 213);
			for (i = 0; i < 9; i++) {
				if (part[i].nowlocate == m_locate) break;
			}
			//cout << "点击了当前第" << m_locate << endl;
			//cout << "这个应该在第" << part[i].locate << endl;
			if (m_locate - 3 == *BankLocate ) { 
				//cout << "向上移动了" << part[i].nowlocate << endl << endl;
				move_up(&part[i]); 
			}
			if (m_locate + 3 == *BankLocate) {
				//cout << "向下移动了" << part[i].nowlocate << endl << endl;
				move_down(&part[i]);
			}
			if (m_locate - 1 == *BankLocate && part[i].x!=0) {
				//cout << "向左移动了" << part[i].nowlocate << endl << endl;
				move_left(&part[i]);
			}
			if (m_locate + 1 == *BankLocate && part[i].x!=426) {
				//cout << "向右移动了" << part[i].nowlocate << endl<<endl;
				move_right(&part[i]);
			}
		}
		//if (k.ch == 'w' || k.ch == 'a' || k.ch == 's' || k.ch == 'd') {
		//	switch (k.ch) {
		//		case 'w': {
		//			for (i = 0; i < 9; i++) {
		//				if (part[i].nowlocate - 3 == *BankLocate) break;
		//			}
		//			move_up(&part[i]);
		//			break;
		//		}
		//		case 'a': {
		//			for (i = 0; i < 9; i++) {
		//				if (part[i].nowlocate - 1 == *BankLocate) break;
		//			}
		//			move_left(&part[i]);
		//			break;
		//		}
		//		case 's': {
		//			for (i = 0; i < 9; i++) {
		//				if (part[i].nowlocate + 3 == *BankLocate) break;
		//			}
		//			move_down(&part[i]);
		//			break;
		//		}
		//		case 'd': {
		//			for (i = 0; i < 9; i++) {
		//				if (part[i].nowlocate + 1 == *BankLocate) break;
		//			}
		//			move_right(&part[i]);
		//			break;
		//		}
		//	}

		//}

		for (i = 0; i < 9; i++) {
			if (part[i].locate != part[i].nowlocate) break;
			else {
				if (i == 8) flag = 1;
			}
		}
		if (flag == 1) break;
	}
	//成功后将完整图片输出
	Sleep(500);
	IMAGE image;
	loadimage(&image, _T("test.jpg"), 640, 640);
	putimage(0, 0, &image);
	Pic_win();
}
//游戏完成界面,退回欢迎界面
void Pic_win() {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 96;
	settextstyle(&f);
	setcolor(RED);
	wchar_t s1[] = L"恭喜完成";
	outtextxy(128, 272, s1);
	ExMessage m;
	flushmessage(); //清空缓存消息
	while (1) {
		getmessage(&m, EM_MOUSE);
		if (m.lbutton) break;
	}
	Pic_welcome();
}
//打乱算法,生成一段可以被还原的乱序数（0-8）
void num_random(int num[9]) {
	int s,i,j,temp;
	int key;
	int num_clone[9];
	while (1) {
		key = 0;
		srand((int)time(0));
		for (i = 0; i < 9; i++) {
			s = rand() % 9;
			temp = num[i];
			num[i] = num[s];
			num[s] = temp;
		}
		//计算随机数对应图的奇偶性
		for (i = 0; i < 9; i++) {
			num_clone[i] = (num[i] + 1) % 9;
		}
		for (i = 0; i < 8; i++) { 
			for (j = i + 1; j < 9; j++) {
				if ((num_clone[j] != 0) && (num_clone[j] < num_clone[i]) ) {
					key++;
				}
			}
		}
		if (key % 2 == 0) break;
	}
}
//打乱图片
void Pic_play_random(Image_part* part) {
	int i,x,y;
	int num[9] = { 0,1,2,3,4,5,6,7,8 };
	num_random(num);
	for (i = 0; i < 9; i++) {
		cout << num[i] << endl;
	}

	for (i = 0; i < 9; i++) {
		x = 213 * int(i % 3);	//输出位置的横坐标
		y = 213 * (i / 3);		//输出位置的纵坐标
		part[num[i]].x = x;
		part[num[i]].y = y;
		part[num[i]].nowlocate = i;
		putimage(part[num[i]].x, part[num[i]].y, &(part[num[i]].image));
	}
}

//移动操作
void move_down(Image_part* p) {
	clearrectangle(p->x, p->y, (p->x) + (p->weight), (p->y) + (p->height));
	p->y = p->y + 213;
	p->nowlocate = p->nowlocate + 3;  //下移一位位置参数+3
	putimage(p->x, p->y, &p->image);
	*BankLocate = *BankLocate - 3;//更新空白
}
void move_up(Image_part* p) {
	clearrectangle(p->x, p->y, (p->x) + (p->weight), (p->y) + (p->height));
	p->y = p->y - 213;
	p->nowlocate = p->nowlocate - 3;	//上移一位位置参数-3
	putimage(p->x, p->y, &p->image);
	*BankLocate = *BankLocate + 3;
}
void move_left(Image_part* p) {
	clearrectangle(p->x, p->y, (p->x) + (p->weight), (p->y) + (p->height));
	p->x = p->x - 213;
	p->nowlocate = p->nowlocate - 1;	//左移一位位置参数-1
	putimage(p->x, p->y, &p->image);
	*BankLocate = *BankLocate + 1;
}
void move_right(Image_part* p) {
	clearrectangle(p->x, p->y, (p->x) + (p->weight), (p->y) + (p->height));
	p->x = p->x + 213;
	p->nowlocate = p->nowlocate + 1;	//右移一位位置参数+1
	putimage(p->x, p->y, &p->image);
	*BankLocate = *BankLocate - 1;
}

int main(void) {

	initgraph(640, 640, EW_SHOWCONSOLE);
	Pic_welcome();   //加载欢迎界面
	_getch();
	closegraph();
	return 0;
}