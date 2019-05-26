#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include<string>
#include<vector>
using namespace std;

char map[100][100];
bool ending[100][100];
fstream source;
int column, row;
int temps;
char trace[100000][100][100];
int run;
void buildBool() {
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			if (map[i][j] == '2') ending[i][j] = true;
		}
}
void check() {
	int k = 0;
	for (int i = 0; i < row; i++){
		for (int j = 0; j < column; j++) {
			cout << map[i][j];
			if (i == 0 && j == column-1) { cout << "                               目前共走了 " << temps << " 步 ";  j++ ; }	
			}
		cout << endl;
	}
	cout << "\n輸入r (步數>0) 可以返回上一步" << endl;
}
void trackON(){

	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++) {
			trace[run][i][j] = map[i][j];
		}
	run += 1;
	temps += 1;
}
void Print_rule()
{
	system("color A");
	cout << "歡迎來到倉庫番，以下為例圖 : " << endl;

	cout << "     ///////\n     /01--2/\n     ///////" << endl;

	cout << "規則為 : 《倉庫番》的遊戲規則，則是扮演工人的玩家，以「推」的方式，推動箱子。可以在沒有阻礙物（如牆壁等的阻礙物）的情況下，向左、右、上、下的地方移動。將箱子移動到指定點，達到指定數量，即可過關。\n";
	cout << "\n但玩家移動箱子，有條件要注意：\n\n";
	cout << "推到牆壁的箱子，玩家就不可以背對牆壁，把箱子推回到空處。即箱子只能以「被推」的方式被移動，不是以「被拉」的方式被移動。\n但如果玩家推至牆壁後，垂直牆壁的兩側沒有阻礙物，則玩家可以朝這兩個不同的方向推移箱子。\n";
	cout << " /(牆)\n -(道路)\n 0(人物出發點)\n 1(箱子)\n 2(終點)\n" << endl;
	system("pause");
	system("CLS");
	system("color F");
}
int Flag()
{
	int out = 1;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			if (ending[i][j] == true) { out = 0; break; }
		}
	return out;
}
int play(int x, int y) {

	temps = 0;
	int c;
	check();
	run = 1;
	memset(ending,'0', sizeof(ending));
	buildBool();
	while (!Flag()) {
		c = getch();
		if (temps>0 && c == 'r') //back
		{
			system("cls");
			for (int i = 0; i < row; i++)
				for (int j = 0; j < column; j++) {
					map[i][j] = trace[temps - 1][i][j];
					if (map[i][j] == '0'){x = i; y = j;}
				}
			temps -= 1;
			run -= 1;
		}
		else if (c == 224) {  //c==224  224 is up,down,lefy,right command
				c = getch();
				system("cls");
				switch (c) {
					case 80:
						//cout << "下" << endl;
						if (map[x + 1][y] != '/')
						{
							if (map[x + 1][y] == '-' && map[x + 1][y] != '1') {
								map[x + 1][y] = '0'; map[x][y] = '-'; x += 1; trackON();
							}
							else if (map[x + 1][y] == '1')
							{
								if (map[x + 2][y] == '2') {
									map[x + 1][y] = '0'; map[x + 2][y] = '1'; map[x][y] = '-'; ending[x+2][y] = false; x += 1; trackON();
								}
								else if (map[x + 2][y] != '/') {
									map[x + 2][y] = '1'; map[x + 1][y] = '0'; map[x][y] = '-';x += 1; trackON();
								}
							}
						}
						break;

					case 72:
					//cout << "上" << endl;

					if (map[x - 1][y] != '/')
					{
						if (map[x - 1][y] == '-' && map[x - 1][y] != '1') {
							map[x - 1][y] = '0'; map[x][y] = '-'; x -= 1; trackON();
						}
						else if (map[x - 1][y] == '1')
						{
							if (map[x - 2][y] == '2') {
								map[x - 1][y] = '0'; map[x - 2][y] = '1'; map[x][y] = '-'; ending[x - 2][y] = false; x -= 1; trackON();
							}
							else if (map[x - 2][y] != '/') {
								map[x - 2][y] = '1'; map[x - 1][y] = '0'; map[x][y] = '-';  x -= 1; trackON();
							}
						}
					}
					break;
					case 75:
					//cout << "左" << endl;
					if (map[x][y - 1] != '/')
					{
						if (map[x][y - 1] == '-' && map[x][y - 1] != '1') {
							map[x][y - 1] = '0'; map[x][y] = '-'; y -= 1; trackON();
						}
						else if (map[x][y - 1] == '1')
						{
							if (map[x][y - 2] == '2') {
								map[x][y - 1] = '0'; map[x][y - 2] = '1'; map[x][y] = '-'; ending[x][y-2] = false; y -= 1; trackON();
							}
							else if (map[x][y - 2] != '/') {
								map[x][y - 2] = '1'; map[x][y - 1] = '0'; map[x][y] = '-';  y -= 1; trackON();
							}
						}
					}
					break;
					case 77:
					//cout << "右" << endl;
					if (map[x][y + 1] != '/')
					{
						if (map[x][y + 1] == '-' && map[x][y + 1] != '1') { map[x][y + 1] = '0'; map[x][y] = '-'; y += 1; trackON();
						}
						else if (map[x][y + 1] == '1')
						{
							if (map[x][y + 2] == '2') {
								map[x][y + 1] = '0'; map[x][y + 2] = '1'; map[x][y] = '-'; ending[x][y+2] = false; y += 1; trackON();
							}
							else if (map[x][y + 2] != '/') {
								map[x][y + 2] = '1'; map[x][y + 1] = '0'; map[x][y] = '-'; y += 1; trackON();
							}
						}
					}
					break;
					default:break;
				}
			}
				else continue; //avoid another key
		check();

	}
	if (Flag() == 1) {cout << "\nCompleted !! " << endl; system("pause");}
	return Flag();
}
int main()
{
	int startx, starty;
	int result;
	source.open("allmission.txt", ios::in);
	if (!source)
	{
		cerr << "map doesn't exist !";
		exit(1);
	}
	Print_rule();
	for (int time = 0; time < 3; time++)
	{
		memset(map, 'o', sizeof(map));
		source >> row >> column;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				source >> map[i][j];
				if (map[i][j] == '0') { startx = i; starty = j; }
			}
		}
		//initialize trace 0 by original map
	
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				trace[0][i][j] = map[i][j];
				//cout << trace[0][i][j];  <-it's use to scout trace matrix
				}
			//cout << endl;
		}
			
			switch (time) {
			case 0:
				cout << "ＧＡＭＥ　ＯＮＥ \n即將開始" << endl;
				system("pause");
				system("CLS");
				result = play(startx, starty);
				system("cls");
				if (result == 1) cout << "\n恭喜你贏得第一場   共走了 " << temps << " 步 !!\n" << endl;
				system("pause");
				system("CLS");
				break;
			case 1:
				cout << "ＧＡＭＥ　ＴＷＯ  \n即將開始" << endl;
				system("pause");
				system("CLS");
				result = play(startx, starty);
				system("cls");
				if (result == 1) cout << "\n恭喜你贏得第二場   共走了 " << temps << " 步 !!\n" << endl;
				system("pause");
				system("CLS");
				break;
			case 2:
				cout << "ＧＡＭＥ　ＴＨＲＥＥ  \n即將開始" << endl;
				system("pause");
				system("CLS");
				result = play(startx, starty);
				system("cls");
				if (result == 1) cout << "\n恭喜你贏得第三場   共走了 " << temps << " 步 !!\n" << endl;
				system("pause");
				break;
			}
		}
		system("cls");
		cout << "\n\n\n     遊 戲 結 束   " << endl;
		source.close();
		return 0;
	}
