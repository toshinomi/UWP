//
// MainPage.xaml.h
// MainPage クラスの宣言。
//

#pragma once

#include "MainPage.g.h"

namespace MediaPlayer
{
	/// <summary>
	/// それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		MainPage();

		/// <summary>
		/// ファイル選択ボタンのクリックイベント
		/// </summary>
		/// <param name="sender">オブジェクト</param>
		/// <param name="e">ルーティングイベントのデータ</param>
		void OnClickFileSelect(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

	private:
		Windows::Storage::StorageFile^ m_storageFile;

	};
}
