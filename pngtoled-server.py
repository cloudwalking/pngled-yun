#bin/python

from __future__ import print_function
from PIL import Image
from threading import Timer
import numpy, time

pixels_per_second = 20
png = None

def printf(str0):
	print(str, end='')
	
def openPNG(filename):
  image = Image.open(filename);
  return numpy.asarray(image)

def out(column):
	for row in column:
		printf(chr(int(row[0])))
		printf(chr(int(row[1])))
		printf(chr(int(row[2])))

def step():
	# Send the start command.
	printf('\xf005ba11\x00');
	
	# Pick the proper column based on how much time has gone by.
	now = time.time()
	columns = png.shape[1]
	i = int((now * pixels_per_second) % columns)
	
	# Output row count.
	rows = png.shape[0]
	printf(chr(int(rows)))
	
	# Output full column.
	column = png[:,i]
	out(column)

if __name__ == "__main__":
	png = openPNG("data.png")
	
	def loop():
		step()
		t = Timer(0.01, loop)
		t.start()
		
	loop()
	
	# columns = png.shape[1]
	# rows = png.shape[0]
	# 
	# for i in range(0, columns):
	# 	printf('\xf005ba11\x00');
	# 	
	# 	for row in png[:,i]:
	# 		printf(chr(int(row[0])))
	# 		printf(chr(int(row[1])))
	# 		printf(chr(int(row[2])))
	
	