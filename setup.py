import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="resurgance_renderer-Jellohunter7", 
    version="0.0.1",
    author="Rachit Kakkar",
    author_email="rachitkakkar7@gmail.com",
    description="resurgance_renderer is an easy to use library used to generate 3D scenes, and can be easily scripted/extended with python",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/pypa/sampleproject",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.6',
)
