#include <graphics.h>
#include <conio.h>
#include<iostream>

using namespace std;

//��ʼ����Ϸ����
void gameinit() {
	initgraph(640, 640, EW_SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();

	//�����ƴͼ������
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 48;						// ��������߶�Ϊ 48
	_tcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	wchar_t s1[] = L"ƴ ͼ";
	int x = 320 - (textwidth(s1) / 2);
	int y = 30;
	//cout << textwidth(s1) << endl;		//�������峤��
	//cout << textheight(s1) << endl;
	setcolor(BLACK);
	outtextxy(x, y, s1);
	
	//�������ģʽѡ��
	gettextstyle(&f);
	f.lfHeight = 24;						// ��������߶�Ϊ
	settextstyle(&f);
	rectangle(200, 158, 440, 208);			//(200,158) -> (440,208)
	wchar_t s2[] = L"����ģʽ";
	outtextxy(272, 171, s2);
	rectangle(200, 268, 440, 318);			//(200,268) -> (440,318)
	wchar_t s3[] = L"���ģʽ";
	outtextxy(272, 281, s3);
	rectangle(200, 378, 440, 428);			//(200,378) -> (440,428)
	wchar_t s4[] = L"��Ϸ����";
	outtextxy(272, 391, s4);


}

int waitchoose() {
	ExMessage m;
	while (1) {
		peekmessage(&m, EM_MOUSE);
		//��һ����
		if (m.x > 200 && m.x < 440 && m.y>158 && m.y < 208) {
			setlinecolor(GREEN);
			rectangle(200, 158, 440, 208);
			setcolor(GREEN);
			wchar_t s2[] = L"����ģʽ";
			outtextxy(272, 171, s2);
			if (m.lbutton) {
				cout << "�����һ��" << endl;
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
				cout << "�����һ��" << endl;
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
				cout << "�����һ��" << endl;
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

	return 0;
}


int main(void) {
	int choose;

	gameinit();//��ʼ����Ϸ�����ر���ͼƬ�����ѡ����ԣ���ң����ܣ�
	choose=waitchoose();//�ȴ����ѡ��ѡ����������ģʽ
	//switch (choose){
	//	case 1: {
	//		conputer();
	//		break;
	//		}
	//	case 2: {
	//		play();
	//		break;
	//		}
	//	case 3: {
	//		introduction();
	//		break;
	//	}
	//}
	_getch();
	closegraph();
	return 0;
}