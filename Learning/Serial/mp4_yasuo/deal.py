import cv2
import numpy as np

def video_to_led_matrix_data(video_path):
    cap = cv2.VideoCapture(video_path)
    frames_data = []

    if not cap.isOpened():
        print("Error: Cannot open video file.")
        return frames_data

    frame_count = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    print(f"Total frames in the video: {frame_count}")

    frame_num = 0
    while cap.isOpened():
        
        ret, frame = cap.read()
        if not ret:
            break
        
        frame_num += 1
        if frame_num < 105:
            continue
        elif frame_num > 130:
            break

        # 将帧从BGR转换为HSV
        hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # 定义绿色的HSV范围
        lower_green = np.array([0, 0, 0])
        upper_green = np.array([255, 150, 255])

        # 创建掩膜，仅保留绿色部分
        green_mask = cv2.inRange(hsv_frame, lower_green, upper_green)

        # 将原图像与掩膜结合，仅保留非绿色部分
        non_green_frame = cv2.bitwise_and(frame, frame, mask=green_mask)

        # 将非绿色部分转换为灰度图像
        gray_frame = cv2.cvtColor(non_green_frame, cv2.COLOR_BGR2GRAY)
        # 将图像转换为二值图像
        _, binary_frame = cv2.threshold(gray_frame, 1, 255, cv2.THRESH_BINARY)
        
        binary_frame = binary_frame[15: 465, 203: 653]
        # 缩放图像到8x8
        resized_frame = cv2.resize(binary_frame, (128, 64), interpolation=cv2.INTER_AREA)
        # output_shape = np.shape(binary_frame)
        # rate = output_shape[0] / 8
        # output_frame = np.zeros(output_shape)
        # for idx in range(output_shape[0]):
        #     for idy in range(output_shape[1]):
        #         output_frame[idx][idy] = resized_frame[int(idx / rate)][int(idy / rate)]
        
        # cv2.imshow('frame', output_frame)
        # if cv2.waitKey(1) & 0xFF == ord('q'):
        #     break
        # 将二值图像转换为LED矩阵数据
        frame_data = [0 for _ in range(1024)]
        frame_height = 64
        frame_width = 128
        for i in range(0, frame_height):
            for j in range(0, frame_width):
                # print(((0X80 if resized_frame[i][j] else 0) >> (i % 8)))
                frame_data[(i // 8) * 128 + j] = (frame_data[(i // 8) * 128 + j] | ((0X01 if resized_frame[i][j] else 0) << (i % 8)))
        
        frames_data.append(frame_data)
        
        # 只取一帧测试情况
        # break
        

    cap.release()
    return frames_data

def format_frames(frames_data):
    formatted_frames = []
    for frame_data in frames_data:
        formatted_frame = [f'"{byte:02X}"' for byte in frame_data]
        formatted_frames.append(formatted_frame)
    return formatted_frames

def save_frames_to_file(frames_data, file_path):
    with open(file_path, 'w') as f:
        f.write("{")
        for frame in frames_data:
            f.write("{", )
            for byte in frame:
                f.write(f'0X{byte:02X}, ')
            f.write("}, \n")
        f.write("}; \n")

# 替换为你的视频文件路径
video_path = 'D:\\51projects\\mp4_yasuo\\video\\chicken.mp4'

# 将视频转换为LED矩阵数据
frames_data = video_to_led_matrix_data(video_path)

# 格式化数据
# formatted_frames = format_frames(frames_data)

# 保存数据到文件
output_file = 'led_matrix_data.txt'
save_frames_to_file(frames_data, output_file)

print(f"LED矩阵数据已保存到 {output_file}")
