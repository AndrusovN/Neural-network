from PIL import Image, ImageDraw, ImageFont
import os

alphabet = [chr(i) for i in range(65+26+6, 65+52+6)] + [chr(i) for i in range(65, 65+26)]

for _font in os.listdir("Fonts"):
    for letter in alphabet:
        image = Image.open("main.png")  # Открываем изображение.
        draw = ImageDraw.Draw(image)  # Создаем инструмент для рисования.
        width = image.size[0]  # Определяем ширину.
        height = image.size[1]  # Определяем высоту.
        img = image.load()

        for i in range(round(width)):
            for j in range(round(height)):
                draw.point((i, j), (255, 255, 255))
        font = ImageFont.truetype("Fonts\\" + _font, 20)
        draw.text((5, 0), letter, fill=(0, 0, 0), font=font)
        image.save("Data\\" + _font[:-4] + "_" + letter + ".png", "PNG")

        del draw


