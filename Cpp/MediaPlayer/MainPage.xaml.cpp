//
// MainPage.xaml.cpp
// MainPage クラスの実装。
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Concurrency;
using namespace MediaPlayer;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Media::Core;
using namespace Windows::Media::Editing;
using namespace Windows::Media::Transcoding;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace Windows::Storage::AccessCache;

// 空白ページの項目テンプレートについては、https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x411 を参照してください

MainPage::MainPage()
{
	InitializeComponent();
}

void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
}

void MainPage::OnNavigatedFrom(NavigationEventArgs^ e)
{
	mediaElement->Source = nullptr;
}

void MainPage::OnClickFileSelect(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto picker = ref new FileOpenPicker();
	picker->SuggestedStartLocation = PickerLocationId::VideosLibrary;
	picker->FileTypeFilter->Append("*");
	picker->FileTypeFilter->Append(".mp4");

	create_task(picker->PickSingleFileAsync()).then([this](StorageFile^ videoFile)
	{
		if (videoFile == nullptr)
		{
			return;
		}

		m_storageFile = videoFile;

		create_task(m_storageFile->OpenReadAsync()).then([this](IRandomAccessStreamWithContentType^ videoSource)
		{
			mediaElement->SetSource(videoSource, m_storageFile->ContentType);
		});
	});
}
