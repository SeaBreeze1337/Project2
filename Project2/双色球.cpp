#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include <ctime>

using namespace std;

//��ȡ�û��ڿ���̨�������һ������
int getNumberInput() {
	int input = 0;
	cin >> input;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "��������������������" << endl;
		cin >> input;
	}
	return input;
}

//ð�����򣬶�˫ɫ��ǰ6�������������
void sortBalls(int* balls) 
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5 - 1 - i; j++)
		{
			if (balls[j]>balls[j+1])
			{
				int temp = balls[j];
				balls[j] = balls[j + 1];
				balls[j + 1] = temp;
			}
		}
	}
}

//��ѡ����
int* getCustomBalls() {

	//����һ�����飬������7�������洢6�������1������
	//��Ϊ������Ҫ������������ʹ��������飬��˲�����ջ�ռ俪�����飬Ӧ���ڶѿռ俪��
	int* balls = new int[7];

input_red_balls:
	cout << "������6��������룺";
	for (int i = 0; i < 6; i++)
	{
		balls[i] = getNumberInput();
	}
	//����������
	sortBalls(balls);
	//�жϺ����Ƿ�Խ��
	if (balls[0]<1||balls[5]>33)
	{
		cout << "����Խ�磬���������룡" << endl;
		goto input_red_balls;
	}

	//�жϺ����Ƿ��ظ�
	for (int i = 0; i < 5; i++)
	{
		if (balls[i] == balls[i + 1])
		{
			//˵�����ظ�Ԫ��
			cout << "�����ظ��ˣ����������룡" << endl;
			goto input_red_balls;
		}
	}

input_blue_balls:
	cout << "������һ������";
	balls[6] = getNumberInput();
	if (balls[6]>16||balls[6]<1)
	{
		//˵��Խ��
		cout << "����Խ�磬���������룡" << endl;
		goto input_blue_balls;
	}


	return balls;
}

//��ѡ����
int* getRandomBalls() {
	//����һ�����飬�����洢������ɵ�˫ɫ��
	int* balls = new int[7];

	//��������Դ�����д洢1-33�����֣�����Χ��
	int* datapool = new int[33];
	for (int i = 0; i < 33; i++){
		datapool[i] = i + 1;
	}

	//���balls
	for (int i = 0; i < 6; i++)
	{
		//��������Դ�ĳ���
		int len = 33 - i;
		//������Դ�����ȡһ��������±�
		int randomIndex = rand() % len;
		//������Դ�����У�ͨ������±꣬��ȡԪ�أ�������ӵ�balls������
		balls[i] = datapool[randomIndex];
		//��������Դ
		int* temp = new int[len - 1];
		for (int i1 = 0,i2 = 0; i1 < len; i1++)
		{
			if (i1 == randomIndex) {
				continue;
			}
			temp[i2++] = datapool[i1];
		}
		delete datapool;
		datapool = temp;
	}
	//����������
	sortBalls(balls);

	//�������������
	balls[6] = rand() % 16 + 1;






	return balls;
}

//��ʽ������������ؽ��
string descBalls(int* balls) {
	stringstream ss;
	ss << "����";
		for (int i = 0; i < 7; i++){
			ss <<setw(2)<< setfill('0') << balls[i];
			if (i < 5) {
				ss << ", ";
			}
			else if (i==5){
				ss << ", ����";
			}
		}
	return ss.str();
}


//�ȶ���ע˫ɫ��ȷ�����Ƚ�
int  getTicketLevel(int* userBalls,int* systemBalls) {
	//���������������ֱ�������¼�����������н�����
	int redCount = 0, blueCount = 0;
	//�˶Ժ����н�������
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++) {
			if (userBalls[i] == systemBalls[j]) {
				redCount++;
				break;
			}
		}
	}
	//�˶���������
	blueCount = userBalls[6] == systemBalls[6];

	//ȷ������
	if (redCount==6&&blueCount==1){
		return 1;
	}
	else if (redCount == 6 && blueCount == 0){
		return 2;
	}
	else if (redCount == 5 && blueCount == 1) {
		return 3;
	}
	else if (redCount + blueCount == 5) {
		return 4;
	}
	else if (redCount + blueCount == 4) {
		return 5;
	}
	else if (blueCount ==1 ) {
		return 6;
	}
	return 7;
}


int getMoney(int level) {
	switch (level)
	{
	case 1:
		return 5000000;
	case 2:
		return 800000;
	case 3:
		return 3000;
	case 4:
		return 200;
	case 5:
		return 10;
	case 6:
		return 5;
		case 7:
		return 0;
	default:
		break;
	}
}

void playGame() {

	
	int userChoice = -1; //��������������洢�û��Ĳ���

	
	bool flag = 1;//����һ��������������¼��Ϸ�Ƿ����

	
	int* userBalls=NULL; //����һ��ָ�룬ָ���û�ѡ���˫ɫ��

	while (flag)
	{
		cout << "*******************" << endl;
		cout << "* ���������ѡ��" << endl;
		cout << "* 1.��ѡ����           " << endl;
		cout << "* 2.��ѡ����           " << endl;
		cout << "* 0.�˳�                  " << endl;
		cout << "*******************" << endl;

		userChoice = getNumberInput();
		switch (userChoice)
		{
		case 0:
			flag = 0;
			break;
		case 1:
			userBalls=getCustomBalls();
			break;
		case 2:
			userBalls = getRandomBalls();
			break;
		default:
			continue;
		}

		//����û�ѡ���˫ɫ��
		cout << "�û���ѡ����ǣ�" <<descBalls(userBalls) << endl;

		//����н�������ʲô
		int* systemBalls = getRandomBalls();
		cout << "�н������ǣ�" << descBalls(systemBalls)<<endl;

		//��ȡ�н��ȼ�
		int level=getTicketLevel(userBalls, systemBalls);
		//�����н����
		int money = getMoney(level);

		if (level == 7) {
			cout << "���ź�����û���н����ٽ�������" << endl;
		}
		else {
			cout << "��ϲ��������" << level << "�Ƚ�������" << money << "Ԫ��" << endl;
		}
		system("pause"); 
		system("cls");
	}
}

int getRandomNumber(int start,int end) {
	return rand() % (end - start) + start;
}


int main() {

	//time(0)��ȡ���Ǵ�1970��1��1�����𣬵����ڵĺ�����
	srand(time(0));

	playGame();

	

	
	

	return 0;
}