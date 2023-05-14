from matplotlib import pyplot
from PIL import Image
from numpy import asarray
from mtcnn.mtcnn import MTCNN
 
def extract_face(filename, required_size=(224, 224)):
 
 pixels = pyplot.imread(filename)
 
 detector = MTCNN()
 
 results = detector.detect_faces(pixels)
 
 x1, y1, width, height = results[0]['box']
 x2, y2 = x1 + width, y1 + height
 
 face = pixels[y1:y2, x1:x2]
 
 image = Image.fromarray(face)
 image = image.resize(required_size)
 face_array = asarray(image)
 return face_array
 
pixels = extract_face('000019.jpg')
pyplot.imshow(pixels)
pyplot.show()
