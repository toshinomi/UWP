' 空白ページの項目テンプレートについては、https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x411 を参照してください

Imports Windows.System
''' <summary>
''' それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
''' </summary>
Public NotInheritable Class MainPage
    Inherits Page

    Private Const m_strUri As String = "https://www.bing.com/"

    Public Sub New()

        ' この呼び出しはデザイナーで必要です。
        InitializeComponent()

        ' InitializeComponent() 呼び出しの後で初期化を追加します。

    End Sub

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

    Protected Overrides Sub OnNavigatedTo(ByVal e As NavigationEventArgs)
        HomeWebView()

        Return
    End Sub

    Protected Overrides Sub OnNavigatedFrom(ByVal e As NavigationEventArgs)
        Me.OnNavigatedFrom(e)

        Return
    End Sub

    Public Sub OnClickBack(ByVal sender As Object, ByVal e As RoutedEventArgs)
        BackWebView()

        Return
    End Sub

    Public Sub OnClickForward(ByVal sender As Object, ByVal e As RoutedEventArgs)
        ForwardWebView()

        Return
    End Sub

    Public Sub OnClickRefresh(ByVal sender As Object, ByVal e As RoutedEventArgs)
        RefreshWebView()

        Return
    End Sub

    Public Sub OnClickHome(ByVal sender As Object, ByVal e As RoutedEventArgs)
        HomeWebView()

        Return
    End Sub

    Public Sub OnClickFind(ByVal sender As Object, ByVal e As RoutedEventArgs)
        Dim strUri As String = textUri.Text
        ShowWebView(strUri)

        Return
    End Sub

    Public Sub OnKeyDownTextUri(ByVal sender As Object, ByVal e As KeyRoutedEventArgs)
        If (e.Key = VirtualKey.Enter) Then
            Dim strUri As String = textUri.Text
            ShowWebView(strUri)
        End If

        Return
    End Sub

    Public Function ShowWebView(ByRef _strUri As String) As Boolean
        Dim bRst As Boolean = True

        Try
            webView.Navigate(New Uri(_strUri, UriKind.Absolute))
            textUri.Text = _strUri
        Catch ex As Exception
            bRst = False
        End Try

        Return bRst
    End Function

    Public Function BackWebView() As Boolean
        Dim bRst As Boolean = True

        Try
            webView.GoBack()
        Catch ex As Exception
            bRst = False
        End Try

        Return bRst
    End Function

    Public Function ForwardWebView() As Boolean
        Dim bRst As Boolean = True

        Try
            webView.GoForward()
        Catch ex As Exception
            bRst = False
        End Try

        Return bRst
    End Function

    Public Function RefreshWebView() As Boolean
        Dim bRst As Boolean = True

        Try
            webView.Refresh()
        Catch ex As Exception
            bRst = False
        End Try

        Return bRst
    End Function

    Public Function HomeWebView() As Boolean
        textUri.Text = m_strUri
        Dim strUri As String = m_strUri
        Return ShowWebView(strUri)
    End Function

    Public Function GetCurUri() As String
        Dim uriSource As Uri = webView.Source

        Return uriSource.ToString()
    End Function
End Class
