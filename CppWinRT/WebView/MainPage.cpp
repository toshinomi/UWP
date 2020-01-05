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
	/// <summary>
	/// コンストラクタ
	/// </summary>
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

	/// <summary>
	/// ナビゲーション完了時に発生するイベント
	/// </summary>
	/// <param name="sender">WebView</param>
	/// <param name="e">WebViewナビゲーション完了時イベントのデータ</param>
	void MainPage::OnNavigationCompletedWebView(Controls::WebView const& sender, WebViewNavigationCompletedEventArgs const& e)
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

	/// <summary>
	/// 戻るボタンのクリックイベント
	/// </summary>
	/// <param name="sender">オブジェクト</param>
	/// <param name="e">ルーティングイベントのデータ</param>
	void MainPage::OnClickBack(IInspectable const& sender, RoutedEventArgs const& e)
	{
		BackWebView();

		return;
	}

	/// <summary>
	/// 進むボタンのクリックイベント
	/// </summary>
	/// <param name="sender">オブジェクト</param>
	/// <param name="e">ルーティングイベントのデータ</param>
	void MainPage::OnClickForward(IInspectable const& sender, RoutedEventArgs const& e)
	{
		ForwardWebView();

		return;
	}

	/// <summary>
	/// リフレッシュボタンのクリックイベント
	/// </summary>
	/// <param name="sender">オブジェクト</param>
	/// <param name="e">ルーティングイベントのデータ</param>
	void MainPage::OnClickRefresh(IInspectable const& sender, RoutedEventArgs const& e)
	{
		RefreshWebView();

		return;
	}

	/// <summary>
	/// ホームボタンのクリックイベント
	/// </summary>
	/// <param name="sender">オブジェクト</param>
	/// <param name="e">ルーティングイベントのデータ</param>
	void MainPage::OnClickHome(IInspectable const& sender, RoutedEventArgs const& e)
	{
		HomeWebView();

		return;
	}

	/// <summary>
	/// サーチボタンのクリックイベント
	/// </summary>
	/// <param name="sender">オブジェクト</param>
	/// <param name="e">ルーティングイベントのデータ</param>
	void MainPage::OnClickFind(IInspectable const& sender, RoutedEventArgs const& e)
	{
		ShowWebView(textUri().Text());
		return;
	}

	/// <summary>
	/// URIテキストボックスのキーダウンイベント
	/// </summary>
	/// <param name="sender">オブジェクト</param>
	/// <param name="e">キールーティングイベントのデータ</param>
	void MainPage::OnKeyDownTextUri(IInspectable const& sender, KeyRoutedEventArgs const& e)
	{
		if (e.Key() == Windows::System::VirtualKey::Enter)
		{
			ShowWebView(textUri().Text());
		}

		return;
	}

	/// <summary>
	/// WebView表示
	/// </summary>
	/// <param name="_strUri">URI</param>
	/// <returns>WebView表示 成功/失敗</returns>
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

	/// <summary>
	/// WebView戻る
	/// </summary>
	/// <returns>WebView戻る 成功/失敗</returns>
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

	/// <summary>
	/// WebView進む
	/// </summary>
	/// <returns>WebView進む 成功/失敗</returns>
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

	/// <summary>
	/// WebViewリフレッシュ
	/// </summary>
	/// <returns>WebViewリフレッシュ 成功/失敗</returns>
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

	/// <summary>
	/// WebViewホーム
	/// </summary>
	/// <returns>WebViewホーム 成功/失敗</returns>
	bool MainPage::HomeWebView(void)
	{
		textUri().Text(m_strUri);
		return ShowWebView(m_strUri);
	}

	/// <summary>
	/// URI取得
	/// </summary>
	/// <returns>URI</returns>
	hstring MainPage::GetCurUri(void)
	{
		Uri uriSource = webView().Source();

		return uriSource.ToString();
	}
}