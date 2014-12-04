#include "ofxCvUtilities.h"
#include "ofMath.h"

// vs2010 support (this should be added to the OF core)
#if (_MSC_VER)
#include <stdint.h>
#endif

namespace ofxCv {
	
	using namespace cv;
    
    
    void drawCvUmat(const cv::UMat &uMat,  float x, float y, float w, float h)
    {
        // - - - - - - -- - - - - -
        ofImage img;
        img.allocate(uMat.rows, uMat.cols, OF_IMAGE_COLOR);
        
        //Umat -> mat
//      cv::Mat mat = uMat.getMat(ACCESS_RW);
        
        //mat -> ofImage
        ofxCv::toOf(uMat.getMat(ACCESS_RW), img.getPixelsRef());
        img.update();
        img.draw(x, y, w, h);
    }

    
    //estimateAffine3D function
    ofMatrix4x4 estimateAffine3D(vector<ofVec3f>& from, vector<ofVec3f>& to, vector<unsigned char>& outliers, float accuracy) {
        
        //ERROR handling
        if(from.size() < 1|| to.size() < 1){

            cout<< "tracking point less " << endl;
            ofMatrix4x4 output;
            output.makeIdentityMatrix();
            return output;
        }
        
		Mat fromMat(1, from.size(), CV_32FC3, &from[0]);
		Mat toMat(1, to.size(), CV_32FC3, &to[0]);
		Mat affine;
        //Modified 3
		estimateAffine3D(fromMat, toMat, affine, outliers, 1, accuracy);
        
        cout<< "outliers " << outliers.size() << endl;
        
        if(affine.cols * affine.rows == 0)
        {
            cout<< "affine estimation ERR " << endl;
            ofMatrix4x4 output;
            output.makeIdentityMatrix();
            return output;
        }
        
		ofMatrix4x4 affine4x4;
		affine4x4.set(affine.ptr<double>());
		affine4x4(3, 0) = 0;
		affine4x4(3, 1) = 0;
		affine4x4(3, 2) = 0;
		affine4x4(3, 3) = 1;
		Mat affine4x4Mat(4, 4, CV_32F, affine4x4.getPtr());
		affine4x4Mat = affine4x4Mat.t();
		affine4x4.set(affine4x4Mat.ptr<float>());
		return affine4x4;
	}

	Mat toCv(Mat& mat) {
		return mat;
	}
	
	Point2f toCv(ofVec2f vec) {
		return Point2f(vec.x, vec.y);
	}
	
	Point3f toCv(ofVec3f vec) {
		return Point3f(vec.x, vec.y, vec.z);
	}
	
	cv::Rect toCv(ofRectangle rect) {
		return cv::Rect(rect.x, rect.y, rect.width, rect.height);
	}
	
	Mat toCv(ofMesh& mesh) {
		vector<ofVec3f>& vertices = mesh.getVertices();
		return Mat(1, vertices.size(), CV_32FC3, &vertices[0]);
	}
	
	vector<cv::Point2f> toCv(const ofPolyline& polyline) {
		// if polyline.getVertices() were const, this could wrap toCv(vec<vec2f>)
		vector<cv::Point2f> contour(polyline.size());
		for(int i = 0; i < polyline.size(); i++) {
			contour[i].x = polyline[i].x;
			contour[i].y = polyline[i].y;
		}
		return contour;		
	}
	
	vector<cv::Point2f> toCv(const vector<ofVec2f>& points) {
		vector<cv::Point2f> out(points.size());
		for(int i = 0; i < points.size(); i++) {
			out[i].x = points[i].x;
			out[i].y = points[i].y;
		}
		return out;		
	}
	
	vector<cv::Point3f> toCv(const vector<ofVec3f>& points) {
		vector<cv::Point3f> out(points.size());
		for(int i = 0; i < points.size(); i++) {
			out[i].x = points[i].x;
			out[i].y = points[i].y;
			out[i].z = points[i].z;
		}
		return out;		
	}
	
	Scalar toCv(ofColor color) {
		return Scalar(color.r, color.g, color.b, color.a);
	}
	
	ofVec2f toOf(Point2f point) {
		return ofVec2f(point.x, point.y);
	}
	
	ofVec3f toOf(Point3f point) {
		return ofVec3f(point.x, point.y, point.z);
	}
	
	ofRectangle toOf(cv::Rect rect) {
		return ofRectangle(rect.x, rect.y, rect.width, rect.height);
	}
	
	ofPolyline toOf(cv::RotatedRect rect) {
		vector<cv::Point2f> corners(4);
		rect.points(&corners[0]);
		ofPolyline polyline = toOf(corners);
		return polyline;
	}
	
