' 空白ページの項目テンプレートについては、https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x411 を参照してください

Imports Windows.Storage.Streams
''' <summary>
''' それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
''' </summary>
Public NotInheritable Class MainPage
    Inherits Page

    ''' <summary>
    ''' コンストラクタ
    ''' </summary>
    Public Sub New()

        ' この呼び出しはデザイナーで必要です。
        InitializeComponent()

        ' InitializeComponent() 呼び出しの後で初期化を追加します。

    End Sub

    ''' <summary>
    ''' ファイル選択ボタンのクリックイベント
    ''' </summary>
    ''' <param name="sender">オブジェクト</param>
    ''' <param name="e">ルーティングイベントのデータ</param>
    Public Async Sub OnClickFileSelect(ByVal sender As Object, ByVal e As RoutedEventArgs)
        Dim picker = New Windows.Storage.Pickers.FileOpenPicker()
        picker.SuggestedStartLocation = Windows.Storage.Pickers.PickerLocationId.VideosLibrary
        picker.FileTypeFilter.Add("*")
        picker.FileTypeFilter.Add(".png")
        picker.FileTypeFilter.Add(".jpg")
        picker.FileTypeFilter.Add(".jpeg")
        Dim file = Await picker.PickSingleFileAsync()
        If file Is Nothing Then
            Return
        End If

        Dim openFile = Await file.OpenReadAsync()
        Me.Image.Source = CreateImage(openFile)
    End Sub

    ''' <summary>
    ''' ビットマップイメージ生成
    ''' </summary>
    ''' <param name="_openFile">ファイルランダムアクセスストリーム</param>
    ''' <returns>ビットマップイメージ</returns>
    Public Function CreateImage(ByVal _openFile As IRandomAccessStreamWithContentType) As BitmapImage
        Dim bitmap As BitmapImage = New BitmapImage()
        bitmap.SetSource(_openFile)
        Return bitmap
    End Function
End Class
