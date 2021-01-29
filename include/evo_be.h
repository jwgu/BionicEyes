/*****************************************************************************
*  Eyevolution BionicEye series products SDK.
*  Copyright (C) 2018 Openking  wang.kaifang@ilooktech.com
*
* @file evo_be.h
* @brief This is for general use of Eyevolution BionicEye series products.
* @author Openking <wang.kaifang@ilooktech.com>
* @date <2018/10/01>
* @version <0.5.1>
* @license
* @note This file is very important! Please Do Not Modify it!!!
* This SDK is only for Eyevolution BionicEye series products.
*****************************************************************************/

#pragma once
#ifndef _EVO_BE_H_
#define _EVO_BE_H_

#include <iostream>
#include <opencv2/core/core.hpp>

#ifndef M_PI
#define M_PI (3.14159265358979323846f)
#endif

#define DEGToRAD(x) (x / 180.0f * M_PI)
#define RADToDEG(x) (x / M_PI * 180.0f)

namespace evo_be
{
	/**************************************************
	 * Run Site type
	 * @brief Run Site type
	 **************************************************/
	enum BE_RunSite_Type
	{
		enumLocal = 0,
		enumRemote = 1,
	};

	/**************************************************
	 * Eye motor type
	 * @brief Eye motor type
	 **************************************************/
	enum MotorType
	{
		enumRightPitch = 0,     /**< Right Pitch Motor */
		enumRightRoll = 1,	    /**< Right Roll Motor */
		enumRightYaw = 2,	    /**< Right Yaw Motor */
		enumLeftPitch = 3,	    /**< Left Pitch Motor */
		enumLeftRoll = 4,	    /**< Left Roll Motor */
		enumLeftYaw = 5,	    /**< Left Yaw Motor */
		enumAllMotor = 6,	    /**< All Motor */
		enumNoMotor = 7,	    /**< No Motor */
	};

    /**************************************************
     * Neck Motor type
     * @brief Neck Motor type
     **************************************************/
	enum MotorType_Neck
	{
		enumNeckPitch = 0,	  /**< Neck Pitch Motor */
		enumNeckRoll = 1,	  /**< Neck Roll Motor */
		enumNeckYaw = 2,	  /**< Neck Yaw Motor */
		enumNeckAllMotor = 3, /**< Neck All Motor */
		enumNeckNoMotor = 4,  /**< Neck No Motor */
	};

    /**************************************************
     * Motor Name
     * @brief Motor Name
     **************************************************/
	static std::string MotorName[6] = {
		"RightPitch",
		"RightRoll",
		"RightYaw",
		"LeftPitch",
		"LeftRoll",
		"LeftYaw"};

    /**************************************************
     * Motor Axis Tags
     * @brief Motor Axis Tags
     **************************************************/
	static std::string MotorTags[3] = {
		"Pitch",
		"Roll",
		"Yaw"};

    /**************************************************
     * Eye Type Tags
     * @brief Eye Type Tags
     **************************************************/
	static std::string EyeTags[2] = {
		"Right",
		"Left"};

    /**************************************************
     * Enumeration of IMU Data Type
     * @brief Enumeration of IMU Data Type
     **************************************************/
	enum IMUDataType
	{
		enumAcc = 0,       /**< Acceleration */
		enumGyo = 1,       /**< Gyroscope */
		enumMag = 2,       /**< Magnetometer */
		enumEuler = 3,     /**< Euler angle */
		enumQuat = 4,      /**< Quaternion */
	};

    /**************************************************
     * Enumeration of General Axis type
     * @brief Enumeration of General Axis type
     **************************************************/
	enum AxisType
	{
		enumPitch = 0,
		enumRoll = 1,
		enumYaw = 2,
		enumX = 0,
		enumY = 1,
		enumZ = 2,
		enumA = 0,
		enumB = 1,
		enumC = 2,
		enumD = 3,
	};

    /**************************************************
     * Enumeration of image color type
     * @brief Enumeration of image color type
     **************************************************/
	enum ImageColorType
	{
		enumMono = 0,
		enumColor = 1,
	};

