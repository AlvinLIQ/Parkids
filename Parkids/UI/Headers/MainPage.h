#include "../../Headers/Parkids.h"
#include "../../Headers/Murrela/Src/Core/Murrela/Headers/CoreApp.h"

class MainPage : Controls::ItemsContainer
{
public:
	MainPage(Murrela *murla);
	~MainPage()
	{

	}

	Parkids* parkids;
protected:
};