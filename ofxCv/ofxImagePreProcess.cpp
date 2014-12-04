#include "ofxImagePreProcess.h"
#include "DebugUtil.h"


using namespace cv;
using namespace std;
using namespace ofxCv;

void ofxImagePreProcess::setup() {
    isInitial = true;
}


void ofxImagePreProcess::update(const cv::UMat & _src, cv::UMat & dst){
    
    cv::UMat src = _src.clone();
    // - - - - convert into Gray
    cvtColor( src, src, COLOR_BGR2GRAY );
    
    // - - - - filter
    //cv::bilateralFilter(camerauMat, mUMat, 7, 100, 7);
    cv::Size kernel = cv::Size(5,5);
    cv::boxFilter(src, mUMat, -1, kernel);

    //- - - - - get "detials image"
    cv::absdiff(src, mUMat, difMat);
    
    //- - - multiply
    cv::multiply(difMat, 20, difMat);
    
    // - - - -temporal filtering
    if(isInitial)
    {
        tempFilteredDifMat = difMat.clone();
        cv::multiply(tempFilteredDifMat, 1, tempFilteredDifMat);
        isInitial = false;
    }else{
        cv::addWeighted(tempFilteredDifMat,0.7,difMat,0.7,0.0, tempFilteredDifMat);
    }
    
    //- - - - then blur it.
    cv::Size Blurkernel = cv::Size(55,55);
    cv::blur(tempFilteredDifMat, regionMask, Blurkernel);
    
    // - - - then Thresh it.
    cv::threshold(regionMask, regionMask, 50, 255, THRESH_BINARY_INV);
    
    // - - - create masked image from src
    cv::UMat mask;
    mMaskOperated = src.clone();
    cv::multiply(regionMask, 1.0/255.0, mask);
    cv::multiply(mMaskOperated, mask, mMaskOperated);
    
    // - - - expand dynamic range
    // TODO parameters
    cv::subtract(mMaskOperated, 200, mMaskOperatedAndDym);
    cv::multiply(mMaskOperatedAndDym, 255.0 / (255.0 - 200) , mMaskOperatedAndDym);
    
    cv::subtract(src, mMaskOperatedAndDym, dst);
   
}

void ofxImagePreProcess::calcHist(const cv::UMat & mat)
{

    cv::Mat img = mat.getMat(ACCESS_READ).clone();
    
    // ヒストグラムを生成するために必要なデータ
    int image_num = 1;      // 入力画像の枚数
    int channels[] = { 0 }; // cv::Matの何番目のチャネルを使うか　今回は白黒画像なので0番目のチャネル以外選択肢なし
    cv::MatND hist;         // ここにヒストグラムが出力される
    int dim_num = 1;        // ヒストグラムの次元数
    int bin_num = 64;       // ヒストグラムのビンの数
    int bin_nums[] = { bin_num };      // 今回は1次元のヒストグラムを作るので要素数は一つ
    float range[] = { 0, 256 };        // 扱うデータの最小値、最大値　今回は輝度データなので値域は[0, 255]
    const float *ranges[] = { range }; // 今回は1次元のヒストグラムを作るので要素数は一つ
    
    // 白黒画像から輝度のヒストグラムデータ（＝各binごとの出現回数をカウントしたもの）を生成
    cv::calcHist(&img, image_num, channels, regionMask.getMat(ACCESS_READ), hist, dim_num, bin_nums, ranges);
    
    std::cout << hist << std::endl;
 
    /// - - -
    
    cv::Mat hist_img;
    
    {
        // histogramを描画するための画像領域を確保
        int img_width = 512;
        int img_height = 512;
        hist_img = cv::Mat(cv::Size(img_width, img_height), CV_8UC3, cv::Scalar::all(255));
        
        // ヒストグラムのスケーリング
        // ヒストグラムのbinの中で、頻度数最大のbinの高さが、ちょうど画像の縦幅と同じ値になるようにする
        double max_val = 0.0;
        cv::minMaxLoc(hist, 0, &max_val);
        hist = hist * (max_val ? img_height / max_val : 0.0);
        
        // ヒストグラムのbinの数だけ矩形を書く
        for (int j = 0; j < bin_num; ++j){
            // saturate_castは、安全に型変換するための関数。桁あふれを防止
            int bin_w = cv::saturate_cast<int>((double)img_width / bin_num);
            cv::rectangle(
                          hist_img,
                          cv::Point(j*bin_w, hist_img.rows),
                          cv::Point((j + 1)*bin_w, hist_img.rows - cv::saturate_cast<int>(hist.at<float>(j))),
                          cv::Scalar::all(0), -1);
        }
    }
    
    drawCvUmat(hist_img.getUMat(ACCESS_READ).clone(), 600, 0, 400, 400 );
    
}

void ofxImagePreProcess::draw(float w, float h){
    
    drawCvUmat(difMatBinary,0, h, w, h);
    drawCvUmat(regionMask,0, 2 *  h, w, h);
    drawCvUmat(mMaskOperated,0, 3 *  h, w, h);
    drawCvUmat(mMaskOperatedAndDym,0, 4 *  h, w, h);
    
    
    //calcHist(mMaskOperated);
    
    ofSetColor(255);
    ofDrawBitmapStringHighlight("ofxImagePreProcess ", 0, ofGetHeight() - 20);
    
}
