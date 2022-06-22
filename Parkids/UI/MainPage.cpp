#include "Headers/MainPage.h"

using namespace Controls;

MainPage::MainPage(Murrela* murla) : ItemsContainer(murla, Stretch)
{
	ItemsContainer* mContainer = new StackPanel(murrela, Center);

	auto title = new TextBlock(L"Parkids", murrela, Center, Center, { 200, 80 });
	mContainer->AppendItem((Control*)title);
	title->SetFontSize(40);

	Button* tBtn;
	mContainer->AppendItem((Control*)(tBtn = new Button(L"Start", murrela, Center, { 180, 40 })));
	tBtn->ClickEvent.param = this;
	tBtn->Clicked.push_back([](void* param)
		{
			auto mainPage = (MainPage*)param;
			mainPage->RemoveAt(0);
			mainPage->AppendItem((Control*)(mainPage->parkids = new Parkids(mainPage->GetMurrela())));
			((CoreApp*)((ItemsContainer*)param)->GetMurrela()->CoreApp)->ResizeEvent.param = ((MainPage*)param)->parkids;
			((CoreApp*)((ItemsContainer*)param)->GetMurrela()->CoreApp)->SizeChanged.push_back([](void* param)
				{
					auto parkids = (Parkids*)param;
					if (parkids != nullptr && parkids->drnMap != nullptr)
					{
						RECT wndSize;
						GetClientRect(((Control*)parkids)->GetMurrela()->GetWindow(), &wndSize);
						D2D1_SIZE_F newSize = D2D1::SizeF((float)(wndSize.right - wndSize.left), (float)(wndSize.bottom - wndSize.top));
						parkids->drnMap->Resize(newSize);
					}
				});
		});
	mContainer->AppendItem((Control*)new TextBlock(L"", murrela, Left, Left, {20, 20}));
	mContainer->AppendItem((Control*)(tBtn = new Button(L"Exit", murrela, Center, { 180, 40 })));
	tBtn->Clicked.push_back([](void* param) 
		{
			exit(0);
		});
	this->AppendItem((Control*)mContainer);

}