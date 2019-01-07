
#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include "fstream"
#include <direct.h>
#include <io.h>
#include <Windows.h>

using namespace std;
using namespace cv;

extern int readDir(char *dirName, vector<string> &filesName);

struct rect2
{
	int x1;
	int y1;
	int x2;
	int y2;
	int label;
};
int test41(int argc, char *argv[])
{

	string imgpath = "G:/F/Traffic-signs/data/FullIJCNN2013/test";
	string txtpath = "G:/F/Traffic-signs/data/FullIJCNN2013/test/0-Traffic-signs.txt";

	fstream finWrite;
	finWrite.open(txtpath, ios::out);
	if (!finWrite.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	vector<string> v_img_; int num = 0;
	readDir((char*)imgpath.c_str(), v_img_);
	for (int i = 0; i<v_img_.size(); i++)
	{
		int npos = v_img_[i].find_last_of('/');
		int npos2 = v_img_[i].find_last_of('.');
		cout << v_img_[i] << endl;
		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{
			printf("img.data = NULL！\n");
			system("pause");
			continue;
		}

		finWrite << "#" << " " << num << endl;
		num++;
		string str1 = name1 + ".jpg";
		finWrite << str1 << endl;





		string str = imgpath + "/" + name1 + ".txt";
		fstream finRead1;
		finRead1.open(str, ios::in);
		if (!finRead1.is_open())
		{
			cout << "finRead 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string line; int num1 = 0;
		vector<rect2>rts;
		while (getline(finRead1, line))
		{

			if (line.empty())
			{
				break;
			}

			num1++;

			int label; int x1, y1, x2, y2;
			stringstream str_s(line);
			str_s >> label >> x1 >> y1 >> x2 >> y2;
			rect2 rt; rt.label = label + 1; rt.x1 = x1; rt.y1 = y1; rt.x2 = x2; rt.y2 = y2;



			rts.push_back(rt);

		}

		finRead1.close();

		if (num1 != rts.size())
		{
			printf("error!\n");
			system("pause");
		}

		finWrite << num1 << endl;

		for (int j = 0; j < rts.size(); j++)
		{
			rect2 rt = rts[j];
			finWrite << rt.label << " " << rt.x1 << " " << rt.y1 << " " << rt.x2 << " " << rt.y2 << " " << 0 << endl;
		}
	}

	finWrite.close();

	return 0;
}
