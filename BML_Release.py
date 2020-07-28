import os
import shutil

version = [0, 0, 0]

with open('BuildVer.h', 'r') as fin:
	for i in range(3):
		version[i] = int(fin.readline().split(' ')[-1])

shutil.rmtree('..\\dist', True)

dist_dir = '..\\dist\\BML-' + str(version[0]) + '.' + str(version[1]) + '.' + str(version[2]) + '-dist'
os.makedirs(dist_dir)

os.makedirs(dist_dir + '\\include\\BML')
shutil.copy('BMLAll.h', dist_dir + '\\include\\BML')
shutil.copy('BuildVer.h', dist_dir + '\\include\\BML')
shutil.copy('ExecuteBB.h', dist_dir + '\\include\\BML')
shutil.copy('Export.h', dist_dir + '\\include\\BML')
shutil.copy('Gui.h', dist_dir + '\\include\\BML')
shutil.copy('IBML.h', dist_dir + '\\include\\BML')
shutil.copy('ICommand.h', dist_dir + '\\include\\BML')
shutil.copy('IConfig.h', dist_dir + '\\include\\BML')
shutil.copy('ILogger.h', dist_dir + '\\include\\BML')
shutil.copy('IMod.h', dist_dir + '\\include\\BML')
shutil.copy('RegisterBB.h', dist_dir + '\\include\\BML')
shutil.copy('ScriptHelper.h', dist_dir + '\\include\\BML')
shutil.copy('Version.h', dist_dir + '\\include\\BML')
shutil.copytree('virtools', dist_dir + '\\include\\BML\\virtools', ignore = shutil.ignore_patterns('*.cpp'))

os.mkdir(dist_dir + '\\bin')
os.mkdir(dist_dir + '\\lib')

shutil.copy('D:\\Program Files (x86)\\Ballance\\BuildingBlocks\\BML.dll', dist_dir + '\\bin')
shutil.copy('D:\\Program Files (x86)\\Ballance\\BuildingBlocks\\BML.lib', dist_dir + '\\lib')

shutil.copy('Debug\\BML.dll', dist_dir + '\\bin\\BMLd.dll')
shutil.copy('Debug\\BML.lib', dist_dir + '\\lib\\BMLd.lib')

shutil.make_archive(dist_dir, 'zip', dist_dir)
