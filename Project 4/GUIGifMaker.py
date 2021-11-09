import os
import imageio

file_directory = "project4.gif"
images_directory = "C:\\Users\\mathe\\source\\repos\\TSP\\TSP\\graph\\"
images = []
x = 0
for file in os.listdir(images_directory):
    try:
        images.append(imageio.imread(images_directory + "graph" + str(x) + ".jpeg"))
    except:
        None
    x+=1

kargs = {'duration' : 0.5}
if(x != 0):
    imageio.mimwrite(file_directory, images, **kargs)
