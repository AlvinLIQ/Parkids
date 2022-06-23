#include "../../Headers/Parkids.h"
#include "../../Headers/Murrela/Src/Core/Murrela/Headers/CoreApp.h"

class MainPage : Controls::ItemsContainer
{
public:
	MainPage(Murrela *murla);
	~MainPage()
	{

	}

	void Draw();

	Parkids* parkids;
private:
	time_t lastTime = 0;
protected:
};