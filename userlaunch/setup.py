from setuptools import find_packages, setup
import glob, os

package_name = "userlaunch"
share_dir = "share/" + package_name

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (share_dir + "/launch", glob.glob(os.path.join("launch", "*.launch.py"))),
        (share_dir + "/param", glob.glob(os.path.join("param", "*.yaml"))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ubuntu',
    maintainer_email='ubuntu@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        ],
    },
)
