import cv2
import os

def get_video_fram(video, savepath, prefix, interval, shrink_rate):
    if not os.path.exists(savepath):
        os.mkdir(savepath)
    caper = cv2.VideoCapture(video)
    total_frame = int(caper.get(7)) #获取总帧数
    cnt = 0
    for i in range(0, total_frame, interval):
        print("Extracting image " + str(cnt) + ", " + str(int(total_frame/interval+1)) + " images to extract in total.")
        caper.set(1, i)
        flag, frame = caper.read()
        if flag:
            save_img = "{}/{}_{:d}.jpg".format(savepath, prefix, cnt)
            output = cv2.resize(frame, (0, 0), fx=shrink_rate, fy=shrink_rate)
            cv2.imwrite(save_img, output)
            cnt += 1
    caper.release()
    print("Extraction done. Totally extracted " + str(cnt) + " images.")


video = input("请输入源视频路径: ")
savepath = input("请输入保存文件夹路径: ")
prefix = input("请输入想要的保存文件名前缀: ")
interval = int(input("请输入取样间隔(单位:帧): "))
shrink_rate = int(input("请输入缩放比例(0~100): "))
get_video_fram(video, savepath, prefix, interval, shrink_rate/100)