	float getMaxVal(int cvDepth) {
		switch(cvDepth) {
			case CV_8U: return numeric_limits<uint8_t>::max();
			case CV_16U: return numeric_limits<uint16_t>::max();
				
			case CV_8S: return numeric_limits<int8_t>::max();
			case CV_16S: return numeric_limits<int16_t>::max();
			case CV_32S: return numeric_limits<int32_t>::max();
				
			case CV_32F: return 1;
			case CV_64F: default: return 1;
		}
	}
	
	float getMaxVal(const Mat& mat) {
		return getMaxVal(mat.depth());
	}
    
    ///TODO
    
    /*
	
	// for some reason, cvtColor handles this info internally rather than having
	// a single helper function. so we have to create a helper function to aid
	// in doing the allocationg ofxCv::convertColor()
#define mkcase(x, y) {case x: return y;}
	int getTargetChannelsFromCode(int conversionCode) {
		switch(conversionCode) {
			//	mkcase(CV_RGB2RGBA,4)	mkcase(CV_RGBA2RGB,3) mkcase(CV_RGB2BGRA,4)
			//	mkcase(CV_RGBA2BGR,3) mkcase(CV_BGR2RGB,3) mkcase(CV_BGRA2RGBA,4)
			//	mkcase(CV_BGR2GRAY,1) mkcase(CV_RGB2GRAY,1) mkcase(CV_GRAY2RGB,3)
			//	mkcase(CV_GRAY2RGBA,4) mkcase(CV_BGRA2GRAY,1) mkcase(CV_RGBA2GRAY,1)
			//	mkcase(CV_BGR5652BGR,3) mkcase(CV_BGR5652RGB,3) mkcase(CV_BGR5652BGRA,4)
			//	mkcase(CV_BGR5652RGBA,4) mkcase(CV_BGR5652GRAY,1) mkcase(CV_BGR5552BGR,3)
			//	mkcase(CV_BGR5552RGB,3) mkcase(CV_BGR5552BGRA,4) mkcase(CV_BGR5552RGBA,4)
				mkcase(CV_BGR5552GRAY,1) mkcase(CV_BGR2XYZ,3) mkcase(CV_RGB2XYZ,3)
				mkcase(CV_XYZ2BGR,3) mkcase(CV_XYZ2RGB,3) mkcase(CV_BGR2YCrCb,3)
				mkcase(CV_RGB2YCrCb,3) mkcase(CV_YCrCb2BGR,3) mkcase(CV_YCrCb2RGB,3)
				mkcase(CV_BGR2HSV,3) mkcase(CV_RGB2HSV,3) mkcase(CV_BGR2Lab,3)
				mkcase(CV_RGB2Lab,3) mkcase(CV_BayerGB2BGR,3) mkcase(CV_BayerBG2RGB,3)
				mkcase(CV_BayerGB2RGB,3) mkcase(CV_BayerRG2RGB,3) mkcase(CV_BGR2Luv,3)
				mkcase(CV_RGB2Luv,3) mkcase(CV_BGR2HLS,3) mkcase(CV_RGB2HLS,3)
				mkcase(CV_HSV2BGR,3) mkcase(CV_HSV2RGB,3) mkcase(CV_Lab2BGR,3)
				mkcase(CV_Lab2RGB,3) mkcase(CV_Luv2BGR,3) mkcase(CV_Luv2RGB,3)
				mkcase(CV_HLS2BGR,3) mkcase(CV_HLS2RGB,3) mkcase(CV_BayerBG2RGB_VNG,3)
				mkcase(CV_BayerGB2RGB_VNG,3) mkcase(CV_BayerRG2RGB_VNG,3)
				mkcase(CV_BayerGR2RGB_VNG,3) mkcase(CV_BGR2HSV_FULL,3)
				mkcase(CV_RGB2HSV_FULL,3) mkcase(CV_BGR2HLS_FULL,3)
				mkcase(CV_RGB2HLS_FULL,3) mkcase(CV_HSV2BGR_FULL,3)
				mkcase(CV_HSV2RGB_FULL,3) mkcase(CV_HLS2BGR_FULL,3)
				mkcase(CV_HLS2RGB_FULL,3) mkcase(CV_LBGR2Lab,3) mkcase(CV_LRGB2Lab,3)
				mkcase(CV_LBGR2Luv,3) mkcase(CV_LRGB2Luv,3) mkcase(CV_Lab2LBGR,4)
				mkcase(CV_Lab2LRGB,4) mkcase(CV_Luv2LBGR,4) mkcase(CV_Luv2LRGB,4)
				mkcase(CV_BGR2YUV,3) mkcase(CV_RGB2YUV,3) mkcase(CV_YUV2BGR,3)
				mkcase(CV_YUV2RGB,3)
			default: return 0;
		}
	}*/
    
}