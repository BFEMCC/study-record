#include <iostream>
#include <iomanip>
using namespace std;
float kaigenghaodayu1(float a)
{
	float low = 0;
	float high = a;
	float median = high / 2;
	if (a > 1)
	{
		for (int i = 0; i < 70; i++)
		{
			if (median * median < a)
			{
				low = median;
				median = (low + high) / 2;
			}
			else if (median * median > a)
			{
				high = median;
				median = (low + high) / 2;
			}
			else
				break;
		}
	}
	return median;
}
int main()
{
lab:
	float n;
	cout << "���뱻��������";
	cin >> n;
	cout << endl;
	int m = 0;
	if (n > 1)
	{
		cout << "���뱣����С��λ�����������룩��";
		cin >> m;
		cout << endl;
		cout << "�����" << setiosflags(ios::fixed) << setprecision(m) << kaigenghaodayu1(n) << endl; // �������뱣����λС��
	}
	else if (n <= 1 && n >= 0)
	{
		cout << "���뱣����С��λ�����������룩��";
		cin >> m;
		cout << endl;
		cout << "�����" << setiosflags(ios::fixed) << setprecision(m) << kaigenghaodayu1(n * 10) / kaigenghaodayu1(10) << endl; // �������뱣����λС��
	}
	else
	{
		cout << "������������Ϊ�Ǹ�����" << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	goto lab;
	return 0;
}