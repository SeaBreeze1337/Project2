#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include <ctime>

using namespace std;

//读取用户在控制台上输入的一个整数
int getNumberInput() {
	int input = 0;
	cin >> input;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "输入有误，请再输入数字" << endl;
		cin >> input;
	}
	return input;
}

//冒泡排序，对双色球前6个红球进行排序
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

//自选号码
int* getCustomBalls() {

	//定义一个数组，长度是7，用来存储6个红球和1个蓝球
	//因为我们需要在其他函数中使用这个数组，因此不能在栈空间开辟数组，应该在堆空间开辟
	int* balls = new int[7];

input_red_balls:
	cout << "请输入6个红球号码：";
	for (int i = 0; i < 6; i++)
	{
		balls[i] = getNumberInput();
	}
	//将红球排序
	sortBalls(balls);
	//判断红球是否越界
	if (balls[0]<1||balls[5]>33)
	{
		cout << "红球越界，请重新输入！" << endl;
		goto input_red_balls;
	}

	//判断红球是否重复
	for (int i = 0; i < 5; i++)
	{
		if (balls[i] == balls[i + 1])
		{
			//说明有重复元素
			cout << "红球重复了，请重新输入！" << endl;
			goto input_red_balls;
		}
	}

input_blue_balls:
	cout << "请输入一个蓝球：";
	balls[6] = getNumberInput();
	if (balls[6]>16||balls[6]<1)
	{
		//说明越界
		cout << "蓝球越界，请重新输入！" << endl;
		goto input_blue_balls;
	}


	return balls;
}

//机选号码
int* getRandomBalls() {
	//定义一个数组，用来存储随机生成的双色球
	int* balls = new int[7];

	//定义数据源，其中存储1-33的数字（红球范围）
	int* datapool = new int[33];
	for (int i = 0; i < 33; i++){
		datapool[i] = i + 1;
	}

	//填充balls
	for (int i = 0; i < 6; i++)
	{
		//计算数据源的长度
		int len = 33 - i;
		//从数据源数组获取一个随机的下标
		int randomIndex = rand() % len;
		//从数据源数组中，通过随机下标，获取元素，并且添加到balls数组中
		balls[i] = datapool[randomIndex];
		//更新数据源
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
	//将红球排序
	sortBalls(balls);

	//生成随机的篮球
	balls[6] = rand() % 16 + 1;






	return balls;
}

//格式化输出，并返回结果
string descBalls(int* balls) {
	stringstream ss;
	ss << "红球：";
		for (int i = 0; i < 7; i++){
			ss <<setw(2)<< setfill('0') << balls[i];
			if (i < 5) {
				ss << ", ";
			}
			else if (i==5){
				ss << ", 蓝球：";
			}
		}
	return ss.str();
}


//比对两注双色球，确定几等奖
int  getTicketLevel(int* userBalls,int* systemBalls) {
	//定义两个变量，分别用来记录红球和蓝球的中奖数量
	int redCount = 0, blueCount = 0;
	//核对红球中奖的数量
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++) {
			if (userBalls[i] == systemBalls[j]) {
				redCount++;
				break;
			}
		}
	}
	//核对蓝球数量
	blueCount = userBalls[6] == systemBalls[6];

	//确定奖项
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

	
	int userChoice = -1; //定义变量，用来存储用户的操作

	
	bool flag = 1;//定义一个布尔变量，记录游戏是否继续

	
	int* userBalls=NULL; //定义一个指针，指向用户选择的双色球

	while (flag)
	{
		cout << "*******************" << endl;
		cout << "* 请输入你的选择：" << endl;
		cout << "* 1.自选号码           " << endl;
		cout << "* 2.机选号码           " << endl;
		cout << "* 0.退出                  " << endl;
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

		//输出用户选择的双色球
		cout << "用户的选择的是：" <<descBalls(userBalls) << endl;

		//输出中奖号码是什么
		int* systemBalls = getRandomBalls();
		cout << "中奖号码是：" << descBalls(systemBalls)<<endl;

		//获取中奖等级
		int level=getTicketLevel(userBalls, systemBalls);
		//计算中奖金额
		int money = getMoney(level);

		if (level == 7) {
			cout << "很遗憾，您没有中奖，再接再厉！" << endl;
		}
		else {
			cout << "恭喜您，中了" << level << "等奖，奖金" << money << "元！" << endl;
		}
		system("pause"); 
		system("cls");
	}
}

int getRandomNumber(int start,int end) {
	return rand() % (end - start) + start;
}


int main() {

	//time(0)获取的是从1970年1月1日算起，到现在的毫秒数
	srand(time(0));

	playGame();

	

	
	

	return 0;
}