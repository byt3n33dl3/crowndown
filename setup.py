"""
MIT License

Copyright (c) 2020-2024 CappaX ( Sulaiman ) - EntySec

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
"""

from setuptools import setup, find_packages

setup(name='crowndown',
      version='2.0.0',
      description=(
          'CrownTouchDown is a exploitation framework for smartphone that exploits the'
          ' android && iOS debug bridge to remotely access an smartphone.'
      ),
      url='https://github.com/pxcs/crowndown',
      author='pxcs',
      author_email='pxmxx3csz@outlook.com',
      license='MIT, OSL',
      python_requires='>=3.9.0',
      packages=find_packages(),
      include_package_data=True,
      entry_points={
          "console_scripts": [
              "crowndown = crowndown:cli"
          ]
      },
      install_requires=[
          'adb-shell',
          'pex @ git+https://github.com/EntySec/Pex',
          'badges @ git+https://github.com/EntySec/Badges',
          'colorscript @ git+https://github.com/EntySec/ColorScript'
      ],
      zip_safe=False
      )
