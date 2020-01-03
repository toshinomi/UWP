using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Graphics.Imaging;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

// 空白ページの項目テンプレートについては、https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x411 を参照してください

namespace ImgProc
{
    /// <summary>
    /// それ自体で使用できる空白ページまたはフレーム内に移動できる空白ページ。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        /// <summary>
        /// コンストラクタ
        /// </summary>
        public MainPage()
        {
            this.InitializeComponent();
        }

        /// <summary>
        /// ファイル選択ボタンのクリックイベント
        /// </summary>
        /// <param name="sender">オブジェクト</param>
        /// <param name="e">ルーティングイベントのデータ</param>
        public async void OnClickFileSelect(object sender, RoutedEventArgs e)
        {
            var picker = new Windows.Storage.Pickers.FileOpenPicker();
            picker.SuggestedStartLocation = Windows.Storage.Pickers.PickerLocationId.VideosLibrary;
            picker.FileTypeFilter.Add("*");
            picker.FileTypeFilter.Add(".png");
            picker.FileTypeFilter.Add(".jpg");
            picker.FileTypeFilter.Add(".jpeg");
            var file = await picker.PickSingleFileAsync();
            if (file == null)
            {
                return;
            }

            var openFile = await file.OpenReadAsync();
            BitmapImage bitmap = new BitmapImage();
            bitmap.SetSource(openFile);

            var softwareBitmap = await CreateSoftwareBitmap(file, bitmap);
            ImgProcGrayScale(softwareBitmap);
            this.Image.Source = await ConvertToSoftwareBitmapSource(softwareBitmap);
        }

        /// <summary>
        /// ソフトウェアビットマップイメージ生成
        /// </summary>
        /// <param name="_file">ストレージファイル</param>
        /// <param name="_bitmap">ビットマップイメージ</param>
        /// <returns>ソフトウェアビットマップ</returns>
        public async Task<SoftwareBitmap> CreateSoftwareBitmap(Windows.Storage.StorageFile _file, BitmapImage _bitmap)
        {
            Windows.Storage.Streams.IRandomAccessStream random = await Windows.Storage.Streams.RandomAccessStreamReference.CreateFromFile(_file).OpenReadAsync();
            Windows.Graphics.Imaging.BitmapDecoder decoder = await Windows.Graphics.Imaging.BitmapDecoder.CreateAsync(random);

            var softwareBitmap = new SoftwareBitmap(BitmapPixelFormat.Rgba8, _bitmap.PixelWidth, _bitmap.PixelHeight);
            return softwareBitmap = await decoder.GetSoftwareBitmapAsync();
        }

        /// <summary>
        /// 画像処理グレースケール
        /// </summary>
        /// <param name="_bitmap">ソフトウェアビットマップ</param>
        public void ImgProcGrayScale(SoftwareBitmap _bitmap)
        {
            int nIdxWidth;
            int nIdxHeight;
            unsafe
            {
                using (var buffer = _bitmap.LockBuffer(BitmapBufferAccessMode.ReadWrite))
                using (var reference = buffer.CreateReference())
                {
                    if (reference is IMemoryBufferByteAccess)
                    {
                        byte* pData;
                        uint capacity;
                        ((IMemoryBufferByteAccess)reference).GetBuffer(out pData, out capacity);

                        var desc = buffer.GetPlaneDescription(0);

                        for (nIdxHeight = 0; nIdxHeight < desc.Height; nIdxHeight++)
                        {
                            for (nIdxWidth = 0; nIdxWidth < desc.Width; nIdxWidth++)
                            {
                                var pixel = desc.StartIndex + desc.Stride * nIdxHeight + 4 * nIdxWidth;

                                byte b = pData[pixel + 0];
                                byte g = pData[pixel + 1];
                                byte r = pData[pixel + 2];

                                byte nGrayScale = (byte)((b + g + r) / 3);

                                pData[pixel + 0] = nGrayScale;
                                pData[pixel + 1] = nGrayScale;
                                pData[pixel + 2] = nGrayScale;
                            }
                        }
                    }
                }
            }
        }

        /// <summary>
        /// ソフトウェアビットマップからソフトウェアビットマップソース変換
        /// </summary>
        /// <param name="_bitmap">ソフトウェアビットマップ</param>
        /// <returns>ソフトウェアビットマップソース</returns>
        public async Task<SoftwareBitmapSource> ConvertToSoftwareBitmapSource(SoftwareBitmap _bitmap)
        {
            SoftwareBitmap displayableImage = SoftwareBitmap.Convert(_bitmap, BitmapPixelFormat.Bgra8, BitmapAlphaMode.Premultiplied);
            SoftwareBitmapSource bitmapSource = new SoftwareBitmapSource();
            await bitmapSource.SetBitmapAsync(displayableImage);

            return bitmapSource;
        }
    }
}
