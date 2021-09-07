#include <graphics.h>
#include <conio.h>
#include<iostream>

using namespace std;

//初始化游戏界面
void gameinit() {
	initgraph(640, 640, EW_SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();

	//输出“拼图”标题
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 48;						// 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	wchar_t s1[] = L"拼 图";
	int x = 320 - (textwidth(s1) / 2);
	int y = 30;
	//cout << textwidth(s1) << endl;		//测试字体长宽
	//cout << textheight(s1) << endl;
	setcolor(BLACK);
	outtextxy(x, y, s1);
	
	//输出三个模式选项
	gettextstyle(&f);
	f.lfHeight = 24;						// 设置字体高度为
	settextstyle(&f);
	rectangle(200, 158, 440, 208);			//(200,158) -> (440,208)
	wchar_t s2[] = L"电脑模式";
	outtextxy(272, 171, s2);
	rectangle(200, 268, 440, 318);			//(200,268) -> (440,318)
	wchar_t s3[] = L"玩家模式";
	outtextxy(272, 281, s3);
	rectangle(200, 378, 440, 428);			//(200,378) -> (440,428)
	wchar_t s4[] = L"游戏介绍";
	outtextxy(272, 391, s4);


}

int waitchoose() {
	ExMessage m;
	while (1) {
		peekmessage(&m, EM_MOUSE);
		//第一个框
		if (m.x > 200 && m.x < 440 && m.y>158 && m.y < 208) {
			setlinecolor(GREEN);
			rectangle(200, 158, 440, 208);
			setcolor(GREEN);
			wchar_t s2[] = L"电脑模式";
			outtextxy(272, 171, s2);
			if (m.lbutton) {
				cout << "点击了一下" << endl;
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
				cout << "点击了一下" << endl;
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
				cout << "点击了一下" << endl;
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

	return 0;
}


int main(void) {
	int choose;

	gameinit();//初始化游戏，加载背景图片，输出选项（电脑，玩家，介绍）
	choose=waitchoose();//等待玩家选择选项，并进入相关模式
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