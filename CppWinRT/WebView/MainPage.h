#pragma once

#include "MainPage.g.h"

namespace winrt::WebView::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
		/// <summary>
		/// コンストラクタ
		/// </summary>
        MainPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

	private:
		hstring const m_strUri = L"https://www.bing.com/";

	public:
		/// <summary>
		/// ナビゲーション完了時に発生するイベント
		/// </summary>
		/// <param name="sender">WebView</param>
		/// <param name="e">WebViewナビゲーション完了時イベントのデータ</param>
		void OnNavigationCompletedWebView(Windows::UI::Xaml::Controls::WebView const& sender, Windows::UI::Xaml::Controls::WebViewNavigationCompletedEventArgs const& e);
		
		/// <summary>
		/// 戻るボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickBack(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);

		/// <summary>
		/// 進むボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickForward(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);

		/// <summary>
		/// リフレッシュボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickRefresh(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);

		/// <summary>
		/// ホームボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickHome(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);

		/// <summary>
		/// サーチボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickFind(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);

		/// <summary>
		/// URIテキストボックスのキーダウンイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">キールーティングイベントのデータ</param>
		void OnKeyDownTextUri(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);

		/// <summary>
		/// WebView表示
		/// </summary>
		/// <param name="_strUri">URI</param>
		/// <returns>WebView表示 成功/失敗</returns>
		bool ShowWebView(hstring const& _strUri);

		/// <summary>
		/// WebView戻る
		/// </summary>
		/// <returns>WebView戻る 成功/失敗</returns>
		bool BackWebView(void);

		/// <summary>
		/// WebView進む
		/// </summary>
		/// <returns>WebView進む 成功/失敗</returns>
		bool ForwardWebView(void);

		/// <summary>
		/// WebViewリフレッシュ
		/// </summary>
		/// <returns>WebViewリフレッシュ 成功/失敗</returns>
		bool RefreshWebView(void);

		/// <summary>
		/// WebViewホーム
		/// </summary>
		/// <returns>WebViewホーム 成功/失敗</returns>
		bool HomeWebView(void);

		/// <summary>
		/// URI取得
		/// </summary>
		/// <returns>URI</returns>
		hstring GetCurUri(void);
    };
}

namespace winrt::WebView::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
