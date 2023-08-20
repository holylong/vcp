import os

# 假设图片文件都在images文件夹下
files = os.listdir("images")
# 按照数字大小排序
files.sort(key=lambda x: int(x[:-4])) # 去掉.jpg后缀再转换成整数
# 打印前十个文件名
print(files[:10])