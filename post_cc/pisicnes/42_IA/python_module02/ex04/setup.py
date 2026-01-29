from setuptools import setup, find_packages

setup(
    name="my_minipack",
    version="1.0.0",
    author="mfernand",
    author_email="mfernand@student.42.fr",
    description="Howto create a package in python.",
    license="MIT",
    packages=find_packages(),
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Developers",
        "Intended Audience :: Students",
        "Topic :: Education",
        "Topic :: HowTo",
        "Topic :: Package",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3 :: Only",
    ],
    python_requires=">=3.7",
)
