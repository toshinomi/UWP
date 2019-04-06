using System;
using Windows.UI.Popups;
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
        public MainPage()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            textUri.Text = "https://www.bing.com/";
            string strUri = textUri.Text;
            ShowWebView(ref strUri);

            return;
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            base.OnNavigatedFrom(e);

            return;
        }

        private void OnBack_Click(object sender, RoutedEventArgs e)
        {
            BackWebView();
            textUri.Text = GetCurUri();

            return;
        }

        private void OnForward_Click(object sender, RoutedEventArgs e)
        {
            ForwardWebView();
            textUri.Text = GetCurUri();

            return;
        }

        private void OnRefresh_Click(object sender, RoutedEventArgs e)
        {
            RefreshWebView();
            textUri.Text = GetCurUri();

            return;
        }

        private void OnFind_Click(object sender, RoutedEventArgs e)
        {
            String strAddress = textUri.Text;
            ShowWebView(ref strAddress);

            return;
        }

        private void OnKeyDown(object sender, KeyRoutedEventArgs e)
        {
            String strAddress = textUri.Text;
            ShowWebView(ref strAddress);

            return;
        }

        public bool ShowWebView(ref String _strUri)
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

        public String GetCurUri()
        {
            Uri uriSource = webView.Source;

            return uriSource.ToString();
        }
    }
}