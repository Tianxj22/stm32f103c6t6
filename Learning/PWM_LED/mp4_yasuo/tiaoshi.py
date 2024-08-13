import cv2
import numpy as np

def nothing(x):
    pass

# 读取视频
video_path = 'D:\\51projects\\mp4_yasuo\\video\\chicken.mp4'  # 请替换为你的实际视频路径
cap = cv2.VideoCapture(video_path)

# 创建窗口
cv2.namedWindow('frame')

# 创建TrackBars
# cv2.createTrackbar('LH', 'frame', 0, 255, nothing)
# cv2.createTrackbar('LS', 'frame', 0, 255, nothing)
# cv2.createTrackbar('LV', 'frame', 0, 255, nothing)
# cv2.createTrackbar('UH', 'frame', 255, 255, nothing)
# cv2.createTrackbar('US', 'frame', 255, 255, nothing)
# cv2.createTrackbar('UV', 'frame', 255, 255, nothing)

# 读取视频的某一帧
# cap.set(cv2.CAP_PROP_POS_FRAMES, 20)  # 这里设定为第100帧
# ret, frame = cap.read()
# if not ret:
#     print("Failed to grab the frame.")
#     cap.release()
#     cv2.destroyAllWindows()
#     exit()
cnt = 0
while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        print("Failed to grab the frame.")
        cap.release()
        cv2.destroyAllWindows()
        exit()
    cnt += 1
    # 获取TrackBars的值
    # lh = cv2.getTrackbarPos('LH', 'frame')
    # ls = cv2.getTrackbarPos('LS', 'frame')
    # lv = cv2.getTrackbarPos('LV', 'frame')
    # uh = cv2.getTrackbarPos('UH', 'frame')
    # us = cv2.getTrackbarPos('US', 'frame')
    # uv = cv2.getTrackbarPos('UV', 'frame')

    # 颜色滤波
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    lower_bound = np.array([0, 0, 0])
    upper_bound = np.array([255, 150, 255])
    mask = cv2.inRange(hsv, lower_bound, upper_bound)
    non_green_frame = cv2.bitwise_and(frame, frame, mask=mask)
    
    gray_frame = cv2.cvtColor(non_green_frame, cv2.COLOR_BGR2GRAY)
    # resized_frame = cv2.resize(gray_frame, (8, 8), interpolation=cv2.INTER_AREA)
    _, binary_frame = cv2.threshold(gray_frame, 1, 255, cv2.THRESH_BINARY)
    # 截取部分
    binary_frame = binary_frame[15: 465, 203: 653]
    # print(binary_frame)
    resized_data = cv2.resize(binary_frame, (128, 64), interpolation=cv2.INTER_AREA)
    output_shape = np.shape(binary_frame)
    ratex = output_shape[0] / 64
    ratey = output_shape[1] / 128
    output_frame = np.zeros(output_shape)
    for idx in range(output_shape[0]):
        for idy in range(output_shape[1]):
            output_frame[idx][idy] = resized_data[int(idx / ratex)][int(idy / ratey)]
    
    # 显示结果
    print(f"{cnt}")
    cv2.imshow('frame', resized_data)
    # print(np.shape(binary_frame))

    # 按下 'q' 键退出
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 释放资源
cap.release()
cv2.destroyAllWindows()
