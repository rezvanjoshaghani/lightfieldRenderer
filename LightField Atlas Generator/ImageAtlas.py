from PIL import Image
from os import listdir
from os.path import isfile, join


def generateAtlasFromStanfordImages(sourceDir, destDir, destFileName, gridRows, gridColumns, imageWidth, imageHeight):
    files = [f for f in listdir(sourceDir) if
             isfile(join(sourceDir, f))]

    finalWidth=gridColumns*imageWidth
    finalHeight=gridRows*imageHeight

    new_im = Image.new('RGB', (finalWidth,finalHeight))

    index = 0
    for i in range(0, finalWidth, imageWidth):
        for j in range(0, finalHeight, imageHeight):
            im = Image.open(sourceDir+files[index])
            im.thumbnail((imageWidth, imageHeight))
            new_im.paste(im, (i, j))
            index += 1
            print(index)

    new_im.save(destDir+destFileName)


generateAtlasFromStanfordImages("StanfordDataset/cristalBall/", "StanfordDataset/", "cristalBall_Atlas.jpg", 17, 17, 300, 300)