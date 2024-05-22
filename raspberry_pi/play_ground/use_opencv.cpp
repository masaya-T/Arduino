#include "opencv2/opencv.hpp"
#include "facerecog.hpp"

int main(int argh, char *argv[])
{
    cv::VideoCapture cap(1); // デバイスのオープン
    cv::Mat frame;           // 取得したフレーム
    if (!cap.isOpened())     // カメラデバイスが正常にオープンしたか確認．
    {
        // 読み込みに失敗したときの処理
        return -1;
    }

    while (cap.read(frame)) // 無限ループ
    {
        face_recog(frame);
        cv::imshow("win", frame); // 画像を表示．
        const int key = cv::waitKey(1);
        if (key == 'q' /*113*/) // qボタンが押されたとき
        {
            break; // whileループから抜ける．
        }
        else if (key == 's' /*115*/) // sが押されたとき
        {
            // フレーム画像を保存する．
            cv::imwrite("img.png", frame);
        }
    }
    cv::destroyAllWindows();
    return 0;
}
