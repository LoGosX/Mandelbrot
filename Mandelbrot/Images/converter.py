import cv2
import os

path = os.path.realpath(__file__)

path = path[:len(path) - len('converter.py') - 1]

image_folder = input('Which folder to convert: ')

os.chdir(path)

number_of_images = len(os.listdir(image_folder))

images = ["{0}.jpg".format(i) for i in range(1,number_of_images + 1)]

frame = cv2.imread(os.path.join(image_folder, images[0]))
height, width, layers = frame.shape



video = cv2.VideoWriter('{0}.mp4'.format(image_folder), cv2.VideoWriter_fourcc(*'MP4V'), int(input('How much fps: ')), (width,height))

for i,image in enumerate(images):
    print('{0}/{1}'.format(i+1,len(images)))
    video.write(cv2.imread(os.path.join(image_folder, image)))

cv2.destroyAllWindows()
video.release()