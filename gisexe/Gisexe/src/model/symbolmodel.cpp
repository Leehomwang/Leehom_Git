#include <gl/glew.h>
#include "symbolmodel.h"
#include "../painter/sphere.h"
#include "fan.h"
#include "stackedbar.h"
#include "pie.h"

_GIS_BEGIN
gis::SymbolModel::SymbolModel()
{
	_shpLoader = NULL;
	_dbfLoader = NULL;
}

SymbolModel::~SymbolModel()
{
	if (_shpLoader)
	{
		delete _shpLoader;
		_shpLoader = NULL;
	}
	if (_dbfLoader)
	{
		delete _dbfLoader;
		_dbfLoader = NULL;
	}
}

void SymbolModel::setShpLoader( ShpLoader* shpLoader )
{
	_shpLoader = shpLoader;
}

void SymbolModel::setDbfLoader( DbfLoader* dbfLoader )
{
	_dbfLoader = dbfLoader;
}

void SymbolModel::setChartType( const ChartType& chartType )
{
	_chartType = chartType;
}

void SymbolModel::setFieldIndices( const std::vector<int>& fieldIndices )
{
	_fieldIndices = fieldIndices;
}

void SymbolModel::setColors( const std::vector<float3>& colors )
{
	_colors = colors;
}

void SymbolModel::init()
{
	const SHPHandle& hSHP = _shpLoader->getHandle();
	const DBFHandle& hDBF = _dbfLoader->getHandle();

	float maxVal = -99999999999, minVal = 99999999999; 

	std::vector<float2> xy; // 2d定位点
	std::vector<std::vector<float> > table; 
	std::vector<float> colsum; 

	for (int i = 0; i < hSHP->nRecords; i++) // 遍历记录
	{
		SHPObject* psShape = SHPReadObject(hSHP, i); // 每个记录存放一个点
		float v[] = { psShape->padfX[0], psShape->padfY[0] }; // 定位点
		xy.push_back(v);
		SHPDestroyObject(psShape);

		std::vector<float> row; 
		float sum = 0; 

		for (int j = 0; j < _fieldIndices.size(); j++)
		{
			float val = DBFReadDoubleAttribute(hDBF, i + 1, _fieldIndices[j]);

			sum += val;
			row.push_back(val);
		}

		if (maxVal < sum) 
		{
			maxVal = sum;
		}
		if (minVal > sum)
		{
			minVal = sum;
		}

		colsum.push_back(sum); 
		table.push_back(row);
	}

	LinearScaler hScaler(_valueScaler.getBottom()/* + 0.1*/, _valueScaler.getTop());
	hScaler.setBound(minVal, maxVal);

	for (int i = 0; i < hSHP->nRecords; i++)
	{
		float pos[] = { xy[i][0], xy[i][1], 0 }; 

		float top = hScaler(colsum[i]); 
		switch (_chartType)
		{
		case SPHERE:
			{
				Sphere* sphere = new Sphere(pos, _colors.front());
				sphere->setLinearScaler(LinearScaler(_valueScaler.getBottom(), top));
				_container.add(sphere);
			}
			break;
		case BAR:
			{
				Fan* fan = new Fan;
				fan->set(0, 360, _colors.front(), pos, 1.1);
				fan->setLinearScaler(LinearScaler(_valueScaler.getBottom(), top));
				fan->init();
				_container.add(fan);
			}
			break;
		case STACKEDBAR:
			{
				StackedBar* bar = new StackedBar;
				bar->set(table[i], _colors, pos, 1.1);
				bar->setLinearScaler(LinearScaler(_valueScaler.getBottom(), top));
				bar->init();
				_container.add(bar);
			}
			break;
		case PIE:
			{
				Pie* pie = new Pie;
				pie->set(table[i], _colors, pos, 1.1);
				pie->setLinearScaler(_valueScaler); // 应该同高度
				pie->init();
				_container.add(pie);
			}
			break;
		default:;
		}
	}
}

void SymbolModel::begin()
{
	glEnable(GL_LIGHTING);
}

void SymbolModel::end()
{
	glDisable(GL_LIGHTING);
}

void SymbolModel::pick( int x, int y )
{

}

_GIS_END

