from retinaface import RetinaFace
import cv2
import matplotlib.pyplot as plt

img_path = "img.jpg"
img = cv2.imread(img_path)

obj = RetinaFace.detect_faces(img_path)
len(obj.keys())

for key in obj.keys():
    identity = obj[key]
    
    facial_area = identity["facial_area"]
    
    cv2.rectangle(img, (facial_area[2], facial_area[3]), (facial_area[0], facial_area[1]), (255,255,255), 1)

plt.figure(figsize = (10,10))
plt.imshow(img[:,:,::-1])
plt.show()

#RetinaFace

from deepface import DeepFace


obj = DeepFace.verify(img1_path = "img1.jpg", img2_path = "img2.jpg", model_name = 'ArcFace', detector_backend = 'retinaface')
obj



