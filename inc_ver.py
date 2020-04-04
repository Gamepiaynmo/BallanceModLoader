version = 0

with open('BuildVer.h', 'r') as fin:
	version = int(fin.readline().split(' ')[-1])

version += 1

with open('BuildVer.h', 'w') as fout:
	fout.write('#define BML_BUILD_VER ' + str(version))