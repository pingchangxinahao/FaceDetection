#include <aac_ndkopencv_OpencvNativeClass.h>
#include <android/log.h>

#define APPNAME "NDKopenCV"


JNIEXPORT jint JNICALL Java_aac_ndkopencv_OpencvNativeClass_convertGray
  (JNIEnv *, jclass, jlong addrRgba, jlong addrGray){
    Mat& mrgb = *(Mat*) addrRgba;
    Mat& mgray = *(Mat*) addrGray;

    int conv;
    jint retVal;
    conv = toGray(mrgb,mgray);

    retVal = (jint) conv;

    return retVal;

  }
  

JNIEXPORT void JNICALL Java_aac_ndkopencv_OpencvNativeClass_Open(){
    processor->setFrameProcessor(getSkin);

}

JNIEXPORT jboolean JNICALL
        Java_aac_ndkopencv_OpencvNativeClass_ProcessFrame(JNIEnv *env, jobject instance,jlong addrRgba,jstring rpalm_path,jstring fist_path,jstring right_path) {

    Mat& img  = *(Mat*)addrRgba;
    //LOGI("from c++ xx");
    /* const char *str_rpalm = env->GetStringUTFChars(rpalm_path, 0);
     const char *str_fist = env->GetStringUTFChars(fist_path, 0);
     int ret = getGestureStyle(img,str_rpalm,str_fist);

    LOGI("=====xxx path=%d",ret);*/
    const char *str_fist = env->GetStringUTFChars(fist_path, 0);
    const char *str_right = env->GetStringUTFChars(right_path, 0);
    // LOGI("xxx path=%s",str_rpalm);
    processor->run(img,str_fist,NULL,NULL);
    return flag_rpalm;

}

JNIEXPORT void JNICALL Java_aac_ndkopencv_OpencvNativeClass_faceDetection
  (JNIEnv *, jclass, jlong addrRgba){
    Mat& frame = *(Mat*) addrRgba;
    detect(frame);
  }

void detect(Mat& frame){
    String face_cascade_name = "/storage/emulated/0/data/lbpcascade_frontalface.xml";
    CascadeClassifier face_cascade;

    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return ; };
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80) );
    for( size_t i = 0; i < faces.size(); i++ ) {
        rectangle(frame, faces[i].tl(), faces[i].br(), Scalar(0, 255, 0, 255),3,LINE_8,0);
    }
}

int toGray(Mat img, Mat& gray){
    cvtColor(img, gray, CV_RGBA2GRAY);

    if(gray.rows == img.rows && gray.cols == img.cols)
        return 1;
    else
        return 0;
}
