# About: \
In this code we measure the effect of inlining on virtual and non virtual functions using different g++ versions

# Requirements: \
g++ version 11 and 12 on Linux operating system

# Run: \
use an executable filename
and run build.sh like : ./build.sh filename

# Expectations: \
We asume that virtual functions should be slower and disallow inlining does not speed up code

# Results: \
The measurements show that virtual functions with same g++ version and same inlining characteristics is slower than
non virtual functions but, it is a verry intereting fact, disallowing inlining can exploit more optimization ability from compiler.  
