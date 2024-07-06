#ifndef __OPENCV__
#define __OPENCV__
#include "opencv2/opencv.hpp"
#endif
#include <iostream>
#include "pthread.h"

cv::Mat crop_white(cv::Mat image_org)
{
    int x, y, i, area_max_index;
    double area, area_max;
    /* 切り取る領域 */
    int upper_left_x= image_org.size[0], upper_left_y= image_org.size[1], lower_right_x, lower_right_y;
    /* 切り出し画像 */
    cv::Mat tmp_image, crop_image; 
    /* 検出された輪郭．各輪郭は，点のベクトルとして格納 */
    std::vector<std::vector<cv::Point>> contours;
    /* オプション．画像のトポロジーに関する情報を含む出力ベクトル */
    std::vector<cv::Vec4i> hierarchy;

    /*- グレースケール画像にする */
    cv::cvtColor(image_org, tmp_image, cv::COLOR_BGR2GRAY);
    /*- ２値化する */
    cv::threshold(tmp_image, tmp_image, 200, 255, cv::THRESH_BINARY);
    /*- 輪郭を抽出する */
    cv::findContours(tmp_image, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    /* 輪郭ごとの処理 今回は一番外側の領域を取り出す*/
    for( size_t i = 0; i< contours.size(); i++ )
    {
        if( cv::Point(contours[i][0]).x == 0 && cv::Point(contours[i][0]).y == 0)
        {
            continue;
        }
        area = cv::contourArea(contours[i]);
        if( area > area_max)
        {
            area_max = area;
            area_max_index = i;
        }
    }

    /* 領域の左上と右下を取得する*/
    for( size_t i = 0; i< contours[area_max_index].size(); i++ )
    {
        x = contours[area_max_index][i].x;
        y = contours[area_max_index][i].y;
        if ( upper_left_x > x)
        {
            upper_left_x = x;
        }
        if ( upper_left_y > y)
        {
            upper_left_y = y;
        }
        if ( lower_right_x < x)
        {
            lower_right_x = x;
        }
        if ( lower_right_y < y)
        {
            lower_right_y = y;
        }
    }
    upper_left_x = upper_left_x + 1;
    upper_left_y = upper_left_y + 1;
    /* 領域の描画*/
    // drawContours( image_org, contours, (int)area_max_index, (255,255,255), 2, cv::LINE_8, hierarchy, 0 );
    /* 矩形図形の描画 */
    // cv::rectangle(image_org, cv::Point(upper_left_x,upper_left_y), cv::Point(lower_right_x,lower_right_y), cv::Scalar(0, 0, 0), 5);
    crop_image = image_org(cv::Rect(upper_left_x, upper_left_y, lower_right_x-upper_left_x ,lower_right_y-upper_left_y));
    // cv::imshow("test", crop_image);
    // cv::waitKey(0);

    return crop_image;
}
int main(int argh, char *argv[])
{
    cv::Mat image_org, crop_image, image_left, image_right, diff_img; // 画像

    image_org = cv::imread("../test_image.png", 1);
    crop_image = crop_white(image_org);
    /* 始点となるx座標, 始点となるy座標, 横幅(width), 縦幅(height) */
    image_left = crop_image(cv::Rect(0,0,(crop_image.size[1]/2),crop_image.size[0]));
    image_right = crop_image(cv::Rect(crop_image.size[1]/2,0,crop_image.size[1]/2,crop_image.size[0]));

    cv::absdiff(image_left,image_right, diff_img);
    cv::imshow("test",diff_img);
    cv::waitKey(0);

    return 0;
}
