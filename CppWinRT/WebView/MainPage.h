#pragma once

#include "MainPage.g.h"

namespace winrt::WebView::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

	private:
		hstring const m_strUri = L"https://www.bing.com/";

	public:
		void OnNavigationCompletedWebView(Windows::UI::Xaml::Controls::WebView const& sender, Windows::UI::Xaml::Controls::WebViewNavigationCompletedEventArgs const& e);
		void OnClickBack(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
		void OnClickForward(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
		void OnClickRefresh(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
		void OnClickHome(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
		void OnClickFind(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
		void OnKeyDownTextUri(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
		bool ShowWebView(hstring const& _strUri);
		bool BackWebView(void);
		bool ForwardWebView(void);
		bool RefreshWebView(void);
		bool HomeWebView(void);
		hstring GetCurUri(void);
    };
}

namespace winrt::WebView::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
