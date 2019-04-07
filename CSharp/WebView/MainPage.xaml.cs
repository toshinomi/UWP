﻿using System;
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

        public MainPage()
        {
            this.InitializeComponent();
        }

        private async void WebView_NavigationCompleted(Windows.UI.Xaml.Controls.WebView sender, WebViewNavigationCompletedEventArgs e)
        {
            if (!e.IsSuccess)
            {
                string strErrMsg = e.WebErrorStatus.ToString();
                int nErrCode = (int)e.WebErrorStatus;
                string strMsg = string.Format("{0} ( {1} )", strErrMsg, nErrCode);
                await new Windows.UI.Popups.MessageDialog(strMsg).ShowAsync();
            }

            textUri.Text = GetCurUri();

            return;
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            HomwWebView();

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

            return;
        }

        private void OnForward_Click(object sender, RoutedEventArgs e)
        {
            ForwardWebView();

            return;
        }

        private void OnRefresh_Click(object sender, RoutedEventArgs e)
        {
            RefreshWebView();

            return;
        }

        private void OnHome_Click(object sender, RoutedEventArgs e)
        {
            HomwWebView();

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
            if (e.Key == VirtualKey.Enter)
            {
                String strAddress = textUri.Text;
                ShowWebView(ref strAddress);
            }

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

        public bool HomwWebView()
        {
            textUri.Text = m_strUri;
            string strUri = m_strUri;
            return ShowWebView(ref strUri);
        }

        public String GetCurUri()
        {
            Uri uriSource = webView.Source;

            return uriSource.ToString();
        }
    }
}