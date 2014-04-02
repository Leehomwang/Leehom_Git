#ifndef _SYMBOLMODEL_H_
#define _SYMBOLMODEL_H_

#include "model.h"
#include "../io/shploader.h"
#include "../io/dbfloader.h"

_GIS_BEGIN

class SymbolModel : public Model
{
public:
	enum ChartType { SPHERE, BAR, STACKEDBAR, PIE };

	SymbolModel();
	virtual ~SymbolModel();

	virtual void init(); // 初始化
	virtual void begin();
	virtual void end();

	virtual void pick(int x, int y); // 选择

	void setShpLoader(ShpLoader* shpLoader);
	void setDbfLoader(DbfLoader* dbfLoader);

	void setChartType(const ChartType& chartType = ChartType::SPHERE);
	void setFieldIndices(const std::vector<int>& fieldIndices);
	void setColors(const std::vector<float3>& colors);
protected:
	ShpLoader* _shpLoader;
	DbfLoader* _dbfLoader;

	std::vector<float3> _colors; // 颜色集合
	std::vector<int> _fieldIndices; // 属性名
	ChartType _chartType;
};

_GIS_END

#endif

