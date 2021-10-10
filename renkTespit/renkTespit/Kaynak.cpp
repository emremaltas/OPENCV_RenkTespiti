#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

class renkTespit {
public:
	Mat resim, resimCopy;
	int maxVal, minVal;
	int h1=0, s1=0, v1=0;
	int h2=0, s2=0, v2=0;

	void ilk()
	{
		VideoCapture kamera(0);
		if (kamera.isOpened())
		{
			vector<Point2f>Maviciz;
			vector<Point2f>Yesilciz;
			Mat ekran;
			Mat resim;
			Mat ekranCopy;
			while (true)
			{
				//kýrmýzý odamda:35,35,105,255,45,255
				//mavi odamda:59,16,15,90,32,49

				kamera.read(ekran);
				ekranCopy = ekran.clone();
				inRange(ekran, Scalar(59, 16, 15), Scalar(90, 32, 49), resim);//mavi
				inRange(ekranCopy, Scalar(35, 35, 105), Scalar(255, 45, 255), ekranCopy);//kýrmýzý
				vector<vector<Point>>kirmiziNok;
				vector<Vec4i>kirmiziHiy;

				vector<vector<Point>>maviNok;
				vector<Vec4i>maviHiy;
				findContours(ekranCopy, kirmiziNok, kirmiziHiy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
				findContours(resim, maviNok, maviHiy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
				
				drawContours(ekran, kirmiziNok, 0,Scalar(180,180,25),FILLED,8,kirmiziHiy);
				drawContours(ekran, maviNok, 0, Scalar(25, 150, 200), FILLED, 8, maviHiy);
				
				if (maviNok.size()>=1)
				{
					Moments a;
					a = moments(maviNok[0]);
					Point2f center;
					center.x = a.m10 / a.m00;
					center.y = a.m01 / a.m00;
					Maviciz.push_back(center);
					
						for (int i = 0; i < Maviciz.size(); i++)
						{
							line(ekran, Maviciz[i], Point(Maviciz[i].x + 0.1, Maviciz[i].y + 0.1), Scalar(255, 0, 0), 8, 8);
						}
					
				}
				if (kirmiziNok.size()>0)
				{
					Moments yesil;
					Point2f centerGreen;
					yesil = moments(kirmiziNok[0]);
					centerGreen.x = yesil.m10 / yesil.m00;
					centerGreen.y = yesil.m01 / yesil.m00;
					Yesilciz.push_back(centerGreen);
					for (int i=0;i<Yesilciz.size();i++)
					{
						line(ekran, Point(Yesilciz[i]), Point(Yesilciz[i].x + 0.1, Yesilciz[i].y + 0.1), Scalar(0, 0, 255), 8, 8);
					}


				}

				imshow("orjin", ekran);
				//imshow("kirmizi", ekranCopy);
				imshow("mavi", resim);
				if (waitKey(100)==32)
				{
					break;
				}

			}
		}
		
	}
	
	

}a;
void h1(int, void*)
{
	
	a.h1++;
	
	
}
void s1(int, void*)
{
	a.s1++;
	
}
void v1(int, void*)
{
	a.v1++;
	
}
void h2(int, void*)
{

	a.h2++;

	
}
void s2(int, void*)
{
	a.s2++;
	
}
void v2(int, void*)
{
	a.v2++;

}
int main()
{


	//namedWindow("degerler", WINDOW_AUTOSIZE);

	//createTrackbar("h1", "degerler", &a.h1, 255, h1);
	//createTrackbar("s1", "degerler", &a.s1, 255, s1);
	//createTrackbar("v1", "degerler", &a.v1, 255, v1);
	//createTrackbar("h2", "degerler", &a.h2, 255, h2);
	//createTrackbar("s2", "degerler", &a.s2, 255, s2);
	//createTrackbar("v2", "degerler", &a.v2, 255, v2);

	a.ilk();
	

	waitKey(0);
	return 0;

}