#include "Point_Radar.h"



#define PI 3.141592654

int segments = 36;
//int numbOfPoints = 94;

osg::ref_ptr<osg::Vec3Array> createPoints(const char* filename, int numbOfPoints)
{
	std::ofstream SaveFile("Verteies.txt");
	char c1[16], c2[16], c3[16];

	osg::ref_ptr<osg::Vec3Array> points = new osg::Vec3Array;
	//points->push_back(osg::Vec3(1.0f,0.0f,0.0f));
	//points->push_back(osg::Vec3(3.0f,0.0f,0.0f));
	//points->push_back(osg::Vec3(1.0f,0.0f,2.0f));
	//points->push_back(osg::Vec3(3.0f,0.0f,2.0f));

	//MyPoint mypoint[4] = {{1.0f,0.0f,0.0f},{3.0f,0.0f,0.0f},{3.0f,0.0f,2.0f},{1.0f,0.0f,2.0f}};
	MyPoint *mypoint = new MyPoint[numbOfPoints];

	//读取OBJ文件
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		std::cout<<"Can't open file"<<filename<<std::endl;
		return 0;
	}

	char buffer[1024];
	int everything_ok = 1;

	for (int i = 0; everything_ok && fgets(buffer, 1024, file)!= NULL && i < numbOfPoints; i++)
	{
		if (strncmp(buffer, "v ", 2)== 0)
		{
			double px, py, pz;
			if (sscanf(buffer, "v %lf %lf %lf", &px, &py, &pz)== 3)
			{
				mypoint[i].x = px;
				mypoint[i].y = py;
				mypoint[i].z = pz;
			}
			else
			{
				everything_ok = 0;
				std::cout<<"读入顶点出错"<<std::endl;
			}
		}
	}



	float angle = 2*PI/segments;
	float tempx, tempy, tempz;
	float sinA = sin(angle);
	float cosA = cos(angle);

	for (int i= 0; i < numbOfPoints; i++)
	{
		tempx = mypoint[i].x; tempy = mypoint[i].y; tempz = mypoint[i].z;
		sprintf(c1,"%f",tempx);
		sprintf(c2,"%f",tempy);
		sprintf(c3,"%f",tempz);
		SaveFile << c1 <<" ";
		SaveFile << c2 <<" ";
		SaveFile << c3 <<" "<<std::endl;
		points->push_back(osg::Vec3(mypoint[i].x, mypoint[i].y, mypoint[i].z));
		for (int j =1; j <= segments; j++)
		{
			float temps = sin(angle*j);
			float tempc = cos(angle*j);
			tempx = mypoint[i].x * cos(angle*j) - mypoint[i].y * sin(angle*j);
			tempy = mypoint[i].x * sin(angle*j) + mypoint[i].y * cos(angle*j);
			tempz = mypoint[i].z;
			sprintf(c1,"%f",tempx);
			sprintf(c2,"%f",tempy);
			sprintf(c3,"%f",tempz);
			SaveFile << c1 <<" ";
			SaveFile << c2 <<" ";
			SaveFile << c3 <<" "<<std::endl;
			points->push_back(osg::Vec3(tempx, tempy, tempz));
		}

	}
	SaveFile.close();
	delete mypoint;
	return points;
}


osg::ref_ptr<osg::IntArray> createIndeies(int numbOfPoints)
{
	std::ofstream SaveFile("Indeices.txt");
	char temp1[8], temp2[8], temp3[8], temp4[8], temp5[8], temp6[8];

	osg::ref_ptr<osg::IntArray> indeices = new osg::IntArray; 
	//osg::ref_ptr<osg::UByteArray> indeices = new osg::UByteArray;
	for (int j = 0; j < numbOfPoints-1; j++)
	{
		for (int i = 0; i < segments; i++)
		{
			//第一个三角形
			indeices->push_back(segments*j +i+j);
			indeices->push_back(segments*(j+1)+i+j+1);
			indeices->push_back(segments*(j+1)+i+j+2);
			itoa(segments*j +i+j, temp1, 10);
			itoa(segments*(j+1)+i+j+1, temp2, 10);
			itoa(segments*(j+1)+i+j+2, temp3, 10);
			SaveFile << temp1 <<" ";
			SaveFile << temp2 <<" ";
			SaveFile << temp3 <<" "<<std::endl;
			//第二个三角形
			indeices->push_back(segments*j+i+j+1);
			indeices->push_back(segments*j+i+j);
			indeices->push_back(segments*(j+1)+i+j+2);
			itoa(segments*j+i+j+1, temp4, 10);
			itoa(segments*j+i+j, temp5, 10);
			itoa(segments*(j+1)+i+j+2, temp6, 10);
			SaveFile << temp4 <<" ";
			SaveFile << temp5 <<" ";
			SaveFile << temp6 <<" "<<std::endl;
		}
		//首位相连处的三角形
		//第一个
		//indeices->push_back(segments+(segments+1)*j);
		//indeices->push_back(segments+(segments+1)*(j+1));
		//indeices->push_back(segments+(segments+1)*j+1);
		//itoa(segments+(segments+1)*j, temp7, 10);
		//itoa(segments+(segments+1)*(j+1), temp8, 10);
		//itoa(segments+(segments+1)*j+1, temp9, 10);
		//SaveFile << temp7 <<" ";
		//SaveFile << temp8 <<" ";
		//SaveFile << temp9 <<" "<<std::endl;
		////第二个
		//indeices->push_back((segments+1)*j);
		//indeices->push_back(segments+(segments+1)*j);
		//indeices->push_back(segments+(segments+1)*j+1);
		//itoa((segments+1)*j, temp10, 10);
		//itoa(segments+(segments+1)*j, temp11, 10);
		//itoa(segments+(segments+1)*j+1, temp12, 10);
		//SaveFile << temp10 <<" ";
		//SaveFile << temp11 <<" ";
		//SaveFile << temp12 <<" "<<std::endl;
	}
	SaveFile.close();
	return indeices;

}