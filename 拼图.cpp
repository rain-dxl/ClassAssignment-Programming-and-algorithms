#include <graphics.h>
#include <conio.h>
#include<iostream>
#include<windows.h>
#include<ctime>
using namespace std;

//�и���ͼƬ�ṹ��
typedef struct  Image_part {
	IMAGE image;
	int x;		//���Ϻ�����
	int y;		//����������
	int height = 213;  //�߶�
	int weight = 213;	//���
	int locate; // ��ͼƬλ�ã�����0������8
	int nowlocate; //��ͼƬ��ǰλ��

}Image_part;
int *BankLocate;// �հ�����λ��

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

//�����ӭ����,���뻶ӭ�������
void Pic_welcome() {
	setbkcolor(WHITE);
	cleardevice();

	//�����ƴͼ������
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 48;						// ��������߶�Ϊ 48
	_tcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ

	setcolor(BLACK);
	//���⡰ƴͼ��
	wchar_t s1[] = L"ƴ ͼ";
	outtextxy(260, 30, s1);

	gettextstyle(&f);
	f.lfHeight = 24;						// ��������߶�Ϊ24
	settextstyle(&f);

	//�������ģʽѡ��
	rectangle(200, 158, 440, 208);			//(200,158) -> (440,208)
	wchar_t s2[] = L"����ģʽ";
	outtextxy(272, 171, s2);
	rectangle(200, 268, 440, 318);			//(200,268) -> (440,318)
	wchar_t s3[] = L"���ģʽ";
	outtextxy(272, 281, s3);
	rectangle(200, 378, 440, 428);			//(200,378) -> (440,428)
	wchar_t s4[] = L"��Ϸ����";
	outtextxy(272, 391, s4);

	waitchoose_w();
}
//��������Ϸ���棬��������Ϸ����
void Pic_play() {
	setbkcolor(WHITE);
	cleardevice();

	//����ͼƬ
	int i;
	IMAGE image;
	Image_part part[9];
	loadimage(&image, _T("test.jpg"), 640, 640);
	putimage(0, 0, &image);
	clearrectangle(426, 426, 640, 640);

	for (i = 0; i < 9; i++) {
		part[i].x = 213 * (i % 3);
		part[i].y = 213 * int(i / 3);
		part[i].locate = i;//��ʼ��λ��
		part[i].nowlocate = i;//��ǰλ��
		getimage(&part[i].image, part[i].x, part[i].y, part[i].weight, part[i].height);
	}
	BankLocate = &part[8].nowlocate;
	Sleep(1000);
	Pic_play_random(part);
	waitchoose_p(part);
}
//�����Ϸ���ܽ��棬��������ܽ������
void Pic_introduction() {
	setbkcolor(WHITE);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 48;						// ��������߶�Ϊ 48
	_tcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	setcolor(BLACK);
	//���� ��Ϸ����
	wchar_t s1[] = L"��Ϸ����";
	wchar_t s2[] = L"1.ͨ��������ƶ���Ӧ��ͼƬ�������ƴͼ��";
	//wchar_t s3[] = L"2.ͨ��������ƶ�ͼƬ���ƴͼ��";
	wchar_t s4[] = L"ȷ��";
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
//��ӭ�������
void waitchoose_w() {
	ExMessage m;
	int flag = -1;
	flushmessage(); //�����Ϣ
	while (1) {
		getmessage(&m, EM_MOUSE);
		//��һ����
		if (m.x > 200 && m.x < 440 && m.y>158 && m.y < 208) {
			setlinecolor(GREEN);
			rectangle(200, 158, 440, 208);
			setcolor(GREEN);
			wchar_t s2[] = L"����ģʽ";
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
			wchar_t s2[] = L"����ģʽ";
			outtextxy(272, 171, s2);
		}
		//�ڶ�����
		if (m.x > 200 && m.x < 440 && m.y>268 && m.y < 318) {
			setlinecolor(GREEN);
			rectangle(200, 268, 440, 318);
			setcolor(GREEN);
			wchar_t s3[] = L"���ģʽ";
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
			wchar_t s3[] = L"���ģʽ";
			outtextxy(272, 281, s3);
		}
		//��������
		if (m.x > 200 && m.x < 440 && m.y>378 && m.y < 428) {
			setlinecolor(GREEN);
			rectangle(200, 378, 440, 428);
			setcolor(GREEN);
			wchar_t s4[] = L"��Ϸ����";
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
			wchar_t s4[] = L"��Ϸ����";
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
//���ܽ������
void waitchoose_i() {
	ExMessage m;
	flushmessage(); //�����Ϣ
	while (1) {
		peekmessage(&m, EM_MOUSE);
		if (m.x > 280 && m.x < 360 && m.y>300 && m.y < 340) {
			setlinecolor(GREEN);
			setcolor(GREEN);
			wchar_t s4[] = L"ȷ��";
			rectangle(280, 300, 360, 340);
			outtextxy(296, 310, s4);
			if (m.lbutton) {
				break;
			}
		}
		else {
			setlinecolor(BLACK);
			setcolor(BLACK);
			wchar_t s4[] = L"ȷ��";
			rectangle(280, 300, 360, 340);
			outtextxy(296, 310, s4);
		}

	}
	Pic_welcome();
}
//�����Ϸ����
void waitchoose_p(Image_part *part) {
	int i,flag=0; //flag=0��ʾͼ��û��ƴ��
	int m_move;		//��ǵ�ǰ���ƶ�����
	int m_locate;	//��¼�������ͼƬλ��
	ExMessage m;

	flushmessage(); //��ջ�����Ϣ
	while (1) {
		getmessage(&m, EM_MOUSE);
		//getmessage(&k, EM_CHAR);
		if (m.lbutton) {
			
			m_locate = int(m.y / 213) * 3 + int(m.x / 213);
			for (i = 0; i < 9; i++) {
				if (part[i].nowlocate == m_locate) break;
			}
			//cout << "����˵�ǰ��" << m_locate << endl;
			//cout << "���Ӧ���ڵ�" << part[i].locate << endl;
			if (m_locate - 3 == *BankLocate ) { 
				//cout << "�����ƶ���" << part[i].nowlocate << endl << endl;
				move_up(&part[i]); 
			}
			if (m_locate + 3 == *BankLocate) {
				//cout << "�����ƶ���" << part[i].nowlocate << endl << endl;
				move_down(&part[i]);
			}
			if (m_locate - 1 == *BankLocate && part[i].x!=0) {
				//cout << "�����ƶ���" << part[i].nowlocate << endl << endl;
				move_left(&part[i]);
			}
			if (m_locate + 1 == *BankLocate && part[i].x!=426) {
				//cout << "�����ƶ���" << part[i].nowlocate << endl<<endl;
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
	//�ɹ�������ͼƬ���
	Sleep(500);
	IMAGE image;
	loadimage(&image, _T("test.jpg"), 640, 640);
	putimage(0, 0, &image);
	Pic_win();
}
//��Ϸ��ɽ���,�˻ػ�ӭ����
void Pic_win() {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 96;
	settextstyle(&f);
	setcolor(RED);
	wchar_t s1[] = L"��ϲ���";
	outtextxy(128, 272, s1);
	ExMessage m;
	flushmessage(); //��ջ�����Ϣ
	while (1) {
		getmessage(&m, EM_MOUSE);
		if (m.lbutton) break;
	}
	Pic_welcome();
}
//�����㷨,����һ�ο��Ա���ԭ����������0-8��
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
		//�����������Ӧͼ����ż��
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
//����ͼƬ
void Pic_play_random(Image_part* part) {
	int i,x,y;
	int num[9] = { 0,1,2,3,4,5,6,7,8 };
	num_random(num);
	for (i = 0; i < 9; i++) {
		cout << num[i] << endl;
	}

	for (i = 0; i < 9; i++) {
		x = 213 * int(i % 3);	//���λ�õĺ�����
		y = 213 * (i / 3);		//���λ�õ�������
		part[num[i]].x = x;
		part[num[i]].y = y;
		part[num[i]].nowlocate = i;
		putimage(part[num[i]].x, part[num[i]].y, &(part[num[i]].image));
	}
}

//�ƶ�����
void move_down(Image_part* p) {
	clearrectangle(p->x, p->y, (p->x) + (p->weight), (p->y) + (p->height));
	p->y = p->y + 213;
	p->nowlocate = p->nowlocate + 3;  //����һλλ�ò���+3
	putimage(p->x, p->y, &p->image);
	*BankLocate = *BankLocate - 3;//���¿հ�
}
void move_up(Image_part* p) {
	clearrectangle(p->x, p->y, (p->x) + (p->weight), (p->y) + (p->height));
	p->y = p->y - 213;
	p->nowlocate = p->nowlocate - 3;	//����һλλ�ò���-3
	putimage(p->x, p->y, &p->image);
	*BankLocate = *BankLocate + 3;
}
void move_left(Image_part* p) {
	clearrectangle(p->x, p->y, (p->x) + (p->weight), (p->y) + (p->height));
	p->x = p->x - 213;
	p->nowlocate = p->nowlocate - 1;	//����һλλ�ò���-1
	putimage(p->x, p->y, &p->image);
	*BankLocate = *BankLocate + 1;
}
void move_right(Image_part* p) {
	clearrectangle(p->x, p->y, (p->x) + (p->weight), (p->y) + (p->height));
	p->x = p->x + 213;
	p->nowlocate = p->nowlocate + 1;	//����һλλ�ò���+1
	putimage(p->x, p->y, &p->image);
	*BankLocate = *BankLocate - 1;
}

int main(void) {

	initgraph(640, 640, EW_SHOWCONSOLE);
	Pic_welcome();   //���ػ�ӭ����
	_getch();
	closegraph();
	return 0;
}