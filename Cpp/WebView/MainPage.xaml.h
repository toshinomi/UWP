//
// MainPage.xaml.h
// MainPage クラスの宣言。
//

#pragma once

#include "MainPage.g.h"

namespace WebView
{
	/// <summary>
	/// それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
		bool ShowWebView(Platform::String^ _strUri);
		bool BackWebView(void);
		bool ForwardWebView(void);
		bool RefreshWebView(void);
		bool HomeWebView(void);
		Platform::String^ GetCurUri(void);

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		Platform::String^ m_strUri = "https://www.bing.com/";

	public:
		void OnNavigationCompletedWebView(Windows::UI::Xaml::Controls::WebView^ sender, Windows::UI::Xaml::Controls::WebViewNavigationCompletedEventArgs^ e);
		void OnClickBack(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickForward(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickRefresh(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickHome(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClickFind(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnKeyDownTextUri(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
	};
}
