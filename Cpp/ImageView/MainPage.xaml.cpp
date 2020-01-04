//
// MainPage.xaml.cpp
// MainPage クラスの実装。
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ImageView;
using namespace Concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace Windows::Storage::AccessCache;

// 空白ページの項目テンプレートについては、https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x411 を参照してください

/// <summary>
/// コンストラクタ
/// </summary>
MainPage::MainPage()
{
	InitializeComponent();
}

/// <summary>
/// ファイル選択ボタンのクリックイベント
/// </summary>
/// <param name="sender">オブジェクト</param>
/// <param name="e">ルーティングイベントのデータ</param>
void MainPage::OnClickFileSelect(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto picker = ref new Windows::Storage::Pickers::FileOpenPicker();
	picker->SuggestedStartLocation = Windows::Storage::Pickers::PickerLocationId::VideosLibrary;
	picker->FileTypeFilter->Append("*");
	picker->FileTypeFilter->Append(".png");
	picker->FileTypeFilter->Append(".jpg");
	picker->FileTypeFilter->Append(".jpeg");
	create_task(picker->PickSingleFileAsync()).then([this](Windows::Storage::StorageFile^ file)
	{
		if (file == nullptr)
		{
			return;
		}

		create_task(file->OpenReadAsync()).then([this](Windows::Storage::Streams::IRandomAccessStreamWithContentType^ openFile)
		{
			this->Image->Source = CreateImage(openFile);
		});
	});
}

/// <summary>
/// ビットマップイメージ生成
/// </summary>
/// <param name="_openFile">ファイルランダムアクセスストリーム</param>
/// <returns>ビットマップイメージ</returns>
BitmapImage^ MainPage::CreateImage(IRandomAccessStreamWithContentType^ _openFile)
{
	auto bitmap = ref new BitmapImage();
	bitmap->SetSource(_openFile);
	return bitmap;
}
