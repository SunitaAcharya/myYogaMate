# mobilenet_v2_1.0_224
- mobilenet_v2_1.0_224.tflite
    - https://tfhub.dev/tensorflow/lite-model/mobilenet_v2_1.0_224/1/default/1
    - Licensed under the Apache License, Version 2.0
- mobilenet_v2_1.0_224_quant.tflite
    - https://tfhub.dev/tensorflow/lite-model/mobilenet_v2_1.0_224_quantized/1/default/1
    - Licensed under the Apache License, Version 2.0
- mobilenet_v2_1.0_224_quant_edgetpu.tflite
    - `!edgetpu_compiler mobilenet_v2_1.0_224_quant.tflite`
- mobilenet_v2_1.0_224.onnx
    - `tflite2onnx  mobilenet_v2_1.0_224.tflite mobilenet_v2_1.0_224_.onnx`
    - `python3 -m onnxsim  mobilenet_v2_1.0_224_.onnx mobilenet_v2_1.0_224.onnx`
    - Note: this model doesn't work on OpenCV
- mobilenet_v2_1.0_224.mnn
    - `MNNConvert.exe -f ONNX --modelFile mobilenet_v2_1.0_224.onnx --MNNModel mobilenet_v2_1.0_224.mnn --bizCode biz`
- mobilenet_v2_1.0_224.param, mobilenet_v2_1.0_224.bin
    - `onnx2ncnn.exe mobilenet_v2_1.0_224.onnx`

# coco_ssd_mobilenet_v1_1.0_quant_2018_06_29
- https://www.tensorflow.org/lite/models/object_detection/overview
- https://storage.googleapis.com/download.tensorflow.org/models/tflite/coco_ssd_mobilenet_v1_1.0_quant_2018_06_29.zip
    - Licensed under the Apache License, Version 2.0

# deeplabv3_mnv2_dm05_pascal_quant
- https://github.com/google-coral/edgetpu/tree/master/test_data
- https://github.com/google-coral/edgetpu/blob/master/test_data/deeplabv3_mnv2_dm05_pascal_quant.tflite
- https://github.com/google-coral/edgetpu/blob/master/test_data/deeplabv3_mnv2_dm05_pascal_quant_edgetpu.tflite
    - Licensed under the Apache License, Version 2.0

# hand tracking
- https://github.com/google/mediapipe/tree/master/mediapipe/models/palm_detection.tflite
- https://github.com/google/mediapipe/tree/master/mediapipe/models/hand_landmark.tflite
    - Licensed under the Apache License, Version 2.0

# style transfer
- https://www.tensorflow.org/lite/models/style_transfer/overview
- https://tfhub.dev/google/lite-model/magenta/arbitrary-image-stylization-v1-256/fp16/prediction/1?lite-format=tflite
- https://tfhub.dev/google/lite-model/magenta/arbitrary-image-stylization-v1-256/fp16/transfer/1?lite-format=tflite
- https://github.com/tensorflow/examples/tree/master/lite/examples/style_transfer/android/app/src/main/assets/thumbnails
    - Licensed under the Apache License, Version 2.0

# lite-model_midas_v2_1_small_1_lite_1.tflite
- https://tfhub.dev/intel/lite-model/midas/v2_1_small/1/lite/1
    - Licensed under MIT License
    - Copyright (c) 2019 Intel ISL (Intel Intelligent Systems Lab)

# centernet_mobilenetv2_fpn_kpts_480x640.tflite
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/042_centernet/20_tensorflow_models/download_centernet_mobilenetv2_fpn_kpts_480x640.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://github.com/tensorflow/models/blob/master/research/object_detection/g3doc/tf2_detection_zoo.md
    - Licensed under the Apache License, Version 2.0

# lite-model_efficientdet_lite0_detection_metadata_1.tflite
- https://tfhub.dev/tensorflow/lite-model/efficientdet/lite0/detection/metadata/1
    - Licensed under the Apache License, Version 2.0

# nanodet_320x320.tflite, nanodet_320x320.onnx
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/072_NanoDet/download.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://github.com/RangiLyu/nanodet
    - Licensed under the Apache License, Version 2.0

# yolov5_480x640.tflite
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/059_yolov5/22_yolov5s_new/download.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://github.com/ultralytics/yolov5
    - Licensed under the GNU General Public License v3.0
    - https://github.com/ultralytics/yolov5/blob/master/LICENSE

# yolox_nano_480x640.tflite, yolox_nano_480x640.onnx
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/132_YOLOX/download_nano_new.sh
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/132_YOLOX/download_nano.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://github.com/Megvii-BaseDetection/YOLOX
    - Licensed under the GNU General Public License v3.0

# face_detection_back_256x256_float32.tflite, face_detection_front.tflite, face_detection_front_128x128_float32.tflite
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/030_BlazeFace/01_float32/download.sh
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/030_BlazeFace/01_float32/download_new.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://github.com/google/mediapipe/tree/master/mediapipe/models
    - Licensed under the Apache License, Version 2.0

# dbface_mbnv2_480x640.tflite
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/041_DBFace/21_mobilenetv2/download.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://github.com/dlunion/DBFace
    - Licensed under the MIT License
    - https://github.com/dlunion/DBFace/issues/19#issuecomment-628336583

# face_landmark.tflite
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/032_FaceMesh/01_float32/download.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://github.com/google/mediapipe/tree/master/mediapipe/models
    - Licensed under the Apache License, Version 2.0


# head-pose-estimation-adas-0001.tflite
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/134_head-pose-estimation-adas-0001/download.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://github.com/openvinotoolkit/open_model_zoo/tree/master/models/intel/head-pose-estimation-adas-0001
    - Licensed under the Apache License, Version 2.0

# WHENet.tflite
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/106_WHENet/download.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://github.com/Ascend-Research/HeadPoseEstimation-WHENet.git
    - Licensed under the BSD 3-Clause "New" or "Revised" License
    - https://github.com/Ascend-Research/HeadPoseEstimation-WHENet/blob/master/LICENSE.txt

# movenet_lightning.tflite
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/115_MoveNet/download_lightning_v4.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://tfhub.dev/google/movenet/singlepose/lightning/4
    - Licensed under the Apache License, Version 2.0

# mobilenet_v3_segm_256.tflite
- https://github.com/NikolasEnt/PersonMask_TFLite

# deepsort_128x64.tflite, deepsort_128x64.onnx
- https://github.com/PINTO0309/PINTO_model_zoo/blob/main/087_DeepSort/download.sh
    - Licensed under the MIT License
    - https://github.com/PINTO0309/PINTO_model_zoo/blob/main/LICENSE
- https://github.com/mikel-brostrom/Yolov5_DeepSort_Pytorch
    - Licensed under the GNU General Public License v3.0
    - https://github.com/mikel-brostrom/Yolov5_DeepSort_Pytorch/blob/master/LICENSE
