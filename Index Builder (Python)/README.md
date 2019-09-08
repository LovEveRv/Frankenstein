# Index Builder 索引建立脚本
库需求：opencv-python

使用方法：在命令行运行脚本，根据提示依次输入图片文件夹路径、图片扩展名、预筛分辨率，即可开始建立索引。

+ 图片文件夹路径：需要建立索引的含有图片的文件夹的路径
+ 图片扩展名：指定文件的扩展名，输入格式形如 ".jpg" 。此扩展名以外的文件不会被写进索引
+ 预筛分辨率：指定图片的**最小**尺寸，宽高之间以半角逗号分隔。宽或高不足此尺寸的图片不会被写进索引。如果输入 "0,0" 则所有图片都会被写进索引。（但是注意，这会导致索引文件将所有图片中的最小宽度和最小高度设置为**最小**尺寸）

### 什么是索引文件？有什么用？
索引文件是图片文件夹下名为 "img_index" 的文件，需要使用索引建立脚本生成。索引文件为文件夹下的图片赋予编号，方便主程序进行处理。没有此文件的文件夹不能在主程序中被选为“源文件夹”。索引文件同时指定了图片的**最小**尺寸，大于此尺寸的图片在处理时只会考虑左上角等同于此尺寸大小的部分。