from PIL import Image, ImageDraw
import os

file = open("D:\\Dropbox_old\\никита\\Программы (1)\\c++\\NN_ML\\Data.csv", "w")
for image in os.listdir("Data\\"):
    print(image)
    img = Image.open("Data\\" + image)
    draw = ImageDraw.Draw(img)
    width = img.size[0]
    height = img.size[1]
    _img = img.load()
    for i in range(width):
        for j in range(height):
            file.write(str(round((_img[i, j][0] + _img[i, j][1] + _img[i, j][2]) / 3 / 256 * 1000) / 1000) + ";")
    alphabet = [chr(i) for i in range(65 + 26 + 6, 65 + 52 + 6)] + [chr(i) for i in range(65, 65 + 26)]
    for i in range(len(alphabet)):
        if(alphabet[i] == image[-5]):
            file.write("1;")
        else:
            file.write("0;")
    file.write("0;\n")

file.close()