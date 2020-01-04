' 空白ページの項目テンプレートについては、https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x411 を参照してください

Imports Windows.System
''' <summary>
''' それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
''' </summary>
Public NotInheritable Class MainPage
    Inherits Page

    Private Const m_strUri As String = "https://www.bing.com/"

    ''' <summary>
    ''' コンストラクタ
    ''' </summary>
    Public Sub New()

        ' この呼び出しはデザイナーで必要です。
        InitializeComponent()

        ' InitializeComponent() 呼び出しの後で初期化を追加します。

    End Sub

    ''' <summary>
    ''' ナビゲーション完了時に発生するイベント
    ''' </summary>
    ''' <param name="sender">WebView</param>
    ''' <param name="e">WebViewナビゲーション完了時イベントのデータ</param>
    Public Async Sub OnNavigationCompletedWebView(ByVal sender As Windows.UI.Xaml.Controls.WebView, ByVal e As WebViewNavigationCompletedEventArgs)
        textUri.Text = GetCurUri()

        If (e.IsSuccess = False) Then
            Dim strErrMsg As String = e.WebErrorStatus.ToString()
            Dim nErrCode As Integer = e.WebErrorStatus
            Dim strMsg As String = String.Format("{0} ( {1} )", strErrMsg, nErrCode)
            Await New Windows.UI.Popups.MessageDialog(strMsg).ShowAsync()
        End If

        Return
    End Sub

    ''' <summary>
    ''' 遷移先のページがアクティブになる前に呼び出されるイベント
    ''' </summary>
    ''' <param name="e">ナビゲーションベントのデータ</param>
    Protected Overrides Sub OnNavigatedTo(ByVal e As NavigationEventArgs)
        HomeWebView()

        Return
    End Sub

    ''' <summary>
    ''' 戻るボタンのクリックイベント
    ''' </summary>
    ''' <param name="sender">オブジェクト</param>
    ''' <param name="e">ルーティングイベントのデータ</param>
    Public Sub OnClickBack(ByVal sender As Object, ByVal e As RoutedEventArgs)
        BackWebView()

        Return
    End Sub

    ''' <summary>
    ''' 進むボタンのクリックイベント
    ''' </summary>
    ''' <param name="sender">オブジェクト</param>
    ''' <param name="e">ルーティングイベントのデータ</param>
    Public Sub OnClickForward(ByVal sender As Object, ByVal e As RoutedEventArgs)
        ForwardWebView()

        Return
    End Sub

    ''' <summary>
    ''' リフレッシュボタンのクリックイベント
    ''' </summary>
    ''' <param name="sender">オブジェクト</param>
    ''' <param name="e">ルーティングイベントのデータ</param>
    Public Sub OnClickRefresh(ByVal sender As Object, ByVal e As RoutedEventArgs)
        RefreshWebView()

        Return
    End Sub

    ''' <summary>
    ''' ホームボタンのクリックイベント
    ''' </summary>
    ''' <param name="sender">オブジェクト</param>
    ''' <param name="e">ルーティングイベントのデータ</param>
    Public Sub OnClickHome(ByVal sender As Object, ByVal e As RoutedEventArgs)
        HomeWebView()

        Return
    End Sub

    ''' <summary>
    ''' サーチボタンのクリックイベント
    ''' </summary>
    ''' <param name="sender">オブジェクト</param>
    ''' <param name="e">ルーティングイベントのデータ</param>
    Public Sub OnClickFind(ByVal sender As Object, ByVal e As RoutedEventArgs)
        Dim strUri As String = textUri.Text
        ShowWebView(strUri)

        Return
    End Sub

    ''' <summary>
    ''' URIテキストボックスのキーダウンイベント
    ''' </summary>
    ''' <param name="sender">オブジェクト</param>
    ''' <param name="e">キールーティングイベントのデータ</param>
    Public Sub OnKeyDownTextUri(ByVal sender As Object, ByVal e As KeyRoutedEventArgs)
        If (e.Key = VirtualKey.Enter) Then
            Dim strUri As String = textUri.Text
            ShowWebView(strUri)
        End If

        Return
    End Sub

    ''' <summary>
    ''' WebView表示
    ''' </summary>
    ''' <param name="_strUri">URI</param>
    ''' <returns>WebView表示 成功/失敗</returns>
    Public Function ShowWebView(ByVal _strUri As String) As Boolean
        Dim bRst As Boolean = True

        Try
            webView.Navigate(New Uri(_strUri, UriKind.Absolute))
            textUri.Text = _strUri
        Catch ex As Exception
            bRst = False
        End Try

        Return bRst
    End Function

    ''' <summary>
    ''' WebView戻る
    ''' </summary>
    ''' <returns>WebView戻る 成功/失敗</returns>
    Public Function BackWebView() As Boolean
        Dim bRst As Boolean = True

        Try
            webView.GoBack()
        Catch ex As Exception
            bRst = False
        End Try

        Return bRst
    End Function

    ''' <summary>
    ''' WebView進む
    ''' </summary>
    ''' <returns>WebView進む 成功/失敗</returns>
    Public Function ForwardWebView() As Boolean
        Dim bRst As Boolean = True

        Try
            webView.GoForward()
        Catch ex As Exception
            bRst = False
        End Try

        Return bRst
    End Function

    ''' <summary>
    ''' WebViewリフレッシュ
    ''' </summary>
    ''' <returns>WebViewリフレッシュ 成功/失敗</returns>
    Public Function RefreshWebView() As Boolean
        Dim bRst As Boolean = True

        Try
            webView.Refresh()
        Catch ex As Exception
            bRst = False
        End Try

        Return bRst
    End Function

    ''' <summary>
    ''' WebViewホーム
    ''' </summary>
    ''' <returns>WebViewホーム 成功/失敗</returns>
    Public Function HomeWebView() As Boolean
        textUri.Text = m_strUri
        Dim strUri As String = m_strUri
        Return ShowWebView(strUri)
    End Function

    ''' <summary>
    ''' URI取得
    ''' </summary>
    ''' <returns>URI</returns>
    Public Function GetCurUri() As String
        Dim uriSource As Uri = webView.Source

        Return uriSource.ToString()
    End Function
End Class