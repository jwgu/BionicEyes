//
// Created by be on 2019/8/27.
//

#include "evo_be_Common.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>

using namespace evo_be;

int main()
{
    CBionicEyes *device = device->create(enumConnect_ImageControl, enumDeviceServer_First);

    // on/off SV function
    device->onoff_SV(false);

//    device->setImageResolution_Transfer(cv::Size(1920,540));
//    device->setImageResolution(cv::Size(3840,1080));
//    device->setImageColor_Transfer(enumColor);
//    device->setImageCompressionQuality(95);
////    device->setImageColor(enumMono);
//    //cout<< device->getMaxImageFrameRate()<<endl;
//    device->setDataRate_Transfer(25);
    while (1)
    {
        cout<< "test"<<endl;
        if (device->isBeDataReady())
        {
            BE_ImageGeneralInfo data = device->getBeData();
            if(!data.image.empty())
            {
                cv::Mat temp;
                cv::resize(data.image, temp, cv::Size(960, 480));
                cv::imshow("BE_Image", temp);
            }
            cout<<data.imageSize_Trans<<"  "<<data.imageTranQualityLevel<<endl;
        }
        cv::waitKey(40);
    }
    return 0;
}