    /**************************************************
     * Enumeration of camera index type
     * @brief Enumeration of camera index type
     **************************************************/
	enum CameraIndex
	{
		enumLeft = 0,
		enumRight = 1,
		enumBoth = 2,
	};

    /**************************************************
     * Enumeration of GPS Data Type
     * @brief Enumeration of GPS Data Type
     **************************************************/
	enum GpsDataType
	{
		enumLongitude = 0,
		enumLatitude = 1,
		enumGpsHeight = 2,
		enumGpsGMT = 3,
	};

    /**************************************************
     * Enumeration of SV work type
     * @brief Enumeration of Standard Vergence type,
     * mainly include global sv and certre sv
     **************************************************/
	enum SVType
	{
		enumGlobalSV = 0,         /**< Global sv */
		enumCentreSV = 1,         /**< Centre sv */
		enumAreaSV = 2,	          /**< Area sv */
	};

#pragma pack(1)
    /**************************************************
     * Bionic Eye ip information structure
     * @brief Bionic Eye ip information structure
     **************************************************/
	struct BE_IpInfo
	{
		char deviceName[30];	        /**< bionic eye device name */
		unsigned int ipAddrInt;         /**< ip addr in uint (like 0x01010101) */
		char ipAddrStr[20];		        /**< ip addr in string (like "1.1.1.1") */
	};

    /**************************************************
     * Bionic Eye basic data structure, include all synchronized data
     * @brief Bionic eye general information
     * @note Do not modify this struct!!!
     **************************************************/
	struct BE_ImageGeneralInfo
	{
		cv::Mat image;              /**< Image(sidebyside) */

		uint32_t id;			    /**< unique global id */
		uint32_t timeStamp;		    /**< timestamp (100 us) */
		BE_IpInfo be_device_info;   /**< BE device info */

		ImageColorType colorType;   /**< Image color type */
		CameraIndex cameraIndex;    /**< Camera index */
		long imageLen;              /**< Image length (Bytes) */
		int imageTranQualityLevel;  /**< image transfer quality level */
		cv::Size imageSize;		    /**< Image size of this image */
		cv::Size imageSize_Trans;   /**< Image Size of network transform image */

		float motorData[6];	        /**< Motor Coder Data */
		float imuData[5][4];        /**< IMU Data */
		double gpsData[4];	        /**< GPS Data(longitude, latitude, height, GMT) */

		bool isMovingFastly;        /**< whether eyes move fastly when grab this data */

        BE_ImageGeneralInfo()
        {
            memset(&(this->id), 0, sizeof(BE_ImageGeneralInfo) - sizeof(cv::Mat));
        }

		inline BE_ImageGeneralInfo operator=(BE_ImageGeneralInfo &tmp) /**< @note shallow copy */
		{
			memcpy(&(this->id), &(tmp.id), sizeof(BE_ImageGeneralInfo) - sizeof(cv::Mat));
			if (!tmp.image.empty())
				this->image = tmp.image;
			return *this;
		}

		inline BE_ImageGeneralInfo &operator=(const BE_ImageGeneralInfo &tmp)
		{
			if (this != &tmp)
			{
				memcpy(&(this->id), &(tmp.id), sizeof(BE_ImageGeneralInfo) - sizeof(cv::Mat));
				if (!tmp.image.empty())
					this->image = tmp.image;
			}
			return *this;
		}

		inline void copyTo(BE_ImageGeneralInfo &tmp) const // deep copy, use this first, more efficient
		{
			memcpy(&(tmp.id), &(this->id), sizeof(BE_ImageGeneralInfo) - sizeof(cv::Mat));
			if (!this->image.empty())
				this->image.copyTo(tmp.image);
		}

		inline BE_ImageGeneralInfo clone() const // deep copy
		{
			BE_ImageGeneralInfo tmp;
			copyTo(tmp);
			return tmp;
		}
	};

#pragma pack()
} // namespace evo_be
#endif //_EVO_BE_H_