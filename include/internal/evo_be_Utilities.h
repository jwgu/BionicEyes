#pragma once
#ifndef _EVO_BE_UTILITIES_H_
#define _EVO_BE_UTILITIES_H_

#include <evo_be.h>
#include <string>
#include <opencv2/opencv.hpp>
#include "Eigen/Core"

#ifdef _WIN32
#ifdef EVO_BE_UTILITIES_EXPORTS
#define EVO_BE_UTILITIES_API __declspec(dllexport)
#else
#define EVO_BE_UTILITIES_API __declspec(dllimport)
#endif // EVO_BE_IMAGEPROCESS_CORE_EXPORTS
#else
#define EVO_BE_UTILITIES_API
#endif // _WIN32

namespace evo_be
{
    /**
     * @brief Static class API for commonly used utility functions
     */
    class EVO_BE_UTILITIES_API BE_Utilities
    {
    public:
        /**
         * @brief Extract the substring between two delimiters.
         * @param  s                Input string
         * @param  start_delim      First delimiter 
         * @param  stop_delim       Second delimiter
         * @return std::string 
         */
        static std::string getStrBetweenTwoStr(const std::string &s, const std::string &start_delim, const std::string &stop_delim);
        /**
         * @brief Load files of certain extension from path. Files must be zero-padded (e.g. "000.bmp" and "001.bmp")
         * @param  path             Input directory such as "/xxx/yyy"
         * @param  ext              Input extension, currently limited to ".bmp" and ".png"
         * @param  imgFiles_sort    Output file names  {".png"}
         */
        static void loadFiles(std::string path, std::string ext, std::vector<std::string> &imgFiles_sort);
        static void SplitString(std::vector<std::string> &tokens, const std::string &str, const std::string &delimiters = " ", bool trim_empty_str = true);
        static std::string GetProgramOptionAsString(int argc, char **argv, const std::string &option, const std::string &default_value = "");
        static int GetProgramOptionAsInt(int argc, char **argv, const std::string &option, const int default_value = 0);
        static double GetProgramOptionAsDouble(int argc, char **argv, const std::string &option, const double default_value = 0.0);
        static Eigen::VectorXd GetProgramOptionAsEigenVectorXd(int argc, char **argv, const std::string &option, const Eigen::VectorXd default_value = Eigen::VectorXd::Zero(0));
        static bool ProgramOptionExists(int argc, char **argv, const std::string &option);
        static bool ProgramOptionExistsAny(int argc, char **argv, const std::vector<std::string> &options);
        /**
         * @brief Convert degree to radian
         * @param  deg              Input degree
         * @return float 
         */
        static float deg2rad(float deg);
        /**
         * @brief Convert degree to radian
         * @param  deg              Input degree
         * @return double 
         */
        static double deg2rad(double deg);
        /**
         * @brief Compute inverse of a R|t pair on SE(3) group
         * \f[
         * \mathbf{\mathsf{T}}=\begin{bmatrix}
         * \mathbf{\mathsf{R}}^{\phantom{\top}} & \mathbf{t}\\
         * \mathbf{0}^\top & 1        
         * \end{bmatrix}\Rightarrow
         * \mathbf{\mathsf{T}}^{-1}=\begin{bmatrix}
         * \mathbf{\mathsf{R}}^{\top} & -\mathbf{\mathsf{R}}^{\top}\mathbf{t}\\
         * \mathbf{0}^\top & 1        
         * \end{bmatrix}
         * \f]
         * @param  R                Input rotation matrix of a homogenous transform
         * @param  t                Input translation vector of a homogenous transform
         * @param  ROut             Ouput rotation matrix of the inverse of this homogenous transform
         * @param  tOut             Ouput translation vector of the inverse of this homogenous transform
         */
        static void RtInv(const cv::Mat &R, const cv::Mat &t, cv::Mat &ROut, cv::Mat &tOut);
        /**
         * @brief Right-composition two R|t pairs. Let  
         * \f[
         * \mathbf{\mathsf{T}}_a=\begin{bmatrix}
         * \mathbf{\mathsf{R}}^{\phantom{\top}}_a & \mathbf{t}_a\\
         * \mathbf{0}^\top & 1        
         * \end{bmatrix},\quad
         * \mathbf{\mathsf{T}}_b=\begin{bmatrix}
         * \mathbf{\mathsf{R}}^{\phantom{\top}}_b & \mathbf{t}_b\\
         * \mathbf{0}^\top & 1        
         * \end{bmatrix}~.
         * \f]
         * This function performs the following,
         * \f[
         * \mathbf{\mathsf{T}}_a=\mathbf{\mathsf{T}}_a\mathbf{\mathsf{T}}_b
         * \f]
         * @param  Ra               Input rotation matrix of the first homogenous transform; will be modified in-place after right-composition
         * @param  ta               Input translation vector of the first homogenous transform; will be modified in-place after right-composition
         * @param  Rb               Input rotation matrix of the second homogenous transform
         * @param  tb               Input translation vector of the second homogenous transform
         */
        static void RtRightTimes(cv::Mat &Ra, cv::Mat &ta, const cv::Mat &Rb, const cv::Mat &tb);
        static void RtInv(const cv::Matx33d &R, const cv::Matx31d &t, cv::Matx33d &Rout, cv::Matx31d &tout);
        static void RtRightTimes(cv::Matx33d &Ra, cv::Matx31d &ta, const cv::Matx33d &Rb, const cv::Matx31d &tb);
        /**
         * @brief Convert a R|t pair into a homogenous matrix:	    
         * \f[
         * \mathbf{\mathsf{T}}=\begin{bmatrix}
         * \mathbf{\mathsf{R}}^{\phantom{\top}} & \mathbf{t}\\
         * \mathbf{0}^\top & 1        
         * \end{bmatrix}
         * \f]        
         * @param  R                Input rotation 3-by-3 matrix in SO(3) group
         * @param  t                Input translation 3-by-1 vector in T(3) group
         * @param  T                Output homogenous 4-by-4 matrix in SE(3) group
         */
        static void Rt2T(const Eigen::Matrix3f &R, const Eigen::Vector3f &t, Eigen::Matrix4f &T);
        /**
         * @brief Rt2T(R,t,T) when R is the identity matrix
         * @param  t                My Param doc
         * @param  T                My Param doc
         */
        static void Rt2T(const Eigen::Vector3f &t, Eigen::Matrix4f &T);
        /**
         * @brief Rt2T(R,t,T) when t is a zero vector
         * @param  R                My Param doc
         * @param  T                My Param doc
         */
        static void Rt2T(const Eigen::Matrix3f &R, Eigen::Matrix4f &T);
        static void Rt2T(const Eigen::Matrix3d &R, const Eigen::Vector3d &t, Eigen::Matrix4d &T);
        static void Rt2T(const Eigen::Vector3d &t, Eigen::Matrix4d &T);
        static void Rt2T(const Eigen::Matrix3d &R, Eigen::Matrix4d &T);
    };
} // namespace evo_be

#endif