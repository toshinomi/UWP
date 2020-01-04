using System;

using Windows.System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Navigation;

// 空白ページの項目テンプレートについては、https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x411 を参照してください

namespace WebView
{
    /// <summary>
    /// それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private const string m_strUri = "https://www.bing.com/";

        /// <summary>
        /// コンストラクタ
        /// </summary>
        public MainPage()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// ナビゲーション完了時に発生するイベント
        /// </summary>
        /// <param name="sender">WebView</param>
        /// <param name="e">WebViewナビゲーション完了時イベントのデータ</param>
        public async void OnNavigationCompletedWebView(Windows.UI.Xaml.Controls.WebView sender, WebViewNavigationCompletedEventArgs e)
        {
            textUri.Text = GetCurUri();

            if (!e.IsSuccess)
            {
                string strErrMsg = e.WebErrorStatus.ToString();
                int nErrCode = (int)e.WebErrorStatus;
                string strMsg = string.Format("{0} ( {1} )", strErrMsg, nErrCode);
                await new Windows.UI.Popups.MessageDialog(strMsg).ShowAsync();
            }

            return;
        }

        /// <summary>
        /// 遷移先のページがアクティブになる前に呼び出されるイベント
        /// </summary>
        /// <param name="e">ナビゲーションベントのデータ</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            HomeWebView();

            return;
        }

        /// <summary>
        /// 戻るボタンのクリックイベント
        /// </summary>
        /// <param name="sender">オブジェクト</param>
        /// <param name="e">ルーティングイベントのデータ</param>
        public void OnClickBack(object sender, RoutedEventArgs e)
        {
            BackWebView();

            return;
        }

        /// <summary>
        /// 進むボタンのクリックイベント
        /// </summary>
        /// <param name="sender">オブジェクト</param>
        /// <param name="e">ルーティングイベントのデータ</param>
        public void OnClickForward(object sender, RoutedEventArgs e)
        {
            ForwardWebView();

            return;
        }

        /// <summary>
        /// リフレッシュボタンのクリックイベント
        /// </summary>
        /// <param name="sender">オブジェクト</param>
        /// <param name="e">ルーティングイベントのデータ</param>
        public void OnClickRefresh(object sender, RoutedEventArgs e)
        {
            RefreshWebView();

            return;
        }

        /// <summary>
        /// ホームボタンのクリックイベント
        /// </summary>
        /// <param name="sender">オブジェクト</param>
        /// <param name="e">ルーティングイベントのデータ</param>
        public void OnClickHome(object sender, RoutedEventArgs e)
        {
            HomeWebView();

            return;
        }

        /// <summary>
        /// サーチボタンのクリックイベント
        /// </summary>
        /// <param name="sender">オブジェクト</param>
        /// <param name="e">ルーティングイベントのデータ</param>
        public void OnClickFind(object sender, RoutedEventArgs e)
        {
            string strUri = textUri.Text;
            ShowWebView(strUri);

            return;
        }

        /// <summary>
        /// URIテキストボックスのキーダウンイベント
        /// </summary>
        /// <param name="sender">オブジェクト</param>
        /// <param name="e">キールーティングイベントのデータ</param>
        public void OnKeyDownTextUri(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == VirtualKey.Enter)
            {
                string strUri = textUri.Text;
                ShowWebView(strUri);
            }

            return;
        }

        /// <summary>
        /// WebView表示
        /// </summary>
        /// <param name="_strUri">URI</param>
        /// <returns>WebView表示 成功/失敗</returns>
        public bool ShowWebView(string _strUri)
        {
            bool bRst = true;
            try
            {
                webView.Navigate(new Uri(_strUri, UriKind.Absolute));
                textUri.Text = _strUri;
            }
            catch (Exception)
            {
                bRst = false;
            }

            return bRst;
        }

        /// <summary>
        /// WebView戻る
        /// </summary>
        /// <returns>WebView戻る 成功/失敗</returns>
        public bool BackWebView()
        {
            bool bRst = true;
            try
            {
                webView.GoBack();
            }
            catch (Exception)
            {
                bRst = false;
            }

            return bRst;
        }

        /// <summary>
        /// WebView進む
        /// </summary>
        /// <returns>WebView進む 成功/失敗</returns>
        public bool ForwardWebView()
        {
            bool bRst = true;
            try
            {
                webView.GoForward();
            }
            catch (Exception)
            {
                bRst = false;
            }

            return bRst;
        }

        /// <summary>
        /// WebViewリフレッシュ
        /// </summary>
        /// <returns>WebViewリフレッシュ 成功/失敗</returns>
        public bool RefreshWebView()
        {
            bool bRst = true;
            try
            {
                webView.Refresh();
            }
            catch (Exception)
            {
                bRst = false;
            }

            return bRst;
        }

        /// <summary>
        /// WebViewホーム
        /// </summary>
        /// <returns>WebViewホーム 成功/失敗</returns>
        public bool HomeWebView()
        {
            textUri.Text = m_strUri;
            string strUri = m_strUri;
            return ShowWebView(strUri);
        }

        /// <summary>
        /// URI取得
        /// </summary>
        /// <returns>URI</returns>
        public string GetCurUri()
        {
            Uri uriSource = webView.Source;

            return uriSource.ToString();
        }
    }
}
