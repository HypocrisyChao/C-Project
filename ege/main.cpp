#include <graphics.h>

int main()
{
	initgraph(640, 480);


	setviewport(200, 100, 330, 130, 1);
	//�����ӿھ�������Ϊ(200,100) - (330, 130)
	//���һ������Ϊ1��ʾ������������ͼ�λᱻ�ü�
	//�������滭��ͼ�ε�ԭ������(0,0)����ӳ�䵽(200,100)

	setcolor(EGERGB(0x0, 0xFF, 0x0));
	setfontbkcolor(RGB(0x80, 0x00, 0x80));
	setfont(18, 0, "����");
	outtextxy(0, 0, "Hello EGE Graphics");

	setbkmode(TRANSPARENT);
	outtextxy(0, 20, "Hello EGE Graphics");

	setviewport(0, 0, getwidth(), getheight(), 1);
	//�����ӿ�Ϊ��������
	outtextxy(0, 0, "Hello EGE Graphics");

	getch();

	closegraph();
	return 0;
}

