#include <stdio.h>

//���� ó���� ��� �Ǵ��� �ñ��ؼ� ���� �Լ�
void test()
{
	FILE* fp = fopen("test.txt", "w");
	fprintf(fp, "%d&%d&%d&%d\n", 6, 6, 6, 6);
	fprintf(fp, "%d&%d&%d&%d\n", 7, 7, 7, 7);
	fprintf(fp, "%d&%d&%d&%d\n", 6, 6, 6, 6);
	fclose(fp);
	fp = fopen("test.txt", "r");
	long pos=0;
	int a, b, c, d;
	while (!feof(fp))
	{
		pos = ftell(fp);
		fscanf(fp, "%d&%d&%d&%d\n", &a, &b, &c, &d);
	}
	fclose(fp);
	fp = fopen("test.txt", "r+");
	fseek(fp, pos, SEEK_SET);
	fprintf(fp, "%d&%d&%d&%d\n", 8, 8, 8, 8);
	fclose(fp);
}