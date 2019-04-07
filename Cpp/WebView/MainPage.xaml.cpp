//
// MainPage.xaml.cpp
// MainPage クラスの実装。
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace WebView;

using namespace Platform;
using namespace Windows::UI::Popups;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// 空白ページの項目テンプレートについては、https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x411 を参照してください

MainPage::MainPage()
{
	InitializeComponent();
}

void MainPage::WebView_NavigationCompleted(Windows::UI::Xaml::Controls::WebView^ sender, Windows::UI::Xaml::Controls::WebViewNavigationCompletedEventArgs^ e)
{
	textUri->Text = GetCurUri();

	if (!e->IsSuccess)
	{
		Platform::String^ strErrMsg = e->WebErrorStatus.ToString();
		int nErrCode = (int)e->WebErrorStatus;
		Platform::String^ strMsg = strErrMsg + " ( " + nErrCode.ToString() + " ) ";
		MessageDialog^ msgDialog = ref new MessageDialog(strMsg);
		msgDialog->ShowAsync();
	}

	return;
}

void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	HomeWebView();

	return;
}

void MainPage::OnNavigatedFrom(NavigationEventArgs^ e)
{
	return;
}

void MainPage::OnBack_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	return;
}

void MainPage::OnForward_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	BackWebView();

	return;
}

void MainPage::OnRefresh_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	RefreshWebView();

	return;
}

void MainPage::OnHome_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	HomeWebView();

	return;
}

void MainPage::OnFind_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Platform::String^ strUri = textUri->Text;
	ShowWebView(strUri);

	return;
}

void MainPage::OnKeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (e->Key == Windows::System::VirtualKey::Enter)
	{
		Platform::String^ strUri = textUri->Text;
		ShowWebView(strUri);
	}

	return;
}

bool MainPage::ShowWebView(Platform::String^ _strUri)
{
	bool bRst = true;
	try
	{
		webView->Navigate(ref new Uri(_strUri));
		textUri->Text = _strUri;
	}
	catch (Exception^)
	{
		bRst = false;
	}

	return bRst;
}

bool MainPage::BackWebView(void)
{
	bool bRst = true;
	try
	{
		webView->GoBack();
	}
	catch (Exception^)
	{
		bRst = false;
	}

	return bRst;
}

bool MainPage::ForwardWebView(void)
{
	bool bRst = true;
	try
	{
		webView->GoForward();
	}
	catch (Exception^)
	{
		bRst = false;
	}

	return bRst;
}

bool MainPage::RefreshWebView(void)
{
	bool bRst = true;
	try
	{
		webView->Refresh();
	}
	catch (Exception^)
	{
		bRst = false;
	}

	return bRst;
}

bool MainPage::HomeWebView(void)
{
	textUri->Text = m_strUri;
	Platform::String^ strUri = m_strUri;
	return ShowWebView(strUri);
}

Platform::String^ MainPage::GetCurUri(void)
{
	Uri^ uriSource = webView->Source;

	return uriSource->ToString();
}