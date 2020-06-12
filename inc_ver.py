import sys

version = [0, 0, 0]

with open('BuildVer.h', 'r') as fin:
	for i in range(3):
		version[i] = int(fin.readline().split(' ')[-1])

if sys.argv[1] == '-m':
	version[0] += 1
if sys.argv[1] == '-n':
	version[1] += 1
if sys.argv[1] == '-b':
	version[2] += 1

with open('BuildVer.h', 'w') as fout:
	fout.write('#define BML_MAJOR_VER ' + str(version[0]) + '\n')
	fout.write('#define BML_MINOR_VER ' + str(version[1]) + '\n')
	fout.write('#define BML_BUILD_VER ' + str(version[2]) + '\n')