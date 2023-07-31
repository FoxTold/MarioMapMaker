import os

##check if folder build exists
if not os.path.exists('build'):
    os.makedirs('build')
    print("Created build directory")
os.chdir('build')
os.system('cmake .. -G "Visual Studio 17 2022" ')
