
optimization_level="-O3"
filename=$1
macros=(" " "-DNOINLINE")
versions=(-11 -12)

for version in "${versions[@]}"
do
printf "\ng++$version \n"
for macro in "${macros[@]}"
do
g++$version gcc_interesting1.cpp $optimization_level  -o$filename $macro
./$filename
done
done
