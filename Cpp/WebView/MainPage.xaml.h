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
		/// <summary>
		/// コンストラクタ
		/// </summary>
		MainPage();

		/// <summary>
		/// WebView表示
		/// </summary>
		/// <param name="_strUri">URI</param>
		/// <returns>WebView表示 成功/失敗</returns>
		bool ShowWebView(Platform::String^ _strUri);

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
		Platform::String^ GetCurUri(void);

	protected:
		/// <summary>
		/// 遷移先のページがアクティブになる前に呼び出されるイベント
		/// </summary>
		/// <param name="e">ナビゲーションベントのデータ</param>
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		Platform::String^ m_strUri = "https://www.bing.com/";

	public:
		/// <summary>
		/// ナビゲーション完了時に発生するイベント
		/// </summary>
		/// <param name="sender">WebView</param>
		/// <param name="e">WebViewナビゲーション完了時イベントのデータ</param>
		void OnNavigationCompletedWebView(Windows::UI::Xaml::Controls::WebView^ sender, Windows::UI::Xaml::Controls::WebViewNavigationCompletedEventArgs^ e);

		/// <summary>
		/// 戻るボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickBack(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		/// <summary>
		/// 進むボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickForward(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		/// <summary>
		/// リフレッシュボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickRefresh(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		/// <summary>
		/// ホームボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickHome(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		/// <summary>
		/// サーチボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickFind(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		/// <summary>
		/// URIテキストボックスのキーダウンイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">キールーティングイベントのデータ</param>
		void OnKeyDownTextUri(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
	};
}
