{
  "targets": [
    {
      "target_name": "turret",
      "sources": [ "base64.cpp", "turret.cpp" ],
      "include_dirs": ["<!(node -e \"require('nan')\")", "/usr/local/include/opencv", "/usr/local/include"],
      "libraries": ["-L/usr/local/lib", "-lopencv_shape", "-lopencv_stitching", "-lopencv_objdetect", "-lopencv_superres", "-lopencv_videostab", "-lippicv", "-lopencv_calib3d", "-lopencv_features2d", "-lopencv_highgui", "-lopencv_videoio", "-lopencv_imgcodecs", "-lopencv_video", "-lopencv_photo", "-lopencv_ml", "-lopencv_imgproc", "-lopencv_flann", "-lopencv_core"]
    }
  ]
}
