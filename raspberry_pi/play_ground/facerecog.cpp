#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>

#include "facerecog.hpp"

#define YUNET_MODEL_PATH "/home/takahash/opencv/data/haarcascades/haarcascade_frontalface_default.xml"
#define SFACE_MODEL_PATH "/home/takahash/opencv/data/haarcascades/haarcascade_frontalface_default.xml"
static void visualize(cv::Mat &input, cv::Mat &faces, int thickness = 2)
{

    for (int i = 0; i < faces.rows; i++)
    {

        // Draw bounding box
        rectangle(input, cv::Rect2i(int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1)), int(faces.at<float>(i, 2)), int(faces.at<float>(i, 3))), Scalar(0, 255, 0), thickness);
        // Draw landmarks
        circle(input, cv::Point2i(int(faces.at<float>(i, 4)), int(faces.at<float>(i, 5))), 2, Scalar(255, 0, 0), thickness);
        circle(input, cv::Point2i(int(faces.at<float>(i, 6)), int(faces.at<float>(i, 7))), 2, Scalar(0, 0, 255), thickness);
        circle(input, cv::Point2i(int(faces.at<float>(i, 8)), int(faces.at<float>(i, 9))), 2, Scalar(0, 255, 0), thickness);
        circle(input, cv::Point2i(int(faces.at<float>(i, 10)), int(faces.at<float>(i, 11))), 2, Scalar(255, 0, 255), thickness);
        circle(input, cv::Point2i(int(faces.at<float>(i, 12)), int(faces.at<float>(i, 13))), 2, Scalar(0, 255, 255), thickness);
    }
    putText(input, cv::Point(0, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
}
cv::Mat face_recog(cv::Mat frame)
{
    cv::Mat faces;
    cv::Mat vis_image = frame.clone();
    cv::Ptr<cv::FaceDetectorYN> detector = cv::FaceDetectorYN::create(YUNET_MODEL_PATH, "", cv::Size(320, 320), scoreThreshold, nmsThreshold, topK);
    cv::Ptr<cv::FaceRecognizerSF> faceRecognizer = cv::FaceRecognizerSF::create(SFACE_MODEL_PATH, "");

    detector->setInputSize(frame.size());
    detector->detect(frame, faces);
    if (faces.rows < 1)
        return frame;

    // Draw results on the input image
    visualize(vis_image, faces);

    return vis_image;
}