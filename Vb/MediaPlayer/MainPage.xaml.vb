﻿' 空白ページの項目テンプレートについては、https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x411 を参照してください

Imports Windows.Storage
Imports Windows.Storage.AccessCache
''' <summary>
''' それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
''' </summary>
Public NotInheritable Class MainPage
    Inherits Page

    Private m_storageItemAccessList As StorageItemAccessList
    Private m_storageFile As StorageFile

    Public Sub New()
        ' この呼び出しはデザイナーで必要です。
        InitializeComponent()

        ' InitializeComponent() 呼び出しの後で初期化を追加します。
    End Sub

    Protected Overrides Sub OnNavigatedTo(ByVal e As NavigationEventArgs)
        m_storageItemAccessList = StorageApplicationPermissions.FutureAccessList
        m_storageItemAccessList.Clear()
    End Sub

    Protected Overrides Sub OnNavigatedFrom(ByVal e As NavigationEventArgs)
        mediaElement.Source = Nothing
        Me.OnNavigatedFrom(e)
    End Sub

    Private Async Sub BtnFileSelect_Click(ByVal sender As Object, ByVal e As RoutedEventArgs)
        Dim picker = New Windows.Storage.Pickers.FileOpenPicker()
        picker.SuggestedStartLocation = Windows.Storage.Pickers.PickerLocationId.VideosLibrary
        picker.FileTypeFilter.Add("*")
        picker.FileTypeFilter.Add(".mp4")
        m_storageFile = Await picker.PickSingleFileAsync()
        If (m_storageFile Is Nothing) Then
            Return
        End If

        m_storageItemAccessList.Add(m_storageFile)
        mediaElement.SetSource(Await m_storageFile.OpenReadAsync(), m_storageFile.ContentType)
    End Sub
End Class