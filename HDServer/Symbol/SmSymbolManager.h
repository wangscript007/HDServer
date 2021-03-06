#pragma once
#include "../Global/TemplateSingleton.h"
#include <string>
#include <map>
#include <memory>
#include "HdProductInfo.h"
#include "../Timer/cpptime.h"

class SmSymbol;
class SmSymbolManager : public TemplateSingleton<SmSymbolManager>
{
public:
	SmSymbolManager();
	~SmSymbolManager();
	void AddSymbol(std::shared_ptr<SmSymbol> sym);
	std::shared_ptr<SmSymbol> FindSymbol(std::string symCode);
	std::map<std::string, std::shared_ptr<SmSymbol>>& GetSymbolMap() {
		return _SymbolMap;
	}

	int KospiCurrent;
	int Kospi200Current;
	int Kosdaq150Current;
	std::shared_ptr<HdProductInfo> AddProductInfo(std::string code);
	std::shared_ptr<HdProductInfo> FindProductInfo(std::string code);
	// 파일에서 국내 상품 정보를 읽어 온다. 
	void LoadProductInfo();
	static std::string& TrimRight(std::string& input, char c);
	static std::string& TrimLeft(std::string& input, char c);
	static std::string& TrimBoth(std::string& input, char c);

	// 타이머로 차트 데이터 수집을 시작한다.
	void StartCollectData();
private:
	std::map<std::string, std::shared_ptr<SmSymbol>> _SymbolMap;
	std::map<std::string, std::shared_ptr<HdProductInfo>> ProductInfoMap;

	// 현재 차트 데이터 수집중인 심볼 목록
	std::vector<std::shared_ptr<SmSymbol>> _ChartSymbolVector;

	// 차트 타이머가 동작했을때 처리하는 함수
	void OnTimer();
	CppTime::Timer _Timer;
	std::map<int, CppTime::timer_id> _CycleDataReqTimerMap;
	// 차트 데이터 수집 타이머 시작
	void StartTimer();

};

