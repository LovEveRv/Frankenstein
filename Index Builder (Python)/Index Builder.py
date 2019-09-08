import os
import cv2


def build_index(path, extension, filter):
    index_file = open(path + "/image_index", "w")
    filter_x = int(filter[0])
    filter_y = int(filter[1])
    NoFilter = False
    if filter_x == 0 and filter_y == 0:
        NoFilter = True
    for root, dirs, files in os.walk(path):
        i = 0
        for file in files:
            if os.path.splitext(file)[1] != extension:
                continue
            img = cv2.imread(path+'/'+file)
            if img is None:
                continue
            y, x = img.shape[0: 2]
            if NoFilter:
                if filter_x == 0 and filter_y == 0:
                    filter_x = x
                    filter_y = y
                else:
                    filter_x = min(filter_x, x)
                    filter_y = min(filter_y, y)
            elif x < filter_x or y < filter_y:
                continue
            index_file.write(str(i) + ' "' + file + '"\n')
            i += 1
            print("Image " + str(i) + " index built.")
    index_file.write(str(filter_x) + ' ' + str(filter_y))
    index_file.close()
    print(str(i) + " images included. Index building finished.")


path = input("请输入目标文件夹路径: ")
extension = input("请输入图片扩展名: ")
filter_str = input("请输入想要筛查的分辨率，以逗号分隔(0,0表示不筛查): ")
filter = filter_str.split(',')
build_index(path, extension, filter)
