#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml::Input;

namespace winrt::WebView::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();

		HomeWebView();
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

	void MainPage::OnNavigationCompletedWebView(Controls::WebView const&, WebViewNavigationCompletedEventArgs const& e)
	{
		textUri().Text(GetCurUri());

		if (!e.IsSuccess())
		{
			hstring strMsg = L"NotFound";
			MessageDialog msgDialog =  MessageDialog(strMsg);
			msgDialog.ShowAsync();
		}

		return;
	}

	void MainPage::OnClickBack(IInspectable const&, RoutedEventArgs const&)
	{
		BackWebView();

		return;
	}

	void MainPage::OnClickForward(IInspectable const&, RoutedEventArgs const&)
	{
		ForwardWebView();

		return;
	}

	void MainPage::OnClickRefresh(IInspectable const&, RoutedEventArgs const&)
	{
		RefreshWebView();

		return;
	}

	void MainPage::OnClickHome(IInspectable const&, RoutedEventArgs const&)
	{
		HomeWebView();

		return;
	}

	void MainPage::OnClickFind(IInspectable const&, RoutedEventArgs const&)
	{
		ShowWebView(textUri().Text());
		return;
	}

	void MainPage::OnKeyDownTextUri(IInspectable const&, KeyRoutedEventArgs const& e)
	{
		if (e.Key() == Windows::System::VirtualKey::Enter)
		{
			ShowWebView(textUri().Text());
		}

		return;
	}

	bool MainPage::ShowWebView(hstring const& _strUri)
	{
		bool bRst = true;
		try
		{
			webView().Navigate(Uri(_strUri));
			textUri().Text(_strUri);
		}
		catch (hresult_error const&)
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
			webView().GoBack();
		}
		catch (hresult_error const&)
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
			webView().GoForward();
		}
		catch (hresult_error const&)
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
			webView().Refresh();
		}
		catch (hresult_error const&)
		{
			bRst = false;
		}

		return bRst;
	}

	bool MainPage::HomeWebView(void)
	{
		textUri().Text(m_strUri);
		return ShowWebView(m_strUri);
	}

	hstring MainPage::GetCurUri(void)
	{
		Uri uriSource = webView().Source();

		return uriSource.ToString();
	}
}