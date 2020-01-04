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

/// <summary>
/// コンストラクタ
/// </summary>
MainPage::MainPage()
{
	InitializeComponent();
}

/// <summary>
/// ナビゲーション完了時に発生するイベント
/// </summary>
/// <param name="sender">WebView</param>
/// <param name="e">WebViewナビゲーション完了時イベントのデータ</param>
void MainPage::OnNavigationCompletedWebView(Windows::UI::Xaml::Controls::WebView^ sender, Windows::UI::Xaml::Controls::WebViewNavigationCompletedEventArgs^ e)
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

/// <summary>
/// 遷移先のページがアクティブになる前に呼び出されるイベント
/// </summary>
/// <param name="e">ナビゲーションベントのデータ</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	HomeWebView();

	return;
}

/// <summary>
/// 戻るボタンのクリックイベント
/// </summary>
/// <param name="sender">オブジェクト</param>
/// <param name="e">ルーティングイベントのデータ</param>
void MainPage::OnClickBack(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	BackWebView();

	return;
}

/// <summary>
/// 進むボタンのクリックイベント
/// </summary>
/// <param name="sender">オブジェクト</param>
/// <param name="e">ルーティングイベントのデータ</param>
void MainPage::OnClickForward(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ForwardWebView();

	return;
}

/// <summary>
/// リフレッシュボタンのクリックイベント
/// </summary>
/// <param name="sender">オブジェクト</param>
/// <param name="e">ルーティングイベントのデータ</param>
void MainPage::OnClickRefresh(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	RefreshWebView();

	return;
}

/// <summary>
/// ホームボタンのクリックイベント
/// </summary>
/// <param name="sender">オブジェクト</param>
/// <param name="e">ルーティングイベントのデータ</param>
void MainPage::OnClickHome(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	HomeWebView();

	return;
}

/// <summary>
/// サーチボタンのクリックイベント
/// </summary>
/// <param name="sender">オブジェクト</param>
/// <param name="e">ルーティングイベントのデータ</param>
void MainPage::OnClickFind(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Platform::String^ strUri = textUri->Text;
	ShowWebView(strUri);

	return;
}

/// <summary>
/// URIテキストボックスのキーダウンイベント
/// </summary>
/// <param name="sender">オブジェクト</param>
/// <param name="e">キールーティングイベントのデータ</param>
void MainPage::OnKeyDownTextUri(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (e->Key == Windows::System::VirtualKey::Enter)
	{
		Platform::String^ strUri = textUri->Text;
		ShowWebView(strUri);
	}

	return;
}

/// <summary>
/// WebView表示
/// </summary>
/// <param name="_strUri">URI</param>
/// <returns>WebView表示 成功/失敗</returns>
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

/// <summary>
/// WebView戻る
/// </summary>
/// <returns>WebView戻る 成功/失敗</returns>
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

/// <summary>
/// WebView進む
/// </summary>
/// <returns>WebView進む 成功/失敗</returns>
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

/// <summary>
/// WebViewリフレッシュ
/// </summary>
/// <returns>WebViewリフレッシュ 成功/失敗</returns>
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

/// <summary>
/// WebViewホーム
/// </summary>
/// <returns>WebViewホーム 成功/失敗</returns>
bool MainPage::HomeWebView(void)
{
	textUri->Text = m_strUri;
	Platform::String^ strUri = m_strUri;
	return ShowWebView(strUri);
}

/// <summary>
/// URI取得
/// </summary>
/// <returns>URI</returns>
Platform::String^ MainPage::GetCurUri(void)
{
	Uri^ uriSource = webView->Source;

	return uriSource->ToString();
}